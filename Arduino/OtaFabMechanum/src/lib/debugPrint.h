/**
 * @file  debugPrint.h
 * @brief Printfデバッグ用のデバッグ関数(シリアル通信で重くならない用にon/offを一括でしたいため)
 * 
 */
#ifndef DEBUG_PRINT_H_INCLUDED
#define DEBUG_PRINT_H_INCLUDED

#include <Arduino.h>

/**
 * @brief DEBUG_LOG･･･trueでログ出力、falseでログoff
*/
#define DEBUG_LOG true

void DebugLogPrintln(String str);
void DebugLogPrint(String str);
#endif
