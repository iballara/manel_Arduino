/*************************************************
** Tad Control: This Tad, allows have the control over all others Tads system and motors.
** Enginyers:  Ignasi Ballarà Franco, Joaquim Porte Jimenez, Arnau Tienda Tejedo
** Date:       02/05/2017
*************************************************/

/* Constants*/
const char BP_left_sleep = 3;
const char BP_right_sleep = 4;

int state_fre = 0;
unsigned long milis_fre = 0;

const char ULT_sleep = 5;

const char BP_left = 0;
const char BP_right = 1;
const char ULT = 2;

const int INIT_RODONA = 100;
const int FOW_RODONA = 101;
const int TURN_RODONA = 102;
const int STOP_RODONA = 103;


const int INIT_TRIANGLE = 104;
const int FOW_TRIANGLE = 105;
const int TURN_TRIANGLE = 106;
const int STOP_TRIANGLE = 107;


const int INIT_SQ = 108;
const int FOW_SQ = 109;
const int TURN_SQ = 110;
const int STOP_SQ = 111;

const int sp_F_low = 100;
const int sp_F_med = 110;
const int sp_F_fast = 180;

const int sp_B_low = 80;
const int sp_B_med = 70;
const int sp_B_fast = 0;
const int AUTO_MODE_RUN = 99;
const int AUTO_MODE_SLEEP = 0;
const int AUTO_MODE_TURN = 98;

const int SEARCH_ACCEL_2 = 999;
const int PLA_ACCEL = 69;
const int INIT_ACCEL = 5;
const int SEARCH_ACCEL = 6;
const int START_ACCEL = 10;
const int FIN_ACCEL = 7;
const int SLOW_SPEED = 1;
const int accel_x = 0;
const int accel_y = 1;
const int accel_z = 2;

/*Variables*/
int state_accel = INIT_ACCEL;
char BP_left_ant = 0;
char BP_right_ant = 0;
char BP_ULT_ant = 0;
int  llum_on = 0;
int start_accel_mode = 0;
int start_auto_mode = 0;
unsigned long control_rebot = 0;
unsigned long Millis_aut = 0;
int state_act = 0;
char mode = 'm';
char ang[2];
char lig = 0;
int  vel = 0;
char shp = '0';
int marxa_anterior = 0;
char acc = 0;
int pl = 0;
int triangle = 0;
int quadrat = 0;
int rodona = 0;
int estat_led = 0;
unsigned long  Millis_led  = 0;
int led_on = 0;
int state_Control = INIT_ACCEL;
char *trama;
float temperature = 0.00;

char send_control_Data[255];
// Pins LED configuration.
float *data_accel;
unsigned long Millis = 0; 
unsigned long Millis_fi = 0;
unsigned int temp = 0;

char angle[4];
/************************************************* Private functions *************************************************/

void switch_scenario(char *scenario) {
    
    // Prioritat a la proba del accel.
    if (acc == '1'){
        state_Control = 0;
        start_accel_mode = 1;
        pl = 0;
    }else{
        start_accel_mode = 0;
        if (shp != '0' && mode != 'a'){
            rodona = 0;
            triangle = 0;
            quadrat = 0;
            if (shp == 'T'){
                 state_Control = INIT_TRIANGLE;
            }
            if (shp == 'C'){
                state_Control = INIT_RODONA;
            }
            if (shp == 'S'){
                state_Control = INIT_SQ;
            }
            
        }else{
      
            if (mode == 'm'){
                start_auto_mode = 0;
                man_control (ang,vel);
            }else{
                start_auto_mode = 1;
            }
            
            state_Control = 0;
        }     
    }

}

/************************************************* Public functions *************************************************/

/*************************************************
** Pre:  Others Tads initialized.
** Post: Tad control initialized.
*************************************************/
// mod:aut,ang:00,lig:1,vel:+3,shp:0,acc:1

