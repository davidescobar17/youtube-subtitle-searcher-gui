#ifndef VIDEO_H
#define VIDEO_H

#include <QVector>
#include <string>
#include "videomatch.h"

class video{

    private:
        std::string vidName;
        QVector<videoMatch> vidMatches;

    public:
        video(std::string n, QVector<videoMatch> v);

        std::string getName();

        int getMatchesInVideo();

        // print the details of the subtitles that contained the searched term
        void printVideoMatches(QStringList* gOutput);
};

#endif // VIDEO_H
