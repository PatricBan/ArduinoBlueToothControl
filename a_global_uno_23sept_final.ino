#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

//_____________________________________________________________________RTC:

#include "ds3231.h"


//______________________________________________________________________RTC^



//void myDelay(int x);
//void afisare32();
//void afisare22();
//void aprindere_lampi();
//void timeleft(int h, int m, unsigned long t);
void blink_led();
void checksensors(int x, int y);
//void checksensor1(int minVal, int maxVal);
//void checksensor2(int minVal, int maxVal);
//void checksensor3(int minVal, int maxVal);

boolean stop_bluetooth;           
unsigned long previousMillis;

/*
   pentru senzorii de curent
*/
int minCurrentVal;
int maxCurrentVal;    //valorile intre care trebuie sa fie curentul

int maxReadings1;
int minReadings1;
int offsets1;

int maxReadings2;
int minReadings2;
int offsets2;

int maxReadings3;
int minReadings3;
int offsets3;

String mesajTimp;
String H = "h";
String M = "min";

/*
   variabile pentru senzorii de curent
*/
boolean lampa1 = true;
boolean lampa2 = true;
boolean lampa3 = true;
boolean blinkLed;
boolean led_on;
boolean led_off = true;
int sensorc1;
int sensorc2;
int sensorc3;

boolean vents = true;


char character_global;
/*

*/

class MeniuPrincipal {
  private:
    String mesaj_start = "Select a Program";

    int splitT;
  public:
    void afisare() {
      lcd.clear();
      lcd.setCursor(1, 2);
      lcd.print(mesaj_start);
      lcd.setCursor(0, 2);
      lcd.print(">");
    }
    //  void afisareOra(){
    //    timeClient.update();
    //    lcd.setCursor(12, 0);
    //    splitT = timeClient.getFormattedDate().indexOf("T");
    //    lcd.print(timeClient.getFormattedDate().substring(splitT+1,timeClient.getFormattedDate().length()-1));
    //
    //    lcd.setCursor(0, 0);
    //    lcd.print(timeClient.getFormattedDate().substring(0,splitT));
    //  }



    void setMesaj(String x) {
      this -> mesaj_start = x;
    }
    String getMesaj() {
      return this-> mesaj_start;
    }

};



MeniuPrincipal meniu = MeniuPrincipal();

class MeniuPrincipal2 {

  public:
    MeniuPrincipal2() {
    }

    void afisare() {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(">");
      lcd.setCursor(2, 0);
      lcd.print("Back");
      lcd.setCursor(1, 1);
      lcd.print("P1: Continous");
      lcd.setCursor(1, 2);
      lcd.print("P2: Custom Timer");
      lcd.setCursor(1, 3);
      lcd.print("P3: Cyclic");
    }

};  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   1   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

class MeniuProgram1 {
  public:
    void afisare() {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Program 1 selected.");

      lcd.setCursor(0, 2);
      lcd.print("Press START to begin");
    }


};  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   2   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



class MeniuProgram2 {
  private:
    long hour;
    int mins;
    // MeniuPrincipal meniup2 = MeniuPrincipal();

    unsigned long time_start;
    boolean timer = true;
  public:
    void selectare_timer() {
      lcd.clear();

      lcd.setCursor(1, 0);
      lcd.print("Hours:");
      lcd.setCursor(11, 0);
      lcd.print("Mins:");

      lcd.setCursor(8, 0);
      lcd.print(this -> getHour());
      lcd.setCursor(17, 0);
      lcd.print(this -> getMins());

      lcd.setCursor(8, 1);
      lcd.print("^");

      lcd.setCursor(1, 3);
      lcd.print("Back");
      lcd.setCursor(11, 3);
      lcd.print("Continue");
    }
    void setHour(long x) {
      this -> hour = x;
    }
    void setMins(int x) {
      this -> mins = x;
    }
    int getHour() {
      return this -> hour;
    }
    int getMins() {
      return this -> mins;
    }

