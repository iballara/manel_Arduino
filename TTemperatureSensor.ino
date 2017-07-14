/**********************************************************************************************************************
** Tad Temperature: This tad allows all seconds to display the ambient temperature value through the serial channel.
** Enginyers: Ignasi Ballarà Franco, Joaquim Porte Jimenez, Arnau Tienda Tejedo
** Date:      02/05/2017
**********************************************************************************************************************/

int state_TS = 0;
float temperature_value = 0.00;
unsigned long millisant = 0;
int start_temperature;
const int PIN_Data = 37;
const int PIN_Clock = 39;
const int PIN_CS = 35;
byte dataHigh,dataLow;
int dataIN;
String info_temperature;
const String temperature_string = "\tTemperature: \t";

/************************************************* Private functions *************************************************/

void readTemperature(){
      digitalWrite(PIN_CS, LOW);

    dataHigh = shiftIn(PIN_Data, PIN_Clock, MSBFIRST);
    
    //reads the higher part of the data sent by the sensor
    dataLow = shiftIn(PIN_Data, PIN_Clock, MSBFIRST);
    
    // DataIN is an int that contains dataHigh on the MSB and dataLow on the LSB
    dataIN = (dataHigh << 8) | dataLow;
    
    //as the data received only use 12 highest bits, an int has 16, and the three LSB received are not used: dataIn has been devided by 8  
    dataIN /= 8; 
    temperature_value=(float)dataIN * 0.0625;
        digitalWrite(PIN_CS, HIGH);

}

/************************************************* Public functions *************************************************/


void init_TTemperatureSensor(){
    pinMode(PIN_Data, INPUT);
    pinMode(PIN_Clock, OUTPUT);
    pinMode(PIN_CS, OUTPUT);
    digitalWrite(PIN_CS, HIGH);
    temperature_value = 0;
}

int getTemperature(){
  float data;
  readTemperature();
  return data*1000;
}

