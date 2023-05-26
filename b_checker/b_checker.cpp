#include <iostream>
#include <string>

using namespace std;

// symbol order is important
const string open_brackets = "<[(", close_brackets = ">])";
int verify(const string&);
int verify_frame(const char, int, const string&);

int main()
{
    // tests
    std::cout << verify("before ( middle []) after ") << "=" << 1 << "\n";
    std::cout << verify("---(++++)----") << "=" << 1 << "\n";
    std::cout << verify("") << "=" << 1 << "\n";
    std::cout << verify(") (") << "=" << 0 << "\n";
    std::cout << verify("<(   >)") << "=" << 0 << "\n";
    std::cout << verify("(  [  <>  ()  ]  <>  )") << "=" << 1 << "\n";
    std::cout << verify("   (      [)") << "=" << 0 << "\n";
}

int verify(const string& text) {
    auto i = 0;
    while (i < text.length()) {
        auto ch = text[i];
        if (close_brackets.find(ch) != string::npos) return 0; // Failure: forbidden symbol detected 
        auto index = open_brackets.find(ch);
        if (index != string::npos) { // new frame detected
            i = verify_frame(close_brackets[index], ++i, text);
            if (i == -1) return 0; // Failure: nested frame is bad
        }
        ++i;
    }
    return 1; // Success
}

int verify_frame(const char expected, int i, const string& text) {
    while (i < text.length()) {
        auto ch = text[i];
        if (close_brackets.find(ch) != string::npos) return ch == expected ? i : -1;
        auto index = open_brackets.find(ch);
        if (index != string::npos) { // nested frame detected
            i = verify_frame(close_brackets[index], ++i, text); // recursion
            if (i == -1) return -1; // Failure: nested frame is bad :(
        }
        ++i;
    }
    return -1; // Failure: current frame is not closed
}


