int state_laberint = 0;
bool *sensorValues_2;
int init_lab = 0;
int possicio[2];
int i1 = 0;
int e1 = 0;
int possicio_ant[2];
char dd[255];
char dd2[255];
int orientacio_guarda = 0;
int state_sol = 0;

int init_solv = 0;
int x_lab = 0;
int y_lab = 0;
int orientacio_ant = 1; // 0 (0º), 1 (90º -> la inicial), 2 (180º), 3 (270º);
int orientacio = 1;

int direccio_ant = 1; // 0 (R), 1 (F), 2 (L), 3 (B);
int direccio = 1;

int right_mov = 0;
int front_mov = 0;
int left_mov = 0;
int oth_mov = 0;

typedef struct 
   {   
       int passat; 
       int bonna;   
       int orientacio;
       int direccio;
       int next_posicio[2];  
   }Casella;


Casella laberint[5][5];

void init_laberint (){
    int i = 0;
    int e = 0;

    getinfraRed(sensorValues_2);
    init_lab = 1; 
    state_sol = 0;
    state_laberint = 1; 
    possicio[0] = 0;
    possicio[1] = 0;
    possicio_ant[0] = 0;
    possicio_ant[1] = 0; 
    while (i < 5){
        e = 0;
        while (e < 5){
            laberint[i][e].passat = 0;
            laberint[i][e].bonna = 0;
            laberint[0][0].orientacio = 1;
            laberint[0][0].direccio = 1;
            laberint[0][0].next_posicio[0] = 0;
            laberint[0][0].next_posicio[1] = 0;
            e++;
        }
        i++;
    }
    
}

void motor_laberint_abanca(){
    
    switch (state_laberint){
    
        case 0:
            if (init_lab == 1){
                state_laberint = 1;                
            }         
            
            break;

        case 1:
            getinfraRed(sensorValues_2);                           

            if ((sensorValues3[2] & sensorValues3[3]  & !sensorValues3[0] & true)  == true){
                  FORWARD_BACK (2); 
  

            }

            state_laberint = 2;      
            break;
                           
        case 2:
        
            getinfraRed(sensorValues_2);
            if ((sensorValues3[0] | sensorValues3[1]) & true){
                TOURN_left('1',2); 
            }
            state_laberint = 3;      
                
            break;
                
        case 3: 
        
            getinfraRed(sensorValues_2);               
            if ((sensorValues3[4] | sensorValues3[5]) & true){
                TOURN_right('1',2);          
            }
            state_laberint = 4;      
                
            break;
                
        case 4:
        
            getinfraRed(sensorValues_2);                
            if ((sensorValues3[0] & sensorValues3[1] & sensorValues3[2] & sensorValues3[3] &sensorValues3[4] & sensorValues3[5]) & true){
                
                STOP();                
                state_laberint = 5;
                if (possicio[0] == 4 && possicio[1] == 4){
                    state_laberint = 10;
                }
                
            }else{
                state_laberint = 1;
            }
                
            break;   
        case 5:
              switch_dir();
              break;
        case 6:
            getinfraRed(sensorValues_2);                           
            if ((sensorValues3[5]) & true  == true){
                state_laberint = 9; 
                
                set_servo_forw ();
              
            }else{
                state_laberint = 6;      
            }
            
            break;
      case 7:
            getinfraRed(sensorValues_2);                           
            if ((sensorValues3[1]) & true  == true){
                state_laberint = 9;
                set_servo_forw ();
               
            }else{
                state_laberint = 7;      
            }
            
            break;
      case 8:
            getinfraRed(sensorValues_2);                           
            if ((sensorValues3[2] & sensorValues3[3]  & !sensorValues3[0] & true)  == true){
                state_laberint = 9;
                set_servo_forw ();
               
            }else{
                state_laberint = 8;      
            }
            
            break;
       case 9:                           
          
          
          possicio_ant[0] = possicio[0];
          possicio_ant[1] = possicio[1];     

          switch (orientacio_ant){
            
              case 0:
                  if (right_mov == 1){
                      possicio[0]--;          
                  }
                  if (front_mov == 1){
                      possicio[1]++;
                  }
                  if (left_mov == 1){
                      possicio[0]++;
                  }
                  if (oth_mov == 1){
                      possicio[1]--;                   
                  }
                  
                  break;
              case 1:
                  
                  if (right_mov == 1){
                      possicio[1]++;                 
                  }
                  if (front_mov == 1){
                      possicio[0]++;
                  }
                  if (left_mov == 1){
                      possicio[1]--;
                  }
                  if (oth_mov == 1){
                      possicio[0]--;
                  }
                  break;
              case 2:             
                  if (right_mov == 1){
                      possicio[0]++;
                  }
                  if (front_mov == 1){
                      possicio[1]--;
                  }
                  if (left_mov == 1){
                      possicio[0]--;
                  }
                  if (oth_mov == 1){
                      possicio[1]++;
                  }
                  break;
                  
              case 3:                 
                  if (right_mov == 1){
                      possicio[1]--;
                  }
                  if (front_mov == 1){
                      possicio[0]--;
                  }
                  if (left_mov == 1){
                      possicio[1]++;
                  }
                  if (oth_mov == 1){
                      possicio[0]++;
                  }
                  break;
          }

          laberint[possicio_ant[0]][possicio_ant[1]].passat = 1;         

          if (laberint[possicio[0]][possicio[1]].passat == 1){
            
              laberint[possicio_ant[0]][possicio_ant[1]].bonna = 0; 
                           
          }else{
            
              laberint[possicio_ant[0]][possicio_ant[1]].bonna = 1;                
              laberint[possicio_ant[0]][possicio_ant[1]].orientacio = orientacio_ant;
              laberint[possicio_ant[0]][possicio_ant[1]].direccio = direccio_ant;
              laberint[possicio_ant[0]][possicio_ant[1]].next_posicio[0] = possicio[0];
              laberint[possicio_ant[0]][possicio_ant[1]].next_posicio[1] = possicio[1];   
           
          }
          orientacio_ant = orientacio_ant + orientacio;
          
          
          if (orientacio_ant == -2){
              orientacio_ant = 2;
          }else{
              if (orientacio_ant == 5){
                  orientacio_ant = 1;
              }else{
                  if (orientacio_ant == 4){
                      orientacio_ant = 0;
                  }
              }
          }
          if (orientacio_ant == -1){
              orientacio_ant = 3;  
          }   

          
          //send_data_wifi(dd);

          direccio_ant = direccio;

          state_laberint = 1;

          break;
          
          case 10:
              // END LABERINT
              laberint[possicio_ant[0]][possicio_ant[1]].next_posicio[0] = 4;
              laberint[possicio_ant[0]][possicio_ant[1]].next_posicio[1] = 4;      
              
              laberint[possicio_ant[0]][possicio_ant[1]].bonna = 1;      
              STOP (); 
              i1 = 0;

              strcpy (dd,'\0');

              while (i1 < 5){
                  e1 = 0;
                 strcpy (dd2,'\0');
            
                  while (e1 < 5){
                      sprintf(dd2,"%d%d ",laberint[i1][e1].next_posicio[0],laberint[i1][e1].next_posicio[1]);
                      

                      strcat (dd,dd2);
                      e1++;
                  }
                  sprintf(dd2," ");
                  strcat (dd,dd2);

                  i1++;
              }
              send_data_wifi(dd);

              state_laberint = 11;
              
              break;  

              case 11:
                  possicio[0] = 0; 
                  possicio[1] = 0;
                  delay(5000);
                  orientacio_ant = 1;
                  init_solv = 1;
                  state_laberint = 12;

                  break;

              case 12:
                  break;
    }   
}



