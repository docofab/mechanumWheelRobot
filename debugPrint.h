/**
 * @file  debugPrint.h
 * @brief Printfデバッグ用のデバッグ関数(シリアル通信で重くならない用にon/offを一括でしたいため)
 * 
 */

#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H
/**
 * @brief DEBUG_LOG･･･trueでログ出力、falseでログoff
*/
#define DEBUG_LOG true

/**
 * @brief DEBUG_LOG＝trueのとき、入力値をシリアルログに出力
 * @param[in] str
 * @param[out]  
 * @sa DEBUG_LOG
 * @return none 
 */
void DebugPrint(String str){
#if DEBUG_LOG 
    Serial.println(str);
#endif
}