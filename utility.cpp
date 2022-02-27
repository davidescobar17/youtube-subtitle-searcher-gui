#include "utility.h"

#include <QRegularExpression>
#include <iostream>
#include <string>

bool containsTarget(std::string line, std::string target) {

    line = toLowerString(line);
    target = toLowerString(target);

    QString lineConv = QString::fromStdString(line);
    QString targetConv = QString::fromStdString(target);
    QRegularExpression re("\\b" + targetConv + "\\b");
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

    QRegularExpression re("<.*?>");
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
