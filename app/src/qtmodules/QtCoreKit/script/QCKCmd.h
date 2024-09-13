// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QCK_CMD_H
#define QCK_CMD_H

#define QCK_CMD_TIME_LIMIT 500000

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

class QString;
class QStringList;
class QByteArray;

extern const QString CMD_BIN;
extern const QString CMD_EXT;

class QCKCmd
{
public:
    /// @param  output  if return true, output is cmd success info; if return false,  output is cmd error info.
    static bool ExecCmd(const QString &toolPath, const QStringList &options, QByteArray &output);
    
    static QString GetSoftPath(const QString &name);
    static QString GetPyBin();
};

#endif /* QCK_CMD_H */
