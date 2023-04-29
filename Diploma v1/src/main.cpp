#include <WiFi.h>
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <DNSServer.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>
#include "EasyBuzzer.h"
#include <IRremote.h>

#define SS_PIN  5   
#define RST_PIN 27  
#define DHTTYPE DHT11
#define DHT_PIN 4 //Пін датчка темп. та волог.
#define PINA 33 //Пін датчика газу
#define SERVO_PIN 2 //Пін сервоприводу
#define BUZZER_PIN 32 //Пін п'єзодинаміка
#define IR_PIN 35 //Пін ІЧ сенсоруу
#define BTN_PIN 15 //Пін чорної кнопки
#define DIST 34 //Пін датчика перешкоди

BLEServer *pServer = NULL;
BLECharacteristic *tempCharacteristic = NULL;
BLECharacteristic *humidityCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t temperature = 0;
uint8_t humidity = 0;

uint8_t newTemperature = 0;
uint8_t newHumidity = 0;
String PARAM_INPUT = "state";
int TEMP_SENSOR_PIN = 14;
#define SERVICE_UUID "c23b7ab5-0301-441a-ac60-1757084297d4"
#define TEMP_CHARACTERISTIC_UUID "e7ca3a76-9026-4f56-9b35-09da4c3c5eea"
#define HUMIDITY_CHARACTERISTIC_UUID "8c6fe5b0-0931-41f7-bab5-6b08cb20f524"

const char *ssid = "GeyFell"; //Назва мережі Wi-Fi
const char *password = "multicultural41"; //пароль мережі

const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

unsigned long uidDec, uidDecTemp;  
long UID = 4141495794;
int counter = 0; int freq = 0; int light = 0; int ggwp = 0;
int flagIR = 0; 
byte uID[4];
String S = "";
int IRarr [4];
bool flagBtn = false;
String LEDState = "false";
String FireState = "false";
String ServoState = "false";
DHT dht(DHT_PIN, DHTTYPE);
Servo servo; //Ініціалізація сервоприводу
LiquidCrystal_I2C lcd(0x27, 16, 2); //Ініціалізація LCD-дисплею
MFRC522 rfid(SS_PIN, RST_PIN); //Ініціалізація MFRC522
AsyncWebServer server(80); //Призначення веб-серверу порт прослуховування 80

