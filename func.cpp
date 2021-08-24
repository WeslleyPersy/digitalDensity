#include "functions.h"

//==================================================================================
// Realiza leitura dos sensores
void sense() {
  
  #define raws 10                    // numero de leituras do sensor
  peso = scale.get_units(10);

  for (int i = raws - 1; i > 0; i--) raw[i] = raw[i - 1];
      raw[0] = distanceSensor.measureDistanceCm();
      double integer = 0x00;
      for (int i = 0; i < raws; i++)integer += raw[i];
      dist_f = (double)integer / 10;
  // implementar calc densidade
  /*
    usar tare_agua

  */
}
//==================================================================================



//==================================================================================

void cal_dist() {

  #define tara 4
  /*#define raws 10                        // numero de valores para a media
  */
  extern double valor_d;               // altura do fundo do becker ate o sensor
  char call = 0x01;                    // controle de saida do loop
  unsigned long tim = millis();        // controle de update do display
  

  lcd.setCursor(0, 0);
  lcd.print("Distancia Fundo:");


  while (call) {



    if (millis() - tim > 200) {

      sense();
      valor_d = dist_f;

      tim = millis();
      
      lcd.setCursor(0, 4);
      lcd.print(valor_d, 2);
      
      if (!digitalRead(tara)) {
        call = 0x00;
        delay(200);
      }
      
    }
  }
}

//==================================================================================



//==================================================================================

void calib() {
  
  extern double tare_agua;            // nivel de agua padrao
  char call = 0x01;                   // controle de saida do loop
  unsigned long tim = millis();       // controle de update do display
  


  lcd.clear();

  while (call) {

    if (millis() - tim > 200) {
      tim = millis();
      sense();
      float wat = dist_f;  // pega valor medio do nivel da agua

      lcd.setCursor(0, 0);
      lcd.print("V: ");
      float vol = ( valor_d - wat) * area_b;  // gera volume total (para chegar ao Th de agua)
      lcd.print(vol, 2);

      float massa = peso; // scale.get_units(10);
      
      lcd.setCursor(0, 1);
      lcd.print("m: ");
      lcd.print(massa, 2);

      if (!digitalRead(5)){
        call = 0x00;
        mC = 0x01;
        delay(200);
      }


      if (!digitalRead(tara)) {
        tare_agua = dist_f;
        m_agua = peso;
        call = 0x00;
        mC=1;
        delay(200);

      }
    }
  }
}
//==================================================================================



//==================================================================================

  void printout(){
    sense(); // gera dist_f(float) e peso(float)
    // printar: volume e massa DO OBJETO e a densidade
    
      lcd.setCursor(8, 0);
      lcd.print("V:");
      float vol = ( (tare_agua - dist_f )) * area_b; 
      lcd.print(vol, 2);
      lcd.setCursor(0, 0);

      float m_obj = peso - m_agua;
      lcd.print("m:");
      lcd.print(m_obj, 2);

      double dens = (double)m_obj/vol;
      lcd.setCursor(0, 1);
      lcd.print("D: ");
      lcd.print(dens,2);
    
    
   }



//==================================================================================



//==================================================================================
// menu seleciona a informaçao exibida
void menu(char n) {

  switch (n) {

    case 0 :
      calib();
      break;

    case 1 :

      printout();
      break;
  }// end switch()

}
//==================================================================================
