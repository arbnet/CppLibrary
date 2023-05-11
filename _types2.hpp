/** Типы данных
 * Библиотека OWNI */

#pragma once
#define FILE_types

#include <typeinfo>
#include <cstdlib>
#include <stdio.h>
#include <ctime>

/** Пустые макросы _error */
#ifndef FILE_error
#define FIX
#define TRY
#define CATCH
#endif

#ifndef NULL
#ifndef __cplusplus
#define NULL ((void *)0)
#else
#define NULL 0
#endif
#endif

typedef bool LOGIC;// Логический тип 0..1
typedef char LETTER;// Буква
typedef __INT8_TYPE__ RANGE;// Диапазон -128..127
typedef __UINT8_TYPE__ BYTE;// Байт 0..255
typedef __INT16_TYPE__ INT_S;// Целое число -32768..32767
typedef __UINT16_TYPE__ INT_W;// Целое число 0..65535
typedef __INT32_TYPE__ INT_M;// Целое число -2147483648..2147483647
typedef __UINT32_TYPE__ INT_L;// Целое число 0..4294967295
typedef __INT64_TYPE__ INT_T;// Целое число -9223372036854775808..9223372036854775807
typedef __UINT64_TYPE__ INT_B;// Целое число 0..18446744073709551615
typedef float FLOAT;// Плавающее число 1.8E-38..1.8E+38		32b точность 6 .3 знаков
typedef double DOUBLE;// Плавающее число двойной точности 2.2E-308..1.8E+308	64b	точность 15 .6 знаков
typedef void* ADDRESS;// Указатель адреса
typedef const char* CHARS;// Указатель на массив символов

/** Структура типа Id и Name */
template<typename dTYPE> struct Type {
	/** Id типа */
	static const INT_W Id=0;
	/** Name типа */
	static constexpr char Name[]="UNKNOWN";
};
/** Добавление ID типа */
#define ID_TYPE(nID,dTYPE) \
template<> struct Type<dTYPE> {\
	static const INT_W Id=nID;\
	static constexpr char Name[]=#dTYPE;\
};

ID_TYPE(1,LOGIC)
ID_TYPE(2,LETTER)
ID_TYPE(3,RANGE)
ID_TYPE(4,BYTE)
ID_TYPE(5,INT_S)
ID_TYPE(6,INT_W)
ID_TYPE(7,INT_M)
ID_TYPE(8,INT_L)
ID_TYPE(9,INT_T)
ID_TYPE(10,INT_B)
ID_TYPE(11,FLOAT)
ID_TYPE(12,DOUBLE)
ID_TYPE(13,ADDRESS)
ID_TYPE(14,CHARS)

/** Структура битов .b0..b7 */
struct Bits {
	unsigned b0:1;
	unsigned b1:1;
	unsigned b2:1;
	unsigned b3:1;
	unsigned b4:1;
	unsigned b5:1;
	unsigned b6:1;
	unsigned b7:1;
};
/** Структура байтов .b0..b7 */
struct Bytes {
	BYTE b0;
	BYTE b1;
	BYTE b2;
	BYTE b3;
	BYTE b4;
	BYTE b5;
	BYTE b6;
	BYTE b7;
};
/** Союз BYTE & Bits */
union Code {
	BYTE byte;
	Bits bit;
};
/** Союз INT_B & Bytes */
union Block {
	INT_B numb;
	Bytes byte;
};

/** Структура даты-времени */
struct DateTime {
	int seconds;
	int minutes;
	int hours;
	int day;
	int month;
	int year;
	int wday;
	int yday;
	int summer;
};
/** Союз tm & DateTime */
union DateTimeU {
	struct tm stm;
	DateTime dtm;
};

