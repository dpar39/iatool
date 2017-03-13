#include "testhelpers.h"
#include <QDir>
#include <QFile>
#include <QApplication>

static QString g_testExePath;

QString TestHelpers::resolveFullPath(const QString &relFileName)
{
    auto currentPath = QDir(g_testExePath);
    while ( currentPath.cdUp() )
    {
        auto testPath = currentPath.filePath(relFileName);
        QFile file(testPath);
        if (file.exists())
        {
            return testPath;
        }
    }
    return QString();
}

void TestHelpers::initTestHelpers(const QString &testExePath)
{
    g_testExePath = testExePath;
}
