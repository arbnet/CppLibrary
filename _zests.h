/* Изюминки для отладки */
#ifndef FILE_zests

#include <clocale>
#include <cstdlib>
#include <iostream>
#include "_calc.h"

/** Пространство имёт от _zests */
namespace z {
	using namespace std;
	//LOGIC s=true;
	/** число символов сдвига табуляции*/
	INT_W t=0;
	/** Табуляция 
	 * @param tb число символов табуляции
	 * @param sl символ табуляции	*/
	void tab(INT_W tb=0,LETTER sl=' '){
		INT_W szt=z::t+tb;
		if(szt){
			LETTER ltr[szt+1];POINTER pnt=ltr;
			t::fill(pnt,szt,(BYTE)sl);*(BYTE*)pnt=0;
			cout<<ltr;
		}
	}
	/** Ввод значения */
	template <typename dTYPE>
	void i(dTYPE &var,STRING msg=""){
		cout<<endl;
		if(msg)cout<<msg <<": ";
		cin>>var;
	}
	/** Вывод значения
	 * @param var переменная
	 * @param msg сообщение */
	template <typename dTYPE>
	void o(const dTYPE &var,STRING msg=""){
		cout<<endl;
		if(msg){tab();cout<<"# "<<msg<<endl;}
		tab();cout<<var<<endl;
	}
	/** Вывод значения
	 * @param str строка
	 * @param msg сообщение */
	void o(const STRING &str,STRING msg=""){
		tab();cout<<endl;
		if(msg){tab();cout<<"# "<<msg<<endl;}
		STRING obj(str);
		INT_W rv=obj.Reserve();
		tab();cout<<"STRING("<<obj.Size()<<','<<obj.Total();
		if(rv)cout<<','<<rv;
		cout<<"){"<<obj<<'}'<<endl;
	}
	void dump(POINTER pnt,INT_W size){
		cout<<endl<<"#address\t0  1  2  3  4  5  6  7\t\t~~dump~~"<<endl;
		tab(56,'-');cout<<endl<<hex;
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
			t::shift(pnt);size--;
		}
		if(col){
			if(col<6)cout<<'\t';
			if(col<3)cout<<'\t';
			cout<<"\t\t"<<txt<<endl;
		}
		tab(56,'-');cout<<dec<<endl;
	}
	template <typename dTYPE>
	void dump(const dTYPE &var,STRING msg=""){
		cout<<endl<<"# "<<::Type<dTYPE>::Name;
		if(msg)cout<<"\t"<<msg;
		dump((POINTER)&var,sizeof(var));
	}
	void dump(LETTER *ltr,STRING msg=""){
		INT_W sz=t::lsize(ltr);
		cout<<endl;
		tab();cout<<"# CHARS";
		if(msg)cout<<"\t"<<msg;
		dump((POINTER)ltr,sz);
	}
	void dump(CHARS(ltr),STRING msg=""){
		dump((LETTER*)ltr,msg);
	}
	void dump(const STRING &str,STRING msg=""){
		cout<<endl<<"# STRING";
		if(msg)cout<<"\t"<<msg;
		STRING obj(str);
		dump((POINTER)*obj,obj.Total());
	}
	/*
	void o(Associative oas,INT_W tb=0){
		tab(tb);cout<<"Associative{"<<endl;
		tb++;
		if(oas){oas.Reset();
			do{
				tab(tb);cout<<'['<<oas.Index()<<"] "<<oas.Key()<<"=";
				o(oas.Value());cout<<endl;
			}while(oas.Next());
		}else{tab(tb);cout<<"empty"<<endl;}
		tb--;
		tab(tb);cout <<'}'<<endl;
	}*/

	/** Включение кирилицы */
	void r(){setlocale(LC_ALL,"");}
	/** Пауза */
	void p(){system("pause");}
}

#define FILE_zests
#endif