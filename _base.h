
#include "_types.h"

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