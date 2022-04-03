#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include "allmatches.h"

#include <QObject>
#include <QThread>
#include <string>
#include <vector>

class SearchThread : public QThread
{
    Q_OBJECT

public:
    void search();

    // search in subtitle file for the target
    void parseFile(std::string file, std::string target);

    void setToFind(std::string toFind);

    void setTermInTitle(std::string termInTitle);

    void setFiles(QVector<std::string> inputFiles);

    void setResults(allMatches* results);

    SearchThread();

signals:

    void percentageUpdated(int percent);

    void resultReady(QStringList result);

protected:
    void run();

private:
    std::string toFind;
    std::string termInTitle;
    QVector<std::string> inputFiles;
    allMatches* results;
    QStringList* gOutput = new QStringList();
};

#endif // SEARCHTHREAD_H
