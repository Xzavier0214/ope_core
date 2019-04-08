//
// Created by zx on 19-4-4.
//

#include "cpython_core.h"
#include "core.h"
#include "util.h"

PyObject* spherical_state_fcn(PyObject *self, PyObject *args) {
    double gState[SPHERICAL_STATE_SIZE], gControl[SPHERICAL_CONTROL_SIZE], tm, mu;
    double gDotState[SPHERICAL_STATE_SIZE];
    PyObject *pState, *pControl;

    if (!PyArg_ParseTuple(args, "OOdd",
            &pState,
            &pControl,
            &tm,
            &mu))
        return NULL;

    if (!PyTupleToGDouble(pState, gState, SPHERICAL_STATE_SIZE))
        return NULL;

    if (PyTuple_Check(pControl)) {
        PyTupleToGDouble(pControl, gControl, SPHERICAL_CONTROL_SIZE);
        SphericalStateFcn(gState, gControl, tm, mu, gDotState);
    }
    else if (pControl == Py_None) {
        SphericalStateFcn(gState, nullptr, tm, mu, gDotState);
    }

    auto returnTuple = PyTuple_New(SPHERICAL_STATE_SIZE);
    GDoubleToPyTuple(gDotState, returnTuple, SPHERICAL_STATE_SIZE);
    return returnTuple;
}

PyObject* spherical_costate_fcn(PyObject *self, PyObject *args) {
    double gState[SPHERICAL_STATE_SIZE], gCostate[SPHERICAL_STATE_SIZE], gControl[SPHERICAL_CONTROL_SIZE], tm, mu;
    double gDotCostate[6];
    PyObject *pState, *pCostate, *pControl;

    if (!PyArg_ParseTuple(args, "OOOdd",
            &pState,
            &pCostate,
            &pControl,
            &tm,
            &mu))
        return NULL;

    if (!PyTupleToGDouble(pState, gState, SPHERICAL_STATE_SIZE))
        return NULL;

    if (!PyTupleToGDouble(pCostate, gCostate, SPHERICAL_STATE_SIZE))
        return NULL;

    if (!PyTupleToGDouble(pControl, gControl, SPHERICAL_CONTROL_SIZE))
        return NULL;

    SphericalCostateFcn(gState, gCostate, gControl, tm, mu, gDotCostate);

    auto returnTuple = PyTuple_New(SPHERICAL_STATE_SIZE);
    GDoubleToPyTuple(gDotCostate, returnTuple, SPHERICAL_STATE_SIZE);
    return returnTuple;
}

PyObject* spherical_control_fcn(PyObject *self, PyObject *args) {
    double gState[SPHERICAL_STATE_SIZE], gCostate[SPHERICAL_STATE_SIZE];
    int flag;
    PyObject *pState, *pCostate;

    if (!PyArg_ParseTuple(args, "OOi",
                          &pState,
                          &pCostate,
                          &flag))
        return NULL;

    if (!PyTupleToGDouble(pState, gState, SPHERICAL_STATE_SIZE))
        return NULL;

    if (!PyTupleToGDouble(pCostate, gCostate, SPHERICAL_STATE_SIZE))
        return NULL;

    double gControl[SPHERICAL_CONTROL_SIZE];
    SphericalControlFcn(gState, gCostate, flag, gControl);

    auto returnTuple = PyTuple_New(SPHERICAL_CONTROL_SIZE);
    GDoubleToPyTuple(gControl, returnTuple, SPHERICAL_CONTROL_SIZE);
    return returnTuple;
}

PyObject *spherical_hamilton_fcn(PyObject *self, PyObject *args) {
    double gState[SPHERICAL_STATE_SIZE], gCostate[SPHERICAL_STATE_SIZE], gControl[SPHERICAL_CONTROL_SIZE], tm, mu;
    PyObject *pState, *pCostate, *pControl;

    if (!PyArg_ParseTuple(args, "OOOdd",
                          &pState,
                          &pCostate,
                          &pControl,
                          &tm,
                          &mu))
        return NULL;

    if (!PyTupleToGDouble(pState, gState, SPHERICAL_STATE_SIZE))
        return NULL;

    if (!PyTupleToGDouble(pCostate, gCostate, SPHERICAL_STATE_SIZE))
        return NULL;

    if (!PyTupleToGDouble(pControl, gControl, SPHERICAL_CONTROL_SIZE))
        return NULL;

    double hamilton = SphericalHamiltonFcn(gState, gCostate, gControl, tm, mu);
    return PyFloat_FromDouble(hamilton);
}

