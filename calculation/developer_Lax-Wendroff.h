#ifndef DEVELOPER_LAXWENDROFF_H
#define DEVELOPER_LAXWENDROFF_H
#include "developer.h"
#include <vector>
#include <iostream>

class Developer_LaxWendroff:public Developer{
    private:
    const double* roller(const double* const ptr)const;

    public:
    Developer_LaxWendroff(double v,double grid_size_x,double grid_size_t,int num_of_step):
        Developer(v,grid_size_x,grid_size_t,num_of_step)
    {
        std::cout<<courant_value<<"";
    }
    void next_step(const double* before,double* after)override;
    void next_step_edge(const double* before,double* after)override;
};

#endif