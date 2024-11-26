#include <unistd.h>
#include <fcntl.h>
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


    friend My_Cout& operator<<(My_Cout& my_cout, char ch) {
        std::string str = std::string(1, ch);
        my_cout << str;
        return my_cout;
    }

    friend My_Cout& operator<<(My_Cout& my_cout, int n) {
        std::string str = std::to_string(n);
        my_cout << str;
        return my_cout;
    }

    friend My_Cout& operator<<(My_Cout& my_cout, double n) {
        int precision = 10000;
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
    char curChar;
    std::vector<char> delimiters;
public:
    My_Cin() {
        bytesRead = 0;
        delimiters = {' ', '\n'};
        curChar = ' ';
    }

    ~My_Cin() {
        // Read everything from the buffer
        int flags = fcntl(0, F_GETFL, 0);
        fcntl(0, F_SETFL, flags | O_NONBLOCK);

        read(0, &curChar, 1);
        while (curChar != '\n') {
            read(0, &curChar, 1);
        }
    }

    int getBytesRead() {
        return bytesRead;
    }

    bool isDelimiter(char ch) const {
        for (const auto& elt : delimiters) {
            if (ch == elt) {
                return true;
            }
        }
        return false;
    }

    friend My_Cin& operator>>(My_Cin& my_cin, std::string& str) {
        str.clear();

        // If left over from previous cin
        if (!my_cin.isDelimiter(my_cin.curChar)) {
            str += my_cin.curChar;
        }

        // Read byte by byte until delimiter
        my_cin.bytesRead += read(0, &my_cin.curChar, 1);
        while (!my_cin.isDelimiter(my_cin.curChar)) {
            str += my_cin.curChar;
            my_cin.bytesRead += read(0, &my_cin.curChar, 1);
        }

        return my_cin;
    }

    friend My_Cin& operator>>(My_Cin& my_cin, char& ch) {
        
        // If left over from previous cin
        if (!my_cin.isDelimiter(my_cin.curChar)) {
            ch = my_cin.curChar;
        }
        else {
            // Keep reading until no delimiter
            my_cin.bytesRead += read(0, &my_cin.curChar, 1);
            while(my_cin.isDelimiter(my_cin.curChar)) {
                my_cin.bytesRead += read(0, &my_cin.curChar, 1);
            }
            ch = my_cin.curChar;
        }

        my_cin.bytesRead += read(0, &my_cin.curChar, 1);
        return my_cin;

    }

    friend My_Cin& operator>>(My_Cin& my_cin, int& n) {
        // TODO: handle integer overflow
        n = 0;

        // If left over from previous cin
        if (!my_cin.isDelimiter(my_cin.curChar)) {
            if (!isdigit(my_cin.curChar)) {
                return my_cin;
            }
            n = 10 * n + my_cin.curChar;
        }

        // Read until a non digit
        my_cin.bytesRead += read(0, &my_cin.curChar, 1);
        while(isdigit(my_cin.curChar)) {
            n = 10 * n + (my_cin.curChar - '0');
            my_cin.bytesRead += read(0, &my_cin.curChar, 1);
        }

        return my_cin;
    }

    friend My_Cin& operator>>(My_Cin& my_cin, double& n) {
        n = 0;

        int numDecimals = 1;
        bool decimal = false;

        // If left over from previous cin
        if (!my_cin.isDelimiter(my_cin.curChar) || my_cin.curChar == '.') {
            if (my_cin.curChar == '.') {
                decimal = true;
            }
            else if (!isdigit(my_cin.curChar)) {
                return my_cin;
            }
            else {
                n = 10 * n + (my_cin.curChar - '0');
            }
        }

        // Read until non digit or not a '.'
        my_cin.bytesRead += read(0, &my_cin.curChar, 1);
        while ((isdigit(my_cin.curChar) || my_cin.curChar == '.')) {
            if (my_cin.curChar == '.') {
                if (decimal) {
                    break;
                }
                decimal = true;
            }
            else {
                if (decimal) {
                    numDecimals *= 10;
                }
                n = 10 * n + (my_cin.curChar - '0');
            }
            my_cin.bytesRead += read(0, &my_cin.curChar, 1);
        }
        n /= numDecimals;
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
    my_cout << 'q' << "\n";
    my_cout << "Bytes printed: " << my_cout.getBytesPrinted() << "\n";

    My_Cin my_cin;
    std::string str2;
    int n;
    double d;
    char ch;

    // my_cout << "Enter a string: ";
    // my_cin >> str2;
    // my_cout << "You entered: " << str2 << "\n";
    // my_cout << "Enter an int: ";
    // my_cin >> n;
    // my_cout << "You entered: " << n << "\n";

    // my_cout << "Enter a double: ";
    // my_cin >> d;
    // my_cout << "You entered: " << d << "\n";

    my_cout << "Enter a char: ";
    my_cin >> ch;
    my_cout << "You entered: " << ch << "\n";

    // my_cout << "Enter something random: ";
    // my_cin >> n >> d >> ch >> str;
    // my_cout << n << "\n";
    // my_cout << d << "\n";
    // my_cout << ch << "\n";
    // my_cout << str << "\n";

    my_cout << "Bytes read: " << my_cin.getBytesRead();

    write(1, "\n", 1);
    return 0;
}