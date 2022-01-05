#ifndef VIDEOMATCH_H
#define VIDEOMATCH_H

#include <QVector>
#include <QStringList>
#include <string>

class videoMatch{

    private:
        std::string time;
        QVector<std::string> passage;

    public:
        videoMatch(std::string t, QVector<std::string> p);

        // print time and matching subtitle that contained the searched term
        void printPassage(std::string vidName, QStringList* output);
};

#endif // VIDEOMATCH_H
