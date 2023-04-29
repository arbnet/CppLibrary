/** Интерфэйс
 * Библиотека OWNI */

#ifndef FILE_interface

#include <iostream>
#include "_types.h"

/** Пространство имёт от _interface */
namespace i {
	using namespace std;
	/** число символов сдвига табуляции*/
	INT_W t=0;
	/** Табуляция 
	 * @param tb число символов табуляции
	 * @param sl символ табуляции	*/
	void tab(INT_W tb=0,LETTER sl=' '){
		INT_W szt=t+tb;
		if(szt){
			LETTER ltr[szt+1];POINTER pnt=ltr;
			t::Fill(pnt,szt,(BYTE)sl);*(BYTE*)pnt=0;
			cout<<ltr;
		}
	}
	/** Ввод значения */
	template <typename dTYPE>
	void i(dTYPE &var){
		cin>>var;
	}
	/** Ввод значения с сообщением */
	template <typename dTYPE>
	void i(STRING msg,dTYPE &var){
		cout<<endl<<msg<<": ";cin>>var;
	}
	/* * Вывод типа и значения
	 * @param var переменная * /
	 -----------------
	template <typename dTYPE>
	void o(const dTYPE &var){
		ANY any(var);
		cout<<endl;tab();
		cout<<any.Type()<<'{'<<any<<'}';
	}
	/** Вывод типа и значения с сообщением
	 * @param msg сообщение
	 * @param var переменная * /
	template <typename dTYPE>
	void o(STRING msg,const dTYPE &var){
		ANY any(var);
		cout<<endl;tab();
		cout<<msg<<": "<<any.Type()<<'{'<<any<<'}';
	}
	---------------
	*/
	/* * Вывод строки и параметров
	 * @param str строка * /
	void o(const STRING &str){
		STRING obj(str);
		INT_W rv=obj.Reserve();
		cout<<endl;t::tab();
		cout<<"STRING("<<obj.Size();
		if(rv)cout<<','<<obj.Total()<<','<<rv;
		cout<<"){"<<obj<<'}';
	}
	/ ** Вывод строки и параметров с сообщением
	 * @param str строка * /
	void o(STRING msg,const STRING &str){
		STRING obj(str);
		INT_W rv=obj.Reserve();
		cout<<endl;t::tab();
		cout<<msg<<": "<<"STRING("<<obj.Size();
		if(rv)cout<<','<<obj.Total()<<','<<rv;
		cout<<"){"<<obj<<'}';
	}
	/ ** Вывод любого типа
	 * @param any любой тип * /
	void o(const ANY &any){
		cout<<endl;t::tab();
		ANY obj(any);
		cout<<"ANY("<<obj.Type()<<"){"<<obj<<'}';
	}*/
}

#define FILE_interface
#endif