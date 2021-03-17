void checkp2() {
  while (p2) {
    xPosition = analogRead(VRy);
    yPosition = analogRead(VRx);
    SW_state = digitalRead(SW);
    mapX = map(xPosition, 0, 1023, -512, 512);
    mapY = map(yPosition, 0, 1023, -512, 512);

    lcd.setCursor(7, 0);
    delay(200);

    /*
       cand vrem sa crestem ora sau minutele (joystick up)
    */
    while (mapY > 150) {
      if (cursorVal == 0) {
        if (setHour + 1 > 99) {
          setHour = 0;
          lcd.setCursor(9, 0);
          lcd.print(" ");
          lcd.setCursor(8, 0);
        } else {
          setHour++;
        }
        lcd.setCursor(8, 0);
        lcd.print(setHour);
        delay(200);

      }
      if (cursorVal == 1) {
        if (setMinutes + 5 > 55) {
          setMinutes = 0;
          lcd.setCursor(18, 0);
          lcd.print(" ");
          lcd.setCursor(17, 0);
        } else {
          setMinutes = setMinutes + 5;
        }

        lcd.setCursor(17, 0);
        lcd.print(setMinutes);
        delay(300);
      }
      mapY = map(analogRead(VRx), 0, 1023, -512, 512);
    }

    /*
       cand vrem sa scadem ora sau minutele (joystick down)
    */
    while (mapY < -150) {
      if (cursorVal == 0) {
        if (setHour - 1 < 0) {
          setHour = 99;
        } else {
          setHour--;
          if (setHour == 9) {
            lcd.setCursor(9, 0);
            lcd.print(" ");
            lcd.setCursor(8, 0);
          }
        }
        lcd.noBlink();
        lcd.setCursor(8, 0);
        lcd.print(setHour);
        delay(200);

      }
      if (cursorVal == 1) {
        if (setMinutes - 5 < 0) {
          setMinutes = 55;

        } else {
          setMinutes = setMinutes - 5;
        }

        if (setMinutes < 10) {
          lcd.setCursor(18, 0);
          lcd.print(" ");
          lcd.setCursor(17, 0);
        }
        lcd.noBlink();
        lcd.setCursor(17, 0);
        lcd.print(setMinutes);
        delay(300);
      }
      mapY = map(analogRead(VRx), 0, 1023, -512, 512);
    }

    while (mapX > 200) {

      if ((cursorVal + 1) <= 3) {
        cursorVal++;
      } else if ((cursorVal + 1) > 3) {
        cursorVal = 0;
      }

      if (cursorVal == 0) {  //pentru a selecta una dintre cele 4 variante
        // si sa ne apara sageti cu valoarea pe care o avem selectata
        lcd.setCursor(10, 3);
        lcd.print(" ");
        lcd.setCursor(8, 1);
        lcd.print("^");
      } else if (cursorVal == 1) {
        lcd.setCursor(8, 1);
        lcd.print(" ");
        lcd.setCursor(17, 1);
        lcd.print("^");

      } else if (cursorVal == 2) {
        lcd.setCursor(17, 1);
        lcd.print(" ");
        lcd.setCursor(0, 3);
        lcd.print(">");

      } else if (cursorVal == 3) {
        lcd.setCursor(0, 3);
        lcd.print(" ");
        lcd.setCursor(10, 3);
        lcd.print(">");

      }

      delay(500);
      mapX = map(analogRead(VRy), 0, 1023, -512, 512);
    }


    while (mapX < -200) {         //cand navigam la dreapta in setarile programului 2

      if ((cursorVal - 1) >= 0) {
        cursorVal--;
      } else if ((cursorVal - 1) < 0) {
        cursorVal = 3;
      }

      if (cursorVal == 0) {  //pentru a selecta una dintre cele 4 variante
        // si sa ne apara sageti cu valoarea pe care o avem selectata
        lcd.setCursor(17, 1);
        lcd.print(" ");
        lcd.setCursor(8, 1);
        lcd.print("^");
      } else if (cursorVal == 1) {
        lcd.setCursor(0, 3);
        lcd.print(" ");
        lcd.setCursor(17, 1);
        lcd.print("^");

      } else if (cursorVal == 2) {
        lcd.setCursor(10, 3);
        lcd.print(" ");
        lcd.setCursor(0, 3);
        lcd.print(">");

      } else if (cursorVal == 3) {
        lcd.setCursor(8, 1);
        lcd.print(" ");
        lcd.setCursor(10, 3);
        lcd.print(">");

      }

      delay(500);
      mapX = map(analogRead(VRy), 0, 1023, -512, 512);
    }

    SW_state = digitalRead(SW);
    if (SW_state == LOW) {  //daca apasam joystick-ul
      switch (cursorVal) {
        case 2:
          meniu1.afisare();
          delay(500);
          m1 = true;
          p2 = false;
          row = 1;
          cursorVal = 0;
          break;

        case 3:
          p22 = true;
          p2 = false;
          afisare22();
          cursorVal = 0;
          program2.setHour(setHour);
          program2.setMins(setMinutes);

          delay(300);
          break;
      }
    }
  }

}
