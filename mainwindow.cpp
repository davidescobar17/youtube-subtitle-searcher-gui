#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "allmatches.h"
#include "utility.h"

#include <QMessageBox>
#include <QRegularExpression>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QThread>
#include <QProcess>
#include <QDirIterator>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>

namespace fs = std::filesystem;
using std::cout;
using std::endl;

void MainWindow::parseFile(std::string file, std::string target){

    std::string line;
    std::ifstream infile(file);
    std::string time;
    QVector<std::string> passage;
    QVector<videoMatch> matches;
    bool found = false;
    bool foundOnce = false;
    int foundCount = 0;

    while (std::getline(infile, line))
    {
        std::istringstream iss(line);

        line = removeTags(line);

        // parse the line, it can be time or the text (or blank line)
        if(isTime(line)){

            time = line;

            // if found target, print the time and the passage
            if (found){

                // create new match item
                videoMatch match(time, passage);
                matches.push_back(match);
                foundOnce = true;
                foundCount++;
            }

            found = false;
            passage.clear();
        }
        else{

            if(containsTarget(line, target)){

                found = true;
            }

            // add to passage for this time
            passage.push_back(line);
        }
    }

    if (foundCount > 0){

        // this gets filled with all matches, then stored to the results
        video newVideo(file, matches);
        results->addVideo(newVideo);
    }
}


void MainWindow::saveOutputToFile(bool saveToFile){

    std::string option = "";

    if(saveToFile){

        std::ofstream out(qApp->applicationDirPath().toStdString()+"/output/out.txt");
        std::streambuf *coutbuf = std::cout.rdbuf();

        // redirect output to file
        std::cout.rdbuf(out.rdbuf());

        //reset to standard output again
        std::cout.rdbuf(coutbuf);
    }
}

bool done = false;

void MainWindow::search(std::string toFind, std::string termInTitle){

    // apply loading cursor
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    std::string inputFolder = "input";
    std::string ext(".vtt");

    ui->textBrowser->clear();
    gOutput->clear();

    float fileSearchedCount = 0.0;

    if(ui->radioButton_file->isChecked()){

        // input from file(s)

        float numberFiles = inputIfFilesChecked.size();

        for(std::string s : inputIfFilesChecked){

            int progress = (fileSearchedCount / numberFiles) * 100;
            ui->progressBar->setValue(progress);
            QApplication::processEvents();

            if(videoTitleContainsTarget(s, termInTitle) || termInTitle == ""){

                parseFile(s, toFind);
            }

            fileSearchedCount++;

            results->listAllResults(gOutput);

            for(auto x: *gOutput){

                ui->textBrowser->append(x);
            }

            gOutput->clear();
        }
    }
    else{

        // input from folder

        float numberFiles = inputIfFolderChecked.size();

        for(std::string s : inputIfFolderChecked){

            int progress = (fileSearchedCount / numberFiles) * 100;

            ui->progressBar->setValue(progress);
            QApplication::processEvents();

            if(videoTitleContainsTarget(s, termInTitle) || termInTitle == ""){

                parseFile(s, toFind);
            }

            fileSearchedCount++;

            results->listAllResults(gOutput);

            for(auto x: *gOutput){

                ui->textBrowser->append(x);
            }

            gOutput->clear();
        }
    }

    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);

    saveOutputToFile(ui->checkBox->isChecked());
    results->reset();

    // remove loading cursor
    QApplication::restoreOverrideCursor();
    done = true;

    // set text browser scroll position to start at top
    QTextCursor cursor = ui->textBrowser->textCursor();
    cursor.setPosition(0);
    ui->textBrowser->setTextCursor(cursor);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir dir(QCoreApplication::applicationDirPath());

    QDirIterator it(qApp->applicationDirPath() + QString("/input"), QStringList() << "*.vtt", QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext()){
        it.next();
        inputIfFolderChecked.push_back(it.filePath().toStdString());
        ui->lineEdit_filePath->setText(qApp->applicationDirPath() + QString("/input"));
    }

    ui->lineEdit_downloadSubPath->setText(qApp->applicationDirPath() + QString("/input"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// search button
void MainWindow::on_pushButton_clicked()
{
    QString le1 = ui->lineEdit_term->text();
    QString le2 = ui->lineEdit_fileFilter->text();

    std::string le1convert = le1.toStdString();
    std::string le2convert = le2.toStdString();

    int numberFiles = 0;

    if(ui->radioButton_file->isChecked()){

        // file(s) selection

        QVector<std::string> vectorFiles;

        numberFiles = fileNames.size();

        QString le2 = ui->lineEdit_fileFilter->text();

        std::string le2convert = le2.toStdString();

        bool firstFileAdded = false;

        if (!fileNames.isEmpty()){

            ui->lineEdit_filePath->clear();

            // to push QStringList to a string vector
            foreach( QString str, fileNames){

                if(firstFileAdded){

                    ui->lineEdit_filePath->insert(", ");
                }

                inputIfFilesChecked.push_back(str.toStdString());
                ui->lineEdit_filePath->insert(str);
            }
        }
    }
    else{

        // folder selection

        if(!dir.isEmpty()){

            QDirIterator it(qApp->applicationDirPath() + QString("/input"), QStringList() << "*.vtt", QDir::Files, QDirIterator::Subdirectories);

            while (it.hasNext()){
                numberFiles++;
                inputIfFolderChecked.push_back(it.filePath().toStdString());
            }
        }
    }

    search(le1convert, le2convert);
}

// to open input file or folder
void MainWindow::on_pushButton_2_clicked()
{
    inputIfFilesChecked.clear();
    inputIfFolderChecked.clear();

    int numberFiles = 0;

    if(ui->radioButton_file->isChecked()){

        // file(s) selection

        fileNames = QFileDialog::getOpenFileNames(this, "Open a file", qApp->applicationDirPath(), tr("Subtitle Files (*.vtt)"));
    }
    else{

        // folder selection

        dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    qApp->applicationDirPath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    }
}

// subtitle download location selection
void MainWindow::on_pushButton_3_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                qApp->applicationDirPath(),
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);

    subDownloadPath = dir;

    ui->lineEdit_downloadSubPath->setText(dir);
}

// subtitle download command
void MainWindow::on_pushButton_4_clicked()
{
    std::string link = ui->lineEdit_link->text().toStdString();
    std::string command = "youtube-dl --sub-lang en --write-auto-sub --sub-format vtt --skip-download --output \"" + subDownloadPath.toStdString() + "/%(title)s-%(id)s.%(ext)s\" \"" + link + "\"";
    system(command.c_str());
}