// HTML-сторінка
const char index_html[] PROGMEM = R"rawliteral( 
<!DOCTYPE HTML><html>
<head>
  <title>ESPWebServer</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
 
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous"> 
</head>
<body>

  <style>
    html {
    font-family: Arial;
    display: inline-block;
    margin: 0px auto;
    text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align: middle;
      padding-bottom: 15px;
    }

    #h2{
      display: flex;
      flex-direction: column;
      align-items: center;
    }
    .Main{
      display: flex;
      justify-content: space-around;
    }

    .switch {
      position: relative;
      display: inline-block;
      vertical-align: middle;
      width: 60px;
      height: 34px;
    }

    /* Hide default HTML checkbox */
    .switch input {
      opacity: 0;
      width: 0;
      height: 0;
    }

    .slider {
      position: absolute;
      cursor: pointer;
      top: 0;
      left: 0;
      right: 0;
      bottom: 0;
      background-color: #ccc;
      -webkit-transition: .4s;
      transition: .4s;
    }

    .slider:before {
      position: absolute;
      content: "";
      height: 26px;
      width: 26px;
      left: 4px;
      bottom: 4px;
      background-color: white;
      -webkit-transition: .4s;
      transition: .4s;
    }
    .validate {
      width: 120px;
      height: 40px;
      vertical-align: middle;
      text-align: center;
      text-overflow: ellipsis;
    }

    input:checked + .slider {
      background-color: #0066cc;
    }

    input:focus + .slider {
      box-shadow: 0 0 1px #0066cc;
    }

    input:checked + .slider:before {
      -webkit-transform: translateX(26px);
      -ms-transform: translateX(26px);
      transform: translateX(26px);
    }

    /* Rounded sliders */
    .slider.round {
      border-radius: 34px;
    }

    .slider.round:before {
      border-radius: 50px;
    }

    .button {
        background-color: #0066cc; 
        border: none;
        color: white;
        padding: 20px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 20px;
        margin: 4px 2px;
        cursor: pointer;
        border-radius: 12px;
    }
  </style>

  <br>
  <div id="h2"><h2>ESP32 HOUSE CONTROL</h2>
  <br>
  <div>
  <p>
    <i class="fas fa-fire" style="color:red;"></i> 
    <span class="dht-labels">Fire in the house!</span>
    <label class="switch">
            <input class="dht-labels" type="checkbox" align="middle">
    <span class="slider round">    
    </span>
    </label>
    </p>
  </div>
  </div>
  <br><br><br>
  <div class="Main">
  <div class="Col1"> 
  <div>
   <p>
    <i class="fas fa-wind" style="color:#ffcc00;"></i> 
    <span class="dht-labels">Air pollution:</span> 
    <span id="air" style="font-size: 30px">%AIR%</span>
    <span class=" dht-labels">ppm</span>
  </p>
  </div>

  <div>
  <p>
    <i class="fas fa-thermometer-half" style="color:#ffcc00;"></i>  
    <span class="dht-labels">Temperature:</span> 
    <span id="temperature" style="font-size: 30px">%TEMPERATURE%</span>
    <span class=" dht-labels">C</span>
  </p>
  </div>

  <div>
  <p>
    <i class="fas fa-water" style="color:#ffcc00;"></i> 
    <span class="dht-labels">Humidity:</span> 
    <span id="humidity" style="font-size: 30px">%HUMIDITY%</span>
    <span class=" dht-labels">%</span>
  </p>
  </div></div>

  <div class="Col2">
  
  <div>
  <p>
    <i class="fas fa-lightbulb" style="color:#0066cc;"></i> 
    <span class="dht-labels">Lighting</span>
    <label class="switch">
            <input class="dht-labels" id="LEDswitch" type="checkbox" align="middle">
    <span class="slider round">    
    </span>
    </label>
    </p>
  </div>

  <div>
  <p>
    <i class="fas fa-door-open" style="color:#0066cc;"></i> 
    <span class="dht-labels">Door</span>
    <label class="switch">
            <input class="dht-labels" id="Servoswitch" type="checkbox" align="middle">
    <span class="slider round">    
    </span>
    </label>
    </p>
  </div>
  
  <button class="button" onClick="toggleCheckbox();"><b>Send data</b></button> 
  
  </div>
  </div>
</body>

<script> 
let LEDswitch = document.getElementById('LEDswitch');
let Servoswitch = document.getElementById('Servoswitch');

function toggleCheckbox() {  
  var xhreq1 = new XMLHttpRequest();
  
  if(LEDswitch.checked){ xhreq1.open("GET", "/LEDweb?state=1", true); }
  else { xhreq1.open("GET", "/LEDweb?state=0", true); }
    
  xhreq1.send();

  var xhreq2 = new XMLHttpRequest();
  
  if(Servoswitch.checked){ xhreq2.open("GET", "/Servoweb?state=1", true); }
  else { xhreq2.open("GET", "/Servoweb?state=0", true); }
  
  xhreq2.send();
  console.log("Web data sent!");
}

let swi=[{ id: '2', Enabled: false },
  { id: '3', Enabled: false }];

  const data = () => {
    let dat;
    let air;
    let temp;
    let hum;
    (document.getElementById("air").innerHTML=='nan')?air='225':air=document.getElementById("air").innerHTML;
    (document.getElementById("temperature").innerHTML=='nan')?temp='24':temp=document.getElementById("temperature").innerHTML;
    (document.getElementById("humidity").innerHTML=='nan')?hum='63':hum=document.getElementById("humidity").innerHTML;
    return dat=[{ id: '1', Indicator: 'AirPollution', Value: air.toString() },
                { id: '2', Indicator: 'Temperature', Value: temp.toString() },
                { id: '3', Indicator: 'Humidity', Value: hum.toString() }]
  }  
  
  // POST запрос
  fetch('http://localhost:5000/postData', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify(data()),
  })
  .then(response => {response.text(); console.log(response)});
  //.then(data => console.log(data));

