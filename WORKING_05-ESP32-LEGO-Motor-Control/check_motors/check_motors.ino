#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// PCA9685 #1 (0x40) -> Richtungssignale (IN1/IN2)
// PCA9685 #2 (0x41) -> Geschwindigkeit  (PWM)
Adafruit_PWMServoDriver pcaDir   = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pcaSpeed = Adafruit_PWMServoDriver(0x41);

const uint8_t NUM_MOTORS = 7;
const uint16_t PWM_FREQ_HZ = 1000;
const uint16_t PWM_MAX = 4095;

const uint32_t RAMP_MS  = 3000;
const uint32_t PAUSE_MS = 1000;
const uint16_t RAMP_STEPS = 100;

void pcaWrite(Adafruit_PWMServoDriver &pca, uint8_t ch, uint16_t value) {
  pca.setPWM(ch, 0, value);
}

void setDirection(uint8_t motor, bool forward) {
  uint8_t in1 = motor * 2;
  uint8_t in2 = motor * 2 + 1;
  pcaWrite(pcaDir, in1, forward ? PWM_MAX : 0);
  pcaWrite(pcaDir, in2, forward ? 0 : PWM_MAX);
}

void setSpeed(uint8_t motor, uint16_t value) {
  pcaWrite(pcaSpeed, motor, value);
}

void stopAllMotors() {
  for (uint8_t m = 0; m < NUM_MOTORS; m++) {
    setSpeed(m, 0);
    pcaWrite(pcaDir, m * 2,     0);
    pcaWrite(pcaDir, m * 2 + 1, 0);
  }
}

void rampMotor(uint8_t motor) {
  Serial.print("Motor ");
  Serial.print(motor);
  Serial.println(": ramping 0 -> 100%");

  setDirection(motor, true);

  for (uint16_t step = 0; step <= RAMP_STEPS; step++) {
    uint16_t value = (uint32_t)PWM_MAX * step / RAMP_STEPS;
    setSpeed(motor, value);
    delay(RAMP_MS / RAMP_STEPS);
  }

  setSpeed(motor, 0);
  setDirection(motor, true);
  pcaWrite(pcaDir, motor * 2,     0);
  pcaWrite(pcaDir, motor * 2 + 1, 0);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  delay(200);

  Wire.begin(21, 22);

  pcaDir.begin();
  pcaDir.setPWMFreq(PWM_FREQ_HZ);

  pcaSpeed.begin();
  pcaSpeed.setPWMFreq(PWM_FREQ_HZ);

  stopAllMotors();

  Serial.println("\ncheck-motors ready");
  delay(500);
}

void loop() {
  for (uint8_t m = 0; m < NUM_MOTORS; m++) {
    rampMotor(m);
    delay(PAUSE_MS);
  }
  Serial.println("--- cycle complete ---\n");
  delay(2000);
}
