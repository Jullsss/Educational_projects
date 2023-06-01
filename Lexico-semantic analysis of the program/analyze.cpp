#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <stack>

using namespace std;

enum type_of_lex {
    LEX_NULL,/*0*/
    LEX_AND, LEX_BOOLEAN, LEX_CONT, LEX_DO, LEX_ELSE, /*1, 2, 3, 4, 5*/
    LEX_FALSE, LEX_IF, LEX_INT, LEX_MAIN, LEX_NOT, LEX_OR, /*6, 7, 8, 9, 10, 11*/
    LEX_PROG, LEX_READ, LEX_REAL, LEX_STRING, LEX_TRUE,/*12, 13, 14, 15, 16*/
    LEX_WHILE, LEX_WRITE, LEX_FIN, LEX_POINT, LEX_SEMICOLON,/*17, 18, 19, 20, 21*/
    LEX_COMMA, LEX_NEG, LEX_EQEQ /*==*/ , LEX_LEFTPAR, LEX_RIGHTPAR, //"=="
    /*22, 23, 24, 25, 26*/
    LEX_EQ, LEX_LESS, LEX_GREATER, LEX_PLUS, LEX_PLUSEQ /*+=*/, /*27, 28, 29, 30, 31*/
    LEX_PLUSPLUS /*++*/, LEX_MINUS, LEX_MINUSEQ /*-=*/, LEX_MINUSMINUS/*--*/, LEX_MUL, /*32, 33, 34, 35, 36*/
    LEX_MULEQ, LEX_DIV, LEX_DIVEQ, LEX_LEQ, LEX_GEQ, /*37, 38, 39, 40, 41*/
    LEX_LEFTBR /*{*/, LEX_RIGHTBR, LEX_NUMB, LEX_ID, LEX_QUO,/*42, 43, 44, 45, 46*/
    POLIZ_LABEL,/*47*/
    POLIZ_ADDRESS,/*48*/
    POLIZ_GO,/*49*/
    POLIZ_FGO /*50*/
};

class Lex {
    type_of_lex t_lex;
    double v_lex;
public:
    Lex (type_of_lex t = LEX_NULL, double v = 0.0) {
        t_lex = t;
        v_lex = v;
    }
    type_of_lex get_type() const {
        return t_lex;
    }
    int get_value () const {
        return v_lex;
    }
    friend ostream& operator << (ostream & s, Lex l );
    bool operator== (Lex X) const {
        if (t_lex == X.t_lex && v_lex == X.v_lex) {
            return true;
        } else {
            return false;
        }
    }
};

class Ident {
    string name;
    bool declare;
    type_of_lex type;
    bool assign;
    int value;
public:
    Ident() {
        declare = false;
        assign = false;
    }
    Ident(const string &n) {
        name = n;
        declare = false;
        assign = false;
    }
    bool operator== (const string &s) const {
        return name == s;
    }
    string get_name() const{
        return name;
    }
    bool get_declare() const{
        return declare;
    }
    void put_declare(){
        declare = true;
    }
    type_of_lex get_type() const{
        return type;
    }
    void put_type (type_of_lex t){
        type = t;
    }
    bool get_assign() const{
        return assign;
    }
    void put_assign(){
        assign = true;
    }
    int get_value() const{
        return value;
    }
    void put_value(int v){
        value = v;
    }
};

vector <Ident> TID;
int put (const string &buf) {
    vector <Ident> :: iterator k;
    if ((k = find (TID.begin(), TID.end(), buf)) != TID.end() ){
        return k - TID.begin();
    }
    TID.push_back (Ident(buf));
    return TID.size() - 1;
}

class Scanner {
    FILE *fp;
    char c;
    int look (string &buf, const char **token){
        int i = 0;
        while (token[i]){
            if (buf == token[i]) {
                //cout << buf << ' ' << token[i] << ' ' << i << endl;
                return i;
            }
            i++;
            if (i > 25) {
                break;
            }
        }
        return 0;
    }
    void gc(){
        c = fgetc (fp);
    }
public:
    static const char *TW[], *TD[];
    Scanner (const char *program) {
        fp = fopen ( program, "r" );
    }
    Lex get_lex();
};

