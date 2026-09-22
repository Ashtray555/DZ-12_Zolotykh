# Product Requirements Document: Smart Room Guardian

## 1. Product Vision

**Smart Room Guardian (SRG)** is an ESP32-S3-based IoT device that monitors the environmental conditions of a room and warns the user when the temperature reaches a dangerous level. The device reads temperature and humidity from a DHT22 sensor, reads ambient light from a photoresistor, drives a local alarm LED, and publishes telemetry and alarm state through Wi-Fi and MQTT.

The target user is a homeowner or facility operator who needs a simple, observable, and recoverable room-monitoring device.

### Product purpose

The purpose of SRG is to provide continuous room-condition monitoring and an immediate local and MQTT notification when the temperature reaches the safety threshold.

## 2. Scope

### In scope

- Periodic temperature, humidity, and ambient-light acquisition.
- Local high-temperature alarm with a threshold of 30.0 degrees C.
- Wi-Fi connection and automatic recovery after a disconnect.
- MQTT publication of sensor values and alarm state.
- Serial diagnostics for HIL automation.

### Out of scope

- Cloud dashboard implementation.
- Battery management.
- Actuators other than the alarm LED.
- Security hardening beyond using configured Wi-Fi and MQTT credentials.

## 3. System Architecture

```text
DHT22 + photoresistor -> ESP32-S3 firmware -> alarm LED
                                  |
                         Wi-Fi / MQTT telemetry
                                  |
                         MQTT broker / test client

Test PC / Pytest <-> USB/UART <-> ESP32-S3
Test PC / HIL controller -> sensor/environment stimulation
```

The HIL controller stimulates or emulates sensor conditions, controls the DUT through a serial command channel, observes the alarm LED and serial diagnostics, and validates MQTT messages.

## 4. Technical Stack

| Layer | Technology |
|---|---|
| MCU | ESP32-S3 DevKit |
| Temperature/humidity sensor | DHT22 |
| Ambient light sensor | Photoresistor connected to ADC |
| Local indication | Red LED with current-limiting resistor |
| Firmware | C++ with Arduino framework |
| Connectivity | 2.4 GHz Wi-Fi |
| Messaging | MQTT, JSON payloads |
| Diagnostics/control | USB/UART serial at 115200 baud |
| Automation | Python, pytest, PySerial, paho-mqtt |
| Simulation | Wokwi |
| HIL reporting | JUnit XML and captured serial/MQTT logs |

## 5. Interfaces and Data Contract

### MQTT topics

- `srg/room/temperature` — numeric temperature in degrees C.
- `srg/room/humidity` — numeric relative humidity in percent.
- `srg/room/light` — integer ADC-derived light level from 0 to 4095.
- `srg/room/alarm` — JSON object containing `alarm`, `temperature`, and `timestamp_ms`.

Example alarm payload:

```json
{"alarm":true,"temperature":32.4,"timestamp_ms":123456}
```

### Serial test commands

- `SIM:TEMP=<value>` — inject a simulated temperature for HIL/Wokwi demonstration.
- `SIM:HUM=<value>` — inject a simulated humidity value.
- `SIM:LIGHT=<value>` — inject a simulated light value.
- `STATUS` — print the current state as a machine-readable line.

## 6. Functional Requirements

| ID | Requirement | Acceptance criteria |
|---|---|---|
| FR-001 | The device shall initialize all configured sensors and outputs during startup. | Startup diagnostics report DHT22, light input, alarm LED, and network services as initialized. |
| FR-002 | The device shall measure temperature from the DHT22. | A valid DHT22 temperature is reported in degrees C and appears in the status/telemetry record. |
| FR-003 | The device shall measure relative humidity from the DHT22. | A valid DHT22 humidity value is reported as percent and appears in the status/telemetry record. |
| FR-004 | The device shall measure ambient light level. | An ADC light value in the configured 0..4095 range is reported. |
| FR-005 | The device shall activate the alarm when temperature is 30.0 degrees C or higher. | At 30.0 degrees C or above, the alarm state becomes `true` and the red LED is ON within one sampling cycle. |
| FR-006 | The device shall deactivate the alarm when temperature is below 30.0 degrees C. | Below 30.0 degrees C, the alarm state becomes `false` and the red LED is OFF within one sampling cycle. |
| FR-007 | The device shall connect to the configured Wi-Fi network. | The serial log reports a successful connection and the device obtains an IP address. |
| FR-008 | The device shall reconnect to Wi-Fi after a connection loss. | After a forced disconnect, the device retries without reboot and returns to the connected state. |
| FR-009 | The device shall publish temperature data via MQTT. | A temperature message is received on `srg/room/temperature` with the current reading. |
| FR-010 | The device shall publish humidity data via MQTT. | A humidity message is received on `srg/room/humidity` with the current reading. |
| FR-011 | The device shall publish the ambient-light level via MQTT. | A light message is received on `srg/room/light` with the current ADC-derived value. |
| FR-012 | The device shall publish alarm state via MQTT. | A valid JSON alarm message is received on `srg/room/alarm` and matches the local LED state. |

## 7. Non-functional Requirements

| ID | Requirement | Acceptance criteria |
|---|---|---|
| NFR-001 | The device shall complete startup within 5 seconds. | From reset release, the ready diagnostic is emitted within 5 seconds under nominal network conditions. |
| NFR-002 | The device shall publish a complete telemetry set at least once every 10 seconds. | The test client observes temperature, humidity, light, and alarm updates with no interval greater than 10 seconds for 60 seconds. |
| NFR-003 | The device shall recover from Wi-Fi disconnection without manual restart. | A Wi-Fi fault injection does not require a reset; reconnect and MQTT publication resume automatically. |

## 8. Critical Use Cases

### UC-01: Normal environmental monitoring

1. Power on the device.
2. The device initializes sensors and connects to Wi-Fi/MQTT.
3. The device samples all inputs and publishes telemetry.
4. The alarm LED remains OFF while temperature is below 30.0 degrees C.

### UC-02: High-temperature alarm

1. HIL or Wokwi injects 32.0 degrees C.
2. The next sampling cycle detects the threshold crossing.
3. The alarm LED turns ON.
4. The device publishes `alarm=true` with the measured temperature.

### UC-03: Return to safe temperature

1. The simulated temperature falls below 30.0 degrees C.
2. The next sampling cycle clears the alarm.
3. The LED turns OFF and the MQTT alarm state becomes `false`.

### UC-04: Wi-Fi recovery

1. The test controller interrupts the access point or Wi-Fi connection.
2. The device logs the disconnect and retries in the background.
3. The connection is restored without a reboot.
4. MQTT telemetry resumes.

## 9. Quality Gates

- Every requirement has at least one mapped automated test in `traceability_matrix.md`.
- The HIL design can stimulate inputs and observe local and MQTT outputs.
- The Wokwi demonstration visibly proves the critical alarm scenario.
- No requirement is considered passed solely from a simulated result when physical-HIL evidence is required; the test report records the execution target.
