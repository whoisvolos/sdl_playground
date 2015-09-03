#pragma once

#include <GL/glew.h>
#include "tiny_obj_loader.h"

using namespace tinyobj;

class TinyObjUtils {
public:
    static void normalize(std::vector<shape_t>& shapes);
};
