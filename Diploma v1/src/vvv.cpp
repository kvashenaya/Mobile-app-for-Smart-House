// #include <SPI.h>
// #include <MFRC522.h>

// #define SS_PIN  25  // ESP32 pin GIOP5 
// #define RST_PIN 27 // ESP32 pin GIOP27 

// MFRC522 rfid(SS_PIN, RST_PIN);

// void setup() {
//   Serial.begin(115200);
//   SPI.begin(); // init SPI bus
//   rfid.PCD_Init(); // init MFRC522

//   Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
// }

// void loop() {
//   if (rfid.PICC_IsNewCardPresent()) { // new tag is available
//     if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
//       MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
//       Serial.print("RFID/NFC Tag Type: ");
//       Serial.println(rfid.PICC_GetTypeName(piccType));

//       // print UID in Serial Monitor in the hex format
//       Serial.print("UID:");
//       for (int i = 0; i < rfid.uid.size; i++) {
//         Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
//         Serial.print(rfid.uid.uidByte[i], HEX);
//       }
//       Serial.println();

//       rfid.PICC_HaltA(); // halt PICC
//       rfid.PCD_StopCrypto1(); // stop encryption on PCD
//     }
//   }
// }








//#include <Arduino.h>
// #include <SPI.h>
// #include <WiFi.h>
// #include <MFRC522.h>
// #include "ESPAsyncWebServer.h"
// #include <Adafruit_Sensor.h>
// #include <DHT.h>
// #include <ESP32Servo.h>
// #include <LiquidCrystal_I2C.h>
// #include "EasyBuzzer.h"

// // // const char *ssid = "HUGE_DICK";
// // // const char *password = "748596123";

// const char *ssid = "GeyFell";
// const char *password = "multicultural41";

// const char *ssid = "iPhone";
// const char *password = "idinaher";

// #define DHTTYPE DHT11
// #define DHT_PIN 4
// #define PINA 33
// #define SS_PIN 5
// #define RST_PIN 27
// #define SERVO_PIN 14
// #define BUZZER_PIN 32
// #define BUZZER_CHANNEL 0
// #define DIST 34
// #define SOUND_SPEED 0.034
// #define CM_TO_INCH 0.393701

// int flag = 0;
// int btnPin = 12;
// long duration;
// float distanceCm; float distanceInch;
// int counter = 0; int freq = 0; int light = 0; int ggwp = 0;

// DHT dht(DHT_PIN, DHTTYPE);
// Servo servo;
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// MFRC522 rfid(SS_PIN, RST_PIN);
// MFRC522::MIFARE_Key key;

// AsyncWebServer server(80);
// byte uID[4];
// String S = "";
// String colour[4] = {"1314018225", "1379031136", "", ""};

// const char index_html[] PROGMEM = R"rawliteral( 
// <!DOCTYPE HTML><html>
// <head>
//   <meta name="viewport" content="width=device-width, initial-scale=1">
//   <meta http-equiv="Refresh" content="2" />
//   <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
//   <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
//   <style>
//     html {
//      font-family: Arial;
//      display: inline-block;
//      margin: 0px auto;
//      text-align: center;
//     }
//     h2 { font-size: 3.0rem; }
//     p { font-size: 3.0rem; }
//     .units { font-size: 1.2rem; }
//     .dht-labels{
//       font-size: 1.5rem;
//       vertical-align:middle;
//       padding-bottom: 2px;
//       padding-right: 1px;
//       padding-left: 1px;
//       text-align: center;
//     }
//     .fas{
//       font-size: 2.6rem;
//     }
//     /* The switch - the box around the slider */

// .switch {
//   position: relative;
//   display: inline-block;
//   width: 60px;
//   height: 34px;
// }

// /* Hide default HTML checkbox */
// .switch input {
//   opacity: 0;
//   width: 0;
//   height: 0;
// }

// /* The slider */
// .slider {
//   position: absolute;
//   cursor: pointer;
//   top: 0;
//   left: 0;
//   right: 0;
//   bottom: 0;
//   background-color: #ccc;
//   -webkit-transition: .4s;
//   transition: .4s;
// }

// .slider:before {
//   position: absolute;
//   content: "";
//   height: 26px;
//   width: 26px;
//   left: 4px;
//   bottom: 4px;
//   background-color: white;
//   -webkit-transition: .4s;
//   transition: .4s;
// }

// .validate {
//   vertical-align: middle;
//   text-align: center;
//   text-overflow: ellipsis;
// }

// input:checked + .slider {
//   background-color: #2196F3;
// }

// input:focus + .slider {
//   box-shadow: 0 0 1px #2196F3;
// }

// input:checked + .slider:before {
//   -webkit-transform: translateX(26px);
//   -ms-transform: translateX(26px);
//   transform: translateX(26px);
// }

// /* Rounded sliders */
// .slider.round {
//   border-radius: 34px;
// }

