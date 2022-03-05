#ifndef __EDPPAINTEXT_H
#define __EDPPAINTEXT_H

#include "epdpaint.h"

class PaintExt
{
public:
    PaintExt(Paint *, Epd *);
    ~PaintExt(void);
    void DrawBitmap(uint8_t *, int16_t, int16_t, int16_t, int16_t, int16_t);
    bool AppendChar(uint8_t *, uint8_t, uint8_t, uint8_t);
    void NewPage(uint16_t, uint16_t);

private:
    Paint *wPaint;
    uint16_t X, Y, Width, Height;
    uint8_t maxy;
    Epd *epd;
};
#endif