void checkp3() {
  while (p3) {

    xPosition = analogRead(VRy);
    yPosition = analogRead(VRx);
    SW_state = digitalRead(SW);
    mapX = map(xPosition, 0, 1023, -512, 512);
    mapY = map(yPosition, 0, 1023, -512, 512);

    /*
       cand vrem sa crestem ora sau minutele (joystick up)
    */
    while (mapY > 150) {                                                                                 //@INCREMENT@
      if (cursorVal == 0) {
        if (setHourOn + 1 > 99) {
          setHourOn = 0;
          lcd.setCursor(10, 0);
          lcd.print(" ");
          lcd.setCursor(9, 0);
        } else {
          setHourOn++;
        }
        lcd.setCursor(9, 0);
        lcd.print(setHourOn);
        delay(200);

      } else if (cursorVal == 1) {
        if (setMinutesOn + 5 > 55) {
          setMinutesOn = 0;
          lcd.setCursor(18, 0);
          lcd.print(" ");
          lcd.setCursor(17, 0);
        } else {
          setMinutesOn = setMinutesOn + 5;
        }

        lcd.setCursor(17, 0);
        lcd.print(setMinutesOn);
        delay(300);
      } else if (cursorVal == 2) {
        if (setHourOff + 1 > 99) {
          setHourOff = 0;
          lcd.setCursor(10, 1);
          lcd.print(" ");
          lcd.setCursor(9, 1);
        } else {
          setHourOff++;
        }
        lcd.setCursor(9, 1);
        lcd.print(setHourOff);
        delay(200);

      }
      else if (cursorVal == 3) {
        if (setMinutesOff + 5 > 55) {
          setMinutesOff = 0;
          lcd.setCursor(18, 1);
          lcd.print(" ");
          lcd.setCursor(17, 1);
        } else {
          setMinutesOff = setMinutesOff + 5;
        }

        lcd.setCursor(17, 1);
        lcd.print(setMinutesOff);
        delay(300);
      }
      mapY = map(analogRead(VRx), 0, 1023, -512, 512);
    }

    /*
       cand vrem sa scadem ora sau minutele (joystick down)
    */
    while (mapY < -150) {
      if (cursorVal == 0) {
        if (setHourOn - 1 < 0) {
          setHourOn = 99;
        } else {
          setHourOn--;
          if (setHourOn == 9) {
            lcd.setCursor(10, 0);
            lcd.print(" ");
            lcd.setCursor(9, 0);
          }
        }
        lcd.setCursor(9, 0);
        lcd.print(setHourOn);
        delay(200);

      }
      if (cursorVal == 1) {
        if (setMinutesOn - 5 < 0) {
          setMinutesOn = 55;

        } else {
          setMinutesOn = setMinutesOn - 5;
        }

        if (setMinutesOn < 10) {
          lcd.setCursor(18, 0);
          lcd.print(" ");
          lcd.setCursor(17, 0);
        }
        lcd.setCursor(17, 0);
        lcd.print(setMinutesOn);
        delay(300);
      }

      if (cursorVal == 2) {
        if (setHourOff - 1 < 0) {
          setHourOff = 99;
        } else {
          setHourOff--;
          if (setHourOff == 9) {
            lcd.setCursor(10, 1);
            lcd.print(" ");
            lcd.setCursor(9, 1);
          }
        }
        lcd.setCursor(9, 1);
        lcd.print(setHourOff);
        delay(200);

      }
      if (cursorVal == 3) {
        if (setMinutesOff - 5 < 0) {
          setMinutesOff = 55;
        } else {
          setMinutesOff = setMinutesOff - 5;
        }
        if (setMinutesOff < 10) {
          lcd.setCursor(18, 1);
          lcd.print(" ");
          lcd.setCursor(17, 1);
        }
        lcd.setCursor(17, 1);
        lcd.print(setMinutesOff);
        delay(300);
      }

      mapY = map(analogRead(VRx), 0, 1023, -512, 512);
    }


    while (mapX > 200) {

      if ((cursorVal + 1) <= 6) {
        cursorVal++;
      } else if ((cursorVal + 1) > 6) {
        cursorVal = 0;
      }

      if (cursorVal == 0) {  //pentru a selecta una dintre cele 6 variante
        // si sa ne apara sageti cu valoarea pe care o avem selectata
        lcd.setCursor(6, 3);
        lcd.print(" ");
        lcd.setCursor(6, 0);
        lcd.print(">");
      } else if (cursorVal == 1) {
        lcd.setCursor(6, 0);
        lcd.print(" ");
        lcd.setCursor(12, 0);
        lcd.print(">");

      } else if (cursorVal == 2) {
        lcd.setCursor(12, 0);
        lcd.print(" ");
        lcd.setCursor(6, 1);
        lcd.print(">");

      } else if (cursorVal == 3) {
        lcd.setCursor(6, 1);
        lcd.print(" ");
        lcd.setCursor(12, 1);
        lcd.print(">");

      } else if (cursorVal == 4) {
        lcd.setCursor(12, 1);
        lcd.print(" ");
        lcd.setCursor(0, 3);
        lcd.print(">");

      } else if (cursorVal == 5) {
        lcd.setCursor(0, 3);
        lcd.print(" ");
        lcd.setCursor(6, 2);
        lcd.print(">");

      } else if (cursorVal == 6) {
        lcd.setCursor(6, 2);
        lcd.print(" ");
        lcd.setCursor(6, 3);
        lcd.print(">");

      }
      delay(500);
      mapX = map(analogRead(VRy), 0, 1023, -512, 512);
    }


    while (mapX < -200) {         //cand navigam la dreapta in setarile programului 3

      if ((cursorVal - 1) >= 0) {
        cursorVal--;
      } else if ((cursorVal - 1) < 0) {
        cursorVal = 6;
      }

      if (cursorVal == 0) {  //pentru a selecta una dintre cele 6 variante
        // si sa ne apara sageti cu valoarea pe care o avem selectata
        lcd.setCursor(12, 0);
        lcd.print(" ");
        lcd.setCursor(6, 0);
        lcd.print(">");
      } else if (cursorVal == 1) {
        lcd.setCursor(6, 1);
        lcd.print(" ");
        lcd.setCursor(12, 0);
        lcd.print(">");

      } else if (cursorVal == 2) {
        lcd.setCursor(12, 1);
        lcd.print(" ");
        lcd.setCursor(6, 1);
        lcd.print(">");

      } else if (cursorVal == 3) {
        lcd.setCursor(0, 3);
        lcd.print(" ");
        lcd.setCursor(12, 1);
        lcd.print(">");

      }
      else if (cursorVal == 4) {
        lcd.setCursor(6, 2);
        lcd.print(" ");
        lcd.setCursor(0, 3);
        lcd.print(">");

      }
      else if (cursorVal == 5) {
        lcd.setCursor(6, 3);
        lcd.print(" ");
        lcd.setCursor(6, 2);
        lcd.print(">");

      } else if (cursorVal == 6) {
        lcd.setCursor(6, 0);
        lcd.print(" ");
        lcd.setCursor(6, 3);
        lcd.print(">");

      }

      delay(500);
      mapX = map(analogRead(VRy), 0, 1023, -512, 512);
    }

    SW_state = digitalRead(SW);
    if (SW_state == LOW) {  //daca apasam joystick-ul
      switch (cursorVal) {
        case 4:
          meniu1.afisare();
          delay(500);
          m1 = true;
          p3 = false;
          row = 1;
          break;

        case 5:
          p3 = false;
          p32 = true;
          afisare32();
          lcd.setCursor(6, 3);
          lcd.print("OFF - ON");
          program3.setHourOn(setHourOn);
          program3.setHourOff(setHourOff);
          program3.setMinutesOn(setMinutesOn);
          program3.setMinutesOff(setMinutesOff);

          delay(400);
          break;

        case 6:
          p3 = false;
          p32 = true;
          afisare32();
          lcd.setCursor(6, 3);
          lcd.print("ON - OFF");
          program3.setHourOn(setHourOn);
          program3.setHourOff(setHourOff);
          program3.setMinutesOn(setMinutesOn);
          program3.setMinutesOff(setMinutesOff);
          delay(400);
      }
    }
  }

}