// .slider.round:before {
//   border-radius: 50px;
// }

// .button {
//     background-color: green; 
//     border: none;
//     color: white;
//     padding: 20px;
//     text-align: center;
//     text-decoration: none;
//     display: inline-block;
//     font-size: 16px;
//     margin: 4px 2px;
//     cursor: pointer;
//     border-radius: 12px;
//     margin-left: auto; 
//     margin-right: auto; 
//     width: 40%;"
// }
//   </style>
// </head>
// <body>
  
// <div id="Main">
//   <h2>ESP32 HOUSE CONTROL</h2>
// <div>
//   <p> 
//     <i class="fas fa-thermometer-half" style="color:#e6a122;"></i>  
//     <span class="dht-labels">Temperature:</span> 
//     <span id="temperature" style="font-size: 30px">%TEMPERATURE%</span>
//     <span class="units dht-labels">C</span>
//   </p>
// </div>

// <div>
//   <p>  
//     <i class="fas fa-water" style="color:#e6a122;"></i> 
//     <span class="dht-labels">Humidity:</span> 
//     <span id="humidity" style="font-size: 30px">%HUMIDITY%</span>
//     <span class="units dht-labels">%</span>
//   </p>
// </div>

// <div>
//   <p>  
//     <i class="fas fa-wind" style="color:#e6a122;"></i> 
//     <span class="dht-labels">Air pollution:</span> 
//     <span id="air" style="font-size: 30px">%AIR%</span>
//     <span class="units dht-labels">%</span>
//   </p>
// </div>

// <div>
//   <p>
//     <i class="fab fa-gripfire" style="color:#e63222;"></i> 
//     <span class="dht-labels">Fire in the house!</span>
//     <label class="switch">
//             <input class="dht-labels" type="checkbox" align="middle">
//     <span class="slider round">    
//     </span>
//     </label>
//   </p>
// </div>

// <div>
//   <p>
//     <i class="fas fa-volume-up" style="color:#2277e6;"></i> <i class="fas fa-wave-square"></i>
//     <span class="dht-labels">Buzzer Frequency</span> 
//     <input value="500" type="number" class="validate dht-labels" >
//     <span class="units dht-labels">Hz</span>
//   </p>
// </div>


//   <p>
//     <button class="button" href = \"/data\"><b>Send data</b></button>
//   </p>
// </div>
// </body>

// <script>
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

// </script>
// <script>
//  setTimeout(function(){
//    location.reload();
//    }, 1000);
// </script> 
// </html>
// )rawliteral";



// String printDec(byte *buffer, byte bufferSize){
//   S = "";
//   for (byte i = 0; i < bufferSize; i++)
//   {
//     // Serial.print(buffer[i] < 0x10 ? " 0" : " ");
//     //Serial.print(buffer[i], DEC);
//     S += buffer[i];
//   }
//   return S;
// }

// bool checkKey(String S){
//   for (int i = 0; i < 4; i++)
//   {
//     if (colour[i] == S)
//       return true;
//   }

//   return false;
// }

// String readT(){
//   return String(dht.readTemperature());
// }

// String readH(){
//   return String(dht.readHumidity());
// }

// String readA(){
//   return String(analogRead(PINA));
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
//   else if (var == "AIR")
//   {
//     return readA();
//   }
//   return String();
// }

// void setup(){
//   Serial.begin(115200);
//   Serial.println("Start...");
//   rfid.PCD_Init(); // Init MFRC522
//   EasyBuzzer.setPin(BUZZER_PIN);
//   for (byte i = 0; i < 6; i++)
//   {
//     key.keyByte[i] = 0xFF;
//   }
//   pinMode(PINA, INPUT);
//   EasyBuzzer.setPin(BUZZER_PIN);
//   SPI.begin();     // Init SPI bus
//   dht.begin();
//   lcd.init();
//   lcd.backlight();
//   // pinMode(2, OUTPUT);
//   // pinMode(4, OUTPUT);
//   // pinMode(5, OUTPUT);
//   // pinMode(btnPin, INPUT);
//   // ESP32PWM::allocateTimer(0);
//   // ESP32PWM::allocateTimer(1);
//   // ESP32PWM::allocateTimer(2);
//   // ESP32PWM::allocateTimer(3);
  
