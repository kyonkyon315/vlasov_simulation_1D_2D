#include <iostream>

class Node{
	private:
	int value;
	public:
	void set_value(int x){
		value=x;
	}
	friend std::ostream &operator<<(std::ostream &ostm,const Node &n){
		return ostm<<n.value;
	}
};

int main(){
	Node n;
	n.set_value(5);
	std::cout<<n;
}