/** Пространство имёт от _types */
namespace t {
	/** Проверка на тип\класс */
	template <bool tBool, class oCLASS=void>
	struct IfType {};
	template <class oCLASS>
	struct IfType<true, oCLASS> {typedef oCLASS type;};
	/** Включение в компиляцию */
	template <bool tBool, class oCLASS=void>
	using Enable = typename IfType<tBool,oCLASS>::type;
	/** Сравнение типов */
	template <typename T1,typename T2>
	struct Match {static const bool v=false;};
	template <typename T0>
	struct Match<T0,T0> {static const bool v=true;};
	/** Ниличие типа в перечне */
	template <typename dTYPE, typename ...aTYPE>
	struct IsMatch{static constexpr bool v{(Match<dTYPE,aTYPE>::v || ...)};};
	/** Проверка на базовый тип данных */
	template <typename dTYPE>
	constexpr bool isBaseB=IsMatch<dTYPE,LOGIC,LETTER,RANGE,BYTE,INT_S,INT_W,INT_M,INT_L,INT_T,INT_B,FLOAT,DOUBLE,ADDRESS>::v;
	/** Проверка на целочисленный тип данных */
	template <typename dTYPE>
	constexpr bool isInteger=IsMatch<dTYPE,RANGE,BYTE,INT_S,INT_W,INT_M,INT_L,INT_T,INT_B>::v;
	/** Проверка на дробный тип данных */
	template <typename dTYPE>
	constexpr bool isFloating=IsMatch<dTYPE,FLOAT,DOUBLE>::v;
};

#include "_zests.hpp"