const char *Scanner::TW[] = {"and","boolean","continue", "do","else","false", "if","int","main", "not",
    "or","program", "read","real","string","true","while","write"};

const char *Scanner::TD[] = {"@", ".", ";", ",", "!=", "==", "(", ")",
    "=","<", ">", "+", "+=", "++", "-", "-=", "--", "*", "*=", "/", "/=", "<=", ">=", "{", "}"};

Lex Scanner::get_lex () {
    enum state {H, IDENT, NUMB, SL, COM1, COM2, COM3, ALE, NEG, MINUS, PLUS, MUL, ALL, QUO, REAL1, REAL2};
    state CS = H;
    string buf; int j, e, k = 0;
    double f, d;
    do {
        gc ();
        //cout << buf << endl;
        switch(CS) {
            case H:
                if (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
                    CS = H;
                } else {
                    if (isalpha(c)){
                        buf.push_back(c); CS = IDENT;
                    } else if (isdigit(c)){
                        d = c - '0'; CS = NUMB;
                    } else if (c == '/') {
                        CS = SL;
                    } else if (c == '=' || c == '<' || c == '>') {
                        buf.push_back(c); CS = ALE;
                    } else if ( c == '@' || c == EOF) {
                        return Lex (LEX_FIN);
                    } else if (c == '-') {
                        buf.push_back(c); CS = MINUS;
                    } else if (c == '+'){
                        buf.push_back(c); CS = PLUS;
                    } else if (c == '*'){
                        buf.push_back(c); CS = MUL;
                    } else if (c == '!'){
                        buf.push_back(c); CS = NEG;
                    } else if (c == '"'){
                        CS = QUO;
                    } else if (c == '#') {
                        CS = COM3;
                    } else {
                        buf.push_back(c); CS = ALL;
                    }
                }
                break;
            case IDENT:
                if (isalpha(c) || isdigit(c)) {
                    buf.push_back(c);
                } else {
                    ungetc(c, fp);
                    if ((j = look(buf, TW))) {
                        return Lex((type_of_lex) (j + 1) , (j + 1) );
                    } else {
                        j = put (buf);
                        return Lex (LEX_ID, j);
                    }
                }
                break;
            case NUMB:
                if (isdigit (c)) {
                    d = d * 10 + (c - '0');
                } else if (c == '.') {
                    CS = REAL1;
                } else if (c == 'e' || c == 'E'){
                    CS = REAL2;
                } else {
                    ungetc(c, fp);
                    return Lex (LEX_NUMB, d);
                }
                break;
            case REAL1: {
                if (isdigit (c)) {
                    f = f * 10 + (c - '0');
                    k++;
                } else if (c == 'e' || c == 'E'){
                    int i = 0;
                    while (i < k) {
                        f /= 10;
                        i++;
                    }
                    d += f;
                    CS = REAL2;
                } else {
                    int i = 0;
                    while (i < k) {
                        f /= 10;
                        i++;
                    }
                    f += d;
                    //cout << f << endl;
                    ungetc(c, fp);
                    return Lex (LEX_NUMB, f);
                }
                break;
            }
            case REAL2:
                if (isdigit (c)) {
                    e = e * 10 + (c - '0');
                } else {
                    ungetc(c, fp);
                    int i = 0;
                    while (i < e) {
                        d *= 10;
                        i++;
                    }
                    return Lex (LEX_NUMB, d);
                }
                break;
            case SL:
                if (c == '*') {
                    CS = COM1;
                } else if (c == '/') {
                    CS = COM3;
                } else if (c == '='){
                    buf.push_back(c);
                    j = look(buf, TD);
                    return Lex ((type_of_lex) (j + (int) LEX_FIN ), j );
                } else {
                    ungetc(c, fp);
                    j = look (buf, TD);
                    return Lex ((type_of_lex) (j + (int) LEX_FIN ), j );
                }
                break;
            case COM1:
                if (c == '*') {
                    CS = COM2;
                } else if (c == '@')
                    throw c;
                break;
            case COM2:
                if (c == '/') {
                    CS = H;
                } else if (c == '@') {
                    throw c;
                } else {
                    CS = COM1;
                }
                break;
            case COM3:
                if (c == '\n') {
                    CS = H;
                } else if (c == '@') {
                    throw c;
                }
                break;
            case ALE:
                if ( c == '=') {
                    buf.push_back(c);
                    j = look(buf, TD);
                    return Lex ((type_of_lex) (j + (int) LEX_FIN), j );
                } else {
                    ungetc(c, fp);
                    j = look (buf, TD);
                    return Lex ((type_of_lex) (j + (int) LEX_FIN), j );
                }
                break;
            case PLUS:
                if (c == '=' || c == '+'){
                    buf.push_back(c);
                    j = look(buf, TD);
                    return Lex ((type_of_lex) (j + (int) LEX_FIN), j );
                } else {
                    ungetc(c, fp);
                    j = look (buf, TD);
                    return Lex ((type_of_lex) (j + (int) LEX_FIN), j );
                }
                break;
            case MINUS:
                if (c == '=' || c == '-'){
                    buf.push_back(c);
                    j = look(buf, TD);
                    return Lex ((type_of_lex) (j + (int) LEX_FIN), j );
                } else {
                    ungetc(c, fp);
                    j = look (buf, TD);
                    return Lex ((type_of_lex) (j + (int) LEX_FIN), j );
                }
                break;
            case MUL:
                if (c == '='){
                    buf.push_back(c);
                    j = look(buf, TD);
                    return Lex ((type_of_lex) (j + (int) LEX_FIN), j );
                } else {
                    ungetc(c, fp);
                    j = look (buf, TD);
                    return Lex ((type_of_lex) (j + (int) LEX_FIN), j );
                }
                break;
            case NEG:
                if ( c == '=' ) {
                    buf.push_back(c);
                    j = look (buf, TD);
                    return Lex (LEX_NEG, j);
                } else throw '!';
                break;
            case QUO:
                if (c == '@' || c == '\n') {
                    throw c;
                } else if (c == '"') {
                    CS = H;
                    j = put (buf);
                    return Lex (LEX_QUO, j);
                } else {
                    buf.push_back(c);
                }
                break;
            case ALL:
                if ((j = look (buf, TD))) {
                    ungetc(c, fp);
                    CS = H;
                    return Lex((type_of_lex)(j + (int)LEX_FIN), j );
                } else {
                    throw c;
                }
                break;
        } //end switch
    } while (true);
}

