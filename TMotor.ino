/*************************************************
** Tad Motor: This tad allows both motor control (speed -100 to 100).
** Enginyers: Ignasi Ballarà Franco, Joaquim Porte Jimenez, Arnau Tienda Tejedo
** Date:      02/05/2017
*************************************************/

const int PIN_motor_RIGHT = 5;
const int PIN_motor_LEFT = 6;

const int sp_stop = 90;


/*const int sp_F_low = 100;
const int sp_F_med = 120;
const int sp_F_fast = 180;

const int sp_B_low = 80;
const int sp_B_med = 60;
const int sp_B_fast = 0;*/

Servo rightMotor;
Servo leftMotor;



/************************************************* Public functions *************************************************/

/*************************************************
** Pre:  --
** Post: Initialize Motors.
*************************************************/
void init_TMOTOR(){
    rightMotor.attach(PIN_motor_RIGHT);
    leftMotor.attach(PIN_motor_LEFT);
    rightMotor.write(90);
    leftMotor.write(90);
}

/*************************************************
** Pre:  --
** Post: Left motor's speed will change to the input value(-100 to 100).
*************************************************/
void set_speed_MOTOR_left(int speed2){
    leftMotor.write(speed2);
}

/*************************************************
** Pre:  --
** Post: Right motor's speed will change to the input value (-100 to 100).
*************************************************/
void set_speed_MOTOR_right(int speed2){
    rightMotor.write(speed2);
}

void FORWARD_BACK (int Speed){

    if(Speed == -1){
        set_speed_MOTOR_right (sp_B_low);
        set_speed_MOTOR_left (sp_F_low);
    }
    
    if(Speed == -2){
        set_speed_MOTOR_right (sp_B_med);
        set_speed_MOTOR_left (sp_F_med);
    }
    
    if(Speed == -3){
        set_speed_MOTOR_right (sp_B_fast);
        set_speed_MOTOR_left (sp_F_fast);
    }
    
    if(Speed == 1){
        set_speed_MOTOR_right (sp_F_low);
        set_speed_MOTOR_left (sp_B_low);
    }
    
    if(Speed == 2){
        set_speed_MOTOR_right (sp_F_med);
        set_speed_MOTOR_left (sp_B_med);
    }
    
    if(Speed == 3){
        set_speed_MOTOR_right (sp_F_fast);
        set_speed_MOTOR_left (sp_B_fast);
    }
}



// velocitat --> '3' -> 90º 1385ms
unsigned int turn_left (int angle, char Speed){
    
    float temp = 0;
    
    if(Speed == '1'){
        set_speed_MOTOR_right (90);
        set_speed_MOTOR_left (100); 
        temp = (2.580*angle)/90;
        return (int)(temp*1000);  
    }
    if(Speed == '2'){
        set_speed_MOTOR_right (90);
        set_speed_MOTOR_left (110);         
        temp = (1.630*angle)/90;
        return (int)(temp*1000);  
    }
    if(Speed == '3'){
        set_speed_MOTOR_right (90);
        set_speed_MOTOR_left (180);
        temp = (1.385*angle)/90;
        return (int)(temp*1000);  
             
    }
    return 0;
}




void man_control (char angle[2], int Speed){
    // // ang:00,mod:aut,lig:1,vel:+3,shp:0,acc:1

    
    if (Speed == 0){         
        STOP (); 
    }else{   
        if (angle[0] == '0'){
            FORWARD_BACK (Speed);
        }

        if (angle[0] == '1'){
            TOURN_right(angle[1],Speed);
        }
        if (angle[0] == '2'){
            TOURN_left(angle[1],Speed);
        }
    }
      
  
}


unsigned int turn_right (int angle, char Speed){
      float temp = 0;

        if (Speed == '1'){         
            set_speed_MOTOR_left (90);
            set_speed_MOTOR_right (80); 
            temp = (2.580*angle)/90;
            return (int)(temp*1000);                   
        }
        
        if (Speed == '2'){        
            set_speed_MOTOR_left (90);
            set_speed_MOTOR_right (70); 
            temp = (1.630 *angle)/90;
       
            return (int)(temp*1000);
        }
        
        if (Speed == '3'){
            set_speed_MOTOR_left (90);
            set_speed_MOTOR_right (0); 
            temp = (1.400*angle)/90;
 
            return (int)(temp*1000);   
        }
    
    return 0;  
}


