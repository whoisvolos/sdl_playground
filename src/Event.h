#pragma once

#include <SDL.h>

namespace Event {
    const int UE_FPS = 1;

    inline SDL_Event getFillFPSEvent() {
        SDL_UserEvent userEvent;
        userEvent.type = SDL_USEREVENT;
        userEvent.code = UE_FPS;
        SDL_Event event;
        event.type = SDL_USEREVENT;
        event.user = userEvent;
        return event;
    };
}