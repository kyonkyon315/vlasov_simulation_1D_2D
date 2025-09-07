#ifndef RUNGE_KUTTA2_H
#define RUNGE_KUTTA2_H
#include "../../../distribution_function.h"

namespace ExplicitMethods{
template<typename RealCoordinate,typename VeloCoordinate,typename SpatialDiscretization>
class RungeKutta2{
private:
    using F = DistributionFunction<RealCoordinate,VeloCoordinate>;
    F k1,f_temp;
    const SpatialDiscretization& spatial_discretization;
public:
    RungeKutta2(
        const RealCoordinate& real_coordinate,
        const VeloCoordinate& velo_coordinate,
        const SpatialDiscretization& spatial_discretization
    ):
        spatial_discretization(spatial_discretization),
        k1(real_coordinate,velo_coordinate),
        k2(real_coordinate,velo_coordinate),
        f_temp(real_coordinate,velo_coordinate),
    {}

    void develop(F& f,Value dt){
        spatial_discretization.rhs(f, k1);  // df/dt を k1 に格納

        f_temp.copy_from(f);
        f_temp.axpy(0.5*dt, k1);  // f_temp = f + 0.5*dt*k1

        spatial_discretization.differentiate(f_temp, k1);  // df_temp/dt を k1 に格納

        f.axpy(dt, k1);   // f = f + dt*k1
    }
};
}
#endif// RUNGE_KUTTA2_H
