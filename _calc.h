// Вычисление\преобразование

#ifndef FILE_calc

#include "_types.h"

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
	/** Получение шестнадтиричного значения байта
	 * @param b байт 
	 * @return HEX значение	*/
	STRING Hex(BYTE b){
		LETTER s[]="0123456789ABCDEF";
		LETTER h[3]={s[b/16],s[b%16],'\0'};
		return STRING(h);
	}
}

#define FILE_calc
#endif