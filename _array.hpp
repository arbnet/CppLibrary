/** Массивы
 * Библиотека OWNI */

#ifndef FILE_array

#include "_types.h"

/** Структура КлючЗначение */
struct KeyValue {
	STRING key;
	ANY value;
};

/** Массив */
template <typename dTYPE>
class Array {
struct Data {
	INT_W rv=0;
	INT_L sz=0,tl=0;
	dTYPE *vars=NULL;
};
	Data *mdt;
	INT_L ix=0;
	LOGIC dbl=false;
	LOGIC how=false;
	void Init(INT_L tl=0,INT_W rv=10){
		if(this->dbl){mdt=new Data;dbl=false;}
		else if(mdt->vars)delete []mdt->vars;
		if(tl)mdt->vars=new dTYPE[tl];
		mdt->rv=rv;mdt->tl=tl;mdt->sz=this->ix=0;
	}
public:
	Array(const Array &obj): mdt(obj.mdt),dbl(true){}
	Array(INT_L tl=0,INT_W rv=10){mdt=new Data;this->Init(tl,rv);}
	~Array(){if(!this->dbl){delete []mdt->vars;delete mdt;}}
	void Clear(){this->Init(mdt->tl,mdt->rv);}
	operator bool(){return mdt->sz?true:false;}
	dTYPE& operator[](INT_L index){
		if(index==0)index=this->ix;
		else t::Index(index,mdt->sz);
		return mdt->vars[index];
	}
	Array<dTYPE>& operator=(const Array<dTYPE> &oar){
		if(this!=&oar){this->Init(oar.mdt->tl,oar.mdt->rv);
			mdt->sz=oar.mdt->sz;
			if(mdt->sz){
				Array<dTYPE> obj(oar);
				for(INT_L nx=0;nx++<mdt->sz;)
					(*this)[nx]=obj[nx];
			}
		}
		return *this;
	}
	INT_L Size(){return mdt->sz;}
	INT_L Total(){return mdt->tl;}
	INT_L Index(){return mdt->sz?this->ix+1:0;}
	INT_L Reserve(){return mdt->rv;}
	void Reserve(INT_W rv){mdt->rv=rv;}
	void How(LOGIC how){
		Index(how?-1:0);this->how=how;
	}
	void Index(INT_L index){
		t::Index(index,mdt->sz);this->ix=index;
	}
	void Reset(){
		Index(this->how?-1:0);
	}
	LOGIC Last(){
		LOGIC res=false;
		if(this->how){
			if(this->ix==0)res=true;
		}else{
			if(this->ix==mdt->sz-1)res=true;
		}
		return res;
	}
	LOGIC Next(){
		LOGIC res=false;
		if(this->how){
			if(this->ix>0){this->ix--;res=true;}
		}else{
			if(this->ix<mdt->sz-1){this->ix++;res=true;}
		}
		return res;
	}
	template<typename... aARG>
	void Add(aARG... args){
		(this->Put(args), ...);
	}
	void Put(dTYPE val,INT_L index=0){
		INT_L ntx=mdt->rv?4294967295:mdt->tl;
		if(mdt->sz!=ntx){
			if(index==0)index=mdt->sz;
			else t::Index(index,mdt->sz);
			mdt->sz++;
			if(mdt->rv){
				ntx=t::Volume(mdt->sz,mdt->rv);
				if(mdt->tl!=ntx){
					dTYPE *vars=new dTYPE[ntx] ;
					if(mdt->tl){INT_L nx=0;
						for(;nx<index;nx++)vars[nx]=mdt->vars[nx];
						for(;nx<mdt->sz;nx++)vars[nx+1]=mdt->vars[nx];
						delete []mdt->vars;
					}
					mdt->tl=ntx;mdt->vars=vars;
				}else if(index<mdt->sz){ntx=mdt->sz;
					while(index<ntx){
						mdt->vars[ntx]=mdt->vars[ntx-1];ntx--;
					}
				}
			}else if(index<mdt->sz){ntx=mdt->sz;
				while(index<ntx){
					mdt->vars[ntx]=mdt->vars[ntx-1];ntx--;
				}
			}
			mdt->vars[index]=val;
		}
	}
	dTYPE Take(INT_L index=-1){
		dTYPE val;
		if(mdt->sz){
			t::Index(index,mdt->sz);
			val=mdt->vars[index];mdt->sz--;
			while(index<mdt->sz){
				mdt->vars[index]=mdt->vars[index+1];index++;
			}
		}else val=0;
		return val;
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<< (std::ostream &out,const Array<dTYPE> &oar){
		Array<dTYPE> obj(oar);INT_L sz=obj.Size();
		out<<std::endl;
		if(sz){out<<'{'<<std::endl;
			INT_L ix=oar.ix+1;
			for(INT_L nx=0;nx++<sz;){i::tab(1);
				out<<'['<<nx<<']'<<(ix==nx?'>':' ')<<obj[nx]<<std::endl;
			}
			out<<'}';
		}else out<<"NULL";
		return out<<std::endl;
	}
	#endif
};

ID_TYPE(21,Array<LOGIC>)
ID_TYPE(22,Array<RANGE>)
ID_TYPE(23,Array<LETTER>)
ID_TYPE(24,Array<BYTE>)
ID_TYPE(25,Array<INT_S>)
ID_TYPE(26,Array<INT_W>)
ID_TYPE(27,Array<INT_M>)
ID_TYPE(28,Array<INT_L>)
ID_TYPE(29,Array<INT_T>)
ID_TYPE(30,Array<INT_B>)
ID_TYPE(31,Array<FLOAT>)
ID_TYPE(32,Array<DOUBLE>)
ID_TYPE(33,Array<POINTER>)
//ID_TYPE(34,Array<DATETIME>)
ID_TYPE(35,Array<STRING>)

/** Аргументы */
class Args :public Array<POINTER> {
public:
	Args(){}
	template<typename... aARG>
	Args(aARG... args){(this->Put(args), ...);}

