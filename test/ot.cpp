#include <iostream>
#include "ec_group/group.h"

using namespace std;


//stupid hash
string H(const Group &G,const Point &p){
    return G.to_hex(p);
}

string E(string key,string m){
    for(int i=0;i<(int)m.length();i++)
        m[i]^=key[i];
    return m;
}
string D(string key,string c){
    for(int i=0;i<(int)c.length();i++)
        c[i]^=key[i];
    return c;
}



string ot(string m[],int c){
    BigInt a,b;
    a.from_dec("324123");
    b.from_dec("4134213");
    //stupid random
    
    Group G(NID_secp256k1);


    Point A,B;
    Point g;
    G.init(A);
    G.init(B);
    G.init(g);
    G.get_generator(g);


    A=g;

    G.mul(A,A,a);
    //send A
    if(c==0){
        B=g;
        G.mul(B,B,b);
    }else{
        B=g;
        G.mul(B,B,b);
        G.add(B,B,A);
    }

    Point t0;
    G.init(t0);
    t0=A;
    G.mul(t0,t0,b);
    string kb=H(G,t0);

    
    //send B
    Point t1,t2,iv;
    G.init(t1);
    G.init(t2);
    G.init(iv);
    t1=B;
    G.mul(t1,t1,a);

    
    
    t2=B;

    iv=A;
    G.inv(iv,iv);
    G.add(t2,t2,iv);

    G.mul(t2,t2,a);
    string k0=H(G,t1);
    string k1=H(G,t2);

    string e[2];
    e[0]=E(k0,m[0]);
    e[1]=E(k1,m[1]);
    return D(kb,e[c]);
}

int main(){
    

    string m[2];
    m[0]="hello";
    m[1]="goodbye";

    cout<<ot(m,1)<<endl;


    return 0;
}
