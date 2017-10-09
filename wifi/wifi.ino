char *ssid     = "Livebox-CFFC";
char *password = "CF5341C5D91651E54127C6E947";
char *hostName = "rxy";

#include <ESP8266WiFi.h>

#define REMOTEXY_MODE__ESP8266WIFI_LIB
#include <RemoteXY.h> 



// Data for RemoteXY's instance 1
CRemoteXY *rxy1;

const uint16_t rxy1_port = 8266;

const uint8_t PROGMEM rxy1_config[] = { 0,0,12,0,6,5,1,129,0,2,2,4,6,9,65,0 };

struct {
  uint8_t connect_flag;  /* =1 if wire connected, else =0 */
} rxy1_struct;



// Data for RemoteXY's instance 2
CRemoteXY *rxy2;

const uint16_t rxy2_port = 8267;

const uint8_t PROGMEM rxy2_config[] = { 0,0,12,0,6,5,1,129,0,2,2,4,6,9,66,0 };
  
struct {
  uint8_t connect_flag;  /* =1 if wire connected, else =0 */
} rxy2_struct;



void setup()
{
  WiFi.hostname( hostName );
  
  rxy1 = new CRemoteXY( rxy1_config, &rxy1_struct, "", ssid, password, rxy1_port );
  rxy2 = new CRemoteXY( rxy2_config, &rxy2_struct, "", ssid, password, rxy2_port );
} 

void loop() 
{
  rxy1->handler();
  rxy2->handler();
}
