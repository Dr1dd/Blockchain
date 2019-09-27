#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <vector>
#include <hashish.h>

using std::string;
using std::cout;
using std::endl;


string Hashish(string &a, double &laikoSuma){ 
int sz=0;
string b;
string first;
int hashSize = 16;
int sk2 = 0;
int val;
//int sz2=0;
sz = a.size();
int fullSum = 1;

auto start = std::chrono::high_resolution_clock::now();
for(std::string::size_type j= 0; j < a.size(); j++){
	fullSum += a[j] * j;
}
if(sz>0){
	if(a.size()<=hashSize){
		b.resize(hashSize);
		//sz2 = hashSize-sz;
		for(std::string::size_type i = 0; i < hashSize; i++){
			if(i == 0 ) {
				first = a[i];
				first = ToHex(first, false);
				//cout << first[0] <<endl;
				b[i] = (first[0]  * sz * a[i] *a[sz-1] *fullSum) %127;
				if(b[i] == 0) b[i] = (first[0]  *a[sz-1] * sz * a[i] *fullSum) %113;
               // cout << first[0] << " " << sz << " " << a[i] << " " << fullSum << endl;
			    val = int(b[i]);
		        valueCheck(val, b, a, i);
			}
			if(i < sz && i > 0){
				if (sk2 == sz) sk2 =0;
				b[i] = (b[i-1] * a[i] *a[i-1] * b[sk2] *fullSum) %127;
                //cout << int(b[i]) << " as" <<  endl;
                if(int(b[i]) == 0){
                    b[i] = (b[i-1] * a[i] *a[i-1] * b[sk2] *fullSum) %113;
                }
                //cout << int(b[i]) << " asdg " <<endl;
				val = int(b[i]);
		        valueCheck(val, b, a, i);
			    sk2++;
			}
			if(i>=sz){
				if (sk2 == sz) sk2 =0;
				b[i] = (b[i-1] * b[sk2] * a[i%sz] *fullSum) %127;
                if(b[i] == 0) b[i] = (b[i-1] * a[i%sz] * b[sk2] *fullSum) %113;
				val = int(b[i]);
				valueCheck(val, b, a, i);
				sk2++;
			}
	}
		b = ToHex(b, false);
	}
	if(sz>hashSize){
		b.resize(hashSize);
		//sz2 = sz-hashSize;
		b= Compress(b, a, hashSize);
		for(std::string::size_type i = 0; i < hashSize; i++){
			if(i != 0) {
				b[i] = (sz*b[i-1]*i) %127;
                if(b[i] == 0) b[i] = (sz*b[i-1]*i) %113;
				val = int(b[i]);
				valueCheck(val, b, a, i);
			}
			else{
				b[i] = (sz*b[0]*a[0]) %127;
                if(b[i] == 0) b[i] = (sz*b[0]*a[0]) %113;
				val = int(b[i]);
				valueCheck(val, b, a, i);				
			}
		}
		b = ToHex(b, false);
	}
	a = b;
}       
		auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        laikoSuma += diff.count();
	return a;
}

void MainHash(int argc, char* argv[]){
	string a;
	double laikoSuma = 0;
	int lnsk = 0;
	a = Skaitymas(argc, argv, lnsk);
	string line;
	if(lnsk>0){
		std::istringstream ss(a);
		std::ofstream fr("output.txt");
		while(std::getline(ss,line,'\n')){
				Hashish(line, laikoSuma);
				fr << line;
				fr << endl;
		}
		fr.close();
	}
	else{
		Hashish(a, laikoSuma);
		std::ofstream fr("../output/output.txt");
		fr << a;
		fr.close();
	} 
	cout << "Visas hashavimo laikas: " << laikoSuma << " s." << endl;
	GenerateAndCheck();
}

