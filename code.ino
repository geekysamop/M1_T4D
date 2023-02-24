const int sensor1_pin = 2;
const int sensor2_pin = 3;
const int sensor3_pin = 4;
const int led_pin = 13;

volatile bool sensor1_triggered = false;
volatile bool sensor2_triggered = false;
volatile bool sensor3_triggered = false;
volatile bool led_on = false;

void setup() {
  pinMode(sensor1_pin, INPUT);
  pinMode(sensor2_pin, INPUT);
  pinMode(sensor3_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  
  PCICR |= 0b00000100;
  PCMSK2 |= (1<<PD4);
  
  
  attachInterrupt(digitalPinToInterrupt(sensor1_pin), sensor1_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(sensor2_pin), sensor2_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(sensor3_pin), sensor3_ISR, CHANGE);
  
  // initialize Timer1
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 15624;            // compare match value (1 sec)
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);    // 1024 prescaler
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
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

ISR(TIMER1_COMPA_vect) {
  led_on = !led_on;
  digitalWrite(led_pin, led_on ? HIGH : LOW);
  
  Serial.println("Timer interrupt occurred!");
}
ISR(PCINT2_vect){
	digitalWrite(led_pin, HIGH);
    delay(500);
    digitalWrite(led_pin, LOW);
    delay(500);
    Serial.println("Sensor 3 triggered!");
}
