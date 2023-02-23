const int sensor1_pin = 2;
const int sensor2_pin = 3;
const int sensor3_pin = 4;
const int led_pin = 13;

volatile bool sensor1_triggered = false;
volatile bool sensor2_triggered = false;
volatile bool sensor3_triggered = false;

void setup() {
  pinMode(sensor1_pin, INPUT);
  pinMode(sensor2_pin, INPUT);
  pinMode(sensor3_pin, INPUT);
  
  pinMode(led_pin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(sensor1_pin), sensor1_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(sensor2_pin), sensor2_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(sensor3_pin), sensor3_ISR, CHANGE);
  
  Serial.begin(9600);
}

void loop() {
  if (sensor1_triggered || sensor2_triggered || sensor3_triggered) {
    digitalWrite(led_pin, HIGH);
    delay(500);
    digitalWrite(led_pin, LOW);
    delay(500);
    
    if (sensor1_triggered) {
      Serial.println("Sensor 1 triggered!");
      sensor1_triggered = false;
    }
    if (sensor2_triggered) {
      Serial.println("Sensor 2 triggered!");
      sensor2_triggered = false;
    }
    if (sensor3_triggered) {
      Serial.println("Sensor 3 triggered!");
      sensor3_triggered = false;
    }
  }
}

void sensor1_ISR() {
  sensor1_triggered = true;
}

void sensor2_ISR() {
  sensor2_triggered = true;
}

void sensor3_ISR() {
  sensor3_triggered = true;
}
