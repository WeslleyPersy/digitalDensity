
/*

  Engenharia Eletrônica 2020/1
  
  Data 21/07/21 Disciplina: Física II
    
  Projeto Densímetro Digital

  Grupo: Weslley Pereira,  Lucas Erlo, Sérgio Henrique 
  
 ** POSICIONAR O BECKER VAZIO ANTES DE LIGAR **



*/



//==================================================================================
//  ---  Bibliotecas ---
  #include "functions.h"
//#include <LiquidCrystal_I2C.h>  // lib lcd 16x2
//#include <HCSR04.h>         // lib sensor ultrassonico
//#include "HX711.h"          // lib sensor de carga
//   ** TODAS AS LIBS SAO CHAMADAS NO HEADER **
//==================================================================================



//==================================================================================
// --- objetos --- 

  LiquidCrystal_I2C lcd(0x27,16,2);       //
  HX711 scale;                                   // objeto do sensor de carga
  UltraSonicDistanceSensor distanceSensor(7, 6);
//==================================================================================



//==================================================================================
// --- botoes e entradas ---

  #define menus_m 0x05     // botao +  no pino 5
  #define tara 0x04        // botao de tara no pino 6

  const int LOADCELL_DOUT_PIN = 3;  // pinos comunicação do sensor de carga
  const int LOADCELL_SCK_PIN  = 2;

//=================================================================================



//==================================================================================
// --- variaveis --- 
  const float area_b = 86.29; // area circular do becker
  char mC = 0x01;             // seleciona o menu atual
  unsigned long times;        // controla a leitura do botao

  float dist_f;               // marca a altura dinâmica do liquido 
  float peso;                 // marca a massa dinâmica

  double valor_d;             // altura do sensor em relacao ao fundo do becker
  double tare_agua;           // nivel de agua padrao(threshold)
  double m_agua;              // valor de threshold massa de agua

  #define raws 10             // numero de leituras para media da distancia 
  double raw[10];             // vetor de distancias
                  
//==================================================================================




void setup() {
  
//==================================================================================
// --- pinos --- 
  pinMode(menus_m,INPUT_PULLUP); // pino de botao como entrada
  pinMode(tara,INPUT_PULLUP);    // pino de tara como entrada
    
//==================================================================================



//==================================================================================
// --- sensor de carga ---   
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); // inicializa HX711
  scale.set_scale(478.91);  // escala de calibração do sensor de carga                    
  scale.tare();             // gera a tara ao ligar o circuito

  lcd.init();
  lcd.setBacklight(HIGH);
  lcd.setCursor(3, 0);
  lcd.print("DENSIMETRO");
  delay(8000);
  times = millis();
  cal_dist();
  calib();
}

  


//==================================================================================



//==================================================================================

void loop() {

  if(millis() - times >= 160){      // a cada 160ms verifica se o botao esta pressionado
      times = millis();
      butcall();                    // realiza leitura dos botoes
      menu(mC);                     // troca menu ou atualiza a tela do display 
    }
  

}// end loop()

//==================================================================================



//==================================================================================
// monitora o pressionar do botao, e gera o valor do proximo menu
void butcall(){  
  if(!digitalRead(menus_m)){
      lcd.clear();
      if(mC < 0x01)mC ++;
      else mC = 0x00;  
    }
   
}// end butcall()

//==================================================================================
