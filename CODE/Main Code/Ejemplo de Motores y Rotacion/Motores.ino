#define pwmi  3   //PWM LEFT MOTOR
#define izq1  5   //LEFT1 MOTOR
#define izq2  4   //LEFT2 MOTOR
#define pwmd  11  //PWM RIGHT MOTOR
#define der1  6   //RIGHT1 MOTOR
#define der2  7   //RIGHT2 MOTOR
void setup() {
//TCCR2B = TCCR2B & B11111000 | B00000001;
//set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz

//TCCR2B = TCCR2B & B11111000 | B00000010; 
//set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz

TCCR2B = TCCR2B & B11111000 | B00000011;   
//set timer 2 divisor to    32 for PWM frequency of   980.39 Hz

//TCCR2B = TCCR2B & B11111000 | B00000100;   
//set timer 2 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)

//TCCR2B = TCCR2B & B11111000 | B00000101;   
//set timer 2 divisor to   128 for PWM frequency of   245.10 Hz

//TCCR2B = TCCR2B & B11111000 | B00000110;   
//set timer 2 divisor to   256 for PWM frequency of   122.55 Hz

//TCCR2B = TCCR2B & B11111000 | B00000111;   
//set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz

pinMode(izq1,OUTPUT);
pinMode(izq2,OUTPUT);
pinMode(der1,OUTPUT);
pinMode(der2,OUTPUT);
}

void loop() {
motores(20,0); // motores(izq,der)
}


void motores(int izq, int der){//0 hasta 255    0 hasta -255
  ////////////////motor LEFT "IZQUIERDO" ////////////////////////
  if(izq>=0){
    digitalWrite(izq1,HIGH);
    digitalWrite(izq2,LOW);
  }
  else{
    digitalWrite(izq1,LOW);
    digitalWrite(izq2,HIGH);
    izq=izq*(-1);
  }
  analogWrite(pwmi,izq);
  
  ////////////////motor RIGHT "DERECHO" ////////////////////////
  if(der>=0){
    digitalWrite(der1,HIGH);
    digitalWrite(der2,LOW);
  }
  else{
    digitalWrite(der1,LOW);
    digitalWrite(der2,HIGH);
    der=der*(-1);
  }
  analogWrite(pwmd,der);
  
}
