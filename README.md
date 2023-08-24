Wi-Fi мониторинг температуры и влажности на основе ESP-01S. Веб-сервер монитора. Часть 1.

Для мониторинга температуры и относительной влажности окружающей среды посредством Wi-Fi может служить устройство, собранное из нескольких модулей: Wi-Fi модуля ESP-01S и платы расширения с датчиком температуры DHT11. 

Сперва необходимо прошить модуль ESP-01S программатором USB-TTL, файлы прошивки и необходимых библиотек вы сможете найти в архиве к посту. Для прошивки модуля требуется установка нескольких библиотек (ESP8266WiFi.h, Adafruit_Sensor.h и DHT.h), установить их можно двумя способами, описанными в посте о одноканальном реле (см. ранее). 

В прошивке необходимо указать адрес и пароль вашей Wi-Fi сети, в Arduino IDE выбрать плату Generic ESP8266 Module, подключить ESP-01S к программатору USB-TTL и загрузить прошивку в модуль. После прошивки модуля необходимо узнать IP-адрес ESP-01S (с помощью монитора порта Arduino IDE, в нем необходимо указать такую же скорость передачи данных, как написано в прошивке – 115200). 

Далее необходимо переставить модуль ESP-01S на плату расширения с датчиком температуры и влажности, подать питание 5В на разъем питания платы расширения, перейти по IP-адресу, полученному после прошивки, в браузере ПК. В открывшейся странице можно увидеть действующие значения температуры и относительной влажности.
