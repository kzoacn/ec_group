#ifndef GROUP_H
#define GROUP_H

#include "openssl/ec.h"
#include "openssl/bn.h"
#include "openssl/obj_mac.h"
#include <string>
#include <cstring>
using std::string;

class Point;
class Group;
class BigInt
{
    BIGNUM *n;

public:
    BigInt()
    {
        n = BN_new();
    }
    BigInt(const BigInt &oth)
    {
        BN_copy(n, oth.n);
    }
    BigInt &operator=(const BigInt &oth)
    {
        BN_copy(n, oth.n);
        return *this;
    }
    ~BigInt()
    {
        BN_free(n);
    }
    void from_dec(const string &s)
    {

        char *p_str;
        p_str = new char[s.length() + 1];
        memcpy(p_str, s.c_str(), s.length());
        p_str[s.length()] = 0;
        BN_dec2bn(&n, p_str);
        delete[] p_str;
    }
    void from_hex(const string &s)
    {

        char *p_str;
        p_str = new char[s.length() + 1];
        memcpy(p_str, s.c_str(), s.length());
        p_str[s.length()] = 0;
        BN_hex2bn(&n, p_str);
        delete[] p_str;
    }
    string to_hex()
    {

        char *number_str = BN_bn2hex(n);
        string ans(number_str);
        OPENSSL_free(number_str);

        return ans;
    }

    BigInt &add(const BigInt &oth)
    {
        BN_add(n, n, oth.n);
        return *this;
    }
    // mod
    BigInt &mod(const BigInt &oth)
    {
        BN_mod(n, n, oth.n, NULL);
        return *this;
    }
    friend class Group;
    friend class Point;
};

class Group
{
private:
    EC_GROUP *ec_group;

public:
    Group(int nid)
    {
        ec_group = EC_GROUP_new_by_curve_name(nid);
    }
    ~Group()
    {
    }
    void get_generator(Point &g);
    void precompute()
    {
        EC_GROUP_precompute_mult(ec_group, NULL);
    }
    //precomputation table for some group element
    friend class Point;

    void init(Point &p);
    void add(Point &res, const Point &lhs, const Point &rhs);
    void inv(Point &res, const Point &p);
    void mul(Point &res, const Point &lhs, const BigInt &m);
    string to_hex(const Point &p) const;
    void from_hex(Point &p,const string &s) const;
};

class Point
{
private:
    //EC_GROUP *ec_group;
    EC_POINT *p;

public:
    Point() {p=NULL;}
    ~Point()
    {
        if(!p)return;   
        EC_POINT_free(p);
    }

    Point(const Point &oth)
    {
        EC_POINT_copy(p, oth.p);
    }
    Point &operator=(const Point &oth)
    {
        EC_POINT_copy(p, oth.p);
        return *this;
    }

    friend class Group;
};

#endif
