#include <iostream>

template<typename A>
class B{
    public:
    A a;
    B(A a):
        a(a)
    {}

    template<typename C>
    void print(C c){
        std::cout<<a<<" "<<c<<"\n";
    }
};

int main(){
    int x(0);
    double y(1.);
    B b(x);
    b.print(y);
}
