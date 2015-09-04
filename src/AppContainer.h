#pragma once

#include <SDL.h>
#include <iostream>
#include "logger.h"

#define EPS 0.000001

class AppContainer {
private:
    bool running;
    unsigned long ticks = 0;
    float prevUpdate = 0;

protected:
    int width = 0, height = 0;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    const char* windowName = nullptr;

    unsigned int rMask, bMask, gMask, aMask;
    int bpp = 32;

public:
    AppContainer(const char* name);
    virtual ~AppContainer();

    int init(int width, int height, bool onlyOpenGl = false);
    int run();
    void stop();
    float getFPS();

    virtual int afterInit();
    virtual void onTick(float update);
    virtual void onEvent(SDL_Event& event);
    virtual void onRender();
};
