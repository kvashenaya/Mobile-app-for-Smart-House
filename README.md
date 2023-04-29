# ESP32 SMART HOUSE CONTROL

ESP32 web server (Diploma v1 directory) + React Native mobile application client (first-app directory) + Apollo server (server directory)

# ESP32 web server:
1. Use PlatformIO for ESP32
2. Install all required libraries using PlatformIO (Diploma v1/src/main.cpp)
3. Upload your code (use -> on the bottom panel in the VS Code)
4. Find the IP-address of your ESP32 device in the serial monitor (the bottom panel in the VS Code) 
5. Open a web page in the browser

# React Native mobile application and Apollo server:
1. command 'npm start' for the client
2. command 'npm run dev' for the server

The app (client side) consists of two pages: main and informational. 
On the main page, the user needs to be authorized using a fingerprint or password, (it is '123' in the code). 
After entering valid data, the user can go to the information page using the "GO TO DATA" button, 
which displays temperature, humidity and air pollution indicators. 
To return to the main page, click the "GO TO HOME" button.

Data query language GraphQL is used to transfer data between the client and the server. 
The server part of the mobile application sends and receives data from the ESP32 server.

1. Receiving data from the ESP32 server:
  • Occurs using the command fetch, GET request
  • Sensor data is constantly updated
  • The ESP32 server sends updated data to the mobile application server every 5 seconds, after which the data is broadcast to the client
2. Sending data to the ESP32 server:
  • Occurs using the fetch command, POST request
  • When the user changes the state of the LED and servo switches, the updated data is sent from the client to the server
  • The mobile application server sends data to the ESP32 server, then the lighting or entrance door status is updated
