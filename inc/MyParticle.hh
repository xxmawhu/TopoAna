/* ====================================================
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : MyParticle.hh
#   Create Time   : 2020-01-08 13:05
#   Last Modified : 2020-01-08 13:05
#   Describe      :
#
# ====================================================*/
#ifndef MyParticle_HH
#define MyParticle_HH
#include <iostream>
using std::string;

struct MyParticle {
    std::string col1;
    std::string col2;
    std::string ParType;
    std::string ParName;
    int ParId;
    double ParMass;
    double ParWidth;
    double ParDm;
    int Par3Charge;
    int Par2Spin;
    double ParLifeTime;
    int ParLundKC;
};
#endif
