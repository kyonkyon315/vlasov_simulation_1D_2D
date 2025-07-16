#include "developer_Lax-Wendroff.h"
#include <iostream>
//u_j^n+1 = sum c_n*u_j+n   n=-m,-m+1,------,m-1,m
void Developer_LaxWendroff::next_step(const double* before,double* after){
    double a0=courant_value*(1.+courant_value)/2.;
    double a1=1.-courant_value*courant_value;
    double a2=-courant_value*(1.-courant_value)/2.;
    *after=a0*(*(before-1))+a1*(*before)+a2*(*(before+1));
}
const double* Developer_LaxWendroff::roller(const double* const ptr)const{
    if(ptr < begin){
        return ptr+num_of_grid_x;
    }
    else if(end <= ptr){
        return ptr-num_of_grid_x;
    }
    return ptr;
}
void Developer_LaxWendroff::next_step_edge(const double* before,double* after){
    double a0=courant_value*(1.+courant_value)/2.;
    double a1=1-courant_value*courant_value;
    double a2=-courant_value*(1.-courant_value)/2.;
    *after=a0*(*roller(before-1))+a1*(*roller(before))+a2*(*roller(before+1));
}
