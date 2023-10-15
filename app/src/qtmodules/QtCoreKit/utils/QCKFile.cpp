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

#include "QCKFile.h"

#include <QDir>
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>

#include "QCKDefines.h"
#include <CUtils/CUString.h>

bool QCKFile::DirectoryCopy(const QString &srcDir, const QString &dstDir, bool coverIfExist)
{
    QDir src_dir(srcDir);
    QDir dst_dir(dstDir);
    if (!dst_dir.exists() && !dst_dir.mkpath(dst_dir.absolutePath())) {
        return false;
    }

    QFileInfoList list = src_dir.entryInfoList();
    foreach(QFileInfo item, list) {
        if (item.fileName() == "." || item.fileName() == "..") {
            continue;
        }
        
        if (item.isDir()) {
            if(!DirectoryCopy(item.filePath(), dst_dir.filePath(item.fileName()), coverIfExist)) {
                return false;
            }
        } else {
            if (coverIfExist && dst_dir.exists(item.fileName())) {
                dst_dir.remove(item.fileName());
            }
            
            if (!QFile::copy(item.filePath(), dst_dir.filePath(item.fileName()))) {
                return false;
            }
        }
    }
    
    return true;
}

bool QCKFile::DirectoryMove(const QString &srcDir, const QString &dstDir, bool coverIfExist)
{
    QDir src_dir(srcDir);
    QDir dst_dir(dstDir);
    if (!dst_dir.exists() && !dst_dir.mkpath(dst_dir.absolutePath())) {
        return false;
    }

    QFileInfoList list = src_dir.entryInfoList();
    foreach(QFileInfo item, list) {
        if (item.fileName() == "." || item.fileName() == "..") {
            continue;
        }

        if (item.isDir()) {
            if (!DirectoryMove(item.filePath(), dst_dir.filePath(item.fileName()), coverIfExist)) {
                return false;
            }
        } else {
            if (coverIfExist && dst_dir.exists(item.fileName())) {
                dst_dir.remove(item.fileName());
            }
            
            if (!QFile::copy(item.filePath(), dst_dir.filePath(item.fileName()))) {
                return false;
            }
            src_dir.remove(item.fileName());
        }
    }

    if (src_dir.isEmpty()) {
        src_dir.removeRecursively();
    }

    return true;
}

// QCKFile::filesWithFilter(".", QStringList() << "test.json", dstList)
bool QCKFile::FilesWithFilter(const QDir &srcDir, const QStringList &filters, QFileInfoList &dstList)
{
    QFileInfoList list = srcDir.entryInfoList(filters, QDir::AllDirs|QDir::Files);
    foreach(QFileInfo item, list)
    {
        if (item.fileName() == "." || item.fileName() == "..") {
            continue;
        }
        
        if (item.isDir()) {
            if (!FilesWithFilter(item.filePath(), filters, dstList)) {
                return false;
            }
        } else {
            dstList.append(item);
        }
    }
    return true;
}

bool QCKFile::FilesWithExts(const QDir &srcDir, const QStringList &exts, QFileInfoList &dstList)
{
    QFileInfoList list = srcDir.entryInfoList(QDir::AllDirs|QDir::Files);
    foreach(QFileInfo item, list)
    {
        if (item.fileName() == "." || item.fileName() == "..") {
            continue;
        }
        
        if (item.isDir()) {
            if (!FilesWithExts(item.filePath(), exts, dstList)) {
                return false;
            }
        } else {
            foreach(QString ext, exts) {
                if (item.suffix().toLower() == ext.toLower()) {
                    dstList.append(item);
                }
            }
        }
    }
    return true;
}

// e.g. QCKFile::SelectFiles(STRING("Files(*.png; *.jpg)"), true);
QStringList QCKFile::SelectFiles(const QString &filter, bool isMulti) {
    QString desktop = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    if (isMulti) {
        QStringList list = QFileDialog::getOpenFileNames(nullptr, STRING("Select File(s)"), desktop, filter);
        return list.size()>0 ? list : QStringList();
    }
    
    QString obj_path = QFileDialog::getOpenFileName(nullptr, STRING("Select File(s)"), desktop, filter);
    if (obj_path.length() > 0) {
        return QStringList() << obj_path;
    }
    
    return QStringList();
}

QStringList QCKFile::SelectDirectory(bool isMulti) {
    QString desktop = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString dir_path = QFileDialog::getExistingDirectory(nullptr, STRING("Select Directory"), desktop, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (dir_path.length() > 0) {
        return QStringList() << dir_path;
    }
    
    return QStringList();
}

QCKFile::State QCKFile::LoadFile(const QString& fileName, QByteArray &fileData)
{
    QFileInfo info(fileName);
    if (!info.isFile()) {
        return State::Err_NotFile;
    }
    
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return State::Err_FileOpen;
    }

    // fileData = file.read(file.bytesAvailable());
    fileData = file.readAll();
    file.close();
    
    if (fileData.isEmpty()) {
        return State::Err_FileEmpty;
    }
    
    return State::Succeed;
}

QCKFile::State QCKFile::LoadFileLines(const QString& fileName, QStringList& dataLines)
{
    QByteArray fileData;
    QCKFile::State st = LoadFile(fileName, fileData);
    if (State::Succeed != st) {
        return st;
    }

    // Convert fileData to dataLines
    QString qstr(fileData);
    std::vector < std::string > str_list;
    CU::String::SplitStringToVector(qstr.toStdString(), "\r\n", str_list);
    for (size_t idx = 0; idx < str_list.size(); idx++) {
        dataLines << QString::fromStdString(str_list[idx]);
    }

    return State::Succeed;
}

QCKFile::State QCKFile::LoadFile(const QString& dirPath, const QString& fileSuffix, QByteArray &fileData)
{
    QString filePath = "";
    QDir dir(dirPath);
    QFileInfoList list = dir.entryInfoList(QDir::Files);
    foreach (QFileInfo item, list) {
        if (item.absoluteFilePath().toLower().endsWith(fileSuffix.toLower())) {
            filePath = item.absoluteFilePath();
            break;
        }
    }
    
    if (filePath.isEmpty()) {
        return State::Err_NotFile;
    }
    
    return LoadFile(filePath, fileData);
}

bool QCKFile::SaveFile(const QString& fileName, const QByteArray &data)
{
    QFileInfo info(fileName);
    if (!info.dir().exists()) {
        bool ret = info.dir().mkpath(info.dir().absolutePath());
        if (!ret) {
//#ifdef DEBUG
            QString tips = "mkpath : " + info.dir().absolutePath() + " failed !";
            QMessageBox::warning(NULL, "SaveFile", tips);
//#endif
            return false;
        }
    }
    
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream outStream(&file);
        outStream.writeRawData(data.data(), data.size());
        file.close();
#ifdef DEBUG
        QString tips = "Write File : " + fileName + " succeed !";
        QMessageBox::information(NULL, "SaveFile", tips);
#endif
        return true;
    }

//#ifdef DEBUG
    QString tips = "Open : " + fileName + " failed !";
    QMessageBox::warning(NULL, "SaveFile", tips);
//#endif
    return false;
}
