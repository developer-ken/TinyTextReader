#include "sdfont.h"
#include "epdpaintext.h"
#include "epdpaint.h"
#include "epd2in13.h"
#include <arduino.h>
#include <SPI.h>
#include <SD.h>
#include <stdint.h>

PaintExt::PaintExt(Paint *paint, Epd *epd)
{
    this->wPaint = paint;
    this->epd = epd;
    this->X = 0;
    this->Y = 0;
    this->maxy = 0;
}

PaintExt::~PaintExt(void)
{
}

void PaintExt::DrawBitmap(uint8_t *bitmap, int16_t x, int16_t y, int16_t w, int16_t h, int16_t color)
{
    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    for (int16_t j = 0; j < h; j++)
    {
        for (int16_t i = 0; i < w; i++)
        {
            if (i & 7)
                byte <<= 1;
            else
                byte = bitmap[j * byteWidth + i / 8];
            if (byte & 0x80)
                this->wPaint->DrawPixel(x + i, y + j, color);
        }
    }
}

bool PaintExt::AppendChar(uint8_t *bitmap, uint8_t width, uint8_t height, uint8_t colored)
{
    this->X += width;
    if (this->X > (this->wPaint->GetWidth() + width))
    {
        this->X = 0;
        this->Y = maxy;
        this->epd->SetFrameMemory(this->wPaint->GetImage(),0,this->Y,this->wPaint->GetWidth(),this->maxy);
        this->wPaint->Clear(!colored);
    }
    if (this->Y + height > this->wPaint->GetHeight())
    {
        return false;
    }
    if (this->maxy < (this->Y + height))
    {
        this->maxy = (this->Y + height);
    }
    this->DrawBitmap(bitmap, this->X, 0, width, height, colored);
    return true;
}

void PaintExt::NewPage(uint16_t x, uint16_t y)
{
    this->X = x;
    this->Y = y;
    this->maxy = y;
}

void PaintExt::NewPage(uint16_t width, uint16_t height)
{
    this->X = 0;
    this->Y = 0;
    this->maxy = 0;
}