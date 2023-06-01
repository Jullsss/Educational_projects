class Data {
    int _d, _m, _y;
public:
    Data (int d = 0, int m = 0, int y = 0) : _d(d), _m(m), _y(y) {};
    Data (const Data & X);
    int get_d () const;
    int get_m () const;
    int get_y () const;
    void operator= (const Data & X);
    virtual void date () const = 0;
    virtual ~Data ();
};

class Day : public Data {
public:
    Day (int d) : Data (d, 0, 0) {};
    virtual void date () const;
};

class Month : public Data {
public:
    Month (int m) : Data (0, m, 0) {};
    virtual void date () const;
};

class Year : public Data {
public:
    Year (int y) : Data (0, 0, y) {};
    virtual void date () const;
};
