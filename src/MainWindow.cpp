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

#include <QtGui>
#include <QtXml>

#include "EditReport.h"
#include "Filter.h"
#include "Find.h"
#include "MainWindow.h"
#include "Report.h"
#include "constants.h"
#include "ui_MainWindow.h"
#include "EditReport.h"
#include "DumpToHtml.h"
#include "actions/Actions.h"

using namespace std;

MainWindow::MainWindow() {

    widget.setupUi(this);

    connect(widget.actionExit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(widget.actionSaveAsText, SIGNAL(triggered()),
            this, SLOT(saveAsText()));
    connect(widget.actionSaveAsHtml, SIGNAL(triggered()),
            this, SLOT(saveAsHtml()));
    connect(widget.actionSaveAsQfb, SIGNAL(triggered()),
            this, SLOT(saveAsQfb()));
    connect(widget.actionSave, SIGNAL(triggered()),
            this, SLOT(save()));
    connect(widget.actionImport, SIGNAL(triggered()),
            this, SLOT(import()));
    connect(widget.actionOpenQfb, SIGNAL(triggered()),
            this, SLOT(openQfb()));
    connect(widget.actionNewQfb, SIGNAL(triggered()),
            this, SLOT(newQfb()));
    connect(widget.actionAddReport, SIGNAL(triggered()),
            this, SLOT(addReport()));
    connect(widget.actionEditReport, SIGNAL(triggered()),
            this, SLOT(editReport()));
    connect(widget.actionAbout, SIGNAL(triggered()),
            this, SLOT(about()));

    connect(widget.actionCalculateGoals, SIGNAL(triggered()),
            this, SLOT(callCalculateGoals()));
    connect(widget.actionCalculateMatches, SIGNAL(triggered()),
            this, SLOT(callCalculateMatches()));
    connect(widget.actionCalculateReferies, SIGNAL(triggered()),
            this, SLOT(callCalculateReferies()));
    connect(widget.actionCalculateCoaches, SIGNAL(triggered()),
            this, SLOT(callCalculateCoaches()));
    connect(widget.actionCalculateTable, SIGNAL(triggered()),
            this, SLOT(callCalculateTable()));
    connect(widget.actionCalculateStadiums, SIGNAL(triggered()),
            this, SLOT(callCalculateStadiums()));
    connect(widget.actionCalculatePlayers, SIGNAL(triggered()),
            this, SLOT(callCalculatePlayers()));
    connect(widget.actionCalculateTeams, SIGNAL(triggered()),
            this, SLOT(callCalculateTeams()));
    connect(widget.actionVerifyPlayers, SIGNAL(triggered()),
            this, SLOT(callVerifyPlayers()));
    connect(widget.actionVerifyPlayers2, SIGNAL(triggered()),
            this, SLOT(callVerifyPlayers2()));
    connect(widget.actionVerifyAttendance, SIGNAL(triggered()),
            this, SLOT(callVerifyAttendance()));
    connect(widget.actionFindPlayer, SIGNAL(triggered()),
            this, SLOT(callFindPlayer()));
    connect(widget.actionFindCoach, SIGNAL(triggered()),
            this, SLOT(callFindCoach()));
    connect(widget.pushButton_0, SIGNAL(clicked()),
            this, SLOT(selectMode0()));
    connect(widget.pushButton_1, SIGNAL(clicked()),
            this, SLOT(selectMode1()));
    connect(widget.pushButton_2, SIGNAL(clicked()),
            this, SLOT(selectMode2()));
    connect(widget.pushButton_3, SIGNAL(clicked()),
            this, SLOT(selectMode3()));
    connect(widget.pushButton_4, SIGNAL(clicked()),
            this, SLOT(selectMode4()));
    connect(widget.pushButton_5, SIGNAL(clicked()),
            this, SLOT(selectMode5()));
    connect(widget.pushButton_6, SIGNAL(clicked()),
            this, SLOT(selectMode6()));
    connect(widget.pushButton_7, SIGNAL(clicked()),
            this, SLOT(selectMode7()));
    connect(widget.pushButton_8, SIGNAL(clicked()),
            this, SLOT(selectMode8()));
    connect(widget.text, SIGNAL(anchorClicked(const QUrl &)),
            this, SLOT(linkActivated(const QUrl &)));
    connect(widget.table, SIGNAL(cellDoubleClicked(int, int)),
            this, SLOT(cellSelected(int, int)));
    connect(widget.pushRefresh, SIGNAL(clicked()),
            this, SLOT(refresh()));
    connect(widget.pushSelect, SIGNAL(clicked()),
            this, SLOT(select()));
    connect(widget.pushBack, SIGNAL(clicked()),
            this, SLOT(back()));
    connect(widget.comboTournaments, SIGNAL(currentIndexChanged (int)),
            this, SLOT(changeTournaments(int)));
    connect (widget.table, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(contextMenu(const QPoint&)));
    widget.table->setContextMenuPolicy(Qt::CustomContextMenu);

    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
            "football.mojgorod.ru", "QFootballStat");
    data = settings.value("data").toString();
    if (data == "") {
        QString applicationDir = QCoreApplication::applicationDirPath();
        if (applicationDir != "") {
            if (QFile::exists(applicationDir + "/demo.qfb")) {
                data = applicationDir + "/demo.qfb";
            }
        }
    }
    widget.dateEditFrom->setDate(LAST_DAY);
    widget.dateEditTill->setDate(FIRST_DAY);
    load(false);
    QRect rectangle = frameGeometry();
    rectangle.moveCenter(QDesktopWidget().availableGeometry().center());
    move(rectangle.topLeft());
    startPage();
}

