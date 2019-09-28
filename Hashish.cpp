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
sz = a.size();
int fullSum = 1;

auto start = std::chrono::high_resolution_clock::now();
for(std::string::size_type j= 0; j < a.size(); j++){
	fullSum += a[j] * j;
}
if(sz>0){
	if(a.size()<=hashSize){
		b.resize(hashSize);
		for(std::string::size_type i = 0; i < hashSize; i++){
			if(i == 0 ) {
				first = a[i];
				first = ToHex(first, false);
				b[i] = (first[0]  * sz * a[i] *a[sz-1] *fullSum) %127;
				if(b[i] == 0) b[i] = (first[0]  *a[sz-1] * sz * a[i] *fullSum) %113;
			    val = int(b[i]);
		        valueCheck(val, b, a, i);
			}
			if(i < sz && i > 0){
				if (sk2 == sz) sk2 =0;
				b[i] = (b[i-1] * a[i] *a[i-1] * b[sk2] *fullSum) %127;
                if(int(b[i]) == 0){
                    b[i] = (b[i-1] * a[i] *a[i-1] * b[sk2] *fullSum) %113;
                }
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
	string testas;
	cout << "Noresite generuoti ir testuoti? (taip/ne)" << endl;
	std::cin >> testas;
	while(testas != "taip" && testas !="ne"){
	    cout << "Bandykite dar karta ivesdami taip arba ne" << endl;
	    std::cin >> testas;
	}
	if(testas == "taip")GenerateAndCheck();
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

string valueCheck(int & val, string & b, string a, int i ){
	while (val < 0 || val < 16 || val ==0){
	   if(val <0) {
	       if((-b[i]%127) != 0) b[i] = (-b[i]+i)%127;
		   	else b[i] = (-b[i]+i)%113;
		   	val = int(b[i]);
	   }
		if(0 < val && val < 16){
			b[i] = (b[i]+15)*2+i;
			val = int(b[i]);
		}
		if(val == 0){
			if(i != 0){
				b[i] = (b[i-1]*a.size()+a[0]+i)%127;
                if(b[i] == 0) b[i] = (b[i-1]*a.size()+a[0]+i)%113;
				val = int(b[i]);
			}
			else {
				b[i] = (127*a.size()+a[0]+i)%127;
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
    std::vector<std::vector<string> > genDiff;
	genvector.reserve(2222222);
    genDiff.reserve(2);
	Generatevector(genvector, genDiff);
	string ivestis;
	cout << "Pasirinkite kokio tikrinimo norite: Bitu lygmenyje = b | paprasto = p" << endl;
	std::cin >> ivestis;
	while(ivestis!="b" && ivestis != "p"){
	    cout << "Bandykite is naujo irasydami b arba p" << endl;
	    std::cin >> ivestis;
	}
	if(ivestis == "p"){
        double laikas = 0;

        std::ofstream fr("../randomText/3uzdRezultatas.txt");
        for(int i=0; i < 2222222; i++) {
            Hashish(genvector[i], laikas);
            laikas = 0;
            if (i %2== 0) fr << genvector[i] << " ";
            else fr << genvector[i] << endl;
        }
        fr.close();


        int sutampa = 0;
        cout << "Rezultatai sugeneruoti. Pradedamas hash'u lyginimas" << endl;
        for(int j =0; j<2222222; j++){
            if(j%2!=0){
                if(genvector[j] == genvector[j-1]){
                    cout << "sutampa = " << genvector[j] << " " << j/2 << " eilute" << endl;
                    sutampa++;
                }
            }
        }
        cout<< "Sutapimu = " << sutampa << endl;
    }
	if(ivestis == "b") {
        double laikas2 = 0;
        string pp;
        std::ofstream off("../randomText/4uzdHashintas1skirtumas.txt");
        for (int i = 0; i < 100000; i++) {
            for (int j = 0; j < 2; j++) {
                Hashish(genDiff[j][i], laikas2);
                laikas2 = 0;
                if (j == 0) off << genDiff[j][i] << " ";
                else off << genDiff[j][i] << endl;
                genDiff[j][i] = ToBit(genDiff[j][i]);
            }

        }
        off.close();

        std::ofstream bin("../randomText/4uzdBinaryLyginimas.txt");
        double proc;
        double vienodi = 0;
        double procMax = 0;
        double procMin = 100;
        double avgSum = 0;
        int sz = genDiff[0][0].size();
        for(int b = 0; b < 100000; b++) {
            bin << genDiff[0][b] << " " << genDiff[1][b] << endl;
            for (int h = 0; h < sz; h++) {
                if (genDiff[0][b][h] == genDiff[1][b][h]) vienodi++;
            }
            proc = 1-vienodi/sz;
            avgSum += proc;
            if(proc > procMax) procMax = proc;
            if(proc < procMin) procMin = proc;
            vienodi = 0;
        }
        avgSum = avgSum/100000;
        bin << endl;
        bin << "Minimalus skirtingumas (procentais) bitu lygmenyje: " <<std::fixed << std::setprecision(2) <<  procMin*100 << " %"<<endl;
        bin << "Maksimalus skirtingumas (procentais) bitu lygmenyje: " <<std::fixed << std::setprecision(2) <<  procMax*100 << " %"<<endl;
        bin << "Skirtingumo vidurkis bit (procentais)u lygmenyje: " <<std::fixed << std::setprecision(2) <<  avgSum*100 << " %"<<endl;

        cout << "Minimalus skirtingumas (procentais) bitu lygmenyje: " <<std::fixed << std::setprecision(2) <<  procMin*100 << " %"<<endl;
        cout << "Maksimalus skirtingumas (procentais) bitu lygmenyje: " <<std::fixed << std::setprecision(2) <<  procMax*100 << " %"<<endl;
        cout << "Skirtingumo vidurkis bitu lygmenyje: " <<std::fixed << std::setprecision(2) <<  avgSum*100 << " %"<<endl;
        bin.close();
    }
}


