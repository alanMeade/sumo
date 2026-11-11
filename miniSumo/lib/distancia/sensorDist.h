#pragma once
#include <Arduino.h>

//extern float d1, d2, d3;   // cm (-1 = sin lectura válida)

// Una sola llamada en el loop: se inicializa sola y mide los 3 sensores
void ultrasonicoActualizar();

// Últimas distancias en cm (-1 si no hubo eco)
float ultrasonicoFrenteCm();
float ultrasonicoIzqCm();
float ultrasonicoDerCm();