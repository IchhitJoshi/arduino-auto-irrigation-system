#include<SPI.h>
#include<Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xEF, 0xED};
EthernetServer server(80);
String readString;

String a;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ethernet.begin(mac);

  Serial.print("The server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
    a = Serial.readString();
    Serial.println(a);
  }
  
    EthernetClient client = server.available();
    if (client) {
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          Serial.print(c);
          if (readString.length() < 100) {
            readString += c;
          }
          if (c == '\n') {
            Serial.print(readString);
            client.println("<HTTP/1.1 200 OK>");
            client.println("<Connection-Type: text/html>");
            client.println("<Connection: close>");
            client.println();
            client.println("<!DOCTYPE html>");
            client.println("<html style=""background-color:skyblue;"">");
            client.println("<head>");
            client.println("<title>Automatic Irrigation System</title>");
            client.println("<link rel=""icon"" href=""https://png2.cleanpng.com/sh/9b4fda42a5c75c2aef67194563f86aa1/L0KzQYm3U8MyN6hmfZH0aYP2gLBuTfFzbKZuhtG2aX73dbj5ggRmbF5pfehubHBzfbb1lL1mdqduitH3bXXxhH72kPVvNaR0ReV0aX6wRbLphsM4OWNoUKs8ZkWxSYO4U8c4QWQ2TaQ7NEizSYK7WMIyPl91htk=/kisspng-arduino-integrated-development-environment-open-so-skin-5abf3712c893f5.9213779315224809148216.png""></link>");
            client.println("</head>");
            client.println("<body>");
            
            client.println("<h1 style =""text-align:center;"">Automatic Irrigation System</h1>");
            
            
            client.println(a);
            
            client.println("</body>");
            client.println("</html>");
            delay(1);
            client.stop();


          }
        }
      }
    }
  }
  
