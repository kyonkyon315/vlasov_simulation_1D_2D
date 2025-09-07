#ifndef COORDINATE_H
#define COORDINATE_H
#include <tuple>
#include <array>
template<typename Axis_x,typename Axis_y,typename Axis_z>
class Coordinate{
    using Value = double;
    using Index = int;
private:
    const Index length;
public:
    Coordinate(const Axis_x& axis_x,const Axis_y& axis_y,const Axis_z& axis_z):
        length(axis_x.size()*axis_y.size()*axis_z.size())
    {}
    Index size()const{
        return length;
    }
};

#endif// COORDINATE_H