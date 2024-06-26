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

25.06:
Am adaugat switch-uri pentru a selecta o adresa si un mod de selectie.
Modul de selectie va specifica programatorului ce sa faca (sa scrie, sa citeasca tot/de la o anumita adresa...)
Exista niste probleme care trebuie remediate.
Am experimentat cu un display LCD. Nu poate fi folosit deoarece cablurile lui nu fac bine contact.
De asemenea are nevoie de 8 cabluri de control iar placa de dezvoltare nu mai are pini liberi.

26.06:
Am remediat problemele din ziua respectiva.
Programatorul este complet.
Selectul poate actiona urmatoarele operatiuni:
0: nimic
1: scrie intreg EEPROM-ul
2: sterge intreg EEPROM-ul (scriere cu 1)
3: citire a intreg EEPROM-ului intr-un buffer si afisarea la Serial Monitor (SM)
4: citire a intreg EEPROM-ului si afisarea pe LED-uri
5: citire a unui byte la apasare de buton si afisare pe SM si LED-uri
6: citire a unui byte de la adresa switch-urilor
7: afisarea in SM a starii inputurilor (adresa, select-ul, counter-ul);


