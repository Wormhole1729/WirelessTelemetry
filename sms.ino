#include <GSM.h>
#define PINNUMBER ""

GSM gsmAccess;
GSM_SMS sms;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  Serial.println("SMS Messages Sender")
  boolean notConnected = true;
  while(notConnected){
  if(gsmAccess.begin(PINNUMBER) == GSM_READY){
    notConnected = false;
  }
  else{
    Serial.println("Not connected");
    delay(1000);
    }
}

  Serial.println("GSM initialized");

}

int readSerial(char result[])
void loop() {

  // put your main code here, to run repeatedly:

}