void TOURN_right(char angle, int vel){

   if (angle == '1'){
       if (vel == 1){
           set_speed_MOTOR_left (sp_B_low);
           set_speed_MOTOR_right (sp_stop);         
       }
       if (vel == 2){
           set_speed_MOTOR_left (sp_B_med);
           set_speed_MOTOR_right (sp_stop);         
       }
       if (vel == 3){
           set_speed_MOTOR_left (sp_B_fast);
           set_speed_MOTOR_right (sp_stop);         
       }

       
       if (vel == -1){
           set_speed_MOTOR_left (sp_F_low);
           set_speed_MOTOR_right (sp_stop);         
       }
       if (vel == -2){
           set_speed_MOTOR_left (sp_F_med);
           set_speed_MOTOR_right (sp_stop);         
       }
       if (vel == -3){
           set_speed_MOTOR_left (sp_F_fast);
           set_speed_MOTOR_right (sp_stop);         
       }
   }

   
   if (angle == '2'){
       if (vel == 1){
           set_speed_MOTOR_left (sp_B_low);
           set_speed_MOTOR_right (sp_B_low);         
       }
       if (vel == 2){
           set_speed_MOTOR_left (sp_B_med);
           set_speed_MOTOR_right (sp_B_med);         
       }
       if (vel == 3){
           set_speed_MOTOR_left (sp_B_fast);
           set_speed_MOTOR_right (sp_B_fast);         
       }
       
       if (vel == -1){
           set_speed_MOTOR_left (sp_F_low);
           set_speed_MOTOR_right (sp_F_low);         
       }
       if (vel == -2){
           set_speed_MOTOR_left (sp_F_med);
           set_speed_MOTOR_right (sp_F_med);         
       }
       if (vel == -3){
           set_speed_MOTOR_left (sp_F_fast);
           set_speed_MOTOR_right (sp_F_fast);         
       }
   }
}


void TOURN_left(char angle, int vel){

   if (angle == '1'){
       if (vel == 1){
           set_speed_MOTOR_left (sp_stop);
           set_speed_MOTOR_right (sp_F_low);         
       }
       if (vel == 2){
           set_speed_MOTOR_left (sp_stop);
           set_speed_MOTOR_right (sp_F_med);         
       }
       if (vel == 3){
           set_speed_MOTOR_left (sp_stop);
           set_speed_MOTOR_right (sp_F_fast);         
       }

       
       if (vel == -1){
           set_speed_MOTOR_left (sp_stop);
           set_speed_MOTOR_right (sp_B_low);         
       }
       if (vel == -2){
           set_speed_MOTOR_left (sp_stop);
           set_speed_MOTOR_right (sp_B_med);         
       }
       if (vel == -3){
           set_speed_MOTOR_left (sp_stop);
           set_speed_MOTOR_right (sp_B_fast);         
       }
 
   }

   
   if (angle == '2'){
       if (vel == 1){
           set_speed_MOTOR_left (sp_F_low);
           set_speed_MOTOR_right (sp_F_low);         
       }
       if (vel == 2){
           set_speed_MOTOR_left (sp_F_med);
           set_speed_MOTOR_right (sp_F_med);         
       }
       if (vel == 3){
           set_speed_MOTOR_left (sp_F_fast);
           set_speed_MOTOR_right (sp_F_fast);         
       }
       
       if (vel == -1){
           set_speed_MOTOR_left (sp_B_low);
           set_speed_MOTOR_right (sp_B_low);         
       }
       if (vel == -2){
           set_speed_MOTOR_left (sp_B_med);
           set_speed_MOTOR_right (sp_B_med);         
       }
       if (vel == -3){
           set_speed_MOTOR_left (sp_B_fast);
           set_speed_MOTOR_right (sp_B_fast);         
       }
   }
}


void STOP (){
   set_speed_MOTOR_left (sp_stop);
   set_speed_MOTOR_right (sp_stop);
}




