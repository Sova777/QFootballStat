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

#include "DumpToHtml.h"
#include "MainWindow.h"
#include <QFile>
#include <QTextStream>

void DumpToHtml::save(QVector<Report>& reports, QString directory) {
    int id = 0;
    foreach(Report report, reports) {
        QString qstr = QString::fromLatin1("%1/report_%2.html").arg(directory).arg(id);
        QFile file(qstr);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
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
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src='images/goal.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_GOAL_PENALTY) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src='images/pen.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_MISSED_PENALTY) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src='images/missed.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_AUTOGOAL) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src='images/autogoal.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_RED_CARD) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src='images/red.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_RED_YELLOW_CARD) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src='images/yellow2.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_YELLOW_CARD) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src='images/yellow.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_REPLACE_KEEPER) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src='images/keeper.png'>").arg(eventType).arg(team).arg(player));
                } else if (eventType == EVENT_SUBSTITUTION) {
                    text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5 - %6</td></tr>").arg(time).arg("<img src='images/subs.png'>").arg(eventType).arg(team).arg(player).arg(player2));
                } else if (player2 == "") {
                    text.append(QString("<tr><td>%1'</td><td>%2</td><td>%3</td><td>%4</td></tr>").arg(time).arg(eventType).arg(team).arg(player));
                } else {
                    text.append(QString("<tr><td>%1'</td><td>%2</td><td>%3</td><td>%4 - %5</td></tr>").arg(time).arg(eventType).arg(team).arg(player).arg(player2));
                }
            }
            text.append(QString::fromLatin1("</table>"));
            out << text;
            file.close();
        }
        id++;
    }
}