    void start(long h, int m) {

      previousMillis = 0;
      int ST_state = digitalRead(7);
      if (h != 0 || m != 0) {
        digitalWrite(9, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(6, HIGH);
        myDelay(2000);
        digitalWrite(10, HIGH);
        myDelay(2000);
        digitalWrite(11, HIGH);
        myDelay(2000);


        this->time_start = millis() / 1000;
        timeleft(h, m, millis() / 1000 - time_start);


        while (millis() / 1000 - time_start <= (h * 3600 + m * 60) && ST_state == LOW) {
          ST_state  = digitalRead(7);
          //     // meniu.afisareOra();
          checksensors(minCurrentVal, maxCurrentVal); //--------------------------------------------------------> sensors
          blink_led();
          mesajTimp = String(getHourLeft(h, m, millis() / 1000 - time_start)) + "h " + String(getMinLeft(h, m, millis() / 1000 - time_start)) + "min";
          afisareOra();
          myDelay(1000);
          unsigned long currentMillis = millis();
          if (currentMillis - previousMillis >= 60000) {  //aka 60 secunde
            previousMillis = currentMillis;
            timeleft(h, m, millis() / 1000 - time_start);
          }
          /*
             afisare Serial pentru bluetooth. Program selectat, timp ramas, status lampi.
          */

          Serial.print(meniu.getMesaj());
          Serial.print(",");
          Serial.print(mesajTimp );
          Serial.print(",");
          Serial.println(verificare_lampi());

          if (Serial.available() >= 0) {         //citeste informatia de la telefon
            character_global = Serial.read();         //citeste caracter cu caracter textul primit
            if (character_global == 'q') {        //daca am apasat butonul de stop din aplicatie
              character_global = 0;
              ST_state = HIGH;               // = HIGH ca sa iasa din while
            }
          }
        }

      } else if (h == 0 && m == 0) {
        lcd.setCursor(0, 1);
        lcd.print("Time = 0. Exiting");
        myDelay(4000);
      }
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      digitalWrite(6, LOW);

      meniu.setMesaj("Select a Program");
      meniu.afisare();
    }

};   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   3   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
MeniuProgram2 program2 = MeniuProgram2();



class MeniuProgram3 {
  private:
    long hourOn = 0;
    int minOn = 0;
    long hourOff = 0;
    int minOff = 0;
    unsigned long time_start;
    boolean ofon;
    //  MeniuPrincipal meniup3 = MeniuPrincipal();

    boolean on;
  public:
    void setHourOn(long x) {
      this -> hourOn = x;
    }
    int getHourOn() {
      return this -> hourOn;
    }

    void setMinutesOn(long x) {
      this -> minOn = x;
    }
    int getMinutesOn() {
      return this -> minOn;
    }

    void setHourOff(int x) {
      this -> hourOff = x;
    }
    int getHourOff() {
      return this -> hourOff;
    }

    void setMinutesOff(int x) {
      this -> minOff = x;
    }
    int getMinutesOff() {
      return this -> minOff;
    }
    void afisare() {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ton:");
      lcd.setCursor(7, 0);
      lcd.print("h:");
      lcd.setCursor(13, 0);
      lcd.print("min:");

      lcd.setCursor(6, 0);
      lcd.print(">");

      lcd.setCursor(0, 1);
      lcd.print("Toff:");
      lcd.setCursor(7, 1);
      lcd.print("h:");
      lcd.setCursor(13, 1);
      lcd.print("min:");

      lcd.setCursor(1, 3);
      lcd.print("Back");
      lcd.setCursor(7, 3);
      lcd.print("Start ON/OFF");
      lcd.setCursor(7, 2);
      lcd.print("Start OFF/ON");

      lcd.setCursor(9, 0);
      lcd.print(this -> getHourOn());
      lcd.setCursor(9, 1);
      lcd.print(this -> getHourOff());
      lcd.setCursor(17, 0);
      lcd.print(this -> getMinutesOn());
      lcd.setCursor(17, 1);
      lcd.print(this -> getMinutesOff());
    }

