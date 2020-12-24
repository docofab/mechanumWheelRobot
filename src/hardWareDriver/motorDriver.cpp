/**
 * @file  motorDriver.cpp
 * @brief モーターを動作させるものはここに記載
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#include "motorDriver.h"

/**
 * @brief モーター部分の初期化
 * @return true:初期化成功 false:失敗
 * 
 */
bool motorInitialize(){
  /* ハードウェアピンの初期化 */
  motorHWpinInitilalize();
}

/**
 * @brief ピン部分の初期化
 * @return true:現状必ずtrue、エンコーダ初期化などの際に機能追加する
 */
bool motorHWpinInitilalize(){
  /*setup L298N pin mode*/
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
  return true;
}

void go_Advance()  //Forward
{
FR_fwd();
FL_fwd();
RR_fwd();
RL_fwd();
}

void go_Left()  //Turn left
{
FR_fwd();
FL_bck();
RR_fwd();
RL_bck();
}
void go_Right()  //Turn right
{
FR_bck();
FL_fwd();
RR_bck();
RL_fwd();
}
void go_Back()  //Reverse
{
FR_bck();
FL_bck();
RR_bck();
RL_bck();
}
 
 

void stop_Stop()    //Stop
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2,LOW);
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,LOW);
  digitalWrite(RightMotorDirPin1B, LOW);
  digitalWrite(RightMotorDirPin2B,LOW);
  digitalWrite(LeftMotorDirPin1B,LOW);
  digitalWrite(LeftMotorDirPin2B,LOW);
  set_Motorspeed(0,0,0,0);
}

/*set motor speed */
void set_Motorspeed(int leftFront,int rightFront,int leftBack,int rightBack)
{
 analogWrite(speedPinL,leftFront); 
 analogWrite(speedPinR,rightFront); 
 analogWrite(speedPinLB,leftBack);  
 analogWrite(speedPinRB,rightBack);

}

void FR_fwd()  //front-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1,HIGH);
  digitalWrite(RightMotorDirPin2,LOW); 
}
void FR_bck() // front-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1,LOW);
  digitalWrite(RightMotorDirPin2,HIGH); 
}
void FL_fwd() // front-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1,HIGH);
  digitalWrite(LeftMotorDirPin2,LOW);
}
void FL_bck() // front-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,HIGH);
}

void RR_fwd()  //rear-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1B,HIGH);
  digitalWrite(RightMotorDirPin2B,LOW); 
}
void RR_bck()  //rear-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1B,LOW);
  digitalWrite(RightMotorDirPin2B,HIGH); 
}
void RL_fwd()  //rear-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1B,HIGH);
  digitalWrite(LeftMotorDirPin2B,LOW);
}
void RL_bck()    //rear-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1B,LOW);
  digitalWrite(LeftMotorDirPin2B,HIGH);
}


