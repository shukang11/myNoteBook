#include <iostream>
#include <string>

using namespace std;

class Shape {
protected:
    int width;
    int height;

public:
    Shape();
    ~Shape();
    void setWidth(int w);
    void setHeight(int h);
};

Shape::Shape() {
}

Shape::~Shape() {
}

void Shape::setHeight(int h) {
    height = h;
};

void Shape::setWidth(int w) {
    width = w;
};

// 单继承
class Squera: public Shape {
    public:
        int getArea() { return width * height; }
};

// 多继承
class PaintCost {
public:
    int getCost(int area);
};

int PaintCost::getCost(int area) {
    return area * 70;
}

class ReactAngle: public Squera, public PaintCost {
    
};

int main() {
    Shape shape = Shape();
    shape.setHeight(10);
    shape.setWidth(5);

    ReactAngle angle = ReactAngle();
    angle.setHeight(50);
    angle.setWidth(10);
    int cost = angle.getCost(angle.getArea());
    cout << "总消费" << cost << endl;
}