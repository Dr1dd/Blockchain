#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath> 
using std::string;
using std::cout;
using std::endl;

string Skaitymas(int argc, char* argv[]);
string ToHex(const string &, bool upper_case);
string valueCheck(int &, string &, string a, int i);
string Compress(string &b, string a, int hashSize);

string Hashish(string &a){ 
int sz=0;
string b;
string first;
int hashSize = 16;
int sk2 = 0;
int val;
int sz2=0;
sz = a.size();
if(sz>0){
	if(a.size()<=hashSize){
		b.resize(hashSize);
		sz2 = hashSize-sz;
		for(std::string::size_type i = 0; i < hashSize; i++){
			
			if(i == 0 ) {
					first = a[i];
					first = ToHex(first, false);
				b[i] = first[0] * sz * a[i] %15;
			    val = int(b[i]);
		        valueCheck(val, b, a, i);
			}
			if(i <= sz && i > 0){
					if (sk2 == sz) sk2 =0;
				b[i] = (b[i-1] * a[i] * b[sk2]) %127;
				val = int(b[i]);
		        valueCheck(val, b, a, i);
			    sk2++;
			}
			if(i>sz){
				if (sk2 == sz) sk2 =0;
				b[i] = (b[i-1] * b[sk2]) %127;
				val = int(b[i]);
				valueCheck(val, b, a, i);
						sk2++;
			}
	}
		b = ToHex(b, false);

	}
	if(sz>hashSize){
		b.resize(hashSize);
		sz2 = sz-hashSize;
		b= Compress(b, a, hashSize);
		for(std::string::size_type i = 0; i < hashSize; i++){
			if(i != 0) {
				b[i] = sz*b[i-1]*i %127;
				val = int(b[i]);
				valueCheck(val, b, a, i);
			}
			else{
				b[i] = sz*b[0]*a[0] %127;
				val = int(b[i]);
				valueCheck(val, b, a, i);				
			}
		}
		b = ToHex(b, false);
	}
	a = b;
}
cout << sz;
	return a;
}
int main(int argc, char* argv[]){
	string a;
	a = Skaitymas(argc, argv);
	Hashish(a);
	std::ofstream fr("output.txt");
	fr << a;	
    return 0;
}
string Skaitymas(int argc, char* argv[]){
	string c;
	bool fin = true;
	string file;
	string text;
	string choice;
	if(argc > 1) {
		cout << "Pasirinkite, kur naudosite argumentus (input is failo = 1 | input is argumentu = 2)" <<endl;
		std::cin >> choice;
		while(choice != "1" && choice !="2"){
		std::cout<<"Ivestis neteisinga, bandykite dar karta: (Iveskite 1 arba 2)" << std::endl;
		std::cin >> choice;
		}	
		if(choice == "1"){
			if(argc > 2) {
				cout << "Ivesta per daug argumentu" << endl;
				return 0;
			}
			else{
				file = argv[1];
				std::ifstream fd("bandymai/"+file);
				if(!fd){
					cout<<"failo nera" << endl;
					return 0;
				}
				string b((std::istreambuf_iterator<char>(fd)), std::istreambuf_iterator<char>());
				fd.close();
				return b;
			}
		}
		if(choice == "2"){
			string stringIvestis;
			for(int i = 0; i < argc; ++i){
				stringIvestis += argv[i];
			}
			return stringIvestis;
		}
	}
	else{
		cout<< "Iveskite ar norite ranka rasyti ar nuskaityti failà? (R - ranka, S - skaityti faila)" <<endl;
		while(fin != false){
			std::cin >> c;
			if (c == "S" || c =="s"){
				cout << "Iveskite failo pavadinima (be .txt)" << endl;
				std::cin >> file;
				std::ifstream fd("bandymai/"+file+".txt");
				if(!fd){
					cout<<"failo nera" << endl;
					return 0;
				}
				string b((std::istreambuf_iterator<char>(fd)), std::istreambuf_iterator<char>());
				fd.close();
				return b;
			}
			if (c == "R" || c == "r"){
				cout << "Iveskite teksta, kuri norite uzhashinti" << endl;
				std::cin >> text;
				return text;
			
			}
			else cout<< "Iveskite is naujo" << endl;
			cout << "Dar noresite hash'inti teksta? (taip/ne)"<< endl;
			string pasirinkti;
			std::cin >> pasirinkti;
			if (pasirinkti == "ne" || pasirinkti == "Ne" || pasirinkti == "n") fin = false;
			else return 0;
			}
	}
}
string ToHex(const string& s, bool upper_case /* = true */)
{
    std::ostringstream ret;
    for (string::size_type i = 0; i < s.length(); ++i)
        ret << std::hex << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << (int)s[i];

    return ret.str();
}
string valueCheck(int & val, string & b, string a, int i ){
	while (val < 0 || val < 16){
	   if(val <0) {
		   	b[i] = -b[i]/1.5;
		   	val = int(b[i]);
	   }
		if(0 < val && val < 16){
			b[i] = (b[i]+15)*2;	
			val = int(b[i]);
		} 
		if(val == 0){
			b[i] = b[i-1]*a[0]%127;
			val = int(b[i]);	
		} 
	}
		return b;
}
string Compress(string &b, string a, int hashSize){
	int skaicius = 0;
	int sum = 0;
	int j = 0;
	int daliklis = a.length()/hashSize;
	for(std::string::size_type i = 0; i < a.size(); i++){
		sum = sum + a[i];
		if(skaicius == daliklis){
			b[j] = sum / daliklis;
			skaicius = 0;
			sum = 0;
			j++;
		}
		skaicius++;
	}
	return b;
}

