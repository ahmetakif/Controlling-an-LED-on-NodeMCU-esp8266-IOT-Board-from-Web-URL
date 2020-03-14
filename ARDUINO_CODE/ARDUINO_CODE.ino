#include <ESP8266WiFi.h>

#include <WiFiClient.h>

#include <ESP8266WebServer.h>

#include <ESP8266mDNS.h>



uint8_t pin_led = 14;



const char* ssid = "...";

const char* password = "...";



ESP8266WebServer server(80);



void handleRoot() {

  server.send(200, "text/plain", "ESP8266nMcu01'den Merhabalar :P");

}



void handleNotFound(){

  String message = "File Not Found\n\n";

  message += "URI: ";

  message += server.uri();

  message += "\nMethod: ";

  message += (server.method() == HTTP_GET)?"GET":"POST";

  message += "\nArguments: ";

  message += server.args();

  message += "\n";

  for (uint8_t i=0; i<server.args(); i++){

    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";

  }

  server.send(404, "text/plain", message);

}



void setup(void){

  pinMode(pin_led, OUTPUT);

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.println("");



  // Wait for connection

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.print("Connected to ");

  Serial.println(ssid);

  Serial.print("IP address: ");

  Serial.println(WiFi.localIP());



  if (MDNS.begin("esp8266")) {

    Serial.println("MDNS responder started");

  }



  server.on("/", handleRoot);



  server.on("/inline", [](){

    server.send(200, "text/plain", "Evet, bu da calisiyor :P");

  });



  server.on("/ac",LEDac);

  server.on("/kapa",LEDkapa);



  server.onNotFound(handleNotFound);



  server.begin();

  Serial.println("HTTP server started");

}



void loop(void){

  server.handleClient();

}



void LEDac()

{

  digitalWrite(pin_led,1);

  server.send(200, "text/plain", "LED acildi :D");

}

void LEDkapa()

{

  digitalWrite(pin_led,0);

  server.send(200, "text/plain", "LED kapatildi :)");

}
