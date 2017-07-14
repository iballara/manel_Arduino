/*************************************************
** Tad Uart: Allows communication using the UART
** Enginyers: Ignasi Ballarà Franco, Joaquim Porte Jimenez, Arnau Tienda Tejedo
** Date:      02/05/2017
*************************************************/

int state_UART = 0;
int drawMenu = 0;
String data_write2 = "\n1. Temperature Sensor\n2. Accelerometer\n3. Ultrasound\n4. Infrared\n5. Right Motor\n6. Left Motor\n7. 180 Servo Motor\n8. LEDs\nOption? ";
int new_data = 0;
char inBytes[5];
int new_data_write = 0;

/************************************************* Public functions *************************************************/


void init_TUART(){
    Serial.begin(9600);
    new_data_write = 1;
    state_UART = 0;
}

void writeUart(String data){
  Serial.flush();
  data_write2 = data;
  new_data_write = 1;
}

int getData(){
    new_data = 0;
    int p = 'q';
    if (inBytes[0] == 'q') return p;
    return atoi(inBytes);
}
int getnewData(){
  return new_data;
}

void motor_TUart(){

    switch(state_UART){
        case 0: 
            state_UART = 1;
            break;
        case 1:
            if (Serial.available() > 0){
                Serial.setTimeout(10);
                inBytes[0] = '\0';
                inBytes[1] = '\0';
                inBytes[2] = '\0';
                inBytes[3] = '\0';
                inBytes[4] = '\0';
                Serial.readBytes(inBytes, 5);
                Serial.println(inBytes);
                state_UART = 2;
            }
            
            if(new_data_write == 1){
                Serial.println(data_write2);
                new_data_write = 0;
            }
           
            break;
         case 2:
            new_data = 1;
            state_UART = 0;
            break;
    }
}



