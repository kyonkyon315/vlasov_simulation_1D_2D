#ifndef DEVELOPER_H
#define DEVELOPER_H
#include <vector>
#include <string>
class Developer{
    private:
    const double grid_size_t;
    const double grid_size_x;
    const double v;

    protected:
    const double courant_value;
    const int num_of_grid_x;
    const int edge_length=5;
    const double* begin;
    const double* end;

    public:
    Developer(const double v,
            const double grid_size_x,
            const double grid_size_t,
            const int num_of_grid_x):
        grid_size_t(grid_size_t),
        grid_size_x(grid_size_x),
        num_of_grid_x(num_of_grid_x),
        courant_value(grid_size_t*v/grid_size_x),
        v(v)
    {}

    virtual ~Developer(){    
    }

    void develop(const std::vector<double>& before,
                       std::vector<double>& after);

    virtual void next_step(const double* before,double* after)=0;
    virtual void next_step_edge(const double* before,double* after)=0;
};
#endif