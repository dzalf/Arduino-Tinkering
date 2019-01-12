int clk = 3;
int dt = 6;
int sw = 7;
int red = 2;
int latchPin = 8; //Pin connected to ST_CP of 74HC595
int clockPin = 12; //Pin connected to SH_CP of 74HC595
int dataPin = 11; ////Pin connected to DS of 74HC595
int flag;
int counter;
int number_pos;
int number_neg;
int pos_neg;
int array_pos[8] = {1,2,4,8,16,32,64,128};
int array_neg[8] = {127,191,223,239,247,251,253,254};
//int array_neg[8] = {254,253,223,239,247,251,253,254};
void setup(){

  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(clk,INPUT);
  pinMode(dt,INPUT);
  pinMode(sw,INPUT);
  pinMode(red,OUTPUT);
  digitalWrite(sw,HIGH);
  counter = 0;
  number_pos = 0;
  number_neg = 0;
  flag = 1;
  pos_neg = 0;
  attachInterrupt(0,handleEncoder,FALLING);  
}

void loop(){
  
  
  while (pos_neg == 0){ 
  number_pos = array_pos[counter];
 
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin,clockPin,LSBFIRST,number_pos);  
   digitalWrite(latchPin, HIGH);
   digitalWrite(red,LOW);
   
      if(digitalRead(sw) == LOW){
      flag = 0;
      debounce();
      digitalWrite(red,HIGH);
      pos_neg = 1;
    }
  }
 
  while (pos_neg == 1){ 
  number_neg = array_neg[counter];
    digitalWrite(latchPin, LOW);
   shiftOut(dataPin,clockPin,MSBFIRST,number_neg);  //Attention to MSBFIRST!!
   digitalWrite(latchPin, HIGH);
   digitalWrite(red,LOW);
   
    if(digitalRead(sw) == LOW){
      flag = 0;
      debounce();
      digitalWrite(red,HIGH);
      pos_neg = 0;
    }
  } 
  
  
 
}

void handleEncoder(){
  
  int clk_val = digitalRead(clk);
  int dt_val = digitalRead(dt);
  
  if(clk_val == LOW || dt_val == LOW ){
   flag = 0;
   debounce(); 
  if(clk_val == dt_val){
//    digitalWrite(yellow, HIGH);
//    delay(100);
//    digitalWrite(yellow,LOW); 
    counter--;
    
     if(counter < 0){
      counter = 7;
    }
  }
  else
  { 
//    digitalWrite(green, HIGH);
//   delay(100);
//    digitalWrite(green,LOW);
    counter++;
    
    if(counter > 7){
      counter = 0;
    }
  }
  }
}


void debounce(){
    while (flag == 0){
     
      if(digitalRead(clk) == HIGH && flag == 0){
      flag = 1 ;
      }
     else{
        while(digitalRead(clk) == LOW){
        flag = 0;
        }
     } 
     
     if(digitalRead(dt) == HIGH && flag == 0){
      flag = 1 ;
     }
     else{
       while(digitalRead(dt) == LOW){
        flag = 0;
        }
     } 
     
     if(digitalRead(sw) == HIGH && flag == 0){
      flag = 1 ;
     }
     else{
       while(digitalRead(sw) == LOW){
        flag = 0;
        }
     } 
          
     }
}

