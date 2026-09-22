# DZ-12: Smart Room Guardian

This package contains the HIL and E2E automation design for **Smart Room Guardian (SRG)**, an ESP32-S3 IoT device that monitors temperature, humidity, and ambient light and raises a local/MQTT alarm at 30.0 degrees C.

## Deliverables

- [PRD.md](PRD.md) — product vision, interfaces, functional and non-functional requirements.
- [stand_diagram.png](stand_diagram.png) — HIL architecture diagram.
- [project_structure.md](project_structure.md) — proposed automated-test project tree.
- [traceability_matrix.md](traceability_matrix.md) — requirement-to-test traceability with 100% planned coverage.
- [wokwi_link.md](wokwi_link.md) — Wokwi publication and evidence record.
- [wokwi/](wokwi/) — local Wokwi model files for the high-temperature alarm scenario.

## Key scenario

The demonstration drives the device through:

```text
25 degrees C -> alarm OFF
32 degrees C -> alarm ON
25 degrees C -> alarm OFF
```

The state transitions are visible on the red LED and in the Serial Monitor.

## Wokwi

Open the files in `wokwi/` in a Wokwi ESP32 project, start the simulation, and use the Serial Monitor. The firmware includes a deterministic demonstration mode so the alarm scenario can be observed without a physical DHT22.

After saving the project in your Wokwi account, copy the public URL and add an execution screenshot to [wokwi_link.md](wokwi_link.md).

## HIL architecture

The real HIL flow uses a test PC running pytest and a HIL controller. The controller stimulates sensor inputs, communicates with the ESP32-S3 over USB/UART, observes the LED and serial diagnostics, and validates telemetry received from the MQTT broker.

## Packaging

The submission archive must be named `DZ-12_Zolotykh.zip` and contain the `dz12/` directory at its root.
