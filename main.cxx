/*
 TXNeko - a port of XNeko to TXLin
 Copyright (C) 2019 Tim K <timprogrammer@rambler.ru>
 
 Graphical assets: Copyright (C) 1990 Masayuki Koba
 (Artwork license was not specified in XNeko source code, if you are
 the owner of the artwork bundled with XNeko and TXNeko, please email
 me and I will remove it.)

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "TXLin.h"
#include "TXCairo.h"
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>

struct txneko_args {
    unsigned width;
    unsigned height;
    unsigned speed;
    unsigned stepping;
};

typedef struct txneko_args txneko_args_t;

char* strfrom(const char* in, unsigned index) {
    unsigned diff = strlen(in) - index;
    char* result = (char*)(calloc(diff + 1, sizeof(char)));
    for (unsigned id = index; id < strlen(in); id++) {
        unsigned id2 = id - index;
        result[id2] = in[id];
    }
    return result;
}

txneko_args_t* parseArgs(int argc, const char** argv) {
    txneko_args_t* structure = (txneko_args_t*)(malloc(sizeof(txneko_args_t)));
    structure->width = 480;
    structure->height = 320;
    structure->speed = 200;
    structure->stepping = 40;
    for (int i = 0; i < argc; i++) {
        const char* arg = argv[i];
        if (strlen(arg) >= 3 && arg[0] == '-') {
            char* substStr = strfrom(arg, 2);
            if (arg[1] == 'w')
                structure->width = atoi(substStr);
            else if (arg[1] == 'h')
                structure->height = atoi(substStr);
            else if (arg[1] == 's')
                structure->speed = atoi(substStr);
            else if (arg[1] == 'i')
                structure->stepping = atoi(substStr);
        }
    }
    return structure;
}

void drawCat(const char* state, unsigned whereX, unsigned whereY) {
    txSetFillColor(TX_WHITE);
    txClear();
    char* txPath = (char*)(calloc(256, sizeof(char)));
    strcpy(txPath, "png/");
    strcat(txPath, state);
    strcat(txPath, ".png");
    txBlitPNG(txPath, txDC(), whereX, whereY);
    free(txPath);
}

void comfortMousePos(unsigned* x, unsigned* y) {
    if (!x || !y)
        return;
    POINT mpos = txMousePos();
    (*x) = mpos.x;
    (*y) = mpos.y;
}

int main(int argc, const char** argv) {
    txneko_args_t* params = parseArgs(argc, argv);
    txCreateWindow(params->width, params->height);
    int centerX = (params->width / 2) - 16;
    int centerY = (params->height / 2) - 16;
    drawCat("sleep1", centerX, centerY);
    unsigned mouseX = 0;
    unsigned mouseY = 0;
    while (true) {
        txSleep(50);
        unsigned oldMouseX = mouseX;
        unsigned oldMouseY = mouseY;
        comfortMousePos(&mouseX, &mouseY);
        if (GetAsyncKeyState(VK_DOWN))
            return 0;
        else if (oldMouseX != mouseX || oldMouseY != mouseY) {
            drawCat("awake", centerX, centerY);
            txSleep(1000);
            if (centerX != mouseX) {
                if (mouseX < centerX) {
                    while (mouseX <= centerX) {
                        drawCat("left2", centerX, centerY);
                        txSleep(params->speed);
                        centerX -= params->stepping;
                        if (centerX <= 0)
                            centerX = 0;
                        drawCat("left1", centerX, centerY);
                        txSleep(params->speed);
                        comfortMousePos(&mouseX, &mouseY);
                    }
                }
                else {
                    while (mouseX >= centerX) {
                        drawCat("right2", centerX, centerY);
                        txSleep(params->speed);
                        centerX += params->stepping;
                        if (centerX >= params->width)
                            centerX -= params->stepping * 2;
                        drawCat("right1", centerX, centerY);
                        txSleep(params->speed);
                        comfortMousePos(&mouseX, &mouseY);
                    }
                }
            }
            centerX = mouseX;
            drawCat("mati2", centerX, centerY);
            if (centerY != mouseY) {
                if (mouseY > centerY) {
                    while (centerY <= mouseY) {
                        drawCat("down2", centerX, centerY);
                        txSleep(params->speed);
                        centerY += params->stepping;
                        if (centerY >= params->height)
                            centerY -= params->stepping * 2;
                        drawCat("down1", centerX, centerY);
                        txSleep(params->speed);
                        comfortMousePos(&mouseX, &mouseY);
                    }
                }
                else {
                    while (centerY >= mouseY) {
                        drawCat("up2", centerX, centerY);
                        txSleep(params->speed);
                        centerY -= params->stepping;
                        if (centerY <= 0)
                            centerY = 0;
                        drawCat("up1", centerX, centerY);
                        txSleep(params->speed);
                        comfortMousePos(&mouseX, &mouseY);
                    }
                }
            }
            centerY = mouseY;
            drawCat("awake", centerX, centerY);
            txSleep(100);
            drawCat("mati3", centerX, centerY);
            txSleep(500);
            drawCat("sleep1", centerX, centerY);
        }
    }
    return 1;
}
