/** Типы данных
 * Библиотека OWNI */

#pragma once
#define FILE_types

#include <typeinfo>
#include <cstdlib>
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
	/** Проверка на основной тип данных */
	template <typename dTYPE>
	constexpr bool isBase=IsMatch<dTYPE,LOGIC,LETTER,RANGE,BYTE,INT_S,INT_W,INT_M,INT_L,INT_T,INT_B,FLOAT,DOUBLE,ADDRESS>::v;
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
	LOGIC guard=false;
	POINTER<CHARS>(INT_W tl=32,INT_W rv=0):tl(tl),rv(!tl && !rv?32:rv){
		pnt=new LETTER[tl+1];*(BYTE*)pnt=0;
	}
	POINTER<CHARS>(const LETTER *lts){
		sz=tl=z::Lsize(lts);rv=0;
		pnt=new LETTER[tl+1];
		Assign(lts);
	}
	POINTER<CHARS>(POINTER<CHARS> &obj):
		pnt(obj.pnt),sz(obj.sz),tl(obj.tl),obj(&obj){
			if(obj.guard)obj.guard=false;
	}
	~POINTER<CHARS>(){if(!obj)if(pnt)delete pnt;}
	explicit operator bool(){return pnt?true:false;}
  LETTER* operator*(){return (LETTER*)pnt;}
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
  void Kill(){
		if(pnt){
			if(obj)obj->Kill(guard);else delete pnt;
			if(!guard){pnt=NULL;sz=tl=rv=0;}
		}
	}
	INT_W Size(LOGIC sgn=false){
		if(sgn)sz=z::Lsize(pnt);
		return sz;
	}
	INT_W Total(){return tl;}
	INT_W Reserve(){return rv;}
	void Reserve(INT_W rv){this->rv=rv;}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<< (std::ostream &out,const POINTER<CHARS> &obj){
		return obj.sz?out<<(LETTER*)obj.pnt:out<<"NULL";
	}
	#endif
};

//ID_TYPE(14,POINTER)

