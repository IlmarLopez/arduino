#include "WiFiEsp.h"

// Emulate Serial1 on pins 2/3 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#endif

const int LEDPin = 13;        // pin para el LED
const int PIRPin = 4;         // pin de entrada (for PIR sensor)

int pirState = LOW;           // de inicio no hay movimiento
int val = 0;                  // estado del pin

char ssid[] = "MYHMP";            // your network SSID (name)
char pass[] = "Hol@2020#";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

// Configuration server
IPAddress serverIP(192,168,1,206);
int serverPort = 8084;

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  pinMode(LEDPin, OUTPUT); 
  pinMode(PIRPin, INPUT);
  
  // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  
  printWifiStatus();

  if (client.connect(serverIP, serverPort)) {
    Serial.println("Se pudo conectar con ip statica mensaje de prueba");
  }
  else {
   Serial.println("Coneccion fallida");
  }

  Serial.println();
  Serial.println("Starting connection to server...");
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if the server's disconnected, stop the client
//  if (!client.connected()) {
//    Serial.println();
//    Serial.println("Disconnecting from server...");
//    client.stop();
//
//    // do nothing forevermore
//    while (true);
//  }

  if (WiFi.status() == WL_CONNECTED)
  {
    val = digitalRead(PIRPin);
    if (val == HIGH)   //si está activado
    { 
      digitalWrite(LEDPin, HIGH);  //LED ON
      if (pirState == LOW)  //si previamente estaba apagado
      {
        Serial.println("Sensor activado");
        pirState = HIGH;

        if (client.connect(serverIP, serverPort))
        {
          // Make a HTTP request
          String content = "Hey, just testing a post request.";
          client.println("POST /smart-building-server/createAlarm?teaching_id=9999 HTTP/1.1");
          client.println("Host: 192.168.1.206:8084");
          client.println("Accept: */*");
          client.println("Cache-Control: no-cache");
          client.println("Accept-Encoding: gzip, deflate");
          client.println("Content-Length: 0");
          client.println("Connection: keep-alive");
          client.println("cache-control: no-cache");
          client.println();
          client.println(content);
        } 
        
      }
    } 
    else // si esta desactivado
    {
      digitalWrite(LEDPin, LOW); // LED OFF
      if (pirState == HIGH)  //si previamente estaba encendido
      {
        Serial.println("Sensor parado");
        pirState = LOW;
      }
    }

    client.stop();  
  }
}


void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
