bool program1start;
int countp1;

void checkp1() {
  program1start = false;

  while (p1) {
    countp1 = 0;

    SW_state = digitalRead(SW);
    if (SW_state == LOW) {  //daca apasam joystick-ul, ne intoarcem la meniul principal
      meniu1.afisare();
      delay(500);
      m1 = true;
      p1 = false;
      break;
    }

    SB_state = digitalRead(start_button);
    while (SB_state == HIGH) {

      SB_state = digitalRead(start_button);
      if (SB_state == HIGH && countp1 >= 3) {
        mp = true;
        p1 = false;
        meniu.setMesaj("Selectat: Program 1");
        meniu.afisare();
        workingp1 = true;
        program1start = true;
        break;
      }

      SB_state = digitalRead(start_button);
      myDelay(1000);
      countp1 ++;
    }
    if (program1start == true) {
      aprindere_lampi();
    }

    //  if (SB_state == HIGH) {   //daca apasam butonul de start,
    //     p1 = false;
    //     mp = true;
    //     workingp1 = true;
    //     meniu.setMesaj("Selectat: Program 1");
    //     meniu.afisare();
    //     aprindere_lampi();
    //     delay(500);
    //     break;
    //  }
  }
}
