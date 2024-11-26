#pragma once
#include <string>
class My_Cout {
private:
    int bytesPrinted;
public:
    My_Cout();
    int getBytesPrinted();
    friend My_Cout& operator<<(My_Cout& my_cout, std::string str);
    friend My_Cout& operator<<(My_Cout& my_cout, char ch);
    friend My_Cout& operator<<(My_Cout& my_cout, int n);
    friend My_Cout& operator<<(My_Cout& my_cout, double n);
};