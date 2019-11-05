#include "TXLin.h"
#include "nekodimensions.h"
#include "cat.h"

int main(int argc, const char** argv) {
    txCreateWindow(NEKO_WIDTH, NEKO_HEIGHT);
    txSetFillColor(RGB(255, 255, 255));
    txClear();
    Cat* purr = new Cat();
    purr->drawIdle(txDC(), RGB(0, 0, 0), 12, 12);
    txSticky();
    return 0;
}
