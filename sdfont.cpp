#include "sdfont.h"
#include <arduino.h>
#include <SPI.h>
#include <SD.h>
#include <stdint.h>

SDFont::SDFont(const char *filename)
{
    this->fontFile = SD.open(filename);
    if (!fontFile)
    {
        Serial.println("Failed to open font file");
        return;
    }
    Byte8Block *header = this->readBlock();
    this->Info.Width = header->Bytes[0];
    this->Info.Height = header->Bytes[1];
    this->Info.Size = Info.Width * Info.Height / 8;
    Byte8Block *firstchar = this->readBlock();
    this->Info.Count = firstchar->UInt32[1] / this->Info.Size;
}

SDFont::~SDFont(void)
{
    this->fontFile.close();
}

CharInfo SDFont::SeekCharUnicode(uint32_t unicode)
{
    fontFile.seek(8);
    uint32_t bodyoffset = this->Info.Count * this->Info.Size;
    Byte8Block *block = this->readBlock();
    while (block->UInt32[0] != unicode)
    {
        if (fontFile.position() >= bodyoffset)
        {
            Serial.println("Failed to find char");
            return CharInfo{
                .Size = 0,
                .Width = 0,
                .Height = 0,
                .Address = 0};
        }
        block = this->readBlock();
    }

    return CharInfo{
        .Size = this->Info.Size,
        .Width = this->Info.Width,
        .Height = this->Info.Height,
        .Address = block->UInt32[1]};
}

uint8_t *SDFont::ReadFont(CharInfo c){
    uint8_t *font = (uint8_t *)malloc(c.Size);
    fontFile.seek(c.Address);
    fontFile.read(font, c.Size);
    return font;
}