string Skaitymas(int argc, char* argv[], int & lnsk){
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
				string failoSkaitymas;
				string b;
				file = argv[1];
				std::ifstream fd("bandymai/"+file);
				if(!fd){
					cout<<"failo nera" << endl;
					return 0;
				}
								cout << "Failas bus skaitomas visas ar po viena eilute? (visas = 1, viena = 2)"<<endl;
				std::cin >> failoSkaitymas;
				while(failoSkaitymas!="1" &&failoSkaitymas!="2"){
					cout << "Bandykite is naujo. (Irasykite 1 - visas failas arba 2 - viena eilute)" << endl;
					std::cin >> failoSkaitymas;
				}
				if (failoSkaitymas == "1") b.assign((std::istreambuf_iterator<char>(fd)), std::istreambuf_iterator<char>());
				if (failoSkaitymas =="2"){
					string str;
					while (std::getline(fd, str)){
						b += str;
						b.push_back('\n');
						lnsk++;
					}
				}
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
		cout<< "Iveskite ar norite ranka rasyti ar nuskaityti faila? (R - ranka, S - skaityti faila)" <<endl;
		while(fin != false){
			std::cin >> c;
			while(c!="R" && c!= "r" && c!="s" && c!= "S"){
				cout << "Bandykite dar karta. (Irasydami R - rasyti ranka arba S - Skaityti is failo)" << endl;
				std::cin >> c;
			}
			if (c == "S" || c =="s"){
				string failoSkaitymas;
				string b;
				cout << "Iveskite failo pavadinima (be .txt)" << endl;
				std::cin >> file;
				std::ifstream fd("bandymai/"+file+".txt");
				if(!fd){
					cout<<"failo nera" << endl;
					return 0;
				}
				else{
		
				cout << "Failas bus skaitomas visas ar po viena eilute? (visas = 1, viena = 2)"<<endl;
				std::cin >> failoSkaitymas;
				while(failoSkaitymas!="1" &&failoSkaitymas!="2"){
					cout << "Bandykite is naujo. (Irasykite 1 - visas failas arba 2 - viena eilute)" << endl;
					std::cin >> failoSkaitymas;
				}
				if (failoSkaitymas == "1") b.assign((std::istreambuf_iterator<char>(fd)), std::istreambuf_iterator<char>());
				if (failoSkaitymas =="2"){
					string str;
					while (std::getline(fd, str)){
						b += str;
						b.push_back('\n');
						lnsk++;
					}
				}
				fd.close();
				return b;
				}
			}
			if (c == "R" || c == "r"){
				cout << "Iveskite teksta, kuri norite uzhashinti" << endl;
				std::cin >> text;
				return text;
			
			}
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
   // cout << val << " " << i << endl;
	while (val < 0 || val < 16 || val ==0){
	   if(val <0) {
	       if((-b[i]%127) != 0) b[i] = (-b[i]+i)%127;
		   	else b[i] = (-b[i]+i)%113;
		   	val = int(b[i]);
         //  cout << val << " " << i << " 1" << endl;
	   }
		if(0 < val && val < 16){
			b[i] = (b[i]+15)*2+i;
			val = int(b[i]);
           // cout << val << " " << i << " 2" << endl;
		} 
		if(val == 0){
           // cout << val << " " << i << " 3" << endl;
			if(i != 0){
				b[i] = (b[i-1]*a.size()+a[0]+i)%127;
             //   cout << val << " " << i << " 4" << endl;
                if(b[i] == 0) b[i] = (b[i-1]*a.size()+a[0]+i)%113;
              //  cout << int(b[i]) <<  " " << i << " 4" << endl;
				val = int(b[i]);	
			}
			else {
				b[i] = (127*a.size()+a[0]+i)%127;
              //  cout << val << " " << i << " 5" << endl;
				if(b[i] == 0) b[i] = (b[i-1]*a.size()+a[0]+i)%113;
				val = int(b[i]);		
			}
		} 
	}
		return b;
}
string Compress(string &b, string a, int hashSize){
	int skaicius = 0;
	int sum = 0;
	int gSum = 0;
	int j = 0;
	int daliklis = a.length()/hashSize;
	for(std::string::size_type v = 0; v < a.size(); v++){
		gSum += a[v];
	}
	for(std::string::size_type i = 0; i < a.size(); i++){
		sum = sum + a[i];
		if(skaicius == daliklis){
			b[j] = sum / daliklis*gSum %127;
			skaicius = 0;
			sum = 0;
			j++;
		}
		skaicius++;
	}
	return b;
}
void GenerateAndCheck(){
	std::vector<string> genvector;
	genvector.reserve(200000);
	Generatevector(genvector);
	double laikas = 0;
	std::ofstream fr("../randomText/rezultatas.txt");
		for(int i=0; i < 200000; i++) {
                Hashish(genvector[i], laikas);
                laikas = 0;
                if (i %2== 0) fr << genvector[i] << " ";
                else fr << genvector[i] << endl;
        }
	fr.close();

	int sk=0;
	int sk1 = 0;
	for(int j =0; j<200000; j++){
		for(int j1 =0; j1<200000; j1++){
			if(genvector[j] == genvector[j1] && j != j1) cout << "sutampa = " << genvector[j] << " " << j << " " << j1 << endl;

		}
	}
}


