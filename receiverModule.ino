//code for receiving and displaying voltage in TFT LCD screen

#include<RFM69.h>
#include<SPI.h>
#include<TFT.h>
#define cs_tft 7
#define cs_rfm 10
#define DC 9
#define RESET 8
#define NETWORKID 0
#define MYNODEID 2
#define TONODEID 1
#define FREQUENCY_RF69 868
#define ENCRYPT true
#define ENCRYPTKEY "FirstProject"
#define USEACK true
RFM69 radio;
TFT TFTscreen = TFT(cs_tft,DC,RESET); // initialize the tft screen by passing cs,dc,rst pins

void setup(){
  pinMode(cs_tft,OUTPUT);
  pinMode(cs_rfm,OUTPUT);
  digitalWrite(cs_tft,HIGH);

  //initialize RFM69

  Serial.begin(9600);
  Serial.print("Node ");
  Serial.print(MYNODEID,DEC);
  Serial.println("ready");
  radio.initialize(FREQUENCY_RF69,MYNODEID,NETWORKID);
  radio.setHighPower();
  
  if(ENCRYPT)
  radio.encrypt(ENCRYPTKEY);

  digitalWrite(cs_rfm,HIGH);

  //initialize the tft display and drawing a table with 6 rows and 2 columns with writing a heading 
  //"Voltage values" and channel no in each row
  int i_tft=15,l_tft=6,m_tft=1;
  int j_tft=0;
  float k_tft=1;
  pinMode(cs_tft,OUTPUT);
  TFTscreen.begin();
  TFTscreen.background(200,200,200);
  TFTscreen.stroke(0,0,0);
  TFTscreen.text("Voltage Values\n" ,5,5);
  for(m_tft;m_tft<=l_tft;m_tft++){
    TFTscreen.line(0,i_tft,168,i_tft);
    TFTscreen.text("Channel-",5,j_tft=i_tft+3);
    myDisplay(k_tft,56,j_tft);
    i_tft += 12;
    k_tft += 1;
  }
  TFTscreen.line(0,i_tft,168,i_tft);
  TFTscreen.line(70,16,70,i_tft);
  digitalWrite(cs_tft,HIGH);
  digitalWrite(cs_rfm,LOW);

}
  //function to display a number
  void myDisplay(float a, int b, int c){
    int d,f=0,g;
    float e;
    g=c;
    d=a;
    e=a-d;
    if(e!=0){
      char voltage[8];
      String sensorVal = String(a);
      sensorVal.toCharArray(voltage1,8);
      TFTscreen.stroke(200,200,200);
      TFTscreen.text(voltage1,b,c);
    }
    //if float then display in the format of integer
    else{
      char voltage1[8];
      String sensorVal = String(d);
      sensorVal.toCharArray(voltage1,8);
      for(f=1;f<=8;f++){
        TFTscreen.stroke(200,200,200);
        TFTscreen.line(76,g,168,g);
        g = g+1;
      }
      TFTscreen.stroke(0,0,0);
      TFTscreen.text(voltage1,b,c);
    }
    delay(100);
    
  }

  






void loop() {
  // put your main code here, to run repeatedly:
  byte datasize = 0,assemble_count=0;
  int a = b = c = e = 0, f_1=18;
  int voltage_digit[30];
  int voltage[30];
  //receive data from transmitter and print in serial monitor
  if(radio.receiveDone()){
    Serial.print("received from node  ");
    Serial.println(radio.SENDERID,DEC);
    for(len=0;len<radio.DATALEN;len++){
      voltage_digit[len] = radio.DATA[len];
    }
    Serial.println("Data in assemble form");
    for( ;a<radio.DATALEN;b++){
      voltage[b] = assemble_byte(&voltage_digit[a],&a);
      Serial.prinltln(voltage[b]);
    }
    Serial.println("***************************");
    digitalWrite(cs_rfm,HIGH);
    for(e=0;e<b;e++){
      myDisplay(voltage[e],76,f_1);
      f_1 += 12;
    }
    digitalWrite(cs_tft,HIGH);
    if(radio.ACKRequested()){
      radio.sendACK();
      Serial.println("ACK Sent")
    }
    Serial.print("\n\n");
    delay(1000);
  }

}
