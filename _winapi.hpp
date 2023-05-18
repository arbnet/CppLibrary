/** Обработка ошибок
 * Библиотека OWNI */ 

#pragma once
#define FILE_winapi

#include <windows.h>
#include "_types.hpp"

namespace w {
  /** Конвертация UTF8 в ANSI
   * @param chs указатель на массив символов
   * @return массив символов в ANSI */
  POINTER<CHAR> utf8_ansi(const CHAR *chs){
    INT_W sz=z::Lsize(chs);
    POINTER<CHAR> res(sz);
    POINTER<WCHAR> wch(sz);
    MultiByteToWideChar(CP_UTF8,0,chs,-1,*wch,sz);
    WideCharToMultiByte(CP_ACP,0,*wch,-1,*res,sz,NULL,NULL);
    res.Size(true);
    return res;
  }
}
