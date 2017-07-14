/*************************************************
** Tad WIFI: Allows communication using the WIFI
** Enginyers: Ignasi Ballarà Franco, Joaquim Porte Jimenez, Arnau Tienda Tejedo
** Date:      02/05/2017
* 
*  Trama WIFI:
*     -> Moviment motor
*     F-1 --> Endevant vel 1
*     F-2 --> Endevant vel 2
*     F-3 --> Endevant vel 3
*     
*     B-1 --> Enrere vel 1
*     B-2 --> Enrere vel 2
*     B-3 --> Enrere vel 3
*     
*     L-1-ANGLE (0 a 360) 
*     L-2-ANGLE (0 a 360) 
*     L-3-ANGLE (0 a 360) 
*     
*     R-1-ANGLE (0 a 360) 
*     R-2-ANGLE (0 a 360) 
*     R-3-ANGLE (0 a 360) 
*     
*     mod:aut,ang:00,lig:1,vel:+3,shp:0,acc:1
*     
*     -> Figures
*     R (Rodona)   
*     S (Cuadrado)
*     P (Triangle)
*     
*     -> Get value sensor
*     T -> Temperature
*************************************************/
const String light = "lig:";
const String be = "bl:"; 
const String bd = "br:"; 
const String us = "us:";
const String t = "tmp:"; 
const String x_s = "x:"; 
const String y_s = "y:"; 
const String z_s = "z:"; 


int state_WIFI = 0;
String data_write_wifi = "\n1. Temperature Sensor\n2. Accelerometer\n3. Ultrasound\n4. Infrared\n5. Right Motor\n6. Left Motor\n7. 180 Servo Motor\n8. LEDs\nOption? ";
int new_data2 = 0;
unsigned long Millis_wifi = 0;
int new_data_write_wifi = 0;
String data_write;
int status = WL_IDLE_STATUS;
char ssid[] = "AndroidAP6315"; //  your network SSID (name)
char pass[] = "123456789";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int packetSize;
unsigned int localPort = 2390;      // local port to listen on
char packetBuffer[255]; //buffer to hold incoming packet
char ReplyBuffer[255] = "acknowledged";

WiFiUDP Udp;


/************************************************* Public functions *************************************************/

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void init_TWIFI(){
    
    new_data_write_wifi = 1;
    state_WIFI = 0;
      
    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
      // don't continue:
      while (true);
    }
  
    String fv = WiFi.firmwareVersion();
    if (fv != "1.1.0") {
    //  Serial.println("Please upgrade the firmware");
    }
  
    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
      //Serial.print("Attempting to connect to SSID: ");
      //Serial.println(ssid);
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
      status = WiFi.begin(ssid,pass);
      // wait 10 seconds for connection:
      delay(6000);
    }
    //Serial.println("Connected to wifi");
    printWifiStatus();
  
    //Serial.println("\nStarting connection to server...");
    // if you get a connection, report back via serial:
    Udp.begin(localPort);
    IPAddress remoteIp = Udp.remoteIP();
    Serial.println(remoteIp);
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.endPacket();
                
}

char* getData_wifi(){
    new_data2 = 0;
    return packetBuffer;
}
int getnewData_wifi(){
  return new_data2;
}

void send_data_wifi(char send_Data[255]){
  strcpy (ReplyBuffer,send_Data);
  new_data_write_wifi = 1;
}



void trama_app(){
    float *accel;
    accel = readAccelerometer();
    readTemperature();
    data_write = light + get_LED_fron_state() + ","+ be + get_left_bp() + "," + bd + get_right_bp() +","+ us + readUltrasound() + "," + t + temperature_value+","+x_s+accel[0]+","+y_s+accel[1]+","+z_s+accel[2];
    //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.beginPacket(Udp.remoteIP(), 58723);
    data_write.toCharArray(ReplyBuffer, 255);
    Udp.write(ReplyBuffer);
    Udp.endPacket();
}

void motor_TWIFI(){

    switch(state_WIFI){
        case 0: 
            state_WIFI = 1;
            break;
        case 1:
     Serial.println("sss");

            packetSize = Udp.parsePacket();
                Serial.println("sss");

            if (packetSize) { 
                IPAddress remoteIp = Udp.remoteIP();
                strcpy(packetBuffer,"\0");
                int len = Udp.read(packetBuffer, 255);
                
                if (len > 0) {
                  packetBuffer[len] = 0;
                }
                Serial.println(remoteIp);
                Serial.println(Udp.remotePort());
                Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
                Udp.write("Acknowledged");
                Udp.endPacket();
                
                new_data2 = 1;
            }

            if (millis() > Millis_wifi + 1000){
                //trama_app();
                Millis_wifi = millis();
            } 
            
            if(new_data_write_wifi == 1){
                IPAddress remoteIp = Udp.remoteIP();
                Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
                Udp.write(ReplyBuffer);
                Udp.endPacket();
                new_data_write_wifi = 0;
            }
           
            break;
         case 2:
            new_data2 = 1;
            state_WIFI = 0;
            break;
    }
}



