#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>

class My_Cout {
private:
    int bytesPrinted;
public:
    My_Cout() {
        bytesPrinted = 0;
    }

    int getBytesPrinted() {
        return bytesPrinted;
    }

    friend My_Cout& operator<<(My_Cout& my_cout, std::string str) {
        my_cout.bytesPrinted += write(1, str.c_str(), str.length());
        return my_cout;
    }

    friend My_Cout& operator<<(My_Cout& my_cout, int n) {
        std::string str = std::to_string(n);
        my_cout << str;
        return my_cout;
    }

    friend My_Cout& operator<<(My_Cout& my_cout, double n) {
        int precision = 100;
        int out = n * precision;
        n = (double) out / precision;
        std::string str = std::to_string(n);
        str.erase(str.find_last_not_of('0') + 1, std::string::npos);
        str.erase(str.find_last_not_of('.') + 1, std::string::npos);
        my_cout << str;
        return my_cout;
    }
};

class My_Cin {
private:
    int bytesRead;
    int maxBufSize;
    std::vector<int> buf;
public:
    My_Cin() {
        bytesRead = 0;
        maxBufSize = 100;
        buf.resize(100);
    }

    friend My_Cin& operator>>(My_Cin& my_cin, std::string& str) {
        read(0, my_cin.buf.data(), my_cin.maxBufSize);
        return my_cin;
    }
};




int main() {
    std::string str = "hello";
    My_Cout my_cout;
    my_cout << str << str << "\n";
    my_cout << 12345 << "\n";
    my_cout << 0x12345 << "\n";
    my_cout << 0b0100101 << "\n";
    my_cout << 31.345 << "\n";
    my_cout << 31.000 << "\n";
    my_cout << "Bytes printed: " << my_cout.getBytesPrinted();

    // My_Cin my_cin;
    // std::string str2;
    // my_cin >> str2;
    

    write(1, "\n", 1);
    return 0;
}