// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QCK_FILE_H
#define QCK_FILE_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QString>
#include <QFileInfo>

#include "../QtCoreKitDef.h"

// File Write
// https://blog.csdn.net/kllo__/article/details/120176545
// https://blog.csdn.net/xiao123456bin/article/details/123135669
// JSON
// https://blog.csdn.net/qq_45662588/article/details/118882717
// https://blog.51cto.com/dlican/3740655
// https://www.csdn.net/tags/NtDaEgzsMjgxNzItYmxvZwO0O0OO0O0O.html
// https://blog.csdn.net/dengjin20104042056/article/details/102747097
// https://blog.csdn.net/dengjin20104042056/article/details/102747691

//class QCK_CLASS QCKFile
class QCKFile 
{
public:
    enum class State {
        Succeed,

        Err_OOM,
        Err_NotFile,
        Err_FileOpen,
        Err_FileEmpty
    };
    
    static bool DirectoryCopy(const QString &srcDir, const QString &dstDir, bool coverIfExist);
    static bool DirectoryMove(const QString &srcDir, const QString &dstDir, bool coverIfExist);

    static bool FilesWithFilter(const QDir &srcDir, const QStringList &filters, QFileInfoList &dstList);
    static bool FilesWithExts(const QDir &srcDir, const QStringList &exts, QFileInfoList &dstList);

    static QStringList SelectFiles(const QString &filter, bool isMulti = true);
    static QStringList SelectDirectory(bool isMulti = true);
    
    static State LoadFile(const QString& fileName, QByteArray &fileData);
    static State LoadFileLines(const QString& fileName, QStringList& dataLines);
    static State LoadFile(const QString& dirPath, const QString& fileSuffix, QByteArray &fileData);
    static bool SaveFile(const QString& fileName, const QByteArray& data);
};

#endif /* QCK_FILE_H */
