#include <Servo.h>


//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
/*
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 12
#define REMOTEXY_SERIAL_TX 13
#define REMOTEXY_SERIAL_SPEED 9600
*/
#define REMOTEXY_MODE__SERIAL 
#include <RemoteXY.h> 

/* RemoteXY connection settings */ 
#define REMOTEXY_SERIAL Serial 
#define REMOTEXY_SERIAL_SPEED 9600  

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
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

} RemoteXY;
#pragma pack(pop) 

#define PIN_OD 5 //oeil droit
#define PIN_OG 4 //oeil gauche
/*
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
*/
void setup() {
  // put your setup code here, to run once:

  RemoteXY_Init (); 
  
  pinMode (PIN_OD, OUTPUT);
  pinMode (PIN_OG, OUTPUT);

 /* brasGauche.attach(11);
  tete.attach(10);
  brasDroit.attach(9);*/
  Serial.begin(9600);
  digitalWrite(PIN_OD,HIGH);
  digitalWrite(PIN_OG,HIGH);

  RemoteXY.bras_droit = 50;
  RemoteXY.tete = 50;
  RemoteXY.bras_gauche = 50;


}

void loop() {
  // put your main code here, to run repeatedly:

  RemoteXY_Handler ();
    digitalWrite(PIN_OD, (RemoteXY.oeil_droit==0)?LOW:HIGH);
  digitalWrite(PIN_OG, (RemoteXY.oeil_gauche==0)?LOW:HIGH);
/*
  positionBG = map(RemoteXY.bras_droit, 0, 100, 0, 179);
  positionT = map(RemoteXY.tete, 100, -100, 0, 179);
  positionBD = map(RemoteXY.bras_gauche, 100, 0, 0, 179);
  if (positionBD != old_positionBD) ordre_bouge = 1;
  if (positionBG != old_positionBG) ordre_bouge = 1;
  if (positionT != old_positionT) ordre_bouge = 1;
  if (ordre_bouge == 1) {
    old_positionT = positionT;
    old_positionBG = positionBG;
    old_positionBD = positionBD; 
    //bouge();
  }
  else {
    if (check_attach > 1000) {
      brasGauche.detach();
  tete.detach();
  brasDroit.detach();
    }
  
  }
*/  
    
}
/*
void bouge() {
  brasGauche.attach(11);
  tete.attach(10);
  brasDroit.attach(9);
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
*/
