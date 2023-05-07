/** Интерфэйс
 * Библиотека OWNI */

#pragma once
#define FILE_interface

#include <clocale>
#include <iostream>
#include "_calc.hpp"

/** Пространство имёт от _interface */
namespace i {
	using namespace std;
	/** число символов сдвига табуляции*/
	INT_W t=0;
	/** Табуляция 
	 * @param tb число символов табуляции
	 * @param sl символ табуляции	*/
	void tab(INT_W tb=0,LETTER sl=' '){
		INT_W tsz=t+tb;
		if(tsz){
			LETTER lts[tsz+1];ADDRESS pnt=lts;
			z::Fill(pnt,tsz,(BYTE)sl);*(BYTE*)pnt=0;
			cout<<lts;
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
	}
	void dump(POINTER pnt,INT_W size){
		cout<<endl<<"#address\t0  1  2  3  4  5  6  7\t\t~~dump~~"<<endl;
		i::tab(56,'-');cout<<endl<<hex;
		BYTE val,col=0;
		STRING txt("        ");
		while(size>0){
			val=*(BYTE*)pnt;
			if(col==0){cout<<pnt<<'\t';col=0;}
			else cout<<' ';
			cout<<c::Hex(val);
			col++;if(val>15)txt[col]=val;
			if(col==8){
				cout<<"\t\t"<<txt<<endl;
				txt="        ";col=0;
			}
			z::Shift(pnt);size--;
		}
		if(col){
			if(col<6)cout<<'\t';
			if(col<3)cout<<'\t';
			cout<<"\t\t"<<txt<<endl;
		}
		i::tab(56,'-');cout<<dec<<endl;
	}
	template <typename dTYPE>
	void dump(const dTYPE &var){
		cout<<endl<<"# "<<::Type<dTYPE>::Name;
		dump((POINTER)&var,sizeof(var));
	}
	void dump(LETTER *ltr){
		INT_W sz=z::Lsize(ltr);
		cout<<endl<<"# "<<(sz>1?"CHARS":"LETTER");
		dump((POINTER)ltr,sz);
	}
	void dump(CHARS(ltr)){
		dump((LETTER*)ltr);
	}
	void dump(const STRING &str,STRING msg=""){
		cout<<endl<<"# STRING";
		if(msg)cout<<"\t"<<msg;
		STRING obj(str);
		dump((POINTER)*obj,obj.Total());
	}*/
	/** Пауза */
	void p(){
		cout<<endl;system("pause");
	}
	/** Включение кирилицы */
	void r(){setlocale(LC_ALL,"");}
}