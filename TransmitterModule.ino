#include<RFM69.h>
#include<SPI.h>
#define NETWORKID 0
#define MYNODEID 1
#define TONODEID 2
#define FREQUENCY_RF69_MHZ 866
#define ENCRYPT true
#define ENCRYPTKEY "FirstProject"
#define USEACK true
RFM69 radio;

void setup() {
  Serial.begin(9600);
  Serial.print("Node ");
  Serial.print(MYNODEID,DEC);
  radio.initialize(FREQUENCY,MYNODEID,NETWORKID);
  radio.setHighPower();
  if(ENCRYPT){
    radio.encrypt(ENCRYPTKEY);
  }
  // put your setup code here, to run once:

}

int separateDigit(byte *n , int readValue, int count){
  while((readValue/10) != 0){
    *n = readValue%10;
    readValue /= 10;
    n += 1;
    count++;
  }

  *n = 255;
  count++;
  return(count);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte data[30];
  //didn't understand from here
  int c, i=0,j=0,k=5,l=0;
  //read the A/D converter and store in"data" variable.
  for(l=0;l<=k;l++){
    c = analogRead(l);
    Serial.print(" A to D converter Value port ");
    Serial.print(l);
    Serial.print(":");
    Serial.println(c);
    i=separatebit(&data[i],c,i);
  }

  //Transmit the data

  Serial.println("sending to node");
  Serial.println(TONODEID, DEC);
  if(USEACK){
    if(radio.sendWithRetry(TONODEID,data,i))
    Serial.println("\n ACK received!");
    else
    Serialprintln("\n No ACK received");
  }
  else radio.send(TONODEID,data,i);
  delay(5000);
}
















//source https://circuitdigest.com/microcontroller-projects/how-to-interface-rfm69hcw-rf-module-with-arduino





