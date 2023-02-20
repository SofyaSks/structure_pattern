#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

// ������� 

//class FahrenheitSensor
//{
//public:
//
//    float getFahrenheitTemp() {
//        float t = 32.0;
//        // ... ����� �� ���
//        return t;
//    }
//};
//
//class Sensor
//{
//public:
//    virtual ~Sensor() {}
//    virtual float getTemperature() = 0;
//};
//
//class Adapter : public Sensor
//{
//public:
//    Adapter(FahrenheitSensor* p) : p_fsensor(p) {
//    }
//    ~Adapter() {
//        delete p_fsensor;
//    }
//    float getTemperature() {
//        return (p_fsensor->getFahrenheitTemp() - 32.0) * 5.0 / 9.0;
//    }
//private:
//    FahrenheitSensor* p_fsensor;
//};
//
//void main()
//{
//    Sensor* p = new Adapter(new FahrenheitSensor);
//    cout << "Celsius temperature = " << p->getTemperature() << endl;
//    delete p;
//
//}

// ����_������_�������

//class FahrenheitSensor
//{
//public:
//    float getFahrenheitTemp()
//    {
//        float t = 32.0;
//        // ... 
//        return t;
//    }
//protected:
//    void adjust() { cout << "JUST" << endl; }
//};
//
//class Sensor
//{
//public:
//    virtual ~Sensor() {}
//    virtual float getTemperature() = 0;
//    virtual void adjust() = 0;
//};
//
//class Adapter : public Sensor, private FahrenheitSensor
//{
//public:
//    Adapter() { }
//    float getTemperature() {
//        return (getFahrenheitTemp() - 32.0) * 5.0 / 9.0;
//    }
//    void adjust() {
//        FahrenheitSensor::adjust();
//    }
//};
//
//void main()
//{
//    Sensor* p = new Adapter();
//    p->adjust();
//    cout << "Celsius temperature = " << p->getTemperature() << endl;
//    delete p;
//}



// ����������� 
// ��������� ������������� ������� � ����������� ��������� � ����� �������� � ���� ���, ���� �� ��� ��� ��������� ������
// ���������

 // Component 
class Unit
{
public:
    virtual int getStrength() = 0;
    virtual void addUnit(Unit* p) { assert(false); }
    virtual ~Unit() {}
};
// Primitives
class Archer : public Unit
{
public:
    virtual int getStrength() { return 1; }
};
class Infantryman : public Unit
{
public:
    virtual int getStrength() { return 2; }
};
class Horseman : public Unit
{
public:
    virtual int getStrength() { return 3; }
};

// Composite
class CompositeUnit : public Unit
{
public:
    int getStrength() {
        int total = 0;
        for (int i = 0; i < c.size(); ++i)
            total += c[i]->getStrength();
        return total;
    }
    void addUnit(Unit* p) { c.push_back(p); }
    ~CompositeUnit() {
        for (int i = 0; i < c.size(); ++i)
            delete c[i];
    }
private:
    std::vector<Unit*> c;
};

// ��������������� ������� ��� �������� �������
CompositeUnit* createLegion()
{
    // ������� ������ ��������:
    CompositeUnit* legion = new CompositeUnit;
    // 3000 ������� ����������
    for (int i = 0; i < 3000; ++i)
        legion->addUnit(new Infantryman);
    // 1200 ������ ����������
    for (int i = 0; i < 1200; ++i)
        legion->addUnit(new Archer);
    // 300 ���������
    for (int i = 0; i < 300; ++i)
        legion->addUnit(new Horseman);
    return legion;
}

int main()
{
    // ������� ����� ������� �� 4-� ��������
    CompositeUnit* army = new CompositeUnit;
    for (int i = 0; i < 4; ++i)
        army->addUnit(createLegion());
    cout << "Roman army damaging strength is "
        << army->getStrength() << endl;
    // �
    delete army;
    return 0;
}