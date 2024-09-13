// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

// https://blog.csdn.net/ai_admin/article/details/119784756

#ifndef CS_PYTHON_H
#define CS_PYTHON_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <string>

#include "CScriptDef.h"

NS_CS_BEGIN
namespace Python {

    bool InitPy();
    void RunPyString(const std::string& str);
    bool DelPy();

} //namespace Python
NS_CS_END

#endif // CS_PYTHON_H
