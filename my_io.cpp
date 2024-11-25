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
    std::vector<char> buf;
    bool more;
public:
    My_Cin() {
        bytesRead = 0;
        maxBufSize = 100;
        buf.resize(maxBufSize);
        more = false;   
    }

    int getBytesRead() {
        return bytesRead;
    }

    friend My_Cin& operator>>(My_Cin& my_cin, std::string& str) {
        str.clear();
        int bytesRead = 0;
        char* data = my_cin.buf.data();
        
        // If left over from previous cin
        if (my_cin.more) {
            str += my_cin.buf[0];
            my_cin.more = false;
        }

        // Read byte by byte until white space or newline or bufsize reached
        my_cin.bytesRead += read(0, data, 1);
        while (*data != ' ' && *data != '\n' && bytesRead != my_cin.maxBufSize) {
            ++bytesRead;
            ++data;
            my_cin.bytesRead += read(0, data, 1);
        }

        for(int i = 0; i < bytesRead; ++i) {
            str += my_cin.buf[i];
        }

        return my_cin;
    }

    friend My_Cin& operator>>(My_Cin& my_cin, int& n) {
        n = 0;
        char* data = my_cin.buf.data();
        int bytesRead = 0;
        my_cin.bytesRead += read(0, data, 1);
        while(isdigit(*data) && bytesRead != my_cin.maxBufSize) {
            n = 10 * n + (*data - '0');
            my_cin.bytesRead += read(0, data, 1);
            ++bytesRead;
        }
        if (*data != ' ' || *data != '\n') {
            my_cin.more = true;
        }

        return my_cin;
    }

    // friend My_Cin& operator>>(My_Cin& my_cin, double& n) {
    //     n = 0;
    //     int bytesRead = 0;

    //     while (bytesRead != )
    // }
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
    my_cout << "Bytes printed: " << my_cout.getBytesPrinted() << "\n";

    My_Cin my_cin;
    std::string str2;
    int n;
    // my_cout << "Enter a string: ";
    // my_cin >> str2;
    // my_cout << "You entered: " << str2 << "\n";
    // my_cout << "Enter an int: ";
    // my_cin >> n;
    // my_cout << "You entered: " << n << "\n";

    my_cout << "Enter something random: ";
    my_cin >> n >> str;
    my_cout << n << "\n";
    my_cout << str << "\n";
    

    write(1, "\n", 1);
    return 0;
}