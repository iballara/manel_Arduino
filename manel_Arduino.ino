/*************************************************
** Task:      Task2 Robot     
** Team:      GRUP 2
** Enginyers: Ignasi Ballarà Franco, Joaquim Porte Jimenez, Arnau Tienda Tejedo
** Date:      02/05/2017
*************************************************/

///* Import Libraries*/// 

#include <QTRSensors.h>
#include <SFE_MMA8452Q.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

#include <Servo.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>

/*************************************************
** Initialize the system, inits all Tads.
*************************************************/


void setup() {
   init_TUART();

   init_TWIFI();
 
   // init_TTemperatureSensor(); 
   
   init_TMOTOR();
    
   init_TUltrasonicSensor();
    
   // init_TAccelerometerSensor();
    
   // init_BP();

    Serial.println("Init");
    init_TServo();
    

    init_TControl ();
    
    init_ligth();
    Serial.println("Infra calib");

    init_TIRInfraRedSensor();
    Serial.println("End Infra calib");

    init_laberint ();

    motor_TUart();

    LED_ON_nas();
}

/***********************************************************
** Main loop. Add the necessary motors next to the others.
************************************************************/

void loop() { 
  
    motor_TWIFI();

    //motor_TControl();

   // motor_actualitza();

  //  motor_accelerometre();
    
    //motor_auto_mode();
  
    //motor_led_fre();
    motor_laberint_abanca();
    motor_resol_lab ();

}
