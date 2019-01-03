#include "arduino_secrets.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBotClient.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "DHT.h"
#include <ESP8266HTTPClient.h>

#define DHTPIN 2
#define DHTTYPE DHT22 

// Initialize Wifi connection to the router
const char* ssid  = SECRET_SSID;
const char* password = SECRET_PASS;


// Initialize Telegram BOT
const String botToken = SECRET_BOT_TOKEN;

WiFiClientSecure net_ssl;
TelegramBotClient client(
      botToken, 
      net_ssl);

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

uint16_t acOffData[583] = {3444, 1746,  402, 1318,  416, 1312,  414, 458,  412, 456,  410, 456,  412, 1306,  416, 450,  410, 456,  408, 1310,  398, 1318,  420, 460,  408, 1308,  396, 474,  412, 456,  410, 1308,  418, 1300,  396, 474,  416, 1308,  412, 1306,  414, 452,  394, 470,  414, 1308,  414, 492,  376, 452,  402, 1320,  414, 454,  410, 456,  408, 456,  394, 462,  414, 460,  408, 456,  396, 468,  402, 460,  402, 466,  416, 452,  412, 448,  408, 458,  410, 456,  400, 472,  412, 446,  398, 468,  396, 472,  412, 452,  412, 488,  358, 470,  414, 456,  412, 452,  400, 462,  404, 466,  412, 454,  408, 450,  414, 1308,  400, 1280,  458, 456,  408, 1310,  414, 566,  228, 560,  358, 1322,  414, 458,  408, 1306,  416, 448,  398, 468,  400, 464,  414, 460,  398, 466,  394, 1286,  452, 1350,  374, 488,  374, 1302,  402, 1358,  364, 470,  410, 454,  410, 1304,  398, 472,  392, 532,  354, 1306,  412, 1306,  414, 492,  372, 1312,  392, 474,  412, 1308,  400, 1280,  460, 1304,  402, 464,  448, 1294,  410, 1312,  408, 1308,  414, 456,  410, 454,  400, 468,  410, 490,  374, 492,  374, 488,  374, 450,  408, 454,  394, 468,  414, 460,  408, 454,  406, 452,  414, 496,  374, 494,  372, 458,  410, 456,  406, 456,  400, 470,  412, 460,  412, 452,  410, 454,  400, 468,  412, 492,  374, 454,  410, 452,  410, 452,  410, 452,  412, 452,  412, 456,  408, 1310,  412, 458,  410, 454,  408, 452,  398, 468,  412, 456,  408, 454,  408, 454,  396, 468,  416, 492,  356, 470,  410, 456,  410, 452,  396, 506,  376, 458,  396, 466,  398, 470,  414, 492,  376, 450,  414, 456,  408, 1312,  396, 466,  416, 1350,  372, 1312,  410, 454,  396, 468,  414, 456,  408, 1312,  414, 17048,  3534, 1742,  416, 1308,  394, 1326,  414, 454,  444, 518,  260, 524,  398, 1322,  442, 520,  328, 452,  412, 1312,  390, 1366,  356, 470,  396, 1326,  416, 454,  400, 464,  414, 1350,  372, 1306,  412, 464,  408, 1310,  408, 1308,  414, 452,  394, 470,  412, 1316,  410, 454,  408, 458,  396, 1318,  444, 438,  410, 452,  402, 464,  412, 452,  398, 468,  396, 476,  438, 440,  408, 452,  408, 460,  410, 458,  396, 504,  374, 454,  414, 454,  396, 466,  412, 454,  408, 456,  410, 464,  410, 456,  412, 452,  410, 462,  404, 450,  416, 454,  392, 472,  412, 454,  410, 452,  400, 506,  374, 1310,  414, 1352,  376, 456,  408, 1308,  414, 448,  408, 454,  412, 1306,  402, 466,  414, 1344,  358, 476,  408, 454,  410, 454,  412, 450,  408, 456,  412, 1426,  294, 1394,  318, 468,  398, 1320,  418, 1312,  410, 452,  414, 456,  410, 1306,  404, 462,  416, 458,  398, 1316,  408, 1318,  398, 462,  408, 1314,  408, 468,  412, 1304,  396, 1338,  412, 1306,  416, 448,  412, 1308,  400, 1326,  394, 1326,  414, 488,  374, 454,  410, 456,  410, 452,  396, 466,  400, 466,  408, 458,  422, 500,  364, 452,  410, 490,  374, 454,  394, 470,  412, 494,  358, 470,  412, 492,  358, 470,  436, 440,  412, 446,  402, 464,  412, 492,  374, 454,  408, 452,  412, 452,  410, 494,  360, 468,  402, 462,  416, 458,  408, 496,  372, 452,  400, 1330,  410, 488,  370, 456,  408, 456,  408, 458,  406, 454,  396, 468,  414, 454,  440, 478,  398, 438,  410, 454,  408, 452,  410, 456,  410, 452,  396, 508,  374, 456,  396, 468,  414, 456,  394, 470,  436, 438,  412, 1308,  414, 456,  398, 1320,  412, 1314,  400, 506,  360, 468,  392, 466,  418, 1306,  400};  // MITSUBISHI_AC
uint16_t acOnData[583] = {3406, 1744,  406, 1314,  418, 1308,  414, 454,  410, 448,  398, 470,  394, 1330,  410, 454,  410, 448,  412, 1306,  416, 1306,  412, 456,  408, 1306,  398, 468,  414, 456,  396, 1316,  410, 1322,  414, 450,  402, 1324,  412, 1308,  414, 452,  412, 454,  412, 1308,  412, 456,  412, 452,  406, 1316,  412, 452,  410, 450,  412, 450,  400, 504,  358, 466,  400, 508,  376, 454,  410, 456,  406, 452,  412, 450,  414, 454,  410, 452,  412, 454,  408, 494,  358, 466,  402, 464,  416, 452,  412, 450,  412, 454,  394, 466,  416, 1312,  396, 462,  442, 440,  410, 450,  398, 470,  410, 452,  410, 1358,  378, 1344,  374, 454,  414, 1306,  416, 494,  376, 454,  408, 1346,  372, 458,  412, 1306,  416, 458,  412, 456,  408, 454,  394, 472,  412, 454,  412, 1308,  410, 1344,  358, 466,  406, 1318,  416, 1346,  404, 438,  408, 452,  410, 1312,  396, 464,  416, 452,  416, 1302,  416, 1308,  414, 454,  408, 1306,  402, 460,  408, 1324,  412, 1302,  416, 1308,  412, 490,  360, 1326,  398, 1318,  408, 1314,  416, 458,  406, 454,  412, 456,  410, 458,  410, 448,  406, 462,  414, 452,  412, 452,  412, 452,  412, 448,  410, 458,  408, 490,  374, 456,  410, 450,  412, 450,  410, 492,  358, 466,  404, 462,  414, 494,  366, 464,  398, 472,  400, 460,  418, 450,  446, 434,  410, 452,  410, 454,  406, 460,  406, 458,  412, 450,  414, 1308,  412, 458,  392, 468,  432, 434,  418, 454,  412, 456,  412, 458,  398, 466,  410, 456,  410, 456,  400, 466,  416, 452,  396, 476,  410, 456,  412, 450,  410, 460,  410, 448,  398, 468,  412, 456,  412, 454,  410, 1306,  414, 458,  410, 1306,  412, 1306,  412, 454,  442, 1288,  416, 446,  414, 1308,  414, 17050,  3568, 1726,  416, 1308,  410, 1312,  400, 464,  416, 458,  392, 470,  416, 1302,  400, 470,  414, 492,  362, 1318,  418, 1306,  396, 466,  418, 1306,  412, 460,  406, 458,  408, 1310,  412, 1302,  416, 452,  412, 1304,  416, 1348,  372, 456,  416, 454,  396, 1362,  376, 456,  410, 458,  408, 1304,  402, 470,  408, 456,  392, 472,  414, 458,  412, 488,  370, 456,  392, 470,  412, 458,  408, 454,  410, 458,  394, 470,  414, 454,  414, 454,  408, 452,  396, 470,  414, 452,  400, 508,  370, 452,  396, 468,  394, 466,  416, 1352,  370, 456,  394, 466,  400, 462,  402, 470,  410, 458,  398, 1320,  414, 1310,  410, 452,  406, 1314,  398, 466,  414, 490,  370, 1314,  396, 470,  418, 1306,  414, 454,  410, 456,  408, 458,  392, 472,  408, 456,  396, 1326,  412, 1312,  412, 490,  362, 1316,  416, 1308,  412, 462,  390, 470,  414, 1310,  414, 450,  396, 472,  412, 1308,  412, 1308,  412, 456,  406, 1310,  414, 454,  408, 1308,  414, 1302,  404, 1322,  416, 458,  394, 1322,  400, 1322,  410, 1310,  396, 468,  404, 468,  410, 456,  412, 454,  410, 450,  398, 468,  396, 474,  410, 456,  412, 452,  406, 452,  414, 454,  410, 452,  396, 468,  416, 490,  358, 474,  414, 448,  414, 452,  396, 484,  410, 454,  394, 472,  412, 450,  412, 452,  396, 466,  412, 462,  406, 538,  330, 452,  408, 456,  408, 454,  394, 470,  446, 1292,  408, 498,  370, 454,  410, 454,  398, 468,  414, 490,  358, 472,  406, 456,  410, 458,  412, 454,  410, 488,  392, 440,  414, 454,  394, 468,  412, 456,  408, 452,  410, 458,  406, 536,  330, 492,  360, 470,  398, 1320,  406, 464,  412, 1312,  414, 1306,  414, 454,  394, 1324,  412, 494,  374, 1302,  412};  // MITSUBISHI_AC

