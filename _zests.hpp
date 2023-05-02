/** Изюминки, вспомогательные функции
 * Библиотека OWNI */

#pragma once
#define FILE_zests

#ifndef FILE_types
#include "_types.hpp"
#endif

/** Пространство имёт от _zests */
namespace z {
		/** Поменять местами переменные
	 * @param vr1 переменная 1
	 * @param vr2 переменная 2	*/
	template <typename dTYPE>
	void Swap(dTYPE &vr1, dTYPE &vr2){
		dTYPE tmp(vr1);vr1=vr2;vr2=tmp;
	}
	/** Поменять местами указатели
	 * @param vr1 указатель переменной 1
	 * @param vr2 указатель переменной 2	*/
	template <typename dTYPE>
	void Swap(dTYPE *vr1, dTYPE *vr2){
		dTYPE tmp(*vr1);*vr1=*vr2;*vr2=tmp;
	}
	/** Сдвиг указателя
	 * @param pnt указатель
	 * @param shift смещение */
	template <typename dTYPE>
	void Shift(dTYPE* &pnt,INT_S shift=1){
		pnt+=shift;
	}
	/** Сдвиг указателя
	 * @param pnt указатель
	 * @param shift смещение */
	void Shift(ADDRESS &pnt,INT_S shift=1){
		pnt=(ADDRESS*)((INT_B)pnt+shift);
	}
	/** Заполнение памяти значением
	 * @param pnt указатель адреса
	 * @param size размер\\длинна
	 * @param val значение */
	template <typename dTYPE=BYTE>
	void Fill(ADDRESS &pnt,INT_W size,dTYPE val=0){
		while(size>0){
			*(dTYPE*)pnt=val;Shift(pnt,sizeof(dTYPE));size--;
		}
	}
	/** Копирование в памяти
	 * @param adr1 адрес куда копировать
	 * @param adr2 адрес от куда копировать
	 * @param size размер */
	void Copy(ADDRESS &adr1,ADDRESS &adr2,INT_M size){
		INT_W ct;
		if(size>0){
			ct=size/8;
			if(ct>0){size=size%8;
				do{
					*(INT_B*)adr1=*(INT_B*)adr2;
					Shift(adr1,8);Shift(adr2,8);ct--;
				}while(ct>0);
			}
			ct=size/4;
			if(ct>0){size=size%4;
				do{
					*(INT_L*)adr1=*(INT_L*)adr2;
					Shift(adr1,4);Shift(adr2,4);ct--;
				}while(ct>0);
			}
			ct=size/2;
			if(ct>0){size=size%2;
				do{
					*(INT_W*)adr1=*(INT_W*)adr2;
					Shift(adr1,2);Shift(adr2,2);ct--;
				}while(ct>0);
			}
			if(size>0){ct=size;
				do{
					*(BYTE*)adr1=*(BYTE*)adr2;
					Shift(adr1,1);Shift(adr2,1);ct--;
				}while(ct>0);
			}
		}else{size=-size;
			ct=size/8;
			if(ct>0){size=size%8;
				do{
					Shift(adr1,-8);Shift(adr2,-8);ct--;
					*(INT_B*)adr1=*(INT_B*)adr2;
				}while(ct>0);
			}
			ct=size/4;
			if(ct>0){size=size%4;
				do{
					Shift(adr1,-4);Shift(adr2,-4);ct--;
					*(INT_L*)adr1=*(INT_L*)adr2;
				}while(ct>0);
			}
			ct=size/2;
			if(ct>0){size=size%2;
				do{
					Shift(adr1,-2);Shift(adr2,-2);ct--;
					*(INT_W*)adr1=*(INT_W*)adr2;
				}while(ct>0);
			}
			if(size>0){ct=size;
				do{
					Shift(adr1,-1);Shift(adr2,-1);ct--;
					*(BYTE*)adr1=*(BYTE*)adr2;
				}while(ct>0);
			}
		}
	}
	/** Сравнение памяти
	 * @param adr1 указатель адреса 1
	 * @param adr2 указатель адреса 2
	 * @param size размер\\длинна */
	LOGIC Compare(ADDRESS adr1,ADDRESS adr2,INT_W size){
		LOGIC res=true;
		while(size>0){
			if(size>=8){
				if(*(INT_B*)adr1!=*(INT_B*)adr2)res=false;
				else{Shift(adr1,8);Shift(adr2,8);size-=8;}
			}else if(size>=4){
				if(*(INT_L*)adr1!=*(INT_L*)adr2)res=false;
				else{Shift(adr1,4);Shift(adr2,4);size-=4;}
			}else if(size>=2){
				if(*(INT_W*)adr1!=*(INT_W*)adr2)res=false;
				else{Shift(adr1,2);Shift(adr2,2);size-=2;}
			}else{
				if(*(BYTE*)adr1!=*(BYTE*)adr2)res=false;
				else{Shift(adr1,1);Shift(adr2,1);size-=1;}
			}
			if(!res)break;
		}
		return res;
	}
	/** Валидация индекса
	 * @param index индекс
	 * @param size размер массива */
	void Index(INT_W &index,INT_W size){
		if(index>0){
			if(size>0){
				if(index<=size)index--;
				else{index=~index+1;
					if(index<=size)index=size-index;
					else index=size-1;
				}
			}else index=0;
		}
	}
	/** Валидация индекса
	 * @param index индекс
	 * @param size размер массива	*/
	void Index(INT_L &index,INT_L size){
		if(index>0){
			if(size>0){
				if(index<=size)index--;
				else{index=~index+1;
					if(index<=size)index=size-index;
					else index=size-1;
				}
			}else index=0;
		}
	}
	/** Расчёт объёма от размера и резерва
	 * @param sz текущий размер
	 * @param mr резерв памяти
	 * @return значение объёма */
	INT_W Volume(INT_W sz,INT_W mr){
		INT_L res=mr+(sz/mr)*mr;
		if(res>65535)res=65535;
		return res;
	}
	/** Расчёт объёма от размера и резерва
	 * @param sz текущий размер
	 * @param mr резерв памяти
	 * @return значение объёма */
	INT_L Volume(INT_L sz,INT_W mr){
		INT_B res=mr+(sz/mr)*mr;
		if(res>4294967295)res=4294967295;
		return res;
	}
	/** Получение длинны массива символов
	 * @param ltr массив символов
	 * @return размер массива символов */
	INT_W Lsize(CHARS(ltr)){
		INT_W sz=0;
		while(ltr[sz]!='\0'){sz++;if(sz==65535)break;}
		return sz;
	}
	/** Проверка на NULL
	 * @param val переменная
	 * @return `true` NULL, иначе `false` */
	template <typename dTYPE>
	LOGIC isNULL(dTYPE val){
		LOGIC res=false;
		if(::Type<dTYPE>::Name=="INT_T")if(!val)res=true;
		return res;
	}
}