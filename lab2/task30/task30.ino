#define LED1 3
#define LED2 5

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
}

const int period = 4096;
void loop() {
    for (int i = 0; i <= 510; i++) {
    delay(16);
    int brightness1 = i;
    int brightness2 = i / 2;
    int highTime1 = period * brightness1 / 255;
    int highTime2 = period * brightness2 / 255;
    for (int j = 0; j <= 100; j++) {
      if (brightness1 >= brightness2){
        digitalWrite(LED1, 1);
        digitalWrite(LED2, 1);
        delayMicroseconds(10*(highTime2));
        digitalWrite(LED2, 0);
        delayMicroseconds(10*(highTime1 - highTime2));
        digitalWrite(LED1, 0);
        delayMicroseconds(10*(period - highTime1));
      } else {
        digitalWrite(LED2, 1);
        digitalWrite(LED1, 1);
        delayMicroseconds(10*(highTime1));
        digitalWrite(LED1, 0);
        delayMicroseconds(10*(highTime2 - highTime1));
        digitalWrite(LED2, 0);
        delayMicroseconds(10*(period - highTime2));
      }
    }
  }
}
