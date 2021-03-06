#include "AppContainer.h"

using namespace utils;

AppContainer::AppContainer(const char* name): running(false), windowName(name) { }

int AppContainer::init(int width, int height, bool onlyOpenGL) {
    this->width = width;
    this->height = height;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError(std::cerr, "Init");
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    window = SDL_CreateWindow(
        windowName,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
    );
    if (window == nullptr) {
        logSDLError(std::cerr, "SDL_CreateWindow");
        return 1;
    }

    if (!onlyOpenGL) {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            logSDLError(std::cerr, "SDL_CreateRenderer");
            return 1;
        }
        SDL_PixelFormatEnumToMasks(SDL_PIXELFORMAT_ARGB8888, &bpp, &rMask, &gMask, &bMask, &aMask);
    }

    prevUpdate = 0;
    ticks = 0;

    return afterInit();
}

AppContainer::~AppContainer() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

int AppContainer::afterInit() {
    return 0;
}

void AppContainer::onTick(float update) {

}

void AppContainer::onEvent(SDL_Event& event) {

}

void AppContainer::onRender() {
    if (renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}

void AppContainer::onResize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
}

void AppContainer::stop() {
    running = false;
}

int AppContainer::run() {
    running = true;
    SDL_Event event;
    ticks = SDL_GetPerformanceCounter();
    while(running) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case (SDL_QUIT): {
                    stop();
                    break;
                }
                case (SDL_WINDOWEVENT): {
                    if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        onResize(event.window.data1, event.window.data2);
                    }
                    break;
                }
                default:
                    break;
            }
            onEvent(event);
        }
        if (running) {
            // Time calculation
            unsigned long newTicks = SDL_GetPerformanceCounter();
            float update = (float)(newTicks - ticks) / 1000000;
            onTick(update);
            ticks = newTicks;

            // FPS calculation
            prevUpdate = fabs(prevUpdate) < EPS ? update : (prevUpdate + update) / 2;

            // Rendering
            onRender();
        }
    }
    return 0;
}

float AppContainer::getFPS() {
    return fabs(prevUpdate) < EPS ? 0 : (1000 / prevUpdate);
}
