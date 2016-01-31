/*
Copyright (c) 2009 - 2016, Valeriy Soldatov
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
 * Neither the name of the football.mojgorod.ru nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include <QDesktopWidget>
#include <QFileDialog>
#include <QMap>
#include <QMessageBox>
#include <QString>
#include <QtXml>
#include "ui_MainWindow.h"
#include "XmlFileReader.h"
#include "ContextMenu.h"
#include "Filter.h"
#include "Record.h"
#include "Report.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();
    QString expr;
    Ui::MainWindow widget;
    void initTable(QStringList& titles, int columnWidth, int rows);
    void setCellValue(int row, int column, QString value);
    void jump(const QString link, const QString param = "");
    ContextMenu popupMenu;
    void getCodeAndId(const QString& link, QString& code, QString& id);
    QVector<Report> reports;
    QString current;
    QMap<QString, int> tournaments;
private:
    QString data;
    QString previous;
    QString param_current;
    QString param_previous;
    void closeEvent(QCloseEvent *event);
    void report(const QString& fileName);
    void analyzeXml(pointer func, const Filter& filter, StatHash* hash);
    Report saxParser(QFile& file);
    void load(bool withWarning = true);
    void startPage();
    void writeLine(QTextStream& out);

    void calculate(pointer func, const QString& qfilter);
    void openQfb(const QString& fileName, QDate* fromDate, QDate* tillDate);
    void itemSelected(QTableWidgetItem* item);

    void findPlayer();
    void findCoach();
    void saveChanges();

private slots:
    void import();
    void openQfb();
    void newQfb();
    void save();
    void saveAsText();
    void saveAsHtml();
    void saveAsQfb();
    void addReport();
    void editReport();
    void about();
    void callCalculateGoals();
    void callCalculateMatches();
    void callCalculateReferies();
    void callCalculateCoaches();
    void callCalculateTable();
    void callCalculateStadiums();
    void callCalculatePlayers();
    void callCalculateTeams();
    void callVerifyPlayers();
    void callVerifyPlayers2();
    void callVerifyAttendance();
    void callFindPlayer();
    void callFindCoach();

    void selectMode0();
    void selectMode1();
    void selectMode2();
    void selectMode3();
    void selectMode4();
    void selectMode5();
    void selectMode6();
    void selectMode7();
    void selectMode8();
    void linkActivated(const QUrl & link);
    void cellSelected(int row, int column);
    void refresh();
    void back();
    void select();
    void changeTournaments(int index);
    void contextMenu(const QPoint& pos);
};

#endif	/* _MAINWINDOW_H */
