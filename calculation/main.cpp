#include "simulator.h"
#include "schemes/include.h"
#include "geometry/include.h"
#include <string>
int main(){    

//有限体積法か有限差分法のどちらかを選択してください
#define use_FiniteVolumeMethod
//#define use_FiniteDifferenceMethod
    
#ifdef use_FiniteVolumeMethod
//flux_limiterを以下から選択してください
    using flux_limiter              = Limiter::TakayukiUmeda2008;
    //using flux_limiter              = Limiter::VanLeer;
    //using flux_limiter              = Limiter::SuperBee;
    //using flux_limiter              = Limiter::MinMod;

//riemann_solverを以下から選択してください
    using riemann_solver            = RiemannSolver::Rusanov;
    //using riemann_solver            = RiemannSolver::HLL;
    //using riemann_solver            = RiemannSolver::ExactRiemannSolver;
    //using riemann_solver            = RiemannSolver::Roe;

    using spatial_discretization    = FiniteVolumeMethod<flux_limiter, riemann_solver>;
#endif// use_FiniteVolumeMethod

#ifdef use_FiniteDifferenceMethod
    using spatial_discretization    = FiniteDifferenceMethod<>;
#endif// use_FiniteDifferenceMethod


//陽解法と陰解法のどちらかを選択してください
#define use_explicit_method
//#define use_inplicit_method

#ifdef use_explicit_method
//explicit_methodを以下から選択してください
    using explicit_method           = ExplicitMethods::RungeKutta2;
    //using explicit_method           = ExplicitMethods::RungeKutta4;
    //using explicit_method           = ExplicitMethods::LeapFrog;

    using time_integration          = TimeIntegration<Explicit<explicit_method>>;
#endif// use_explicit_method


#ifdef use_inplicit_method
//inplicit_methodを以下から選択してください
    using inplicit_method           = InplicitMethods::CrankNicolson;
    using inplicit_method           = InplicitMethods::ImexSchemes;

    using time_integration          = TimeIntegration<Inplicit<inplicit_method>>;
#endif// use_inplicit_method



    using field_solver              = FieldSolver<FDTD>;

//シミュレーション空間を設定してください。
    using Value = double;
    using Index = int;

#define Periodic true
#define Aperiodic false
#define PI 3.14159265
    //実空間の設定
    const Index x_size(100);
    const Value x_begin(0.),x_end(100.);
    using Axis_x                    = Axis<Periodic,x_size>;
    using real_space                = CartesianCoordinate<Axis_x>;
    Axis_x axis_x(x_begin,x_end);

    //速度空間の設定
    Index r_size(100);
    Value r_begin(1.),r_end(100.);
    using axis_r                    = Axis<Aperiodic,r_size,r_begin,r_end>;
    
    Index theta_size(100);
    Value theta_begin(0.),theta_end(PI);
    using axis_theta                = Axis<Aperiodic,theta_size,theta_begin,theta_end>;

    Index phi_size(100);
    Value phi_begin(0.),phi_end(2.*PI);
    using axis_phi                  = Axis<Periodic,phi_size,phi_begin,phi_end>;

    using velocity_space            = PolarCoordinates_3d<axis_r,axis_theta,axis_phi>;
    //実空間と速度空間を合わせてシミュレーション空間を定義する。
    using space                     = Space<real_space,velocity_space>;

    //電磁場を扱うクラス
    using field                     = ElectroMagneticField<real_space>;

    //電流を扱うクラス
    using current                   = Current<real_space>;

    //粒子情報、電磁場、電流を合わせて空間の情報をまとめる。
    using state                     = State<space,field,current>;

    using VlasovSimulator  = Simulator<state,spatial_discretization,time_integration,field_solver>;

    VlasovSimulator simulator;
    simulator.run();
    std::string foldername = "../vlasov_result";    
    simulator.save_result(foldername);
}


