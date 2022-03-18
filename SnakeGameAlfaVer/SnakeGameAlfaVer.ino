#include <MD_MAX72xx.h>
#include <SPI.h>

//Pines
const int pinXJ = A0;
const int pinYJ = A1;
const int DIN;
const int CS;
const int CLK;
const int button;
const int buzzer;

//Variables
const int anchoP = 32;
const int altoP = 8;
int sPosX, sPosY, cPosX, cPosY;
int puntos = 0;
int tamanioSnake = 2;
String direccion;
int colaX[300], colaY[300];
bool isGameOver = false;
MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::GENERIC_HW, DIN, CLK, CS, 4);

void setup(){
  //setPines();
  setMatriz();
  setSnakePos();
  setComidaPos();
}

void setSnakePos(){
  sPosX = 16;
  sPosY = 4;
}

void setComidaPos(){
  cPosX = rand() % anchoP;
  cPosY = rand() % altoP;
}

void setMatriz(){
  mx.control(MD_MAX72XX::SHUTDOWN, false);
  mx.control(MD_MAX72XX::INTENSITY, 8);
}

void loop(){
  if(isGameOver == true) {
    gameOverP();
  }
  else{
    jugar();
  }
}

void jugar(){
  gameOverManager();
  setJoystick();
  cambiarDirS();
  limitesManager();
  comer();
  coordinarCola();
  printSnake();
  delay(500);
}

void gameOverManager(){
  for(int i = 1; i < snakeSize; i++){
    if(colaX[i] == sPosX && colaY == sPosY){
      isGameOver = true;
    }
  }
}

void limitesManager(){
  if(sPosX >= anchoP){
    sPosX = 0;
  }else if(sPosX < 0){
    sPosX = anchoP - 1;
  }

  if(sPosY >= altoP){
    sPosY = 0;
  }else if(sPosY < 0){
    sPosY = altoP - 1;
  }
}

void coordinarCola(){
  int XPrevio, YPrevio, antesX, antesY;
  Xprevio = colaX[0];
  Yprevio = colaY[0];
  colaX[0] = sPosX;
  colaY[0] = sPosY;
  for(int i = 1; i < tamanioSnake; i++){
    antesX = colaX[i];
    antesY = colaY[i];
    colaX[i] = Xprevio;
    colaY[i] = Yprevio;
    Xprevio = antesX;
    Yprevio = antesY;
  }
}

void comer(){
  if(sPosX == cPosX && sPosY == cPosY){
    puntos++;
    tamanioSnake++;
    setComidaPos();
  }
}

void setJoystick(){
  if(analogRead(pinXJ) > 1000){
    direccion = "Arriba";
  }
  else if(analogRead(pinXJ) < 100){
    direccion = "Abajo";
  }
  else if(analogRead(pinYJ) > 1000){
    direccion = "Izquierda";
  }
  else if(analogRead(pinYJ) < 100){
    direccion = "Derecha";
  }
}

void cambiarDirS(){
  switch(direccion){
    case "Arriba":
      sPosY--;
      break;
    case "Abajo":
      sPosY++;
      break;
    case "Izquierda":
      sPosX--;
      break;
    case "Derecha":
      sPosX++;
      break;
  }
}

void gameOverP(){
  for(int i = 0; i < altoP; i++){
    for(int j = 0; j < anchoP; j++){
      prenderLed(j, i);
      delay(300);
    }
  }
  resetVariables();
}

void resetVariables(){
  setSnakePos();
  setComidaPos();
  direccion = "";
  isGameOver = false;
  puntos = 0;
  tamanioSnake = 2;
}

void prenderLed(int fila, int col){
  mx.setPoint(fila, col, true);
}

void apagarLed(int fila, int col){
  mx.setPoint(fila, col, false);
}

void printSnake(){
  for(int i = 0; i < altoP; i++){
    for(int j = 0; j < anchoP; j++){
      if(i == sPosY && j == sPosX){
        prenderLed(sPosX, sPosY);
      }
      else if(i == cPosY && j == cPosX){
        prenderLed(cPosX, cPosY);
      }
      else{
        bool prendido = false;
        for(int k = 0; k < tamanioSnake; k++){
          if(colaX[k] == j && colaY[k] == i){
            prenderLed(j, i);
            prendido = true;
          }
        }
        if(!prendido){
          apagarLed(j, i);
        }
      }
    }
  }
}

void spawnMuros(){
  mx.setPoint(3, 3, true);
  mx.setPoint(3, 4, true);
  mx.setPoint(4, 3, true);
  mx.setPoint(4, 4, true);

  mx.setPoint(3, 11, true);
  mx.setPoint(3, 12, true);
  mx.setPoint(4, 11, true);
  mx.setPoint(4, 12, true);

  mx.setPoint(3, 19, true);
  mx.setPoint(3, 20, true);
  mx.setPoint(4, 19, true);
  mx.setPoint(4, 20, true);
  
  mx.setPoint(3, 27, true);
  mx.setPoint(3, 28, true);
  mx.setPoint(4, 27, true);
  mx.setPoint(4, 28, true);
}
