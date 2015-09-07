#include "SpacexContainer.h"

using namespace utils;
using namespace glm;

SpacexContainer::SpacexContainer(const char* name)
        : AppContainer(name),
          fpsTimerId(0),
          fpsSurface(nullptr) {}

SpacexContainer::~SpacexContainer() {
    if (fpsTimerId) {
        SDL_RemoveTimer(fpsTimerId);
    }
    if (fpsSurface) {
        SDL_FreeSurface(fpsSurface);
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(screenTex);
    SDL_FreeSurface(screen);
}

int SpacexContainer::afterInit() {
    screen = SDL_CreateRGBSurface(0, width, height, bpp, rMask, gMask, bMask, aMask);
    if (!screen) {
        logSDLError(std::cerr, "SDL_CreateRGBSurface");
        return 1;
    }
    screenTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!screenTex) {
        logSDLError(std::cerr, "SDL_CreateTexture");
        return 1;
    }
    if (TTF_Init() != 0) {
        logSDLTTFError(std::cerr, "SDL_CreateTexture");
        return 1;
    }
    font = TTF_OpenFont("/Library/Fonts/Verdana.ttf", 11);
    if (!font) {
        logSDLTTFError(std::cerr, "TTF_OpenFont");
        return 1;
    }

    fpsTimerId = SDL_AddTimer(1000, onFPSTimer, this);

    colorLines = ColorLinesModel(16, 16, 20, 20);

    return 0;
}

void SpacexContainer::onEvent(SDL_Event &event) {
    switch (event.type) {
        case (SDL_USEREVENT): {
            switch (event.user.code) {
                case Event::UE_FPS: {
                    if (fpsSurface) {
                        SDL_FreeSurface(fpsSurface);
                        fpsSurface = nullptr;
                    }
                    std::stringstream ss;
                    ss << "FPS: " << (int)round(getFPS()) << ", " << width << "x" << height;
                    fpsSurface = TTF_RenderText_Solid(font, ss.str().c_str(), Color::white);
                    fpsRect = { 10, 10, fpsSurface->clip_rect.w, fpsSurface->clip_rect.h };
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
}

void SpacexContainer::onTick(float update) {
    int x, y;
    SDL_GetMouseState(&x, &y);
}

void SpacexContainer::onRender() {
    SDL_FillRect(screen, NULL, 0x00000000);

    int topX = colorLines.getCenteredX(width);
    int topY = colorLines.getCenteredY(height);
    for (int y = 0; y < colorLines.numRectsY; ++y) {
        for (int x = 0; x < colorLines.numRectsX; ++x) {
            SDL_Rect rect = { colorLines.rectWidth * x + topX, colorLines.rectHeight * y + topY, colorLines.rectWidth - 1, colorLines.rectHeight - 1 };
            SDL_FillRect(screen, &rect, SDL_MapRGBA(screen->format, 255, 255, 255, 255));
        }
    }

    // FPS on top
    if (fpsSurface) {
        SDL_BlitSurface(fpsSurface, NULL, screen, &fpsRect);
    }

    SDL_UpdateTexture(screenTex, NULL, screen->pixels, screen->pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, screenTex, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void SpacexContainer::onResize(int newWidth, int newHeight) {
    AppContainer::onResize(newWidth, newHeight);
    SDL_DestroyTexture(screenTex);
    SDL_FreeSurface(screen);
    screen = SDL_CreateRGBSurface(0, width, height, bpp, rMask, gMask, bMask, aMask);
    screenTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
}

unsigned int SpacexContainer::onFPSTimer(unsigned int interval, void *param) {
    SDL_Event event = Event::getFillFPSEvent();
    SDL_PushEvent(&event);
    return interval;
}