# Requirements Traceability Matrix

Coverage target: every requirement in `PRD.md` maps to at least one automated test file and test function.

| Requirement | Test file | Test function | Layer | Expected evidence |
|---|---|---|---|---|
| FR-001 | `tests/smoke/test_boot.py` | `test_all_devices_report_initialized_on_boot()` | Smoke | Serial initialization diagnostics |
| FR-002 | `tests/functional/test_sensor_measurements.py` | `test_temperature_is_read_from_dht22()` | Functional | Temperature status and range |
| FR-003 | `tests/functional/test_sensor_measurements.py` | `test_humidity_is_read_from_dht22()` | Functional | Humidity status and range |
| FR-004 | `tests/functional/test_sensor_measurements.py` | `test_ambient_light_is_read_from_adc()` | Functional | ADC light value |
| FR-005 | `tests/functional/test_temperature_alarm.py` | `test_alarm_activates_at_temperature_threshold()` | Functional/HIL | LED ON, status alarm true, MQTT alarm true |
| FR-006 | `tests/functional/test_temperature_alarm.py` | `test_alarm_deactivates_below_temperature_threshold()` | Functional/HIL | LED OFF, status alarm false, MQTT alarm false |
| FR-007 | `tests/smoke/test_connectivity_smoke.py` | `test_device_connects_to_configured_wifi()` | Smoke | Connected state and IP address |
| FR-008 | `tests/hil/test_wifi_recovery.py` | `test_device_reconnects_after_wifi_disconnect()` | HIL | Reconnected state without reset |
| FR-009 | `tests/mqtt/test_temperature_topic.py` | `test_temperature_is_published_on_temperature_topic()` | MQTT | Message on `srg/room/temperature` |
| FR-010 | `tests/mqtt/test_humidity_topic.py` | `test_humidity_is_published_on_humidity_topic()` | MQTT | Message on `srg/room/humidity` |
| FR-011 | `tests/mqtt/test_light_topic.py` | `test_light_is_published_on_light_topic()` | MQTT | Message on `srg/room/light` |
| FR-012 | `tests/functional/test_mqtt_payloads.py` | `test_alarm_payload_matches_local_alarm_state()` | MQTT/HIL | JSON schema and LED consistency |
| NFR-001 | `tests/hil/test_startup_timing.py` | `test_device_reaches_ready_state_within_five_seconds()` | HIL | Reset-to-ready timestamp |
| NFR-002 | `tests/mqtt/test_telemetry_cadence.py` | `test_complete_telemetry_set_is_published_within_ten_seconds()` | MQTT | 60-second timestamped capture |
| NFR-003 | `tests/hil/test_wifi_recovery.py` | `test_mqtt_telemetry_resumes_after_wifi_recovery()` | HIL/MQTT | Publication after reconnect without reset |

## Coverage summary

| Requirement group | Requirements | Covered | Coverage |
|---|---:|---:|---:|
| Functional | 12 | 12 | 100% |
| Non-functional | 3 | 3 | 100% |
| **Total** | **15** | **15** | **100%** |

The matrix describes the intended automated test contract. Execution reports must identify whether a test ran against physical HIL hardware or the Wokwi simulation.
