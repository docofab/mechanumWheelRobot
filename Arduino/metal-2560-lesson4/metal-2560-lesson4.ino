/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Arduino Mecanum Omni Direction Wheel Robot Car Bluetooth Testing Lesson
 * Tutorial URL http://osoyoo.com/?p=30022
 * CopyRight www.osoyoo.com 
 */
 
 
 
 
#define MAX_PACKETSIZE 32    //Serial receive buffer
char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;
struct car_status{
  int speed;
  int angle;
  int direct;
};
int move_speed=100 ;

#define MAX_SPEED  250
#define MIN_SPEED  80

#define TURN_SPEED  80
#define SLOW_TURN_SPEED  50
#define BACK_SPEED  80

int buttonState;
char old_status='0';
#define speedPinR 9   //  RIGHT WHEEL PWM pin D45 connect front MODEL-X ENA 
#define RightMotorDirPin1  22    //Front Right Motor direction pin 1 to Front MODEL-X IN1  (K1)
#define RightMotorDirPin2  24   //Front Right Motor direction pin 2 to Front MODEL-X IN2   (K1)                                 
#define LeftMotorDirPin1  26    //Left front Motor direction pin 1 to Front MODEL-X IN3 (  K3)
#define LeftMotorDirPin2  28   //Left front Motor direction pin 2 to Front MODEL-X IN4 (  K3)
#define speedPinL 10   // Left WHEEL PWM pin D7 connect front MODEL-X ENB

#define speedPinRB 11   //  RIGHT WHEEL PWM pin connect Back MODEL-X ENA 
#define RightMotorDirPin1B  5    //Rear Right Motor direction pin 1 to Back MODEL-X IN1 (  K1)
#define RightMotorDirPin2B 6    //Rear Right Motor direction pin 2 to Back MODEL-X IN2 (  K1) 
#define LeftMotorDirPin1B 7    //Rear left Motor direction pin 1 to Back MODEL-X IN3  K3
#define LeftMotorDirPin2B 8  //Rear left Motor direction pin 2 to Back MODEL-X IN4  k3
#define speedPinLB 12    //   LEFT WHEEL  PWM pin D8 connect Rear MODEL-X ENB
int car_direction = 1; // 1 means forward, 0 gear backward

/*motor control*/
void right_shift(int speed_fl_fwd,int speed_rl_bck ,int speed_rr_fwd,int speed_fr_bck) {
  FL_fwd(speed_fl_fwd); 
  RL_bck(speed_rl_bck); 
  RR_fwd(speed_rr_fwd);
  FR_bck(speed_fr_bck);
}
void left_shift(int speed_fl_bck,int speed_rl_fwd ,int speed_rr_bck,int speed_fr_fwd){
   FL_bck(speed_fl_bck);
   RL_fwd(speed_rl_fwd);
   RR_bck(speed_rr_bck);
   FR_fwd(speed_fr_fwd);
}
void go_advance(int left_speed,int right_speed){
   RL_fwd(left_speed);
   RR_fwd(right_speed);
   FR_fwd(right_speed);
   FL_fwd(left_speed); 
}
void go_back(int left_speed,int right_speed){
   RL_bck(left_speed);
   RR_bck(right_speed);
   FR_bck(right_speed);
   FL_bck(left_speed); 
}
void left_turn(int speed){
   RL_bck(speed);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_bck(speed); 
}
void right_turn(int speed){
   RL_fwd(speed);
   RR_bck(speed);
   FR_bck(speed);
   FL_fwd(speed); 
}
void left_back(int speed){
   RL_fwd(0);
   RR_bck(speed);
   FR_bck(speed);
   FL_fwd(0); 
}
void right_back(int speed){
   RL_bck(speed);
   RR_fwd(0);
   FR_fwd(0);
   FL_bck(speed); 
}
void clockwise(int speed){
   RL_fwd(speed);
   RR_bck(speed);
   FR_bck(speed);
   FL_fwd(speed); 
}
void countclockwise(int speed){
   RL_bck(speed);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_bck(speed); 
}
void FR_fwd(int speed)  //front-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1,HIGH);
  digitalWrite(RightMotorDirPin2,LOW); 
  analogWrite(speedPinR,speed);
}
void FR_bck(int speed) // front-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1,LOW);
  digitalWrite(RightMotorDirPin2,HIGH); 
  analogWrite(speedPinR,speed);
}
void FL_fwd(int speed) // front-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1,HIGH);
  digitalWrite(LeftMotorDirPin2,LOW);
  analogWrite(speedPinL,speed);
}
void FL_bck(int speed) // front-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,HIGH);
  analogWrite(speedPinL,speed);
}

void RR_fwd(int speed)  //rear-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1B, HIGH);
  digitalWrite(RightMotorDirPin2B,LOW); 
  analogWrite(speedPinRB,speed);
}
void RR_bck(int speed)  //rear-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1B, LOW);
  digitalWrite(RightMotorDirPin2B,HIGH); 
  analogWrite(speedPinRB,speed);
}
void RL_fwd(int speed)  //rear-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1B,HIGH);
  digitalWrite(LeftMotorDirPin2B,LOW);
  analogWrite(speedPinLB,speed);
}
void RL_bck(int speed)    //rear-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1B,LOW);
  digitalWrite(LeftMotorDirPin2B,HIGH);
  analogWrite(speedPinLB,speed);
}
 
 
void stop_stop()    //Stop
{
    analogWrite(speedPinLB,0);
 analogWrite(speedPinRB,0);
    analogWrite(speedPinL,0);
 analogWrite(speedPinR,0);
}