MainWindow::~MainWindow() {
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
            "football.mojgorod.ru", "QFootballStat");
    settings.setValue("data", data);
    settings.sync();
    event->accept();
}

void MainWindow::startPage() {
    widget.text->setText(FIRST_MESSAGE.arg(data).arg(reports.size()));
    widget.actionSaveAsText->setDisabled(true);
    widget.text->setVisible(true);
    widget.table->setVisible(false);
}

void MainWindow::selectMode0() {
    startPage();
}

void MainWindow::selectMode1() {
    jump("ta01_");
}

void MainWindow::selectMode2() {
    jump("te01_");
}

void MainWindow::selectMode3() {
    jump("re01_");
}

void MainWindow::selectMode4() {
    jump("pl01_");
}

void MainWindow::selectMode5() {
    jump("ma01_");
}

void MainWindow::selectMode6() {
    jump("go01_");
}

void MainWindow::selectMode7() {
    jump("co01_");
}

void MainWindow::selectMode8() {
    jump("st01_");
}

void MainWindow::callCalculateGoals() {
    jump("go01_");
}

void MainWindow::callCalculateMatches() {
    jump("ma01_");
}

void MainWindow::callCalculateReferies() {
    jump("re01_");
}

void MainWindow::callCalculateCoaches() {
    jump("co01_");
}

void MainWindow::callCalculateTable() {
    jump("ta01_");
}

void MainWindow::callCalculateStadiums() {
    jump("st01_");
}

void MainWindow::callCalculatePlayers() {
    jump("pl01_");
}

void MainWindow::callCalculateTeams() {
    jump("te01_");
}

void MainWindow::callVerifyPlayers() {
    jump("vpl1_");
}

void MainWindow::callVerifyPlayers2() {
    jump("vpl2_");
}

void MainWindow::callVerifyAttendance() {
    jump("vat1_");
}

void MainWindow::callFindPlayer() {
    jump("fpl1_");
}

void MainWindow::callFindCoach() {
    jump("fco1_");
}

void MainWindow::calculate(pointer func, const QString& qfilter) {
    StatHash hash;
    Filter filter(qfilter, widget.checkBoxID->isChecked(), param_current);
    analyzeXml(func, filter, &hash);
    if (reports.size() > 0) {
        Report report = reports[0];
        XmlFilter xmlFilter(this, &report, report.getReportId(), &filter);
        (*func)(xmlFilter, &hash);
    }
}

void MainWindow::findPlayer(void) {
    expr = "";
    Find find(this);
    find.setWindowTitle(FIND_PLAYER);
    find.exec();
    if (expr != "") {
        calculate(&listOfPlayers3, expr);
    }
}
void MainWindow::findCoach(void) {
    expr = "";
    Find find(this);
    find.setWindowTitle(FIND_COACH);
    find.exec();
    if (expr != "") {
        calculate(&listOfCoaches3, expr);
    }
}

