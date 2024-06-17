#include "sculptor.hpp"

int main() {
  Sculptor projeto (100, 100, 100);

  // CASA
  projeto.setColor(0.72, 0.39, 0.17, 1.0); 
  projeto.putBox(20, 50, 20, 50, 1, 30);
  projeto.setColor(0.10, 0.10, 0.10, 1.0);
  projeto.putBox(25, 35, 20, 21, 1, 20);
  projeto.putBox(40, 48, 20, 21, 14, 20);
    
  // GRAMADO
    
  projeto.setColor(0.0, 1.0, 0.0, 1.0);
  projeto.putBox(5, 85, 5, 85, 0, 1);

  // INVERSOR
  projeto.setColor(1.0, 1.0, 1.0, 0.2); 
  projeto.putBox(18, 19, 30, 36, 14, 20);
  projeto.setColor(0.0, 1.0, 0.0, 1.0);
  projeto.putBox(18, 19, 30, 36, 20, 21);
  projeto.putBox(18, 19, 30, 36, 13, 14);
  
  // MÓDULOS
  projeto.setColor(0.66, 0.65, 0.72, 1.0);
  projeto.putBox(22, 27, 22, 30, 30, 31);
  projeto.setColor(0, 0, 1, 1);
  projeto.putBox(23, 26, 23, 29, 30, 31);
  
  projeto.setColor(0.66, 0.65, 0.72, 1.0);
  projeto.putBox(29, 34, 22, 30, 30, 31);
  projeto.setColor(0, 0, 1, 1);
  projeto.putBox(30, 33, 23, 29, 30, 31);

  projeto.setColor(0.66, 0.65, 0.72, 1.0);
  projeto.putBox(36, 41, 22, 30, 30, 31);
  projeto.setColor(0, 0, 1, 1);
  projeto.putBox(37, 40, 23, 29, 30, 31);

  projeto.setColor(0.66, 0.65, 0.72, 1.0);
  projeto.putBox(43, 48, 22, 30, 30, 31);
  projeto.setColor(0, 0, 1, 1);
  projeto.putBox(44, 47, 23, 29, 30, 31);

  projeto.setColor(0.66, 0.65, 0.72, 1.0);
  projeto.putBox(22, 27, 32, 40, 30, 31);
  projeto.setColor(0, 0, 1, 1);
  projeto.putBox(23, 26, 33, 39, 30, 31);

  projeto.setColor(0.66, 0.65, 0.72, 1.0);
  projeto.putBox(29, 34, 32, 40, 30, 31);
  projeto.setColor(0, 0, 1, 1);
  projeto.putBox(30, 33, 33, 39, 30, 31);

  projeto.setColor(0.66, 0.65, 0.72, 1.0);
  projeto.putBox(36, 41, 32, 40, 30, 31);
  projeto.setColor(0, 0, 1, 1);
  projeto.putBox(37, 40, 33, 39, 30, 31);

  projeto.setColor(0.66, 0.65, 0.72, 1.0);
  projeto.putBox(43, 48, 32, 40, 30, 31);
  projeto.setColor(0, 0, 1, 1);
  projeto.putBox(44, 47, 33, 39, 30, 31);

  // SOL
  projeto.setColor(1.0, 1.0, 0.0, 1.0);
  projeto.putSphere(10,50,80,10);

  projeto.writeOFF("CASA.off");
  
  return 0;
}