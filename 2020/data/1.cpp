#include <iostream>
#include <string>

// ������� ����������� ����� ��������
class Liquid
{
public:
    Liquid(): color() {}
    Liquid(const std::string &c): color(c) {}
    virtual ~Liquid() {} // ������� ����� ������ ����� ����. ����������
    virtual void boil() = 0; // ����� ����������� �������
protected:
    std::string color;
    // some other
};

// �����������
class Drink: public Liquid
{
public:
    // ���������� ����� ������������ ������ - ����� ������ �� �����������
    void boil() { std::cout << "Drink::boil()\n"; }
};

class Fuel: public Liquid
{
public:
    void boil() { std::cout << "Fuel::boil()\n"; }
};

class Reagent: public Liquid
{
public:
    void boil() { std::cout << "Reagent::boil()\n"; }
};

int main()
{
   // Liquid l; // error - ����������� ����� �� ����� ����� ���������� � ���� ��������
   Liquid *p = new Reagent; // OK
   p->boil();               // Reagent::boil()
   Liquid *p2 = NULL;       // OK
   p2 = new Drink;          // OK
   p2->boil();              // Drink::boil()
   // ����������� ������
   delete p;
   delete p2;
   return 0;
}
