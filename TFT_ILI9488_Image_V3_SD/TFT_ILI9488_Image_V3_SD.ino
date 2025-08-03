// Simple example to embed pictures in your sketch
// and draw on the ILI9341 display with writeRect()
//
// By Frank Bösing
//
// https://forum.pjrc.com/threads/32601-SPI-Library-Issue-w-ILI9341-TFT-amp-PN532-NFC-Module-on-Teensy-3-2?p=94534&viewfull=1#post94534
#include <Wire.h>
#include <SD.h>
#include <SdFat.h>
#include <Adafruit_INA219.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <utility>
#include <Adafruit_GFX.h>
#include "ILI9488_t3.h"
#include <XPT2046_Touchscreen.h>
#include <ILI9488_t3_font_Arial.h>
#include <ILI9488_t3_font_ArialBold.h>

// Converted to code with:
// http://www.rinkydinkelectronics.com/t_imageconverter565.php
//
//#include "picture.c"  //the picture
//#include "boobs.c"    //the picture
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
#define TFT_RST 16  // 255 = unused, connect to 3.3V
#define TFT_MOSI 11
#define TFT_SCLK 13
#define TFT_MISO 12
#define USE_DMA

//320 * 480 is the maximum buffer size we will need
#define MAX_BUFFER_SIZE 320 * 480  // Adjust as needed for your use case
uint16_t buffer[MAX_BUFFER_SIZE];
//😘(●'◡'●)❤️



ILI9488_t3 tft = ILI9488_t3(&SPI, TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);

int pic_delay(20000);  // microseconds between pics

const int chipSelect = 21;  //SD card chip select pin


void setup() {


  Wire.begin();
  SPI.begin();

  tft.begin(70000000);  //slow this down if not using a Teensy
  tft.setRotation(3);   //rotate the screen for landscape mode


  if (!SD.begin(chipSelect)) {
    Serial.println("SD card failed to initialize.");
    tft.println("SD init failed!");
    while (1)
      ;
  }

  delay(1000);


  tft.fillScreen(ILI9488_BLACK); //fill the screen black
  delay(200);
}

void loop() {

  if (loadPictureFromC("/pics/picture.c", buffer, 256, 174))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/forrest.c", buffer, 447, 320))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/cat.c", buffer, 480, 320))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/mower.c", buffer, 480, 320))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/forrest.c", buffer, 447, 320))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/flowers.c", buffer, 480, 268))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/plant.c", buffer, 480, 320))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/f35.c", buffer, 480, 295))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/gps.c", buffer, 340, 320))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/leaves.c", buffer, 480, 270))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/city.c", buffer, 480, 270))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/wave.c", buffer, 480, 270))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/pebbles.c", buffer, 480, 270))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/waterfall.c", buffer, 480, 319))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/peacock.c", buffer, 480, 319))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/beach.c", buffer, 480, 299))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/woman.c", buffer, 480, 300))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);

  if (loadPictureFromC("/pics/droplet.c", buffer, 480, 300))
    Serial.println("Image loaded successfully.");
  else
    Serial.println("Failed to load image.");
  delay(pic_delay);




  // while (true);  // Halt after drawing
}
