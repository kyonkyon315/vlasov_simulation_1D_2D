#ifndef POLAR_COODINATE_3D_H
#define POLAR_COODINATE_3D_H
#include "coordinate.h"
template<typename Axis_r,typename Axis_theta,typename Axis_phi>
class PolarCoordinates_3d:public Coordinate<Axis_r, Axis_theta, Axis_phi>{
public:
    PolarCoordinates_3d(const Axis_r& axis_r,const Axis_theta& axis_theta,const Axis_phi& axis_phi):
        Coordinate<Axis_r, Axis_theta, Axis_phi>(axis_r,axis_theta,axis_phi)
    {}

};
#endif// POLAR_COODINATE_3D_H