void motor_resol_lab (){
    switch (state_sol){
        case 0:
            if (init_solv == 1){
                state_sol = 1;
                possicio[0] = 0;
                possicio[1] = 0;
            }
            break;
       case 1:
                if (possicio[0] == 4 && possicio[1] == 4){
                    STOP();
                    state_sol = 6;
                }else{
                
                    if (laberint[possicio[0]][possicio[1]].next_posicio[0] > possicio[0]){                    
                        switch (orientacio_ant){
                           case 0:                
                                tourn_left();
                                break;
                            case 1:
                                mov_front();
                                break;
                            case 2:
                                mov_right();
                                break;                   
                            case 3:
                                turn_half();
                                break;  
                        
                        }
                        
                        
                    }
                    if (laberint[possicio[0]][possicio[1]].next_posicio[0] < possicio[0]){                    
                        switch (orientacio_ant){
                           case 0:                
                                mov_right();
                                break;
                            case 1:
                                turn_half();
                                break;
                            case 2:
                                tourn_left();
                                break;     
                             case 3:
                                mov_front();
                                break;     
                            
                          }
                
                    }
    
                    if (laberint[possicio[0]][possicio[1]].next_posicio[1] > possicio[1]){
     
                        switch (orientacio_ant){
                           case 0:                
                                mov_front();
                                break;
                            case 1:
                                mov_right();
                                break;
                            case 2:
                                turn_half();
                                break;                                
                            case 3:
                                tourn_left();
                                break;                   
                        }
                                             
                    }
               if (laberint[possicio[0]][possicio[1]].next_posicio[1] < possicio[1]){
                    
                        switch (orientacio_ant){
                           case 0:                
                                turn_half();
                                break;
                            case 1:
                                tourn_left();
                                break;
                            case 2:
                                mov_front();
                                break;  
                            case 3:
                                mov_right();
                                break;  
                                                     
                        }
                    }
              orientacio_ant = orientacio_ant + orientacio;
              
              
              if (orientacio_ant == -2){
                  orientacio_ant = 2;
              }else{
                  if (orientacio_ant == 5){
                      orientacio_ant = 1;
                  }else{
                      if (orientacio_ant == 4){
                          orientacio_ant = 0;
                      }
                  }
              }
              if (orientacio_ant == -1){
                  orientacio_ant = 3;  
              }   

                
                y_lab = laberint[possicio[0]][possicio[1]].next_posicio[0];
                x_lab = laberint[possicio[0]][possicio[1]].next_posicio[1];
                possicio[0] = y_lab;
                possicio[1] = x_lab;
                
                        state_sol = 2;
                    
            } 
            break;

        case 2:
            getinfraRed(sensorValues_2);                           

            if ((sensorValues3[2] & sensorValues3[3]  & !sensorValues3[0] & true)  == true){
                  FORWARD_BACK (2); 
            }

            state_sol = 3;      
            break;
                           
        case 3:
        
            getinfraRed(sensorValues_2);
            if ((sensorValues3[0] | sensorValues3[1]) & true){
                TOURN_left('1',2); 
            }
            state_sol = 4;      
                
            break;
                
        case 4: 
        
            getinfraRed(sensorValues_2);               
            if ((sensorValues3[4] | sensorValues3[5]) & true){
                TOURN_right('1',2);          
            }
            state_sol = 5;      
                
            break;
                
        case 5:
        
            getinfraRed(sensorValues_2);                
            if ((sensorValues3[0] & sensorValues3[1] & sensorValues3[2] & sensorValues3[3] &sensorValues3[4] & sensorValues3[5]) & true){
                
                STOP();
                delay(100);                
                state_sol = 1;
                if (possicio[0] == 4 && possicio[1] == 4){
                    state_sol = 6;
                }
                
            }else{
                state_sol = 2;
            }
                
            break;   
        
      
    }
}


