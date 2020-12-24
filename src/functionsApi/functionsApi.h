/**
 * @file  functionsApi.h 
 * @brief 
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#ifndef FUNCTION_APIS_H_INCLUDED
#define FUNCTION_APIS_H_INCLUDED


#include <Arduino.h>

#include "./../lib/debugPrint.h"
#include "./../lib/pinAssignment.h"

void   autoAvoidance();
String watchSurrounding();

#endif
