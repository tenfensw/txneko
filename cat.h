#include "TXLin.h"
#include <cstdlib>
#include <cstdio>

class Cat {
    public:
        Cat(unsigned length = 5);
        ~Cat();
    
        void drawIdle(HDC graphicsContext, COLORREF clr, unsigned x, unsigned y);
    
    protected:
        unsigned lengthCoef;
};
