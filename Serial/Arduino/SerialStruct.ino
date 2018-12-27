// Data to send as struct
typedef struct
{
  float temperature;
  float humidity;
} MonitorData;

// Forward declarations
void getMonitorData(MonitorData &data);
void sendMonitorData(const MonitorData &data);

// Global
char sendBuf[256];

void setup()
{
  // Why 19200? 9600?
  Serial.begin(19200);
}

void loop()
{
  MonitorData data;
  getMonitorData(data);
  sendMonitorData(data);
  delay(5000);
}

void getMonitorData(MonitorData &data)
{
  data.temperature = rand();
  data.humidity = rand();
}

void sendMonitorData(const MonitorData &data)
{
  snprintf(sendBuf, sizeof(sendBuf), "%d,%d\n",
           data.temperature, data.humidity);
  Serial.print(sendBuf);
}
