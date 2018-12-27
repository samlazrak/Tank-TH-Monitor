#include "Particle.h"

// Constants
const unsigned long SEND_INTERVAL_MS = 2000;
const size_t READ_BUF_SIZE = 64;

// Forward declarations
void processBuffer();

// Global variables
int counter = 0;
unsigned long lastSend = 0;

char readBuf[READ_BUF_SIZE];
size_t readBufOffset = 0;

void setup()
{
  Serial.begin(9600);

  // Serial1 RX is connected to Arduino TX (1)
  // Serial2 TX is connected to Arduino RX (0)
  // Photon GND is connected to Arduino GND
  Serial1.begin(9600);
}

void loop()
{
  if (millis() - lastSend >= SEND_INTERVAL_MS)
  {
    lastSend = millis();

    Serial1.printlnf("%d", ++counter);
    Serial.printlnf("Sent to Arduiuno: %d", counter);
  }

  // Read data from serial
  while (Serial1.available())
  {
    if (readBufOffset < READ_BUF_SIZE)
    {
      char c = Serial1.read();
      if (c != '\n')
      {
        // Add character to buffer
        readBuf[readBufOffset++] = c;
      }
      else
      {
        // End of line character found, process line
        readBuf[readBufOffset] = 0;
        processBuffer();
        readBufOffset = 0;
      }
    }
    else
    {
      Serial.println("readBuf overflow, emptying buffer");
      readBufOffset = 0;
    }
  }
}

void processBuffer()
{
  Serial.printlnf("Received from Arduino: %s", readBuf);
}