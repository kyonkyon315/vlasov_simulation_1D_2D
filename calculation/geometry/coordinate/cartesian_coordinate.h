#ifndef CARTESIAN_COORDINATE_H
#define CARTESIAN_COORDINATE_H
#include <tuple>
#include <array>
template<typename... Axes>
class CartesianCoordinate{
public:
    const std::tuple<Axes...> axis_tuple;
    static constexpr size_t dimension = sizeof...(Axes);
    CartesianCoordinate(Axes... axes):axis_tuple(axes...){}
    std::array<size_t,dimension> sizes() const {return {Axes::size...};}
};

#endif// CARTESIAN_COORDINATE_H