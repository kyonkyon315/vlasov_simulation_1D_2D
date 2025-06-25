#include "vlasov_simulator.h"
#include "developer_muscl.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>

VlasovSimulator::VlasovSimulator(const std::vector<double> &initial_state,
        double v,
        double grid_size_x,
        double grid_size_t,
        int    num_of_step,
        const std::string type_of_developer):
    v(v),
    grid_size_x(grid_size_x),
    grid_size_t(grid_size_t),
    num_of_step(num_of_step),
    num_of_grid_x(initial_state.size()),
    type_of_developer(type_of_developer)
{
    //num_of_step*num_of_grid_x の二次元配列を作成
    f=std::vector<std::vector<double>>(num_of_step + 1,
                   std::vector<double>(num_of_grid_x,0.));
    if(type_of_developer=="MUSCL"){
        developer = new Developer_MUSCL(v,grid_size_x,grid_size_t,num_of_grid_x);
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
