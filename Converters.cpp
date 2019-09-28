#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <bitset>
#include <hashish.h>

using std::string;
string ToHex(const string& s, bool upper_case /* = true */)
{
    std::ostringstream ret;
    for (string::size_type i = 0; i < s.length(); ++i)
        ret << std::hex << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << (int)s[i];

    return ret.str();
}
string ToBit(string& s){
    int i = 0;
    string temp;
    while(s[i])
    {
        switch(s[i])
        {
            case '0' : temp.append("0000");
                break;
            case '1' : temp.append("0001");
                break;
            case '2' : temp.append("0010");
                break;
            case '3' : temp.append("0011");
                break;
            case '4' : temp.append("0100");
                break;
            case '5' : temp.append("0101");
                break;
            case '6' : temp.append("0110");
                break;
            case '7' : temp.append("0111");
                break;
            case '8' : temp.append("1000");
                break;
            case '9' : temp.append("1001");
                break;
            case 'A' : temp.append("1010");
                break;
            case 'B' : temp.append("1011");
                break;
            case 'C' : temp.append("1100");
                break;
            case 'D' : temp.append("1101");
                break;
            case 'E' : temp.append("1110");
                break;
            case 'F' : temp.append("1111");
                break;
            case 'a' : temp.append("1010");
                break;
            case 'b' : temp.append("1011");
                break;
            case 'c' : temp.append("1100");
                break;
            case 'd' : temp.append("1101");
                break;
            case 'e' : temp.append("1110");
                break;
            case 'f' : temp.append("1111");
                break;
            default : std::cout<<"\n Negalimas hex simbolis... "<<s[i];
        }
        i++;
    }
    return temp;
}