/**********************************************************************************************************************
** Tad Temperature: This tad displays the position of the black part in the reflectance sensor array.
** Enginyers: Ignasi Ballarà Franco, Joaquim Porte Jimenez, Arnau Tienda Tejedo
** Date:      02/05/2017
**********************************************************************************************************************/

#define NUM_SENSORS   6     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   28     // emitter is controlled by digital pin 2

QTRSensorsRC qtrrc((unsigned char[]) {22,23,24,25,26,27},
NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];
bool sensorValues3[NUM_SENSORS];

int state_TIRs = 0;
unsigned long millisant_TIRs = 0;
int start_Infra;
unsigned int position=0;
String data_position;

/************************************************* Private functions *************************************************/

void readInfraRed(){
  
    position = qtrrc.readLine(sensorValues);
    data_position = "\nPosition: ";
    
    for (unsigned char i = 0; i < NUM_SENSORS; i++)  {
        if (sensorValues[i] > 150) {
            sensorValues3[i] = true;
        }else{
            sensorValues3[i] = false;
        }
        
    }
  
}

/************************************************* Public functions *************************************************/


void init_TIRInfraRedSensor(){
    LED_OFF_nas();
    for (int i = 0; i < 300; i++){  
        qtrrc.calibrate();
        delay(20);
    }
    LED_ON_nas();
    state_TIRs = 0;
    start_Infra = 0;

}

void asdad(){
    readInfraRed();
    Serial.println(sensorValues[0]);
    Serial.println(sensorValues[1]);
    Serial.println(sensorValues[2]);
    Serial.println(sensorValues[3]);
    Serial.println(sensorValues[4]);
    Serial.println(sensorValues[5]);

    delay(200);
}

void getinfraRed(bool *sensorValues2){
  
    readInfraRed();
    sensorValues2 = sensorValues3;
}