/** Строка */
class STRING :public POINTER<CHARS> {
	/*
	LOGIC Compare(ADDRESS pnt,INT_W sz){
		return sz==sz?z::Compare(str,pnt,sz):false;
	}*/
public:
	//STRING(const STRING &obj): mdt(obj.mdt),dbl(true){
	//	cout<<"Cr1"<<endl;
	//}
	STRING(INT_W tl=0,INT_W rv=0):POINTER<CHARS>(tl,rv){}
	STRING(const LETTER *lts):POINTER<CHARS>(lts){}
	explicit operator bool(){return sz?true:false;}
	template<typename dTYPE, typename = t::Enable<t::isInteger<dTYPE>,dTYPE>>
	STRING(dTYPE val){
		POINTER<CHARS> lts;
		sprintf(*lts,"%d",val);lts.Size(true);
		cout<<"VVV="<<*lts<<' '<<lts.Size()<<' '<<lts.Total()<<endl;
		//POINTER<CHARS>::operator=(lts);
	}
	LETTER& operator[](INT_L idx){
		z::Index(idx,sz);
		return pnt[idx];
	}
	STRING& operator=(const LETTER *lts){
		POINTER<CHARS>::operator=(lts);
		return *this;
	}
	/*
	
	STRING& operator=(const LETTER *ltr){
		this->Assign((ADDRESS)ltr,z::Lsize(ltr));
		return *this;
	}
	STRING& operator=(const STRING &obj){
		this->Assign(obj.str,obj.sz);
		return *this;
	}
	
	STRING& operator+=(const STRING &obj){
		this->Put(obj);
		return *this;
	}
	STRING& operator-=(const STRING &obj){
		this->Cut(obj);
		return *this;
	}
	LOGIC operator==(const STRING &obj){
		return this->Compare(obj.str,obj.sz);
	}
	LOGIC operator!=(const STRING &obj){
		return !this->Compare(obj.str,obj.sz);
	}
	*/
	/*void Put(const STRING &obj,INT_W index=0){
		if(INT_W sz=obj.mdt->sz){
			if(INT_L(mdt->sz+sz)>(mdt->mr?65535:mdt->tl))
				sz=(mdt->mr?65535:mdt->tl)-mdt->sz;
			if(sz){
				POINTER pnt1,pnt2,pntt;
				if(!index)index=mdt->sz;
				else z::Index(index,mdt->sz);
				if(LETTER* str=this->Change(mdt->sz+sz)){
					pnt1=(POINTER)str;pnt2=(POINTER)mdt->str;
					if(index)z::Copy(pnt1,pnt2,index);
					pntt=pnt2;pnt2=(POINTER)obj.mdt->str;
					z::Copy(pnt1,pnt2,sz);pnt2=pntt;
					z::Copy(pnt1,pnt2,mdt->sz-index);
					*(BYTE*)pnt1=0;
					delete []mdt->str;mdt->str=str;
				}else{
					pnt1=(POINTER)mdt->str;z::Shift(pnt1,mdt->sz);
					pnt2=pnt1;z::Shift(pnt1,sz);*(BYTE*)pnt1=0;
					z::Copy(pnt1,pnt2,-(mdt->sz-index));
					pnt1=pnt2;pnt2=(POINTER)obj.mdt->str;
					z::Copy(pnt1,pnt2,sz);
				}
				mdt->sz+=sz;
			}
		}
	}
	void Cut(INT_W index,INT_W size){
		if(size && mdt->sz){
			z::Index(index,mdt->sz);
			if(index+size>mdt->sz)size=mdt->sz-index;
			POINTER pnt1,pnt2;
			if(LETTER* str=this->Change(mdt->sz-size)){
				pnt1=(POINTER)str;pnt2=(POINTER)mdt->str;
				if(index)z::Copy(pnt1,pnt2,index);
				z::Shift(pnt2,size);index+=size;
				z::Copy(pnt1,pnt2,mdt->sz-index);
				delete []mdt->str;mdt->str=str;
			}else{
				pnt1=(POINTER)mdt->str;
				if(index)z::Shift(pnt1,index);
				pnt2=pnt1;z::Shift(pnt2,size);
				index+=size;z::Copy(pnt1,pnt2,mdt->sz-index);
			}
			*(BYTE*)pnt1=0;mdt->sz-=size;
		}
	}
	void Cut(const STRING &obj,INT_W index=0){
		index=this->Find(obj,index);
		if(index)this->Cut(index,obj.mdt->sz);
	}
	INT_W Find(const STRING &obj,INT_W index=0){
		INT_W res=0;
		if(mdt->sz){
			z::Index(index,mdt->sz);
			POINTER pse=mdt->str;
			if(index>0)z::Shift(pse,index);
			for(INT_W lmx=mdt->sz-obj.mdt->sz;index<=lmx;index++){
				if(z::Compare(pse,obj.mdt->str,obj.mdt->sz)){res=index+1;break;}
				z::Shift(pse);
			}
		}
		return res;
	}
	*/
};
ID_TYPE(15,STRING)

