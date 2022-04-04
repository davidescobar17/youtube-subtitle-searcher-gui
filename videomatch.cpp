#include "videomatch.h"
#include "utility.h"

#include <QString>
#include <QRegularExpression>
#include <iostream>

using std::cout;
using std::endl;

std::string extractVidId(std::string str) {

    QString testStringConv = QString::fromStdString(str);
    QRegularExpression re(".{11}(?=\\.(.*)$)");
    QRegularExpressionMatch match = re.match(testStringConv);
    QString textMatched = match.captured(0);

    return textMatched.toStdString();
}

videoMatch::videoMatch(std::string t, QVector<std::string> p) {

    time = t;
    passage = p;
}

void videoMatch::printPassage(std::string vidName, QStringList* output) {

    int seconds = extractTime(time);
    std::string vidId = extractVidId(vidName);

    std::string url = "https://youtu.be/" + vidId + "?t=" + std::to_string(seconds);
    std::string urlInTag = "<a href=\"https://youtu.be/" + vidId + "?t=" + std::to_string(seconds) + "\">" + url + " </a>";

    output->append(QString::fromUtf8(urlInTag.c_str()));

    for (auto x: passage) {

        if (x.find_first_not_of(' ') != std::string::npos) {

            output->append(QString::fromUtf8(x.c_str()));
        }
    }

    output->append("");
}
