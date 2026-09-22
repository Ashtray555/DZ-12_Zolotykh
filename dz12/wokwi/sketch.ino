#include <Arduino.h>

namespace {
constexpr int kAlarmLedPin = 2;
constexpr unsigned long kStepDurationMs = 3000;
constexpr unsigned long kHeartbeatIntervalMs = 1000;

struct DemoPoint {
  float temperature;
  float humidity;
  int light;
};

const DemoPoint kDemo[] = {
    {25.0f, 45.0f, 1200},
    {32.0f, 48.0f, 850},
    {25.0f, 45.0f, 1200},
};

size_t demoIndex = 0;
unsigned long lastStep = 0;
unsigned long lastHeartbeat = 0;

void publishState(const DemoPoint& point) {
  const bool alarm = point.temperature >= 30.0f;
  digitalWrite(kAlarmLedPin, alarm ? HIGH : LOW);

  Serial.printf("%.1f %.1f %d %d\n", point.temperature, point.humidity, point.light, alarm ? 1 : 0);

  Serial.printf(
      "SRG_STATUS temperature=%.1fC humidity=%.1f%% light=%d alarm=%s\n",
      point.temperature,
      point.humidity,
      point.light,
      alarm ? "ON" : "OFF");
  Serial.printf("MQTT srg/room/temperature %.1f\n", point.temperature);
  Serial.printf("MQTT srg/room/humidity %.1f\n", point.humidity);
  Serial.printf("MQTT srg/room/light %d\n", point.light);
  Serial.printf(
      "MQTT srg/room/alarm {\"alarm\":%s,\"temperature\":%.1f}\n",
      alarm ? "true" : "false",
      point.temperature);
}
}  // namespace

void setup() {
  pinMode(kAlarmLedPin, OUTPUT);
  digitalWrite(kAlarmLedPin, LOW);
  Serial.begin(115200);
  delay(500);
  Serial.println("SRG_READY sensors_initialized=true wifi=simulated mqtt=simulated");
  publishState(kDemo[demoIndex]);
  lastStep = millis();
}

void loop() {
  if (millis() - lastHeartbeat >= kHeartbeatIntervalMs) {
    lastHeartbeat = millis();
    Serial.println("SRG_HEARTBEAT running=true");
  }

  if (millis() - lastStep >= kStepDurationMs) {
    lastStep = millis();
    demoIndex = (demoIndex + 1) % (sizeof(kDemo) / sizeof(kDemo[0]));
    publishState(kDemo[demoIndex]);
  }
}
