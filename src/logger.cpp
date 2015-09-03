#include "logger.h"

void utils::logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

void utils::logSDLTTFError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << TTF_GetError() << std::endl;
}
