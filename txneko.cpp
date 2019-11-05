#include "TXLin.h"
#include "nekodimensions.h"
#include "cat.h"

int main(int argc, const char** argv) {
    txCreateWindow(NEKO_WIDTH, NEKO_HEIGHT);
    txSetFillColor(RGB(255, 255, 255));
    txClear();
    Cat* purr = new Cat(NEKO_LENGTHPT);
    purr->drawIdle(txDC(), NEKO_COLOR, 12, 12);
    txSticky();
    delete purr;
    return 0;
}