//     // digitalWrite(2, LOW);
//     // digitalWrite(4, LOW);
//     // digitalWrite(5, LOW);
// 	WiFi.begin(ssid, password);  
//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
//             { request->send_P(200, "text/html", index_html, processor); });
//   server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request)
//             { request->send_P(200, "text/plain", readT().c_str()); });
//   server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request)
//             { request->send_P(200, "text/plain", readH().c_str()); });
//   server.on("/air", HTTP_GET, [](AsyncWebServerRequest *request)
//             { request->send_P(200, "text/plain", readA().c_str()); });
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
//   if (WiFi.status() == 5)
//   {
//     Serial.println("Oops... Connection lost"); 
//     delay(5000);    
//   } 
//   if (WiFi.status() == 1)
//   {
//     Serial.println("No SSID available!"); 
//     delay(5000);   
//   } 
//   //RGB and Button
//   // if(digitalRead(btnPin) && flag == 0){
//   //    //digitalWrite(2, HIGH);
//   //   digitalWrite(4, HIGH);
//   //   digitalWrite(5, HIGH);
//   // }
//   // else if(digitalRead(btnPin) && flag == 1){
//   //   //digitalWrite(2, LOW);
//   //   digitalWrite(4, LOW);
//   //   digitalWrite(5, LOW);
//   //   flag++;
//   //   flag++;
//   // }
//   // else if(digitalRead(btnPin) && flag == 2){
//   //   //digitalWrite(2, HIGH);
//   //   digitalWrite(4, LOW);
//   //   digitalWrite(5, LOW);
//   //   flag++;
//   // }
//   // else if(digitalRead(btnPin) && flag == 3){
//   //   //digitalWrite(2, LOW);
//   //   digitalWrite(4, HIGH);
//   //   digitalWrite(5, LOW);
//   //   flag++;
//   // }
//   // else if(digitalRead(btnPin) && flag == 4){
//   //   //digitalWrite(2, LOW);
//   //   digitalWrite(4, LOW);
//   //   digitalWrite(5, HIGH);
//   //   flag = 0;
//   // }
  
//   // float h = dht.readHumidity();
//   // float t = dht.readTemperature();

//   // Serial.print(F("Humidity: "));
//   // Serial.print(h);
//   // Serial.print(F("%  Temperature: "));
//   // Serial.print(t);
//   // delay(3000);

//   //Servo
//   if (!servo.attached())
//   {
//     servo.setPeriodHertz(50); // standard 50 hz servo
//     servo.attach(5);          // Attach the servo after it has been detatched
//     delay(500);
//   }
//   //RFID
//   // if (!rfid.PICC_IsNewCardPresent())
//   //   return;

//   // if (!rfid.PICC_ReadCardSerial())
//   //   return;

//   // for (byte i = 0; i < 4; i++)
//   // {
//   //   uID[i] = rfid.uid.uidByte[i];
//   //   Serial.print(uID[i]);
//   // }
  
//   // delay(1000);
//   // if (checkKey(printDec(rfid.uid.uidByte, rfid.uid.size)))
//   // {
//   //   pinMode(BUZZER_PIN, OUTPUT);
//   //   //pinMode(4, INPUT);
//   //   //counter++;
//   //   //Serial.print(counter);
//   //   // EasyBuzzer.beep(350);
//   //   // delay(500);
//   //   EasyBuzzer.stopBeep();
//   //   //EasyBuzzer.update();
//   //   // pinMode(4, INPUT);
//   //   // pinMode(4, OUTPUT);
//   //   lcd.setCursor(0, 0);
//   //   lcd.clear();
//   //   lcd.print("Welcome!");
//   //   servo.write(90);
//   //   //delay(500);
//   // }
//   // else
//   // {
//   //   pinMode(BUZZER_PIN, INPUT);
//   //   //pinMode(4, OUTPUT);
//   //   //lcd.backlight();
//   //   lcd.setCursor(0, 0);
//   //   lcd.clear();
//   //   lcd.print("Who are you?!");
//   //    EasyBuzzer.beep(600);
//   //   delay(500);
//   //   //EasyBuzzer.stopBeep();
//   // }

//   // EasyBuzzer.stopBeep();
//   // lcd.clear();
//   // rfid.PICC_HaltA();
//   // rfid.PCD_StopCrypto1();

//   // Serial.println(WiFi.status());
//   // delay(2000);




//   if (rfid.PICC_IsNewCardPresent()) { // new tag is available
//     if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
//       MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
//       Serial.print("RFID/NFC Tag Type: ");
//       Serial.println(rfid.PICC_GetTypeName(piccType));

//       // print UID in Serial Monitor in the hex format
//       Serial.print("UID:");
//       for (int i = 0; i < rfid.uid.size; i++) {
//         Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
//         Serial.print(rfid.uid.uidByte[i], HEX);
//       }
//       Serial.println();

//       rfid.PICC_HaltA(); // halt PICC
//       rfid.PCD_StopCrypto1(); // stop encryption on PCD
//     }
//   }
// }


// // void setup(){
// //   Serial.begin(115200);
// //   lcd.init();
  
// // }

// // void loop(){
// //   delay(2000);
//   // float h = dht.readHumidity();
//   // float t = dht.readTemperature();

//   // Serial.print(F("Humidity: "));
//   // Serial.print(h);
//   // Serial.print(F("%  Temperature: "));
//   // Serial.print(t);
// // lcd.setCursor(0, 0);
// //     lcd.backlight();
// //     lcd.clear();
// //     lcd.print("Hello!");
// // }