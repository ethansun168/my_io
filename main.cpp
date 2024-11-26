#include "my_cin.h"
#include "my_cout.h"


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

    my_cout << "Enter a string: ";
    my_cin >> str2;
    my_cout << "You entered: " << str2 << "\n";
    my_cout << "Enter an int: ";
    my_cin >> n;
    my_cout << "You entered: " << n << "\n";

    my_cin >> str2;

    my_cout << "Enter a double: ";
    my_cin >> d;
    my_cout << "You entered: " << d << "\n";

    my_cin >> str2;

    my_cout << "Enter a char: ";
    my_cin >> ch;
    my_cout << "You entered: " << ch << "\n";

    // my_cout << "Enter something random: ";
    // my_cin >> n >> d >> ch >> str;
    // my_cout << n << "\n";
    // my_cout << d << "\n";
    // my_cout << ch << "\n";
    // my_cout << str << "\n";

    // my_cout << "Bytes read: " << my_cin.getBytesRead() << '\n';

    // write(1, "\n", 1);
    return 0;
}