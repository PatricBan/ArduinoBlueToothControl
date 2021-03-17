struct ts t;

void setup() {
  Serial.begin(9600);


  //_____________________________________________________________________RTC:


  Wire.begin();

  // DS3231_init(DS3231_INTCN);
  DS3231_init(DS3231_CONTROL_INTCN);


  //  t.hour=9; //ora
  //  t.min=21;
  //  t.sec=0;
  //
  //  t.mday=26;    //data
  //  t.mon=8;
  //  t.year=2020;
  //  DS3231_set(t);

  //______________________________________________________________________RTC^

  blinkLed = false;
  lcd.init();
  lcd.backlight();

  // pinMode(A2, OUTPUT);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  delay(100);
  meniu.afisare();

  // pinMode(A2, OUTPUT);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led_rosu, OUTPUT);
  pinMode(start_button, INPUT);
  pinMode(stop_button, INPUT);

  Serial.setTimeout(2000);
  //  while(true){
  //       Serial.print(meniu.getMesaj());
  //       Serial.print("|");
  //       Serial.print(" - ");
  //       Serial.print("|");
  //       Serial.println(mesajTimp );
  //       myDelay(2000);
  //  }
  setCurrentBounds(0, 210);
}
