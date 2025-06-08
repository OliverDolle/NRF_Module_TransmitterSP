#include <Arduino.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 4
#define CSN_PIN 5

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "NODE1";

const char text[] = "Ping";
const int delayMs = 10;  // delay between channel hops

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!radio.begin()) {
    Serial.println("NRF24L01 error");
    while (1);
  }

  radio.setPALevel(RF24_PA_MAX);   // Maximum power
  radio.setDataRate(RF24_2MBPS);   // Highest data rate
  radio.setAutoAck(false);         // Disable auto acknowledgement
  radio.setRetries(0, 0);          // No retries
  radio.openWritingPipe(address);  // Set address
  radio.stopListening();           // Set as transmitter

  Serial.println("Ready for transmition on several chanels");
}

void loop() {
  for (int channel = 0; channel <= 125; channel++) {
    radio.setChannel(channel);
    bool success = radio.write(&text, sizeof(text));
    
    Serial.printf("Chanel %d: %s\n", channel, success ? "Sent" : "error");
    delay(delayMs);
  }
}
