/** Массивы
 * Библиотека OWNI */

#pragma once
#define FILE_array

#include "_types.hpp"

/** Структура КлючЗначение */
struct KeyValue {
	STRING key;
	ANY value;
};

/** Итератор */
class Iterator {
protected:
	INT_L sz=0;// размер
	INT_L idx=0;// индекс
	LOGIC how=false;// признак перебора
public:
  /** Получение признака перебора */
  LOGIC How(){return how;}
	/** Указание как перебирать
	 * @param how `true` с конца, `false` с начала */
	void How(LOGIC how){Index(how?-1:0);this->how=how;}
  /** Размер */
  INT_L Size(){return sz;}
  /** Текущий индекс */
	INT_L Index(){return sz?idx+1:0;}
  /** Установка индекса
   * @param idx новый интдекс */
	void Index(INT_L idx){z::Index(idx,sz);this->idx=idx;}
  /** Сброс
	 * @param idx индекс */
	void Reset(INT_L idx=0){
		Index(idx?idx:this->how?-1:0);
	}
  /** Проверка на последний элемент */
	LOGIC Last(){
		LOGIC res=false;
		if(this->how){
			if(idx==0)res=true;
		}else{
			if(idx==sz-1)res=true;
		}
		return res;
	}
  /** Переход к следующему элементу */
	LOGIC Next(){
		LOGIC res=false;
		if(this->how){
			if(idx>0){idx--;res=true;}
		}else{
			if(idx<sz-1){idx++;res=true;}
		}
		return res;
	}
};

