#ifndef SOLVER_H
#define SOLVER_H
#include<vector>
#include<iostream>
#include <string>
class Solver{
    private:
    
    public:
    Solver(const std::vector<double> &initial_state,
        double v,
        double grid_size_x,
        double grid_size_t);
    ~Solver();
    void calc();
    void save_result(const std::string &foldername) const;
};

#endif