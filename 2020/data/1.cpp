#include <iostream>
#include <string>

// базовый абстрактный класс жидкость
class Liquid
{
public:
    Liquid(): color() {}
    Liquid(const std::string &c): color(c) {}
    virtual ~Liquid() {} // базовый класс должен иметь вирт. деструктор
    virtual void boil() = 0; // чисто виртуальная функция
protected:
    std::string color;
    // some other
};

// наследнички
class Drink: public Liquid
{
public:
    // реализация чисто виртуального метода - класс больше не абстрактный
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
   // Liquid l; // error - абстрактный класс не может иметь реализацию в виде объектов
   Liquid *p = new Reagent; // OK
   p->boil();               // Reagent::boil()
   Liquid *p2 = NULL;       // OK
   p2 = new Drink;          // OK
   p2->boil();              // Drink::boil()
   // освобождаем память
   delete p;
   delete p2;
   return 0;
}