    void startOnOff(long hon, int mon, long hoff, int minoff) {    // ------------------------------------  functia de ON/OFF
      int ST_state = digitalRead(7);
      previousMillis = 0;
      on = true;
//Serial.println("Outside while ST_state == low ");
//Serial.print("STOP_BLUETOOTH =  ");
//Serial.println(stop_bluetooth);
//Serial.println();

      while (ST_state == LOW && stop_bluetooth == false) {
        
//Serial.println("INSIDE while ST_state == low ");
//Serial.print("STOP_BLUETOOTH =  ");
//Serial.println(stop_bluetooth);
//Serial.println();

        if (on = true) {    //pornim lampile

          if (hon != 0 || mon != 0) {    //aprindem lampile daca macar una dintre cele doua valori este diferita de zero
            digitalWrite(9, HIGH);
            digitalWrite(12, HIGH);
            digitalWrite(6, HIGH);
            myDelay(2000);
            digitalWrite(10, HIGH);
            myDelay(2000);
            digitalWrite(11, HIGH);
            myDelay(2000);
            lcd.setCursor(4, 3);
            lcd.print(" ");
            lcd.setCursor(2, 3);
            lcd.print("ON");
//Serial.println("Am PORNIT lampile toate toate ");
//Serial.print("STOP_BLUETOOTH =  ");
//Serial.println(stop_bluetooth);
//Serial.println();
            this->time_start = millis() / 1000;
            timeleft(hon, mon, millis() / 1000 - time_start);

            while (millis() / 1000 - time_start <= (hon * 3600 + mon * 60) && ST_state == LOW && stop_bluetooth == false) {
//Serial.println("Inside First (ON) While ");
//Serial.print("STOP_BLUETOOTH =  ");
//Serial.println(stop_bluetooth);
//Serial.println();
              ST_state  = digitalRead(7);
              checksensors(minCurrentVal, maxCurrentVal); //--------------------------------------------------------> sensors

              blink_led();
              afisareOra();
              myDelay(1000);

              unsigned long currentMillis = millis();
              if (currentMillis - previousMillis >= 60000) {  //aka 60 secunde
                previousMillis = currentMillis;
                timeleft(hon, mon, millis() / 1000 - time_start);
              }
              mesajTimp = String(getHourLeft(hon, mon, millis() / 1000 - time_start)) + "h " + String(getMinLeft(hon, mon, millis() / 1000 - time_start)) + "min";
              Serial.print(meniu.getMesaj() + " ON");
              Serial.print(",");
              Serial.print(mesajTimp );
              Serial.print(",");
              Serial.println(verificare_lampi());

              if (Serial.available() >= 0) {         //citeste informatia de la telefon
                
//Serial.println("SERIAL AVAILABLE ");
//Serial.println();

                character_global = Serial.read();         //citeste caracter cu caracter textul primit
//Serial.print("character = ");
//Serial.println(character_global );
//Serial.println();
                if (character_global == 'q') {        //daca am apasat butonul de stop din aplicatie
                  character_global = 0;
              //    ST_state = HIGH;  
               stop_bluetooth = true;  // ca sa iasa din while
               
//Serial.println("Apasat buton stop ");
//Serial.print("STOP_BLUETOOTH =  ");
//Serial.println(stop_bluetooth);
//Serial.println();
                }
              }
            }
//Serial.println("OUTSIDE First (ON) While ");
//Serial.print("STOP_BLUETOOTH =  ");
//Serial.println(stop_bluetooth);
//Serial.println();
            this->time_start = millis() / 1000;
          } else if (hon == 0  && mon == 0) {
            
            lcd.setCursor(0, 1);
            lcd.print("Ton = 0. Exiting ");
            myDelay(2000);
            if (Serial.available() >= 0) {         //citeste informatia de la telefon
              character_global = Serial.read();         //citeste caracter cu caracter textul primit
              if (character_global == 'q') {        //daca am apasat butonul de stop din aplicatie
                character_global = 0;
                //    ST_state = HIGH;  
               stop_bluetooth = true;  // ca sa iasa din while
              }
            }
          }
          on = false;
        }
        if (on == false) {


          if (hoff != 0 || minoff != 0) {    //stingem lampile daca macar una dintre cele doua valori este diferita de zero
            digitalWrite(9, LOW);
            digitalWrite(10, LOW);
            digitalWrite(11, LOW);
            digitalWrite(12, LOW);
            digitalWrite(13, LOW);
            digitalWrite(6, LOW);
//Serial.println("Am inchis lampile toate toate ");
//Serial.print("STOP_BLUETOOTH =  ");
//Serial.println(stop_bluetooth);
//Serial.println();
            meniu.setMesaj("Selectat: Program 3");
            meniu.afisare();
            lcd.setCursor(2, 3);
            lcd.print("OFF");
            timeleft(hoff, minoff, millis() / 1000 - time_start);

            while (millis() / 1000 - time_start <= (hoff * 3600 + minoff * 60)  && ST_state == LOW &&  stop_bluetooth == false) {
//Serial.println("Inside Second (OFF) While ");
//Serial.print("STOP_BLUETOOTH =  ");
//Serial.println(stop_bluetooth);
//Serial.println();

              ST_state  = digitalRead(7);
              afisareOra();
              myDelay(1000);
//              checksensors(minCurrentVal, maxCurrentVal); //--------------------------------------------------------> sensors
//              blink_led();

              unsigned long currentMillis = millis();
              if (currentMillis - previousMillis >= 60000) {  //aka 60 secunde
                previousMillis = currentMillis;
                timeleft(hoff, minoff, millis() / 1000 - time_start);
              }

              mesajTimp = String(getHourLeft(hoff, minoff, millis() / 1000 - time_start)) + "h " + String(getMinLeft(hoff, minoff, millis() / 1000 - time_start)) + "min";
              Serial.print(meniu.getMesaj()+ " OFF");
              Serial.print(",");
              Serial.print(mesajTimp );
              Serial.print(",");
              Serial.println(verificare_lampi());

              if (Serial.available() >= 0) {         //citeste informatia de la telefon
                character_global = Serial.read();         //citeste caracter cu caracter textul primit
                if (character_global == 'q') {        //daca am apasat butonul de stop din aplicatie
                  character_global = 0;
                 // ST_state = HIGH;  
                 stop_bluetooth = true;  // = HIGH ca sa iasa din while

                }
              }
            }
//Serial.println("OUTSIDE Second (OFF) While ");
//Serial.print("STOP_BLUETOOTH =  ");
//Serial.println(stop_bluetooth);
//Serial.println();

          } else if (hoff == 0  && minoff == 0) {
            lcd.setCursor(0, 1);
            lcd.print("Toff = 0. Exiting");
            myDelay(2000);
            if (Serial.available() >= 0) {         //citeste informatia de la telefon
              character_global = Serial.read();         //citeste caracter cu caracter textul primit
              if (character_global == 'q') {        //daca am apasat butonul de stop din aplicatie
                character_global = 0;
                //    ST_state = HIGH;  
               stop_bluetooth = true;  // ca sa iasa din while
              }
            }
          }
          on = true; //apoi scriem on = false ca sa le oprim
          //  ST_state = digitalRead(7);                               habar nu am de ce citeam inca o data butonul de stop. L-am scos ca sa imi inchida programul
          // cand apasam din aplicatie pe stio
        }
      }
    }




