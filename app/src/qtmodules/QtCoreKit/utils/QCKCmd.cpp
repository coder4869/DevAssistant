#include "QCKCmd.h"

#include <QDebug>
#include <QString>
#include <QProcess>
#include <QDir>
#include <QCoreApplication>

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
    process->waitForFinished(500000);
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
        process->close(); // 需要 new 的 QProcess 否则不会正常退出
        delete process;
        process = nullptr;
    }
    
    return is_succeed;
}
