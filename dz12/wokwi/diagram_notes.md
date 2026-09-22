# Wokwi wiring notes

- ESP32-S3 GPIO4 -> DHT22 data.
- ESP32-S3 GPIO5 <- photoresistor analog output.
- ESP32-S3 GPIO6 -> red alarm LED through 220 ohm resistor.
- 3V3 and GND are shared by the sensors and LED return.
- The current demonstration firmware emits deterministic values to prove the alarm transition. The sensor pins remain present in the model for the HIL design traceability.
