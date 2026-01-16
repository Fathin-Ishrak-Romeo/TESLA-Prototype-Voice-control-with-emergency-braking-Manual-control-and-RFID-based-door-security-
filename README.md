# Objective
Developed a cost-efficient Tesla-inspired robotic car using Arduino Uno and ESP32-CAM, featuring RFID-based door security lock, Wi-Fi–secured web server for manual control, and Bluetooth-based voice control via an android app, with the ability to switch seamlessly between manual and voice control modes at any time. Integrated an emergency braking and collision avoidance system using ultrasonic sensors that detect obstacles within 30 cm (front/rear) and 15 cm (during turns), automatically stopping the vehicle until a new command is received. Added a rearview camera with backlight support to enhance parking precision and low-light visibility.

----

# Full Setup & Installation Guidelines (Module-wise & Step by Step)
## Module 1 Manual Control with Rearview Camera System
### <b>Step i: Installing ESP32 Board</b> </br>
1. Open Arduino IDE.
2. Go to: File > Preferences </br> <img src="images/1.png" alt="1" width="200">
3. Paste this link https://dl.espressif.com/dl/package_esp32_index.json within the "Additional board manager URLs" section > Click "OK". </br> <img src="images/2.png" alt="2" width="550"> </br><b> NOTE: </b> If other boards are already installed, add a comma (,) at the end of the existing link/s, paste the link with no space, and then click ‘OK’ as shown in the above picture.
4. Go to: Tools > Board > Boards Manager. </br> <img src="images/3.png" alt="3" width="360">
5. Search: "esp32 by Espressif Systems" > Select Version: 2.0.0 > Install. </br> <img src="images/4.png" alt="4" width="200">

### <b>Step ii: Installing Necessary Libraries</b> </br>
1. Download: "AsyncTCP-master.zip" from [HERE](https://github.com/Fathin-Ishrak-Romeo/TESLA-Prototype-Voice-control-with-emergency-braking-Manual-control-and-RFID-based-door-security-/blob/01eec37880873f9ae82a443b227cad36dd5af50b/Module%201%20Manual%20Control%20with%20Rearview%20Camera%20System/Libraries/AsyncTCP-master.zip)
2. Download: "ESPAsyncWebServer-master.zip" from [HERE](https://github.com/Fathin-Ishrak-Romeo/TESLA-Prototype-Voice-control-with-emergency-braking-Manual-control-and-RFID-based-door-security-/blob/01eec37880873f9ae82a443b227cad36dd5af50b/Module%201%20Manual%20Control%20with%20Rearview%20Camera%20System/Libraries/ESPAsyncWebServer-master.zip)
3. Open Arduino IDE.
4. Go to: Sketch > Include Library > Add .ZIP Library. </br> <img src="images/5.png" alt="5" width="400">
5. Select both of the downloaded "AsyncTCP-master.zip" and "ESPAsyncWebServer-master.zip" library files one by one > Click: "Open".

### <b>Step iii: Important Settings for Smooth Real-time Video Steaming</b> </br>
1. Open: "This PC".
2. Go to: "Documents" folder > "Arduino" folder > "librares" folder > "ESP_Async_WebServer" folder > "src" folder.
3. Right Click: "AsyncWebSocket.h" file > Open with > Notepad. </br> <img src="images/6.png" alt="6" width="460">
4. Set the marked macro to 1 as shown in the below picture, then save the file by pressing "Win + S". </br> <img src="images/7.png" alt="7" width="460">

### <b>Step iv: Using Arduino UNO as an External Programmer to Upload the Code into ESP32 CAM</b> </br>
1. Build the below circuit. </br><img src="External Programmer Arduino UNO Circuit Diagram.png" alt="500" width="500">
2. Connect the Arduino UNO to the PC using USB cable.
3. Open Arduino IDE
4. Go to: Tools > Board > esp32 > ESP32 Wrover Module. </br> <img src="images/8.png" alt="8" width="500">
5. Go to: Tools > Adjust the marked settings as below. </br> <img src="images/9.png" alt="9" width="320">
6. Go to: Tools > Port > Select the port to which the Arduino is connected (If multiple ports are shown, try connecting one by one to find the actual port).
7. Upload the code.

<b>NOTE:</b> If the upload failed, that means there is a connection loss in the circuit.

----

# Circuit Diagram
<img src="Circuit Diagram.png" alt="1400" width="1400">

----

### Module 1 Manual Control System with Camera
<b> WiFi Name: </b> TESLA Prototype V1 <br>
<b> Password: </b> 12345678 <br>
<b> Web Server: </b> 192.168.4.1

### Module 2 Voice Control System With Object Detection & Emergency Braking System
<b> Bluetooth Name: </b> HC-05 <br>
<b> Password: </b> 1234 or 0000 <br>
<b> Android App: </b> [CLICK HERE](https://play.google.com/store/apps/details?id=com.giristudio.hc05.bluetooth.arduino.control)

### Module 3 Door Security System
<b> RFID UID: </b> E1 24 0C 05


