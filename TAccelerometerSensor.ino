/*************************************************
** Tad Accelerometer: This tad gives each second sample values ​​x, y, z
** of the accelerometer to the serial channel. 
** Enginyers: Ignasi Ballarà Franco, Joaquim Porte Jimenez, Arnau Tienda Tejedo
** Date:      02/05/2017
*************************************************/

int state_AS = 0;
int start_Accelerometre = 1;
unsigned long AS_millisant = 0;
String info_accelerometre;
float x = 0,y = 0,z = 0;
const String X_String = "\tX = \t";
const String Y_String = "\tY = \t";
const String Z_String = "\tZ = \t";
float accel_dades[3];
MMA8452Q accel;

/************************************************* Private functions *************************************************/

float* readAccelerometer(){
   accel.read();
   accel_dades[0] = accel.cx;
   accel_dades[1] = accel.cy;
   accel_dades[2] = accel.cz;
   return accel_dades;
}

/************************************************* Public functions *************************************************/

/*************************************************
** Pre:  Tad Uart initialized.
** Post: Tad Accelerometer initialized.
*************************************************/
void init_TAccelerometerSensor(){
    Wire.begin(); 
    accel.init();
    state_AS = 1;
}

