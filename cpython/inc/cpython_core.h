//
// Created by zx on 19-4-4.
//

#ifndef OPE_CORE_CPYTHON_CORE_H
#define OPE_CORE_CPYTHON_CORE_H

#include <Python.h>

//////////////////////////球坐标系//////////////////////////

//  球坐标系状态微分方程
PyObject* spherical_state_fcn(PyObject *self, PyObject *args);

//  球坐标系协态微分方程
PyObject* spherical_costate_fcn(PyObject *self, PyObject *args);

//  球坐标系控制变量函数
PyObject* spherical_control_fcn(PyObject *self, PyObject *args);

//  球坐标系哈密顿函数
PyObject* spherical_hamilton_fcn(PyObject *self, PyObject *args);

//  球坐标系扩展状态微分方程
PyObject* spherical_ext_state_fcn(PyObject *self, PyObject *args);

//  球坐标系边界条件
PyObject* spherical_boundary_fcn(PyObject *self, PyObject *args);

//  球坐标系适应度函数
PyObject* spherical_fitness_fcn(PyObject *self, PyObject *args);

//  求解球坐标系
PyObject* solve_spherical_fcn(PyObject *self, PyObject *args);

#endif //OPE_CORE_CPYTHON_CORE_H
