#include "solver.h"
#include <vector>
#include <iostream>
#include <string>
int main(){
    /************initial state of f**************
     *                                          *
     *                                          *
     *                          -> V            *
     *          ========                        *
     *                 |H                       *
     * |-=======--------===============---->x   *
     * ^        ^       ^              ^        *
     * 0        x1      x2             length   *
     *                                          *
    *********************************************/
    
    int length=1000000;
    int x1    =  50000;
    int x2    = 100000;
    double H  = 100.;
    double grid_size_x=0.1;
    double grid_size_t=0.1;
    double v          =1.5;
    std::vector<double> initial_state(length);
    for(int i=0;i<x1;i++){
        initial_state[i]=0.;
    }
    for(int i=x1;i<x2;i++){
        initial_state[i]=H;
    }
    for(int i=x2;i<length;i++){
        initial_state[i]=0.;
    }

    Solver solver(initial_state,v,grid_size_x,grid_size_t);
    solver.calc();
    std::string foldername="vlasov_result";    
    solver.save_result(foldername);
}