//Pins initialize
void init_GPIO()
{
  pinMode(RightMotorDirPin1, OUTPUT); 
  pinMode(RightMotorDirPin2, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
 
  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT); 
  pinMode(speedPinR, OUTPUT);
     pinMode(RightMotorDirPin1B, OUTPUT); 
  pinMode(RightMotorDirPin2B, OUTPUT); 
  pinMode(speedPinLB, OUTPUT);  
 
  pinMode(LeftMotorDirPin1B, OUTPUT);
  pinMode(LeftMotorDirPin2B, OUTPUT); 
  pinMode(speedPinRB, OUTPUT);

}

void setup()
{
  init_GPIO();
    Serial.begin(9600);//In order to fit the Bluetooth module's default baud rate, only 9600
   Serial1.begin(9600);
 
 
  stop_stop();
 
}

void loop(){
 do_Uart_Tick();
}

void do_Uart_Tick()
{

  char Uart_Date=0;
  if(Serial1.available()) 
  {
    size_t len = Serial1.available();
    uint8_t sbuf[len + 1];
    sbuf[len] = 0x00;
    Serial1.readBytes(sbuf, len);
    //parseUartPackage((char*)sbuf);
    memcpy(buffUART + buffUARTIndex, sbuf, len);//ensure that the serial port can read the entire frame of data
    buffUARTIndex += len;
    preUARTTick = millis();
    if(buffUARTIndex >= MAX_PACKETSIZE - 1) 
    {
      buffUARTIndex = MAX_PACKETSIZE - 2;
      preUARTTick = preUARTTick - 200;
    }
  }
  car_status cs;
  if(buffUARTIndex > 0 && (millis() - preUARTTick >= 100))//APP send flag to modify the obstacle avoidance parameters
  { //data ready
    buffUART[buffUARTIndex] = 0x00;
    Uart_Date=buffUART[0];
    cs=get_status(buffUART);
    car_direction=cs.angle;
    buffUARTIndex = 0;
  }
  move_speed=cs.speed;
   if (cs.speed>MAX_SPEED) move_speed= MAX_SPEED;
   if (cs.speed<MIN_SPEED) move_speed= MIN_SPEED;

  switch (Uart_Date)    //serial control instructions
  {
    case 'M':  
    if(old_status=='0')
    go_advance(110,110);
    old_status='M';
    delay(55);
    go_advance(move_speed,move_speed);
    break;
    
    case 'L':  
    car_direction=1;
    if (cs.angle<2)
     go_advance(SLOW_TURN_SPEED,TURN_SPEED);
    else  left_turn(SLOW_TURN_SPEED);
    old_status='0';
    break;
    case 'R': 
      car_direction=1;
     if (cs.angle>-2)
      go_advance(TURN_SPEED,SLOW_TURN_SPEED);
     else right_turn(SLOW_TURN_SPEED); 
     old_status='0';
    break;
    case 'B':  
      car_direction=0;
    go_back(BACK_SPEED,BACK_SPEED); 
     old_status='0';
    break;
    case 'X': 
      car_direction=0;
    if (cs.angle>-2)
      go_back(SLOW_TURN_SPEED,TURN_SPEED); 
    else
      left_back(TURN_SPEED);
   old_status='0';
    break;
    case 'Y':  
     car_direction=0;
    if (cs.angle<2)
      go_back(TURN_SPEED,SLOW_TURN_SPEED); 
    else
     right_back(TURN_SPEED); 
    old_status='0';
    break;
     case 'F':  
   //   left_shift(200,150,150,200); //left shift
      left_shift(180,170,190,190) ;//left shift
      delay(800);
      old_status='0';
      break;
    case 'J':       
    //  right_shift(200,150,150,200); //right shift
         right_shift(200,170,170,200); //right shift
      delay(800);
      old_status='0';
      break;
    case 'G': 
       if (car_direction==1) left_shift(0,150,0,150); //left ahead
        else left_shift(150,0,150,0); //left back
    delay(800);
    old_status='0';
    break;
    case 'I': 
     if (car_direction==1) right_shift(180,0,150,0); //right ahead
      else  right_shift(0,130,0,130); //right back
     delay(100);
     old_status='0';
    break;
    case 'E': stop_stop(); 
         old_status='0';
    break;
    default:break;
  }
}

car_status get_status( char buffUART[])
{
  car_status cstatus;
  int index=2;
  if (buffUART[index]=='-'){
    cstatus.angle=-buffUART[index+1]+'0';
    index=index+3;
    
  } else {
   
    cstatus.angle=buffUART[index]-'0';
     index=index+2;
  }
  int currentvalue;
  int spd=0;
  while (buffUART[index]!=',')
  {
    currentvalue=buffUART[index]-'0';
    spd=spd*10+currentvalue;
    index++;
  }
  cstatus.speed=spd;
  index++;
  cstatus.direct=buffUART[index]-'0';
  return cstatus;
}
