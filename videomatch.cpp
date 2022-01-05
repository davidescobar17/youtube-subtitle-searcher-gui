#include "videomatch.h"
#include "utility.h"

#include <QString>
#include <QRegularExpression>
#include <iostream>

using std::cout;
using std::endl;

int extractTime(std::string str){

    int h, m, s = 0;
    int seconds = 0;
    std::string timeString;
    QString testStringConv = QString::fromStdString(str);

    QRegularExpression re("^[0-9]{2}:[0-9]{2}:[0-9]{2}");
    QRegularExpressionMatch match = re.match(testStringConv);
    QString textMatched = match.captured(0);

    timeString = textMatched.toStdString();

    if (sscanf(timeString.c_str(), "%d:%d:%d", &h, &m, &s) >= 2){

        seconds = h *3600 + m*60 + s;
    }

    // move the seconds a bit back (overwise the played clip is slightly too late)
    if (seconds >= 5){

        seconds = seconds - 5;
    }
    else{

        seconds = 0;
    }

    return seconds;
}

std::string extractVidId(std::string str){

    QString testStringConv = QString::fromStdString(str);
    QRegularExpression re(".{11}(?=\\.(.*)$)");
    QRegularExpressionMatch match = re.match(testStringConv);
    QString textMatched = match.captured(0);

    return textMatched.toStdString();
}

videoMatch::videoMatch(std::string t, QVector<std::string> p){

    time = t;
    passage = p;
}

void videoMatch::printPassage(std::string vidName, QStringList* output){

    int seconds = extractTime(time);
    std::string vidId = extractVidId(vidName);

    std::string url = "https://youtu.be/" + vidId + "?t=" + std::to_string(seconds);
    std::string urlInTag = "<a href=\"https://youtu.be/" + vidId + "?t=" + std::to_string(seconds) + "\">" + url + " </a>";

    output->append(QString::fromUtf8(urlInTag.c_str()));

    for(auto x: passage){

        if(x.find_first_not_of(' ') != std::string::npos){

            output->append(QString::fromUtf8(x.c_str()));
        }
    }

    output->append("");
}
