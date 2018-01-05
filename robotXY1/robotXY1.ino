#include <Servo.h>


//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
// RemoteXY select connection mode and include library 
//#define REMOTEXY_MODE__SOFTSERIAL
#define REMOTEXY_MODE__SERIAL  
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial 
#define REMOTEXY_SERIAL_SPEED 9600
/*
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600
*/

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,5,0,0,0,42,0,6,10,0,
  1,0,26,28,12,12,1,88,0,4,
  0,4,2,10,57,2,4,0,86,2,
  10,57,2,4,160,21,7,58,10,1,
  1,0,62,28,12,12,1,88,0 }; 
    
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

double check_attach;
int ordre_bouge = 1;

//declaration tete
//#define PIN_TETE 10
#define PIN_BG 7
#define PIN_BD 8

Servo brasGauche;
Servo brasDroit;


int valBD;
int valBG;




int positionBG; //bras gauche
int positionBD; //bras droit

int old_positionBG = 0; //bras gauche
int old_positionBD = 0; //bras droit



void setup() {
  // put your setup code here, to run once:

  RemoteXY_Init (); 

  brasGauche.attach(PIN_BG);
    RemoteXY.bras_gauche = 50;

  brasDroit.attach(PIN_BD);
  RemoteXY.bras_droit = 50;
  Serial.begin(9600);
  


}

void loop() {
  // put your main code here, to run repeatedly:
RemoteXY_Handler ();
  
    //digitalWrite(PIN_OD, (RemoteXY.oeil_droit==0)?LOW:HIGH);
  //digitalWrite(PIN_OG, (RemoteXY.oeil_gauche==0)?LOW:HIGH);

  positionBG = map(RemoteXY.bras_gauche, 100, 0, 0, 179);

  
  positionBD = map(RemoteXY.bras_droit, 0, 100, 0, 179);
  if (positionBD != old_positionBD) ordre_bouge = 1;
  if (positionBG != old_positionBG) ordre_bouge = 1;
  
 if (ordre_bouge == 1) {
    old_positionBG = positionBG;
    old_positionBD = positionBD; 
    bouge();
}
}

void bouge() {
  //brasGauche.attach(PIN_BG);
  //tete.attach(PIN_TETE);
  //brasDroit.attach(9);
  //brasGauche.write(positionBG);
  //brasDroit.write(positionBD);
  int bg = RemoteXY.bras_gauche;
  int bd = RemoteXY.bras_droit;
  if (bg >= 48 && bg <= 52) {
    bg=50;
  }
  if (bd >= 48 && bd <= 52) {
    bd=50;
  }
  Serial.print("bg:");
  Serial.print(bg);
  Serial.print(",bd:");
  Serial.print(bd);
  brasGauche.writeMicroseconds(bg*20+500); 
  brasDroit.writeMicroseconds(2500-bd*20);  
  ordre_bouge = 0;
   affiche();
}

void affiche() {
  Serial.print("BG,BD :");
  Serial.print(positionBG);
  Serial.print(",");
  Serial.println(positionBD);
}

