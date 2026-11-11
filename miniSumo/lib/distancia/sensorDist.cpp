#include "sensorDist.h"
/*#include <SharpDistSensor.h>

// DIST1, DIST2, DIST3 -> A9, A8, A7 (Teensy 4.0)
static const byte VENTANA = 5;   // filtro de mediana (impar)

static SharpDistSensor sensor1(A9, VENTANA);
static SharpDistSensor sensor2(A8, VENTANA);
static SharpDistSensor sensor3(A7, VENTANA);

float d1 = -1, d2 = -1, d3 = -1;

// Modelo GP2Y0A21F_5V_DS: D = 116483.4 * A^-1.13237 (A calibrado a 5 V).
// Con ADC de 3.3 V: A_lib = A * 3.3/5  ->  C' = C * (0.66)^-1.13237 ≈ 186470
static const float COEF_C = 186470.0f;
static const float COEF_P = -1.132374f;
static const uint16_t VAL_MIN = 130;    // ~0.42 V (≈ 75 cm)
static const uint16_t VAL_MAX = 1023;

static float aCm(uint16_t mm, uint16_t raw) {
  // si el valor crudo está en el límite, la medida no es confiable
  return mm / 10.0f;
}

void setupDist() {
  analogReadResolution(10);
  sensor1.setPowerFitCoeffs(COEF_C, COEF_P, VAL_MIN, VAL_MAX);
  sensor2.setPowerFitCoeffs(COEF_C, COEF_P, VAL_MIN, VAL_MAX);
  sensor3.setPowerFitCoeffs(COEF_C, COEF_P, VAL_MIN, VAL_MAX);
}

void leerDistancia() {
  d1 = sensor1.getDist() / 10.0f;   // mm -> cm
  d2 = sensor2.getDist() / 10.0f;
  d3 = sensor3.getDist() / 10.0f;
}*/

#include "sensorDist.h"

// ---- Pines ----
static const uint8_t trigUno  = 13;  // Frente
static const uint8_t echoUno  = 14;
static const uint8_t trigDos  = 15;  // Izquierda
static const uint8_t echoDos  = 16;
static const uint8_t trigTres = 17;  // Derecha
static const uint8_t echoTres = 18;

// ---- Tiempos ----
static const uint32_t PERIODO_MS = 100;  // ciclo completo de los 3 sensores
static const uint32_t ESPERA_MS  = 20;   // pausa entre sensores (evita ecos cruzados)

// ---- Estado ----
static bool iniciado = false;
static uint32_t ultimoMs = 0;

static float ultimaCmFrente = -1;
static float ultimaCmIzq    = -1;
static float ultimaCmDer    = -1;

// Medición genérica para cualquier sensor
static float medirCm(uint8_t trig, uint8_t echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duracion = pulseIn(echo, HIGH, 30000);  // timeout 30 ms
  if (duracion == 0) return -1;

  return duracion * 0.0343f / 2.0f;
}

static void iniciarPines() {
  pinMode(trigUno, OUTPUT);   pinMode(echoUno, INPUT);
  pinMode(trigDos, OUTPUT);   pinMode(echoDos, INPUT);
  pinMode(trigTres, OUTPUT);  pinMode(echoTres, INPUT);

  digitalWrite(trigUno, LOW);
  digitalWrite(trigDos, LOW);
  digitalWrite(trigTres, LOW);
}

void ultrasonicoActualizar() {
  // Inicialización automática la primera vez
  if (!iniciado) {
    iniciarPines();
    iniciado = true;
  }

  // Solo mide cada PERIODO_MS
  if (millis() - ultimoMs < PERIODO_MS) return;
  ultimoMs = millis();

  ultimaCmIzq = medirCm(trigUno, echoUno);
  delay(ESPERA_MS);
  ultimaCmDer = medirCm(trigDos, echoDos);
  delay(ESPERA_MS);
  ultimaCmFrente = medirCm(trigTres, echoTres);

  Serial.printf("Frente: %.1f cm | Izq: %.1f cm | Der: %.1f cm\n",
                ultimaCmFrente, ultimaCmIzq, ultimaCmDer);
}

extern float ultrasonicoFrenteCm() { return ultimaCmFrente; }
extern float ultrasonicoIzqCm()    { return ultimaCmIzq; }
extern float ultrasonicoDerCm()    { return ultimaCmDer; }