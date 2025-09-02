#include "vlasov_simulator.h"
#include "utils/Timer.h"
#include "schemes/umeda.h"
#include "functions/gaussian_2D_function.h"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
int main(){
    
    /************initial state of f**************
     *                                          *
     *                                          *
     * f(x,vx,vy)=delta(vx-v_input)*delta(vy)   *
     *                                          *
    *********************************************/
    //初期波形の設定　
    const int num_of_grid_x   =100;
    const int num_of_grid_vx  =101;
    const int num_of_grid_vy  =101;
    const int num_of_step     =10000;

    const double grid_size_x  =0.1;
    const double grid_size_vx =0.1;
    const double grid_size_vy =0.1;
    const double grid_size_t  =0.1;
    const double v_input      =0.5;
    Timer timer;
    
    using vec1d = std::vector<double>;
    using vec2d = std::vector<vec1d>;
    using vec3d = std::vector<vec2d>;

    vec3d initial_state(
        num_of_grid_x,
        vec2d(num_of_grid_vx, vec1d(num_of_grid_vy, 0.0))
    );

    for(int x=0;x<grid_size_x;++x){
        for(int vx=0;vx<grid_size_vx;++vx){
            for(int vy=0;vy<grid_size_vy;++vy){
                initial_state[x][vx][vy] = Gaussian_2D_function::function(vx,vy);
            }
        }
    }

    //初期波形の設定　終了
    
    //スキームは以下から選択
    using scheme = Scheme_Umeda;
    //using scheme = Lax_Wendroff;
    //using scheme = MUSCL;
    //using scheme = WENO;

    VlasovSimulator<scheme> simulator(
        initial_state,
        grid_size_x,
        grid_size_vx,
        grid_size_vy,
        grid_size_t,
        num_of_step);

    std::cout<<timer<<"\n";
    timer.start();
    simulator.calc();
    timer.stop();
    std::cout<<timer<<"\n";
    std::string foldername = "../vlasov_result";    
    simulator.save_result(foldername);
}


