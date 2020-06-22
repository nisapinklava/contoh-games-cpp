#include <iostream>
#include <cstring>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	struct data {
		int NIS[12];
		string Name[100];
		string Address[100];
		int Phone[13];
	};
	
	static data siswa;
	
	cout<<"Welcome to Databse Student System"<<endl;
	cout<<"================================="<<endl;
	cout<<"Your NIS: "; cin>>siswa.NIS;
	cout<<"Your Name: "; cin>>siswa.Name;
	cout<<"Your Address: "; cin>>siswa.Address;
	cout<<"Your Phone: "; cin>>siswa.Phone;
	
	
	return 0;
}
