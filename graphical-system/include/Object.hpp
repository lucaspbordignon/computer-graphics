#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <string>
#include <vector>

enum OBJECT_TYPE
{
    LINE,
    POLYGON,
    POINT,
    CURVE
};

enum COORDINATE_TYPE
{
    WORLD,
    WINDOW
};

enum DIRECTION
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum ZOOM_TYPE
{
    IN,
    OUT
};

class Coordinate
{
    public:
        Coordinate() {};
        Coordinate(float x, float y):
            _x(x),
            _y(y) {}
        virtual ~Coordinate() {};

        float x() {return _x;}
        float y() {return _y;}

    private:
        float _x, _y;
};

class Object
{
    public:
        Object() {}
        Object(std::string name, OBJECT_TYPE type):
            _name(name),
            _type(type) {}
        virtual ~Object() {};
        virtual void add_coordinates(float x, float y, COORDINATE_TYPE type);
        virtual void add_coordinates(Coordinate coord, COORDINATE_TYPE type);
        virtual void add_coordinates(std::vector<Coordinate>, COORDINATE_TYPE type);
        virtual Coordinate get_point(float t) {};
        Coordinate center_point();
        void update_coordinate(Coordinate coord, int pos);
        OBJECT_TYPE type() {return _type;}
        std::string name() {return _name;}
        std::vector<Coordinate> world_coordinate() {return _world_coordinates;}
        std::vector<Coordinate> window_coordinate() {return _window_coordinates;}

    private:
        std::string _name;
        OBJECT_TYPE _type;
        std::vector<Coordinate> _world_coordinates;
        std::vector<Coordinate> _window_coordinates;
};


class Line: public Object
{
    public:
        Line(std::string name, OBJECT_TYPE type):
            Object(name, type) {}
        ~Line() {}
};

class Polygon: public Object
{
    public:
        Polygon(std::string name, OBJECT_TYPE type):
            Object(name, type) {}
        ~Polygon() {}
};

class Point: public Object
{
    public:
        Point(std::string name, OBJECT_TYPE type):
            Object(name, type) {}
        ~Point() {}
};

class Curve: public Object
{
    public:
        Curve(std::string name, OBJECT_TYPE type):
            Object(name, type) {}
        ~Curve() {}
        Curve(std::string name, Coordinate p1, Coordinate p2, 
            Coordinate p3, Coordinate p4, float rate):
            Object(name, CURVE),
            _p1(p1), _p2(p2), _p3(p3), _p4(p4) {
                if (rate <= 0 || rate >= 1) {
                    rate = 0.1;
                }

                float t;
                for (t = 0; t <= 1; t = t + rate) {
                    add_coordinates(get_point(t), WORLD);
                }
            }
        Coordinate get_point(float t);
    private:
        Coordinate _p1, _p2, _p3, _p4;
        float bezier(float t, float p1n, float p2n, float p3n, float p4n);
};

#endif // OBJECTS_HPP
