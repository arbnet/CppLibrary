/** Типы данных
 * Библиотека OWNI */

#pragma once
#define FILE_types

//#include <typeinfo>
//#include <cstdlib>
//#include <stdio.h>
#include <ctime>
#include "_quasi.hpp"

typedef bool LOGIC;// Логический тип 0..1
typedef char CHAR;// Буква
typedef __INT8_TYPE__ RANGE;// Диапазон -128..127
typedef __UINT8_TYPE__ BYTE;// Байт 0..255
typedef __INT16_TYPE__ INT_S;// Целое число -32768..32767
typedef __UINT16_TYPE__ INT_W;// Целое число 0..65535
typedef wchar_t WCHAR;// Буква Юникода
typedef __INT32_TYPE__ INT_M;// Целое число -2147483648..2147483647
typedef __UINT32_TYPE__ INT_L;// Целое число 0..4294967295
typedef __INT64_TYPE__ INT_T;// Целое число -9223372036854775808..9223372036854775807
typedef __UINT64_TYPE__ INT_B;// Целое число 0..18446744073709551615
typedef float FLOAT;// Плавающее число 1.8E-38..1.8E+38		32b точность 6 .3 знаков
typedef double DOUBLE;// Плавающее число двойной точности 2.2E-308..1.8E+308	64b	точность 15 .6 знаков
typedef void* ADDRESS;// Указатель адреса

