String verificare_lampi() {
  if (lampa1 == false && lampa2 == false && lampa3 == false) return "Lampile 1 2 3 defecte";
  else if (lampa1 == false && lampa2 == false) return "Lampile 1 2 defecte";
  else if (lampa1 == false && lampa3 == false) return "Lampile 1 3 defecte";
  else if (lampa2 == false && lampa3 == false) return "Lampile 2 3 defecte";
  else if (lampa1 == false) return "Lampa 1 defecta";
  else if (lampa2 == false) return "Lampa 2 defecta";
  else if (lampa3 == false) return "Lampa 3 defecta";
  else return "Lampile sunt ok";
}

unsigned long get_hleft;
unsigned long get_minleft;
long getHourLeft(long h, int m, unsigned long t) {
  get_hleft = ((h * 3600 + m * 60) - t) / 3600;
  return get_hleft;
}

long getMinLeft(long h, int m, unsigned long t) {
  get_minleft = (((h * 3600 + m * 60) - t) % 3600) / 60;
  return get_minleft;
}


void afisareOra() {
  DS3231_get(&t);

  lcd.setCursor(0, 0);  //printare data pe lcd
  lcd.print(t.mday);
  lcd.print("/");
  lcd.print(t.mon);
  lcd.print("/");
  lcd.print(t.year);

  lcd.setCursor(12, 0);   //printare ora pe lcd

  if (t.hour < 10) {     //daca <10 sa apara 09, 08, 07.... etc
    lcd.print("0");
    lcd.print(t.hour);
  } else {
    lcd.print(t.hour);
  }
  lcd.print(":");

  if (t.min < 10) {     //daca <10 sa apara 09, 08, 07.... etc
    lcd.print("0");
    lcd.print(t.min);
  } else {
    lcd.print(t.min);
  }
  lcd.print(":");

  if (t.sec < 10) {     //daca <10 sa apara 09, 08, 07.... etc
    lcd.print("0");
    lcd.print(t.sec);
  } else {
    lcd.print(t.sec);
  }
}

void myDelay(int del) {
  unsigned long myPrevMillis = millis();
  while (millis() - myPrevMillis <= del) {};
}
//_________________________________________________________________________________________WIFI^
void afisare32() {
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("Press START to begin");

  lcd.setCursor(1, 0);
  lcd.print("ON:");

  lcd.setCursor(7, 0);
  lcd.print("h");

  lcd.setCursor(11, 0);
  lcd.print("min");

  if (setHourOn > 9) {
    lcd.setCursor(5, 0);
    lcd.print(setHourOn);
  } else if (setHourOn <= 9) {
    lcd.setCursor(6, 0);
    lcd.print(setHourOn);
  }

  if (setMinutesOn > 9) {
    lcd.setCursor(9, 0);
    lcd.print(setMinutesOn);
  } else if (setMinutesOn <= 9) {
    lcd.setCursor(10, 0);
    lcd.print(setMinutesOn);
  }
  //___________________________________pentru off


  lcd.setCursor(1, 1);
  lcd.print("OFF:");

  lcd.setCursor(7, 1);
  lcd.print("h");

  lcd.setCursor(11, 1);
  lcd.print("min");

  if (setHourOff > 9) {
    lcd.setCursor(5, 1);
    lcd.print(setHourOff);
  } else if (setHourOff <= 9) {
    lcd.setCursor(6, 1);
    lcd.print(setHourOff);
  }

  if (setMinutesOff > 9) {
    lcd.setCursor(9, 1);
    lcd.print(setMinutesOff);
  } else if (setMinutesOff <= 9) {
    lcd.setCursor(10, 1);
    lcd.print(setMinutesOff);
  }
}

void afisare22() {
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("Press START to begin");

  lcd.setCursor(1, 0);
  lcd.print("Time: ");

  lcd.setCursor(8, 0);
  lcd.print("h");

  lcd.setCursor(12, 0);
  lcd.print("min");

  if (setHour > 9) {
    lcd.setCursor(6, 0);
    lcd.print(setHour);
  } else if (setHour <= 9) {
    lcd.setCursor(7, 0);
    lcd.print(setHour);
  }

  if (setMinutes > 9) {
    lcd.setCursor(10, 0);
    lcd.print(setMinutes);
  } else if (setMinutes <= 9) {
    lcd.setCursor(11, 0);
    lcd.print(setMinutes);
  }
}
void aprindere_lampi() {
  digitalWrite(led1, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led_verde, HIGH);
  delay(2000);
  checksensor1(0, 1000);
  digitalWrite(led2, HIGH);
  delay(2000);
  checksensor2(0, 1000);
  digitalWrite(led3, HIGH);
  delay(2000);
  checksensor3(0, 1000);
}


unsigned long hleft;
unsigned long minleft;



void timeleft(long h, int m, unsigned long t) {
  lcd.setCursor(11, 3);
  lcd.print("h");

  lcd.setCursor(16, 3);
  lcd.print("min");

  hleft = ((h * 3600 + m * 60) - t) / 3600;
  minleft = (((h * 3600 + m * 60) - t) % 3600) / 60 ;

  if (hleft <= 9) {
    lcd.setCursor(10, 3);
    lcd.print(hleft);
    lcd.setCursor(9, 3);
    lcd.print(" ");
  } else if (hleft >= 10) {
    lcd.setCursor(9, 3);
    lcd.print(hleft);
  }

  if (minleft <= 9) {
    lcd.setCursor(15, 3);
    lcd.print(minleft);
    lcd.setCursor(14, 3);
    lcd.print(" ");
  } else if (minleft >= 10) {
    lcd.setCursor(14, 3);
    lcd.print(minleft);
  }
}
