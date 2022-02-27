#include "video.h"

#include <iostream>

using std::cout;
using std::endl;

video::video(std::string n, QVector<videoMatch> v) {

    vidName = n;
    vidMatches = v;
}

std::string video::getName() {

    return vidName;
}

int video::getMatchesInVideo() {

    return vidMatches.size();
}

void video::printVideoMatches(QStringList* gOutput) {

    int current = 1;
    int total = getMatchesInVideo();

    // calls the method that lists out the times and passages
    for (auto x: vidMatches) {

        gOutput->append(QString ("%1/%2 %3").arg(current).arg(total).arg(QString::fromStdString(getName())));
        x.printPassage(vidName, gOutput);
        current++;
    }
}
