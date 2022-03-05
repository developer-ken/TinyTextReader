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

class SDFont
{
public:
    FontInfo Info;
    SDFont(const char *filename);
    ~SDFont(void);
    CharInfo SeekCharUnicode(uint32_t unicode);
    uint8_t *ReadFont(CharInfo *c);
private:
    uint8_t *readBlock();
    File fontFile;
};
#endif