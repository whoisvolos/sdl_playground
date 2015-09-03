#pragma once

#include <sstream>
#include <SDL_ttf.h>
#include "AppContainer.h"
#include "logger.h"
#include "Color.h"
#include "Event.h"
#include "SpringModel.h"
#include "ColorLinesModel.h"
#include <glm/glm.hpp>

class SpacexContainer : public AppContainer {
private:
    // Surface representing screen
    SDL_Surface* screen;
    // Texture bound to screen surface
    SDL_Texture* screenTex;

    TTF_Font *font;
    SDL_Surface* fpsSurface;
    SDL_Rect fpsRect;

    SDL_TimerID fpsTimerId;
    static unsigned int onFPSTimer(unsigned int interval, void *param);

    ColorLinesModel colorLines;

public:
    virtual void onEvent(SDL_Event& event) override;
    virtual void onTick(float update) override;
    virtual void onRender() override;
    virtual int afterInit() override;

    SpacexContainer(const char *name);
    ~SpacexContainer();
};