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

    // move the seconds a bit back (overwise the played clip is slightly too late)
    if (seconds >= 5) {

        seconds = seconds - 5;
    }
    else {

        seconds = 0;
    }

    return seconds;
}
