#define LED_NEGRO 11
#define LED_BLANCO 10
#define AIN1 2
#define AIN2 12
#define PWMA 5
#define BIN1 4
#define BIN2 7
#define PWMB 6
#define STBY 9
int sensorPins[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
int sensorValores[8];
int sensorValores_B[8];
int sensorValores_N[8];
int Muestras[8];
int Valor_Digital[8];
// Posiscion 
int x, y, p, plast;
int pesos[8] = {700, 600, 500, 400, 300, 200, 100, 0};
int setpoint = 350;
// PID
int last_error = 0;
void setup() {
  Serial.begin(115200);
  pinMode(LED_NEGRO, OUTPUT);
  pinMode(LED_BLANCO, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
  motoresInit();
  //calculo de sensor negro
  digitalWrite(LED_NEGRO, HIGH);
  unsigned long t0 = millis();
  while (millis() - t0 < 3000) {
    for (int i = 0; i < 8; i++)
      sensorValores_N[i] = analogRead(sensorPins[i]);
  }
  digitalWrite(LED_NEGRO, LOW);
  delay(400);
  //calculo de sesnores en blanco
  digitalWrite(LED_BLANCO, HIGH);
  t0 = millis();
  while (millis() - t0 < 3000) {
    for (int i = 0; i < 8; i++)
      sensorValores_B[i] = analogRead(sensorPins[i]);
  }
  digitalWrite(LED_BLANCO, LOW);
  for (int i = 0; i < 8; i++)
    Muestras[i] = (sensorValores_B[i] + sensorValores_N[i]) / 2;
  Serial.println("Calibración lista – Siguiendo linea");
}
void loop() {
  leerSensores();
  calcularPosicion();
  int potencia = PID(p, 0.332, 1.095);
  int baseSpeed = 120;
  int left = baseSpeed + potencia;
  int right = baseSpeed - potencia;
  left = constrain(left, -255, 255);
  right = constrain(right, -255, 255);
  Motores(left, right);
  imprimirDatos();
  delay(10);
}
void leerSensores() {
  for (int i = 0; i < 8; i++) {
    int lectura = analogRead(sensorPins[i]);
    sensorValores[i] = lectura;
    // Línea blanca
    Valor_Digital[i] = (lectura < Muestras[i]) ? 1 : 0;
  }
}
void calcularPosicion() {
  x = 0;
  y = 0;
  for (int i = 0; i < 8; i++) {
    x += pesos[i] * Valor_Digital[i];
    y += Valor_Digital[i];
  }
  if (y == 0) p = -1;  // fuera de línea ( estamos tomando si el ultimo registro es mayo r o menor que 350 para saber por cual lado salio el carro)
  else p = x / y;
  if (plast <= 350 && p == -1) p = 0;     // izquierda
  if (plast >= 350 && p == -1) p = 700;   // derecha
  plast = p;
}
//PID( el PID es una ecuacion matematica para corregir errores de calibracion)
int PID(int pos, float Kp, float Kd) {
  int error = pos - setpoint;
  int derivative = error - last_error;
  last_error = error;
  return (error * Kp) + (derivative * Kd);
}
void motoresInit() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}
void MotorIz(int value) {
  if (value >= 0) { digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW); }
  else { digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH); value = -value; }
  analogWrite(PWMA, value);
}
void MotorDe(int value) {
  if (value >= 0) { digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW); }
  else { digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH); value = -value; }
  analogWrite(PWMB, value);
}
void Motores(int left, int right) {
  MotorIz(left);
  MotorDe(right);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////Datos serial
void imprimirDatos() {
  for (int i = 0; i < 8; i++) {
    Serial.print(Valor_Digital[i]);
    Serial.print(" ");
  }
  Serial.print(" | p="); Serial.print(p);
  Serial.print(" x="); Serial.print(x);
  Serial.print(" y="); Serial.println(y);
} 
