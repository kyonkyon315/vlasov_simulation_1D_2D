#ifndef DISTRIBUTION_FUNCTION_H
#define DISTRIBUTION_FUNCTION_H
#include <vector>
template<typename RealCoordinate,typename VeloCoordinate>
class DistributionFunction{
    using Value = double;
    using Index = int;
private:
    const RealCoordinate& real_coordinate;
    const VeloCoordinate& velo_coordinate;
    std::vector<Value> f;
public:
    DistributionFunction(
        const RealCoordinate& real_coordinate,
        const VeloCoordinate& velo_coordinate
    ):
        real_coordinate(real_coordinate),  
        velo_coordinate(velo_coordinate)  
    {
        f.resize(real_coordinate.size()*velo_coordinate.size());
    }

    void copy_from(const DistributionFunction& from){
        f=from.f;
    }

    void axpy(Value val,const DistributionFunction& f1){
        const Index id_end(f.size());
        for(Index id=0;id<id_end:++id){
            f[id]+=val*f1.f[id];
        }
    }
};

#endif// DISTRIBUTION_FUNCTION_H
