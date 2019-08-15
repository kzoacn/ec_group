#include <iostream>
#include "group.hpp"

using namespace std;


string H(const Point &p){
    return p.to_hex();
}
string E(string key,string m){
    return m;
}
string D(string key,string c){
    return c;
}

int main(){
    
    Group group(NID_secp256k1);

    Point g(group);
    Point a(group);
    Point b(group);
    BigInt one;
    one.from_dec("1");
    BigInt two;
    two.from_dec("2");


    group.get_generator(g);
    cout<<g.to_hex()<<endl;

    a=g;
    b=g;

    a.add(a);
    a.add(a);
    cout<<a.to_hex()<<endl;


    two.add(two);
    b.mul(two);
    cout<<b.to_hex()<<endl;
    


    return 0;
}