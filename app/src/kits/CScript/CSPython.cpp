// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "CSPython.h"

#ifdef WITH_PY

#include <iostream>
#include <CUtils/logger.h>

// Qt Call Python :: https://blog.csdn.net/New_codeline/article/details/123143138
// slots in python conflicts with slots in qt
#ifdef slots
#   undef slots
#   include <Python.h>
#   define slots Q_SLOTS
#else
#   include <Python.h>
#endif // slots

NS_CS_BEGIN

bool Python::InitPy()
{
    Py_Initialize();
    if (!Py_IsInitialized()) {
        PyErr_Print();
        LOGI("Can't Initialize python!");
        return false;
    }
    return true;
}

void Python::RunPyString(const std::string &str)
{
    PyRun_SimpleString(str.c_str());
}

bool Python::DelPy()
{
    Py_Finalize();
    return true;
}

NS_CS_END

#endif // WITH_PY
