#ifndef QCK_CMD_H
#define QCK_CMD_H

class QString;
class QStringList;
class QByteArray;

class QCKCmd
{
public:
    /// @param  output  if return true, output is cmd success info; if return false,  output is cmd error info.
    static bool ExecCmd(const QString &toolPath, const QStringList &options, QByteArray &output);

};

#endif /* QCK_CMD_H */
