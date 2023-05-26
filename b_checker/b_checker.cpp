#include <iostream>
#include <string>

using namespace std;

// symbol order is important
const string open_brackets{"<[("}, close_brackets{">])"};
bool verify(const string&);
int verify_frame(const char, int, const string&);

int main()
{
    // tests   
    std::cout << verify("before ( middle []) after ") << "=" << true << "\n";
    std::cout << verify("---(++++)----") << "=" << true << "\n";
    std::cout << verify("") << "=" << true << "\n";
    std::cout << verify(") (") << "=" << false << "\n";
    std::cout << verify("<(   >)") << "=" << false << "\n";
    std::cout << verify("(  [  <>  ()  ]  <>  )") << "=" << true << "\n";
    std::cout << verify("   (      [)") << "=" << false << "\n";
}

inline bool closed_bracket_found(char ch) {
    return close_brackets.find(ch) != string::npos;
}

bool verify(const string& text) {
    auto i{0}, index{0};
    while (i < text.length()) {
        auto ch = text[i];
        if (closed_bracket_found(ch)) return false; // Failure: forbidden symbol detected                 
        if ((index = open_brackets.find(ch)) != string::npos) { // new frame detected
            i = verify_frame(close_brackets[index], ++i, text);
            if (i == -1) return false; // Failure: nested frame is bad
        }
        ++i;
    }
    return true; // Success
}

int verify_frame(const char expected, int i, const string& text) {
    auto index{0};
    while (i < text.length()) {
        auto ch = text[i];
        if (closed_bracket_found(ch)) return ch == expected ? i : -1;        
        if ((index = open_brackets.find(ch)) != string::npos) { // nested frame detected
            i = verify_frame(close_brackets[index], ++i, text); // recursion
            if (i == -1) return -1; // Failure: nested frame is bad :(
        }
        ++i;
    }
    return -1; // Failure: current frame is not closed
}


