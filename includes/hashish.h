#ifndef HASHISH_H
#define HASHISH_H

#include<vector>
using std::string;

string Hashish(string &, double &);
string Skaitymas(int argc, char* argv[], int &);
string ToHex(const string &, bool);
string ToBit(string&);
string valueCheck(int &, string &, string , int);
string Compress(string &, string, int);
void Generatevector(std::vector<std::string> &, std::vector<std::vector<std::string> > &);
void MainHash(int argc, char* argv[]);
void GenerateAndCheck();
#endif
