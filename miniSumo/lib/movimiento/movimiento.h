#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

void setupMotores();
void avanzar();
void retroceder();
void girar(unsigned long time, int speed);
void evitarLinea(); 
//void asesino(int &speedFwd);
void fullIn();
void movimiento(int &speedFwd);
void frenar();
void sumo();

#endif