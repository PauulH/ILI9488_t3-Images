// Simple example to embed pictures in your sketch
// and draw on the ILI9341 display with writeRect()
//
// By Frank Bösing
//


//#include <Wire.h>
#include <SD.h>
//#include <utility>
#include <Adafruit_GFX.h>
#include "ILI9488_t3.h"
#include <XPT2046_Touchscreen.h>
#include <ILI9488_t3_font_Arial.h>
#include <ILI9488_t3_font_ArialBold.h>

// Converted to code with:
// http://www.rinkydinkelectronics.com/t_imageconverter565.php  //this is what I use. choose "convert to C"
//
//#include "picture.c"  //the picture
#include "cat.c"  //the picture
//#include "forrest.c"  //the picture

/* GIMP (https://www.gimp.org/) can also be used to export the image using the following steps:

    1. File -> Export As
    2. In the Export Image dialog, use 'C source code (*.c)' as filetype.
    3. Press export to get the export options dialog.
    4. Type the desired variable name into the 'prefixed name' box.
    5. Uncheck 'GLIB types (guint8*)'
    6. Check 'Save as RGB565 (16-bit)'
    7. Press export to save your image.

  Assuming 'image_name' was typed in the 'prefixed name' box of step 4, you can have to include the c file as above,
  using the image can be done with:

    tft.writeRect(0, 0, image_name.width, image_name.height, (uint16_t*)(image_name.pixel_data));

  See also https://forum.pjrc.com/threads/35575-Export-for-ILI9488_t3-with-GIMP 
*/


// Normal Connections
#define TFT_DC 15
#define TFT_CS 17
#define TFT_RST 16
#define TFT_MOSI 11
#define TFT_SCLK 13
#define TFT_MISO 12

char str[200];
ILI9488_t3 tft = ILI9488_t3(&SPI, TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);


const int chipSelect = 21;  //SD card chip select pin

void setup() {

  //😘(●'◡'●)❤️

  SPI.begin();

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9488_BLACK);

  tft.setCursor(10, 35);
  tft.setFont(Arial_18);
  tft.setTextColor(ILI9488_YELLOW, 0);
  sprintf(str, "16 bit image display test");
  tft.println(str);
  
  delay(3000);
  tft.fillScreen(ILI9488_BLACK);
}

void loop() {

  // tft.writeRect(32, 33, 256, 174, (uint16_t*)picture);
  // delay(5000);

  // tft.fillRect(32, 33, 256, 174, ILI9488_BLACK);
  // //tft.writeRect(0, 0, 447, 320, (uint16_t*)forrest);
  // delay(5000);


  tft.fillRect(0, 0, 447, 320, ILI9488_BLACK);
  tft.writeRect(0, 0, 480, 320, (uint16_t*)cat);
  delay(5000);

  //tft.fillRect(0, 0, 480, 320, ILI9488_BLACK);
}
