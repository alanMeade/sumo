#include <Arduino.h>
#include "movimiento.h"
#include "linea.h"
#include "sensorDist.h"
#include "main.cpp"
extern int velocidadBase=140;
const int M1INA = 9;//bajo
const int M1INB = 10;//bajo
const int M2INA = 4;
const int M2INB = 3;

void setupMotores() {
  pinMode(M1INA, OUTPUT);
  pinMode(M1INB, OUTPUT);
  pinMode(M2INA, OUTPUT);
  pinMode(M2INB, OUTPUT);
}

void avanzar(int speedFwd) {
  analogWrite(M1INA, 0);
  analogWrite(M1INB, speedFwd);

  analogWrite(M2INA, speedFwd);
  analogWrite(M2INB, 0);
}

void retroceder(unsigned long time) {
  analogWrite(M1INA, 255);
  analogWrite(M1INB, 0);

  analogWrite(M2INA, 0);
  analogWrite(M2INB, 255);
  delay(time);
}

void girar(unsigned long time, int speed) {
  analogWrite(M1INA, 0);
  analogWrite(M1INB, speed);

  analogWrite(M2INA, 0);
  analogWrite(M2INB, -speed);
  delay(time);
}

void frenar() {
  analogWrite(M1INA, 255);
  analogWrite(M1INB, 255);

  analogWrite(M2INA, 255);
  analogWrite(M2INB, 255);
  delay(40);
}

void evitarLinea(){
  if (sensorValues[0] < 50 or sensorValues[1] < 50) {
      frenar();
      retroceder(500);
      girar(300, 150);
    
    }
else{
  avanzar(velocidadBase);
}
}
/*void asesino(int &speedFwd){
  if (distanciaPresente > distanciaPasada) {
    speedFwd=constrain(speedFwd+20, 0, 255);
    avanzar(speedFwd);
  }

}
*/




void fullIn(){
  
  if (ultrasonicoFrenteCm() < 15) {
   evitarLinea();
  }
  else if (ultrasonicoDerCm() < 20) {
   girar(true, 90);
  }
 
}

void sumo(){
  while(sensorValues[0] > 50 && sensorValues[1] > 50){
    if (ultrasonicoFrenteCm() < 15) {
     avanzar(velocidadBase);
  }
  else if (ultrasonicoDerCm() < 20) {
   girar(true, 90);
  }
 
}
evitarLinea();
  }
