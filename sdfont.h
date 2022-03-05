#ifndef __SDFONTS_H
#define __SDFONTS_H

#include <SD.h>

typedef struct
{
    uint16_t Size;
    uint16_t Width;
    uint16_t Height;
    uint16_t Count;
} FontInfo;

typedef struct
{
    uint16_t Size;
    uint16_t Width;
    uint16_t Height;
    uint32_t Address;
} CharInfo;

union Byte8Block{
    uint32_t UInt32[2];
    uint8_t Bytes[8];
};

class SDFont
{
public:
    FontInfo Info;
    SDFont(const char *filename);
    ~SDFont(void);
    CharInfo SeekCharUnicode(uint32_t unicode);
    uint8_t *ReadFont(CharInfo c);
private:
    Byte8Block *readBlock();
    File fontFile;
};
#endif