#include "Particle.h"

// Const
const size_t READ_BUF_SIZE = 256;

// Structs
typedef struct
{
  float temperature;
  float humidity;
} MonitorData;

// Forward Decs
void processBuffer();
void handleMonitorData(const MonitorData &data);

// Global
int counter = 0;
unsigned long lastSend = 0;

char readBuf[READ_BUF_SIZE];
size_t readBufOffset = 0;

void setup()
{
  Serial.begin(9600);

  Serial1.begin(19200);
}

void loop()
{
  while (Serial1.available())
  {
    if (readBufOffset < READ_BUF_SIZE)
    {
      char c = Serial1.read();
      if (c != '\n')
      {
        // add char to buffer
        readBuf[readBufOffset++] = c;
      }
      else
      {
        // eol char found finish line
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
  MonitorData data;

  if (sscanf(readBuf, "%d, %d", &data.temperature, &data.humidity) == 2)
  {
    handleMonitorData(data);
  }
  else
  {
    Serial.printlnf("Invalid data %s", readBuf);
  }
}

void handleMonitorData(const MonitorData &data)
{
  Serial.printlnf("Temperature=%d Humidity=%d", data.temperature, data.humidity);
}
