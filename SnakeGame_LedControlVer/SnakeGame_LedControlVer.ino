#include <LedControl.h>

//Pines
const int pinXJ = A0; //Pin del Analogico X del Joystick
const int pinYJ = A1; //Pin del Analogico Y del Joystick
const int DIN = 10; //Pin de Entrada de Datos de la Matriz
const int CS = 12; //Pin CS de la Matriz
const int CLK = 11; //Pin CL de la Matriz
const int button = 9; //Pin del Boton Pulsador
const int buzzer = 8; //Pin del Buzzer

//Variables
const int anchoP = 32; //Ancho de la pantalla
const int altoP = 8; //Alto de la pantalla
int sPosX, sPosY, cPosX, cPosY; //Posicion de la serpiente y de la comida en los ejes X e Y
int puntos = 0; //Puntuacion del jugador
int tamanioSnake = 2;//Tamaño de la serpiente
int direccion;//A que direccion va (arriba, abajo, izquierda, derecha)
int colaX[300], colaY[300];//Tamaño maximo de las cola en ambos ejes
bool isGameOver = false;//Comprobacion del gameover
LedControl lC = LedControl(DIN, CS, CLK, 1);

void setup(){
  //setPines();
  setLC();
  setSnakePos();
  setComidaPos();
}

void setSnakePos(){
  /*Esta funcion establece la posicion inicial de la serpiente*/
  sPosX = 16;
  sPosY = 4;
}

void setComidaPos(){
  /*Esta funcion genera de manera aleatoria las coordenadas de la comida*/
  cPosX = rand() % anchoP;
  cPosY = rand() % altoP;
}

void setLC(){
  /*Esta funcion setea las caracteristicas de la libreria y las setea en la matriz*/
  lC.shutdown(0, false);
  lC.setIntensity(0, 1);
  lC.clearDisplay(0);
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
  /*Esta funcion llama al resto de las funciones que permiten que hacen posible al juego*/
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
  /*Funcion que determina en que conficiones uno pierde*/
  for(int i = 1; i < tamanioSnake; i++){
    if(colaX[i] == sPosX && colaY[i] == sPosY){
      isGameOver = true;
    }
  }
}

void limitesManager(){
  /*Funcion que setea los limites*/
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
  /*Funcion que hace que la cola siga a la serpiente*/
  int XPrevio, YPrevio, antesX, antesY;
  XPrevio = colaX[0];
  YPrevio = colaY[0];
  colaX[0] = sPosX;
  colaY[0] = sPosY;
  for(int i = 1; i < tamanioSnake; i++){
    antesX = colaX[i];
    antesY = colaY[i];
    colaX[i] = XPrevio;
    colaY[i] = YPrevio;
    XPrevio = antesX;
    YPrevio = antesY;
  }
}

void comer(){
  /*Funcion que permite a la serpiente comer. Se genera una nueva comida*/
  if(sPosX == cPosX && sPosY == cPosY){
    puntos++;
    tamanioSnake++;
    setComidaPos();
  }
}

void setJoystick(){
  /*Funcion que setea al JoyStick*/
  if(analogRead(pinXJ) > 1000){
    direccion = 1;
  }
  else if(analogRead(pinXJ) < 100){
    direccion = 2;
  }
  else if(analogRead(pinYJ) > 1000){
    direccion = 3;
  }
  else if(analogRead(pinYJ) < 100){
    direccion = 4;
  }
}

void cambiarDirS(){
  /*Funcion que establece el cambio de direccion*/
  switch(direccion){
    case 1:
      sPosY--;
      break;
    case 2:
      sPosY++;
      break;
    case 3:
      sPosX--;
      break;
    case 4:
      sPosX++;
      break;
  }
}

void gameOverP(){
  /*Funcion que imprime una pantalla de game over*/
  for(int i = 0; i < altoP; i++){
    for(int j = 0; j < anchoP; j++){
      prenderLed(j, i);
      delay(300);
    }
  }
  resetVariables();
}

void resetVariables(){
  /*Funcion que resetea todas las variables para empezar un nuevo juego*/
  setSnakePos();
  setComidaPos();
  direccion = 0;
  isGameOver = false;
  puntos = 0;
  tamanioSnake = 2;
}

void prenderLed(int fila, int col){
  /*Función que prende un led. Solicita la fila y columna donde se encuentra el led como parametro*/
  lC.setLed(0, fila, col, true);
}

void apagarLed(int fila, int col){
  /*Función que apaga un led. Solicita la fila y columna donde se encuentra el led como parametro*/
  lC.setLed(0, fila, col, false);
}

void printSnake(){
  /*Funcion que imprime a la serpiente, a la comida y a la cola*/
  for(int i = 0; i < altoP; i++){
    for(int j = 0; j < anchoP; j++){
      if(i == sPosY && j == sPosX){
        prenderLed(sPosX, sPosY);
      }
      else if(i == cPosY && j == cPosX){
        prenderLed(cPosX, cPosY);
      }
      else{
        bool prendido = false;//Verifica si un led esta prendido o apagado
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
