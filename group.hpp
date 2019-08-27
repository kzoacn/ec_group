#ifndef GROUP
#define GROUP

#include "openssl/ec.h"
#include "openssl/bn.h"
#include "openssl/obj_mac.h"
#include <string>
#include <cstring>
using std::string;

class Point;
class Group;
class BigInt{   
    BIGNUM *n;
public:
    BigInt(){
        n=BN_new();
    }
    BigInt(const BigInt &oth){
        BN_copy(n,oth.n);
    }
    BigInt& operator=(const BigInt &oth){
        BN_copy(n,oth.n);
        return *this;
    }
    ~BigInt(){
        BN_free(n);
    }
    void from_dec(const string &s){
                    
        char *p_str;
        p_str=new char[s.length()+1];
        memcpy(p_str,s.c_str(),s.length());
        p_str[s.length()]=0;
        BN_dec2bn(&n, p_str);
        delete[] p_str;
    }
    string to_hex(){

        char * number_str = BN_bn2hex(n);
        string ans(number_str);
        OPENSSL_free(number_str);

        return ans;
    }

    BigInt& add(const BigInt &oth){
        BN_add(n,n,oth.n);
        return *this;
    }
    friend class Group;
    friend class Point;
    // mod
};


class Group{
private:
    EC_GROUP *ec_group;
public:
    Group(int nid){
        ec_group=EC_GROUP_new_by_curve_name(nid);
    }
    ~Group(){

    }
    void get_generator(Point& g);

    //precomputation table for some group element
    friend class Point;
};


class Point{
private:
    EC_GROUP *ec_group;
    EC_POINT *p;
public:
    Point(Group group){
        ec_group=group.ec_group;
        p=EC_POINT_new(ec_group);
    }
    ~Point(){
        EC_POINT_free(p);
    }
    
    Point(const Point &oth){
        //ec_group=oth.ec_group;
        EC_POINT_copy(p,oth.p);
    }
    Point& operator=(const Point &oth){
        //ec_group=oth.ec_group;
        //p=oth.p;
        EC_POINT_copy(p,oth.p);
        return *this;
    }


    Point& add(const Point &oth){
        EC_POINT_add(ec_group,p,p,oth.p,NULL);
        return *this;
    }

    Point& inv(){
        EC_POINT_invert(ec_group,p,NULL);
        return *this;
    }
    Point& mul(const BigInt &m){
        EC_POINT_mul(ec_group,p,NULL,p,m.n,NULL);
        return *this;
    }

    string to_hex()const{
        BigInt x,y;
        EC_POINT_get_affine_coordinates_GFp(ec_group,p,x.n,y.n,NULL);
        return "("+x.to_hex()+","+y.to_hex()+")";
    }

    friend class Group;
}; 


void Group::get_generator(Point& g){
    EC_POINT_copy(g.p,EC_GROUP_get0_generator(ec_group));
}    

#endif
