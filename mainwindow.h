#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "allmatches.h"

#include <QMainWindow>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    // saves the output for the user, if user specified to save to output file
    void saveOutputToFile(bool saveToFile);

    // looks through subtitle file to find the target term
    void parseFile(std::string file, std::string target);

    // passes toFind with subtitile files to parseFile
    // optionally for files with title containing termInTitle
    void search(std::string toFind, std::string termInTitle);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    allMatches* results = new allMatches();
    QStringList* gOutput = new QStringList();
    QVector<std::string> inputIfFilesChecked;
    QVector<std::string> inputIfFolderChecked;
    QString subDownloadPath = "input";
    QStringList fileNames;
    QString downloadDir;
    QString inputDir;

};
#endif // MAINWINDOW_H
