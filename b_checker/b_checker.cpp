#include <iostream>
#include <string>

using namespace std;

struct brackets_holder {
    const string open_brackets;
    const string close_brackets;
    
    bool is_closed_bracket(char ch) const {
        return close_brackets.find(ch) != string::npos;
    }    
    char get_closed_bracket(char open) const {
        int i;
        return (i = open_brackets.find(open)) != string::npos ? close_brackets[i] : ' ';        
    }
} brackets{ "<[(" , ">])" }; // brackets order is important

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

bool verify(const string& text) {
    auto i{0}, index{0};
    while (i < text.length()) {
        auto ch = text[i];
        if (brackets.is_closed_bracket(ch)) return false; // Failure: forbidden symbol detected         
        auto closed{ brackets.get_closed_bracket(ch) };
        if(closed != ' '){ // ch is open bracket, so, new frame detected
            i = verify_frame(closed, ++i, text);
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
        if (brackets.is_closed_bracket(ch)) return ch == expected ? i : -1;
        auto closed{ brackets.get_closed_bracket(ch) };
        if (closed != ' ') { // ch is open bracket, so, nested frame detected
            i = verify_frame(closed, ++i, text); // recursion
            if (i == -1) return -1; // Failure: nested frame is bad :(
        }
        ++i;
    }
    return -1; // Failure: current frame is not closed
}


