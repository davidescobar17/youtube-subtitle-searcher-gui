#include "allmatches.h"
#include "utility.h"

#include <iostream>

using std::cout;
using std::endl;

allMatches::allMatches() {

    totalMatches = 0;
    totalVideos = 0;
}

void allMatches::reset() {

    videos.clear();
    totalVideos = 0;
    totalMatches = 0;
}

void allMatches::addVideo(video v) {

    videos.push_back(v);
    totalVideos++;
    totalMatches = totalMatches + v.getMatchesInVideo();
}

void allMatches::listAllResults(QStringList* gOutput) {

    for (auto x: videos) {

        x.printVideoMatches(gOutput);
    }
}

int allMatches::getTotalMatches() {

    return totalMatches;
}

int allMatches::getTotalVideos() {

    return totalVideos;
}
