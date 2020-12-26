/**
 * @file  debugPrint.cpp
 * @brief Printfデバッグ用のデバッグ関数(シリアル通信で重くならない用にon/offを一括でしたいため)
 * 
 */

#include "debugPrint.h"

/**
 * @brief DEBUG_LOG＝trueのとき、入力値をシリアルログに出力
 * @param[in] str
 * 
 * @sa DEBUG_LOG
 * @return none 
 */
void DebugLogPrintln(String str){
//void DebugLogPrint(){
#if DEBUG_LOG 
    Serial.println(str);
    //Serial.println("a");
#endif
}

void DebugLogPrint(String str){
//void DebugLogPrint(){
#if DEBUG_LOG 
    Serial.print(str);
    //Serial.println("a");
#endif
}
