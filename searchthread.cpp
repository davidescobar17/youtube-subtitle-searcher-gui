#include "searchthread.h"
#include "utility.h"

#include <filesystem>
#include <iostream>
#include <fstream>

void SearchThread::run() {

    search();
}

void SearchThread::search() {

    float fileSearchedCount = 0.0;
    float numberFiles = 0;
    std::vector<std::string> validInputFiles;

    gOutput->clear();
    results->reset();

    emit percentageUpdated(0);

    for (std::string s : inputFiles) {

        if (videoTitleContainsTarget(s, termInTitle) || termInTitle == "") {

            validInputFiles.push_back(s);
            numberFiles++;
        }
    }

    for (std::string s : validInputFiles) {

        int progress = (fileSearchedCount / numberFiles) * 100;

        emit percentageUpdated(progress);

        if (videoTitleContainsTarget(s, termInTitle) || termInTitle == "") {

            parseFile(s, toFind);
        }

        fileSearchedCount++;
    }

    results->listAllResults(gOutput);
    emit percentageUpdated(99);
    emit resultReady(*gOutput);
    gOutput->clear();
}

void SearchThread::parseFile(std::string file, std::string target) {

    std::string line;
    std::ifstream infile(file);
    std::string time;
    QVector<std::string> passage;
    QVector<videoMatch> matches;
    bool found = false;
    int foundCount = 0;

    while (std::getline(infile, line)) {

        std::istringstream iss(line);

        line = removeTags(line);

        // parse the line, it can be time or the text (or blank line)
        if (isTime(line)) {

            time = line;

            // if found target, print the time and the passage
            if (found) {

                // create new match item
                videoMatch match(time, passage);
                matches.push_back(match);
                foundCount++;
            }

            found = false;
            passage.clear();
        }
        else {

            if (containsTarget(line, target)) {

                found = true;
            }

            // add to passage for this time
            passage.push_back(line);
        }
    }

    if (foundCount > 0) {

        // this gets filled with all matches, then stored to the results
        video newVideo(file, matches);
        results->addVideo(newVideo);
    }
}

void SearchThread::setToFind(std::string newToFind) {

    toFind = newToFind;
}

void SearchThread::setTermInTitle(std::string newTermInTitle) {

    termInTitle = newTermInTitle;
}

void SearchThread::setFiles(QVector<std::string> newInputFiles) {

    inputFiles = newInputFiles;
}

void SearchThread::setResults(allMatches* newResults) {

    results = newResults;
}

SearchThread::SearchThread() {

}
