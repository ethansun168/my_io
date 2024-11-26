#include <iostream>

int main() {
    std::string str;
    int n;
    double d;
    char ch;

    std::cout << "Enter something random: ";
    std::cin >> n >> d >> ch >> str;
    std::cout << n << "\n";
    std::cout << d << "\n";
    std::cout << ch << "\n";
    std::cout << str << "\n";
}