	ANY& operator[](INT_L index){
		if(!this->Size())Array<POINTER>::Put(new ANY);
		return *(ANY*)Array<POINTER>::operator[](index);
	}
	template <typename dTYPE>
	void Put(dTYPE val){
		Array<POINTER>::Put(new ANY(val));
	}
	ANY Take(INT_L index=0){
		ANY res;
		if(this->Size()){
			POINTER pnt=Array<POINTER>::operator[](index);
			res=*(ANY*)pnt;delete static_cast<ANY*>(pnt);
		}
		return res;
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<<(std::ostream &out,const Args &oar){
		Args obj(oar);INT_L sz=obj.Size();
		out<<std::endl;
		if(sz){out<<'{'<<std::endl;
			INT_L ix=obj.Index();
			for(INT_L nx=0;nx++<sz;){i::tab(1);
				out<<'['<<nx<<']'<<(ix==nx?'>':' ')<<obj[nx]<<std::endl;
			}
			out<<'}';
		}else out<<"NULL";
		return out<<std::endl;
	}
	#endif
};
ID_TYPE(17,Args)

/* * Аргументы * /
class Args {
private:
	//LOGIC dbl=false;
	Array<POINTER> apr;	
	//void Init(){this->apr=new Array<POINTER>;}this->Init();this->Init();
public:
	Args(){}
	template<typename... aARG>
	Args(aARG... args){(this->Put(args), ...);}
	//Args(const Args &obj): apr(obj.apr),dbl(true){};
	//~Args(){if(!this->dbl)delete this->apr;}
	void Clear(){
		if(this->dbl){this->Init();this->dbl=false;}
		else if(apr->Size()){apr->Reset();
			do{
				delete static_cast<ANY*>((*apr)[0]);
			}while(apr->Next());
			apr->Clear();
		}
	}
	INT_L Size(){return apr.Size();}
	INT_L Total(){return apr.Total();}
	INT_L Index(){return apr.Index();}
	INT_L Reserve(){return apr.Reserve();}
	void Reset(){apr.Reset();}
	void Index(INT_L ix){apr.Index(ix);}
	void How(LOGIC hw){apr.How(hw);}
	void Reserve(INT_L rv){apr.Reserve(rv);}
	LOGIC Next(){return apr.Next();}
	operator bool(){return (LOGIC)apr;}
	ANY& operator[](INT_L index){
		if(!apr.Size())apr.Put((POINTER)new ANY);
		return *(ANY*)apr[index];
	}
	template<typename... aARG>
	void Set(aARG... args){
		this->Clear();(this->Put(args), ...);
	}
	template <typename dTYPE>
	void Put(dTYPE val){
		ANY *vdt=new ANY(val);apr->Put(vdt);
	}
	ANY Take(INT_L index=0){
		ANY res;
		if(apr->Size()){
			//ANY *any=(ANY*)apr->Take(index);
			//res=*any;delete any;
			POINTER pnt=apr->Take(index);
			res=*(ANY*)pnt;
			delete static_cast<ANY*>(pnt);
		}
		return res;
	}
	template <typename dTYPE>
	INT_L Find(dTYPE val){
		INT_L res=0,idx=apr->Index();
		if(apr->Size()){apr->Reset();
			do{
				if((*this)[0]==val){
					res=apr->Index();break;
				}
			}while(apr->Next());
			if(!res)apr->Index(idx);
		}
		return res;
	}
	#ifdef _GLIBCXX_IOSTREAM
	friend std::ostream& operator<<(std::ostream &out,const Args &oar){
		Args obj(oar);INT_L sz=obj.Size();
		out<<std::endl;
		if(sz){out<<'{'<<std::endl;
			INT_L ix=obj.Index();
			for(INT_L nx=0;nx++<sz;){i::tab(1);
				out<<'['<<nx<<']'<<(ix==nx?'>':' ')<<obj[nx]<<std::endl;
			}
			out<<'}';
		}else out<<"NULL";
		return out<<std::endl;
	}
	#endif
};
ID_TYPE(17,Args)
*/
/* * Ассоциативный массив * /
class Associative {
private:
	Array<POINTER> *apr;
	LOGIC dbl=false;
	ANY& Value(STRING key){
		INT_L index=this->Find(key);
		if(index)return (*(KeyValue*)(*apr)[index]).value;
		else{
			KeyValue *skv=new KeyValue;
			(*skv).key=key;apr->Put(skv);
			return (*skv).value;
		}
	}
public:
	Associative(){this->apr=new Array<POINTER>;}
	Associative(const Associative &obj): apr(obj.apr),dbl(true){}
	~Associative(){if(!this->dbl)delete this->apr;}
	void Clear(){
		if(this->dbl)this->apr=new Array<POINTER>;
		else if(apr->Size()){apr->Reset();
			do{
				delete static_cast<KeyValue*>((*apr)[0]);
			}while(apr->Next());
			apr->Clear();
		}
	}
	INT_L Size(){return apr->Size();}
	INT_L Total(){return apr->Total();}
	INT_L Index(){return apr->Index();}
	INT_L Reserve(){return apr->Reserve();}
	void Reset(){apr->Reset();}
	void Index(INT_L ix){apr->Index(ix);}
	void How(LOGIC hw){apr->How(hw);}
	void Reserve(INT_L rv){apr->Reserve(rv);}
	LOGIC Next(){return apr->Next();}
	//template <class oCLASS>
	//explicit operator oCLASS(){return *static_cast<oCLASS*>(**this->Value());}
	operator bool(){return apr->Size()?true:false;}
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
	INT_L Find(STRING key,INT_L index=0){
		INT_L res=0;
		if(apr->Size()){
			INT_L tmp=apr->Index();apr->Reset();
			do{
				if(key==this->Key(index)){
					res=apr->Index();break;
				}
			}while(apr->Next());
			apr->Index(tmp);
		}
		return res;
	}
};
ID_TYPE(18,Associative)
*/

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
#endif*/

#define FILE_array
#endif