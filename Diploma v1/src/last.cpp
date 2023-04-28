// #include <Arduino.h>
// #include <SPI.h>
// #include <MFRC522.h>
// #include <WiFi.h>
// #include "ESPAsyncWebServer.h"
// #include <Adafruit_Sensor.h>
// #include <DHT.h>
// #include <ESP32Servo.h>
// #include <LiquidCrystal_I2C.h>
// #include "EasyBuzzer.h"
// #include <IRremote.h>

// #define SS_PIN  5   
// #define RST_PIN 27  
// #define DHTTYPE DHT11
// #define DHT_PIN 4 //Пін датчка темп. та волог.
// #define PINA 33 //Пін датчика газу
// #define SERVO_PIN 2 //Пін сервоприводу
// #define BUZZER_PIN 32 //Пін п'єзодинаміка
// #define IR_PIN 35 //Пін ІЧ сенсоруу
// #define BTN_PIN 15 //Пін чорної кнопки
// #define DIST 34 //Пін датчика перешкоди

// const char *ssid = "GeyFell"; //Назва мережі Wi-Fi
// const char *password = "multicultural41"; //пароль мережі

// const char* PARAM_INPUT_1 = "output";
// const char* PARAM_INPUT_2 = "state";

// unsigned long uidDec, uidDecTemp;  
// long UID = 4141495794;
// int counter = 0; int freq = 0; int light = 0; int ggwp = 0;
// int flagIR = 0; 
// byte uID[4];
// String S = "";
// int IRarr [4];
// bool flagBtn = false;

// DHT dht(DHT_PIN, DHTTYPE);
// Servo servo; //Ініціалізація сервоприводу
// LiquidCrystal_I2C lcd(0x27, 16, 2); //Ініціалізація LCD-дисплею
// MFRC522 rfid(SS_PIN, RST_PIN); //Ініціалізація MFRC522
// AsyncWebServer server(80); //Призначення веб-серверу порт прослуховування 80

// // HTML-сторінка
// const char index_html[] PROGMEM = R"rawliteral( 
// <!DOCTYPE HTML><html>
// <head>
//   <title>ESPWebServer</title>
//   <meta name="viewport" content="width=device-width, initial-scale=1">
//   <meta http-equiv="Refresh" content="2" />
//   <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
//   <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous"> 
// </head>
// <body>

//   <style>
//     html {
//     font-family: Arial;
//     display: inline-block;
//     margin: 0px auto;
//     text-align: center;
//     }
//     h2 { font-size: 3.0rem; }
//     p { font-size: 3.0rem; }
//     .units { font-size: 1.2rem; }
//     .dht-labels{
//       font-size: 1.5rem;
//       vertical-align: middle;
//       padding-bottom: 15px;
//     }

//     #h2{
//       display: flex;
//       flex-direction: column;
//       align-items: center;
//     }
//     .Main{
//       display: flex;
//       justify-content: space-around;
//     }

//     .switch {
//       position: relative;
//       display: inline-block;
//       vertical-align: middle;
//       width: 60px;
//       height: 34px;
//     }

//     /* Hide default HTML checkbox */
//     .switch input {
//       opacity: 0;
//       width: 0;
//       height: 0;
//     }

//     .slider {
//       position: absolute;
//       cursor: pointer;
//       top: 0;
//       left: 0;
//       right: 0;
//       bottom: 0;
//       background-color: #ccc;
//       -webkit-transition: .4s;
//       transition: .4s;
//     }

//     .slider:before {
//       position: absolute;
//       content: "";
//       height: 26px;
//       width: 26px;
//       left: 4px;
//       bottom: 4px;
//       background-color: white;
//       -webkit-transition: .4s;
//       transition: .4s;
//     }
//     .validate {
//       width: 120px;
//       height: 40px;
//       vertical-align: middle;
//       text-align: center;
//       text-overflow: ellipsis;
//     }

//     input:checked + .slider {
//       background-color: #0066cc;
//     }

//     input:focus + .slider {
//       box-shadow: 0 0 1px #0066cc;
//     }

//     input:checked + .slider:before {
//       -webkit-transform: translateX(26px);
//       -ms-transform: translateX(26px);
//       transform: translateX(26px);
//     }

//     /* Rounded sliders */
//     .slider.round {
//       border-radius: 34px;
//     }

//     .slider.round:before {
//       border-radius: 50px;
//     }

//     .button {
//         background-color: #0066cc; 
//         border: none;
//         color: white;
//         padding: 20px;
//         text-align: center;
//         text-decoration: none;
//         display: inline-block;
//         font-size: 20px;
//         margin: 4px 2px;
//         cursor: pointer;
//         border-radius: 12px;
//     }
//   </style>

