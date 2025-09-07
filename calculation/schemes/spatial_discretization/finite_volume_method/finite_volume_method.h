#ifndef FINITE_VOLUME_METHOD_H
#define FINITE_VOLUME_METHOD_H

template<typename FluxLimiter,typename RiemannSolver>
class FiniteVolumeMethod{
    public:
    FiniteVolumeMethod(const FluxLimiter& flux_limiter,const RiemannSolver& riemann_solver){

    }
    template<typename DistributionFunction>
    void differentiate(const DistributionFunction& f,DistributionFunction& result){
        
    }
};

#endif
