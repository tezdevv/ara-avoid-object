#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>

Servo servoMapping;
VL53L0X lidar1;

#define r1 7
#define r2 4
#define enR 6

#define l1 2
#define l2 3
#define enL 5

float rPwm = 89.5;
int lPwm = 81;

//spesifikasi
float kecepatanRobot = 0.58;
float jariJariRobot = 3.5;

//mapping
int dataMap[16];

int iServo = 0;
bool scanState = true;
bool servoDirection = true;

void setup() {
Serial.begin(9600);
Wire.begin();

lidar1.init();

pinMode(r1, OUTPUT);
pinMode(r2, OUTPUT);
pinMode(l1, OUTPUT);
pinMode(l2, OUTPUT);

pinMode(enR, OUTPUT);
pinMode(enL, OUTPUT);

servoMapping.attach(8);
servoMapping.write(0);
}

void loop() {

  otonomMode();

}

void otonomMode() {

  if (scanState) {

    if (servoDirection) {
      for(iServo; iServo < 15; iServo++) {
        mapping(iServo);

        if (hcM = x) {
          stop();
        }
      }

      for (int i = 0; i < 15; i++) {
        Serial.print("Data ke-");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.println(dataMap[i]);
      }

      servoDirection = false;

      scanState = false;
    } else {
      for(iServo; iServo > 0; iServo--) {
        mapping(iServo - 1);
      }

      for (int i = 15; i > 0; i--) {
        Serial.print("Data ke-");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(dataMap[i - 1]);
      }

      servoDirection = true;

      scanState = false;
    }


  } else {
    int panjangData = sizeof(dataMap) / sizeof(dataMap[0]);
    int maxNilai = dataMap[0];
    int maxIndex = 0;

    for (int i = 1; i < panjangData; i++) {
      if (dataMap[i] > maxNilai) {
        maxNilai = dataMap[i];
        maxIndex = i;
      }
    }

    if (dataMap[8] >= 300) {
        forward(rPwm, lPwm);
        scanState = true;
    } else {
      if (maxNilai >= 300) {
        int normalizeDegree;
        int normalizeDirection;

        if ((maxIndex * 12) >= 90) {
          normalizeDegree = (maxIndex * 12) - 90;
          normalizeDirection = (maxIndex * 12) - 90;
        } else {
          normalizeDegree = -1 * ((maxIndex * 12) - 90);
          normalizeDirection = (maxIndex * 12) - 90;
        }

        decisionMove(normalizeDegree, normalizeDirection);
      } else {
        decisionMove(180, 1);
      }
    }

  }

}

void mapping(int index) {
  servoMapping.write((index * 12));
  int range = lidar1.readRangeSingleMillimeters();
  dataMap[index] = range;
}

void decisionMove(int de, int di) {
  float direction = di;
  float targetDegree = de;
  float lingkarRobot = 0.22;
  float waktuTempuhSempurna = 0.38; // s
  float waktutPutarTarget = (targetDegree / 360) * 500; // mils

  if (hcM = x) {
    stop();
  } else {
    if (direction > 0) {
      left(rPwm, lPwm);
      Serial.print("kiri");
      Serial.println(targetDegree);
      Serial.println(waktutPutarTarget);
      delay(waktutPutarTarget);
      stop();
    } else if (direction < 0) {
      right(rPwm, lPwm);
      Serial.print("kanan");
      Serial.println(targetDegree);
      Serial.println(waktutPutarTarget);
      delay(waktutPutarTarget);
      stop();
    } else if (targetDegree == 0) {
      Serial.print("lurus");
      Serial.println(targetDegree);
      forward(rPwm, lPwm);
    }
  }

  scanState = true;

}

void decisionStop() {
  float hcR =;
  float hcM =;
  float hcL =;

  if (hcR)
}

void forward(float rPwm, int lPwm) {
  digitalWrite(r1,HIGH);
  digitalWrite(r2,LOW);
  digitalWrite(l1,HIGH);
  digitalWrite(l2,LOW);
  analogWrite(enR, rPwm);
  analogWrite(enL, lPwm);
}

void stop() {
  digitalWrite(r1,LOW);
  digitalWrite(r2,LOW);
  digitalWrite(l1,LOW);
  digitalWrite(l2,LOW);
  analogWrite(enR, 0);
  analogWrite(enL, 0);
}

void backward(int rPwm, int lPwm) {
  digitalWrite(r1,LOW);
  digitalWrite(r2,HIGH);
  digitalWrite(l1,LOW);
  digitalWrite(l2,HIGH);
  analogWrite(enR, rPwm);
  analogWrite(enL, lPwm);
}

void right(int rPwm, int lPwm) {
  digitalWrite(r1,LOW);
  digitalWrite(r2,HIGH);
  digitalWrite(l1,HIGH);
  digitalWrite(l2,LOW);
  analogWrite(enR, rPwm);
  analogWrite(enL, lPwm);
}

void left(int rPwm, int lPwm) {
  digitalWrite(r1,HIGH);
  digitalWrite(r2,LOW);
  digitalWrite(l1,LOW);
  digitalWrite(l2,HIGH);
  analogWrite(enR, rPwm);
  analogWrite(enL, lPwm);
}
