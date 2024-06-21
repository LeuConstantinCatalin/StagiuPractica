#include <Wire.h>

#define ADDR_Ax 0b000
#define ADDR (0b1010 << 3) + ADDR_Ax

const int latchPin = 8;
const int clockPin = 11;
const int dataPin = 9;


void setup() {

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  Wire.begin();

  char data[256] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in.";
  byte nums[256] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255};
  

  //WritePage(nums);
  //WritePage(nums);
  //ReadPage();
}

void loop() {
  byte dataForReg;
  for(int i = 0; i < 256; i++)
  {
    dataForReg = readI2CByte(i);
    WriteRegister(dataForReg);
    Serial.println(dataForReg, HEX);
    delay(50);
  }
}

void WriteRegister(byte data)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, data);
  digitalWrite(latchPin, HIGH);
}

void WritePage(char* data)
{
  for(int i = 0; i < 256; i++)
  {
    writeI2CByte(i, data[i]);
    delay(10);
  }
}

void ReadPage()
{
  Serial.println();
  Serial.print("====================================");
  Serial.println();
  for(int i = 0; i < 256; i++)
  {
    //delay(10);
    if(i % 8 == 0)
    {
      Serial.println();
      Serial.print("0x");
      Serial.print(i, HEX);
      Serial.print(": ");
    }
    Serial.print(readI2CByte(i), HEX);
    Serial.print(" ");
  }
}

void writeI2CByte(byte data_addr, byte data){
  Wire.beginTransmission(ADDR);
  Wire.write(data_addr);
  Wire.write(data);
  Wire.endTransmission();
}

byte readI2CByte(byte data_addr){
  byte data = NULL;
  Wire.beginTransmission(ADDR);
  Wire.write(data_addr);
  Wire.endTransmission();
  Wire.requestFrom(ADDR, 1);
  delay(1);
  if(Wire.available()){
    data = Wire.read();
  }
  return data;
}

byte readI2CCurrentByte()
{
  byte data = NULL;
  Wire.requestFrom(ADDR, 1);
  delay(1);
  if(Wire.available())
  {
    data = Wire.read();
  }
  return data;
}