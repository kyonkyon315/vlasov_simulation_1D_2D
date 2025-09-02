#include "vlasov_simulator.h"
#include "utils/Timer.h"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
int main(){
    std::cout<<"helloworld"<<"\n"<<std::flush;
    std::string name_of_scheme="Lax-Wendroff";
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
    int num_of_grid_x   =100;
    int num_of_grid_vx  =101;
    int num_of_grid_vy  =101;
    int num_of_step     =10000;

    double grid_size_x  =0.1;
    double grid_size_vx =0.1;
    double grid_size_vy =0.1;
    double grid_size_t  =0.1;
    double v_input      =0.5;
    Timer timer;
    
    std::vector<std::vector<std::vector<double>>> 
    initial_state(num_of_grid_x, std::vector<std::vector<double>>(
                  num_of_grid_vx,std::vector<double>(
                  num_of_grid_vy,0.                  )));
    //初期波形の設定　終了
    
    VlasovSimulator simulator(initial_state,
        v_input,
        grid_size_x,
        grid_size_vx,
        grid_size_vy,
        grid_size_t,
        num_of_step,
        name_of_scheme);

    std::cout<<timer<<"\n";
    timer.start();
    simulator.calc();
    timer.stop();
    std::cout<<timer<<"\n";
    std::string foldername = "../vlasov_result";    
    simulator.save_result(foldername);
}


