#define TRIG1   9
#define ECHO1  10
#define TRIG2  11
#define ECHO2  12
#define BUZZER 8

#define MAX_DIST  150  
#define MIN_DIST    5   

long readDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 30000); 
  if (duration == 0) return 999;              
  return duration * 0.034 / 2;                
}

void setup() {
  pinMode(TRIG1, OUTPUT); pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT); pinMode(ECHO2, INPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long d1 = readDistance(TRIG1, ECHO1);
  long d2 = readDistance(TRIG2, ECHO2);
  long d = min(d1, d2);   

  Serial.print("D1: "); Serial.print(d1);
  Serial.print("  D2: "); Serial.print(d2);
  Serial.print("  Min: "); Serial.println(d);
  
  if (d < 150) {
    // closer = shorter beep interval = higher intensity
    int interval = map(d, 0, 150, 30, 600);
    interval = constrain(interval, 30, 600);
    digitalWrite(BUZZER, HIGH);
    delay(interval);
    digitalWrite(BUZZER, LOW);
    delay(interval);
  } else {
    digitalWrite(BUZZER, LOW);
    delay(50);
  }
}