setInterval(function() {  
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("air").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/air", true);
  xhttp.send();
}, 10000);

setInterval(function() { 
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000);

setInterval(function() { 
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000);

  // GET запрос
  //setInterval(()=>{
  fetch('http://localhost:5000/getData')
  .then(response => response.json())
  .then(data => {console.log(data); swi = data})
  
    // var xhr1 = new XMLHttpRequest();
    // xhr1.open("GET", "/Fire?state="+swi[0].Enabled, true);
    // xhr1.send();

    var xhr2 = new XMLHttpRequest();
    xhr2.open("GET", "/LED?state="+swi[0].Enabled, true);
    xhr2.send();

    var xhr3 = new XMLHttpRequest();
    xhr3.open("GET", "/Servo?state="+swi[1].Enabled, true);
    xhr3.send();
  //}, 1000)

</script>
</html>
)rawliteral";

String readT(){
  return String(dht.readTemperature());
}

String readH(){
  return String(dht.readHumidity());
}

String readA(){
  return String(analogRead(PINA));
}

String outputState(int output){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
}

String processor(const String &var){
  //Serial.println(var);
  if (var == "TEMPERATURE")
  {
    return readT();
  }
  else if (var == "HUMIDITY")
  {
    return readH();
  }
  if (var == "AIR")
  {
    return readA();
  }
  return String();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Start...");
  SPI.begin(); 
  rfid.PCD_Init(); 
  //IrReceiver.begin(IR_PIN); 
  dht.begin();
  lcd.init();
  lcd.backlight();
  EasyBuzzer.setPin(BUZZER_PIN);
  EasyBuzzer.stopBeep();
  servo.setPeriodHertz(50); // standard 50 hz servo
  servo.attach(SERVO_PIN);
  //if (servo.attached())servo.write(0);
  pinMode(PINA, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  pinMode(BTN_PIN, INPUT);
  pinMode(DIST, INPUT);
  // ESP32PWM::allocateTimer(0);
  // ESP32PWM::allocateTimer(1);
  // ESP32PWM::allocateTimer(2);
  // ESP32PWM::allocateTimer(3);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Put your card");

  WiFi.begin(ssid, password);  
  
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html, processor); });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", readT().c_str()); });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", readH().c_str()); });
  server.on("/air", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/plain", readA().c_str()); });

  // server.on("/Fire", HTTP_GET, [] (AsyncWebServerRequest *request) {
  //   String inputMessage;
  //   if (request->hasParam(PARAM_INPUT)) {
  //     inputMessage = request->getParam(PARAM_INPUT)->value();
  //   }
  //   else {
  //     inputMessage = "No Fire message sent";
  //   }
  //   Serial.println("Input Fire: "+ inputMessage);
  //   request->send(200, "text/plain", "OK");
  // });

 server.on("/LEDweb", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam(PARAM_INPUT)) {
      LEDState = request->getParam(PARAM_INPUT)->value();
      inputMessage = request->getParam(PARAM_INPUT)->value();
      if (LEDState=="1"){
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(14, HIGH);
      }
      else{
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      digitalWrite(14, LOW);
      }
    }
    else {
      inputMessage = "No LEDweb message sent";
    }
    Serial.println("Input LED: "+ inputMessage);
    request->send(200, "text/plain", "OK");
  });

   server.on("/Servoweb", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam(PARAM_INPUT)){
      ServoState = request->getParam(PARAM_INPUT)->value();
      inputMessage = request->getParam(PARAM_INPUT)->value();
      if (ServoState=="1"){
      servo.write(70);
      }
      else{
      servo.write(0);
      }
    }
    else {
      inputMessage = "No Servoweb message sent";
    }
    Serial.println("Input Servo: "+ inputMessage);
    request->send(200, "text/plain", "OK");
  });
  

   server.on("/LED", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam(PARAM_INPUT)) {
      LEDState = request->getParam(PARAM_INPUT)->value();
      inputMessage = request->getParam(PARAM_INPUT)->value();
      if (LEDState=="true"){
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(14, HIGH);
      }
      else{
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      digitalWrite(14, LOW);
      }
    }
    else {
      inputMessage = "No LED message sent";
    }
    Serial.println("Input LED: "+ inputMessage);
    request->send(200, "text/plain", "OK");
  });

   server.on("/Servo", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam(PARAM_INPUT)){
      ServoState = request->getParam(PARAM_INPUT)->value();
      inputMessage = request->getParam(PARAM_INPUT)->value();
      if (ServoState=="true"){
      servo.write(70);
      }
      else{
      servo.write(0);
      }
    }
    else {
      inputMessage = "No Servo message sent";
    }
    Serial.println("Input Servo: "+ inputMessage);
    request->send(200, "text/plain", "OK");
  });
  server.begin();
}

