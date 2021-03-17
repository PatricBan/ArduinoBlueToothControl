void setCurrentBounds(int a, int b) {
  minCurrentVal = a;
  maxCurrentVal = b;
}

void blink_led() {
  if (blinkLed == true) {
    if (led_off == true) {
      digitalWrite(led_rosu, HIGH);
      led_on = true;
      led_off = false;

    } else if (led_on == true) {
      digitalWrite(led_rosu, LOW);
      led_off = true;
      led_on = false;
    }
  }
}

void checksensors(int x, int y) {
  lampa1 = true;
  lampa2 = true;
  lampa3 = true;
  blinkLed = false;

  checksensor1(x, y);
  if (lampa1 == false) {
    afisareOra();
    delay(1000);
  }

  checksensor2(x, y);
  if (lampa2 == false) {
    afisareOra();
    delay(1000);
  }

  checksensor3(x, y);
  if (lampa3 == false) {
  }
  if (lampa1 == false && lampa2 == false && lampa3 == false) {
    digitalWrite(led4, LOW);
    digitalWrite(led_verde, LOW);
    vents = false;
  } else if (vents == false) {
    digitalWrite(led4, HIGH);
    digitalWrite(led_verde, HIGH);

  }
}

void checksensor1(int minVal, int maxVal) {
  maxReadings1 = 0;
  minReadings1 = 1024;
  for (int i = 0; i < 20; i++) {
    delay(1);
    sensorc1 =  analogRead(A2);
    if (sensorc1 < minReadings1) minReadings1  = sensorc1;
    if (sensorc1 > maxReadings1) maxReadings1  = sensorc1;
  }
  offsets1 = maxReadings1 - minReadings1;
//     Serial.print("max: ");
//     Serial.println(maxReadings1);
//     Serial.print("min: ");
//     Serial.println(minReadings1);
//     Serial.print("Offset1: ");
//     Serial.println(offsets1);
//     Serial.println(" ______________________________________________");

  if (offsets1 < minVal || offsets1 > maxVal) {
    lampa1 = false;
    blinkLed = true;
    lcd.setCursor(1, 1);
    lcd.print("Lampa 1 defecta");
    digitalWrite(led1, LOW);
  } else {
    digitalWrite(led1, HIGH);
  }
}

void checksensor2(int minVal, int maxVal) {
  maxReadings2 = 0;
  minReadings2 = 1024;
  for (int i = 0; i < 20; i++) {
    delay(1);
    sensorc2 =  analogRead(A3);
    if (sensorc2 < minReadings2) minReadings2  = sensorc2;
    if (sensorc2 > maxReadings2) maxReadings2  = sensorc2;
  }
  offsets2 = maxReadings2 - minReadings2;
//     Serial.print("max: ");
//     Serial.println(maxReadings2);
//     Serial.print("min: ");
//     Serial.println(minReadings2);
//     Serial.print("Offset2: ");
//     Serial.println(offsets2);
//        Serial.println(" ______________________________________________");

  if (offsets2 < minVal || offsets2 > maxVal) {
    lampa2 = false;
    blinkLed = true;
    lcd.setCursor(1, 1);
    lcd.print("Lampa 2 defecta");
    digitalWrite(led2, LOW);
  } else {
    digitalWrite(led2, HIGH);
  }
}

void checksensor3(int minVal, int maxVal) {
  maxReadings3 = 0;
  minReadings3 = 1024;
  for (int i = 0; i < 20; i++) {
    delay(1);
    sensorc3 =  analogRead(A4);
    if (sensorc3 < minReadings3) minReadings3  = sensorc3;
    if (sensorc3 > maxReadings3) maxReadings3  = sensorc3;
  }
  offsets3 = maxReadings3 - minReadings3;
//     Serial.print("max: ");
//     Serial.println(maxReadings3);
//     Serial.print("min: ");
//     Serial.println(minReadings3);
//     Serial.print("Offset3: ");
//     Serial.println(offsets3);
//     Serial.println(" ______________________________________________");
  if (offsets3 < minVal || offsets3 > maxVal) {
    lampa3 = false;
    blinkLed = true;
    lcd.setCursor(1, 1);
    lcd.print("Lampa 3 defecta");
    digitalWrite(led3, LOW);
  } else {
    digitalWrite(led3, HIGH);
  }
}
