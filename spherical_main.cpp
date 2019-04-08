//
// Created by 曾鑫 on 2019/4/2.
//

#include <iostream>
#include <math.h>
#include <nlopt.hpp>
#include "core.h"
using namespace std;

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

    double gSphereP[6] = { 6578.165e3, 7.784e3, 0, DEG_TO_RAD*10.0, 0,              DEG_TO_RAD*30.0 };
    double gSphereE[6] = { 6578.165e3, 7.784e3, 0, DEG_TO_RAD*36.5, DEG_TO_RAD*7.6, DEG_TO_RAD*49.6 };

    double gCostate[6] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

    double gK[13] {1, DU, DU, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    double gLb[13] {-5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, 0};
    double gUb[13] {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};

    Param param = {
            gSphereP, gSphereE, tmP, tmE, gLb, gUb, gK, DU, TU
    };

//    double gOptIndividual[12];
//    auto optFitness = SolveSpherical(&param, gOptIndividual, true);
//
//    cout << optFitness << endl;

//    double gDotState[6], gDotCostate[6];
//    double gControl[2] = {0, 0};
//    SphericalStateFcn(gSphereP, gControl, tmP, MU, gDotState);
//    for (double i : gDotState)
//        cout << i << ", ";
//    cout << endl;
//
//    SphericalStateFcn(gSphereP, nullptr, tmP, MU, gDotState);
//    for (double i : gDotState)
//        cout << i << ", ";
//    cout << endl;
//
//    SphericalCostateFcn(gSphereP, gCostate, gControl, tmP, MU, gDotCostate);
//    for (double i : gDotCostate)
//        cout << i << ", ";
//    cout << endl;
//
//    SphericalControlFcn(gSphereP, gCostate, 1, gControl);
//    for (double i : gControl)
//        cout << i << ", ";
//    cout << endl;
//
//    SphericalControlFcn(gSphereP, gCostate, -1, gControl);
//    for (double i : gControl)
//        cout << i << ", ";
//    cout << endl;
//
//    gControl[0] = 0;
//    gControl[1] = 0;
//    auto hamilton = SphericalHamiltonFcn(gSphereP, gCostate, gControl, tmP, MU);
//    cout << hamilton << endl;
//
//    double gExtState[24], gDotExtState[24];
//    memcpy(gExtState, gSphereP, 6*sizeof(double));
//    memcpy(gExtState + 6, gSphereE, 6*sizeof(double));
//    memcpy(gExtState + 12, gCostate, 6*sizeof(double));
//    memcpy(gExtState + 18, gCostate, 6*sizeof(double));
//    SphericalExtStateFcn(gExtState, tmP, tmE, MU, gDotExtState);
//    for (double i : gDotExtState)
//        cout << i << ", ";
//    cout << endl;
//
//    double gBoundary[13];
//    SphericalBoundaryFcn(gExtState, tmP, tmE, MU, gBoundary);
//    for (double i : gBoundary)
//        cout << i << ", ";
//    cout << endl;
//
    double gIndividual[12] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    auto fitness = SphericalFitnessFcn(gIndividual, gK, gSphereP, gSphereE, tmP, tmE, DU, TU);
    cout << fitness << endl;

    return 0;
}
