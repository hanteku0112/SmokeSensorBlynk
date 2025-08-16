# SmokeSensorBlynk
IoT Gas/Smoke Leak Detector using ESP32, MQ-2 sensor and Blynk.
This my video for the project: https://drive.google.com/drive/u/0/folders/1r_ufwFTYMfIkPhLvbecYCKfGfkZTPCLg
This project can still have some improvements, such as integrating a buzzer to warn when the gas value is greater than the threshold, or a control relay or a mini pump to automatically pump water when the temperature and gas values are significant. (This will require one more heat sensor.) However, due to a lack of hardware like a transistor, an external 5V supply, and a broken breadboard, this is the best shot I can give to this project.
## Future Improvements
This project can be further enhanced with the following features:
- **Buzzer integration**: add a buzzer to provide an audible alarm when gas levels exceed the safety threshold.  
- **Relay control**: integrate a relay to automatically cut off or control external electrical appliances (e.g., fan or valve) when a gas leak is detected.  
- **Mini water pump**: connect a small pump to spray water automatically when both temperature and gas values reach critical levels (requires adding a temperature sensor).  
- **More stable hardware setup**: use external 5V power supply, transistor drivers for actuators, and a reliable PCB instead of a temporary breadboard for better durability.  
