#include "my_cout.h"
#include <unistd.h>

My_Cout::My_Cout() {
    bytesPrinted = 0;
}

int My_Cout::getBytesPrinted() {
    return bytesPrinted;
}

My_Cout& operator<<(My_Cout& my_cout, std::string str) {
    my_cout.bytesPrinted += write(1, str.c_str(), str.length());
    return my_cout;
}


My_Cout& operator<<(My_Cout& my_cout, char ch) {
    std::string str = std::string(1, ch);
    my_cout << str;
    return my_cout;
}

My_Cout& operator<<(My_Cout& my_cout, int n) {
    std::string str = std::to_string(n);
    my_cout << str;
    return my_cout;
}

My_Cout& operator<<(My_Cout& my_cout, double n) {
    int precision = 10000;
    int out = n * precision;
    n = (double) out / precision;
    std::string str = std::to_string(n);
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    str.erase(str.find_last_not_of('.') + 1, std::string::npos);
    my_cout << str;
    return my_cout;
}