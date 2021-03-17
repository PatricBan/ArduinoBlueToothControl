boolean program_1;
boolean program_2;
boolean program_3_on;
boolean program_3_off;
boolean start;
// boolean stop_bluetooth;   l-am scris in global ca sa il folosesc in p3on p3off
int val_h_on;
int val_h_off;
int val_m_on;
int val_m_off;
int count = 0;
String mesajLampi;

void checkmp() {
  
  stop_bluetooth = false;
  program_1 = false;
  program_2 = false;
  program_3_on = false;
  program_3_off = false;
  val_h_on = 0;
  val_h_off = 0;
  val_m_on = 0;
  val_m_off = 0;

  String data;
  String text1;
  String text2;
  String text3;
  String text4;
  String text5;
  char character;


  lcd.setCursor(8, 1);
  lcd.print("*: ");
  while (mp) {

    lcd.setCursor(0, 3);
    //______________________________________________ BlueTooth Stuff
    if (Serial.available() >= 0) {


      character = Serial.read();
      lcd.setCursor(12, 1);
      lcd.print(character);
      lcd.setCursor(6, 3);
      if (isAlphaNumeric(character)) {
        data = data + character;
      }
      lcd.print(data);
      lcd.setCursor(0, 3);



      if (character == '*') {
        lcd.setCursor(0, 3);


        if (data.startsWith("mon")) {                           //citeste de la cine primeste informatia (buton, slider)
          text2 = data.substring(3, data.length());
          lcd.print(text2);
        }
        else if (data.startsWith("hon")) {
          text1 = data.substring(3, data.length());
          lcd.print(text1);
        }

        else if (data.startsWith("hof")) {
          text3 = data.substring(3, data.length());
          lcd.print(text3);
        }
        else  if (data.startsWith("mof")) {
          text4 = data.substring(3, data.length());
          lcd.print(text4);
        }
        else if (data.startsWith("p")) {                         //citeste ce tip de program ai selectat
          text5 = data.substring(1, data.length());
          if (text5 == "p1") {
            program_1 = true;
            program_2 = false;
            program_3_on = false;
            program_3_off = false;
          }
          else if (text5 == "p2") {
            program_2 = true;
            program_1 = false;
            program_3_on = false;
            program_3_off = false;
          }
          else if (text5 == "p3on") {
            program_3_on = true;
            program_1 = false;
            program_2 = false;
            program_3_off = false;
          }
          else if (text5 == "p3off") {
            program_3_off = true;
            program_1 = false;
            program_2 = false;
            program_3_on = false;
          } else if (text5 != "p3off" && text5 != "p3on" && text5 != "p2" && text5 != "p1") {
            lcd.print("NU");
            myDelay(2000);
          }
          lcd.print(text5);
        }
        else if (data.startsWith("z")) {
          start = true;

        }
        else if (data.startsWith("q")) {
          stop_bluetooth = true;

        }


        delay(100);
        lcd.setCursor(13, 1);
        lcd.print(count++);

        //      lcd.setCursor(6,3);
        //      lcd.print(data);

        data = "";
      }
      delay(20);
    }
    val_h_on = text1.toInt();              //stocheaza in variabilele astea - numerele de langa slidere
    val_h_off = text3.toInt();
    val_m_on = text2.toInt();
    val_m_off = text4.toInt();

    lcd.setCursor(0, 1);
    lcd.print(val_h_on);
    lcd.setCursor(2, 1);
    lcd.print(val_m_on);
    lcd.setCursor(4, 1);
    lcd.print(val_h_off);
    lcd.setCursor(6, 1);
    lcd.print(val_m_off);
    lcd.setCursor(8, 3);
    lcd.print(text5);



    if (start == true) {               //daca apesi butonul de start, vede ce program e selectat si ii da start cu variabilele stocate mai sus
      start = false;

      if (program_1 == true) {
        program_1 == false;
        aprindere_lampi();
        meniu.setMesaj("Selectat: Program 1");
        meniu.afisare();
        workingp1 = true;

      } else if (program_2 == true) {
        program_2 = false;
        meniu.setMesaj("Selectat: Program 2");
        meniu.afisare();
        program2.start(val_h_on, val_m_on);
      }

      else if (program_3_on == true) {
        program_3_on = false;
        meniu.setMesaj("Selectat: Program 3");
        meniu.afisare();
        program3.startOnOff(val_h_on, val_m_on, val_h_off, val_m_off);
      }

      else if (program_3_off == true) {
        program_3_off = false;
        meniu.setMesaj("Selectat: Program 3");
        meniu.afisare();
        program3.startOffOn(val_h_on, val_m_on, val_h_off, val_m_off);
      }
    }

    //______________________________________________ BlueTooth Stuff ^^^^^

    previousMillis = 0;
    ST_state = digitalRead(stop_button);
    SW_state = digitalRead(SW);



    if (workingp1 == true) {                                 // daca functioneaza programul 1
      checksensors(minCurrentVal, maxCurrentVal);
      blink_led();
      afisareOra();
      myDelay(1000);
      Serial.print(meniu.getMesaj());
      Serial.print(",");
      Serial.print(" - ");
      Serial.print(",");
      Serial.println(mesajTimp );
    }

    if (SW_state == LOW ) {

      mp = false;
      m1 = true;
      row = 1;
      meniu1.afisare();
      delay(500);
      break;
    }

    if (ST_state == HIGH || stop_bluetooth == true) {                    //daca apasam butonul de stop sa inchida lampile si sa iasa din P1
      stop_bluetooth = false;
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led_rosu, LOW);
      digitalWrite(led_verde, LOW);

      meniu.setMesaj("Select a Program");
      meniu.afisare();
      workingp1 = false;
      delay(500);


    }

    // mesajTimp = String(getHourLeft() + "h " + String(getMinLeft) +"min ";  //   nu e ok ca e funtie getHourLeft(si aici trebuie parametrii)

    mesajTimp = String(1) + "h " + String(1) + "min ";
    //  mesajLampi = verificare_lampi();
    Serial.print(meniu.getMesaj());
    Serial.print(",");
    Serial.print(mesajTimp);
    Serial.print(",");
    Serial.println(verificare_lampi());

    // meniu.afisareOra();
    afisareOra();
    delay(100);

  }

}
