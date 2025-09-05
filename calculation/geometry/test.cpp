#include "axis.h"
#include "coordinate/cartesian_coordinate.h"
#include <iostream>
#define Periodic true
#define Aperiodic false

int main(){
    Axis<Periodic,5> axis1(1.,5.);
    Axis<Periodic,5> axis2(1.,5.);
    Axis<Periodic,5> axis3(1.,6.);
    Axis<Aperiodic,5> axis4(1.,5.);
    std::cout<<axis1[3]<<"\n";

    CartesianCoordinate<
        Axis<Periodic,5>,
        Axis<Periodic,5>,
        Axis<Periodic,5>,
        Axis<Aperiodic,5>> 
        coodinate(axis1,axis2,axis3,axis4);

    for(auto x: coodinate.sizes()){
        std::cout<<x<<"\n";
    }
}

