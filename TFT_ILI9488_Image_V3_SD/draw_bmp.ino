bool loadPictureFromC(const char* filename, uint16_t* buffer, int16_t w, int16_t h) {
  static bool chip_missing = false;
  static int16_t x_previous = 0, y_previous = 0;
  static int16_t w_previous = 480, h_previous = 320;
  const size_t READ_CHUNK_SIZE = 100000;
  char readBuffer[READ_CHUNK_SIZE];
  bool insideBraces = false, inLineComment = false, inBlockComment = false;
  size_t index = 0;
  char prev = '\0';
  String hexValue = "";


  if (chip_missing)
    SD.begin(chipSelect);

  File bmpFile = SD.open(filename);
  if (!bmpFile) {
    chip_missing = true;
    return false;
  }

  unsigned long start = millis();

  while (bmpFile.available() && index < MAX_BUFFER_SIZE) {
    size_t bytesRead = bmpFile.read(readBuffer, READ_CHUNK_SIZE);
    for (size_t i = 0; i < bytesRead && index < MAX_BUFFER_SIZE; ++i) {
      char c = readBuffer[i];

      // Brace detection
      if (c == '{') {
        insideBraces = true;
        continue;
      }
      if (c == '}') break;
      if (!insideBraces) continue;

      // Comment detection
      if (!inBlockComment && !inLineComment && prev == '/' && c == '/') {
        inLineComment = true;
        continue;
      }
      if (!inBlockComment && !inLineComment && prev == '/' && c == '*') {
        inBlockComment = true;
        continue;
      }
      if (inBlockComment && prev == '*' && c == '/') {
        inBlockComment = false;
        continue;
      }
      if (inLineComment && c == '\n') {
        inLineComment = false;
        continue;
      }
      if (inLineComment || inBlockComment) {
        prev = c;
        continue;
      }

      if (isHexadecimalDigit(c)) {
        hexValue += c;
      } else if (c == 'x' && hexValue == "0") {
        hexValue = "";
      } else if (c == ',' || c == '\n' || c == ' ' || c == '\r') {
        if (hexValue.length() > 0) {
          buffer[index++] = strtol(hexValue.c_str(), NULL, 16);
          hexValue = "";
        }
      }

      prev = c;
    }
  }

  unsigned long elapsed = millis() - start;
  Serial.print("Time to read SD card in milliseconds = ");
  Serial.println(elapsed);

  int16_t x = (w < 480) ? (480 - w) / 2 : 0; //this is a cool way to write this I think.. thougths??
  int16_t y = (h < 320) ? (320 - h) / 2 : 0;

  tft.fillRect(x_previous, y_previous, w_previous, h_previous, ILI9488_BLACK); //only fill the area the last picture took up

  start = millis();
  tft.writeRect(x, y, w, h, buffer);

  elapsed = millis() - start;
  Serial.print("Time to write to TFT in milliseconds = ");
  Serial.println(elapsed);

  x_previous = x;
  y_previous = y;
  w_previous = w;
  h_previous = h;
  chip_missing = false;

  bmpFile.close();
  return true;
}