int amount = 1;

void loop(){ 
  //WiFi
  if (WiFi.status() == 3 && amount == 1)
  {
    Serial.println("CONNECTED!");
    Serial.println(WiFi.localIP());
    amount = 0;
  }  
  if (WiFi.status() == 4)
  {
    Serial.println("Connection failed!"); 
    delay(5000);    
  } 
  else if (WiFi.status() == 5)
  {
    Serial.println("Oops... Connection lost"); 
    delay(5000);    
  } 
  else if (WiFi.status() == 1)
  {
    Serial.println("No SSID available!"); 
    delay(5000);   
  }

  //RGB and Button
  if(digitalRead(BTN_PIN) && flagBtn == 0){
    //digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    digitalWrite(14, LOW);
    flagBtn=!flagBtn; 
    delay(100);
  }
  else if(digitalRead(BTN_PIN) && flagBtn == 1){
    //digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    digitalWrite(14, HIGH); 
    flagBtn=!flagBtn;
    delay(100);
  }

  //IR obstacle
  if (digitalRead(DIST) == 0){
    EasyBuzzer.stopBeep();
    counter++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(counter);
    Serial.println(counter);
    delay(100);
    if (counter==4){    
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Someone in");
      lcd.setCursor(1, 1);
      lcd.print("the house!");
      servo.write(0);
      // EasyBuzzer.singleBeep(
      // 700,
      // 3000	
      // );  
      delay(3000);
      EasyBuzzer.stopBeep();
      counter=0;
    }
  }

  //RFID
  if (!rfid.PICC_IsNewCardPresent()){
    return;}
  if (!rfid.PICC_ReadCardSerial()){
    return;}
  
  uidDec = 0;
  for (byte i = 0; i < rfid.uid.size; i++)
  {
    uidDecTemp = rfid.uid.uidByte[i];
    uidDec = uidDec * 256 + uidDecTemp;
  }
  // Serial.println("Card UID: ");
  // Serial.println(uidDec); 
  
  if (uidDec == UID){
    //EasyBuzzer.stopBeep();
    Serial.println("Welcome home!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome home!");
    //servo.setPeriodHertz(50);
    servo.write(70);
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(14, LOW);
    delay(5000);
    servo.write(0);
    //servo.setPeriodHertz(0);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(14, HIGH);     
  } 
  else{
    Serial.println("WRONG!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Who are you?!");
    
    servo.write(0);
    //servo.setPeriodHertz(0);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    digitalWrite(14, LOW);
    // EasyBuzzer.singleBeep(
    //   500, 	
    //   5000	
    // );
    EasyBuzzer.stopBeep();
  }
  //EasyBuzzer.stopBeep();
  
  rfid.PICC_HaltA(); // halt PICC
  rfid.PCD_StopCrypto1(); // stop encryption on PCD
}





