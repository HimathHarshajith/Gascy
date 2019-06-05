#include <SoftwareSerial.h>

/* this is for GPS */

#include <TinyGPS++.h>
SoftwareSerial gpsSerial(2,3);
TinyGPSPlus gps;
float lattitude,longitude;

/* GPS Global over */

// ************************************************************************************* //


/* Force Sensor Global */

float cf=19.5;
int ffsdata=0;
float vout;

/* Force sensor Global End */

// ************************************************************************************* //

/* Sim800L Global */
SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
String number = "+94773560864"; //-> change with your number

/* Sim800L Global End */

// ************************************************************************************* //


void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);

  
  gpsSerial.begin(9600);

  
  
  _buffer.reserve(50);
  Serial.println("Sistem Started...");
  
  sim.begin(9600);
  delay(1000);

}

void loop() {
  
  ffsdata=analogRead(A0);
  vout=(ffsdata*5.0)/1023.0;
  vout=vout*cf;
  Serial.print("Weight: ");
  Serial.println(vout,3);
  Serial.print("");
  delay(100);

  
    if (Serial.available() > 0)
      switch (vout,3)
        {
          case (2.000<vout<2.500):
            SendMessage_one();
            break;
          
         }
    
 
  while (gpsSerial.available())
  {
    int data = gpsSerial.read();
    if (gps.encode(data))
    {
      lattitude = (gps.location.lat());
      longitude = (gps.location.lng());
      Serial.print ("lattitude: ");
      Serial.println (lattitude);
      Serial.print ("longitude: ");
      Serial.println (longitude);
    }
  }

  

  
}

void SendMessage_one()
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "Hello, Your Gas cylinder will be empty soon...please contac this number to order a gas cylinder +94773391585"+String(vout);
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  
}