void MainWindow::load(bool withWarning) {
    QFileInfo qFileInfo = QFileInfo(data);
    if (qFileInfo.exists()) {
        if (qFileInfo.isFile()) {
            tournaments.clear();
            QDate fromDate = widget.dateEditFrom->date();
            QDate tillDate = widget.dateEditTill->date();
            openQfb(data, &fromDate, &tillDate);
            widget.dateEditFrom->setDate(fromDate);
            widget.dateEditTill->setDate(tillDate);
            QComboBox* combo = widget.comboTournaments;
            combo->clear();
            combo->addItem(ALL_TOURNAMENTS);
            foreach(QString t, tournaments.keys()) {
                combo->addItem(t);
            }
        }
    } else {
        if (withWarning) {
            QMessageBox::information(NULL, QString::fromUtf8("Нет данных"), QString::fromUtf8("Нет данных. Выберите файл с результатами."));
        }
    }
}

// SAX парсер
void MainWindow::analyzeXml(pointer func, const Filter& filter, StatHash* hash) {
    if (reports.size() == 0) {
        QMessageBox::information(NULL, QString::fromUtf8("Нет данных"), QString::fromUtf8("Нет данных. Выберите файл с результатами."));
        return;
    }
    statusBar()->showMessage(STATUS_CALCULATING);
    const QCursor cursor = this->cursor();
    this->setCursor(Qt::WaitCursor);
    QApplication::processEvents();
    QTime t;
    t.start();
    if (reports.size() > 0) {
        int counter = 0;
        QDate fromDate = widget.dateEditFrom->date();
        QDate tillDate = widget.dateEditTill->date();
        QString tourn = widget.comboTournaments->currentText();
        foreach(Report report, reports) {
            counter++;
            QDate date = report.getDate();
            QString currentTournament = report.getMatchTournament();
            if ((tourn == ALL_TOURNAMENTS) || (currentTournament == tourn)) {
                if ((date >= fromDate) && (date <= tillDate)) {
                    XmlFilter xmlFilter(NULL, &report, report.getReportId(), &filter);
                    (*func)(xmlFilter, hash);
                }
            }
            if ((counter % 1000) == 0) {
                statusBar()->showMessage(QString("%1 (%2 %3)")
                        .arg(STATUS_CALCULATING_MEMORY)
                        .arg(counter)
                        .arg(STATUS_CALCULATING_MEMORY2));
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }
    }
    this->setCursor(cursor);
    QString status = STATUS_TIME.arg(t.elapsed());
    statusBar()->showMessage(status, 2000);
    return;
}

Report MainWindow::saxParser(QFile& file) {
    Report report;
    report.setReportId(file);
    QXmlStreamReader xml(&file);
    QString currentTag;
    QString currentId;
    while (!xml.atEnd()) {
        xml.readNext();
        QStringRef ref = xml.name();
        if (xml.isStartElement()) {
            currentTag = ref.toString();
            if (currentTag == "team1") {
                report.setTeam1Attributes(xml);
            } else if (currentTag == "team2") {
                report.setTeam2Attributes(xml);
            } else if (currentTag == "date") {
                report.setDateAttributes(xml);
            } else if (currentTag == "coach1") {
                report.setCoach1Attributes(xml);
            } else if (currentTag == "coach2") {
                report.setCoach2Attributes(xml);
            } else if (currentTag == "stadium") {
                report.setStadiumAttributes(xml);
            } else if (currentTag == "referee") {
                report.setRefereeAttributes(xml);
            } else if (currentTag == "match") {
                report.setMatchAttributes(xml);
            } else if (currentTag == "score") {
                report.setScoreAttributes(xml);
            } else if (currentTag == "event") {
                report.addEvent(xml);
            } else if (currentTag == "player1") {
                currentId = xml.attributes().value("id").toString();
            } else if (currentTag == "player2") {
                currentId = xml.attributes().value("id").toString();
            }
        } else if (xml.isCharacters()) {
            if (currentTag == "team1") {
                report.setTeam1(xml);
            } else if (currentTag == "team2") {
                report.setTeam2(xml);
            } else if (currentTag == "date") {
                report.setDate(xml);
            } else if (currentTag == "coach1") {
                report.setCoach1(xml);
            } else if (currentTag == "coach2") {
                report.setCoach2(xml);
            } else if (currentTag == "stadium") {
                report.setStadium(xml);
            } else if (currentTag == "referee") {
                report.setReferee(xml);
            } else if (currentTag == "player1") {
                report.addPlayer1(xml, currentId);
            } else if (currentTag == "player2") {
                report.addPlayer2(xml, currentId);
            }
        } else {
            currentTag = "";
        }
    }
    if (xml.hasError()) {
        qDebug() << "\"" << file.fileName() << "\" file has error";
    }
    return report;
}

void MainWindow::linkActivated(const QUrl & link) {
    QString code = link.toString().section("_", 0, 0);
    QString id = link.toString().section("_", 1, 1);
    if (code == "cl") {
        //calculateTeamStat(id);
        return;
    }
    if (code == "match") {
        //matchReport(id);
        return;
    }
    return;
}

void MainWindow::setCellValue(int row, int column, QString value) {
    QTableWidgetItem* stlb = new QTableWidgetItem(value);
    stlb->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    widget.table->setItem(row, column, stlb);
}

void MainWindow::import() {
    QString dir = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Выберите директорий"), data);
    if (dir != "") {
        QDate fromDate = widget.dateEditFrom->date();
        QDate tillDate = widget.dateEditTill->date();
        int counter = 0;
        QDir qDir = QDir(dir);
        QDirIterator it(qDir.absolutePath(), QDirIterator::Subdirectories);
        while (it.hasNext()) {
            it.next();
            if (!it.fileInfo().isDir()) {
                counter++;
                QString fileName = it.fileName();
                if (!fileName.endsWith(QLatin1String(".xml"))) continue;
                QString fullFileName = it.fileInfo().absoluteFilePath();
                QFile file(fullFileName);
                if (!file.open(QIODevice::ReadOnly)) continue;
                Report report = saxParser(file);
                reports.append(report);
                QDate currentDate = report.getDate();
                tournaments.insert(report.getMatchTournament(), 0);
                if (currentDate < fromDate) {
                    fromDate = currentDate;
                }
                if (currentDate > tillDate) {
                    tillDate = currentDate;
                }
                file.close();
            }
            if ((counter % 100) == 0) {
                statusBar()->showMessage(QString("%1 (%2 %3)")
                        .arg(STATUS_CALCULATING)
                        .arg(counter)
                        .arg(STATUS_CALCULATING2));
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }
        widget.dateEditFrom->setDate(fromDate);
        widget.dateEditTill->setDate(tillDate);
        QComboBox* combo = widget.comboTournaments;
        combo->clear();
        combo->addItem(ALL_TOURNAMENTS);
        foreach(QString t, tournaments.keys()) {
            combo->addItem(t);
        }
        statusBar()->showMessage(QString("%1 (%2 %3)")
                .arg(STATUS_CALCULATING)
                .arg(counter)
                .arg(STATUS_CALCULATING2), 2000);
    }
    startPage();
}

void MainWindow::about() {
    QMessageBox::about(this, QString::fromUtf8("О программе QFootballStat"), QString::fromUtf8("<h2>QFootballStat</h2><p>Создана Солдатовым Валерием Фёдоровичем для сайта <a href='http://football.mojgorod.ru'>http://football.mojgorod.ru</a></p>"));
}

void MainWindow::writeLine(QTextStream& out) {
    int columns = widget.table->columnCount();
    out << "-";
    for (int k = 0; k < columns; k++) {
        if (!widget.table->isColumnHidden(k)) {
            int len = widget.table->columnWidth(k);
            out << QString("").rightJustified(len / 7, '-', false) << "---";
        }
    }
    out << "\n";
}

void MainWindow::saveAsText() {
    QString qstr = QFileDialog::getSaveFileName(this, QString::fromUtf8("Выберите имя файла"), NULL);
    if (qstr == "") return;
    QFile file(qstr);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    int rows = widget.table->rowCount();
    int columns = widget.table->columnCount();
    writeLine(out);
    out << "| ";
    for (int k = 0; k < columns; k++) {
        if (!widget.table->isColumnHidden(k)) {
            QString label = widget.table->horizontalHeaderItem(k)->text();
            int len = widget.table->columnWidth(k);
            out << label.replace("\n", "").rightJustified(len / 7, ' ', true) << " | ";
        }
    }
    out << "\n";
    writeLine(out);
    for (int i = 0; i < rows; i++) {
        out << "| ";
        for (int j = 0; j < columns; j++) {
            if (!widget.table->isColumnHidden(j)) {
                int len = widget.table->columnWidth(j);
                out << widget.table->item(i, j)->text().rightJustified(len / 7, ' ', false) << " | ";
            }
        }
        out << "\n";
    }
    writeLine(out);
    file.close();
}

void MainWindow::saveAsHtml() {
    QString qstr = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Выберите имя директория"), NULL);
    if (qstr == "") return;
    DumpToHtml::save(reports, qstr);
}

void MainWindow::newQfb() {
    QString qstr = QFileDialog::getSaveFileName(this, QString::fromUtf8("Выберите имя файла"), NULL, "*.qfb");
    if (qstr != "") {
        data = qstr;
        reports.clear();
        QComboBox* combo = widget.comboTournaments;
        combo->clear();
        combo->addItem(ALL_TOURNAMENTS);
        widget.dateEditFrom->setDate(LAST_DAY);
        widget.dateEditTill->setDate(FIRST_DAY);
        startPage();
    }
}

void MainWindow::openQfb() {
    QString qstr = QFileDialog::getOpenFileName(this, QString::fromUtf8("Выберите имя файла"), NULL, "*.qfb");
    if (qstr == "") return;
    if (qstr != "") {
        data = qstr;
        reports.clear();
        widget.dateEditFrom->setDate(LAST_DAY);
        widget.dateEditTill->setDate(FIRST_DAY);
    }
    load(true);
    startPage();
}

void MainWindow::openQfb(const QString& fileName, QDate* fromDate, QDate* tillDate) {
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_0);
    quint32 magicKey;
    in >> magicKey;
    if (magicKey == (quint32)0xF07BA110) {
        quint32 version;
        in >> version;
        if (version == (quint32)1) {
            tournaments.clear();
            reports.clear();
            quint32 records;
            in >> records;
            for (quint32 j = 0; j < records; j++) {
                Report report;
                QString FileName;
                QString MatchId;
                QString MatchRound;
                QString MatchTournament;
                QString Goals1;
                QString Goals2;
                QString Extra1;
                QString Extra2;
                QString Penalties1;
                QString Penalties2;
                QString Time;
                QDate Date;
                QString Coach1id;
                QString Coach1;
                QString Coach2id;
                QString Coach2;
                QString Team1id;
                QString Team1;
                QString Team2id;
                QString Team2;
                QString StadiumId;
                QString Stadium;
                QString StadiumCity;
                QString StadiumAttendance;
                QString RefereeId;
                QString Referee;
                QString RefereeCity;
                QString RefereeCountry;
                quint32 lenPlayers1;
                quint32 lenPlayers2;
                quint32 lenEvents;

                in >> FileName;
                report.setReportId(FileName);
                in >> MatchId;
                report.setMatchId(MatchId);
                in >> MatchRound;
                report.setMatchRound(MatchRound);
                in >> MatchTournament;
                report.setMatchTournament(MatchTournament);
                in >> Goals1;
                report.setGoals1(Goals1);
                in >> Goals2;
                report.setGoals2(Goals2);
                in >> Extra1;
                report.setExtra1(Extra1);
                in >> Extra2;
                report.setExtra2(Extra2);
                in >> Penalties1;
                report.setPenalties1(Penalties1);
                in >> Penalties2;
                report.setPenalties2(Penalties2);
                in >> Time;
                report.setTime(Time);
                in >> Date;
                report.setDate(Date);
                in >> Coach1id;
                report.setCoach1id(Coach1id);
                in >> Coach1;
                report.setCoach1(Coach1);
                in >> Coach2id;
                report.setCoach2id(Coach2id);
                in >> Coach2;
                report.setCoach2(Coach2);
                in >> Team1id;
                report.setTeam1id(Team1id);
                in >> Team1;
                report.setTeam1(Team1);
                in >> Team2id;
                report.setTeam2id(Team2id);
                in >> Team2;
                report.setTeam2(Team2);
                in >> StadiumId;
                report.setStadiumId(StadiumId);
                in >> Stadium;
                report.setStadium(Stadium);
                in >> StadiumCity;
                report.setStadiumCity(StadiumCity);
                in >> StadiumAttendance;
                report.setStadiumAttendance(StadiumAttendance);
                in >> RefereeId;
                report.setRefereeId(RefereeId);
                in >> Referee;
                report.setReferee(Referee);
                in >> RefereeCity;
                report.setRefereeCity(RefereeCity);
                in >> RefereeCountry;
                report.setRefereeCountry(RefereeCountry);
                tournaments.insert(MatchTournament, 0);
                if (Date < *fromDate) {
                    *fromDate = Date;
                }
                if (Date > *tillDate) {
                    *tillDate = Date;
                }

                in >> lenPlayers1;
                for (quint32 i = 0; i < lenPlayers1; i++) {
                    QString id;
                    QString player;
                    in >> id;
                    in >> player;
                    report.addPlayer1(id, player);
                }
                in >> lenPlayers2;
                for (quint32 i = 0; i < lenPlayers2; i++) {
                    QString id;
                    QString player;
                    in >> id;
                    in >> player;
                    report.addPlayer2(id, player);
                }
                in >> lenEvents;
                for (quint32 i = 0; i < lenEvents; i++) {
                    QString type;
                    QString time;
                    QString team;
                    QString comment;
                    QString playerid;
                    QString player;
                    QString playerid2;
                    QString player2;
                    in >> type;
                    in >> time;
                    in >> team;
                    in >> comment;
                    in >> playerid;
                    in >> player;
                    in >> playerid2;
                    in >> player2;
                    report.addEvent(type, time, team, comment, playerid, player, playerid2, player2);
                }
                reports.append(report);
            }
        }
    }
}

void MainWindow::saveChanges() {
    QFile file(data);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint32)0xF07BA110;
    out << (quint32)1;
    out << (quint32)reports.size();
    foreach(Report report, reports) {
        out << report.getReportId();
        out << report.getMatchId();
        out << report.getMatchRound();
        out << report.getMatchTournament();
        out << report.getGoals1();
        out << report.getGoals2();
        out << report.getExtra1();
        out << report.getExtra2();
        out << report.getPenalties1();
        out << report.getPenalties2();
        out << report.getTime();
        out << report.getDate();
        out << report.getCoach1id();
        out << report.getCoach1();
        out << report.getCoach2id();
        out << report.getCoach2();
        out << report.getTeam1id();
        out << report.getTeam1();
        out << report.getTeam2id();
        out << report.getTeam2();
        out << report.getStadiumId();
        out << report.getStadium();
        out << report.getStadiumCity();
        out << report.getStadiumAttendance();
        out << report.getRefereeId();
        out << report.getReferee();
        out << report.getRefereeCity();
        out << report.getRefereeCountry();
        QVector<Report::Player> players1 = report.getPlayers1();
        quint32 count = players1.size();
        out << count;
        foreach(Report::Player player1, players1) {
            out << player1.id;
            out << player1.player;
        }
        QVector<Report::Player> players2 = report.getPlayers2();
        count = players2.size();
        out << count;
        foreach(Report::Player player2, players2) {
            out << player2.id;
            out << player2.player;
        }
        QVector<Report::Event> events = report.getEvents();
        count = events.size();
        out << count;
        foreach(Report::Event event, events) {
            out << event.type;
            out << event.time;
            out << event.team;
            out << event.comment;
            out << event.playerid;
            out << event.player;
            out << event.playerid2;
            out << event.player2;
        }
    }
}

