/** Обработка ошибок
 * Библиотека OWNI */ 

#pragma once
#define FILE_error

#include <iostream>

/** Класс ошибки */
class Error {
	bool exi;
	const char* msg;
public:
	static const char* func;
	static const char* file;
	static unsigned int line;
	/** Конструктор
	 * @param msg сообщение
	 * @param exi признак продолжения */
	Error(const char* msg,bool exi=false):msg(msg),exi(exi){}
	/** Вывод информации о ошибке */
	void info(){
		std::cout<<std::endl<<file<<' '<<func<<':'<<line<<' '<<msg;
		if(!exi)exit(1);
	}
};
const char*  Error::func=__FUNCTION__;
const char*  Error::file=__FILE__;
unsigned int Error::line=__LINE__;

namespace e{
	/** Вывод информации о исключении
	 * @param tpe тип исключения
	 * @param msg сообщение */
	void Excep(const char* tpe,const char* msg){
		std::cout<<std::endl<<Error::file<<' '<<Error::func<<':'<<Error::line<<' '<<tpe<<' '<<msg;
	}
}

#define FIX Error::func=__FUNCTION__;Error::file=__FILE__;Error::line=__LINE__;
#define TRY try{
#define CATCH }catch(Error err){err.info();}\
catch(const exception &exc){e::Excep(typeid(exc).name(),exc.what());}
