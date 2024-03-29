#include "utility.h"

#include <QRegularExpression>
#include <iostream>
#include <string>

bool containsTarget(std::string line, std::string target) {

    line = toLowerString(line);
    target = toLowerString(target);

    QString lineConv = QString::fromStdString(line);
    QString targetConv = QString::fromStdString(target);
    QRegularExpression re(targetConv);
    QRegularExpressionMatch match = re.match(lineConv);
    bool hasMatch = match.hasMatch();

    return hasMatch;
}

bool videoTitleContainsTarget(std::string line, std::string target) {

    if (toLowerString(line).find(toLowerString(target)) != std::string::npos) {

        return true;
    }

    return false;
}

std::string removeTags(std::string s) {

    QString testStringConv = QString::fromStdString(s);

    QRegularExpression re("<.*?>|&nbsp;|\n");
    testStringConv.replace(re,"");

    return testStringConv.toStdString();
}

bool isTime(std::string line) {

    if (line.find("-->") != std::string::npos) {

        return true;
    }

    return false;
}

std::string toLowerString(std::string s) {

    for (int i = 0; i < s.size(); i++) {

        s[i] = tolower(s[i]);
    }

    return s;
}

int extractTime(std::string str) {

    int h, m, s = 0;
    int seconds = 0;
    std::string timeString;
    QString testStringConv = QString::fromStdString(str);

    QRegularExpression re("^[0-9]{2}:[0-9]{2}:[0-9]{2}");
    QRegularExpressionMatch match = re.match(testStringConv);
    QString textMatched = match.captured(0);

    timeString = textMatched.toStdString();

    if (sscanf(timeString.c_str(), "%d:%d:%d", &h, &m, &s) >= 2) {

        seconds = h *3600 + m*60 + s;
    }

    return seconds;
}

int getDifferenceTimestamps(std::string str) {

    int h, m, s, ms = 0;
    int milliseconds = 0;
    std::string timeString;
    QString testStringConv = QString::fromStdString(str);

    QRegularExpression re("[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{3}");
    QRegularExpressionMatchIterator matches = re.globalMatch(testStringConv);
    QString textMatched;
    QString textMatched2;
    bool firstAdded = false;

    while (matches.hasNext()) {

        QRegularExpressionMatch match = matches.next();
        
        if (match.hasMatch()) {

             if (!firstAdded) {

                 textMatched = match.captured(0);
                 firstAdded = true;
             }
             else {

                 textMatched2 = match.captured(0);
             }
        }
    }

    int firstTime = 0;
    int secondTime = 0;
    int result = 0;

    for (int i = 0; i < 2; i++) {

        if (i == 0) {

            timeString = textMatched.toStdString();
        }
        else {

            timeString = textMatched2.toStdString();
        }

        if (sscanf(timeString.c_str(), "%d:%d:%d.%d", &h, &m, &s, &ms) >= 2) {

            milliseconds = h *3600000 + m*60000 + s*1000 + ms;
        }

        if (i == 0) {

            firstTime = milliseconds;
        }
        else {

            secondTime = milliseconds;
        }
    }

    result = secondTime - firstTime;

    return result;
}