DHT dht(DHTPIN, DHTTYPE);

const char* db_name = DB_NAME;
const char* db_password = DB_PASSWORD;

HTTPClient http;

float totalTemperature = 0;
float totalHumidity = 0;
float totalHeatIndex = 0;
int numReadings = 0;
unsigned long sendMetricDelay = 60000;//once per min
unsigned long startTime = 0;

float avgMetric(float metric, int number){
  return metric / number;
}

float avgTemperature(){
  return avgMetric(totalTemperature, numReadings);
}

float avgHumidity(){
  return avgMetric(totalHumidity, numReadings);
}

float avgHeatIndex(){
  return avgMetric(totalHeatIndex, numReadings);
}

// Function called on receiving a message
void onReceive (TelegramProcessError tbcErr, JwcProcessError jwcErr, Message* msg)
{
    if (msg->ChatId != 0){ // Checks if there are some updates
      Serial.println(msg->Text);
      if(msg->Text == "/ac_on")
      {
        acOn();
        client.postMessage(msg->ChatId, "On, Your Magesty!");
      }
      else if(msg->Text == "/ac_off")
      {
        acOff();
        client.postMessage(msg->ChatId, "Off, Your Magesty!");
      }
      else if(msg->Text == "/temperature")//@zloy_home_bot
      {
        char temperatureStr[20];
        sprintf(temperatureStr, "Temperature: %d.%02d C", (int)avgTemperature(), (int)abs(avgTemperature()*100)%100);
        client.postMessage(msg->ChatId, temperatureStr);
      }
      else if(msg->Text == "/humidity")
      {
        char humidityStr[20];
        sprintf(humidityStr, "Humidity: %d.%02d %%", (int)avgHumidity(), (int)abs(avgHumidity()*100)%100);
        client.postMessage(msg->ChatId, humidityStr);
      }
      else if(msg->Text == "/heat_index")
      {
        char heatIndexStr[20];
        sprintf(heatIndexStr, "Heat index: %d.%02d C", (int)avgHeatIndex(), (int)abs(avgHeatIndex()*100)%100);
        client.postMessage(msg->ChatId, heatIndexStr);
      }
      else if(msg->Text == "/metrics")
      {
        char metricsStr[100];
        sprintf(metricsStr, "Temperature: %d.%02d C\n Humidity: %d.%02d %%\n Heat index: %d.%02d C", (int)avgHeatIndex(), (int)abs(avgHeatIndex()*100)%100, (int)avgHumidity(), (int)abs(avgHumidity()*100)%100, (int)avgHeatIndex(), (int)abs(avgHeatIndex()*100)%100);
        client.postMessage(msg->ChatId, metricsStr);
      }
      else
      {
         client.postMessage(msg->ChatId, "What the fuck '" + msg->Text + "' means?!!");
      }
    }
}

