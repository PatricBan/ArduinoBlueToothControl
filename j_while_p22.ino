
bool program2start;
int countp2;
void checkp22() {

  program2start = false;

  while (p22) {
    countp2 = 0;
    SB_state = digitalRead(start_button);

    while (SB_state == HIGH) {

      SB_state = digitalRead(start_button);
      if (SB_state == HIGH && countp2 >= 3) {
        mp = true;
        p22 = false;
        meniu.setMesaj("Selectat: Program 2");
        meniu.afisare();

        program2start = true;
        break;
      }

      SB_state = digitalRead(start_button);
      myDelay(1000);
      countp2 ++;
    }


    SW_state = digitalRead(SW);
    if (SW_state == LOW) {
      p2 = true;
      p22 = false;
      program2.selectare_timer();
      cursorVal = 0;
      delay(400);
      break;
    }
    if (program2start == true) {
      program2.start(setHour, setMinutes);
    }
  }
}

//void checkp22(){
//  while(p22){
//   SB_state = digitalRead(start_button);
//   if(SB_state == HIGH){
//    mp = true;
//    p22 = false;
//    meniu.setMesaj("Selectat: Program 2");
//    meniu.afisare();
//    program2.start(setHour, setMinutes);
//    break;
//   }
//   SW_state = digitalRead(SW);
//   if(SW_state == LOW){
//    p2 = true;
//    p22 = false;
//    program2.selectare_timer();
//    cursorVal = 0;
//    delay(400);
//    break;
//  }
//  }
//}
