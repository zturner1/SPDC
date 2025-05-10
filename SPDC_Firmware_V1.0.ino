/*
  SPDC_Firmware_v1.0.ino
  Sealed Pulse Dosing Cell (SPDC)
  Developed by Zachary Turner – 2025

  Description:
  Precise liquid dispensing system using a diaphragm pump, solenoid valve,
  flow sensor (YF-S401), and check valve. Accepts serial commands to dose
  specific volumes of liquid based on real-time flow sensor pulse feedback.

  Commands:
    on             - Turns on pump and solenoid (manual mode)
    off            - Turns off pump and solenoid
    dispense <ml>  - Dispenses exact volume in milliliters, then stops

  Notes:
    Calibration Factor may need tuning for your specific sensor and tubing.
*/

const byte FLOW_SENSOR_PIN = 3;
const byte RELAY_PIN       = 2;

const float CALIBRATION_FACTOR = 35.5; // pulses/sec per L/min (tuned value)
volatile unsigned int pulseCount = 0;

unsigned long lastReportTime = 0;
float flowRate     = 0;
float totalLiters  = 0;

String inputString   = "";
bool stringComplete  = false;

bool dispensing      = false;
float targetLiters   = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Start with pump OFF

  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, RISING);

  Serial.println("SPDC Ready. Type 'on', 'off', or 'dispense <ml>' to begin.");
}

void loop() {
  unsigned long currentMillis = millis();

  // Report flow every second
  if (currentMillis - lastReportTime >= 1000) {
    detachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN));

    flowRate = ((float)pulseCount / CALIBRATION_FACTOR); // in L/min
    float litersThisInterval = flowRate / 60.0;
    totalLiters += litersThisInterval;

    Serial.print("Flow rate: ");
    Serial.print(flowRate, 2);
    Serial.print(" L/min\tTotal: ");
    Serial.print(totalLiters, 3);
    Serial.println(" L");

    pulseCount = 0;
    lastReportTime = currentMillis;

    // Check if target reached during dispense
    if (dispensing && totalLiters >= targetLiters) {
      digitalWrite(RELAY_PIN, LOW);
      Serial.print("Target reached: ");
      Serial.print(targetLiters * 1000);
      Serial.println(" mL dispensed.");
      dispensing = false;
    }

    attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, RISING);
  }

  // Handle incoming serial commands
  if (stringComplete) {
    inputString.trim();
    inputString.toLowerCase();

    if (inputString == "on") {
      digitalWrite(RELAY_PIN, HIGH);
      dispensing = false;
      Serial.println("Pump turned ON.");
    } else if (inputString == "off") {
      digitalWrite(RELAY_PIN, LOW);
      dispensing = false;
      Serial.println("Pump turned OFF.");
    } else if (inputString.startsWith("dispense")) {
      int spaceIndex = inputString.indexOf(' ');
      if (spaceIndex > 0) {
        String mlString = inputString.substring(spaceIndex + 1);
        int ml = mlString.toInt();
        if (ml > 0) {
          targetLiters = totalLiters + (ml / 1000.0);
          digitalWrite(RELAY_PIN, HIGH);
          dispensing = true;
          Serial.print("Dispensing ");
          Serial.print(ml);
          Serial.println(" mL...");
        } else {
          Serial.println("Invalid amount. Use: dispense 100");
        }
      } else {
        Serial.println("Missing amount. Use: dispense 100");
      }
    } else {
      Serial.println("Unknown command. Use 'on', 'off', or 'dispense <ml>'");
    }

    inputString = "";
    stringComplete = false;
  }
}

// Interrupt service routine for pulse counting
void pulseCounter() {
  pulseCount++;
}

// Handle serial input buffering
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n' || inChar == '\r') {
      if (inputString.length() > 0) stringComplete = true;
    } else {
      inputString += inChar;
    }
  }
}
