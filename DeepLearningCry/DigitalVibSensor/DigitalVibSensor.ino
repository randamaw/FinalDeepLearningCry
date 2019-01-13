#define SensorLED   13
//Connect the sensor to digital Pin 3 which is Interrupts 1.
#define SensorINPUT  3  

#include <SD.h>
  
unsigned char state = 0;
int v = 0;
File csvFile;

void setup() {
  Serial.begin(9600);//Set Baud Rate to 9600 bps
  
  pinMode(13, OUTPUT);
  pinMode(3, INPUT);
  //Trigger the blink function when the falling edge is detected
  attachInterrupt(1, blink, FALLING);  
//  csvFile = SD.open("rohanrohan.csv", FILE_WRITE);
 
  
}

void loop() {
 
  if (state != 0) {       //vibration sensor
    state = 0;
    digitalWrite(13, HIGH);
    delay(50);
    v++;
  } 
  else
    digitalWrite(13, LOW);


  uint16_t val;        //linear temp sensor
  double dat;
  val=analogRead(A0);//Connect LM35 on Analog A0
  dat = (double) val * (5/10.24); 
  dat = dat*1.8+32;
  //Serial.print("Temp: "); 
  Serial.print(dat);
  Serial.print(","); //expected to be lower for adult -> smaller variability in infant
  Serial.println(v);
 
  delay(500);

}
  
//Interrupts function  
void blink() {
    state++;
}
