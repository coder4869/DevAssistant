// https://blog.csdn.net/delphigbg/article/details/127781766

#include "QCKCmd.h"

#include <QDebug>
#include <QString>
#include <QProcess>
#include <QDir>
#include <QCoreApplication>

#ifdef OSX
    const QString PY_BIN = "/usr/bin/python3 ";
#elif WIN
    const QString PY_BIN = "C:/python/python.exe ";
#endif

/// @param  output  if return true, output is cmd success info; if return false,  output is cmd error info.
bool QCKCmd::ExecCmd(const QString &toolPath, const QStringList &options, QByteArray &output)
{
    bool is_succeed = false;
    
    QProcess *process = new QProcess();
    // QProcess::execute() == QProcess::start() + QProcess::waitforFinished() 是阻塞的
    if (options.size() > 0) {
        process->start(toolPath, options);
    } else {
        process->start(toolPath);
    }
    process->waitForFinished(QCK_CMD_TIME_LIMIT);
//    process->waitForReadyRead();
    
    QByteArray qby_error = process->readAllStandardError();
    if (qby_error.size() > 0) {
        output = qby_error;
        is_succeed = false;
    } else {
        output = process->readAllStandardOutput();
        is_succeed = true;
    }

    if (process != nullptr) {
        process->close(); // required: QProcess instance by new, will not exit normally.
        delete process;
        process = nullptr;
    }
    
    return is_succeed;
}

QString QCKCmd::GetSoftPath(const QString &name)
{
    QStringList options;
    QByteArray output;
#ifdef OSX
    // pkexec open root authority
    QString cmd = "/bin/bash";
//    QString cmd = "pkexec /bin/bash where " + name;
#elif WIN
    QString cmd = "cmd.exe";
#endif
    options << "-c";
    options << "which " + name;
    bool ret = ExecCmd(cmd, options, output);
    qDebug() << cmd << "\n" << output.data() << endl;
    if (!ret) {
//        qDebug() << cmd << "\n" << output.data() << endl;
        return "";
    }
    return output;
}
