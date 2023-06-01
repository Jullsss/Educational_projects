/*
Создать иерархию классов
Жидкость<-Напиток
Жидкость<-Топливо
Жидкость<-Реагент
Жидкость - абстрактный класс? инкапсулирует свойства цвет, название, температура замерзания/кипения и т.д.,
а также виртуальный метод Boil. Классы Напиток, Топливо, Реагент реализуют метод Boil(реализация на свое усмотрение)
*/

#include <iostream>
#include <string>

class Aqua {
private:
    std::string m_name;
    std::string m_color;
    double m_boiling_point;
    double m_freezing_point;
public:
    Aqua(const std::string & name, const std::string & color, double boiling, double freezing) : m_name(name), m_color(color),
        m_boiling_point(boiling), m_freezing_point(freezing) {}
    std::string getName() const { return m_name; }
    std::string getColor() const { return m_color; }
    double getBoilingPoint() const { return m_boiling_point; }
    double getFreezingPoint() const { return m_freezing_point; }
    virtual std::string boil() const = 0;
    virtual ~Aqua() {}
};

class Drink : public Aqua {
public:
    Drink(const std::string & name, const std::string & color, double boiling, double freezing) : Aqua(name, color, boiling, freezing) {}
    virtual std::string boil() const { return "Many boubles..."; }
};

class Fuel : public Aqua {
public:
    Fuel(const std::string & name, const std::string & color, double boiling, double freezing) : Aqua(name, color, boiling, freezing) {}
    virtual std::string boil() const { return "CRUSH AND BURN!!!"; }
};

class Reagent : public Aqua {
public:
    Reagent(const std::string & name, const std::string & color, double boiling, double freezing) : Aqua(name, color, boiling, freezing) {}
    virtual std::string boil() const { return "So strange smell here..."; }
};

int main() {
    Aqua * examples[3];
    examples[0] = new Drink("Clear water", "Limpid", 100.0, 0.0);
    examples[1] = new Fuel("Gazoline", "Brown", 90.0, -30.0);
    examples[2] = new Reagent("Lakmus", "Green", 120.0, -10.0);

    for ( int i = 0; i < 3; ++i )
        std::cout << "Object #" << (i + 1) << "\nName: " << examples[i]->getName() << "\nColor: " << examples[i]->getColor()
            << "\nBoiling poing: " << examples[i]->getBoilingPoint() << "\nFreezing point: " << examples[i]->getFreezingPoint()
            << "\nWhen boil: " << examples[i]->boil() << std::endl;

    for ( int i = 0; i < 3; ++i )
        delete examples[i];

    return 0;
}