PyObject *spherical_ext_state_fcn(PyObject *self, PyObject *args) {
    double gExtState[SPHERICAL_EXT_STATE_SIZE], tmP, tmE, mu;
    PyObject *pExtState;

    if (!PyArg_ParseTuple(args, "Oddd",
                          &pExtState,
                          &tmP,
                          &tmE,
                          &mu))
        return NULL;

    if (!PyTupleToGDouble(pExtState, gExtState, SPHERICAL_EXT_STATE_SIZE))
        return NULL;

    double gDotExtState[SPHERICAL_EXT_STATE_SIZE];
    SphericalExtStateFcn(gExtState, tmP, tmE, mu, gDotExtState);

    auto returnTuple = PyTuple_New(SPHERICAL_EXT_STATE_SIZE);
    GDoubleToPyTuple(gDotExtState, returnTuple, SPHERICAL_EXT_STATE_SIZE);
    return returnTuple;
}

PyObject *spherical_boundary_fcn(PyObject *self, PyObject *args) {
    double gExtState[SPHERICAL_EXT_STATE_SIZE], tmP, tmE, mu;
    PyObject *pExtState;

    if (!PyArg_ParseTuple(args, "Oddd",
                          &pExtState,
                          &tmP,
                          &tmE,
                          &mu))
        return NULL;

    if (!PyTupleToGDouble(pExtState, gExtState, SPHERICAL_EXT_STATE_SIZE))
        return NULL;

    double gBoundary[SPHERICAL_BOUNDARY_SIZE];
    SphericalBoundaryFcn(gExtState, tmP, tmE, mu, gBoundary);

    auto returnTuple = PyTuple_New(SPHERICAL_BOUNDARY_SIZE);
    GDoubleToPyTuple(gBoundary, returnTuple, SPHERICAL_BOUNDARY_SIZE);
    return returnTuple;
}

PyObject *spherical_fitness_fcn(PyObject *self, PyObject *args) {
    double gIndividual[SPHERICAL_INDIVIDUAL_SIZE], gK[SPHERICAL_BOUNDARY_SIZE];
    double gStateP0[SPHERICAL_STATE_SIZE], gStateE0[SPHERICAL_STATE_SIZE];
    double tmP, tmE, du, tu;
    PyObject *pIndividual, *pK, *pStateP0, *pStateE0;

    if (!PyArg_ParseTuple(args, "OOOOdddd",
                          &pIndividual,
                          &pK,
                          &pStateP0,
                          &pStateE0,
                          &tmP,
                          &tmE,
                          &du,
                          &tu))
        return NULL;

    if (!PyTupleToGDouble(pIndividual, gIndividual, SPHERICAL_INDIVIDUAL_SIZE))
        return NULL;

    if (!PyTupleToGDouble(pK, gK, SPHERICAL_BOUNDARY_SIZE))
        return NULL;

    if (!PyTupleToGDouble(pStateP0, gStateP0, SPHERICAL_STATE_SIZE))
        return NULL;

    if (!PyTupleToGDouble(pStateE0, gStateE0, SPHERICAL_STATE_SIZE))
        return NULL;

    double fitness = SphericalFitnessFcn(gIndividual, gK, gStateP0, gStateE0, tmP, tmE, du, tu);
    return PyFloat_FromDouble(fitness);
}

PyObject *solve_spherical_fcn(PyObject *self, PyObject *args) {
    double gInitialStateP[SPHERICAL_STATE_SIZE], gInitialStateE[SPHERICAL_STATE_SIZE];
    double gLb[SPHERICAL_INDIVIDUAL_SIZE], gUb[SPHERICAL_INDIVIDUAL_SIZE], gK[SPHERICAL_BOUNDARY_SIZE];
    double tmP, tmE, dU, tU;
    bool printProcess;
    PyObject *pInitialStateP, *pInitialStateE;
    PyObject *pLb, *pUb, *pK;

    if (!PyArg_ParseTuple(args, "OOddOOOddb",
                          &pInitialStateP, &pInitialStateE,
                          &tmP, &tmE,
                          &pLb, &pUb,
                          &pK, &dU, &tU,
                          &printProcess))
        return NULL;

    PyTupleToGDouble(pInitialStateP, gInitialStateP, SPHERICAL_STATE_SIZE);
    PyTupleToGDouble(pInitialStateE, gInitialStateE, SPHERICAL_STATE_SIZE);
    PyTupleToGDouble(pLb, gLb, SPHERICAL_INDIVIDUAL_SIZE);
    PyTupleToGDouble(pUb, gUb, SPHERICAL_INDIVIDUAL_SIZE);
    PyTupleToGDouble(pK, gK, SPHERICAL_BOUNDARY_SIZE);

    Param param = {
        gInitialStateP, gInitialStateE, tmP, tmE, gLb, gUb, gK, dU, tU
    };
    double gOptIndividual[SPHERICAL_INDIVIDUAL_SIZE];
    auto optFitness = SolveSpherical(&param, gOptIndividual, printProcess);

    auto pOptIndividual = PyTuple_New(SPHERICAL_INDIVIDUAL_SIZE);
    GDoubleToPyTuple(gOptIndividual, pOptIndividual, SPHERICAL_INDIVIDUAL_SIZE);

    return Py_BuildValue("(dO)", pOptIndividual, optFitness);
}
