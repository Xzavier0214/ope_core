//
// Created by 曾鑫 on 2019/4/2.
//

#include <iostream>
#include <math.h>
#include <nlopt.hpp>
#include "core.h"
using namespace std;

void ClassicalToCartesianFunc(const double *classical, double *cartesian, double mu) {
    double a  = classical[0], e    = classical[1], i  = classical[2];
    double ap = classical[3], raan = classical[4], ta = classical[5];

    double sini = sin(i),    cosi = cos(i);
    double sina = sin(ap),   cosa = cos(ap);
    double sinr = sin(raan), cosr = cos(raan);
    double sint = sin(ta),   cost = cos(ta);

    double p  = a*(1 - e*e);
    double r  = p/(1 + e*cost);
    double sq = sqrt(mu/p);

    double rx = r*cost,   ry = r*sint;
    double vx = -sq*sint, vy = sq*(e + cost);

    double m11 = cosa*cosr - sina*sinr*cosi, m12 = sina*cosr + cosa*sinr*cosi;
    double m21 = cosa*sinr + sina*cosr*cosi, m22 = sina*sinr - cosa*cosr*cosi;
    double m31 = sina*sini,                  m32 = cosa*sini;

    cartesian[0] = rx*m11 - ry*m12;
    cartesian[1] = rx*m21 - ry*m22;
    cartesian[2] = rx*m31 + ry*m32;
    cartesian[3] = vx*m11 - vy*m12;
    cartesian[4] = vx*m21 - vy*m22;
    cartesian[5] = vx*m31 + vy*m32;
}

int main() {

    // 地球半径
    const double RE = 6378.137e3;

    // 地球引力常数
    const double MU = 3.986004418e14;

    // 归一化常数
    const double DU = RE;
    const double TU = sqrt(DU*DU*DU / MU);

    // 标准速度常量
    const double VU = DU / TU;

    // 标准加速度常量
    const double GU = DU / (TU*TU);

    // 角度与弧度转换常数
    const double DEG_TO_RAD = M_PI / 180.0;

    double tmP = 0.1*GU, tmE = 0.05*GU;

    double gKeplerP[6] = { 6578.165e3, 0, DEG_TO_RAD*30, 0, DEG_TO_RAD*10, 0 };
    double gKeplerE[6] = { 6578.165e3, 0, DEG_TO_RAD*50, 0, DEG_TO_RAD*30, DEG_TO_RAD*10 };

    double gK[13] {10, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    double gLb[13] {-10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 0};
    double gUb[13] {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    double gCartP[6], gCartE[6];
    ClassicalToCartesianFunc(gKeplerP, gCartP, MU);
    ClassicalToCartesianFunc(gKeplerE, gCartE, MU);

    Param param = {
        gCartP, gCartE, tmP, tmE, gLb, gUb, gK, DU, TU
    };

    double gOptIndividual[13];
    auto optFitness = SolveCartesian(&param, gOptIndividual, true);

    cout << optFitness << endl;

    return 0;
}
