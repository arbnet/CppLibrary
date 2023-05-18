/** Обработка ошибок
 * Библиотека OWNI */ 

#pragma once
#define FILE_error

//#include <exception>
#include <iostream>
#include "_quasi.hpp"

/** Класс ошибки */
class Error {
	bool exi;
	const TCHAR *msg;
public:
	static const char *func;
	static const char *file;
	static unsigned int line;
	/** Конструктор
	 * @param msg сообщение
	 * @param exi признак продолжения */
	Error(const TCHAR *msg,bool exi=false):msg(msg),exi(exi){}
	/** Вывод информации о ошибке */
	void info(){
		std::cout<<std::endl<<file<<' '<<func<<':'<<line<<' ';
		_COUT<<msg;
		if(exi)exit(1);
	}
	/** Вывод информации о исключении */
	static void exce(const char* tpe,const char* msg){
		std::cout<<std::endl<<file<<' '<<func<<':'<<line<<' '<<tpe<<' '<<msg;
	}
};
const char*  Error::func=__FUNCTION__;
const char*  Error::file=__FILE__;
unsigned int Error::line=__LINE__;

#define FIX Error::func=__FUNCTION__;Error::file=__FILE__;Error::line=__LINE__;
#define TRY try{
#define CATCH }catch(Error err){err.info();}\
catch(const exception &exc){Error::exce(typeid(exc).name(),exc.what());}
