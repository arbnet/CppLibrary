/* �������� ��� ������� */
#ifndef FILE_zests

#include <clocale>
#include <cstdlib>
#include <iostream>
#include "_calc.h"

/** ������������ ��� �� _zests */
namespace z {
	using namespace std;
	/** ����� �������� ������ ���������*/
	INT_W t=0;
	/** ��������� 
	 * @param tb ����� �������� ���������
	 * @param sl ������ ���������	*/
	void tab(INT_W tb=0,LETTER sl=' '){
		INT_W szt=t+tb;
		if(szt){
			LETTER ltr[szt+1];POINTER pnt=ltr;
			t::Fill(pnt,szt,(BYTE)sl);*(BYTE*)pnt=0;
			cout<<ltr;
		}
	}
	/** ���� �������� */
	template <typename dTYPE>
	void i(dTYPE &var){
		cin>>var;
	}
	/** ���� �������� */
	template <typename dTYPE>
	void i(STRING msg,dTYPE &var){
		cout<<endl<<msg<<": ";cin>>var;
	}
	/* * ����� ���� � ��������
	 * @param var ���������� * /
	 -----------------
	template <typename dTYPE>
	void o(const dTYPE &var){
		ANY any(var);
		cout<<endl;tab();
		cout<<any.Type()<<'{'<<any<<'}';
	}
	/** ����� ���� � �������� � ����������
	 * @param msg ���������
	 * @param var ���������� * /
	template <typename dTYPE>
	void o(STRING msg,const dTYPE &var){
		ANY any(var);
		cout<<endl;tab();
		cout<<msg<<": "<<any.Type()<<'{'<<any<<'}';
	}
	---------------
	*/
	/* * ����� ������ � ����������
	 * @param str ������ * /
	void o(const STRING &str){
		STRING obj(str);
		INT_W rv=obj.Reserve();
		cout<<endl;t::tab();
		cout<<"STRING("<<obj.Size();
		if(rv)cout<<','<<obj.Total()<<','<<rv;
		cout<<"){"<<obj<<'}';
	}
	/ ** ����� ������ � ���������� � ����������
	 * @param str ������ * /
	void o(STRING msg,const STRING &str){
		STRING obj(str);
		INT_W rv=obj.Reserve();
		cout<<endl;t::tab();
		cout<<msg<<": "<<"STRING("<<obj.Size();
		if(rv)cout<<','<<obj.Total()<<','<<rv;
		cout<<"){"<<obj<<'}';
	}
	/ ** ����� ������ ����
	 * @param any ����� ��� * /
	void o(const ANY &any){
		cout<<endl;t::tab();
		ANY obj(any);
		cout<<"ANY("<<obj.Type()<<"){"<<obj<<'}';
	}*/
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
			t::Shift(pnt);size--;
		}
		if(col){
			if(col<6)cout<<'\t';
			if(col<3)cout<<'\t';
			cout<<"\t\t"<<txt<<endl;
		}
		tab(56,'-');cout<<dec<<endl;
	}
	template <typename dTYPE>
	void dump(const dTYPE &var){
		cout<<endl<<"# "<<::Type<dTYPE>::Name;
		dump((POINTER)&var,sizeof(var));
	}
	void dump(LETTER *ltr){
		INT_W sz=t::Lsize(ltr);
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

	
	/** ����� */
	void p(){
		cout<<endl;system("pause");
	}
	/** ��������� �������� */
	void r(){setlocale(LC_ALL,"");}
}

#define FILE_zests
#endif