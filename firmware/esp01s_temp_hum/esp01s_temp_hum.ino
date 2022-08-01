/* 
  ##########################################################################################################
  ##########################################################################################################
  ## Скетч к проекту мониторинга теспературы и влажности на модуле ESP-01S и платы расширения             ##   
  ##                                                                                                      ##
  ## Группа VK для заказа набора (раздел "товары", подборка "наборы устройств": https://vk.com/retech_msc ##
  ##                                                                                                      ##
  ## Источник: https://www.instructables.com/ESP8266-NodeMCU-Access-Point-AP-for-Web-Server-Wit/          ##
  ##           https://www.instructables.com/ESP8266-Nodemcu-Temperature-Monitoring-Using-DHT11/          ##
  ##########################################################################################################
  ##########################################################################################################
*/

#include "ESP8266WiFi.h"                                // Подключение библиотеки ESP8266WiFi
#include "Adafruit_Sensor.h"                            // Подключение библиотеки Adafruit_Sensor
#include "DHT.h"                                        // Подключение библиотеки DHT

const char* ssid = "DukeHome";               // Название Вашей Wi-Fi сети
const char* password = "gaurangagauranga";          // Пароль Вашей Wi-Fi сети
WiFiServer server(80);                                  // Номер порта Web-сервера
#define DHTPIN 2                                        // Пин, к которому подключен DHT11
#define DHTTYPE DHT11                                   
DHT dht(DHTPIN, DHTTYPE);                               

void setup() 
{
  Serial.begin(115200);                                  
  delay(10);                                            
  dht.begin();                                          
                             
  Serial.println("");                                   
  Serial.print("Подключение к Wi-Fi:  ");               
  Serial.println(ssid);                                 
  delay(10); 
  WiFi.begin(ssid, password);                           
  
  while (WiFi.status() != WL_CONNECTED)                 
  {
   delay(500);                                          
   Serial.print(".");                                   
  }
   Serial.println("");                                                                            
   Serial.println("Wi-Fi подключен");                   
   server.begin();                                      
   Serial.println("Web - сервер запущен.");               
   delay(10000);                                        
   Serial.println(WiFi.localIP());                      // Вывод информации о IP-адресе ESP
}
void loop() 
{
 WiFiClient client = server.available();                
  
 if (client){
  Serial.println("Новый клиент");                         
  boolean blank_line = true;                            
  while (client.connected()){                          
    if (client.available()){                            
     char c = client.read();                            
     if (c == '\n' && blank_line){                     
       float t = dht.readTemperature();                  
       float h = dht.readHumidity();
       client.println("HTTP/1.1 200 OK");              
       client.println("Content-Type: text/html"); 
       client.println("Connection: close");             
       client.println("Refresh: 10");                   
       client.println();
       client.println("<!DOCTYPE HTML>");               
       client.println("<html>");                        
       client.println("<head>");
       client.print("<title>ESP8266 TEMP</title>");     
       client.println("</head>");
       client.println("<body>");
       client.println("<h1>ESP8266 - Temperature & Humidity</h1>"); 
       client.println("<h3>Temperature = ");
       client.println(t);                               
       client.println("*C</h3>");
       client.println("</head>");
       client.println("<body>");
       client.println("<h3>Humidity = ");
       client.println(h);                               
       client.println("</h3>");
       client.println("</body>");
       client.println("</html>");                       
       break;                                           
       }
        if (c == '\n'){                                                                            
         blank_line = true;                             
        }                                          
         else if (c != '\r'){                                                                
          blank_line = false;                           
         }                                        
    }
  }  
    client.stop();                                      
    Serial.println("Клиент отключен");             
}
}
