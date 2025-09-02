#include "vlasov_simulator.h"
#include "developer_Lax-Wendroff.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
#include <stdexcept>

int check_shape_of_initial_state(const std::vector<std::vector<std::vector<double>>> &initial_state){
    if(initial_state.size()<1){
        throw std::length_error("initial_state の形状が不適切です。\n");
    }
    else if(initial_state[0].size()<1){
        throw std::length_error("initial_state の形状が不適切です。\n");
    }
    else if(initial_state[0][0].size()<1){
        throw std::length_error("initial_state の形状が不適切です。\n");
    }
    return initial_state.size();
}

VlasovSimulator::VlasovSimulator(const std::vector<std::vector<std::vector<double>>> &initial_state,
        double v_input,
        double grid_size_x,
        double grid_size_vx,
        double grid_size_vy,
        double grid_size_t,
        int    num_of_step,
        const std::string &type_of_developer):
    v_input(v_input),
    grid_size_x(grid_size_x),
    grid_size_vx(grid_size_vx),
    grid_size_vy(grid_size_vy),
    grid_size_t(grid_size_t),
    num_of_step(num_of_step),
    num_of_grid_x(check_shape_of_initial_state(initial_state)),
    num_of_grid_vx(initial_state[0].size()),
    num_of_grid_vy(initial_state[0][0].size()),
    type_of_developer(type_of_developer)
{
    //num_of_step*num_of_grid_x の二次元配列を作成
    f=std::vector<std::vector<double>>(num_of_step + 1,
                   std::vector<double>(num_of_grid_x,0.));
    if(type_of_developer=="Lax-Wendroff"){
        developer = new Developer_LaxWendroff(v,grid_size_x,grid_size_t,num_of_grid_x);
    }
    f[0]=initial_state;
}

void VlasovSimulator::calc(){
    for(int step=1;step < num_of_step+1; ++step){
        //時刻step-1の状態を元に、時刻stepの状態を計算する
        developer->develop(f[step-1],f[step]);
    }
}

void VlasovSimulator::save_result(const std::string &foldername) const{
    std::filesystem::create_directory(foldername);
    std::string filename = foldername+"/data.bin";
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "ファイルを開けません: " << filename << '\n';
        return;
    }

    // 行数・列数を書き出し
    size_t rows = f.size();
    size_t cols = (rows > 0) ? f[0].size() : 0;
    ofs.write(reinterpret_cast<const char*>(&rows), sizeof(rows));
    ofs.write(reinterpret_cast<const char*>(&cols), sizeof(cols));

    // データを書き出し
    for (const auto& row : f) {
        ofs.write(reinterpret_cast<const char*>(row.data()),
                  sizeof(double) * cols);
    }
}
