#define WP 13
#define SCL 12
#define SDA 11

byte CTRL_Write[5] = {B00000000, B10101000, B10101010, B10101100, B10101110};
byte CTRL_Read[5] = {B00000000, B10101001, B10101011, B10101101, B10101111};
byte mask = B10000000;
unsigned int CTRL_i = 0;
bool ACK = true;

void setup() 
{
  pinMode(WP, OUTPUT);
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
  Serial.begin(9600);

  BusNotBusy();
  delay(1000);
  StartDataTransfer();
  SendData(100);
  StopDataTransfer();
  BusNotBusy();
  delay(1000);
}

void BusNotBusy()
{
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
}

void StartDataTransfer()
{
  digitalWrite(SDA, LOW);
  delay(100);
}

void StopDataTransfer()
{
  digitalWrite(SDA, HIGH);
  delay(100);
}

void SendData(byte data)
{
  for(int i = 0; i< 8; i++)
  {
    digitalWrite(SCL, LOW);
    delay(100);

    digitalWrite(SCL, HIGH);
    delay(100);
  }
}

void loop()
{

}

