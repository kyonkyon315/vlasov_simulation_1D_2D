#ifndef VLASOV_SIMULATOR_H
#define VLASOV_SIMULATOR_H
#include <vector>
#include <iostream>
#include <string>
#include "developer.h"
class VlasovSimulator{
    private:
    const double v;
    const double grid_size_x;
    const double grid_size_t;
    const int    num_of_step;
    const int    num_of_grid_x;
    std::vector<std::vector<double>> f; //f[t1][x1]
    Developer* developer;
    const std::string type_of_developer;

    public:
    VlasovSimulator(const std::vector<double> &initial_state,
        double v,
        double grid_size_x,
        double grid_size_t,
        int    num_of_step,
        const std::string type_of_developer);
    ~VlasovSimulator(){
        delete developer;
    }
    void calc();
    void save_result(const std::string &foldername) const;
};

#endif
