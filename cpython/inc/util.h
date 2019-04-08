//
// Created by zx on 19-4-8.
//

#ifndef OPE_CORE_UTIL_H
#define OPE_CORE_UTIL_H

#include <Python.h>

bool PyTupleToGDouble(PyObject *pTuple, double gDouble[], size_t size);

void GDoubleToPyTuple(double gDouble[], PyObject *pTuple, size_t size);

#endif //OPE_CORE_UTIL_H
