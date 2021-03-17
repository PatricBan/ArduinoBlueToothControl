
void checkm1() {
  while (m1) {

    yPosition = analogRead(VRx);
    SW_state = digitalRead(SW);
    ST_state = digitalRead(stop_button);
    mapY = map(yPosition, 0, 1023, -512, 512);

    while (mapY < - 150) {        // pentru a naviga in SUS prin programe
      lcd.setCursor(col, row);
      lcd.print(" ");

      if ((row + 1) > 3) {
        row = 0;
        lcd.setCursor(col, row);
        lcd.print(">");

      } else {
        lcd.setCursor(col, row + 1);
        lcd.print(">");
        row++;
      }
      delay(300);

      mapY = map(analogRead(VRx), 0, 1023, -512, 512);
    }

    while (mapY > 150) { //pentru a naviga in JOS pentru programe

      delay(50);
      lcd.setCursor(col, row);
      lcd.print(" ");

      if ((row - 1) < 0) {
        row = 3;
        lcd.setCursor(col, row);
        lcd.print(">");

      } else {
        lcd.setCursor(col, row - 1);
        lcd.print(">");
        row--;
      }
      delay(300);

      mapY = map(analogRead(VRx), 0, 1023, -512, 512);


    }

    if (SW_state == LOW) {      //apasam joystick-ul pentru a selecta programul
      switch (row) {
        case 0:
          meniu.afisare();
          delay(500);
          m1 = false;
          mp = true;

          break;
        case 1:
          program1.afisare();
          delay(500);
          m1 = false;
          p1 = true;
          break;
        case 2: program2.selectare_timer();
          m1 = false;
          p2 = true;
          cursorVal = 0;
          break;
        case 3:
          m1 = false;
          p3 = true;
          cursorVal = 0;
          setHourOn = 0;
          setHourOff = 0;
          setMinutesOn = 0;
          setMinutesOff = 0;
          program3.setHourOn(0);
          program3.setHourOff(0);
          program3.setMinutesOn(0);
          program3.setMinutesOff(0);
          program3.afisare();
          break;
      }
    }
    if (ST_state == HIGH) {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      delay(500);
    }
  }
}
