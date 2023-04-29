/** Типы данных
 * Библиотека OWNI */

#ifndef FILE_types

#include <string>
#include "time.h"
using namespace std;

/** Пустые макросы _error */
#ifndef FILE_error
#define FIX
#define TRY
#define CATCH
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
typedef void* POINTER;// Указатель

/** Массив символов */
#define CHARS(ltr) const char ltr[]

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

/** Союз tm & DateTime */
union DatetimeU {
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

	/** Поменять местами переменные
	 * @param var1 переменная 1
	 * @param var2 переменная 2	*/
	template <typename dTYPE>
	void Swap(dTYPE &var1, dTYPE &var2){
		dTYPE tmp(var1);var1=var2;var2=tmp;
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
	void Shift(POINTER &pnt,INT_S shift=1){
		pnt=(POINTER*)((INT_B)pnt+shift);
	}
	/** Заполнение памяти значением
	 * @param pnt указатель адреса
	 * @param size размер\\длинна
	 * @param val значение */
	template <typename dTYPE=BYTE>
	void Fill(POINTER &pnt,INT_W size,dTYPE val=0){
		while(size>0){
			*(dTYPE*)pnt=val;Shift(pnt,sizeof(dTYPE));size--;
		}
	}
	/** Копирование в памяти
	 * @param pnt1 указатель адреса 1
	 * @param pnt2 указатель адреса 2
	 * @param size размер */
	void Copy(POINTER &pnt1,POINTER &pnt2,INT_M size){
		INT_W ct;
		if(size>0){
			ct=size/8;
			if(ct>0){size=size%8;
				do{
					*(INT_B*)pnt1=*(INT_B*)pnt2;
					Shift(pnt1,8);Shift(pnt2,8);ct--;
				}while(ct>0);
			}
			ct=size/4;
			if(ct>0){size=size%4;
				do{
					*(INT_L*)pnt1=*(INT_L*)pnt2;
					Shift(pnt1,4);Shift(pnt2,4);ct--;
				}while(ct>0);
			}
			ct=size/2;
			if(ct>0){size=size%2;
				do{
					*(INT_W*)pnt1=*(INT_W*)pnt2;
					Shift(pnt1,2);Shift(pnt2,2);ct--;
				}while(ct>0);
			}
			if(size>0){ct=size;
				do{
					*(BYTE*)pnt1=*(BYTE*)pnt2;
					Shift(pnt1,1);Shift(pnt2,1);ct--;
				}while(ct>0);
			}
		}else{size=-size;
			ct=size/8;
			if(ct>0){size=size%8;
				do{
					Shift(pnt1,-8);Shift(pnt2,-8);ct--;
					*(INT_B*)pnt1=*(INT_B*)pnt2;
				}while(ct>0);
			}
			ct=size/4;
			if(ct>0){size=size%4;
				do{
					Shift(pnt1,-4);Shift(pnt2,-4);ct--;
					*(INT_L*)pnt1=*(INT_L*)pnt2;
				}while(ct>0);
			}
			ct=size/2;
			if(ct>0){size=size%2;
				do{
					Shift(pnt1,-2);Shift(pnt2,-2);ct--;
					*(INT_W*)pnt1=*(INT_W*)pnt2;
				}while(ct>0);
			}
			if(size>0){ct=size;
				do{
					Shift(pnt1,-1);Shift(pnt2,-1);ct--;
					*(BYTE*)pnt1=*(BYTE*)pnt2;
				}while(ct>0);
			}
		}
	}
	/** Сравнение памяти
	 * @param pnt1 указатель адреса 1
	 * @param pnt2 указатель адреса 2
	 * @param size размер\\длинна */
	LOGIC Compare(POINTER pnt1,POINTER pnt2,INT_W size){
		LOGIC res=true;
		while(size>0){
			if(size>=8){
				if(*(INT_B*)pnt1!=*(INT_B*)pnt2)res=false;
				else{Shift(pnt1,8);Shift(pnt2,8);size-=8;}
			}else if(size>=4){
				if(*(INT_L*)pnt1!=*(INT_L*)pnt2)res=false;
				else{Shift(pnt1,4);Shift(pnt2,4);size-=4;}
			}else if(size>=2){
				if(*(INT_W*)pnt1!=*(INT_W*)pnt2)res=false;
				else{Shift(pnt1,2);Shift(pnt2,2);size-=2;}
			}else{
				if(*(BYTE*)pnt1!=*(BYTE*)pnt2)res=false;
				else{Shift(pnt1,1);Shift(pnt2,1);size-=1;}
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
}

/** Строка */
class STRING {
struct Data {
	INT_W mr=0,sz=0,tl=0;
	LETTER* str=NULL;
};
private:
	Data *mdt;
	LOGIC dbl=false;
	void Init(INT_W tl=0,INT_W mr=0){
		if(this->dbl){
			mdt=new Data;dbl=false;
		}else if(mdt->str){
			delete []mdt->str;mdt->sz=0;
		}
		mdt->tl=tl;mdt->mr=mr;
		mdt->str=new LETTER[INT_L(tl+1)];
	}
	LETTER* Change(INT_W sz){
		LETTER* str=NULL;
		if(mdt->mr){
			INT_W ntx=t::Volume(sz,mdt->mr);
			if(mdt->tl!=ntx){
				mdt->tl=ntx;str=new LETTER[INT_L(ntx+1)];
			}
		}
		return str;
	}
	void Assign(POINTER pnt,INT_W sz){
		if(LETTER* str=this->Change(sz)){
			delete []mdt->str;mdt->str=str;
		}else{
			if(mdt->tl<sz)sz=mdt->tl;
		}
		POINTER adr=mdt->str;
		if(sz)t::Copy(adr,pnt,sz);
		*(BYTE*)adr=0;
		if(mdt->sz!=sz)mdt->sz=sz;
	}
	LOGIC Compare(POINTER pnt,INT_W sz){
		return mdt->sz==sz?t::Compare(mdt->str,pnt,sz):false;
	}
public:
	STRING(const STRING &obj): mdt(obj.mdt),dbl(true){}
	STRING(INT_W tl=0,INT_W mr=0){
		this->mdt=new Data;if(!tl && !mr)mr=32;this->Init(tl,mr);
	}
	STRING(CHARS(ltr)){
		INT_W sz=t::Lsize(ltr);
		this->mdt=new Data;this->Init(sz,sz?0:32);
		this->Assign((POINTER)ltr,sz);
	}
	~STRING(){if(!this->dbl){delete []mdt->str;delete this->mdt;}}
	operator bool(){return mdt->sz?true:false;}
	const LETTER* operator*(){return mdt->str;}
	LETTER& operator[](INT_L index){
		t::Index(index,mdt->sz);
		return mdt->str[index];
	}
	STRING& operator=(const LETTER *ltr){
		this->Assign((POINTER)ltr,t::Lsize(ltr));
		return *this;
	}
	STRING& operator=(const STRING &obj){
		this->Assign(obj.mdt->str,obj.mdt->sz);
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
		return this->Compare(obj.mdt->str,obj.mdt->sz);
	}
	LOGIC operator!=(const STRING &obj){
		return !this->Compare(obj.mdt->str,obj.mdt->sz);
	}
	INT_W Size(){return mdt->sz;}
	INT_W Total(){return mdt->tl;}
	INT_W Reserve(){return mdt->mr;}
	void Reserve(INT_W mr){mdt->mr=mr;}
	void Put(const STRING &obj,INT_W index=0){
		if(INT_W sz=obj.mdt->sz){
			if(INT_L(mdt->sz+sz)>(mdt->mr?65535:mdt->tl))
				sz=(mdt->mr?65535:mdt->tl)-mdt->sz;
			if(sz){
				POINTER pnt1,pnt2,pntt;
				if(!index)index=mdt->sz;
				else t::Index(index,mdt->sz);
				if(LETTER* str=this->Change(mdt->sz+sz)){
					pnt1=(POINTER)str;pnt2=(POINTER)mdt->str;
					if(index)t::Copy(pnt1,pnt2,index);
					pntt=pnt2;pnt2=(POINTER)obj.mdt->str;
					t::Copy(pnt1,pnt2,sz);pnt2=pntt;
					t::Copy(pnt1,pnt2,mdt->sz-index);
					*(BYTE*)pnt1=0;
					delete []mdt->str;mdt->str=str;
				}else{
					pnt1=(POINTER)mdt->str;t::Shift(pnt1,mdt->sz);
					pnt2=pnt1;t::Shift(pnt1,sz);*(BYTE*)pnt1=0;
					t::Copy(pnt1,pnt2,-(mdt->sz-index));
					pnt1=pnt2;pnt2=(POINTER)obj.mdt->str;
					t::Copy(pnt1,pnt2,sz);
				}
				mdt->sz+=sz;
			}
		}
	}
	void Cut(INT_W index,INT_W size){
		if(size && mdt->sz){
			t::Index(index,mdt->sz);
			if(index+size>mdt->sz)size=mdt->sz-index;
			POINTER pnt1,pnt2;
			if(LETTER* str=this->Change(mdt->sz-size)){
				pnt1=(POINTER)str;pnt2=(POINTER)mdt->str;
				if(index)t::Copy(pnt1,pnt2,index);
				t::Shift(pnt2,size);index+=size;
				t::Copy(pnt1,pnt2,mdt->sz-index);
				delete []mdt->str;mdt->str=str;
			}else{
				pnt1=(POINTER)mdt->str;
				if(index)t::Shift(pnt1,index);
				pnt2=pnt1;t::Shift(pnt2,size);
				index+=size;t::Copy(pnt1,pnt2,mdt->sz-index);
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
			t::Index(index,mdt->sz);
			POINTER pse=mdt->str;
			if(index>0)t::Shift(pse,index);
			for(INT_W lmx=mdt->sz-obj.mdt->sz;index<=lmx;index++){
				if(t::Compare(pse,obj.mdt->str,obj.mdt->sz)){res=index+1;break;}
				t::Shift(pse);
			}
		}
		return res;
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<< (std::ostream &out,const STRING &obj){
		return obj.mdt->sz?out<<obj.mdt->str:out<<"NULL";
	}
	#endif
};

/** ДатаВремя */
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
		DatetimeU udt;
		udt.dtm=sdt;
		this->dtm=mktime(&udt.stm);
	}
	DateTime Data(){
		DatetimeU udt;
		udt.stm=*localtime(&this->dtm);
		return udt.dtm;
	}
	STRING Format(STRING fmt="%Y.%m.%d %H:%M:%S",BYTE sz=64){
		LETTER res[sz];
		strftime(res,sz,*fmt,localtime(&this->dtm));
		return STRING(res);
	}
};

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
ID_TYPE(13,POINTER)
ID_TYPE(14,DATETIME)
ID_TYPE(15,STRING)

/** Пространство имёт от _types */
namespace t{
	/** Все основные типы данных */
	template <typename dTYPE>
	constexpr bool isBaseA=IsMatch<dTYPE,LOGIC,LETTER,RANGE,BYTE,INT_S,INT_W,INT_M,INT_L,INT_T,INT_B,FLOAT,DOUBLE,POINTER,DATETIME,STRING>::v;
	/** Основные типы данных */
	template <typename dTYPE>
	constexpr bool isBaseB=IsMatch<dTYPE,LOGIC,LETTER,RANGE,BYTE,INT_S,INT_W,INT_M,INT_L,INT_T,INT_B,FLOAT,DOUBLE,POINTER>::v;

	/** Конвертация типа данных
	 * @param val значение
	 * @return значение с новым типом */
	template <typename dTYPE,typename nTYPE>
	nTYPE convert(dTYPE val){
		return static_cast<nTYPE>(val);
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
};

/* Ссылка */
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
	t::Enable<t::isBaseB<dTYPE>,LINK&> operator=(dTYPE val){
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
			switch(obj.idt){//,
			//(*(LOGIC*)obj.pnt?"true":"false")
			//boolalpha<<*(LOGIC*)obj.pnt<<noboolalpha
				case 1:	out<<*(LOGIC*)obj.pnt;break;
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

/** Любой тип */
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
			if(!t::isNULL(val)){
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

namespace t {
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
		return STRING(::Type<dTYPE>::Name);
	}
};

#define FILE_types
#endif