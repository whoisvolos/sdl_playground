#pragma once

class ColorLinesModel {
public:
    int numRectsX;
    int numRectsY;
    int rectWidth;
    int rectHeight;

    ColorLinesModel() {}

    ColorLinesModel(int numRectsX, int numRectsY, int rectWidth, int rectHeight):
        numRectsX(numRectsX),
        numRectsY(numRectsY),
        rectWidth(rectWidth),
        rectHeight(rectHeight) { }

    int getCenteredX(int width) {
        return width / 2 - (rectWidth * numRectsX / 2);
    }

    int getCenteredY(int height) {
        return height / 2 - (rectHeight * numRectsY / 2);
    }
};