ostream & operator<< ( ostream &s, Lex l ) {
    string t;
    if ( l.t_lex <= 18 )
        t = Scanner::TW[l.t_lex - 1];
    else if (l.t_lex >= 19 && l.t_lex <= 43)
        t = Scanner::TD[l.t_lex - 19];
    else if (l.t_lex == 44)
        t = "NUMB";
    else if (l.t_lex == 45)
        t = TID[l.v_lex].get_name();
    else if (l.t_lex == 46)
        t = TID[l.v_lex].get_name();
    else if (l.t_lex == 47)
        t = "Label";
    else if (l.t_lex == 48)
        t = "Addr";
    else if (l.t_lex == 49)
        t = "!";
    else if (l.t_lex == 50)
        t = "!F";
    else
        throw l;
    s << l.t_lex << " (" << t << ',' << l.v_lex << ");" << endl;
    return s;
}

// cинтаксический анализ
template <class T, class T_EL>
void from_st(T st, T_EL & i) {
    i = st.top();
    st.pop();
}

class Parser {
    Lex curr_lex; //текущая лексема
    type_of_lex c_type; //тип лексемы
    int c_val; //значение
    Scanner scan; //сканнер
    stack < int > st_int; //стек переменных
    stack < double > st_real;
    stack < int > st_str;
    stack < type_of_lex >  st_lex; //стек типов лексем

    void  P(); //prog
    void  D();
    void  D1();
    void  D2();
    void  D3();
    void  B();
    void  S();
    void  E();
    void  E1();
    void  T();
    void  F();

