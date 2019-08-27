#ifndef GROUP
#define GROUP
#include "ec_group/group.h"

void Group::get_generator(Point &g)
{
    EC_POINT_copy(g.p, EC_GROUP_get0_generator(ec_group));
}

void Group::init(Point &p)
{
    p.p = EC_POINT_new(ec_group);
}
void Group::add(Point &res, const Point &lhs, const Point &rhs)
{
    EC_POINT_add(ec_group, res.p, lhs.p, rhs.p, NULL);
}

void Group::inv(Point &res, const Point &p)
{
    res = p;
    EC_POINT_invert(ec_group, res.p, NULL);
}
void Group::mul(Point &res, const Point &lhs, const BigInt &m)
{
    EC_POINT_mul(ec_group, res.p, NULL, lhs.p, m.n, NULL);
}
string Group::to_hex(const Point &p) const
{
    BigInt x, y;
    EC_POINT_get_affine_coordinates_GFp(ec_group, p.p, x.n, y.n, NULL);
    return "(" + x.to_hex() + "," + y.to_hex() + ")";
}

void Group::from_hex(Point &p,const string &s) const
{
    BigInt x, y;
    for(int i=0;i<(int)s.length();i++){
        if(s[i]==','){
            x.from_hex(s.substr(1,i));
            y.from_hex(s.substr(i+1,s.length()-i-1));
        }
    }
    EC_POINT_set_affine_coordinates_GFp(ec_group,p.p,x.n,y.n,NULL);
}
#endif