//   <br>
//   <div id="h2"><h2>ESP32 HOUSE CONTROL</h2>
//   <br>
//   <div>
//   <p>
//     <i class="fas fa-fire" style="color:red;"></i> 
//     <span class="dht-labels">Fire in the house!</span>
//     <label class="switch">
//             <input class="dht-labels" type="checkbox" align="middle">
//     <span class="slider round">    
//     </span>
//     </label>
//     </p>
//   </div>
//   </div>
//   <br><br><br>
//   <div class="Main">
//   <div class="Col1"> 
//   <div>
//    <p>
//     <i class="fas fa-wind" style="color:#ffcc00;"></i> 
//     <span class="dht-labels">Air pollution:</span> 
//     <span id="air" style="font-size: 30px">%AIR%</span>
//     <span class=" dht-labels">ppm</span>
//   </p>
//   </div>

//   <div>
//   <p>
//     <i class="fas fa-thermometer-half" style="color:#ffcc00;"></i>  
//     <span class="dht-labels">Temperature:</span> 
//     <span id="temperature" style="font-size: 30px">%TEMPERATURE%</span>
//     <span class=" dht-labels">C</span>
//   </p>
//   </div>

//   <div>
//   <p>
//     <i class="fas fa-water" style="color:#ffcc00;"></i> 
//     <span class="dht-labels">Humidity:</span> 
//     <span id="humidity" style="font-size: 30px">%HUMIDITY%</span>
//     <span class=" dht-labels">%</span>
//   </p>
//   </div></div>

//   <div class="Col2">
//   <div>
//   <p>
//     <i class="fas fa-volume-up" style="color:#0066cc;"></i> 
//     <span class="dht-labels">Buzzer Frequency</span> 
//     <input value="500" type="number" class="validate dht-labels">
//     <span class="units dht-labels">Hz</span>
//   </p>
//   </div>

//   <div>
//   <p>
//     <i class="fas fa-lightbulb" style="color:#0066cc;"></i> 
//     <span class="dht-labels">Lighting</span>
//     <label class="switch">
//             <input class="dht-labels" type="checkbox" align="middle">
//     <span class="slider round">    
//     </span>
//     </label>
//     </p>
//   </div>

//   <div>
//   <p>
//     <i class="fas fa-door-open" style="color:#0066cc;"></i> 
//     <span class="dht-labels">Door</span>
//     <label class="switch">
//             <input class="dht-labels" type="checkbox" align="middle">
//     <span class="slider round">    
//     </span>
//     </label>
//     </p>
//   </div>
  
//   <p>
//     <button class="button" href = \"/data\"><b>Send data</b></button>
//   </p>
  
//   </div>
//   </div>
// </body>

// <script>
// setInterval(function ( ) {
//   var xhttp = new XMLHttpRequest();
//   xhttp.onreadystatechange = function() {
//     if (this.readyState == 4 && this.status == 200) {
//       document.getElementById("air").innerHTML = this.responseText;
//     }
//   };
//   xhttp.open("GET", "/air", true);
//   xhttp.send();
// }, 10000 ) ;

// setInterval(function ( ) {
//   var xhttp = new XMLHttpRequest();
//   xhttp.onreadystatechange = function() {
//     if (this.readyState == 4 && this.status == 200) {
//       document.getElementById("temperature").innerHTML = this.responseText;
//     }
//   };
//   xhttp.open("GET", "/temperature", true);
//   xhttp.send();
// }, 10000 ) ;

// setInterval(function ( ) {
//   var xhttp = new XMLHttpRequest();
//   xhttp.onreadystatechange = function() {
//     if (this.readyState == 4 && this.status == 200) {
//       document.getElementById("humidity").innerHTML = this.responseText;
//     }
//   };
//   xhttp.open("GET", "/humidity", true);
//   xhttp.send();
// }, 10000 ) ;
// </script>
// </html>
// )rawliteral";

// String readT(){
//   return String(dht.readTemperature());
// }

// String readH(){
//   return String(dht.readHumidity());
// }

// String readA(){
//   return String(analogRead(PINA));
// }

// void servoOpen(){
//   servo.write(90);
// }
// void servoClose(){
//   servo.write(0);
// }

