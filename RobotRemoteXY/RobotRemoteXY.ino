#include <Servo.h>


//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
/*
   -- robot --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.3.1 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.0.1 or later version;
     - for iOS 1.1.0 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
char *ssid     = "Livebox-CFFC";
char *password = "CF5341C5D91651E54127C6E947";
char *hostName = "rxy";
#define REMOTEXY__DEBUGLOGS Serial
#include <ESP8266WiFi.h>

#define REMOTEXY_MODE__ESP8266WIFI_LIB

#include <RemoteXY.h>



// Data for RemoteXY's instance 1
CRemoteXY *rxy1;

const uint16_t rxy1_port = 8266;

// RemoteXY configurate  
#pragma pack(push, 1)
const uint8_t PROGMEM titi_conf[] =
  { 255,5,0,0,0,42,0,6,10,0,
  1,0,30,28,12,12,1,88,0,4,
  0,7,2,19,59,2,4,0,71,-1,
  17,62,2,4,160,22,5,54,15,1,
  1,0,53,28,12,12,1,88,0 };
  
// this structure defines all the variables of your control interface 
struct {

    // input variable
  uint8_t oeil_gauche; // =1 if button pressed, else =0 
  int8_t bras_gauche; // =0..100 slider position 
  int8_t bras_droit; // =0..100 slider position 
  int8_t tete; // =-100..100 slider position 
  uint8_t oeil_droit; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} titi;
#pragma pack(pop)

#define PIN_OD 4 //oeil droit
#define PIN_OG 5 //oeil gauche
#define PIN_BG 13
#define PIN_BD 14
#define PIN_T 12

Servo brasGauche;
Servo brasDroit;
Servo tete;

int valBD;
int valBG;
int valTete;

double check_attach;

int positionBG; //bras gauche
int positionBD; //bras droit
int positionT; //tete
int old_positionBG = 0; //bras gauche
int old_positionBD = 0; //bras droit
int old_positionT = 0; //tete
int ordre_bouge = 1;

  int troisP[3] = {positionBG,positionBD,positionT};
  int troisPO[3] = {old_positionBG,old_positionBD,old_positionT};
void setup() {
  // put your setup code here, to run once:

 WiFi.hostname( hostName );
  
  rxy1 = new CRemoteXY( titi_conf, &titi, "", ssid, password, rxy1_port );
  
  pinMode (PIN_OD, OUTPUT);
  pinMode (PIN_OG, OUTPUT);

  brasGauche.attach(PIN_BG);
  tete.attach(PIN_T);
  brasDroit.attach(PIN_BD);
  Serial.begin(9600);
  digitalWrite(PIN_OD,HIGH);
  digitalWrite(PIN_OG,HIGH);

  titi.bras_droit = 50;
  titi.tete = 50;
  titi.bras_gauche = 50;

  

}

void loop() {
  // put your main code here, to run repeatedly:

   rxy1->handler();
  
  digitalWrite(PIN_OD, (titi.oeil_droit==0)?LOW:HIGH);
  digitalWrite(PIN_OG, (titi.oeil_gauche==0)?LOW:HIGH);

  positionBG = map(titi.bras_gauche, 0, 100, 0, 179);
  positionT = map(titi.tete, -100, 100, 0, 179);
  positionBD = map(titi.bras_droit, 100, 0, 0, 179);
  if (positionBD != old_positionBD) ordre_bouge = 1;
  if (positionBG != old_positionBG) ordre_bouge = 1;
  if (positionT != old_positionT) ordre_bouge = 1;
  if (ordre_bouge == 1) {
    old_positionT = positionT;
    old_positionBG = positionBG;
    old_positionBD = positionBD; 
    bouge();
  }
  else {
    if (check_attach > 1000) {
      //brasGauche.detach();
  //tete.detach();
  //brasDroit.detach();
    }
  
  }
  
    
}

void bouge() {
  //brasGauche.attach(11);
  //tete.attach(10);
  //brasDroit.attach(9);
  brasGauche.write(positionBG);
  tete.write(positionT);
  brasDroit.write(positionBD);
  ordre_bouge = 0;
   affiche();
   delay(150);
   check_attach = millis();
}

void affiche() {
  Serial.print("BG,tete,BD :");
  Serial.print(positionBG);
  Serial.print(",");
  Serial.print(positionT);
  Serial.print(",");
  Serial.println(positionBD);
}

