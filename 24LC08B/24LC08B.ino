#define WP 13
#define SCL 12
#define SDA 11

const unsigned int DELAY = 500;

const byte CTRL_Write[5] = {B00000000, B10101000, B10101010, B10101100, B10101110};
const byte CTRL_Read[5] = {B00000000, B10101001, B10101011, B10101101, B10101111};
const byte mask = B10000000;
const byte rw_mask = B00000001;
const bool ACK = true;

void setup() 
{
  pinMode(WP, OUTPUT);
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
  Serial.begin(9600);

  BusNotBusy();
  delay(4 * DELAY);
  StartDataTransfer();
  SendCTRL(CTRL_Write[1]);
  StopDataTransfer();
  BusNotBusy();
}

void BusNotBusy()
{
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
}

void StartDataTransfer()
{
  delay(10);
  digitalWrite(SDA, LOW);
  delay(100);
}

void StopDataTransfer()
{
  delay(10);
  digitalWrite(SDA, HIGH);
  delay(100);
}

void SendData(byte data)
{
  bool bit;
  
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(SCL, LOW);
    delay(DELAY / 2);

    if((data & (mask >> i)) == 0)
      bit = false;
    else
      bit = true;

    digitalWrite(SDA, bit);
  
    delay(DELAY / 2);

    digitalWrite(SCL, HIGH);
    delay(DELAY);
  }
}

void SendCTRL(byte data)
{
  SendData(data);

  digitalWrite(SDA, LOW);
  pinMode(SDA, INPUT);

  digitalWrite(SCL, LOW);
  delay(DELAY);
  digitalWrite(SCL, HIGH);
  delay(DELAY);

  pinMode(SDA, OUTPUT);
}

byte ReadBus()
{
  bool bit;
  
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(SCL, LOW);
    delay(DELAY);

    digitalWrite(SCL, HIGH);
    delay(DELAY / 2);

    
  }
}

void loop()
{

}

