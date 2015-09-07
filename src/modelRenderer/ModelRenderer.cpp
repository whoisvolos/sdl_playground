#include <tiny_obj_loader.h>
#include "ModelRenderer.h"
#include "TinyObjUtils.h"

using namespace utils;

ModelRenderer::ModelRenderer(const char* name, const char*modelFile)
        : AppContainer(name),
          modeFile(modelFile) {}

ModelRenderer::~ModelRenderer() {
    if (glContext) {
        SDL_GL_DeleteContext(glContext);
    }
}

int ModelRenderer::afterInit() {
    std::string err = LoadObj(shapes, materials, modeFile);
    if (!err.empty()) {
        std::cerr << err << std::endl;
        return 1;
    }

    std::cout << "Model shapes: " << shapes.size() << std::endl << std::endl;
    for (auto shape : shapes) {
        std::cout << "Shape: " << shape.name << std::endl;
        std::cout << "Faces: " << shape.mesh.indices.size() / 3 << std::endl;
        std::cout << "Vertices: " << shape.mesh.positions.size() / 3 << std::endl << std::endl;
    }

    TinyObjUtils::normalize(shapes);

    // Init GL context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        logSDLError(std::cerr, "SDL_GL_CreateContext");
        return 1;
    }

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        std::cerr << "Error initializing GLEW: " << glewGetErrorString(glewError) << std::endl;
        return 1;
    }

    if (!GLEW_VERSION_2_1) {
        std::cerr << "GLEW version 2.1 and higher required" << std::endl;
        return 1;
    }

    if (SDL_GL_SetSwapInterval(1) < 0) {
        logSDLError(std::cerr, "SDL_GL_SetSwapInterval");
        return 1;
    }

    /*
    program = new OpenGLShaderProgram;
    if (program->addShaderFromSourceFile(OpenGLShaderProgram::VertexType, "/Users/sgolubev/repos/cpp_projects/sdl_playground/shaders/mvp.vert") != 0 ||
        program->addShaderFromSourceFile(OpenGLShaderProgram::FragmentType, "/Users/sgolubev/repos/cpp_projects/sdl_playground/shaders/simple.frag") != 0) {
        return 1;
    }

    //program->bindAttribLocation("vertex", 0);
    if (program->link() != 0) {
        return 1;
    }

    vao = new OpenGLVAO();
    vao->bind();
    vertices = OpenGLBuffer::arrayBuffer();
    //indices = OpenGLBuffer::indexBuffer();
    mesh_t& mesh = shapes[0].mesh;
    vertices->setData(sizeof(GLfloat), mesh.positions.size(), mesh.positions.data(), GL_STATIC_DRAW);
    //indices->setData(sizeof(unsigned int), mesh.indices.size(), mesh.indices.data(), GL_STATIC_DRAW);

    printf("%lu\n", indices->count());

    vertices->setPointerForProgram(program, "vertex", 3, GL_FLOAT);
    vertices->release();

    cameraMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -2));
    worldMatrix = glm::mat4(1.0);
    projectionMatrix = glm::perspective(45.0f, (float)width/height, 0.01f, 100.0f);

    program->bind();

    program->setUniform("projMatrix", projectionMatrix);
    program->setUniform("worldMatrix", worldMatrix);
    program->setUniform("cameraMatrix", cameraMatrix);

    program->release();

    glClearColor(0.5, 0.5, 0.5, 1.0);
    */

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(2, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

    mesh_t& mesh = shapes[0].mesh;
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBufferData(GL_ARRAY_BUFFER, mesh.positions.size() * sizeof(GLfloat) * 2, mesh.positions.data(), GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, mesh.positions.size() * sizeof(GLfloat), mesh.normals.size() * sizeof(GLfloat), mesh.normals.data());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<const void *>(mesh.positions.size() * sizeof(GLfloat)));

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GL_UNSIGNED_INT), mesh.indices.data(), GL_STATIC_DRAW);

    size_t len;
    vertexSource = OpenGLShaderProgram::readFile("/Users/sgolubev/repos/cpp_projects/sdl_playground/shaders/mvp.vert", len);
    fragmentSource = OpenGLShaderProgram::readFile("/Users/sgolubev/repos/cpp_projects/sdl_playground/shaders/simple.frag", len);
    if (!vertexSource) {
        std::cerr << "Can not load vshader" << std::endl;
        return 1;
    }
    if (!fragmentSource) {
        std::cerr << "Can not load fshader" << std::endl;
        return 1;
    }

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
    glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        std::cerr << "Can not compile vshader" << std::endl;
        return 1;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status) {
        std::cerr << "Can not compile fshader" << std::endl;
        return 1;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (!status) {
        std::cerr << "Can not link shaders" << std::endl;
        GLint maxLen;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLen);
        char* linkInfoLog = new char[maxLen];
        glGetProgramInfoLog(shaderProgram, maxLen, &maxLen, linkInfoLog);
        std::cerr << linkInfoLog << std::endl;
        delete[] linkInfoLog;
        return 1;
    }

    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glUseProgram(shaderProgram);
    worldMatrix = glm::mat4(1.0);
    cameraMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -100));
    projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f * width / height, 0.01f, 1000.0f);
    normalMatrix = glm::mat3(worldMatrix);//glm::inverseTranspose(glm::mat3(worldMatrix));
    lightPos = glm::vec3(100, 0, 100);
    auto wmLoc = glGetUniformLocation(shaderProgram, "worldMatrix");
    auto cmLoc = glGetUniformLocation(shaderProgram, "cameraMatrix");
    auto pmLoc = glGetUniformLocation(shaderProgram, "projMatrix");
    auto nmLoc = glGetUniformLocation(shaderProgram, "normalMatrix");
    auto lpLoc = glGetUniformLocation(shaderProgram, "lightPos");
    glUniformMatrix4fv(wmLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
    glUniformMatrix4fv(cmLoc, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
    glUniformMatrix4fv(pmLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix3fv(nmLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glUniform3fv(lpLoc, 1, glm::value_ptr(lightPos));
    //glUniform3f(lpLoc, lightPos.x, lightPos.y, lightPos.z);
    glUseProgram(0);

    return 0;
}

void ModelRenderer::logProgramParams() const {
    /*
    auto unifs = program->getAllUniforms();
    std::cout << "Uniforms:" << std::endl;
    for (auto u : unifs) {
        printf("%s, type: %s, totalSize: %i\n", u.name.c_str(), program->getTypeName(u.type), u.size);
    }
    std::cout << "Attributes:" << std::endl;
    auto attribs = program->getAllAttributes();
    for (auto a : attribs) {
        printf("%s, type: %s, totalSize: %i, index: %i\n", a.name.c_str(), program->getTypeName(a.type), a.size, a.index);
    }
    */
}

void ModelRenderer::onRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    auto wmLoc = glGetUniformLocation(shaderProgram, "worldMatrix");
    auto pmLoc = glGetUniformLocation(shaderProgram, "projMatrix");
    auto nmLoc = glGetUniformLocation(shaderProgram, "normalMatrix");
    glUniformMatrix4fv(wmLoc, 1, GL_FALSE, glm::value_ptr(worldMatrix));
    glUniformMatrix4fv(pmLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix3fv(nmLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glDrawElements(GL_TRIANGLES, shapes[0].mesh.indices.size(), GL_UNSIGNED_INT, 0);
    glUseProgram(0);

    SDL_GL_SwapWindow(window);
}

void ModelRenderer::onTick(float update) {
    worldMatrix = glm::rotate(worldMatrix, glm::radians(update / 8.0f), glm::vec3(0, 1, 0));
    normalMatrix = glm::mat3(worldMatrix);//glm::inverseTranspose(glm::mat3(worldMatrix));
}

void ModelRenderer::onResize(int newWidth, int newHeight) {
    AppContainer::onResize(newWidth, newHeight);
    printf("Resized to %i x %i\n", width, height);
    projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f * width / height, 0.01f, 1000.0f);
    glViewport(0, 0, width, height);
}

void ModelRenderer::onEvent(SDL_Event &event) {

}