/** Нулевой указатель */
#ifndef NULL
#define NULL ((void *)0)
#endif
/** Пустые макросы _error */
#ifndef FILE_error
#define FIX
#define TRY
#define CATCH
#endif

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
ID_TYPE(2,CHAR)
ID_TYPE(3,RANGE)
ID_TYPE(4,BYTE)
ID_TYPE(5,INT_S)
ID_TYPE(6,INT_W)
ID_TYPE(7,WCHAR)
ID_TYPE(8,INT_M)
ID_TYPE(9,INT_L)
ID_TYPE(10,INT_T)
ID_TYPE(11,INT_B)
ID_TYPE(12,FLOAT)
ID_TYPE(13,DOUBLE)
ID_TYPE(14,ADDRESS)

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
	constexpr bool isBaseB=IsMatch<dTYPE,LOGIC,CHAR,RANGE,BYTE,INT_S,INT_W,INT_M,INT_L,INT_T,INT_B,FLOAT,DOUBLE,ADDRESS>::v;
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
class POINTER<CHAR> {
	void Kill(LOGIC grd){
		if(obj)obj->Kill(grd);else if(!grd)delete pnt;
		pnt=NULL;sz=tl=rv=0;
	}
protected:
	CHAR *pnt;
	INT_W sz=0,tl,rv;
	POINTER<CHAR> *obj=NULL;
	CHAR* Change(){
		CHAR *lts=NULL;
		if(rv){INT_W ntl=z::Volume(sz,rv);
			if(tl!=ntl){tl=ntl;lts=new CHAR[INT_L(tl+1)];}
		}
		return lts;
	}
	void Assign(const CHAR *pch){
		ADDRESS adr=pnt;
		if(sz){
			ADDRESS adl=(ADDRESS)pch;
			z::Copy(adr,adl,sz*sizeof(CHAR));
		}
		*(CHAR*)adr=0;
	}
public:
	/** защита от уничтожения */
	LOGIC guard=false;
	POINTER<CHAR>(INT_W tl=32,INT_W rv=0):tl(tl),rv(!tl && !rv?32:rv){
		pnt=new CHAR[tl+1];*(CHAR*)pnt=0;
	}
	POINTER<CHAR>(const CHAR *pch){
		sz=tl=z::Lsize(pch);rv=0;
		pnt=new CHAR[tl+1];Assign(pch);
	}
	POINTER<CHAR>(POINTER<CHAR> &obj):
		pnt(obj.pnt),sz(obj.sz),tl(obj.tl),obj(&obj){
			if(obj.guard)obj.guard=false;
	}
	~POINTER<CHAR>(){if(!obj)if(pnt)delete pnt;}
	explicit operator bool(){return pnt?true:false;}
  CHAR* operator*(){return pnt;}
	POINTER<CHAR>& operator=(const CHAR *pch){
		if(pnt){
			sz=z::Lsize(pch);
			if(CHAR *npt=Change()){
				delete []pnt;pnt=npt;
			}else	if(sz>tl)sz=tl;
			Assign(pch);
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
	friend std::ostream& operator<< (std::ostream &out,const POINTER<CHAR> &obj){
		return obj.sz?out<<(CHAR*)obj.pnt:out<<"NULL";
	}
	#endif
};

/** Указатель */
template<>
class POINTER<WCHAR> {
	void Kill(LOGIC grd){
		if(obj)obj->Kill(grd);else if(!grd)delete pnt;
		pnt=NULL;sz=tl=rv=0;
	}
protected:
	WCHAR *pnt;
	INT_W sz=0,tl,rv;
	POINTER<WCHAR> *obj=NULL;
	WCHAR* Change(){
		WCHAR *lts=NULL;
		if(rv){INT_W ntl=z::Volume(sz,rv);
			if(tl!=ntl){tl=ntl;lts=new WCHAR[INT_L(tl+1)];}
		}
		return lts;
	}
	void Assign(const WCHAR *pch){
		ADDRESS adr=pnt;
		if(sz){
			ADDRESS adl=(ADDRESS)pch;
			z::Copy(adr,adl,sz*sizeof(WCHAR));
		}
		*(WCHAR*)adr=0;
	}
public:
	/** защита от уничтожения */
	LOGIC guard=false;
	POINTER<WCHAR>(INT_W tl=64,INT_W rv=0):tl(tl),rv(!tl && !rv?64:rv){
		pnt=new WCHAR[tl+1];*(WCHAR*)pnt=0;
	}
	POINTER<WCHAR>(const WCHAR *pch){
		sz=tl=z::Lsize(pch);rv=0;
		pnt=new WCHAR[tl+1];Assign(pch);
	}
	POINTER<WCHAR>(POINTER<WCHAR> &obj):
		pnt(obj.pnt),sz(obj.sz),tl(obj.tl),obj(&obj){
			if(obj.guard)obj.guard=false;
	}
	~POINTER<WCHAR>(){if(!obj)if(pnt)delete pnt;}
	explicit operator bool(){return pnt?true:false;}
  WCHAR* operator*(){return pnt;}
	POINTER<WCHAR>& operator=(const WCHAR *pch){
		if(pnt){
			sz=z::Lsize(pch);
			if(WCHAR *npt=Change()){
				delete []pnt;pnt=npt;
			}else	if(sz>tl)sz=tl;
			Assign(pch);
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
	friend std::wostream& operator<< (std::wostream &out,const POINTER<WCHAR> &obj){
		return obj.sz?out<<(WCHAR*)obj.pnt:out<<"NULL";
	}
	#endif
};

ID_TYPE(21,POINTER<LOGIC>)
ID_TYPE(22,POINTER<CHAR>)
ID_TYPE(23,POINTER<RANGE>)
ID_TYPE(24,POINTER<BYTE>)
ID_TYPE(25,POINTER<INT_S>)
ID_TYPE(26,POINTER<INT_W>)
ID_TYPE(27,POINTER<WCHAR>)
ID_TYPE(28,POINTER<INT_M>)
ID_TYPE(29,POINTER<INT_L>)
ID_TYPE(30,POINTER<INT_T>)
ID_TYPE(31,POINTER<INT_B>)
ID_TYPE(32,POINTER<FLOAT>)
ID_TYPE(33,POINTER<DOUBLE>)
ID_TYPE(34,POINTER<ADDRESS>)

/** Строка */
class STRING {
enum STYPE{None,Char,WChar};
	STYPE mtp=None;// тип строки
	ADDRESS pnt;// указатель на строку
	INT_W tl,rv;// тотальный размер и резерв
	/** Сравнение строк */
	LOGIC Compare(ADDRESS adr,INT_W sz){
		return sz==sz?z::Compare(pnt,adr,sz):false;
	}
public:
	/** Конструктор строки для CHAR */
	STRING(const CHAR *chs){*this=chs;}
	/** Конструктор строки для WCHAR */
	STRING(const WCHAR *chs){*this=chs;}
	/** Конструктор строки с параметрами
	 * @param tl тотальный размер в памяти
	 * @param rv размер резервирования */
	STRING(INT_W tl=0,INT_W rv=0):tl(tl),rv(rv){}
	//STRING(const STRING &obj):POINTER<TCHAR>(obj.pnt){}
	
	explicit operator bool(){
		LOGIC res=false;
		if(mtp){
			if(mtp==Char){
				if(((POINTER<CHAR>*)pnt)->Size())res=true;
			}else{
				if(((POINTER<WCHAR>*)pnt)->Size())res=true;
			}
		}
		return res;
	}
	operator INT_W(){return mtp;}
	/*template<typename dTYPE, typename = t::Enable<t::isBaseB<dTYPE>,dTYPE>>
	STRING(dTYPE val){
		POINTER<TCHAR> pch;
		INT_W vid=::Type<dTYPE>::Id;
		if(vid==1)pch=val?"true":"false";
		else{sprintf(*pch,vid==11 || vid==12?"%f":"%d",val);pch.Size(true);}
		*this=*pch;
	}
	TCHAR& operator[](INT_L idx){
		z::Index(idx,sz);
		return pnt[idx];
	}*/
	STRING& operator=(const CHAR *pch){
		if(mtp!=Char){
			if(mtp!=None)Clear();
			pnt=new POINTER<CHAR>(pch);mtp=Char;
		}else *(POINTER<CHAR>*)pnt=pch;
		return *this;
	}
	STRING& operator=(const WCHAR *pch){
		if(mtp!=WChar){
			if(mtp!=None)Clear();
			pnt=new POINTER<WCHAR>(pch);mtp=WChar;
		}else *(POINTER<WCHAR>*)pnt=pch;
		return *this;
	}
	void Clear(){
		if(mtp){
			if(mtp==Char)delete (POINTER<CHAR>*)pnt;
			else delete (POINTER<WCHAR>*)pnt;
			mtp=None;pnt=NULL;
		}
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<< (std::ostream &out,STRING &obj){
		TRY
		if(obj.mtp==Char){
			POINTER<CHAR> *chs=(POINTER<CHAR>*)obj.pnt;
			out<<(chs->Size()?*chs:"NULL");
		}
		#ifdef FILE_error
		else throw Error(_L("cout<<Значение строки не CHAR!"));
		#endif
		CATCH
		return out;
	}
	friend std::wostream& operator<< (std::wostream &out,STRING &obj){
		TRY
		if(obj.mtp==WChar){
			POINTER<WCHAR> *chs=(POINTER<WCHAR>*)obj.pnt;
			out<<(chs->Size()?*chs:L"NULL");
		}
		#ifdef FILE_error
		else throw Error(_L("wcout<<Значение строки не WCHAR!"));
		#endif
		CATCH
		return out;
	}
	#endif
	/*STRING& operator=(const STRING &obj){
		sz=obj.sz;
		if(TCHAR* npt=Change()){
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
	/ ** Вставка подстроки
	 * @param obj подстрока
	 * @param idx индекс куда вставить * /
	void Put(const STRING &obj,INT_W idx=0){
		if(INT_W psz=obj.sz){
			if(INT_L(sz+psz)>(rv?65535:tl))psz=(rv?65535:tl)-sz;
			if(psz){
				ADDRESS adr1,adr2,adr3;
				INT_W osz=sz;sz+=psz;
				if(!idx)idx=osz;else z::Index(idx,sz);
				if(TCHAR* lts=Change()){
					adr1=(ADDRESS)lts;adr2=(ADDRESS)pnt;
					if(idx)z::Copy(adr1,adr2,idx);
					adr3=(ADDRESS)obj.pnt;
					z::Copy(adr1,adr3,psz);
					z::Copy(adr1,adr2,osz-idx);
					*(TCHAR*)adr1=0;
					delete []pnt;pnt=lts;
				}else{
					adr1=adr2=(ADDRESS)pnt;
					z::Shift(adr1,sz);z::Shift(adr2,osz);
					*(TCHAR*)adr1=0;z::Copy(adr1,adr2,-(osz-idx));
					adr3=(ADDRESS)obj.pnt;z::Shift(adr3,psz);
					z::Copy(adr1,adr3,-psz);
				}
			}
		}
	}
	/ ** Вырезать
	 * @param idx индекс места вырезки
	 * @param csz размер для вырезки * /
	void Cut(INT_W idx=-1,INT_W csz=0){
		if(sz){
			if(!csz)csz++;
			z::Index(idx,sz);
			if(idx+csz>sz)csz=sz-idx;
			if(csz){
				ADDRESS adr1,adr2;
				INT_W osz=sz;sz=sz-csz;
				if(TCHAR* npt=Change()){
					delete []pnt;pnt=npt;
					adr1=(ADDRESS)npt;adr2=(ADDRESS)pnt;
					if(idx)z::Copy(adr1,adr2,idx);
					z::Shift(adr2,csz);idx+=csz;
					z::Copy(adr1,adr2,osz-idx);
				}else{
					adr1=(ADDRESS)pnt;
					if(idx)z::Shift(adr1,idx);
					adr2=adr1;z::Shift(adr2,csz);
					idx+=csz;z::Copy(adr1,adr2,osz-idx);
				}
				*(TCHAR*)adr1=0;
			}
		}
	}
	/ ** Вырезать
	 * @param obj подстрока
	 * @param idx индекс поиска * /
	void Cut(const STRING &obj,INT_W idx=0){
		idx=this->Find(obj,idx);
		if(idx)Cut(idx,obj.sz);
	}
	/ ** Поиск позиции подстроки
	 * @param obj подстрока
	 * @param idx индекс начала поиска
	 * @return индекс позиции * /
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
	*/
};
ID_TYPE(15,STRING)
ID_TYPE(35,POINTER<STRING>)

/* * ДатаВремя * /
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
	/ ** Время выполнения * /
	void Clock(){this->dtm=clock();}
	/ ** Текущее время * /
	void Now(){this->dtm=time(NULL);}
	/ ** Получение строкового представления даты-времени
	 * @param fmt формат даты-времени
	 * @param bsz размер буфера формирования строки
	 * @return строка с датой-временем * /
	STRING Format(STRING fmt=_L("%Y.%m.%d %H:%M:%S"),INT_W sbf=64){
		TCHAR res[sbf];
		#ifndef UNICODE
		strftime(res,sbf,*fmt,localtime(&dtm));
		#else
		wcsftime(res,sbf,*fmt,localtime(&dtm));
		#endif
		return STRING(res);
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<< (std::ostream &out,const DATETIME &obj){
		return out<<obj.dtm;
	}
	friend std::wostream& operator<< (std::wostream &out,const DATETIME &obj){
		return out<<obj.dtm;
	}
	#endif
};
ID_TYPE(16,DATETIME)

//ID_TYPE(17,резерв)
//ID_TYPE(18,резерв)

/ ** Пространство имёт от _types * /
namespace t {
	/ ** Проверка на основной тип данных * /
	template <typename dTYPE>
	constexpr bool isBaseA=IsMatch<dTYPE,LOGIC,CHAR,RANGE,BYTE,INT_S,INT_W,WCHAR,INT_M,INT_L,INT_T,INT_B,FLOAT,DOUBLE,ADDRESS,STRING,DATETIME>::v;

	/ ** Получение Id переменной
	 * @param var переменная 
	 * @return Id переменной * /
	template<typename dTYPE>
	INT_W Id(dTYPE var){
		return ::Type<dTYPE>::Id;
	}
	/ ** Получение типа переменной
	 * @param var переменная 
	 * @return тип переменной * /
	template<typename dTYPE>
	STRING Type(dTYPE var){
		STRING vtp;
		if(::Type<dTYPE>::Id)vtp=::Type<dTYPE>::Name;
		else{vtp=typeid(var).name();
			INT_W nx=0,sz=vtp.Size();
  		while(nx++<sz){BYTE sb=vtp[nx];
    		if(sb<48 || sb>57){nx--;break;}
  		}
  		vtp.Cut(1,nx);
		}
  	return vtp;
	}
}


/ * * Ссылка * /
class LINK {
protected:
	STRING tp;
	ADDRESS pnt=NULL;
	INT_W id=0,sz=0;
public:
	LINK(){}
	template<typename dTYPE>
	LINK(dTYPE &obj){this->Init(obj);}
	LINK(const LINK &obj):tp(obj.tp),id(obj.id),sz(obj.sz),pnt(obj.pnt){}
	ADDRESS operator*(){return pnt;}
	//operator CHAR*(){return (CHAR*)pnt;}
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
	/ ** Получение Id данных * /
	INT_W Id(){return id;}
	/ ** Размер данных * /
	INT_W Size(){return sz;}
	/ ** Тип данных * /
	STRING Type(){return tp;}
	/ ** Инициализация
	 * @param obj объект * /
	template<typename dTYPE>
	void Init(dTYPE &obj){
		pnt=&obj;tp=t::Type(obj);id=::Type<dTYPE>::Id;sz=sizeof(dTYPE);
	}
	/ ** Инициализация
	 * @param chs массив символов * /
	void Init(const TCHAR *chs){
		pnt=(ADDRESS)chs;
		sz=z::Lsize(chs);
		id=::Type<TCHAR>::Id;
		tp=::Type<TCHAR>::Name;
	}
	/ ** Очистка ссылки * /
	void Clear(){
		sz=id=0;tp=_L("");pnt=NULL;
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<<(std::ostream &out,const LINK &obj){
		if(obj.pnt){
			switch(obj.id){
				case 1:	out<<(*(LOGIC*)obj.pnt?"true":"false");break;
				case 2:	out<<*(CHAR*)obj.pnt;break;
				case 3:	out<<(INT_S)*(RANGE*)obj.pnt;break;
				case 4:	out<<(INT_W)*(BYTE*)obj.pnt;break;
				case 5:	out<<*(INT_S*)obj.pnt;break;
				case 6:	out<<*(INT_W*)obj.pnt;break;
				case 7: out<<*(WCHAR*)obj.pnt;break;
				case 8:	out<<*(INT_M*)obj.pnt;break;
				case 9:	out<<*(INT_L*)obj.pnt;break;
				case 10:out<<*(INT_T*)obj.pnt;break;
				case 11:out<<*(INT_B*)obj.pnt;break;
				case 12:out<<*(FLOAT*)obj.pnt;break;
				case 13:out<<*(DOUBLE*)obj.pnt;break;
				case 14:out<<*(ADDRESS*)obj.pnt;break;
				case 15:out<<*(STRING*)obj.pnt;break;
				case 16:out<<*(DATETIME*)obj.pnt;break;
				case 32:out<<*(POINTER<CHAR>*)obj.pnt;break;
				case 37:out<<*(POINTER<WCHAR>*)obj.pnt;break;
				default:out<<obj.tp;
			}
		}else out<<"NULL";
		return out;
	}
	#endif
};
ID_TYPE(19,LINK)
*/