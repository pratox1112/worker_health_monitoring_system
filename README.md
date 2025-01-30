# TinyML-Based Worker Health Monitoring

## Overview
This project implements a **TinyML-powered health monitoring system** designed for field and mining workers. The system uses **embedded devices** and **edge computing** to monitor key health parameters, ensuring real-time safety and proactive intervention in hazardous work environments.

---

## Features
- **Real-Time Health Monitoring**: Tracks heart rate, body temperature, oxygen levels, and posture of workers.
- **Edge Computing**: Uses a TinyML model deployed on an ESP32 microcontroller for local anomaly detection.
- **IoT Integration**: Employs LoRa communication for long-distance data transmission in low-connectivity environments.
- **Mobile Alerts**: Notifies managers through a dedicated mobile application when abnormalities are detected.
- **Low Power Consumption**: Optimized for energy efficiency, suitable for remote field applications.

---

## System Architecture
1. **Sensors**: Collect health parameters (e.g., MAX30100 for heart rate, DHT11 for temperature, accelerometer for posture).
2. **Embedded Device**: ESP32 microcontroller runs the TinyML model for real-time predictions.
3. **Communication Framework**: LoRa-based long-range transmission to a central LoRaWAN hub.
4. **Data Processing**: MQTT protocol facilitates seamless data exchange between devices and the server.
5. **Mobile Application**: Displays health data and provides real-time alerts for abnormalities.

---

## Technologies Used
- **Hardware**: ESP32 microcontroller, MAX30100 sensor, DHT11 sensor, LoRa HC-12 module.
- **Software**: Python, TensorFlow Lite, Arduino IDE, Google Colab.
- **Communication**: LoRaWAN, MQTT protocol.
- **Mobile Development**: React Native for mobile app.

---

## Installation

### Hardware Setup
1. Connect the MAX30100, DHT11, and accelerometer sensors to the ESP32 microcontroller.
2. Configure the LoRa module for communication.
3. Power the system using a suitable DC power supply.

### Software Setup
1. Install the required dependencies:
   - Arduino IDE
   - Python (for model training and deployment)
2. Train and convert the TinyML model to TensorFlow Lite format.
3. Flash the firmware to the ESP32 microcontroller.
4. Set up the MQTT broker and LoRaWAN gateway.
5. Deploy the mobile app using React Native.

---

## Usage
1. Power on the embedded system and ensure all sensors are connected.
2. Monitor real-time worker health data via the mobile app.
3. Receive alerts for abnormal conditions and take proactive measures.

---

## Future Enhancements
- Add support for additional health parameters like ECG and SpO2 levels.
- Enhance machine learning models for higher accuracy.
- Integrate GPS for worker location tracking.
- Improve the mobile app interface with advanced analytics.

---

## Contributors
- **Pratosh Karthikeyan**
- **[Other team members, if applicable]**

---

## License
This project is licensed under the [MIT License](LICENSE).

---

## Contact
For questions or feedback, please contact:
**Pratosh Karthikeyan** - pratosh2002@gmail.com
