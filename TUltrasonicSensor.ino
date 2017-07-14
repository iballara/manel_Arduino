/*************************************************
** Tad Ultrasonic Sensor: Reads the distance between the sensor and objects
** Enginyers: Ignasi Ballarà Franco, Joaquim Porte Jimenez, Arnau Tienda Tejedo
** Date:      02/05/2017
*************************************************/

const int PIN_Trig = 2; 
const int PIN_Echo = 3;
int state_US = 0; 
unsigned long US_millisant = 0;
int start_Ultrasound = 0;
String info_ultrasound;
int distance = 0;
const String distance_string = "\tDistance: \t";


/************************************************* Private functions *************************************************/

int readUltrasound(){
  int x = 0;
  int distanceCm = 0;
  digitalWrite(PIN_Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_Trig, LOW);
  x = pulseIn(PIN_Echo, HIGH);
  distanceCm = x / 29.1 / 2 ;
  if (distanceCm < 20){
      return 1;  
  }else{
      return  0;  
  }
  return  distanceCm;  
}

/************************************************* Public functions *************************************************/

void init_TUltrasonicSensor(){
  pinMode(PIN_Trig, OUTPUT);
  pinMode(PIN_Echo, INPUT);
  digitalWrite(PIN_Trig, LOW);
  state_US = 0;
}



