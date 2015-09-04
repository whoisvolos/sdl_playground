#include <tiny_obj_loader.h>
#include "TinyObjUtils.h"

void TinyObjUtils::normalize(std::vector<shape_t>& shapes) {
    GLfloat min = std::numeric_limits<GLfloat>::min();
    GLfloat max = std::numeric_limits<GLfloat>::max();
    GLfloat minBox[3] = { max, max, max }, maxBox[3] = { min, min, min };

    for (auto shape : shapes) {
        auto positions = shape.mesh.positions;
        for (int i = 0; i < positions.size(); i += 3) {
            for (int k = 0; k < 3; ++k) {
                auto coord = positions[i + k];
                if (coord < minBox[k]) {
                    minBox[k] = coord;
                }
                if (coord > maxBox[k]) {
                    maxBox[k] = coord;
                }
            }
        }
    }

    GLfloat cubeLen = std::max(std::max(maxBox[0] - minBox[0], maxBox[1] - minBox[1]), maxBox[2] - minBox[2]);

    for (auto shape : shapes) {
        auto positions = shape.mesh.positions;
        for (unsigned long i = 0, l = positions.size(); i < l; ++i) {
            *(positions.data() + i) = 0;
        }
    }
}