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
	 * @param adr указатель
	 * @param shift смещение */
	void Shift(ADDRESS &adr,INT_S shift=1){
		adr=(ADDRESS*)((INT_B)adr+shift);
	}
	/** Заполнение памяти значением
	 * @param pnt указатель адреса
	 * @param size размер\\длинна
	 * @param val значение */
	template <typename dTYPE=BYTE>
	void Fill(ADDRESS &adr,INT_W size,dTYPE val=0){
		while(size>0){
			*(dTYPE*)adr=val;Shift(adr,sizeof(dTYPE));size--;
		}
	}
	/** Перенос данных их одной области в другую
	 * @param adr1 адрес куда переносим
	 * @param adr2 адрес откуда переносим
	 * @param cnt счётчик\\количество итераций */
	template <typename dTYPE=BYTE>
	inline void Same(ADDRESS &adr1,ADDRESS &adr2,INT_M cnt){
		if(cnt){INT_S shi=sizeof(dTYPE);
			if(cnt<0){shi=-shi;cnt=-cnt;}
			do{
				*(dTYPE*)adr1=*(dTYPE*)adr2;
				Shift(adr1,shi);Shift(adr2,shi);
			}while(--cnt>0);
		}
	}
	/** Копирование в памяти
	 * @param adr1 адрес куда копировать
	 * @param adr2 адрес от куда копировать
	 * @param size размер\\длинна */
	void Copy(ADDRESS &adr1,ADDRESS &adr2,INT_M size){
		INT_M cnt;
		BYTE dis=(size>0?(INT_B)adr2-(INT_B)adr1:(INT_B)adr1-(INT_B)adr2)%255;
		cnt=size/8;if(cnt && dis>=8){size=size%8;Same<INT_B>(adr1,adr2,cnt);}
		cnt=size/4;if(cnt && dis>=4){size=size%4;Same<INT_L>(adr1,adr2,cnt);}
		cnt=size/2;if(cnt && dis>=2){size=size%2;Same<INT_W>(adr1,adr2,cnt);}
		if(size>0){cnt=size;Same(adr1,adr2,cnt);}
	}
	/** Сравнение памяти
	 * @param adr1 указатель адреса 1
	 * @param adr2 указатель адреса 2
	 * @param size размер\\длинна
	 * @return `true` равно, `false` не равно */
	LOGIC Compare(ADDRESS adr1,ADDRESS adr2,INT_W size){
		LOGIC res=true;
		while(size>0 && res){
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
		}
		return res;
	}
	/** Валидация индекса
	 * @param idx индекс
	 * @param asz размер массива */
	void Index(INT_W &idx,INT_W asz){
		if(idx>0){
			if(asz>0){
				if(idx<=asz)idx--;
				else{idx=~idx+1;
					if(idx<=asz)idx=asz-idx;
					else idx=asz-1;
				}
			}else idx=0;
		}
	}
	/** Валидация индекса
	 * @param idx индекс
	 * @param asz размер массива	*/
	void Index(INT_L &idx,INT_L asz){
		if(idx>0){
			if(asz>0){
				if(idx<=asz)idx--;
				else{idx=~idx+1;
					if(idx<=asz)idx=asz-idx;
					else idx=asz-1;
				}
			}else idx=0;
		}
	}
	/** Расчёт объёма от размера и резерва
	 * @param sz текущий размер
	 * @param rv резерв памяти
	 * @return значение объёма */
	INT_W Volume(INT_W sz,INT_W rv){
		INT_L res=rv+(sz/rv)*rv;
		if(res>65535)res=65535;
		return res;
	}
	/** Расчёт объёма от размера и резерва
	 * @param sz текущий размер
	 * @param rv резерв памяти
	 * @return значение объёма */
	INT_L Volume(INT_L sz,INT_W rv){
		INT_B res=rv+(sz/rv)*rv;
		if(res>4294967295)res=4294967295;
		return res;
	}
	/** Получение длинны массива символов
	 * @param chs массив символов
	 * @return размер массива символов */
	INT_W Lsize(CHARS chs){
		INT_W sz=0;
    while (*chs++){sz++;if(sz==65535)break;}
    return sz;
	}
}