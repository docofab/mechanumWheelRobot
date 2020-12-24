/**
 * @file  moveContllorer.cpp
 * @brief 前後左右の動作を記載、将来的にどっち方向に何cm移動を実装したい
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#include "motorDriver.h"

void moveAdvance()  //Forward
{
    FR_fwd();
    FL_fwd();
    RR_fwd();
    RL_fwd();
}

void moveLeft()  //Turn left
{
    FR_fwd();
    FL_bck();
    RR_fwd();
    RL_bck();
}
void moveRight()  //Turn right
{
    FR_bck();
    FL_fwd();
    RR_bck();
    RL_fwd();
}
void moveBack()  //Reverse
{
    FR_bck();
    FL_bck();
    RR_bck();
    RL_bck();
}
void moveStop()
{
    stop_Stop()
}

void moveSetSpeed(int leftFront,int rightFront,int leftBack,int rightBack){
    set_Motorspeed(int leftFront,int rightFront,int leftBack,int rightBack);
}