


#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//==================================================================================
// --- bibliotecas ---
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"
#include <HCSR04.h>

//==================================================================================



//==================================================================================
// --- Exportados --- 

extern LiquidCrystal_I2C lcd;
extern HX711 scale;
extern UltraSonicDistanceSensor distanceSensor;
extern const float area_b;
extern double valor_d;
extern double tare_agua;
extern double m_agua;
extern float peso;
extern float dist_f;
extern char mC;
extern double raw[10];

//==================================================================================



//==================================================================================
// --- Menus ---

void menu(char);

    void sense();               // funçao que consegue os valores lidos, e gera densidade
    void cal_dist();            // mede a altura do sensor em relação ao fundo do becker
 
    void calib();               // mostra os valores de tara, e permite registrar altura da agua  +++++++
 // void menu_out()             // mostra densidade e leitura dos sensores                        +++++++
 
 

//==================================================================================
#endif
