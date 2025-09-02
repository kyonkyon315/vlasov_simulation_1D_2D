#ifndef VLASOV_SIMULATOR_H
#define VLASOV_SIMULATOR_H
#include <vector>
#include <iostream>
#include <string>
#include "developer.h"

template <typename Scheme>
class VlasovSimulator{
    private:
    const double v_input;
    const double grid_size_x;
    const double grid_size_vx;
    const double grid_size_vy;
    const double grid_size_t;
    const int    num_of_step;
    const int    num_of_grid_x;
    const int    num_of_grid_vx;
    const int    num_of_grid_vy;

    using vec1d = std::vector<double>;
    using vec2d = std::vector<vec1d>;
    using vec3d = std::vector<vec2d>;

    vec3d f_odd,f_even;//f_odd[x][vx][vy]
    Developer* developer;
    const std::string type_of_developer;

    public:
    VlasovSimulator(const vec3d &initial_state,
        double v_input,
        double grid_size_x,
        double grid_size_vx,
        double grid_size_vy,
        double grid_size_t,
        int    num_of_step);
    ~VlasovSimulator(){
        delete developer;
    }
    void calc();
    void save_result(const std::string &foldername) const;
};

#endif
