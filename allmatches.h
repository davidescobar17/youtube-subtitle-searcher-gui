#ifndef ALLMATCHES_H
#define ALLMATCHES_H

#include "video.h"

#include <QVector>
#include <QStringList>
#include <string>

class allMatches{

    private:
        QVector<video> videos;
        int totalVideos;
        int totalMatches;

    public:
        allMatches();

        // reset the member variables
        void reset();

        // add a video that contains the searched term
        void addVideo(video v);

        // prints all the results
        void listAllResults(QStringList* gOutput);

        int getTotalVideos();

        int getTotalMatches();
};

#endif // ALLMATCHES_H
