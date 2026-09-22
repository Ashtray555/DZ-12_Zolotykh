# Run and publish

1. Create a new ESP32-S3 project at https://wokwi.com.
2. Copy `diagram.json` into the diagram editor.
3. Copy `sketch.ino` into the Arduino sketch editor.
4. Start the simulation and open Serial Monitor at 115200 baud.
5. Capture the sequence `25.0C/OFF`, `32.0C/ON`, `25.0C/OFF` and the red LED state.
6. Use **Save** and **Share**, then copy the public project URL into `../wokwi_link.md`.
7. Save the screenshot as `../wokwi_alarm_scenario.png`.

The local firmware deliberately uses deterministic demo points. This makes the key acceptance scenario reproducible in Wokwi; physical-HIL tests would replace the demo source with real DHT22 and MQTT integration.