    void  dec(type_of_lex type);
    void  real(type_of_lex type);
    void  str(type_of_lex type);
    void  check_id ();
    void  check_op ();
    void  check_not ();
    void  eq_type ();
    void  eq_boolean ();
    void  check_id_in_read ();
    void  gl() {
        curr_lex = scan.get_lex();
        cout << curr_lex << endl;
        c_type = curr_lex.get_type();
        c_val = curr_lex.get_value();
    }
public:
    vector <Lex> poliz;
    Parser (const char *program) : scan (program) {}
    void  analyze();
};

void Parser::analyze () {
    gl();
    P();
    if (c_type != LEX_FIN) {
        throw curr_lex;
    }
    //for (Lex l : poliz)
        //cout << l;
    cout << endl << "Yes!!!" << endl;
}

void Parser::P () {
    if (c_type == LEX_PROG){
        gl ();
        if (c_type == LEX_LEFTBR) { // c == {
            gl ();
            D();
            B();
            if (c_type == LEX_RIGHTBR) // c == }
                gl ();
            else
                throw curr_lex;
        } else {
            throw curr_lex;
        }
    } else {
        throw curr_lex;
    }
}

void Parser::D () {
    if (c_type == LEX_INT) {
        gl ();
        D1 ();
        while (c_type == LEX_COMMA) {
            gl ();
            D1 ();
        }
        if (c_type != LEX_SEMICOLON)
            throw curr_lex;
        else
            gl ();
    } else if (c_type == LEX_REAL) {
        gl ();
        D2 ();
        while (c_type == LEX_COMMA) {
            gl ();
            D2 ();
        }
        if (c_type != LEX_SEMICOLON)
            throw curr_lex;
        else
            gl ();
    } else if (c_type == LEX_STRING) {
        gl ();
        D3 ();
        while (c_type == LEX_COMMA) {
            gl ();
            D3 ();
        }
        if (c_type != LEX_SEMICOLON)
            throw curr_lex;
        else
            gl ();
    } else
        throw curr_lex;
}

void Parser::D1 () {
    if ( c_type != LEX_ID )
        throw curr_lex;
    else {
        st_int.push ( c_val );
        dec(LEX_NUMB);
        gl ();
        if (c_type == LEX_EQ) {
            gl ();
            if (c_type != LEX_NUMB && c_type != LEX_ID && c_type != LEX_MINUS) {
                throw curr_lex;
            } else if (c_type == LEX_MINUS){
                if (c_type != LEX_NUMB && c_type != LEX_ID) {
                    throw curr_lex;
                } else {
                    gl();
                }
            } else {
                //проверка соответствия типу int
                gl();
            }
        }
    }
}

void Parser::D2 () {
    if ( c_type != LEX_ID )
        throw curr_lex;
    else {
        st_real.push ( c_val );
        real(LEX_REAL);
        gl ();
        if (c_type == LEX_EQ) {
            gl ();
            if (c_type != LEX_NUMB && c_type != LEX_ID && c_type != LEX_MINUS) {
                throw curr_lex;
            } else if (c_type == LEX_MINUS){
                if (c_type != LEX_NUMB && c_type != LEX_ID) {
                    throw curr_lex;
                } else {
                    gl();
                }
            } else {
                //проверка соответствия типу real
                gl();
            }
        }
    }
}

void Parser::D3 () {
    if ( c_type != LEX_ID )
        throw curr_lex;
    else {
        st_str.push ( c_val );
        str(LEX_STRING);
        gl ();
        if (c_type == LEX_EQ) {
            gl ();
            if (c_type != LEX_QUO) {
                throw curr_lex;
            } else {
                //проверка соответствия типу string
                gl();
            }
        }
    }
}

void Parser::B () {
    S();
    while (c_type == LEX_SEMICOLON) {
        gl();
        if (c_type == LEX_RIGHTBR) {
            break;
        }
        S();
    }
}

