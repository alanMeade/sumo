#include <Arduino.h>
#include "movimiento.h"
#include "sensorDist.h"
#include "linea.h"

 int start=0;
void setup() {
  Serial.begin(9600);
  setupMotores();
  setupLinea();
  pinMode(0, INPUT_PULLDOWN);

}

void boton() {
  if (digitalRead(0) == HIGH) {
    start=1;
  }
}

void loop() {
  ultrasonicoActualizar();
  detectarLinea();
 boton();

  if (start==1) {
    
  sumo();

 }
}