/** Массив */
template <typename dTYPE>
class Array :public Iterator {
	INT_W rv=0;
	INT_L tl=0;
	dTYPE *vars=NULL;
	void Init(INT_L tl,INT_W rv){
		if(vars)delete []vars;
		if(tl){
			if(rv)tl=z::Volume(tl,rv);
			vars=new dTYPE[tl];
		}else vars=NULL;
		this->tl=tl;this->rv=rv;idx=sz=0;how=false;
	}
public:
	Array(INT_L tl=0,INT_W rv=10){this->Init(tl,rv);}
	Array(const Array &obj){
		this->Init(obj.sz,0);sz=obj.sz;
		if(sz){
			ADDRESS adr1=vars,adr2=obj.vars;
			z::Copy(adr1,adr2,sz*sizeof(dTYPE));
		}
	}
	~Array(){if(vars)delete []vars;}
	operator bool(){return sz?true:false;}
	dTYPE& operator[](INT_L idx){
		if(idx==0)idx=this->idx;
		else z::Index(idx,sz);
		return vars[idx];
	}
	Array<dTYPE>& operator=(Array<dTYPE> &oar){
		if(this!=&oar){
			if(tl<oar.sz)this->Init(oar.tl,rv);
			if(oar.sz){sz=oar.sz;
				ADDRESS adr1=vars,adr2=oar.vars;
				z::Copy(adr1,adr2,sz*sizeof(dTYPE));
			}
		}
		return *this;
	}
	/** Очистка массива */
	void Clear(){this->Init(0,0);}
	/** Тотальный размер в памяти */
	INT_L Total(){return tl;}
	/** Размер резервирования */
	INT_L Reserve(){return rv;}
	/** Установка размера резервирования
	 * @param rv размер резервирования */
	void Reserve(INT_W rv){this->rv=rv;}
	/** Добавление новых элементов массива
	 * @param ...args новые элементы */
	template<typename... aARG>
	void Add(aARG ...args){
		(this->Put(args), ...);
	}
	/** Положить новый элемент
	 * @param val значение
	 * @param idx индекс */
	void Put(dTYPE val,INT_L idx=0){
		if(sz<4294967295){
			INT_L nsz=sz+1;
			INT_L ntl=rv?z::Volume(nsz,rv):tl;
			if(nsz<ntl){
				if(idx)z::Index(idx,nsz);else idx=sz;
				if(tl!=ntl){tl=ntl;
					dTYPE *nvrs=new dTYPE[tl];
					if(vars){
						INT_S ln=sizeof(dTYPE);
						ADDRESS adr1=nvrs,adr2=vars;
						z::Copy(adr1,adr2,idx*ln);
						if(idx<sz){z::Shift(adr1,ln);
							z::Copy(adr1,adr2,(nsz-idx)*ln);
						}
						delete []vars;
					}
					vars=nvrs;
				}else	if(idx<sz){
					INT_S ln=sizeof(dTYPE);
					ADDRESS adr1,adr2=vars;
					z::Shift(adr2,sz*ln);adr1=adr2;
					z::Shift(adr2,-ln);
					z::Copy(adr1,adr2,-(sz-idx)*ln);
				}
				vars[idx]=val;sz++;
			}
		}
	}
	/** Взять элемент
	 * @param idx индекс */
	dTYPE Take(INT_L idx=-1){
		dTYPE val;
		if(sz){
			z::Index(idx,sz);val=vars[idx];
			if(idx<sz){
				INT_S ln=sizeof(dTYPE);
				ADDRESS adr1,adr2=vars;
				z::Shift(adr2,idx*ln);adr1=adr2;
				z::Shift(adr2,ln);
				z::Copy(adr1,adr2,(sz-idx)*ln);
			}
			sz--;
		}else val=0;
		return val;
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<< (std::ostream &out,Array<dTYPE> &oar){
		INT_L sz=oar.Size();
		out<<std::endl;
		if(sz){out<<'{'<<std::endl;
			INT_L ix=oar.Index();
			for(INT_L nx=0;nx++<sz;){i::tab(1);
				out<<'['<<nx<<']'<<(ix==nx?'>':' ')<<oar[nx]<<std::endl;
			}
			out<<'}';
		}else out<<"NULL";
		return out<<std::endl;
	}
	#endif
};

ID_TYPE(31,Array<LOGIC>)
ID_TYPE(32,Array<LETTER>)
ID_TYPE(33,Array<RANGE>)
ID_TYPE(34,Array<BYTE>)
ID_TYPE(35,Array<INT_S>)
ID_TYPE(36,Array<INT_W>)
ID_TYPE(37,Array<INT_M>)
ID_TYPE(38,Array<INT_L>)
ID_TYPE(39,Array<INT_T>)
ID_TYPE(40,Array<INT_B>)
ID_TYPE(41,Array<FLOAT>)
ID_TYPE(42,Array<DOUBLE>)
ID_TYPE(43,Array<ADDRESS>)
ID_TYPE(44,Array<CHARS>)
ID_TYPE(45,Array<STRING>)
ID_TYPE(46,Array<DATETIME>)

/** Аргументы */
class Args :public Array<ADDRESS> {
public:
	Args(){}
	template<typename... aARG>
	Args(aARG... args){(Put(args), ...);}
	~Args(){Clear();}
	ANY& operator[](INT_L idx){
		if(!Size())Array<ADDRESS>::Put(new ANY);
		return *(ANY*)Array<ADDRESS>::operator[](idx);
	}
	/** Очистка аргументов */
	void Clear(){
		if(Size()){Reset();
			do{
				delete static_cast<ANY*>(Array<ADDRESS>::operator[](0));
			}while(Next());
			Array<ADDRESS>::Clear();
		}
	}
	/** Положить новый элемент
	 * @param val значение
	 * @param idx индекс */
	template <typename dTYPE>
	void Put(dTYPE val,INT_L idx=0){
		Array<ADDRESS>::Put(new ANY(val),idx);
	}
	/** Взять элемент
	 * @param idx индекс */
	ANY Take(INT_L idx=-1){
		ANY res;
		if(Size()){
			ADDRESS pnt=Array<ADDRESS>::Take(idx);
			res=*(ANY*)pnt;delete static_cast<ANY*>(pnt);
		}
		return res;
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<<(std::ostream &out,Args &oar){
		INT_L sz=oar.Size();
		out<<std::endl;
		if(sz){out<<'{'<<std::endl;
			INT_L ix=oar.Index();
			for(INT_L nx=0;nx++<sz;){i::tab(1);
				out<<'['<<nx<<']'<<(ix==nx?'>':' ')<<oar[nx]<<std::endl;
			}
			out<<'}';
		}else out<<"NULL";
		return out<<std::endl;
	}
	#endif
};
ID_TYPE(47,Args)

/*
namespace a {
	template<typename dTYPE>
	INT_L Find(Array<dTYPE> obj,const dTYPE val){
		INT_L res=0,idx=obj.Index();
		if(obj.Size()){obj.Reset();
			do{
				if(obj[0]==val){res=obj.Index();break;}
			}while(obj.Next());
			obj.Index(idx);
		}
		return res;
	}
}
*/

/** Ассоциативный массив */
class Associative :public Array<ADDRESS> {
	ANY& Value(STRING key){
		idx=this->Find(key);
		if(idx)return ((KeyValue*)Array<ADDRESS>::operator[](idx))->value;
		else{
			KeyValue *skv=new KeyValue;
			skv->key=key;Array<ADDRESS>::Put(skv);
			return skv->value;
		}
	}
public:
	Associative(){}
	//Associative(const Associative &obj): apr(obj.apr),dbl(true){}
	//~Associative(){if(!this->dbl)delete this->apr;}
	KeyValue operator[](INT_L idx){
		if(!idx)idx=this->idx;
		return *(KeyValue*)Array<ADDRESS>::operator[](idx);
	}
	ANY& operator[](CHARS chs){
		return this->Value(STRING(chs));
	}
	STRING Key(INT_L idx=0){
		return ((KeyValue*)Array<ADDRESS>::operator[](idx))->key;
	}
	INT_L Find(STRING key,INT_L idx=0){
		INT_L res=0;
		if(Size()){
			INT_L tix=Index();Reset(idx);
			do{
				if(key==Key(this->idx)){res=this->idx;break;}
			}while(Next());
			Index(tix);
		}
		return res;
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<<(std::ostream &out,Associative &oas){
		INT_L sz=oas.Size();
		out<<std::endl;
		if(sz){out<<'{'<<std::endl;
			INT_L ix=oas.Index();
			for(INT_L nx=0;nx++<sz;){i::tab(1);
				KeyValue kv(oas[nx]);
				out<<'['<<nx<<']'<<(ix==nx?'>':' ')<<kv.key<<'='<<kv.value<<std::endl;
			}
			out<<'}';
		}else out<<"NULL";
		return out<<std::endl;
	}
	#endif

	/*
	void Clear(){
		if(this->dbl)this->apr=new Array<POINTER>;
		else if(apr->Size()){apr->Reset();
			do{
				delete static_cast<KeyValue*>((*apr)[0]);
			}while(apr->Next());
			apr->Clear();
		}
	}
	//template <class oCLASS>
	//explicit operator oCLASS(){return *static_cast<oCLASS*>(**this->Value());}
	//ANY& operator[](INT_L index){
	//	return (*(KeyValue*)(*apr)[index]).value;
	//}
	ANY& operator[](const STRING &key){
		return this->Value(key);
	}
	ANY& operator[](CHARS(ltr)){
		return this->Value(STRING(ltr));
	}
	STRING Key(INT_L index=0){
		return (*(KeyValue*)(*apr)[index]).key;
	}
	ANY& Value(INT_L index=0){
		return (*(KeyValue*)(*apr)[index]).value;
	}
	KeyValue Take(STRING key){
		KeyValue res;
		INT_L index=this->Find(key);
		if(index){
			POINTER pnt=apr->Take(index);
			res=*(KeyValue*)pnt;
			delete static_cast<KeyValue*>(pnt);
		}
		return res;
	}
	*/
};
ID_TYPE(48,Associative)

/*
#ifdef FILE_zests
namespace a {
	template <typename dTYPE>
	void v(const Array<dTYPE> &oar){
		Array<dTYPE> obj(oar);
		INT_W rv=obj.Reserve();INT_L sz=obj.Size();
		t::tab();
		std::cout<<"Array<"<<::Type<dTYPE>::Name<<">("<<sz;
		if(rv)std::cout<<','<<obj.Total()<<','<<rv;
		std::cout<<"){";
		if(sz){std::cout<<std::endl;
			INT_L ix=obj.Index();
			for(INT_L nx=0;nx++<sz;){
				t::tab(1);
				std::cout<<'['<<nx<<']'<<(ix==nx?'>':' ');
				t::v(obj[nx]);std::cout<<std::endl;
			}
		}
		std::cout <<'}';
	}
}
#endif
*/