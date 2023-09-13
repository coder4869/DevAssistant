// MIT License
//
// Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "CSPython.h"

#include <iostream>

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
        std::cout << "Can't Initialize python!\n" ;
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
