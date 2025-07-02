//controller_1
#include <SPI.h>
#include <Ethernet.h>

//car entry entry_gate1
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01};
IPAddress ip(192, 168, 1, 157);

// bike entry For entry_gate2
//byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x02};
//IPAddress ip(192, 168, 1, 158);

// car exit For exit_gate1
//byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03};
//IPAddress ip(192, 168, 1, 159);

// bike exit  exit_gate2
//byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x04};
//IPAddress ip(192, 168, 1, 160);

IPAddress serverIp(192, 168, 1, 21);
EthernetClient client;

const int relayPin = 9;

void setup() {
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
}

void loop() {
  if (client.connect(serverIp, 8000)) {
    client.println("GET /check_boomsig/?gate_id=entry_gate1 HTTP/1.1");
    client.println("Host: 192.168.1.21");
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);

        if (line.indexOf("|OPENEN%") >= 0) {
          Serial.println("Opening gate...");
          digitalWrite(relayPin, LOW);
          delay(500);
          digitalWrite(relayPin, HIGH);
        }
      }
    }
    client.stop();
  } else {
    Serial.println("Connection to server failed");
  }
  delay(5000);
}
