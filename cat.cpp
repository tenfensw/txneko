#include "cat.h"

Cat::Cat(unsigned length) {
    lengthCoef = length;
    printf("meowie\n");
}

Cat::~Cat() {
    printf("bye\n");
}


void Cat::drawIdle(HDC graphicsContext, COLORREF clr, unsigned x, unsigned y) {
    if (!graphicsContext)
        return;
    txSetColor(clr, 1, graphicsContext);
    txLine(x, y, x, y + lengthCoef, graphicsContext);
    txLine(x, y, x + lengthCoef, y + lengthCoef, graphicsContext);
    unsigned middleHeadEndpoint = x + lengthCoef + (lengthCoef / 2);
    txLine(x + lengthCoef, y + lengthCoef, middleHeadEndpoint, y + lengthCoef, graphicsContext);
    txLine(middleHeadEndpoint, y + lengthCoef, middleHeadEndpoint + (lengthCoef / 2), y + lengthCoef, graphicsContext);
    middleHeadEndpoint += (lengthCoef / 2);
    txLine(middleHeadEndpoint, y + lengthCoef, middleHeadEndpoint + lengthCoef, y, graphicsContext);
    txLine(middleHeadEndpoint + lengthCoef, y, middleHeadEndpoint + lengthCoef, y + lengthCoef, graphicsContext);
    txLine(x, y + lengthCoef, x, y + (lengthCoef * 2), graphicsContext);
    txLine(middleHeadEndpoint + lengthCoef, y + lengthCoef, middleHeadEndpoint + lengthCoef, y + (lengthCoef * 2), graphicsContext);
    unsigned neck = x + lengthCoef;
    txLine(x, y + (lengthCoef * 2), neck, y + (lengthCoef * 3), graphicsContext);
    neck = middleHeadEndpoint;
    txLine(middleHeadEndpoint + lengthCoef, y + (lengthCoef * 2), neck, y + (lengthCoef * 3), graphicsContext);
    txSetPixel(x + 4, y + lengthCoef + 4, clr, graphicsContext);
    txSetPixel(middleHeadEndpoint + lengthCoef - 4, y + lengthCoef + 4, clr, graphicsContext);
    unsigned headCenter = middleHeadEndpoint - (lengthCoef / 2);
    txLine(headCenter, y + lengthCoef + 6, headCenter - 2, y + lengthCoef + 7, graphicsContext);
    txLine(headCenter, y + lengthCoef + 6, headCenter + 2, y + lengthCoef + 7, graphicsContext);
}