void MainWindow::save() {
    if (!QFile::exists(data)) {
        return;
    }
    if (QMessageBox::question(this, QString::fromUtf8("Сохранить изменения"), QString::fromUtf8("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        saveChanges();
    }
}

void MainWindow::saveAsQfb() {
    QString qstr = QFileDialog::getSaveFileName(this, QString::fromUtf8("Выберите имя файла"), NULL, "*.qfb");
    if (qstr == "") return;
    data = qstr;
    saveChanges();
}

void MainWindow::addReport() {
    Report report;
    reports.append(report);
    jump("xm01_");
    EditReport editReport(this);
    editReport.setWindowTitle(NEW_REPORT);
    editReport.exec();
}

void MainWindow::editReport() {
    EditReport editReport(this);
    editReport.setWindowTitle(EDIT_REPORT);
    editReport.exec();
}

void MainWindow::initTable(QStringList& titles, int columnWidth, int rows) {
    int columns = titles.size();
    if (columns < 0) {
        return;
    }
    widget.actionSaveAsText->setDisabled(false);
    widget.table->setVisible(true);
    widget.text->setVisible(false);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    widget.table->setColumnCount(columns + 1);
    for (int j = 0; j < columns; j++) {
        widget.table->setColumnHidden(j, false);
        widget.table->setColumnWidth(j, columnWidth);
    }
    widget.table->setColumnHidden(columns, true);
    widget.table->setRowCount(rows);
    widget.table->setHorizontalHeaderLabels(titles);
}

void MainWindow::cellSelected(int row, int column) {
    if (column >= 0) {
        QTableWidgetItem* item = widget.table->item(row, widget.table->columnCount() - 1);
        itemSelected(item);
    }
}

void MainWindow::itemSelected(QTableWidgetItem* item) {
    if (item != NULL) {
        QString link = item->text();
        jump(link);
    }
}

void MainWindow::jump(const QString link, const QString param) {
    int size = link.length();
    if (size < 5) {
        return;
    }
    param_previous = param_current;
    param_current = param;
    previous = current;
    current = link;
    popupMenu.defaultValues();
    QString code;
    QString id;
    getCodeAndId(link, code, id);
    if (code == "xm01_") {
        report(id);
        return;
    }
    if (code == "ma01_") {
        calculate(&listOfMatches, "");
        return;
    }
    if (code == "st01_") {
        calculate(&listOfStadiums, "");
        return;
    }
    if (code == "st02_") {
        calculate(&listOfStadiums2, id);
        return;
    }
    if (code == "re01_") {
        calculate(&listOfReferies, "");
        return;
    }
    if (code == "re02_") {
        calculate(&listOfReferies2, id);
        return;
    }
    if (code == "co01_") {
        calculate(&listOfCoaches, "");
        return;
    }
    if (code == "co02_") {
        calculate(&listOfCoaches2, id);
        return;
    }
    if (code == "pl01_") {
        calculate(&listOfPlayers, "");
        return;
    }
    if (code == "pl02_") {
        calculate(&listOfPlayers2, id);
        return;
    }
    if (code == "go01_") {
        calculate(&listOfGoals, "");
        return;
    }
    if (code == "go02_") {
        calculate(&listOfGoals2, id);
        return;
    }
    if (code == "te01_") {
        calculate(&listOfTeams, "");
        return;
    }
    if (code == "te02_") {
        calculate(&listOfTeams2, id);
        return;
    }
    if (code == "ta01_") {
        calculate(&listOfTable, "");
        return;
    }
    if (code == "ta02_") {
        calculate(&listOfTable2, id);
        return;
    }
    if (code == "vpl1_") {
        calculate(&checkListOfPlayers, "");
        return;
    }
    if (code == "vpl2_") {
        calculate(&checkListOfPlayers2, "");
        return;
    }
    if (code == "vat1_") {
        calculate(&checkListOfAttendance, "");
        return;
    }
    if (code == "fpl1_") {
        findPlayer();
        return;
    }
    if (code == "fco1_") {
        findCoach();
        return;
    }
}

void MainWindow::report(const QString& fileName) {
    widget.actionSaveAsText->setDisabled(true);
    widget.table->setVisible(false);
    widget.text->setVisible(true);
    widget.text->setText("");

    foreach(Report report, reports) {
        if (report.getReportId() == fileName) {
            QString team1 = report.getTeam1();
            QString team2 = report.getTeam2();
            QString coach1 = report.getCoach1();
            QString coach2 = report.getCoach2();
            const QString* score = report.getScore();
            QString time = report.getTime();
            QDate date = report.getDate();
            QString rlocation = report.getRefereeLocation();
            QString referee = report.getReferee();
            QString round = report.getMatchRound();
            QString tournament = report.getMatchTournament();
            QString city = report.getStadiumCity();
            QString attendance = report.getStadiumAttendance();
            QString stadium = report.getStadium();
            QString text = QString::fromUtf8("<h1 align='center'>%1</h1>")
                    .arg(tournament);
            if ((round == "") || (round.length() > 3)) {
                text.append(QString::fromUtf8("<h2 align='center'>%1</h2>")
                        .arg(round));
            } else {
                text.append(QString::fromUtf8("<h2 align='center'>Тур: %1</h2>")
                        .arg(round));
            }
            text.append(QString::fromUtf8("<h2 align='center'>%1 - %2 - %3</h2>")
                    .arg(team1)
                    .arg(team2)
                    .arg(*score));
            text.append(QString::fromUtf8("<p>"));
            if (city != "") {
                text.append(QString::fromUtf8("%1. ").arg(city));
            }
            text.append(QString::fromUtf8("%1. %2 зрителей<br><b>Судья:</b> %3 (%4)<br>%6 %5</p>")
                    .arg(stadium)
                    .arg(attendance)
                    .arg(referee)
                    .arg(rlocation)
                    .arg(time)
                    .arg(date.toString(Qt::DefaultLocaleLongDate)));

            // игроки
            QVector<Report::Player> players1 = report.getPlayers1();
            text.append(QString::fromLatin1("<table border='0' width='100%'>"));
            text.append(QString::fromLatin1("<tr><td>"));
            uint length1 = players1.size();
            for (uint i = 0; i < length1; i++) {
                QString value = players1.at(i).player;
                if (i != 0) {
                    text.append(QString("<br>"));
                }
                text.append(QString("%1").arg(value));
            }
            text.append(QString::fromLatin1("</td><td>"));
            QVector<Report::Player> players2 = report.getPlayers2();
            uint length2 = players2.size();
            for (uint i = 0; i < length2; i++) {
                QString value = players2.at(i).player;
                if (i != 0) {
                    text.append(QString("<br>"));
                }
                text.append(QString("%1").arg(value));
            }
            text.append(QString::fromLatin1("</td></tr>"));
            text.append(QString::fromUtf8("<tr><td><b>Тренер:</b> %1</td><td><b>Тренер:</b> %2</td></tr>").arg(coach1).arg(coach2));
            text.append(QString::fromLatin1("</table>"));

            // события в матче
            text.append(QString::fromLatin1("<table border='0' width='100%'>"));
            QVector<Report::Event> events = report.getEvents();
            uint length = events.size();
            for (uint i = 0; i < length; i++) {
                QString eventType = events.at(i).type;
                QString player = events.at(i).player;
                QString player2 = events.at(i).player2;
                QString team = events.at(i).team;
                QString time = events.at(i).time;
                if (eventType == EVENT_GOAL) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/goal.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_GOAL_PENALTY) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/pen.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_MISSED_PENALTY) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/missed.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_AUTOGOAL) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/autogoal.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_RED_CARD) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/red.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_RED_YELLOW_CARD) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/yellow2.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_YELLOW_CARD) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/yellow.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_REPLACE_KEEPER) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/keeper.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_SUBSTITUTION) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5 - %6</td></tr>").arg(time).arg("<img src=':/icon/images/subs.png'>").arg(eventType).arg(team).arg(player).arg(player2));
                } else if (player2 == "") {
                    text.append(QString("<tr><td>%1'</td><td>%2</td><td>%3</td><td>%4</td></tr>").arg(time).arg(eventType).arg(team).arg(player));
                } else {
                    text.append(QString("<tr><td>%1'</td><td>%2</td><td>%3</td><td>%4 - %5</td></tr>").arg(time).arg(eventType).arg(team).arg(player).arg(player2));
                }
            }
            text.append(QString::fromLatin1("</table>"));
            widget.text->setText(text);
            break;
        }
    }
}

