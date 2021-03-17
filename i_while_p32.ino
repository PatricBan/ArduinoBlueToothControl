bool program3startON = false;
bool program3startOFF = false;

int countp3on;
int countp3off;


void checkp32() {

  program3startON = false;
  program3startOFF = false;

  while (p32) {
    countp3on = 0;
    countp3off = 0;

    SB_state = digitalRead(start_button);
    if (SB_state == HIGH) {
      switch (cursorVal) {
        case 6:                                               // START ON OFF
          while (SB_state == HIGH) {

            SB_state = digitalRead(start_button);
            if (SB_state == HIGH && countp3on >= 3) {
              mp = true;
              p32 = false;
              meniu.setMesaj("Selectat: Program 3");
              meniu.afisare();

              program3startON = true;
              break;
            }

            SB_state = digitalRead(start_button);
            myDelay(1000);
            countp3on ++;
          }
          break;

        case 5:                                               // START OFF ON
          while (SB_state == HIGH) {
            SB_state = digitalRead(start_button);

            if (SB_state == HIGH && countp3off >= 3) {
              mp = true;
              p32 = false;
              meniu.setMesaj("Selectat: Program 3");
              meniu.afisare();

              program3startOFF = true;
              break;
            }

            SB_state = digitalRead(start_button);
            myDelay(1000);
            countp3off ++;
          }
          break;
      }

    }
    if (program3startON == true) {
      program3.startOnOff(setHourOn, setMinutesOn, setHourOff, setMinutesOff);
    }
    if (program3startOFF == true) {
      program3.startOffOn(setHourOn, setMinutesOn, setHourOff, setMinutesOff);
    }
  }
}



// void checkp32(){
// while(p32){
//   SB_state = digitalRead(start_button);
//   if(SB_state == HIGH){
//    switch(cursorVal){
//      case 6:
//    mp = true;
//    p32 = false;
//    meniu.setMesaj("Selectat: Program 3");
//    meniu.afisare();
//
//    program3.startOnOff(setHourOn, setMinutesOn, setHourOff, setMinutesOff);
//    break;
//
//      case 5:
//     mp = true;
//     p32 = false;
//    meniu.setMesaj("Selectat: Program 3");
//    meniu.afisare();
//   ;
//    program3.startOffOn(setHourOn, setMinutesOn, setHourOff, setMinutesOff);
//    }
//   }
//   SW_state = digitalRead(SW);
//  if(SW_state == LOW){
//    p3 = true;
//    p32 = false;
//    program3.afisare();
//    cursorVal = 0;
//    delay(400);
//    break;
//  }
//  }
// }
