#include <iostream>
#include "group.hpp"

using namespace std;


//stupid hash
string H(const Point &p){
    return p.to_hex();
}

string E(string key,string m){
    for(int i=0;i<m.length();i++)
        m[i]^=key[i];
    return m;
}
string D(string key,string c){
    for(int i=0;i<c.length();i++)
        c[i]^=key[i];
    return c;
}



string ot(string m[],int c){
    BigInt a,b;
    a.from_dec("324123");
    b.from_dec("4134213");
    //stupid random
    
    Group group(NID_secp256k1);
    Point A(group),B(group);
    Point g(group);
    group.get_generator(g);

    
    A=g;

    A.mul(a);
    //send A
    if(c==0){
        B=g;
        B.mul(b);
    }else{
        B=g;
        B.mul(b);
        B.add(A);
    }

    Point t0(group);
    t0=A;
    t0.mul(b);
    string kb=H(t0);

    
    //send B
    Point t1(group),t2(group),iv(group);
    t1=B;
    t1.mul(a);

    
    
    t2=B;

    iv=A;
    iv.inv();
    t2.add(iv);

    t2.mul(a);
    string k0=H(t1);
    string k1=H(t2);

    string e[2];
    e[0]=E(k0,m[0]);
    e[1]=E(k1,m[1]);
    return D(kb,e[c]);
}

int main(){
    
    Group group(NID_secp256k1);

    string m[2];
    m[0]="hello";
    m[1]="goodbye";

    cout<<ot(m,0)<<endl;


    return 0;
}