void MainWindow::refresh() {
    jump(current, param_current);
}

void MainWindow::back() {
    jump(previous, param_previous);
}

void MainWindow::select() {
    if (widget.table->isVisible()) {
        QList<QTableWidgetItem*> list = widget.table->selectedItems();
        if (list.size() > 0) {
            QTableWidgetItem* item = widget.table->item(list[0]->row(), widget.table->columnCount() - 1);
            itemSelected(item);
        }
    }
}

void MainWindow::changeTournaments(int index) {
    if (index < 0) {
        return;
    }
    if (reports.size() != 0) {
        jump(current, param_current);
    }
}

void MainWindow::contextMenu(const QPoint& pos) {
    QMenu menu(this);
    popupMenu.fillQMenu(menu);
    QAction* selectedItem = menu.exec(widget.table->viewport()->mapToGlobal(pos));
    if (selectedItem != NULL) {
        QTableWidgetItem* selectedItemInTable = widget.table->itemAt(pos);
        if (selectedItemInTable != NULL) {
            int row = selectedItemInTable->row();
            QTableWidgetItem* item = widget.table->item(row, widget.table->columnCount() - 1);
            if (item != NULL) {
                QString link = item->text();
//                QMessageBox::information(this, "action", value);
                jump(link, selectedItem->text());
            }
        }
    }
}

void MainWindow::getCodeAndId(const QString& link, QString& code, QString& id) {
    int size = link.length();
    if (size > 0) {
        code = link.left(5);
        id = link.right(size - 5);
    } else {
        code = "";
        id = "";
    }
}
