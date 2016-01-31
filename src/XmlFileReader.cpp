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

#include "Filter.h"
#include "Record.h"
#include "Report.h"
#include "MainWindow.h"
#include "XmlFileReader.h"
#include "constants.h"

bool isPlayed(const Report& report, const QString& player) {
    bool value = false;
    QVector<Report::Player> players1 = report.getPlayers1();
    QVector<Report::Player> players2 = report.getPlayers2();
    uint len1 = players1.size();
    for (uint i = 0; i < len1; i++) {
        QString player2 = players1.at(i).player;
        if (player2 == player) {
            return true;
        }
    }
    uint len2 = players2.size();
    for (uint i = 0; i < len2; i++) {
        QString player2 = players2.at(i).player;
        if (player2 == player) {
            return true;
        }
    }
    QVector<Report::Event> events = report.getEvents();
    uint length = events.size();
    for (uint i = 0; i < length; i++) {
        QString eventType = events.at(i).type;
        if (eventType == EVENT_SUBSTITUTION) {
            QString player2 = events.at(i).player2;
            if (player2 == player) {
                return true;
            }
        }
    }
    return value;
}

int getPlayerGoals(const Report* report, const QString* player) {
    int value = 0;
    QVector<Report::Event> events = report->getEvents();
    uint length = events.size();
    for (uint i = 0; i < length; i++) {
        QString eventType = events.at(i).type;
        if ((eventType == EVENT_GOAL) || (eventType == EVENT_GOAL_PENALTY)) {
            QString player2 = events.at(i).player;
            if (player2 == player) {
                value++;
            }
        }
    }
    return value;
}

void addMatch(const Report& report, const QString& fileName, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QDate date = report.getDate();
    const QString* score = report.getScore();
    QString city = report.getStadiumCity();
    QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
    Record* record = Record::getInstance(hash, key);
    QString qdate = date.toString("yyyy/MM/dd");
    record->setString(qdate, 0);
    record->setString(city, 1);
    record->setString(team1, 2);
    record->setString(team2, 3);
    record->setString(*score, 4);
    record->setString(fileName, 5);
}

QString getKeyPlayer(const bool useID, const QString& playerid, const QString& player, const QString& team) {
    QString qstr = (useID) ?
        ((playerid == "") ? QString("%1").arg(player) : QString("%1").arg(playerid)) :
        QString("%1 %2").arg(player).arg(team);
    return qstr;
}

QString getKeyCoach(const bool useID, const QString& coachid, const QString& coach, const QString& team) {
    QString qstr = (useID) ?
        ((coachid == "") ? QString("%1").arg(coach) : QString("%1").arg(coachid)) :
        QString("%1 %2").arg(coach).arg(team);
    return qstr;
}

QString getKeyTeam(const bool useID, const QString& teamid, const QString& team) {
    QString qstr = (useID) ?
        ((teamid == "") ? QString("%1").arg(team) : QString("%1").arg(teamid)) :
        QString("%1").arg(team);
    return qstr;
}