void getDadesTramaWifi(){
    char vel2[3];
    
    mode = trama[11];
    
    ang[0] = trama[4];
    ang[1] = trama[5];
    lig = trama[19];
    
    if(lig == '1'){
      LEDS_ON_fron();
    }else{
      LEDS_OFF_fron();
    }   

    
    
    vel2[0] = trama[25];
    vel2[1] = trama[26];
    vel2[2] = '\0';
    vel = atoi(vel2); 
    if ((vel >= 0 && marxa_anterior > vel) || (vel <= 0 && marxa_anterior < vel)){
        llum_on = 1;
    }else{
        llum_on = 0;
    }
    marxa_anterior = vel;
    shp = trama[32];
    acc = trama[38];
}


void init_TControl () {
  state_Control = 0;
  BP_left_ant = get_left_bp();
  BP_right_ant = get_right_bp();
  BP_ULT_ant = readUltrasound();
}

void motor_TControl() {
  
  switch (state_Control) {  
    case 0:
        if (getnewData_wifi() == 1) {
          trama = getData_wifi();
          state_Control = 1;
        }
        break;
      
    case 1:
      getDadesTramaWifi();
      switch_scenario (trama);
      break;

 
///////////////////////////////////
// Rodona


    case INIT_RODONA:
      Millis = millis();
      FORWARD_BACK (3);
      state_Control = FOW_RODONA;

      break;
      
    case FOW_RODONA:
        if(millis() > Millis + 100){
            rodona = rodona + 1;
            state_Control = TURN_RODONA;        
        }
      break;
    case TURN_RODONA:
      Millis = millis();
      led_on = 1;
      temp = turn_right(10,'3');
    
      state_Control = STOP_RODONA;

      break;
      
    case STOP_RODONA:
      if(millis() > Millis + temp){
          if (rodona == 35){
                STOP();
                rodona = 0;
                state_Control = 0;
            }else{       
                state_Control = INIT_RODONA;
            }
      }
      break;
    // Cuadrat

    
    case INIT_SQ:
        Millis = millis();
        FORWARD_BACK (3);
        state_Control = FOW_SQ;
  
        break;
    case FOW_SQ:
        if(millis() > Millis + 2000){
            quadrat = quadrat + 1;
            state_Control = TURN_SQ;        
        }
      break;
    case TURN_SQ:
        Millis = millis();      
        temp = turn_right(90,'3');
        led_on = 1;
  
        state_Control = STOP_SQ;
    break;
    case STOP_SQ:
        if(millis() > Millis  + temp){
           if (quadrat == 4){
                STOP();
                quadrat = 0;
                state_Control = 0;
            }else{
                state_Control = INIT_SQ;  
            }
        }
     
        break;
    // Triangle FIGURE
    
    case INIT_TRIANGLE:
      Millis = millis();
      FORWARD_BACK (3);
      state_Control = FOW_TRIANGLE;

      break;
      
    case FOW_TRIANGLE:
        if(millis() > Millis + 2000){
            triangle = triangle + 1;
            state_Control = TURN_TRIANGLE;        
        }
      break;
    case TURN_TRIANGLE:
      Millis = millis();
      led_on = 1;
      temp = turn_right(120,'3');
    
      state_Control = STOP_TRIANGLE;

      break;
      
    case STOP_TRIANGLE:
      if(millis() > Millis + temp){
          if (triangle == 3){
                STOP();
                triangle = 0;
                state_Control = 0;
            }else{       
                state_Control = INIT_TRIANGLE;
            }
      }
     
      break;
    }
}