/** Указатель */
template<typename dTYPE>
class POINTER {
	dTYPE *pnt;
	POINTER *obj=NULL;
	void Kill(LOGIC grd){
		if(obj)obj->Kill(grd);else if(!grd)delete pnt;
		pnt=NULL;
	}
public:
	/** защита от уничтожения */
	LOGIC guard=false;
	POINTER(){pnt=new dTYPE;}
  POINTER(dTYPE val){pnt=new dTYPE(val);}
	POINTER(POINTER &obj):pnt(obj.pnt),obj(&obj){
		if(obj.guard)obj.guard=false;
	}
	~POINTER(){if(!obj)if(pnt)delete pnt;}
	operator POINTER<CHARS>();
	explicit operator bool(){return pnt?true:false;}
  dTYPE& operator*(){return *(dTYPE*)pnt;}
	dTYPE& operator=(dTYPE val){
		if(pnt)*(dTYPE*)pnt=val;
		return *this;
	}
	/** Уничтожение указателя */
	void Kill(){
		if(obj)obj->Kill(guard);else delete pnt;
		if(!guard)pnt=NULL;
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<< (std::ostream &out,const POINTER &obj){
		return obj.pnt?out<<*(dTYPE*)obj.pnt:out<<"NULL";
	}
	#endif
};

/** Указатель */
template<>
class POINTER<CHARS> {
	void Kill(LOGIC grd){
		if(obj)obj->Kill(grd);else if(!grd)delete pnt;
		pnt=NULL;sz=tl=rv=0;
	}
protected:
	LETTER *pnt;
	INT_W sz=0,tl,rv;
	POINTER<CHARS> *obj=NULL;
	LETTER* Change(){
		LETTER* lts=NULL;
		if(rv){INT_W ntl=z::Volume(sz,rv);
			if(tl!=ntl){tl=ntl;lts=new LETTER[INT_L(tl+1)];}
		}
		return lts;
	}
	void Assign(const LETTER *lts){
		ADDRESS adr=pnt;
		if(sz){
			ADDRESS adl=(ADDRESS)lts;
			z::Copy(adr,adl,sz);
		}
		*(BYTE*)adr=0;
	}
public:
	/** защита от уничтожения */
	LOGIC guard=false;
	POINTER<CHARS>(INT_W tl=32,INT_W rv=0):tl(tl),rv(!tl && !rv?32:rv){
		pnt=new LETTER[tl+1];*(BYTE*)pnt=0;
	}
	POINTER<CHARS>(CHARS lts){
		sz=tl=z::Lsize(lts);rv=0;
		pnt=new LETTER[tl+1];Assign(lts);
	}
	POINTER<CHARS>(POINTER<CHARS> &obj):
		pnt(obj.pnt),sz(obj.sz),tl(obj.tl),obj(&obj){
			if(obj.guard)obj.guard=false;
	}
	~POINTER<CHARS>(){if(!obj)if(pnt)delete pnt;}
	explicit operator bool(){return pnt?true:false;}
  LETTER* operator*(){return pnt;}
	POINTER<CHARS>& operator=(const LETTER *lts){
		if(pnt){
			sz=z::Lsize(lts);
			if(LETTER* npt=this->Change()){
				delete []pnt;pnt=npt;
			}else	if(sz>tl)sz=tl;
			Assign(lts);
		}
		return *this;
	}
	/** Уничтожение указателя */
  void Kill(){
		if(pnt){
			if(obj)obj->Kill(guard);else delete pnt;
			if(!guard){pnt=NULL;sz=tl=rv=0;}
		}
	}
	/** Получение\подсчёт размера массива символов
	 * @param sgn `true` для подсчёта
	 * @return количество символов */
	INT_W Size(LOGIC sgn=false){
		if(sgn)sz=z::Lsize(pnt);
		return sz;
	}
	/** Тотальный размер в памяти */
	INT_W Total(){return tl;}
	/** Размер резервирования */
	INT_W Reserve(){return rv;}
	/** Установка размера резервирования */
	void Reserve(INT_W rv){this->rv=rv;}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<< (std::ostream &out,const POINTER<CHARS> &obj){
		return obj.sz?out<<(LETTER*)obj.pnt:out<<"NULL";
	}
	#endif
};

ID_TYPE(21,POINTER<LOGIC>)
ID_TYPE(22,POINTER<LETTER>)
ID_TYPE(23,POINTER<RANGE>)
ID_TYPE(24,POINTER<BYTE>)
ID_TYPE(25,POINTER<INT_S>)
ID_TYPE(26,POINTER<INT_W>)
ID_TYPE(27,POINTER<INT_M>)
ID_TYPE(28,POINTER<INT_L>)
ID_TYPE(29,POINTER<INT_T>)
ID_TYPE(30,POINTER<INT_B>)
ID_TYPE(31,POINTER<FLOAT>)
ID_TYPE(32,POINTER<DOUBLE>)
ID_TYPE(33,POINTER<ADDRESS>)
ID_TYPE(34,POINTER<CHARS>)

/** Строка */
class STRING :public POINTER<CHARS> {
	LOGIC Compare(ADDRESS adr,INT_W sz){
		return sz==sz?z::Compare(pnt,adr,sz):false;
	}
public:
	STRING(CHARS lts):POINTER<CHARS>(lts){}
	STRING(const STRING &obj):POINTER<CHARS>(obj.pnt){}
	STRING(INT_W tl=0,INT_W rv=0):POINTER<CHARS>(tl,rv){}
	operator bool(){return sz?true:false;}
	template<typename dTYPE, typename = t::Enable<t::isBaseB<dTYPE>,dTYPE>>
	STRING(dTYPE val){
		POINTER<CHARS> lts;
		INT_W vid=::Type<dTYPE>::Id;
		if(vid==1)lts=val?"true":"false";
		else{sprintf(*lts,vid==11 || vid==12?"%f":"%d",val);lts.Size(true);}
		*this=*lts;
	}
	LETTER& operator[](INT_L idx){
		z::Index(idx,sz);
		return pnt[idx];
	}
	STRING& operator=(const LETTER *lts){
		POINTER<CHARS>::operator=(lts);
		return *this;
	}
	STRING& operator=(const STRING &obj){
		sz=obj.sz;
		if(LETTER* npt=Change()){
			delete []pnt;pnt=npt;
		}else	if(sz>tl)sz=tl;
		Assign(obj.pnt);
		return *this;
	}
	STRING& operator+=(const STRING &obj){
		Put(obj);return *this;
	}
	STRING& operator-=(const STRING &obj){
		this->Cut(obj);return *this;
	}
	LOGIC operator==(const STRING &obj){
		return Compare(obj.pnt,obj.sz);
	}
	LOGIC operator!=(const STRING &obj){
		return !Compare(obj.pnt,obj.sz);
	}
	/** Вставка подстроки
	 * @param obj подстрока
	 * @param idx индекс куда вставить */
	void Put(const STRING &obj,INT_W idx=0){
		if(INT_W psz=obj.sz){
			if(INT_L(sz+psz)>(rv?65535:tl))psz=(rv?65535:tl)-sz;
			if(psz){
				ADDRESS adr1,adr2,adr3;
				INT_W osz=sz;sz+=psz;
				if(!idx)idx=osz;else z::Index(idx,sz);
				if(LETTER* lts=Change()){
					adr1=(ADDRESS)lts;adr2=(ADDRESS)pnt;
					if(idx)z::Copy(adr1,adr2,idx);
					adr3=(ADDRESS)obj.pnt;
					z::Copy(adr1,adr3,psz);
					z::Copy(adr1,adr2,osz-idx);
					*(BYTE*)adr1=0;
					delete []pnt;pnt=lts;
				}else{
					adr1=adr2=(ADDRESS)pnt;
					z::Shift(adr1,sz);z::Shift(adr2,osz);
					*(BYTE*)adr1=0;z::Copy(adr1,adr2,-(osz-idx));
					adr3=(ADDRESS)obj.pnt;z::Shift(adr3,psz);
					z::Copy(adr1,adr3,-psz);
				}
			}
		}
	}
	/** Вырезать
	 * @param idx индекс места вырезки
	 * @param csz размер для вырезки */
	void Cut(INT_W idx,INT_W csz){
		if(sz){z::Index(idx,sz);
			if(idx+csz>sz)csz=sz-idx;
			if(csz){
				ADDRESS adr1,adr2;
				INT_W osz=sz;sz=sz-csz;
				if(LETTER* lts=Change()){
					delete []pnt;pnt=lts;
					adr1=(ADDRESS)lts;adr2=(ADDRESS)pnt;
					if(idx)z::Copy(adr1,adr2,idx);
					z::Shift(adr2,csz);idx+=csz;
					z::Copy(adr1,adr2,osz-idx);
				}else{
					adr1=(ADDRESS)pnt;
					if(idx)z::Shift(adr1,idx);
					adr2=adr1;z::Shift(adr2,csz);
					idx+=csz;z::Copy(adr1,adr2,osz-idx);
				}
				*(BYTE*)adr1=0;
			}
		}
	}
	/** Вырезать
	 * @param obj подстрока
	 * @param idx индекс поиска */
	void Cut(const STRING &obj,INT_W idx=0){
		idx=this->Find(obj,idx);
		if(idx)Cut(idx,obj.sz);
	}
	/** Поиск позиции подстроки
	 * @param obj подстрока
	 * @param idx индекс начала поиска
	 * @return индекс позиции */
	INT_W Find(const STRING &obj,INT_W idx=0){
		INT_W res=0;
		if(sz){
			LOGIC sgn=idx>sz?false:true;
			ADDRESS adr=pnt;
			z::Index(idx,sz);if(idx>0)z::Shift(adr,idx);
			if(sgn){
				for(INT_W nx=sz-obj.sz;idx<=nx;idx++){
					if(z::Compare(adr,obj.pnt,obj.sz)){res=idx+1;break;}
					z::Shift(adr);
				}
			}else if(idx-obj.sz>0){
				for(INT_W nx=idx-obj.sz;idx>0;idx--){
					if(z::Compare(adr,obj.pnt,obj.sz)){res=idx+1;break;}
					z::Shift(adr,-1);
				}
			}
		}
		return res;
	}
	void Kill()=delete;
};
ID_TYPE(15,STRING)
ID_TYPE(35,POINTER<STRING>)

/** ДатаВремя */
class DATETIME {
	time_t dtm;
public:
	DATETIME(time_t dtm=0){this->dtm=dtm;}
	DATETIME(const DATETIME &obj):dtm(obj.dtm){}
	operator INT_B(){return (INT_B)dtm;}
	operator DateTime(){
		DateTimeU udt;
		udt.stm=*localtime(&dtm);
		udt.dtm.year+=1900;
		udt.dtm.month+=1;
		return udt.dtm;
	}
	DATETIME& operator=(time_t val){
		this->dtm=val;return *this;
	}
	DATETIME& operator=(DateTime dtm){
		DateTimeU udt;
		udt.dtm=dtm;
		udt.dtm.month-=1;
		udt.dtm.year-=1900;
		this->dtm=mktime(&udt.stm);
		return *this;
	}
	DATETIME& operator+=(time_t val){
		this->dtm+=val;return *this;
	}
	DATETIME& operator-=(time_t val){
		this->dtm-=val;return *this;
	}
	/** Время выполнения */
	void Clock(){this->dtm=clock();}
	/** Текущее время */
	void Now(){this->dtm=time(NULL);}
	/** Получение строкового представления даты-времени
	 * @param fmt формат даты-времени
	 * @param bsz размер буфера формирования строки
	 * @return строка с датой-временем */
	STRING Format(STRING fmt="%Y.%m.%d %H:%M:%S",INT_W sbf=64){
		LETTER res[sbf];
		strftime(res,sbf,*fmt,localtime(&dtm));
		return STRING(res);
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<< (std::ostream &out,const DATETIME &obj){
		return out<<obj.dtm;
	}
	#endif
};
ID_TYPE(16,DATETIME)

//ID_TYPE(17,резерв)
//ID_TYPE(18,резерв)

/** Пространство имёт от _types */
namespace t {
	/** Проверка на основной тип данных */
	template <typename dTYPE>
	constexpr bool isBaseA=IsMatch<dTYPE,LOGIC,LETTER,RANGE,BYTE,INT_S,INT_W,INT_M,INT_L,INT_T,INT_B,FLOAT,DOUBLE,ADDRESS,CHARS,STRING,DATETIME>::v;

