#include <iostream>
#include <cstring>

using namespace std;

int main(){
	struct SISWA{
		char NIS[9];
		char Nama[25];
		char Alamat[20];
		char kota[15];
	};
	
	SISWA A;
	
	strcpy(A.NIS, "101929992");
	strcpy(A.Nama, "annisa p");
	strcpy(A.Alamat, "bandung");
	strcpy(A.kota, "jabar");
	
	cout<<A.NIS<<endl;
	
	return 0;
}