void motor_actualitza(){
  
    switch (state_act){
        case BP_left:
            if (get_left_bp() != BP_left_ant){
                BP_left_ant = get_left_bp();
                trama_app();
                control_rebot = millis();
                state_act = BP_left_sleep;
            }else{
                state_act = BP_right;
            }
            break;
        case BP_left_sleep:

             if (millis () >control_rebot + 300){
                 state_act = BP_right;
             }
             break;
        
        case BP_right:
            if (get_right_bp() != BP_right_ant){
                BP_right_ant = get_right_bp();
                trama_app();
                control_rebot = millis();
                state_act = BP_right_sleep;
                
            }else{
                state_act = ULT;
            }
            break;      
        case BP_right_sleep:

             if (millis () > control_rebot + 300){
                 state_act = ULT;
             }
             break;
        case ULT:
            if (readUltrasound() != BP_ULT_ant){
                BP_ULT_ant = readUltrasound();
                trama_app();
                control_rebot = millis();
                state_act = ULT_sleep;
                
            }else{
                state_act = BP_left;
            }
            break;

        case ULT_sleep:

             if (millis () >control_rebot + 300){
                 state_act = BP_left;
             }
             break;
    }
}  

int state_auto = 0;

void motor_auto_mode(){
    switch (state_auto){
        case AUTO_MODE_SLEEP:
            if (start_auto_mode == 1){
                state_auto = AUTO_MODE_RUN;
                FORWARD_BACK (2);
            }
            break;
       case AUTO_MODE_RUN:
            if (readUltrasound() == 1){
                temp = turn_right(90,'3');
                llum_on = 1;

                Millis_aut = millis();
                state_auto = 111;
            }else{
                state_auto = AUTO_MODE_TURN;
            }
            if (start_auto_mode == 0){
                state_auto = AUTO_MODE_SLEEP;
                STOP();         
            }
            break;
            
       case AUTO_MODE_TURN:
            if (readUltrasound() == 0){
                FORWARD_BACK (2);
            }   
            state_auto = AUTO_MODE_RUN;

            if (start_auto_mode == 0){
                state_auto = AUTO_MODE_SLEEP;
                STOP();         
            }
            break;

       case 111:
           if (millis() > Millis_aut + temp){
                Millis_aut = millis();
                state_auto = AUTO_MODE_TURN;
            } 
            
            break;
       
    }
  
}

void motor_accelerometre(){
    
    switch (state_accel){
        
        case INIT_ACCEL:
          if (start_accel_mode == 1){
              state_accel = START_ACCEL;
          }
          delay(50);

          break;
        case START_ACCEL:  
          data_accel = readAccelerometer();
          if (data_accel[accel_y] > -0.05 && data_accel[accel_y] < 0.05 && data_accel[accel_x] < 0.00 ){
              TOURN_right('1',2);            
          }
          // Gira dreta;
          state_accel = SEARCH_ACCEL;

          break;         
          
        case SEARCH_ACCEL:
          data_accel = readAccelerometer();
          if (data_accel[accel_y] <= -0.05){
              TOURN_right('1',2);
              llum_on = 1;
          }
          
          data_accel = readAccelerometer();

          state_accel = SEARCH_ACCEL_2;

          break;
          
        case SEARCH_ACCEL_2:
          data_accel = readAccelerometer();
          if (data_accel[accel_y] >= 0.05){
              TOURN_left('1',2);
          }
          
          data_accel = readAccelerometer();

          state_accel = PLA_ACCEL;

          break;
        case PLA_ACCEL:
          data_accel = readAccelerometer();
          if (data_accel[accel_y] > -0.14 && data_accel[accel_y] < 0.14 && data_accel[accel_x] > -0.20 && data_accel[accel_x] < 0.20){
              STOP();
          }
          state_accel = FIN_ACCEL;
          break;
        case FIN_ACCEL:
          data_accel = readAccelerometer();
          
          if (data_accel[accel_y] > -0.07 && data_accel[accel_y] < 0.07 && data_accel[accel_x] > 0.10){
              FORWARD_BACK(2);
          }
          state_accel = INIT_ACCEL;
          break;
    }
}

void motor_led_fre(){
    switch(state_fre){
        case 0:
            LEDS_off_frena();
            if (llum_on == 1){
                state_fre = 1;  
                LEDS_ON_frena();
                milis_fre = millis();
            }
            break;

        case 1:
            if (millis () > milis_fre + 500){
                state_fre = 0;  
                LEDS_off_frena();  
                llum_on = 0;           
            }
            break;
    }
  
}
