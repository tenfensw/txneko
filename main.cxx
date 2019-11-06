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
    unsigned centerX = (params->width / 2) - 16;
    unsigned centerY = (params->height / 2) - 16;
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
                        centerX -= 40;
                        drawCat("left1", centerX, centerY);
                        txSleep(params->speed);
                    }
                }
                else {
                    while (mouseX >= centerX) {
                        drawCat("right2", centerX, centerY);
                        txSleep(params->speed);
                        centerX += 40;
                        drawCat("right1", centerX, centerY);
                        txSleep(params->speed);
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
                        centerY += 40;
                        drawCat("down1", centerX, centerY);
                        txSleep(params->speed);
                    }
                }
                else {
                    while (centerY >= mouseY) {
                        drawCat("up2", centerX, centerY);
                        txSleep(params->speed);
                        centerY -= 40;
                        drawCat("up1", centerX, centerY);
                        txSleep(params->speed);
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
