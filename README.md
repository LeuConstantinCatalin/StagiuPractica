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

21.06:
Am realizat schema electrică in Proteus.
Am legat și registrul de shiftare la circuit. La output-ul acestuia sunt conectate 8 LED-uri pentru a vizualiza byte-ul care este citit din EEPROM.
Registrul are capacitatea de 1 byte. Intrarea lui este seriala iar ieșirea paralelă.
Codul arduino: Când se citește un byte din EEPROM, acesta va fi stocat în registru.
Utilitate: De obicei, când un dispozitiv dorește să citească un byte din EEPROM, acesta le așteaptă pe o magistrală de 8 cabluri (câte un cablu pe bit).
Dar EEPROM-ul fiind serial, acesta pune cei 8 biți pe un singur cablu, unul după altul.
Registrul de shiftare transformă byte-ul serial care vine pe un singur cablu, în unul paralel pe 8 cabluri.

