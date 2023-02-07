#ifndef QCK_CMD_H
#define QCK_CMD_H

#define QCK_CMD_TIME_LIMIT 500000

class QString;
class QStringList;
class QByteArray;

extern const QString PY_BIN;

class QCKCmd
{
public:
    /// @param  output  if return true, output is cmd success info; if return false,  output is cmd error info.
    static bool ExecCmd(const QString &toolPath, const QStringList &options, QByteArray &output);

    static QString GetSoftPath(const QString &name);
};

#endif /* QCK_CMD_H */
