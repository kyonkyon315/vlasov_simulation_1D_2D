#include "developer.h"
#include <iostream>
void Developer::develop(const std::vector<double>& before,
                         std::vector<double>& after)
{
    begin = before.data();
    end = begin + num_of_grid_x;
    const double* before_ptr=before.data();
    double* after_ptr=after.data();
    int i=0;
    for( ;i<edge_length;++i){
        next_step_edge(before_ptr++,after_ptr++);
    } 
    for( ;i < num_of_grid_x-edge_length; ++i){
        next_step(before_ptr++,after_ptr++);
    }
    for( ;i< num_of_grid_x;++i){
        next_step_edge(before_ptr++,after_ptr++);
    }    
}
