// https://blog.csdn.net/delphigbg/article/details/127781766

#include "QCKCmd.h"

#include <QDebug>
#include <QString>
#include <QProcess>
#include <QDir>

#include <QMessageBox>

#ifdef OSX
//    const QString CMD_BIN = "pkexec /bin/bash";
    const QString CMD_BIN = "/bin/bash";
    const QString CMD_EXT = ".sh";
#elif WIN
//    const QString CMD_BIN = "pkexec cmd.exe";
    const QString CMD_BIN = "cmd.exe";
    const QString CMD_EXT = ".bat";
#endif

static QString PY_BIN = "";

/// @param  output  if return true, output is cmd success info; if return false,  output is cmd error info.
bool QCKCmd::ExecCmd(const QString &toolPath, const QStringList &options, QByteArray &output)
{
    bool is_succeed = false;
    
    QProcess *process = new QProcess();
    process->setProcessChannelMode(QProcess::MergedChannels);
    // QProcess::execute() == QProcess::start() + QProcess::waitforFinished() 是阻塞的
    if (options.size() > 0) {
        process->start(toolPath, options);
    } else {
        process->start(toolPath);
    }
    process->waitForStarted();
    bool is_finish = process->waitForFinished(QCK_CMD_TIME_LIMIT);
//    process->waitForReadyRead();
    
    if (process->exitCode() != 0) {
        output = process->readAllStandardError();
        is_succeed = false;
    } else {
        output = process->readAllStandardOutput();
        is_succeed = true;
    }
    
    if (is_finish) {
        process->close(); // required: QProcess instance by new, will not exit normally.
        delete process;
        process = nullptr;
    }
    
    return is_succeed;
}

QString QCKCmd::GetSoftPath(const QString &name)
{
    QByteArray output;
#ifdef OSX
    bool ret = ExecCmd(CMD_BIN, QStringList() << "-c" << "whereis " + name, output);
#elif WIN
    bool ret = ExecCmd(CMD_BIN, QStringList() << "/c" << "where " + name, output);
#endif
    
//    qDebug() << output << endl;
    if (!ret) {
        QMessageBox::critical(NULL, "Check" + name , output.data());
        return QString();
    }
    QString cmd = QString::fromUtf8(output);
    
#ifdef OSX
    QStringList list = cmd.split(" ");
    qDebug() << list << endl;
    return list[1];
#elif WIN
    QStringList list = cmd.split("\r\n");
    qDebug() << list << endl;
    return list[0];
#endif
}

QString QCKCmd::GetPyBin()
{
    if (PY_BIN.isEmpty()) {
#ifdef OSX
        PY_BIN = GetSoftPath("python3") + " ";
#elif WIN
        PY_BIN = GetSoftPath("python") + " ";
#endif
    }
    return PY_BIN;
}

