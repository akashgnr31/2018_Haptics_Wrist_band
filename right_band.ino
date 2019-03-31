#include <SoftwareSerial.h>
 
#define DEBUG true
 
SoftwareSerial esp8266(2,3); 
                             
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  
  
  pinMode(7,OUTPUT);
  digitalWrite(7,LOW);
   
  // pinMode(13,OUTPUT);
   // digitalWrite(13,LOW);
   
 // sendData("AT+RST\r\n",2000,DEBUG); // reset module
 // sendData("AT+CWJAP=\"ABC\",\"12345678\"\r\n",2000,DEBUG);
  //sendData("AT+CWQAP\r\n",1000,DEBUG);
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
  //sendData("AT+CWJAP=\"akash\",\"akashgangwar\"\r\n",2000,DEBUG);
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
}
 
void loop()
{
  if(esp8266.available()) // check if the esp is sending a message zaa
  {
    if(esp8266.find("+IPD," ))
    {
     delay(1000); // wait for the serial buffer to fill up (read all the serial data)
     // get the connection id so that we can then disconnect
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
          
     if(esp8266.find("right"))
     {
      Serial.print("right");
      digitalWrite(7,HIGH);
      delay(3000);
     }
     digitalWrite(7,LOW); 
     }
    }
  }

/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}
