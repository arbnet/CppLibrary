// ��������� ������

#ifndef FILE_error

#include <iostream>
using namespace std;

/** ����� ������ */
class Error {
	bool exi;
	const char* msg;
public:
	static const char* func;
	static const char* file;
	static unsigned int line;
	/** �����������
	 * @param msg ���������
	 * @param exi ������� ����������� */
	Error(const char* msg,bool exi=false):msg(msg),exi(exi){}
	/** ����� ���������� � ������ */
	void info(){
		cout<<endl<<file<<' '<<func<<':'<<line<<' '<<msg;
		if(!exi)exit(1);
	}
};
const char*  Error::func=__FUNCTION__;
const char*  Error::file=__FILE__;
unsigned int Error::line=__LINE__;

namespace e{
	/** ����� ���������� � ����������
	 * @param tpe ��� ����������
	 * @param msg ��������� */
	void Excep(const char* tpe,const char* msg){
		cout<<endl<<Error::file<<' '<<Error::func<<':'<<Error::line<<' '<<tpe<<' '<<msg;
	}
}

#define FIX Error::func=__FUNCTION__;Error::file=__FILE__;Error::line=__LINE__;
#define TRY try{
#define CATCH }catch(Error err){err.info();}\
catch(const exception &exc){e::Excep(typeid(exc).name(),exc.what());}

#define FILE_error
#endif