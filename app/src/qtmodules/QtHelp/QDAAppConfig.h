// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_APP_CONFIG_H
#define QDA_APP_CONFIG_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

class QDAAppConfig
{
public:
    static QDAAppConfig* GetInstance();

    explicit QDAAppConfig();
    ~QDAAppConfig();

    void LoadConfig();

};

#endif // QDA_APP_CONFIG_H
