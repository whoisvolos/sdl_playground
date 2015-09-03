#include <tiny_obj_loader.h>
#include "ModelRenderer.h"
#include "TinyObjUtils.h"

using namespace utils;

ModelRenderer::ModelRenderer(const char* name, const char*modelFile)
        : AppContainer(name),
          modeFile(modelFile),
          program(nullptr) {}

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
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

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

    vao = new OpenGLVAO();
    vao->bind();
    vertices = OpenGLBuffer::arrayBuffer();
    indices = OpenGLBuffer::indexBuffer();
    mesh_t& mesh = shapes[0].mesh;
    vertices->setData(sizeof(GLfloat) * mesh.positions.size(), mesh.positions.data(), GL_STATIC_DRAW);
    indices->setData(sizeof(unsigned int) * mesh.indices.size(), mesh.indices.data(), GL_STATIC_DRAW);

    program = new OpenGLShaderProgram;
    if (program->addShaderFromSourceFile(OpenGLShaderProgram::VertexType, "/Users/sgolubev/repos/cpp_projects/sdl_playground/shaders/mvp.vert") != 0 ||
        program->addShaderFromSourceFile(OpenGLShaderProgram::FragmentType, "/Users/sgolubev/repos/cpp_projects/sdl_playground/shaders/simple.frag") != 0) {
        return 1;
    }

    //program->bindAttribLocation("vertex", 0);
    if (program->link() != 0) {
        return 1;
    }

    vertices->setPointerForProgram(program, "vertex", 3, GL_FLOAT);
    cameraMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -2));
    worldMatrix = glm::mat4(1.0);
    projectionMatrix = glm::perspective(glm::radians(90.0f), (float)width/height, 0.01f, 100.0f);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    return 0;
}

void ModelRenderer::logProgramParams() const {
    auto unifs = program->getAllUniforms();
    std::cout << "Uniforms:" << std::endl;
    for (auto u : unifs) {
        printf("%s, type: %s, size: %i\n", u.name.c_str(), program->getTypeName(u.type), u.size);
    }
    std::cout << "Attributes:" << std::endl;
    auto attribs = program->getAllAttributes();
    for (auto a : attribs) {
        printf("%s, type: %s, size: %i, index: %i\n", a.name.c_str(), program->getTypeName(a.type), a.size, a.index);
    }
}

void ModelRenderer::onRender() {
    /*
    vao->bind();
    program->bind();

    program->setUniform("projMatrix", projectionMatrix);
    program->setUniform("worldMatrix", worldMatrix);
    program->setUniform("cameraMatrix", cameraMatrix);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapWindow(window);

    program->release();
    */

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}

void ModelRenderer::onTick(float update) {

}

void ModelRenderer::onEvent(SDL_Event &event) {

}