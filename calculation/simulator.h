#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <string>
template<typename RealCoordinate,typename VeloCoordinate,typename DistributionFunction,typename Field,typename Current,typename TimeIntegration>
class VlasovSimulator{
    public:
    VlasovSimulator(
        const RealCoordinate& real_coordinate,
        const VeloCoordinate& velo_coordinate,
        const DistributionFunction& distribution_function,
        const Field& field,
        const Current& current,
        const TimeIntegration& time_integration
    );
    void run();
    void save_result(const std::string& folder_name);
};

#endif// SIMULATOR_H