/* * ДатаВремя * /
class DATETIME {
private:
	time_t dtm;
public:
	DATETIME(time_t dtm=0){this->dtm=dtm;}
	DATETIME(const DATETIME &obj): dtm(obj.dtm){}
	INT_B operator *(){return (INT_B)this->dtm;}
	operator time_t(){return this->dtm;}
	DATETIME& operator=(time_t val){
		this->dtm=val;return *this;
	}
	DATETIME& operator+=(time_t val){
		this->dtm+=val;return *this;
	}
	DATETIME& operator-=(time_t val){
		this->dtm-=val;return *this;
	}
	void Clock(){this->dtm=clock();}
	void Now(){this->dtm=time(NULL);}
	void Data(DateTime sdt){
		DateTimeU udt;
		udt.dtm=sdt;
		this->dtm=mktime(&udt.stm);
	}
	DateTime Data(){
		DateTimeU udt;
		udt.stm=*localtime(&this->dtm);
		return udt.dtm;
	}
	STRING Format(STRING fmt="%Y.%m.%d %H:%M:%S",BYTE sz=64){
		LETTER res[sz];
		strftime(res,sz,*fmt,localtime(&this->dtm));
		return STRING(res);
	}
};
ID_TYPE(14,DATETIME)

/ ** Ссылка * /
class LINK {
private:
	STRING vtp;
	POINTER pnt=NULL;
	INT_W vsz=0,idt=0;
public:
	LINK(){}
	template<typename dTYPE>
	LINK(dTYPE &obj){this->Init(obj);}
	LINK(const LINK &obj):idt(obj.idt),vsz(obj.vsz),vtp(obj.vtp),pnt(obj.pnt){}
	POINTER operator *(){return pnt;}
	template <typename dTYPE>
	operator dTYPE(){return *(dTYPE*)pnt;}
	explicit operator bool(){return pnt?true:false;}
	template<typename dTYPE>
	t::Enable<t::isBase<dTYPE>,LINK&> operator=(dTYPE val){
		TRY
		if(idt==::Type<dTYPE>::Id)*(dTYPE*)pnt=val;
		#ifdef FILE_error
		else throw Error("LINK = не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	INT_W Id(){return this->idt;}
	INT_W Size(){return this->vsz;}
	STRING Type(){return this->vtp;}
	template<typename dTYPE>
	void Init(dTYPE &obj){
		pnt=&obj;
		vsz=sizeof(dTYPE);
		idt=::Type<dTYPE>::Id;
		vtp=::Type<dTYPE>::Name;
	}
	void Clear(){
		pnt=NULL;vsz=idt=0;vtp="";
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<<(std::ostream &out,const LINK &obj){
		if(obj.pnt){
			switch(obj.idt){
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
				case 13:out<<*(POINTER*)obj.pnt;break;
				case 14:out<<*(DATETIME*)obj.pnt;break;
				case 15:out<<*(STRING*)obj.pnt;break;
				default:out<<obj.vtp;
			}
		}else out<<"NULL";
		return out;
	}
	#endif
};
ID_TYPE(16,LINK)

//ID_TYPE(17,резерв)
//ID_TYPE(18,резерв)
//ID_TYPE(19,резерв)

/ ** Любой тип * /
class ANY {
private:
	LINK lnk;
	void Clear(){
		if(lnk){
			switch(lnk.Id()){
				case 1:	delete static_cast<LOGIC*>(*lnk);break;
				case 2:	delete static_cast<LETTER*>(*lnk);break;
				case 3:	delete static_cast<RANGE*>(*lnk);break;
				case 4:	delete static_cast<BYTE*>(*lnk);break;
				case 5:	delete static_cast<INT_S*>(*lnk);break;
				case 6:	delete static_cast<INT_W*>(*lnk);break;
				case 7:	delete static_cast<INT_M*>(*lnk);break;
				case 8:	delete static_cast<INT_L*>(*lnk);break;
				case 9:	delete static_cast<INT_T*>(*lnk);break;
				case 10:delete static_cast<INT_B*>(*lnk);break;
				case 11:delete static_cast<FLOAT*>(*lnk);break;
				case 12:delete static_cast<DOUBLE*>(*lnk);break;
				case 13:delete static_cast<POINTER*>(*lnk);break;
				case 14:delete static_cast<DATETIME*>(*lnk);break;
				case 15:delete static_cast<STRING*>(*lnk);break;
				default:delete static_cast<LINK*>(*lnk);
			}
			lnk.Clear();
		}
	}
public:
	ANY(){}
	template <typename dTYPE>
	ANY(dTYPE val){*this=val;}
	ANY(const ANY &obj): lnk(obj.lnk){}
	~ANY(){Clear();}
	explicit operator bool(){return (LOGIC)lnk;}
	template <typename dTYPE>
	explicit operator dTYPE(){return (dTYPE)lnk;}
	template <typename dTYPE>
	ANY& operator=(dTYPE val){
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=val;
		else{
			Clear();
			if(!z::isNULL(val)){
				dTYPE *obj=new dTYPE(val);
				lnk.Init(*obj);
			}
		}
		return *this;
	}
	ANY& operator=(CHARS(ltr)){
		STRING *str=new STRING(ltr);*this=*str;
		return *this;
	}
	ANY& operator++(int){
		switch(lnk.Id()){
			case 1:	lnk=(LOGIC)((LOGIC)lnk?0:1);break;
			case 2:	lnk=(LETTER)((LETTER)lnk+1);break;
			case 3:	lnk=(RANGE)((RANGE)lnk+1);break;
			case 4:	lnk=(BYTE)((BYTE)lnk+1);break;
			case 5:	lnk=(INT_S)((INT_S)lnk+1);break;
			case 6:	lnk=(INT_W)((INT_W)lnk+1);break;
			case 7:	lnk=(INT_M)((INT_M)lnk+1);break;
			case 8:	lnk=(INT_L)((INT_L)lnk+1);break;
			case 9:	lnk=(INT_T)((INT_T)lnk+1);break;
			case 10:lnk=(INT_B)((INT_B)lnk+1);break;
			case 11:lnk=(FLOAT)lnk+(FLOAT)0.01;break;
			case 12:lnk=(DOUBLE)lnk+(DOUBLE)0.0001;break;
			//case 13:lnk=(POINTER)lnk+1;break;
			//case 14:lnk=(DATETIME)lnk+1;break;
			//case 15:lnk=(STRING)lnk+1;break;
			//default:
		}
		return *this;
	}
	ANY& operator--(int){
		switch(lnk.Id()){
			case 1:	lnk=(LOGIC)((LOGIC)lnk?0:1);break;
			case 2:	lnk=(LETTER)((LETTER)lnk-1);break;
			case 3:	lnk=(RANGE)((RANGE)lnk-1);break;
			case 4:	lnk=(BYTE)((BYTE)lnk-1);break;
			case 5:	lnk=(INT_S)((INT_S)lnk-1);break;
			case 6:	lnk=(INT_W)((INT_W)lnk-1);break;
			case 7:	lnk=(INT_M)((INT_M)lnk-1);break;
			case 8:	lnk=(INT_L)((INT_L)lnk-1);break;
			case 9:	lnk=(INT_T)((INT_T)lnk-1);break;
			case 10:lnk=(INT_B)((INT_B)lnk-1);break;
			case 11:lnk=(FLOAT)lnk-(FLOAT)0.01;break;
			case 12:lnk=(DOUBLE)lnk-(DOUBLE)0.0001;break;
			//case 13:lnk=(POINTER)lnk+1;break;
			//case 14:lnk=(DATETIME)lnk+1;break;
			//case 15:lnk=(STRING)lnk+1;break;
			//default:
		}
		return *this;
	}
	template <typename dTYPE>
	ANY& operator+(dTYPE val){
		TRY
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=(dTYPE)lnk+val;
		#ifdef FILE_error
		else throw Error("Оператор + не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template <typename dTYPE>
	ANY& operator-(dTYPE val){
		TRY
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=(dTYPE)lnk-val;
		#ifdef FILE_error
		else throw Error("Оператор - не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template <typename dTYPE>
	ANY& operator*(dTYPE val){
		TRY
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=(dTYPE)lnk*val;
		#ifdef FILE_error
		else throw Error("Оператор * не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template <typename dTYPE>
	ANY& operator/(dTYPE val){
		TRY
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=(dTYPE)lnk/val;
		#ifdef FILE_error
		else throw Error("Оператор / не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template <typename dTYPE>
	ANY& operator+=(dTYPE val){
		TRY
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=(dTYPE)lnk+val;
		#ifdef FILE_error
		else throw Error("Оператор += не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template <typename dTYPE>
	ANY& operator-=(dTYPE val){
		TRY
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=(dTYPE)lnk-val;
		#ifdef FILE_error
		else throw Error("Оператор -= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template <typename dTYPE>
	ANY& operator*=(dTYPE val){
		TRY
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=(dTYPE)lnk*val;
		#ifdef FILE_error
		else throw Error("Оператор *= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template <typename dTYPE>
	ANY& operator/=(dTYPE val){
		TRY
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=(dTYPE)lnk/val;
		#ifdef FILE_error
		else throw Error("Оператор /= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template <typename dTYPE>
	ANY& operator%=(dTYPE val){
		TRY
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=(dTYPE)lnk%val;
		#ifdef FILE_error
		else throw Error("Оператор %= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template <typename dTYPE>
	ANY& operator&=(dTYPE val){
		TRY
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=(dTYPE)lnk&val;
		#ifdef FILE_error
		else throw Error("Оператор &= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template <typename dTYPE>
	ANY& operator|=(dTYPE val){
		TRY
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=(dTYPE)lnk|val;
		#ifdef FILE_error
		else throw Error("Оператор |= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	template <typename dTYPE>
	ANY& operator^=(dTYPE val){
		TRY
		if(lnk.Id()==::Type<dTYPE>::Id)lnk=(dTYPE)lnk^val;
		#ifdef FILE_error
		else throw Error("Оператор ^= не соответствует типу!");
		#endif
		CATCH
		return *this;
	}
	INT_W Id(){return lnk.Id();}
	INT_W Size(){return lnk.Size();}
	STRING Type(){return lnk.Type();}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<< (std::ostream &out,const ANY &obj){
		return out<<obj.lnk;
	}
	#endif
}; 
ID_TYPE(20,ANY)

/ ** Пространство имёт от _types * /
namespace t{
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
			LETTER *lts=new LETTER[20];
  		INT_M len=vtp.Size()-1;
  		_itoa(len,lts,10);vtp-=lts;
		}
  	return vtp;
	}
}
*/