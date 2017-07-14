const int BP_PIN_1 = 45;
const int BP_PIN_2 = 48;


void init_BP(){
  
  pinMode(BP_PIN_1, INPUT);
  pinMode(BP_PIN_2, INPUT);
  
}

int get_left_bp(){
    if (digitalRead(BP_PIN_1) == LOW){
        return 1;
    }
    if (digitalRead(BP_PIN_2) == HIGH){
        return 0;
    }
}


int get_right_bp(){
    if (digitalRead(BP_PIN_2) == LOW){
        return 1;
    }
    if (digitalRead(BP_PIN_2) == HIGH){
        return 0;
    }
}
