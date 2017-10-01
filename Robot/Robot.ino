#include <Servo.h>

Servo brasGauche;
Servo brasDroit;
Servo tete;

int valBD;
int valBG;
int valTete;

int positionBG; //bras gauche
int positionBD; //bras droit
int positionT; //tete
int const potBG = A0;
int const potBD = A2;
int const potTete = A1;
void setup() {
  // put your setup code here, to run once:

  brasGauche.attach(10);
  tete.attach(11);
  brasDroit.attach(9);
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  valBG = analogRead(potBG);
  valTete = analogRead(potTete);
  valBD = analogRead(potBD);
  positionBG = map(valBG, 0, 1023, 0, 179);
  positionT = map(valTete, 0, 1023, 0, 179);
  positionBD = map(valBD, 0, 1023, 0, 179);
  affiche();
  bouge();
    
}

void bouge() {
  brasGauche.write(positionBG);
  tete.write(positionT);
  brasDroit.write(positionBD);
  delay(150);

}

void affiche() {
  Serial.print("BG,tete,BD :");
  Serial.print(positionBG);
  Serial.print(",");
  Serial.print(positionT);
  Serial.print(",");
  Serial.println(positionBD);
}

