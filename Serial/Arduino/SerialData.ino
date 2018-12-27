// Constants
const size_t READ_BUF_SIZE = 64;

// Forward declarations
void processBuffer();

// Global variables
char readBuf[READ_BUF_SIZE];
size_t readBufOffset = 0;

void setup()
{
  // Serial TX (1) is connected to Photon RX
  // Serial RX (0) is connected to Photon TX
  // Ardiuno GND is connected to Photon GND
  Serial.begin(9600);
}

void loop()
{
  // Read data from serial
  while (Serial.available())
  {
    if (readBufOffset < READ_BUF_SIZE)
    {
      char c = Serial.read();
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
      readBufOffset = 0;
    }
  }
}

void processBuffer()
{
  int receivedValue = atoi(readBuf);

  // This program just increments the value sent by the Photon and returns it
  Serial.print(receivedValue + 1, DEC);
  Serial.print('\n');
}