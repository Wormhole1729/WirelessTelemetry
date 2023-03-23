#define sensor_pin A0

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int read_val = analogRead(sensor_pin);
  float voltage = read_val*(5.0/1024.0);
  float temperature = 100*voltage;
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C");
  delay(1000);

}