    void startOffOn(long hon, int mon, long hoff, int minoff) {    // ------------------------------------  functia de OFF/ON

      int ST_state = digitalRead(7);
      previousMillis = 0;
      on = false;
      ofon = true;

      meniu.setMesaj("Selectat: Program 3");
      meniu.afisare();
      while (ST_state == LOW && stop_bluetooth == false) {

        if (on == false) {
          if (hoff != 0 || minoff != 0) {
            digitalWrite(9, LOW);
            digitalWrite(10, LOW);
            digitalWrite(11, LOW);
            digitalWrite(12, LOW);
            digitalWrite(13, LOW);
            digitalWrite(6, LOW);

            //      meniu.setMesaj("Selectat: Program 3");
            //      meniu.afisare();
            lcd.setCursor(2, 3);
            lcd.print("OFF");

            this->time_start = millis() / 1000;
            timeleft(hoff, minoff, millis() / 1000 - time_start);

            while (millis() / 1000 - time_start <= (hoff * 3600 + minoff * 60)  && ST_state == LOW && stop_bluetooth == false) {
            //  checksensors(minCurrentVal, maxCurrentVal); //--------------------------------------------------------> sensors
            //  blink_led();
              afisareOra();
              myDelay(1000);
              ST_state  = digitalRead(7);
              mesajTimp = String(getHourLeft(hoff, minoff, millis() / 1000 - time_start)) + "h " + String(getMinLeft(hoff, minoff, millis() / 1000 - time_start)) + "min";
              Serial.print(meniu.getMesaj()+ " OFF");
              Serial.print(",");
              Serial.print(mesajTimp );
              Serial.print(",");
              Serial.println(verificare_lampi());

              if (Serial.available() >= 0) {         //citeste informatia de la telefon
//Serial.println("SERIAL AVAILABLE ");
//Serial.println();

                character_global = Serial.read();         //citeste caracter cu caracter textul primit
//Serial.print("character = ");
//Serial.println(character_global );
//Serial.println();
          //      character_global = Serial.read();         //citeste caracter cu caracter textul primit
                if (character_global == 'q') {        //daca am apasat butonul de stop din aplicatie
                  character_global = 0;
                  //    ST_state = HIGH;  
               stop_bluetooth = true;  // ca sa iasa din while
                }
              }
             
              unsigned long currentMillis = millis();
              if (currentMillis - previousMillis >= 60000) {  //aka 60 secunde
                previousMillis = currentMillis;
                timeleft(hoff, minoff, millis() / 1000 - time_start);
              }
              if (ST_state == HIGH) {
                ofon = false;     //daca vrem noi sa terminam programul sa nu mai aprinda lampile inainte sa se opreasca
              }                  // altfel le aprinde alea 6 secunde si abia dupa se opreste => not good
            }
          } else if (hoff == 0  && minoff == 0) {
            lcd.setCursor(0, 1);
            lcd.print("Toff = 0. Exiting");
            myDelay(2000);
          }
        }
        on = true;
        if (on = true && ofon == true && stop_bluetooth == false) {              //pornim lampile

          if (hon != 0 || mon != 0) {
            digitalWrite(9, HIGH);
            digitalWrite(12, HIGH);
            digitalWrite(6, HIGH);
            myDelay(2000);
            digitalWrite(10, HIGH);
            myDelay(2000);
            digitalWrite(11, HIGH);
            myDelay(2000);

            lcd.setCursor(4, 3);
            lcd.print(" ");
            lcd.setCursor(2, 3);
            lcd.print("ON");

            this->time_start = millis() / 1000;
            timeleft(hon, mon, millis() / 1000 - time_start);

            while (millis() / 1000 - time_start <= (hon * 3600 + mon * 60)  && ST_state == LOW && stop_bluetooth == false) {
              afisareOra();
              checksensors(minCurrentVal, maxCurrentVal); //--------------------------------------------------------> sensors
              blink_led();
              myDelay(1000);
              ST_state  = digitalRead(7);
              unsigned long currentMillis = millis();
              if (currentMillis - previousMillis >= 60000) {  //aka 60 secunde
                previousMillis = currentMillis;
                timeleft(hon, mon, millis() / 1000 - time_start);
              }

              mesajTimp = String(getHourLeft(hon, mon, millis() / 1000 - time_start)) + "h " + String(getMinLeft(hon, mon, millis() / 1000 - time_start)) + "min";
              Serial.print(meniu.getMesaj()+ " ON");
              Serial.print(",");
              Serial.print(mesajTimp ); 
              Serial.print(",");
              Serial.println(verificare_lampi());
              if (Serial.available() >= 0) {         //citeste informatia de la telefon
                character_global = Serial.read();         //citeste caracter cu caracter textul primit
                if (character_global == 'q') {        //daca am apasat butonul de stop din aplicatie
                  character_global = 0;
                 //    ST_state = HIGH;  
               stop_bluetooth = true;  // ca sa iasa din while
                }
              }
            
            }

          } else if (hon == 0  && mon == 0) {
            lcd.setCursor(0, 1);
            lcd.print("Ton = 0. Exiting ");
            myDelay(2000);
          }

        }
        on = false;
      //  ST_state = digitalRead(7);
      }
    }

};   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   4   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

MeniuPrincipal2 meniu1 = MeniuPrincipal2();
MeniuProgram1 program1 = MeniuProgram1();
MeniuProgram3 program3 = MeniuProgram3();



/*  joystick
  VRx = A0;
  VRy = A1;
  SW = 2;

    LCD
  SCL = A5;
  SDA = A4;
*/

/*
  declarare PINI
*/

const int stop_button = 7;
const int start_button = 8;
int SB_state = 0;
int ST_state = 0;
const int led1 = 9;
const int led2 = 10;
const int led3 = 11;
const int led4 = 12;
const int led_rosu = 13;
const int led_verde = 6;

int col = 0;
int row = 1;

/*
    joystick
*/
int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

/*
   instantiere clase
*/



/*
   variabile booleane ca sa activam functionalitatea unui anumit meniu
*/

boolean mp = true;
boolean m1 = false;
boolean p1 = false;
boolean p2 = false;
boolean p22 = false;
boolean p3 = false;
boolean p32 = false;



boolean workingp1 = false;
/*
   variabile pentru valorile de timp
*/
String luna;

int setHour = 0;
int setMinutes = 0;

int setHourOn = 0;
int setMinutesOn = 0;
int setHourOff = 0;
int setMinutesOff = 0;
int cursorVal = 0;
