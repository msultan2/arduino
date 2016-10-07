#include <AFMotor.h>
#include <NewPing.h>

//int Speed;

AF_DCMotor motor_FR(1);
AF_DCMotor motor_FL(2);
AF_DCMotor motor_BR(4);
AF_DCMotor motor_BL(3);

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, ULTRA_MAX_DISTANCE);
NewPing ultraLeft(18,19);   // (Trig PIN,Echo PIN)
NewPing ultraRight(14,15);  // (Trig PIN,Echo PIN)
NewPing ultraFront(16,17);  // (Trig PIN,Echo PIN)
int ULTRA_MAX_DISTANCE=200;

int MAX_RANGE=40;
int MIN_RANGE=25;
int DELAY_In_TURN=28;
int ALERT_OBSTACLE=70;

int MAX_SPEED=90;
int TURN_SPEED=130;
int NORMAL_SPEED=60;
int BACKWARD_SPEED=70;

int MARGIN_DISTANCE=20;

int HangCount=0;

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Motors test!");
  motor_FR.setSpeed(MAX_SPEED);
  motor_FL.setSpeed(MAX_SPEED);
  motor_BR.setSpeed(MAX_SPEED);
  motor_BL.setSpeed(MAX_SPEED);
  
  Serial.print("Right Sensor: ");
  Serial.println(Get_Distance(ultraRight));
  
  Serial.print("Left Sensor: ");
  Serial.println(Get_Distance(ultraLeft));
  
  Serial.print("Front Sensor: ");
  Serial.println(Get_Distance(ultraFront));
}
void loop() {
Serial.println(Get_Distance(ultraRight));
}
int Get_Distance(NewPing UltaSonic){
  delay(70);
  unsigned int uS = UltaSonic.ping(); // Send ping, get ping time in microseconds (uS).
  int Distance=uS / US_ROUNDTRIP_CM;
  if (Distance==0){
    Distance=ULTRA_MAX_DISTANCE;
  }
  return (Distance); // Convert ping time to distance in cm and print result (0 = outside set distance range)
}
