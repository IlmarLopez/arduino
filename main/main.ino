#include "WiFiEsp.h"

// Emulate Serial1 on pins 2/3 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#endif

// Variables para declarar los pines de los leds a usar
const int LEDPin8 = 8;
const int LEDPin9 = 9;
const int LEDPin10 = 10;
const int LEDPin11 = 11;

// Variables para declarar los pines de los sensores PIR a usar
const int PIRPin4 = 4;
const int PIRPin5 = 5;
const int PIRPin6 = 6;
const int PIRPin7 = 7;

int pirState4 = LOW;           // de inicio no hay movimiento
int val4 = 0;                  // estado del pin

int pirState5 = LOW;           // de inicio no hay movimiento
int val5 = 0;                  // estado del pin

int pirState6 = LOW;           // de inicio no hay movimiento
int val6 = 0;                  // estado del pin

int pirState7 = LOW;           // de inicio no hay movimiento
int val7 = 0;                  // estado del pin

char ssid[] = "MYHMP";            // your network SSID (name)
char pass[] = "Hol@2020#";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

// Configuration server
IPAddress serverIP(192,168,1,206); // IP
int serverPort = 8084; // Port

// Initialize the Ethernet client object
WiFiEspClient client;

void setup()
{
  pinMode(LEDPin8, OUTPUT);
  pinMode(LEDPin9, OUTPUT);
  pinMode(LEDPin10, OUTPUT);
  pinMode(LEDPin11, OUTPUT);

  pinMode(PIRPin4, INPUT);
  pinMode(PIRPin5, INPUT);
  pinMode(PIRPin6, INPUT);
  pinMode(PIRPin7, INPUT);

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

  // status is WL_CONNECTED
  if (WiFi.status() == WL_CONNECTED)
  {
    // Lectura dijital
    val4 = digitalRead(PIRPin4);
    val5 = digitalRead(PIRPin5);
    val6 = digitalRead(PIRPin6);
    val7 = digitalRead(PIRPin7);

    if (val4 == HIGH)   //si está activado
    {
      digitalWrite(LEDPin8, HIGH);  //LED ON
      if (pirState4 == LOW)  //si previamente estaba apagado
      {
        Serial.println("Sensor activado");
        pirState4 = HIGH;

        if (client.connect(serverIP, serverPort))
        {
          // Make a HTTP request
          String content = "Hey, just testing a post request.";
          client.println("POST /smart-building-server/createAlarm?teaching_id=1001 HTTP/1.1");
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
      digitalWrite(LEDPin8, LOW); // LED OFF
      if (pirState4 == HIGH)  //si previamente estaba encendido
      {
        Serial.println("Sensor parado");
        pirState4 = LOW;
      }
    }

    if (val5 == HIGH)   //si está activado
    {
      digitalWrite(LEDPin9, HIGH);  //LED ON
      if (pirState5 == LOW)  //si previamente estaba apagado
      {
        Serial.println("Sensor activado");
        pirState5 = HIGH;

        if (client.connect(serverIP, serverPort))
        {
          // Make a HTTP request
          String content = "Hey, just testing a post request.";
          client.println("POST /smart-building-server/createAlarm?teaching_id=1002 HTTP/1.1");
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
      digitalWrite(LEDPin9, LOW); // LED OFF
      if (pirState5 == HIGH)  //si previamente estaba encendido
      {
        Serial.println("Sensor parado");
        pirState5 = LOW;
      }
    }

    if (val6 == HIGH)   //si está activado
    {
      digitalWrite(LEDPin10, HIGH);  //LED ON
      if (pirState6 == LOW)  //si previamente estaba apagado
      {
        Serial.println("Sensor activado");
        pirState6 = HIGH;

        if (client.connect(serverIP, serverPort))
        {
          // Make a HTTP request
          String content = "Hey, just testing a post request.";
          client.println("POST /smart-building-server/createAlarm?teaching_id=1003 HTTP/1.1");
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
      digitalWrite(LEDPin10, LOW); // LED OFF
      if (pirState6 == HIGH)  //si previamente estaba encendido
      {
        Serial.println("Sensor parado");
        pirState6 = LOW;
      }
    }

    if (val7 == HIGH)   //si está activado
    {
      digitalWrite(LEDPin11, HIGH);  //LED ON
      if (pirState7 == LOW)  //si previamente estaba apagado
      {
        Serial.println("Sensor activado");
        pirState7 = HIGH;

        if (client.connect(serverIP, serverPort))
        {
          // Make a HTTP request
          String content = "Hey, just testing a post request.";
          client.println("POST /smart-building-server/createAlarm?teaching_id=1004 HTTP/1.1");
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
      digitalWrite(LEDPin11, LOW); // LED OFF
      if (pirState7 == HIGH)  //si previamente estaba encendido
      {
        Serial.println("Sensor parado");
        pirState7 = LOW;
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