void Parser::S () {
    //int pl0, pl1, pl2, pl3;

    if (c_type == LEX_INT || c_type == LEX_REAL || c_type == LEX_STRING) {
        D();
    }

    if (c_type == LEX_IF) {
        gl ();
        if (c_type != LEX_LEFTPAR) {
            throw curr_lex;
        } else {
            gl();
        }
        E ();
        //eq_boolean (); //проверка на boolean
        if (c_type != LEX_RIGHTPAR) {
            throw curr_lex;
        } else {
            gl();
        }
        //pl2 = poliz.size();
        //poliz.push_back (Lex());
        //poliz.push_back (Lex(POLIZ_FGO));
        if (c_type == LEX_LEFTBR) {
            gl ();
            if (c_type == LEX_RIGHTBR) {
                gl();
            } else {
                B ();
                if (c_type == LEX_RIGHTBR){
                    gl();
                } else
                    throw curr_lex;
            }
            //pl3 = poliz.size ();
            //poliz.push_back ( Lex() );
            //poliz.push_back (Lex(POLIZ_GO));
            //poliz[pl2] = Lex(POLIZ_LABEL, poliz.size());

            if (c_type == LEX_ELSE) {
                gl();
                if (c_type != LEX_LEFTBR) {
                    throw curr_lex;
                } else {
                    gl();
                }
                if (c_type == LEX_RIGHTBR) {
                    gl();
                    B();
                } else {
                    B ();
                    if (c_type == LEX_RIGHTBR){
                        gl();
                        B();
                    } else
                        throw curr_lex;
                }
                //poliz[pl3] = Lex(POLIZ_LABEL, poliz.size());
            } else
                throw curr_lex;
        } else
            throw curr_lex;
    }//end if
    else if (c_type == LEX_WHILE) {
        //pl0 = poliz.size();
        gl ();
        if (c_type != LEX_LEFTPAR) {
            throw curr_lex;
        } else {
            gl();
        }
        E ();
        //eq_boolean (); //проверка на boolean
        if (c_type != LEX_RIGHTPAR) {
            throw curr_lex;
        } else {
            gl();
        }
        //pl1 = poliz.size();
        //poliz.push_back (Lex());
        //poliz.push_back (Lex(POLIZ_FGO));
        if (c_type == LEX_LEFTBR) {
            gl();
            //poliz.push_back (Lex (POLIZ_LABEL, pl0));
            //poliz.push_back (Lex ( POLIZ_GO));
            //poliz[pl1] = Lex ( POLIZ_LABEL, poliz.size() );
            if (c_type == LEX_RIGHTBR) {
                gl();
                B();
            } else {
                B ();
                if (c_type == LEX_RIGHTBR){
                    gl();
                    B();
                } else
                    throw curr_lex;
            }
        } else
            throw curr_lex;
    }//end while
    else if (c_type == LEX_DO) {
        //pl0 = poliz.size();
        gl ();
        if (c_type == LEX_LEFTBR) {
            gl();

            //poliz.push_back (Lex (POLIZ_LABEL, pl0));
            //poliz.push_back (Lex ( POLIZ_GO));
            //poliz[pl1] = Lex ( POLIZ_LABEL, poliz.size() );
            if (c_type == LEX_RIGHTBR) {
                gl();
                B();
            } else {
                B ();
                if (c_type == LEX_RIGHTBR){
                    gl();
                    B();
                } else
                    throw curr_lex;
            }
        } else
            throw curr_lex;
        if (c_type == LEX_WHILE) {
            if (c_type != LEX_LEFTPAR) {
                throw curr_lex;
            } else {
                gl();
            }
            E ();
            //eq_boolean (); //проверка на boolean
            if (c_type != LEX_RIGHTPAR) {
                throw curr_lex;
            } else {
                gl();
                if (c_type == LEX_SEMICOLON) {
                    gl();
                    B();
                } else {
                    throw curr_lex;
                }
            }
            //pl1 = poliz.size();
            //poliz.push_back (Lex());
            //poliz.push_back (Lex(POLIZ_FGO));
        } else
            throw curr_lex;
    }//end do - while
    else if (c_type == LEX_CONT) {
        gl();
        if (c_type == LEX_SEMICOLON) {
            gl();
            B();
        } else {
            throw curr_lex;
        }
    } //continue
    else if(c_type == LEX_READ) {
        gl();
        if (c_type == LEX_LEFTPAR) {
            gl();
            if (c_type == LEX_ID) {
                check_id_in_read();
                //poliz.push_back (Lex( POLIZ_ADDRESS, c_val));
                gl();
            } else
                throw curr_lex;
            if ( c_type == LEX_RIGHTPAR ) {
                gl();
                //poliz.push_back (Lex (LEX_READ));
            } else
                throw curr_lex;
        } else
            throw curr_lex;
    }//end read
    else if (c_type == LEX_WRITE) {
        gl();
        if (c_type == LEX_LEFTPAR) {
            gl();
            E();
            while (c_type == LEX_COMMA) {
                gl();
                E();
            }
            if (c_type == LEX_RIGHTPAR) {
                gl();
                //poliz.push_back (Lex(LEX_WRITE));
            } else
                throw curr_lex;
        } else
            throw curr_lex;
    }//end write
    else if ( c_type == LEX_ID ) {
        check_id ();
        //poliz.push_back (Lex ( POLIZ_ADDRESS, c_val) );
        gl();
        if ( c_type == LEX_EQ ) {
            gl();
            E();
            eq_type();
            while (c_type == LEX_EQ) {
                gl();
                E();
                eq_type();
            }
            //poliz.push_back (Lex (LEX_ASSIGN) );
        } else if (c_type == LEX_PLUSEQ){
            gl();
            E();
            eq_type();
            //poliz.push_back (Lex (LEX_ASSIGN) );
        } else if (c_type == LEX_MINUSEQ) {
            gl();
            E();
            eq_type();
            //poliz.push_back (Lex (LEX_ASSIGN) );
        } else if (c_type == LEX_MULEQ) {
            gl();
            E();
            eq_type();
            //poliz.push_back (Lex (LEX_ASSIGN) );
        } else if (c_type == LEX_DIVEQ) {
            gl();
            E();
            eq_type();
            //poliz.push_back (Lex (LEX_ASSIGN) );
        } else
            throw curr_lex;
    }//assign-end
    else {
        throw curr_lex;
    }
}

