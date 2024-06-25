#include <Wire.h>

#define ADDR_Ax 0b000
#define ADDR (0b1010 << 3) + ADDR_Ax

const int latchPin = 9;
const int clockPin = 8;
const int dataPin = 10;

const int buttonPin = 6;
const int ledPin = 13;

const int sw_addr_pin[] = {7, 13, 12, 11, 2, 3, 4, 5};
const int sw_sel_pin[] = {A5, A4, A3};

int sw_addr = 0;
int sw_addr_old;
int sw_sel = 0;
int sw_sel_old;

int ledState = LOW;        
int buttonState;            
int lastButtonState = LOW;  
byte counter = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

char data[256] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in.";
byte nums[256] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255};

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for(int i = 0; i < 8; i++)
    pinMode(sw_addr_pin[i], INPUT_PULLUP);
  for(int i = 0; i < 3; i++)
    pinMode(sw_sel_pin[i], INPUT_PULLUP);

  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  sw_sel = 0;
  sw_addr = 0;

  if(DebounceButton())
  {
    ledState = LOW;

    for(int i = 0; i < 8; i++)
    {
      sw_addr += (!digitalRead(sw_addr_pin[i])) * ( 1 << i);
    }
    if(sw_addr != sw_addr_old)
    {
      sw_addr_old = sw_addr;
      //Serial.print("SW_ADDR: ");
      //Serial.print(sw_addr);
      //Serial.println();
    }

    for(int i = 0; i < 3; i++)
    {
      sw_sel += (!digitalRead(sw_sel_pin[i])) * ( 1 << i);
    }
    if(sw_sel != sw_sel_old)
    {
      sw_sel_old = sw_sel;
      //Serial.print("SW_SEL: ");
      //Serial.print(sw_sel);
      //Serial.println();
    }

    Serial.print("====================================");
    Serial.println();
    Serial.print("Counter: ");
    Serial.print(counter);
    Serial.println();

    Serial.print("SW_ADDR: ");
    Serial.print(sw_addr);
    Serial.println();

    Serial.print("SW_SEL: ");
    Serial.print(sw_sel);
    Serial.println();
    Serial.print("====================================");
    Serial.println();

    //ReadPage();

    byte rom_data = readI2CByte(counter);
    WriteRegister(rom_data);
    Serial.print("DATA: 0X");
    Serial.print(rom_data, HEX);
    Serial.println();

    byte rom_data = readI2CByte(sw_addr);
    WriteRegister(rom_data);
    Serial.print("DATA: 0X");
    Serial.print(rom_data, HEX);
    Serial.println();

    byte dataForReg;
    for(int i = 0; i < 256; i++)
    {
      dataForReg = readI2CByte(i);
      WriteRegister(dataForReg);
      Serial.println(dataForReg);
      delay(10);
    }

/*
      if(sw_sel == 0);

      if(sw_sel == 1)
        WritePage(nums);

      if(sw_sel == 2)
        ReadPage();

      if(sw_sel == 3)
        {
        byte rom_data = readI2CByte(sw_addr);
        WriteRegister(rom_data);
        Serial.print("DATA: 0X");
        Serial.print(rom_data, HEX);
        Serial.println();
        }
      if(sw_sel == 4)
        {
        byte dataForReg;
        Serial.println();
        Serial.print("====================================");
        Serial.println();
        for(int i = 0; i < 256; i++)
        {
          if(i % 8 == 0)
          {
            Serial.println();
            Serial.print("0x");
            Serial.print(i, HEX);
            Serial.print(": ");
          }
          dataForReg = readI2CByte(i);
          WriteRegister(dataForReg);
          Serial.print(dataForReg, HEX);
          Serial.print(" ");
          delay(10);
        }
        Serial.println();
        }
      if(sw_sel == 5)
        {
        byte rom_data = readI2CByte(counter);
        WriteRegister(rom_data);
        Serial.print("DATA: 0X");
        Serial.print(rom_data, HEX);
        Serial.println();
        }
        */
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
  byte rp_data;
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
    rp_data = readI2CByte(i);
    Serial.print(rp_data, HEX);
    Serial.print(" ");
    WriteRegister(rp_data);
  }
  Serial.println();
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

bool DebounceButton()
{
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        ledState = !ledState;
        counter++;
      }
    }
  }
  digitalWrite(ledPin, ledState);

  lastButtonState = reading;
  return ledState;
}