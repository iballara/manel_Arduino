/*************************************************
** Tad Servo  Motor: This tad allows servo motor control(angle -90º to 90º).
** Enginyers: Ignasi Ballarà Franco, Joaquim Porte Jimenez, Arnau Tienda Tejedo
** Date:      02/05/2017
*************************************************/

Servo myservo;
const int PIN_Servo   = 8;
const int Servo_right = 0;
const int Servo_left  = 180;
const int Servo_forw  = 90;

/************************************************* Public functions *************************************************/


/*************************************************
** Pre:  --
** Post: Servo motor can start working.
*************************************************/
void init_TServo(){
  myservo.attach(PIN_Servo);  // attaches the servo on pin 9 to the servo object
  set_servo_forw ();
}

/*************************************************
** Pre:  --
** Post: Servo motor's angle will change to the input value(-90 to 90).
*************************************************/
void set_Servo_Value (int value){
    myservo.write(value); 
}

void set_servo_left (){
    set_Servo_Value (Servo_left);
}

void set_servo_right (){
    set_Servo_Value (Servo_right);

}

void set_servo_forw (){
    set_Servo_Value (Servo_forw);

}