void Parser::E () {
    E1();
    while ( c_type == LEX_EQEQ || c_type == LEX_LESS || c_type == LEX_GREATER ||
        c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEG ) {
            st_lex.push (c_type);
            gl();
            E1();
            check_op();
    }
}

void Parser::E1 () {
    T();
    while ( c_type == LEX_PLUS || c_type == LEX_MINUS || c_type == LEX_OR) {
        st_lex.push (c_type);
        gl();
        T();
        check_op();
    }
}

void Parser::T () {
    F();
    while ( c_type == LEX_MUL || c_type == LEX_DIV || c_type == LEX_AND) {
        st_lex.push (c_type);
        gl();
        F();
        check_op();
    }
}

/*
    LEX_FIN, LEX_POINT, LEX_SEMICOLON,
    LEX_COMMA, LEX_NEG, LEX_EQEQ , LEX_RIGHTPAR, LEX_LEFTPAR,
    LEX_EQ, LEX_LESS, LEX_GREATER, LEX_PLUS, LEX_PLUSEQ,
    LEX_PLUSPLUS ++, LEX_MINUS, LEX_MINUSEQ -=, LEX_MINUSMINUS--, LEX_MUL,
    LEX_MULEQ, LEX_DIV, LEX_DIVEQ, LEX_LEQ, LEX_GEQ,
    LEX_LEFTBR {, LEX_RIGHTBR,
    {"@", ".", ";", ",", "!=", "==", "(", ")",
    "=","<", ">", "+", "+=", "++", "-", "-=", "--", "*", "*=", "/", "/=", "<=", ">=", "{", "}"};
};*/

