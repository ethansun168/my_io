#pragma once
#include <string>
#include <vector>


class My_Cin {
private:
    int bytesRead;
    char curChar;
    std::vector<char> delimiters;
public:
    My_Cin();
    ~My_Cin();
    int getBytesRead();
    bool isDelimiter(char ch) const;
    friend My_Cin& operator>>(My_Cin& my_cin, std::string& str);
    friend My_Cin& operator>>(My_Cin& my_cin, char& ch);
    friend My_Cin& operator>>(My_Cin& my_cin, int& n);

    friend My_Cin& operator>>(My_Cin& my_cin, double& n);
};