// Function called if an error occures
void onError (TelegramProcessError tbcErr, JwcProcessError jwcErr)
{
  Serial.println("onError");
  Serial.print("tbcErr"); Serial.print((int)tbcErr); Serial.print(":"); Serial.println(toString(tbcErr));
  Serial.print("jwcErr"); Serial.print((int)jwcErr); Serial.print(":"); Serial.println(toString(jwcErr));
  client = TelegramBotClient(botToken, net_ssl);
  client.begin(onReceive, onError);
}

void setup() {
  irsend.begin();
  Serial.begin(115200);
  while (!Serial); // Wait for the Serial monitor to be opened

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  client.begin(onReceive, onError); 
  dht.begin();

  startTime = millis();
}

void acOff() {
  for(int i = 0; i < 3; i++) {
    irsend.sendRaw(acOffData, 583, 38);  // Send a raw data capture at 38kHz.
    delay(100);  
  }
}

void acOn() {
  for(int i = 0; i < 3; i++) {
    irsend.sendRaw(acOnData, 583, 38);  // Send a raw data capture at 38kHz.
    delay(100);
  }  
}

void ReadMetrics(){
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);

    totalTemperature += t;
    totalHumidity += h;
    totalHeatIndex += hic;
    numReadings++;
}

void SendMetrics() {

  char payloadStr[150];
  sprintf(payloadStr, "dht11_data temperature=%d.%02d,humidity=%d.%02d,heatindex=%d.%02d", (int)avgTemperature(), (int)abs(avgTemperature()*100)%100, (int)avgHumidity(), (int)abs(avgHumidity()*100)%100, (int)avgHeatIndex(), (int)abs(avgHeatIndex()*100)%100);
  Serial.println(payloadStr);
    
  char corlysisUrl[200];
  sprintf(corlysisUrl, "http://corlysis.com:8087/write?db=%s&u=token&p=%s", db_name, db_password);
  http.begin(corlysisUrl);
  //HTTPS variant - check ssh public key fingerprint
  //sprintf(corlysisUrl, "https://corlysis.com:8086/write?db=%s&u=token&p=%s", db_name, db_password);
  //http.begin(corlysisUrl, "92:23:13:0D:59:68:58:83:E6:82:98:EB:18:D7:68:B5:C8:90:0D:03");
    
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");  
  int httpCode = http.POST(payloadStr);
  Serial.print("http result:");
  Serial.println(httpCode);
  http.writeToStream(&Serial);
  http.end();

  if(httpCode == 204) {
      Serial.println("Data successfully sent.");
  }else{
      Serial.println("Data were not sent. Check network connection.");
  }
  
  numReadings = 0;
  totalTemperature = 0;
  totalHumidity = 0;
  totalHeatIndex = 0;
}

void loop() {
    //read metrics from dht11
    ReadMetrics();
    
    unsigned long loopTime = millis() - startTime;
    if(loopTime > sendMetricDelay) {
      SendMetrics();
      startTime = millis();
    }

    client.loop();
    
    delay(1000);
}
