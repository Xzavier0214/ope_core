//
// Created by zx on 19-4-8.
//

#include "util.h"

bool PyTupleToGDouble(PyObject *pTuple, double gDouble[], size_t size) {
    if (!PyTuple_Check(pTuple)) return false;
    for (int i = 0; i < size; i++)
        gDouble[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(pTuple, i));
    return true;
}

void GDoubleToPyTuple(double gDouble[], PyObject *pTuple, size_t size) {
    for (int i = 0; i < size; i++)
        PyTuple_SetItem(pTuple, i, PyFloat_FromDouble(gDouble[i]));
}