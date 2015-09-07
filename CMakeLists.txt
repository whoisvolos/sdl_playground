cmake_minimum_required(VERSION 3.2)
project(sdl_playground)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(EXT_DIR ${PROJECT_SOURCE_DIR}/ext)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

#find_package(CURL REQUIRED)
#include_directories(${CURL_INCLUDE_DIRS})

set(SOURCE_FILES
        src/main.cpp
        src/res_path.h
        src/logger.h
        src/logger.cpp
        src/AppContainer.cpp
        src/AppContainer.h
        src/SpacexContainer.cpp
        src/SpacexContainer.h
        src/Color.h
        src/Event.h
        src/SpringModel.cpp
        src/SpringModel.h
        src/ColorLinesModel.h
        src/modelRenderer/ModelRenderer.cpp
        src/modelRenderer/ModelRenderer.h src/modelRenderer/OpenGLShaderProgram.cpp src/modelRenderer/OpenGLShaderProgram.h src/modelRenderer/OpenGLBuffer.cpp src/modelRenderer/OpenGLBuffer.h src/modelRenderer/OpenGLVAO.cpp src/modelRenderer/OpenGLVAO.h src/modelRenderer/TinyObjUtils.cpp src/modelRenderer/TinyObjUtils.h src/modelRenderer/FuncModel.cpp src/modelRenderer/FuncModel.h)

#Tiny obj loader files
set(TINY_OBJ_LOADER_INCLUDE_DIR "${EXT_DIR}/tinyloader")
include_directories(${TINY_OBJ_LOADER_INCLUDE_DIR})
add_library(tinyobjloader STATIC IMPORTED)
set_property(TARGET tinyobjloader PROPERTY
    IMPORTED_LOCATION ${EXT_DIR}/tinyloader/libtinyobjloader.a)

add_executable(sdl_playground ${SOURCE_FILES})

#target_link_libraries(sdl_playground ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${CURL_LIBRARIES} tinyobjloader)
target_link_libraries(sdl_playground ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} tinyobjloader)