void tourn_left (){
    right_mov = 0;
    front_mov = 0;
    left_mov = 1;
    direccio = 2;
    oth_mov = 0;                          
    orientacio = 1;
    
    FORWARD_BACK (2);   
    delay(400);
    TOURN_left ('2',2);
    delay(700);                      
}

void mov_right(){
    orientacio = -1;
    direccio = 0;
    right_mov = 1;
    front_mov = 0;
    left_mov = 0;
    oth_mov = 0;                   
    FORWARD_BACK (2);   
    delay(400);
    TOURN_right ('2',2);
    delay(600);              
}

void mov_front(){
    right_mov = 0;
    front_mov = 1;
    direccio = 1;
    left_mov = 0;
    oth_mov = 0;  
    orientacio = 0;
    FORWARD_BACK (2);   
    delay(600);       

}


void turn_half (){
    right_mov = 0;
    front_mov = 0;
    orientacio = 2;
    direccio = 3;
    left_mov = 0;
    oth_mov = 1;                            
    set_servo_forw ();
    TOURN_left ('2',2);
    delay(500);                      
}

void switch_dir(){
                set_servo_right ();
                delay(400);
                // Dreta
                if (readUltrasound() != 1 && !(possicio[0] == 0 && orientacio_ant == 0) && !(possicio[1] == 4 && orientacio_ant == 1) && !(possicio[0] == 4 && orientacio_ant == 2) && !(possicio[1] == 0 && orientacio_ant == 3)){
                    mov_right();  
                    state_laberint = 6;      
                
                }else{
                    set_servo_forw ();
                    delay(300);
                    // Recte
                    
                    if ((readUltrasound() != 1) && !(possicio[0] == 4 && orientacio_ant == 1)&&!(possicio[0] == 0 && orientacio_ant == 3) && !(possicio[1] == 4 && orientacio_ant == 0) && !(possicio[0] == 4 && possicio[1] == 0 && orientacio_ant == 2)  && !(possicio[0] == 0 && possicio[1] == 0 && orientacio_ant == 3)){
                        mov_front();
                        state_laberint = 9;
          
                    }else{    
                      
                       set_servo_left ();
                       delay(300);         
                       
                       if (readUltrasound() != 1 && !(possicio[0] == 0 && orientacio_ant == 2) && !(possicio[1] == 4 && orientacio_ant == 3) && !(possicio[0] == 4 && orientacio_ant == 0)){
                          tourn_left();
                          state_laberint = 7;      
  
                      //Mitja volta
                      }else{
                          turn_half();
                          state_laberint = 8;      
  
                      }

                  }
              
              }
}