// String processor(const String &var){
//   //Serial.println(var);
//   if (var == "TEMPERATURE")
//   {
//     return readT();
//   }
//   else if (var == "HUMIDITY")
//   {
//     return readH();
//   }
//   if (var == "AIR")
//   {
//     return readA();
//   }
//   if (var == "OPEN")
//   {
//     servoOpen();
//   }
//   if (var == "CLOSE")
//   {
//     servoClose();
//   }
//   return String();
// }

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Start...");
//   SPI.begin(); 
//   rfid.PCD_Init(); 
//   //IrReceiver.begin(IR_PIN); 
//   dht.begin();
//   lcd.init();
//   lcd.backlight();
//   EasyBuzzer.setPin(BUZZER_PIN);
//   EasyBuzzer.stopBeep();
//   servo.setPeriodHertz(50); // standard 50 hz servo
//   servo.attach(SERVO_PIN);
//   if (servo.attached())servo.write(0);
//   pinMode(PINA, INPUT);
//   pinMode(12, OUTPUT);
//   pinMode(13, OUTPUT);
//   pinMode(14, OUTPUT);
//   digitalWrite(12, LOW);
//   digitalWrite(13, LOW);
//   digitalWrite(14, LOW);
//   pinMode(BTN_PIN, INPUT);
//   pinMode(DIST, INPUT);
//   // ESP32PWM::allocateTimer(0);
//   // ESP32PWM::allocateTimer(1);
//   // ESP32PWM::allocateTimer(2);
//   // ESP32PWM::allocateTimer(3);
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("Put your card");

//   WiFi.begin(ssid, password);  
//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
//             { request->send_P(200, "text/html", index_html, processor); });
//   server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request)
//             { request->send_P(200, "text/plain", readT().c_str()); });
//   server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request)
//             { request->send_P(200, "text/plain", readH().c_str()); });
//   server.on("/air", HTTP_GET, [](AsyncWebServerRequest *request)
//             { request->send_P(200, "text/plain", readA().c_str()); });
//   // server.on("/servo", HTTP_GET, [](AsyncWebServerRequest *request)
//   //           { request->send_P(200, "text/plain", readS().c_str()); });
//   server.begin();
// }

// int amount = 1;

// void loop() {
  
//   //WiFi
//   if (WiFi.status() == 3 && amount == 1)
//   {
//     Serial.println("CONNECTED!");
//     Serial.println(WiFi.localIP());
//     amount = 0;
//   }  
//   if (WiFi.status() == 4)
//   {
//     Serial.println("Connection failed!"); 
//     delay(5000);    
//   } 
//   else if (WiFi.status() == 5)
//   {
//     Serial.println("Oops... Connection lost"); 
//     delay(5000);    
//   } 
//   else if (WiFi.status() == 1)
//   {
//     Serial.println("No SSID available!"); 
//     delay(5000);   
//   }

//   //RGB and Button
//   if(digitalRead(BTN_PIN) && flagBtn == 0){
//     //digitalWrite(12, HIGH);
//     digitalWrite(13, LOW);
//     digitalWrite(14, LOW);
//     flagBtn=!flagBtn; 
//     delay(100);
//   }
//   else if(digitalRead(BTN_PIN) && flagBtn == 1){
//     //digitalWrite(12, LOW);
//     digitalWrite(13, HIGH);
//     digitalWrite(14, HIGH); 
//     flagBtn=!flagBtn;
//     delay(100);
//   }

//   //IR obstacle
//   if (digitalRead(DIST) == 0){
//     EasyBuzzer.stopBeep();
//     counter++;
//     Serial.println(counter);
//     delay(100);
//     if (counter>3){    
//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("Someone in the");
//       lcd.setCursor(0, 4);
//       lcd.print("house!");
//       servo.write(0);
//       EasyBuzzer.singleBeep(
//       700,
//       3000	
//       );  
//       delay(3000);
//       EasyBuzzer.stopBeep();
//       counter=0;
//     }
//   }

//   //RFID
//   if (!rfid.PICC_IsNewCardPresent()){
//     return;}
//   if (!rfid.PICC_ReadCardSerial()){
//     return;}
  
//   uidDec = 0;
//   for (byte i = 0; i < rfid.uid.size; i++)
//   {
//     uidDecTemp = rfid.uid.uidByte[i];
//     uidDec = uidDec * 256 + uidDecTemp;
//   }
//   // Serial.println("Card UID: ");
//   // Serial.println(uidDec); 
  
//   if (uidDec == UID){
//     //EasyBuzzer.stopBeep();
//     Serial.println("Welcome home!");
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("Welcome home!");
//     servo.write(90);
//     digitalWrite(13, HIGH);
//     digitalWrite(12, LOW);
//     digitalWrite(14, LOW);
//     delay(5000);
//     servo.write(0);
//     digitalWrite(13, HIGH);
//     digitalWrite(12, HIGH);
//     digitalWrite(14, HIGH);     
//   } 
//   else{
//     Serial.println("WRONG!");
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("Who are you?!");
//     servo.write(0);
//     digitalWrite(12, HIGH);
//     digitalWrite(13, LOW);
//     digitalWrite(14, LOW);EasyBuzzer.singleBeep(
//       500, 	
//       5000	
//     );
//     EasyBuzzer.stopBeep();
//   }
//   //EasyBuzzer.stopBeep();
  
//   rfid.PICC_HaltA(); // halt PICC
//   rfid.PCD_StopCrypto1(); // stop encryption on PCD
// }





