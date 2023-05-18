/** Работа с диском
 * Библиотека OWNI */

#pragma once
#define FILE_disc

//#include <filesystem>
#include "_array.hpp"
#include <iostream>
using namespace std;

namespace d{
	#include <windows.h>

/** Диск информация */
class Disc :public Array<ADDRESS> {
/* * Структура ДискИнформация * /
struct DiscInfo{
	STRING drive;// драйв\\диск
	STRING label;// метка диска
	STRING type;// тип файловой системы
	INT_B size;// общий размер
	INT_B free;// свободное место
};*/
public:
	Disc(){
		//WCHAR lpBuffer[MAX_PATH];
		//DWORD dwSize = MAX_PATH;cout<<*buf;
		WCHAR dbuf[104];
		if(GetLogicalDriveStringsW(MAX_PATH,dbuf)){
			WCHAR *drv=dbuf;
			while(*drv){
				BYTE dtp=GetDriveTypeW(drv);
				Associative *disc=new Associative;
				switch(dtp){
					case 1: (*disc)["type"]="NO_ROOT";break;
					case 2: (*disc)["type"]="REMOVABLE";break;
					case 3: (*disc)["type"]="FIXED";break;
					case 4: (*disc)["type"]="REMOTE";break;
					case 5: (*disc)["type"]="CDROM";break;
					case 6: (*disc)["type"]="RAMDISC";break;
					default: (*disc)["type"]="UNKNOWN";
				}
				cout<<*disc<<endl;
    		if(dtp){
					WCHAR lbuf[MAX_PATH];CHAR xx;
					ADDRESS adr=&lbuf;z::Fill(adr,MAX_PATH);
        	if(GetVolumeInformationW(drv,lbuf,MAX_PATH,NULL,NULL,NULL,NULL,0)){
						STRING st(L"проверка");//*drv
            wcout << "Drive: " << st << endl;
            wcout << "Volume label: " <<lbuf<<endl;
        	}else{
            wcout << "GetVolumeInformationW failed with error code: " << GetLastError() << endl;
        	}
    		}
    		drv+= wcslen(drv) + 1;
			}
		}

/*
std::cout << "GetLogicalDriveStringsW failed with error code: " << GetLastError() << std::endl;
*/
	}
};

}


/*
namespace d {
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <dirent.h>
	class Info {
	private:
		STRING way;
		struct stat status;
	public:
		Info(STRING way){
			this->way=way;
			stat(*way, &this->status);
		}
		STRING Mode(){
			STRING res;
			switch (this->status.st_mode & S_IFMT){
				case S_IFREG:	res="file";break;
				case S_IFIFO:	res="fifo";break;
				case S_IFDIR:	res="folder";break;
				case S_IFBLK:	res="block device";break;
				case S_IFCHR:	res="character device";break;
				//case S_IFLNK:	res="symbolic link";break;
				//case S_IFSOCK:	res="socket";break;
				default: res="unknown";
			}
			return res;
		}
		STRING Way(){return this->way;}
		INT_S Uid(){return this->status.st_uid;}
		INT_S Gid(){return this->status.st_gid;}
		INT_W Ino(){return this->status.st_ino;}
		INT_L Dev(){return this->status.st_dev;}
		INT_B Size(){return this->status.st_size;}
		INT_L Rdev(){return this->status.st_rdev;}
		INT_S Nlink(){return this->status.st_nlink;}
		DATETIME Opening(){return DATETIME(this->status.st_atime);}
		DATETIME Creating(){return DATETIME(this->status.st_ctime);}
		DATETIME Modification(){return DATETIME(this->status.st_mtime);}
	};
	Associative scan(CHARS(pth)){
		Associative res;
		struct dirent *dt;
		DIR *dir=opendir(pth);
		if(dir!=NULL){
			Array<STRING> way;
			Associative *fls=new Associative;
			Array<STRING> *fld=new Array<STRING>;
			way.Put(pth);way.Put("");
			while((dt=readdir(dir))!=NULL){
				way[2]=dt->d_name;
				Info inf(s::text(way));
				STRING mode=inf.Mode();
				if(way[2]!="." && way[2]!=".."){
					if(mode=="folder")(*fld).Put(way[2]);
					else if(mode=="file"){
						Associative *ifl=new Associative;
						(*ifl)["size"]=inf.Size();
						(*ifl)["opening"]=inf.Opening();
						(*ifl)["creating"]=inf.Creating();
						(*ifl)["modification"]=inf.Modification();
						(*fls)[way[2]]=*ifl;
					}
				}
			}
			if(*fld)res["folders"]=*fld;
			if(*fls)res["files"]=*fls;
			closedir(dir);
		}
		return res;
	}
}*/