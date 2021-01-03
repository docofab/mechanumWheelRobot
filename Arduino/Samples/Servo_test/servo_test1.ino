#include <Servo.h>

Servo servo_5;

void setup()
{
  servo_5.attach(5, 500, 2500);

}

void loop()
{
  servo_5.write(90);
  servo_5.write(120);
  delay(1000); // Wait for 1000 millisecond(s)
  servo_5.write(170);
  delay(3000); // Wait for 3000 millisecond(s)
  servo_5.write(90);
  delay(1000); // Wait for 1000 millisecond(s)
  servo_5.write(40);
  delay(1000); // Wait for 1000 millisecond(s)
  servo_5.write(0);
  delay(1000); // Wait for 1000 millisecond(s)
  servo_5.write(90);
  delay(3000); // Wait for 3000 millisecond(s)
}