void Parser::F () {
    if ( c_type == LEX_ID ) {
        check_id();
        //poliz.push_back (Lex (LEX_ID, c_val));
        gl();
    } else if (c_type == LEX_QUO) {
        gl();
    } else if ( c_type == LEX_NUMB ) {
        st_lex.push ( LEX_NUMB );
        //poliz.push_back ( curr_lex );
        gl();
    } else if ( c_type == LEX_TRUE ) {
        st_lex.push ( LEX_BOOLEAN );
        //poliz.push_back (Lex (LEX_TRUE, 1) );
        gl();
    } else if ( c_type == LEX_FALSE) {
        st_lex.push ( LEX_BOOLEAN );
        //poliz.push_back (Lex (LEX_FALSE, 0) );
        gl();
    } else if (c_type == LEX_NOT) {
        gl();
        F();
        check_not();
    } else if ( c_type == LEX_LEFTPAR ) {
        gl();
        E();
        if ( c_type == LEX_RIGHTPAR)
            gl();
        else
            throw curr_lex;
    } else
        throw curr_lex;
}

//семантический анализ
void Parser::dec ( type_of_lex type ) {
    int i;
    while ( !st_int.empty()) {
        from_st(st_int, i);
        if ( TID[i].get_declare() )
            throw "twice";
        else {
            TID[i].put_declare();
            TID[i].put_type(type);
            break;
        }
    }
}

void Parser::real ( type_of_lex type ) {
    int i;
    while ( !st_real.empty()) {
        from_st(st_real, i);
        if ( TID[i].get_declare() )
            throw "twice";
        else {
            TID[i].put_declare();
            TID[i].put_type(type);
            break;
        }
    }
}

void Parser::str ( type_of_lex type ) {
    int i;
    while ( !st_str.empty()) {
        from_st(st_str, i);
        if ( TID[i].get_declare() )
            throw "twice";
        else {
            TID[i].put_declare();
            TID[i].put_type(type);
            break;
        }
    }
}

void Parser::check_id () {
    if ( TID[c_val].get_declare() ) {
        st_lex.push ( TID[c_val].get_type() );
    } else
        throw "not declared";
}

void Parser::check_op () {
    type_of_lex t1, t2, op, t = LEX_NUMB, r = LEX_BOOLEAN, s = LEX_STRING;

    from_st(st_lex, t2);
    from_st(st_lex, op);
    from_st(st_lex, t1);

    if (op == LEX_MUL || op == LEX_DIV)
        r = LEX_NUMB;
    else if (op == LEX_PLUS || op == LEX_MINUS) {
        if (t2 == t) {
            r = LEX_NUMB;
        } else if (t2 == s) {
            r = LEX_STRING;
        }
    }
    if (op == LEX_OR || op == LEX_AND)
        t = LEX_BOOLEAN;
    if (t1 == t2) {
        if ((t1 == LEX_INT && t == LEX_NUMB) || (t1 == t))
            st_lex.push(r);
    } else
        throw "wrong types are in operation";
    //poliz.push_back (Lex (op) );
}

void Parser::check_not () {
    if (st_lex.top() != LEX_BOOLEAN)
        throw "wrong type is in not";
    //else
        //poliz.push_back (Lex (LEX_NOT));
}

void Parser::eq_type () {
    type_of_lex t;
    from_st(st_lex, t);
    if ( t != st_lex.top())
        throw "wrong types are in =";
    st_lex.pop();
}

void Parser::eq_boolean () {
    int lex = st_lex.top();
    if (lex != LEX_BOOLEAN)
        cout << lex << ' ' << LEX_BOOLEAN << endl;
        //throw "expression is not boolean";
    st_lex.pop();
}

void Parser::check_id_in_read () {
    if ( !TID [c_val].get_declare() )
        throw "not declared";
}

int main()
{
    //Scanner X("prog.txt");
    Parser Z("prog.txt");
        try {
            //Lex Y = X.get_lex();
            //cout << Y << endl;
            //if (Y == Lex (LEX_FIN)) {
            //    cout << "success" << endl;
            //    return 0;
            //}
            Z.analyze();
        }
        catch (char c) {
            cerr << "Illegal char " << c << endl;
            cout << "Error" << endl;
            return 1;
        }
        catch (Lex l) {
            cout << "unexpected lexeme" << l << endl;
            return 1;
        }
        catch ( const char *source ) {
            cout << source << endl;
            return 1;
        }
    return 0;
}
