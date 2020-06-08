#include <iostream>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QCommandLineParser>
#include <QCoreApplication>

int main(int argc, char *argv[]) {

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("jsonDeployer");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Naostage Json File Deployer");
    parser.addHelpOption();
    QCommandLineOption inputOption(QStringList() << "i" << "input",
                                             QCoreApplication::translate("main", "Source Json file to copy"),
                                             QCoreApplication::translate("main", "Json file"));
    parser.addOption(inputOption);
    QCommandLineOption destinationOption(QStringList() << "d" << "destination",
                                             QCoreApplication::translate("main", "Target directory where json file will be copied"),
                                             QCoreApplication::translate("main", "Target directory"));
    parser.addOption(destinationOption);
    QCommandLineOption forceOption(QStringList() << "f" << "force",
                                   QCoreApplication::translate("main", "Overwrite existing files."));
    parser.addOption(forceOption);

    parser.process(app);

    QString sourceFileName = parser.value(inputOption);
    QString targetDir = parser.value(destinationOption);
    bool force = parser.isSet(forceOption);

    // Checking if source fil exist
    if (!QFile::exists(sourceFileName))
    {
        qDebug() << "Source File : " << sourceFileName << "doesn't exist.";
        return -1;
    }

    // Extracting filename from path of the source file
    QFileInfo fileToCopyInfo(sourceFileName);
    QString fileName(fileToCopyInfo.fileName());
    qDebug() << "Source File to copy : " << fileName;

    // Creating a QDir var for target directory
    QDir targetDirectory(targetDir);

    // Checking exception cases
    if(!targetDirectory.exists())
    {
        qDebug() << "Error : Target Directory " << targetDir << " doesn't exist.";
        return -1;
    }
    if(targetDirectory.isEmpty(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        qDebug() << "Target Directory " << targetDir << " is empty.";
        return 0;
    }

    // Iterating recursively in target directory
    QStringList directoryList = targetDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < directoryList.size(); ++i)
    {
        const QString& actualDirName = directoryList.at(i);
        //QDir actualDirectory(actualDirName);
        qDebug() << "Target Directory N°" << i << " : " << actualDirName;
        QString actualTargetFileName(targetDir + "/" + actualDirName + "/" + fileName);
        bool exist = false;
        if (QFile::exists(actualTargetFileName))
        {
            qDebug() << "     In Directory N°" << i << " : " << actualDirName << " the file " << fileName << "already exist.";
            if(force)
            {
                qDebug() << "     You have passed the force Option so it will be overwrite";
                QFile::remove(actualTargetFileName);
            }
            exist = true;
        }
        if(exist && !force)
        {
            qDebug() << "     You didn't passed the force option so the file isn't overwrited and so not copied.";
        }else //(!exist || force)
        {
            QFile::copy(sourceFileName, actualTargetFileName);
        }
    }
    return 0;
}
