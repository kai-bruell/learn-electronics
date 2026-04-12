#include <Wire.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  Wire.begin(21, 22);
  Serial.println("\nI2C Scanner");
}

void loop() {
  byte count = 0;
  Serial.println("Scanning...");

  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("  found device at 0x");
      if (addr < 16) Serial.print("0");
      Serial.println(addr, HEX);
      count++;
    }
  }

  if (count == 0) {
    Serial.println("  no devices found");
  } else {
    Serial.print("  total: ");
    Serial.println(count);
  }

  delay(2000);
}
