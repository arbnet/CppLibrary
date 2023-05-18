/** Квази шаблоны
 * Библиотека OWNI */ 

#pragma once
#define FILE_quasi

#ifdef UNICODE
typedef wchar_t TCHAR;// Универсальный символьный тип
#define _COUT std::wcout// универсальный вывод
#define _L(c) L##c// универсальный символьный массив
#else
typedef char TCHAR;// Универсальный символьный тип
#define _COUT std::cout // универсальный вывод
#define _L(c) c // универсальный символьный массив
#endif