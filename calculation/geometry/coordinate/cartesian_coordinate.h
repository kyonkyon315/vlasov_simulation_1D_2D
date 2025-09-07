#ifndef CARTESIAN_COORDINATE_H
#define CARTESIAN_COORDINATE_H
#include <tuple>
#include <array>
#include "coordinate.h"
template<typename Axis_x,typename Axis_y,typename Axis_z>
class CartesianCoordinate:public Coordinate<Axis_r, Axis_theta, Axis_phi>{
    using Value = double;
    using Index = int;
public:
    const std::tuple<Axis_x,Axis_y,Axis_z> axis_tuple;
    CartesianCoordinate(const Axis_x& axis_x,const Axis_y& axis_y,const Axis_z& axis_z):
        Coordinate<Axis_r, Axis_theta, Axis_phi>(axis_x,axis_y,axis_z)
    {}
};

#endif// CARTESIAN_COORDINATE_H