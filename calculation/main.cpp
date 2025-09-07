#include "simulator.h"
#include "distribution_function.h"
#include "electro_magnetic_field.h"
#include "current.h"
#include "schemes/include.h"
#include "geometry/include.h"

#include <string>
int main(){    

    /********************************
     *                              
     *　   シミュレーション空間の設定
     * 
     ********************************/

    using Value = double;
    using Index = int;

#define Periodic true
#define Aperiodic false
#define PI 3.14159265
//実空間の設定

//x軸の設定
#define x_axis_is_heterogeneous
//#define x_axis_is_homogeneous
#ifdef x_axis_is_heterogeneous
    const Index x_size(100);
    const Value x_begin(0.),x_end(100.);
    const HeteroAxis<Periodic> x_axis(x_size,x_begin,x_end);//周期境界条件
    //const Hetero<Aperiodic> x_axis(x_size,x_begin,x_end);//非周期境界条件
#endif
#ifdef x_axis_is_homogeneous
    const HomoAxis  x_axis;//この軸について一様（実質次元に寄与しない。
#endif

//y軸の設定
//#define y_axis_is_heterogeneous
#define y_axis_is_homogeneous
#ifdef y_axis_is_heterogeneous
    const Index y_size(100);
    const Value y_begin(0.),y_end(100.);
    const HeteroAxis<Periodic> y_axis(y_size,y_begin,y_end);//周期境界条件
    //const Hetero<Aperiodic> y_axis(y_size,y_begin,y_end);//非周期境界条件
#endif
#ifdef y_axis_is_homogeneous
    const HomoAxis  y_axis;//この軸について一様（実質次元に寄与しない。
#endif

//z軸の設定
//#define z_axis_is_heterogeneous
#define z_axis_is_homogeneous
#ifdef z_axis_is_heterogeneous
    const Index z_size(100);
    const Value z_begin(0.),z_end(100.);
    const HeteroAxis<Periodic> z_axis(z_size,z_begin,z_end);//周期境界条件
    //const Hetero<Aperiodic> z_axis(z_size,z_begin,z_end);//非周期境界条件
#endif
#ifdef z_axis_is_homogeneous
    const HomoAxis  z_axis;//この軸について一様（実質次元に寄与しない。
#endif
    const CartesianCoordinate real_coordinate(x_axis,y_axis,z_axis);

//速度空間の設定
//速度空間を極座標にするかデカルト座標にするか決めてください。
#define use_cartesian_coordinate_in_v
//#define use_polar_coordinate_in_v

#ifdef use_polar_coordinate_in_v
    //
    const Index r_size(100) ,theta_size(100) ,phi_size(100);
    const Value r_begin(1.) ,theta_begin(0.) ,phi_begin(0.);
    const Value r_end(100.) ,theta_end(PI)   ,phi_end(2.*PI);

    const Axis<Aperiodic> axis_r(r_size,r_begin,r_end);
    const Axis< Periodic> axis_theta(theta_size,theta_begin,theta_end);
    const Axis< Periodic> axis_phi(phi_size,phi_begin,phi_end);

    const PolarCoordinates_3d velo_coordinate(axis_r,axis_theta,axis_phi);
#else

//vx軸の設定
#define vx_axis_is_heterogeneous
//#define vx_axis_is_delta_like
#ifdef vx_axis_is_heterogeneous
    const Index vx_size(100);
    const Value vx_begin(0.),vx_end(100.);
    const HeteroAxis<Periodic> vx_axis(vx_size,vx_begin,vx_end);//周期境界条件
    //const Hetero<Aperiodic> vx_axis(vx_size,vx_begin,vx_end);//非周期境界条件
#endif
#ifdef vx_axis_is_delta_like
    const Value vx_place_of_peak(10.);
    const DeltaLikeAxis  vx_axis(vx_place_of_peak);//この軸は一つの値しかもたない（実質次元に寄与しない。
#endif

//vy軸の設定
#define vy_axis_is_heterogeneous
//#define vy_axis_is_delta_like
#ifdef vy_axis_is_heterogeneous
    const Index vy_size(100);
    const Value vy_begin(0.),vy_end(100.);
    const HeteroAxis<Periodic> vy_axis(vy_size,vy_begin,vy_end);//周期境界条件
    //const Hetero<Aperiodic> vy_axis(vy_size,vy_begin,vy_end);//非周期境界条件
#endif
#ifdef vy_axis_is_delta_like
    const Value vy_place_of_peak(10.);
    const DeltaLikeAxis  vy_axis(vy_place_of_peak);//この軸は一つの値しかもたない（実質次元に寄与しない。
#endif

//vz軸の設定
//#define vz_axis_is_heterogeneous
#define vz_axis_is_delta_like
#ifdef vz_axis_is_heterogeneous
    const Index vz_size(100);
    const Value vz_begin(0.),vz_end(100.);
    const HeteroAxis<Periodic> vz_axis(vz_size,vz_begin,vz_end);//周期境界条件
    //const Hetero<Aperiodic> vz_axis(vz_size,vz_begin,vz_end);//非周期境界条件
#endif
#ifdef vz_axis_is_delta_like
    const Value vz_place_of_peak(10.);
    const DeltaLikeAxis  vz_axis(vz_place_of_peak);//この軸は一つの値しかもたない（実質次元に寄与しない。
#endif
    const CartesianCoordinate velo_coordinate(vx_axis,vy_axis,vz_axis);
#endif

    //分布関数を扱うクラス（巨大配列の責任者）
    DistributionFunction distribution_function(real_coordinate,velo_coordinate);

    //電磁場を扱うクラス
    ElectroMagneticField field(real_coordinate);//電磁場のグリッドを決めるためにreal_coordinateの情報が必要

    //電流を扱うクラス
    Current current(real_coordinate);//電流のグリッドを決めるためにreal_coordinateの情報が必要

    /********************************
     *                              
     *　   時間発展アルゴリズムの設定
     * 
     ********************************/

//有限体積法か有限差分法のどちらかを選択してください
#define use_FiniteVolumeMethod
//#define use_FiniteDifferenceMethod
    
#ifdef use_FiniteVolumeMethod
//flux_limiterを以下から選択してください
    Limiter::TakayukiUmeda2008        flux_limiter;
    //Limiter::VanLeer                  flux_limiter;
    //Limiter::SuperBee                 flux_limiter;
    //Limiter::MinMod                   flux_limiter;

//riemann_solverを以下から選択してください
    RiemannSolver::Rusanov            riemann_solver;
    //RiemannSolver::HLL                riemann_solver;
    //RiemannSolver::ExactRiemannSolver riemann_solver;
    //RiemannSolver::Roe                riemann_solver;

    FiniteVolumeMethod spatial_discretization(flux_limiter, riemann_solver);
#endif// use_FiniteVolumeMethod

#ifdef use_FiniteDifferenceMethod
    FiniteDifferenceMethod spatial_discretization;
#endif// use_FiniteDifferenceMethod


//陽解法と陰解法のどちらかを選択してください
#define use_explicit_method
//#define use_implicit_method

#ifdef use_explicit_method
//explicit_methodを以下から選択してください
    const ExplicitMethods::RungeKutta2      time_integration(real_coordinate,velo_coordinate,spatial_discretization);
    //const ExplicitMethods::RungeKutta4      explicit_method(real_coordinate,velo_coordinate);
    //const ExplicitMethods::LeapFrog         explicit_method(real_coordinate,velo_coordinate);


    

#endif// use_explicit_method


#ifdef use_implicit_method
//implicit_methodを以下から選択してください
    const ImplicitMethods::CrankNicolson    implicit_method(real_coordinate,velo_coordinate);
    //const ImplicitMethods::ImexSchemes      implicit_method(real_coordinate,velo_coordinate);

#endif// use_implicit_method

    
    VlasovSimulator simulator(
        real_coordinate,
        velo_coordinate,
        distribution_function,
        field,
        current,
        time_integration
    );
    simulator.run();
    std::string foldername = "../vlasov_result";    
    simulator.save_result(foldername);
}


