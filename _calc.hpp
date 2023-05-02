/** Вычисление\преобразование
 * Библиотека OWNI */ 

#pragma once
#define FILE_calc

#include "_types.hpp"
#include <stdio.h>

namespace c {
	
	template <typename dTYPE>
	dTYPE d10(dTYPE var){
		BYTE num=BYTE(var%10);
		while(num==0){
			var=var/10;num=var%10;
		}
		return var;
	}
	/** Получение абсолютного значения
	 * @param var переменная
	 * @return абсолютное значение */
	template <typename dTYPE>
	dTYPE absolute(dTYPE var){
		if(var<0)var=-var;
		return var;
	}
	/** Получение целого числа
	 * @param var переменная FLOAT
	 * @return целое число INT_L */
	INT_L integer(FLOAT var){
		return INT_L(var);
	}
	/** Получение целого числа
	 * @param var переменная DOUBLE
	 * @return целое число INT_B */
	INT_B integer(DOUBLE var){
		return INT_B(var);
	}
	/** Дробная часть
	 * @param var переменная FLOAT
	 * @return значение FLOAT */
	FLOAT fraction(FLOAT var){
		var-=INT_L(var);
		return var;
	}
	/** Дробная часть
	 * @param var переменная DOUBLE
	 * @return значение DOUBLE */
	DOUBLE fraction(DOUBLE var){
		var-=INT_L(var);
		return var;
	}
	/** Целая часть
	 * @param var переменная FLOAT
	 * @return значение INT_L */
	INT_L whole(FLOAT var){
		var-=integer(var);
		INT_L res=var*1000;
		return d10(res);
	}
	/** Целая часть
	 * @param var переменная DOUBLE
	 * @return значение INT_B */
	INT_B whole(DOUBLE var){
		var-=integer(var);
		INT_B res=var*1000000;
		return d10(res);
	}
	/*template<typename dTYPE>
	STRING ToStr(dTYPE val){
		POINTER<CHARS> lts;
		sprintf(*lts,"%f",val);
		return STRING(*lts);
	}
	 * Получение шестнадтиричного значения байта
	 * @param b байт 
	 * @return HEX значение	* /
	STRING Hex(BYTE b,LOGIC sg=false){
		STRING st(16);
  	st="0123456789";st+=sg?"ABCDEF":"abcdef";
		LETTER hx[3]={st[1+b/16],st[1+b%16],'\0'};
		return STRING(hx);
	}*/
}