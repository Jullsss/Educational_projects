#include <iostream>

using namespace std;

class Analyser {
    char c;
public:
    void S();
    void A();
    void B();
    virtual void gc() {
        std::cin >> c;
    }
    ostream & operator<< (ostream &s, Analyzer *a) {
        S();
        s << "success" << endl;
        return s;
    }
    void operator* () {
        S();
        std::cout << "success" << endl;
    }
};

void Analyser::S() {
    A();
    B();
    //cout << "d";
}

void Analyser::A() {
    gc();
    if (c == 'a') {
        B();
        //cout << "da";
    } else if (c == 'c') {
        A();
    }
}

void Analyser::B() {
    gc();
    if (c == 'b') {
        A();
    }
}

class Parser {
public:
      virtual void gc () = 0; // считывание символа со стандартного ввода, маркер конца – @
};

int main () {
    Analyser a;
    Parser& p = a;
    p.gc ();        // считываем первый символ со стандартного ввода
    std::cout << "----------";
    std::cout << *a;  // операция * запускает анализатор по РС-методу  по грамматике
                     // S -> ABd@
                    // A -> aB { da } | cA
                     // B -> bA | ε
                     // затем печатается строка error или success, в зависимости от вх. цепочки.
    std::cout << "----------";
    return 0;
}

