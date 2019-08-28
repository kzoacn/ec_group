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
char* Group::to_hex(const Point &p) const
{
    BigInt x, y;
    EC_POINT_get_affine_coordinates_GFp(ec_group, p.p, x.n, y.n, NULL);
    char *sx,*sy;
    sx=x.to_hex();
    sy=y.to_hex();
    int len=3+strlen(sx)+strlen(sy);
    char *res=new char[len+1];
    memset(res,0,len+1);
    strcat(res,"(");
    strcat(res,sx);
    strcat(res,",");
    strcat(res,sy);
    strcat(res,")");
    return res;
}

void Group::from_hex(Point &p,const char *s) const
{
    BigInt x, y;
    int len=strlen(s);
    char *t=new char[len+1];
    memset(t,0,len+1);
    t[len]=0;
    strcpy(t,s);
    for(int i=0;i<len;i++){
        if(s[i]==','){
            t[0]=0;
            t[i]=0;
            t[len-1]=0;
            x.from_hex(t+1);
            y.from_hex(t+i+1);
        }
    }
    EC_POINT_set_affine_coordinates_GFp(ec_group,p.p,x.n,y.n,NULL);
}
#endif
