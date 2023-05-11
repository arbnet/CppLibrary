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
			POINTER<CHARS> chs(tsz+1);
			ADDRESS adr=*chs;
			z::Fill(adr,tsz,(BYTE)sl);
			*(BYTE*)adr=0;chs.Size(true);
			cout<<chs;
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
	/** Вывод типа и значения
	 * @param var переменная
	 * @param cmt комментарий */
	template <typename dTYPE>
	void o(const dTYPE &var,STRING cmt=""){
		ANY any(var);
		cout<<endl;tab();
		cout<<any.Type()<<'{'<<any<<'}';
		if(cmt)cout<<' '<<cmt;
	}
	/** Вывод строки с параметрами
	 * @param str строка
	 * @param cmt комментарий */
	void o(STRING &str,STRING cmt=""){
		INT_W rv=str.Reserve();
		cout<<endl;tab();
		cout<<"STRING("<<str.Size()<<','<<str.Total();
		if(rv)cout<<','<<rv;
		cout<<"){"<<str<<'}';
		if(cmt)cout<<' '<<cmt;
	}
	/** Вывод любого типа
	 * @param any любой тип
	 * @param cmt комментарий */
	void o(ANY &any,STRING cmt=""){
		cout<<endl;tab();
		cout<<"ANY{"<<any.Type()<<'{'<<any<<"}}";
		if(cmt)cout<<' '<<cmt;
	}
	/** Вывод параметров */
	template<typename... aARG>
	void p(aARG... args){(o(args), ...);}
	/*
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