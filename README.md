# IoTDrowningDetectionSystem
An IoT-based drowning detection system using Arduino, ultrasonic, PIR sensors, and ESP8266. The system monitors movement and pool floor proximity to detect possible drowning incidents and triggers real-time alerts via LCD display and smart dashboard.

# Drowning Detection System  

## 🛠️ Project Overview
An IoT-based system that detects potential drowning incidents using ultrasonic and PIR sensors. It triggers and displays alerts on an LCD when certain threshold values are detected, helping to improve safety in pools and water bodies. It performs real time analysis of data using ThingSpeak and displays the alerts on the connected dashboard.

## 🔧 Components Used
- Arduino Uno
- Ultrasonic Sensor (HC-SR04)
- PIR Motion Sensor (HC-SR501)
- 16x2 LCD Display
- Breadboard and jumper wires
- Power supply
- ESP8266
- Resistors

## ⚙️ How It Works
- The ultrasonic sensor detects proximity to pool floor.
- The PIR sensor checks for motion.
- If a person is detected closer to the pool floor than the threshold value and there is vigorous motion detected, the system considers it a potential drowning.
- The LCD shows the system status.
- The alerts are also provided on smart dashboard

## 📁 File Structure
.
├── drowning-detection.ino       # Arduino code
├── README.md                    # Project overview
├── LICENSE                      # MIT License
└── .gitignore                   # Files to ignore


## 📝 License
This project is licensed under the [MIT License](LICENSE).

## 🙋‍♀️ Author
**Akshita Sondhi**  
Student (ECE), IIIT-Naya Raipur  
Enthusiastic about electronics and AI, and real-world applications of technology.


