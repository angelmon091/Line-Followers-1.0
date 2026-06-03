// QTR-8A Lectura + Calibración Blanco/Negro
// Línea BLANCA (L = 1)

#define LED_NEGRO 11
#define LED_BLANCO 10

int sensorPins[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
int sensorValores[8];
int sensorValores_B[8];
int sensorValores_N[8];
int Muestras[8];
int Valor_Digital[8];

int x, y, p, plast;
int L = 1; // Línea blanca

void setup() {
  Serial.begin(115200);
  pinMode(LED_NEGRO, OUTPUT);
  pinMode(LED_BLANCO, OUTPUT);

  calibrarNegro();
  calibrarBlanco();
  calcularMuestras();
}

void loop() {
  leerSensores();
  calcularPosicion();
  Serial.print("p = ");
  Serial.println(p);
  delay(20);
}

void calibrarNegro() {
  digitalWrite(LED_NEGRO, HIGH);
  unsigned long t0 = millis();
  while (millis() - t0 < 4000) {
    for (int i = 0; i < 8; i++) {
      sensorValores_N[i] = analogRead(sensorPins[i]);
    }
  }
  digitalWrite(LED_NEGRO, LOW);
}

void calibrarBlanco() {
  digitalWrite(LED_BLANCO, HIGH);
  unsigned long t0 = millis();
  while (millis() - t0 < 4000) {
    for (int i = 0; i < 8; i++) {
      sensorValores_B[i] = analogRead(sensorPins[i]);
    }
  }
  digitalWrite(LED_BLANCO, LOW);
}

void calcularMuestras() {
  for (int i = 0; i < 8; i++) {
    Muestras[i] = (sensorValores_B[i] + sensorValores_N[i]) / 2;
  }
}

void leerSensores() {
  for (int i = 0; i < 8; i++) {
    int lectura = analogRead(sensorPins[i]);
    sensorValores[i] = lectura;

    if (L == 1) Valor_Digital[i] = (lectura < Muestras[i]) ? 1 : 0;
    else Valor_Digital[i] = (lectura < Muestras[i]) ? 0 : 1;

    Serial.print(Valor_Digital[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void calcularPosicion() {
  int pesos[8] = {1500, 1300, 1100, 900, 700, 500, 300, 100};

  x = 0;
  y = 0;

  for (int i = 0; i < 8; i++) {
    x += pesos[i] * Valor_Digital[i];
    y += Valor_Digital[i];
  }

  if (y == 0) p = -1;
  else p = x / y;

  if (plast <= 100 && p == -1) p = 0;
  if (plast >= 1400 && p == -1) p = 1500;

  plast = p;
}
