/** Базовые классы
 * Библиотека OWNI */

#ifndef FILE_types
#include "_types.hpp"
#endif
#pragma once
#define FILE_base

/** АвтоУказатель */
template<typename dTYPE>
class AutoPOINTER{
  LOGIC sgn=true;
  static dTYPE *pnt;
public:
  ~AutoPOINTER(){if(sgn)this->Clear();}
  AutoPOINTER(AutoPOINTER &obj){sgn=false;}
  AutoPOINTER(){AutoPOINTER::pnt=new (dTYPE);}
  AutoPOINTER(dTYPE val){AutoPOINTER::pnt=new (dTYPE)(val);}
  dTYPE& operator *(){return *(dTYPE*)pnt;}
  explicit operator bool(){return AutoPOINTER::pnt?true:false;}
  void Clear(){
    if(AutoPOINTER::pnt){
      delete AutoPOINTER::pnt;AutoPOINTER::pnt=NULL;
    }
  }
};
template<class oCLASS>
oCLASS* AutoPOINTER<oCLASS>::pnt=NULL; 

/*
#ifdef VAR
#if VAR+0<1
тут код, VAR заменить на CLASS_Название
#undef VAR
#define VAR 1
#endif
#endif
*/

/*


/ *
STRING tostr(INT_W num){
  LETTER *lts=new LETTER[20];
  _itoa(num,lts,10);
  return STRING(lts);
}

STRING ClassType(STRING type){
  INT_W len=type.Size()-1;
  type-=tostr(len);
  return type;
}

STRING ClassType(STRING type){
  INT_W len=type.Size()-1;
  LETTER *lts=new LETTER[20];
  _itoa(len,lts,10);type-=lts;
  return type;
}
*/