**I got this idea from By Frank Bösing's code.**

There are 2 versions. 
the first on stores the images in microcontroller memory. The other stores the images on an SD card.
If using the non SD card version, you probably wont be able to store more than 1 image in memory at a time.
I used the adafruit SD card reader over SPI
Store the images on the SD card in the "pics" folder.

I used the Teensy 4.0. Note that I have not initialised serial comms so you might need to do that if using an arduino or other micro.
I overclocked the 4.0 to 720mHz and get pretty impressiver results. Im guessing it writes a 300kB file to the TFT screen in around 200ms.

I have pushed the SPI clock speed to the limit. You will need to reduce that if using a slower microcontroller. 

