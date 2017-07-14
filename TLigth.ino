
const int LED_PIN_1 = 49;
const int LED_PIN_2 = 47;
const int LED_PIN_3 = 53;
const int LED_PIN_4 = 41;
const int LED_PIN_NAS = 22;

int LED_state = 0;

void init_ligth(){
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
  pinMode(LED_PIN_NAS, OUTPUT);
  
  digitalWrite (LED_PIN_1,LOW);
  digitalWrite (LED_PIN_2,LOW);
  digitalWrite (LED_PIN_3,LOW);
  digitalWrite (LED_PIN_4,LOW);
  digitalWrite (LED_PIN_NAS,LOW);
   
}


int get_LED_fron_state(){
  return LED_state;
}

void LEDS_ON_fron(){
    digitalWrite (LED_PIN_1,HIGH);
    digitalWrite (LED_PIN_2,HIGH); 
    LED_state = 1;
}
void LEDS_ON_frena(){
    digitalWrite (LED_PIN_3,HIGH);
    digitalWrite (LED_PIN_4,HIGH); 
}


void LEDS_off_frena(){
    digitalWrite (LED_PIN_3,LOW);
    digitalWrite (LED_PIN_4,LOW); 
}


void LEDS_OFF_fron(){ 
    digitalWrite (LED_PIN_1,LOW);
    digitalWrite (LED_PIN_2,LOW); 
    LED_state = 0;
}


void LED_ON_nas(){ 
    digitalWrite (LED_PIN_NAS,LOW);
}

void LED_OFF_nas(){ 
    digitalWrite (LED_PIN_NAS,LOW);
}

