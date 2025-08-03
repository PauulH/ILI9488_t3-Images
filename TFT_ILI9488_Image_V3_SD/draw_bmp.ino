bool loadPictureFromC(const char* filename, uint16_t* buffer, int16_t w, int16_t h) {
  static bool chip_missing = false;
  static int16_t x_previous = 0, y_previous = 0;
  static int16_t w_previous = 480, h_previous = 320;
  const size_t READ_CHUNK_SIZE = 100000;
  char readBuffer[READ_CHUNK_SIZE];
  bool insideBraces = false, inLineComment = false, inBlockComment = false;
  size_t index = 0;
  uint8_t value = 0;
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

      // if (isHexadecimalDigit(c)) {
      //   value = (value << 4) + (isdigit(c) ? c - '0' : toupper(c) - 'A' + 10);
      //   collectingHex = true;
      // } else if (collectingHex && (c == ',' || c == '\n' || c == ' ' || c == '\r')) {
      //   buffer[index++] = value;
      //   value = 0;
      //   collectingHex = false;
      // }

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
  Serial.println(elapsed);

  int16_t x = (w < 480) ? (480 - w) / 2 : 0;
  int16_t y = (h < 320) ? (320 - h) / 2 : 0;

  tft.fillRect(x_previous, y_previous, w_previous, h_previous, ILI9488_BLACK);
  tft.writeRect(x, y, w, h, buffer);

  x_previous = x;
  y_previous = y;
  w_previous = w;
  h_previous = h;
  chip_missing = false;

  bmpFile.close();
  return true;
}
















































/*bool loadPictureFromC(const char* filename, uint16_t* buffer, int16_t w, int16_t h) {


  bool insideBraces = false;
  bool inLineComment = false;
  bool inBlockComment = false;
  static bool chip_missing = 0;
  String hexValue = "";
  size_t index = 0;
  int16_t x = 0;
  int16_t y = 0;
  static int16_t x_previous = 0;
  static int16_t y_previous = 0;
  static int16_t w_previous = 480;
  static int16_t h_previous = 320;
  unsigned long start;


  if (chip_missing == true)
    SD.begin(chipSelect);

  File bmpFile = SD.open(filename);
  if (!bmpFile) {
    chip_missing = true;
    return false;
  }

  // if (bmpFile.available())
  //   file_exists = true;
  // else
  //   file_exists = false;

start = millis();

    while (bmpFile.available() && index < MAX_BUFFER_SIZE) {  // 💡 Guard against overflow

    char c = bmpFile.read();

    if (c == '{') {
      insideBraces = true;
      continue;
    }
    if (c == '}') break;
    if (!insideBraces) continue;

    if (c == '/' && bmpFile.peek() == '/') {
      inLineComment = true;
      bmpFile.read();
      continue;
    }

    if (c == '/' && bmpFile.peek() == '*') {
      inBlockComment = true;
      bmpFile.read();
      continue;
    }

    if (inBlockComment && c == '*' && bmpFile.peek() == '/') {
      inBlockComment = false;
      bmpFile.read();
      continue;
    }

    if (inLineComment && c == '\n') {
      inLineComment = false;
      continue;
    }

    if (inLineComment || inBlockComment) continue;

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
    
  }

  unsigned long elapsed = millis() - start;
    Serial.println(elapsed);

  if (w < 480)
    x = (480 - w) / 2;

  if (h < 320)
    y = (320 - h) / 2;

  tft.fillRect(x_previous, y_previous, w_previous, h_previous, ILI9488_BLACK);
  tft.writeRect(x, y, w, h, (uint16_t*)buffer);

  x_previous = x;
  y_previous = y;
  w_previous = w;
  h_previous = h;
  chip_missing = false;

  bmpFile.close();

  //return file_exists;
  return true;
}
*/