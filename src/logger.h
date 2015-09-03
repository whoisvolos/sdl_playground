#pragma once

#include <ostream>
#include <SDL.h>
#include <SDL_ttf.h>

namespace utils {
    void logSDLError(std::ostream &os, const std::string &msg);
    void logSDLTTFError(std::ostream &os, const std::string &msg);
}