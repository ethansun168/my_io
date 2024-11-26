#include "my_cin.h"
#include <unistd.h>
#include <fcntl.h>

My_Cin::My_Cin() {
    bytesRead = 0;
    delimiters = {' ', '\n'};
    curChar = ' ';
}

My_Cin::~My_Cin() {
    // Read everything from the buffer
    int flags = fcntl(0, F_GETFL, 0);
    fcntl(0, F_SETFL, flags | O_NONBLOCK);

    read(0, &curChar, 1);
    while (curChar != '\n') {
        read(0, &curChar, 1);
    }
}

int My_Cin::getBytesRead() {
    return bytesRead;
}

bool My_Cin::isDelimiter(char ch) const {
    for (const auto& elt : delimiters) {
        if (ch == elt) {
            return true;
        }
    }
    return false;
}

My_Cin& operator>>(My_Cin& my_cin, std::string& str) {
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

My_Cin& operator>>(My_Cin& my_cin, char& ch) {
    
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

My_Cin& operator>>(My_Cin& my_cin, int& n) {
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

My_Cin& operator>>(My_Cin& my_cin, double& n) {
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