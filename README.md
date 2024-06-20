# StagiuPractica
Programator EEPROM folosind ArduinoUNO


17.06:
-alegerea proiectului
Am citit documentația EEPROM-ului 24LC08B.
Am citit documentația registrului de shiftare 74HC595N.
Am realizat un circuit care introduce date in registrul de shiftare.

18.06:
Am citit documentația EEPROM-ului 24C02N.
Am realizat circuitul pentru a exploata IC-ul.
Am scris protocolul I2C pentru Arduino. (Varianta aceasta inca nu funcționează).

19.06:
Am sudat pinii plăcii Arduino nano pentru a putea fi inserată în breadboard.
Pe același breadboard am pus IC-ul EEPROM, registrul de shiftare și Arduino nano.
Am folosit cabluri tăiate la lunginea corespunzătoare.

20.06:
Folosind librăria Wire.h am scris următoarele funcții:

void writeI2CByte(byte data_addr, byte data)
Scrie un byte la adresa specificată.

byte readI2CByte(byte data_addr)
Citește un byte de la adresa specificată.

byte readI2CCurrentByte()
Citește byte-ul la care pintează registrul de adresă al EEPROM-ului.

void ReadPage()
Utilizează funcția writeI2CByte(byte data_addr, byte data) pentru a citi întregul conținut al memoriei.

void WritePage(char* data)
Utilizează funcția writeI2CByte(byte data_addr, byte data) pentru a scrie în memorie cu ce se află in bufferul data.