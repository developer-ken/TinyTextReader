#include <SPI.h>
#include "sdfont.h"
#include "epd2in13.h"
#include "epdpaint.h"
#include "epdpaintext.h"

#define SD_CS_PIN A6

unsigned char image[EPD_WIDTH * EPD_HEIGHT / 16];
Paint paint(image, EPD_WIDTH, EPD_HEIGHT);
Epd epd;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS_PIN))
  {
    Serial.println("initialization failed!");
    while (1)
      ;
  }
  Serial.println("initialization done.");
}

void loop()
{
  // put your main code here, to run repeatedly:
}
