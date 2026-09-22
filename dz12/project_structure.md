```text
tests/srg-qa/
├── README.md
├── pyproject.toml
├── pytest.ini
├── requirements.txt
├── config/
│   ├── default.yaml
│   ├── hil.yaml
│   └── mqtt.yaml
├── src/
│   └── srg_testkit/
│       ├── __init__.py
│       ├── device_driver.py
│       ├── hil_controller.py
│       ├── mqtt_client.py
│       ├── serial_protocol.py
│       └── models.py
├── tests/
│   ├── conftest.py
│   ├── fixtures/
│   │   ├── sensor_profiles.py
│   │   ├── mqtt_fixtures.py
│   │   └── hil_fixtures.py
│   ├── smoke/
│   │   ├── test_boot.py
│   │   └── test_connectivity_smoke.py
│   ├── functional/
│   │   ├── test_sensor_measurements.py
│   │   ├── test_temperature_alarm.py
│   │   └── test_mqtt_payloads.py
│   ├── hil/
│   │   ├── test_sensor_stimulation.py
│   │   ├── test_wifi_recovery.py
│   │   └── test_startup_timing.py
│   └── mqtt/
│       ├── test_temperature_topic.py
│       ├── test_humidity_topic.py
│       ├── test_light_topic.py
│       ├── test_alarm_topic.py
│       └── test_telemetry_cadence.py
├── reports/
│   ├── junit.xml
│   ├── serial.log
│   └── mqtt_capture.jsonl
└── tools/
    ├── discover_device.py
    └── package_results.py
```