	/** Получение Id переменной
	 * @param var переменная 
	 * @return Id переменной */
	template<typename dTYPE>
	INT_W Id(dTYPE var){
		return ::Type<dTYPE>::Id;
	}
	/** Получение типа переменной
	 * @param var переменная 
	 * @return тип переменной */
	template<typename dTYPE>
	STRING Type(dTYPE var){
		STRING vtp;
		if(::Type<dTYPE>::Id)vtp=::Type<dTYPE>::Name;
		else{vtp=typeid(var).name();
			LETTER *lts=new LETTER[32];
  		_itoa(vtp.Size()-1,lts,10);
			vtp-=lts;delete lts;
		}
  	return vtp;
	}
}

/** Ссылка */
class LINK {
protected:
	STRING tp;
	INT_W id=0,sz=0;
	ADDRESS pnt=NULL;
public:
	LINK(){}
	template<typename dTYPE>
	LINK(dTYPE &obj){this->Init(obj);}
	LINK(const LINK &obj):tp(obj.tp),id(obj.id),sz(obj.sz),pnt(obj.pnt){}
	ADDRESS operator*(){return pnt;}
	operator CHARS(){return (CHARS)pnt;}
	template <typename dTYPE>
	operator dTYPE(){return *(dTYPE*)pnt;}
	explicit operator bool(){return pnt?true:false;}
	template<typename dTYPE>
	t::Enable<t::isBaseA<dTYPE>,LINK&> operator=(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)*(dTYPE*)pnt=val;
		#ifdef FILE_error
		else throw Error("LINK = не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template<typename dTYPE>
	t::Enable<t::isBaseA<dTYPE>,LOGIC> operator==(dTYPE val){
		LOGIC res=false;
		TRY
		if(id==::Type<dTYPE>::Id)res=*(dTYPE*)pnt==val;
		#ifdef FILE_error
		else throw Error("LINK == не соответствует типу!");
		#endif
		CATCH
		return res;
	}
	template<typename dTYPE>
	t::Enable<t::isBaseA<dTYPE>,LOGIC> operator!=(dTYPE val){
		LOGIC res=false;
		TRY
		if(id==::Type<dTYPE>::Id)res=*(dTYPE*)pnt!=val;
		#ifdef FILE_error
		else throw Error("LINK == не соответствует типу!");
		#endif
		CATCH
		return res;
	}
	/** Получение Id данных */
	INT_W Id(){return id;}
	/** Размер данных */
	INT_W Size(){return sz;}
	/** Тип данных */
	STRING Type(){return tp;}
	/** Инициализация
	 * @param obj объект */
	template<typename dTYPE>
	void Init(dTYPE &obj){
		pnt=&obj;
		tp=t::Type(obj);
		sz=sizeof(dTYPE);
		id=::Type<dTYPE>::Id;
	}
	void Init(CHARS chs){
		pnt=(ADDRESS)chs;
		sz=z::Lsize(chs);
		tp="CHARS";id=14;
	}
	/** Очистка ссылки */
	void Clear(){
		pnt=NULL;sz=id=0;tp="";
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<<(std::ostream &out,const LINK &obj){
		if(obj.pnt){
			switch(obj.id){
				case 1:	out<<(*(LOGIC*)obj.pnt?"true":"false");break;
				case 2:	out<<*(LETTER*)obj.pnt;break;
				case 3:	out<<(INT_S)*(RANGE*)obj.pnt;break;
				case 4:	out<<(INT_W)*(BYTE*)obj.pnt;break;
				case 5:	out<<*(INT_S*)obj.pnt;break;
				case 6:	out<<*(INT_W*)obj.pnt;break;
				case 7:	out<<*(INT_M*)obj.pnt;break;
				case 8:	out<<*(INT_L*)obj.pnt;break;
				case 9:	out<<*(INT_T*)obj.pnt;break;
				case 10:out<<*(INT_B*)obj.pnt;break;
				case 11:out<<*(FLOAT*)obj.pnt;break;
				case 12:out<<*(DOUBLE*)obj.pnt;break;
				case 13:out<<*(ADDRESS*)obj.pnt;break;
				case 14:out<<(CHARS)obj.pnt;break;
				case 15:out<<*(STRING*)obj.pnt;break;
				case 16:out<<*(DATETIME*)obj.pnt;break;
				case 34:out<<*(POINTER<CHARS>*)obj.pnt;break;
				default:out<<obj.tp;
			}
		}else out<<"NULL";
		return out;
	}
	#endif
};
ID_TYPE(19,LINK)

/** Любой тип */
class ANY :public LINK {
public:
	ANY(){}
	template<typename dTYPE>
	ANY(dTYPE val){*this=val;}
	ANY(const ANY &obj){*this=obj;}
	~ANY(){Clear();}
	ADDRESS operator*(){return pnt;}
	template<typename dTYPE>
	ANY& operator=(dTYPE val){
		INT_W tid=::Type<dTYPE>::Id;
		if(id==tid)LINK::operator=(val);
		else if(tid){
			dTYPE *obj=new dTYPE(val);
			LINK::Init(*obj);
		}else LINK::Init(val);
		return *this;
	}
	ANY& operator=(CHARS chs){
		Clear();
		INT_W nsz=z::Lsize(chs)+1;
		CHARS lts=new LETTER[nsz];
		ADDRESS adr1=(ADDRESS)lts,adr2=(ADDRESS)chs;
		z::Copy(adr1,adr2,sz);LINK::Init(lts);
		return *this;
	}
	ANY& operator=(ANY &obj){
		switch(obj.Id()){
			case 1:	*this=(LOGIC)obj;break;
			case 2:	*this=(LETTER)obj;break;
			case 3:	*this=(RANGE)obj;break;
			case 4:	*this=(BYTE)obj;break;
			case 5:	*this=(INT_S)obj;break;
			case 6:	*this=(INT_W)obj;break;
			case 7:	*this=(INT_M)obj;break;
			case 8:	*this=(INT_L)obj;break;
			case 9:	*this=(INT_T)obj;break;
			case 10:*this=(INT_B)obj;break;
			case 11:*this=(FLOAT)obj;break;
			case 12:*this=(DOUBLE)obj;break;
			case 13:*this=(ADDRESS)obj;break;
			case 14:*this=(CHARS)obj;break;
			case 15:*this=*(STRING*)*obj;break;
			case 16:*this=*(DATETIME*)*obj;break;
			//default:*this=*(Link*)obj.mdt->pnt;
		}
		return *this;
	}
	ANY& operator++(int){
		switch(id){
			case 1:	*this=LOGIC(*(LOGIC*)pnt?0:1);break;
			case 2:	*this=LETTER(*(LETTER*)pnt+1);break;
			case 3:	*this=RANGE(*(RANGE*)pnt+1);break;
			case 4:	*this=BYTE(*(BYTE*)pnt+1);break;
			case 5:	*this=INT_S(*(INT_S*)pnt+1);break;
			case 6:	*this=INT_W(*(INT_W*)pnt+1);break;
			case 7:	*this=INT_M(*(INT_M*)pnt+1);break;
			case 8:	*this=INT_L(*(INT_L*)pnt+1);break;
			case 9:	*this=INT_T(*(INT_T*)pnt+1);break;
			case 10:*this=INT_B(*(INT_B*)pnt+1);break;
			case 11:*this=FLOAT(*(FLOAT*)pnt+0.01);break;
			case 12:*this=DOUBLE(*(DOUBLE*)pnt+0.0001);break;
			case 13:*this=ADDRESS(*(INT_B*)pnt+1);break;
			case 16:*this=DATETIME(*(DATETIME*)pnt+1);break;
		}
		return *this;
	}
	ANY& operator--(int){
		switch(id){
			case 1:	*this=LOGIC(*(LOGIC*)pnt?0:1);break;
			case 2:	*this=LETTER(*(LETTER*)pnt-1);break;
			case 3:	*this=RANGE(*(RANGE*)pnt-1);break;
			case 4:	*this=BYTE(*(BYTE*)pnt-1);break;
			case 5:	*this=INT_S(*(INT_S*)pnt-1);break;
			case 6:	*this=INT_W(*(INT_W*)pnt-1);break;
			case 7:	*this=INT_M(*(INT_M*)pnt-1);break;
			case 8:	*this=INT_L(*(INT_L*)pnt-1);break;
			case 9:	*this=INT_T(*(INT_T*)pnt-1);break;
			case 10:*this=INT_B(*(INT_B*)pnt-1);break;
			case 11:*this=FLOAT(*(FLOAT*)pnt-0.01);break;
			case 12:*this=DOUBLE(*(DOUBLE*)pnt-0.0001);break;
			case 13:*this=ADDRESS(*(INT_B*)pnt-1);break;
			case 16:*this=DATETIME(*(DATETIME*)pnt-1);break;
		}
		return *this;
	}
	template<typename dTYPE>
	ANY& operator+(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)LINK::operator=(dTYPE(*(dTYPE*)pnt+val));
		#ifdef FILE_error
		else throw Error("Оператор + не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template<typename dTYPE>
	ANY& operator-(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)LINK::operator=(dTYPE(*(dTYPE*)pnt-val));
		#ifdef FILE_error
		else throw Error("Оператор - не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template<typename dTYPE>
	ANY& operator*(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)LINK::operator=(dTYPE(*(dTYPE*)pnt*val));
		#ifdef FILE_error
		else throw Error("Оператор * не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template<typename dTYPE>
	ANY& operator/(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)LINK::operator=(dTYPE(*(dTYPE*)pnt/val));
		#ifdef FILE_error
		else throw Error("Оператор / не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template<typename dTYPE>
	ANY& operator+=(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)LINK::operator=(dTYPE(*(dTYPE*)pnt+val));
		#ifdef FILE_error
		else throw Error("Оператор += не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template<typename dTYPE>
	ANY& operator-=(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)LINK::operator=(dTYPE(*(dTYPE*)pnt-val));
		#ifdef FILE_error
		else throw Error("Оператор -= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template<typename dTYPE>
	ANY& operator*=(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)LINK::operator=(dTYPE(*(dTYPE*)pnt*val));
		#ifdef FILE_error
		else throw Error("Оператор *= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template<typename dTYPE>
	ANY& operator/=(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)LINK::operator=(dTYPE(*(dTYPE*)pnt/val));
		#ifdef FILE_error
		else throw Error("Оператор /= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template<typename dTYPE>
	ANY& operator%=(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)LINK::operator=(dTYPE(*(dTYPE*)pnt%val));
		#ifdef FILE_error
		else throw Error("Оператор %= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template<typename dTYPE>
	ANY& operator&=(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)LINK::operator=(dTYPE(*(dTYPE*)pnt&val));
		#ifdef FILE_error
		else throw Error("Оператор &= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template<typename dTYPE>
	ANY& operator|=(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)LINK::operator=(dTYPE(*(dTYPE*)pnt|val));
		#ifdef FILE_error
		else throw Error("Оператор |= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template<typename dTYPE>
	ANY& operator^=(dTYPE val){
		TRY
		if(id==::Type<dTYPE>::Id)LINK::operator=(dTYPE(*(dTYPE*)pnt^val));
		#ifdef FILE_error
		else throw Error("Оператор ^= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	void Clear(){
		if(pnt){
			switch(id){
				case 1:	delete static_cast<LOGIC*>(pnt);break;
				case 2:	delete static_cast<LETTER*>(pnt);break;
				case 3:	delete static_cast<RANGE*>(pnt);break;
				case 4:	delete static_cast<BYTE*>(pnt);break;
				case 5:	delete static_cast<INT_S*>(pnt);break;
				case 6:	delete static_cast<INT_W*>(pnt);break;
				case 7:	delete static_cast<INT_M*>(pnt);break;
				case 8:	delete static_cast<INT_L*>(pnt);break;
				case 9:	delete static_cast<INT_T*>(pnt);break;
				case 10:delete static_cast<INT_B*>(pnt);break;
				case 11:delete static_cast<FLOAT*>(pnt);break;
				case 12:delete static_cast<DOUBLE*>(pnt);break;
				case 13:delete static_cast<ADDRESS*>(pnt);break;
				case 14:delete static_cast<CHARS>(pnt);break;
				case 15:delete static_cast<STRING*>(pnt);break;
				case 16:delete static_cast<DATETIME*>(pnt);break;
			}
			LINK::Clear();
		}
	}
	/*#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<< (std::ostream &out,const ANY &obj){
		return out<<obj.lnk;
	}
	#endif*/
};
ID_TYPE(20,ANY)