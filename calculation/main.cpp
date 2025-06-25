#include "vlasov_simulator.h"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
int main(){
    std::cout<<"helloworld"<<"\n"<<std::flush;
    std::string name_of_scheme="MUSCL";
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
    //初期波形の設定　
    int length=10000;
    int x1    =  500;
    int x2    = 1000;
    int num_of_step=100000;
    double H  = 100.;
    double grid_size_x=0.1;
    double grid_size_t=0.1;
    double v          =0.15;
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
    
    for(int i=0;i<length;++i){
        //initial_state[i]=H*(double)i/(double)length;
    }
    for(int i=0;i<length;++i){
        initial_state[i]=H*std::sin(20.*(double)i/(double)length);
    }
    //初期波形の設定　終了

    VlasovSimulator simulator(initial_state,
        v,
        grid_size_x,
        grid_size_t,
        num_of_step,
        name_of_scheme);
    simulator.calc();
    std::string foldername = "../vlasov_result_sin";    
    simulator.save_result(foldername);
}


