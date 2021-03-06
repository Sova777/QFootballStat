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

#include "../../MainWindow.h"
#include "../../constants.h"

#include "QueryTeams2.h"

void listOfTeams2(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QVector<Report::Player> players1 = xmlFilter.report->getPlayers1();
        QVector<Report::Player> players2 = xmlFilter.report->getPlayers2();
        uint len1 = players1.size();
        for (uint i = 0; i < len1; i++) {
            QString player2 = players1.at(i).player;
            QString player2id = players1.at(i).id;
            QString key = getKeyPlayer(xmlFilter.filter->useID, player2id, player2, team1);
            Record* record = Record::getInstance(hash, key);
            record->setString(player2, 0);
            record->setString(team1, 1);
            record->add(1);
        }
        uint len2 = players2.size();
        for (uint i = 0; i < len2; i++) {
            QString player2 = players2.at(i).player;
            QString player2id = players2.at(i).id;
            QString key = getKeyPlayer(xmlFilter.filter->useID, player2id, player2, team2);
            Record* record = Record::getInstance(hash, key);
            record->setString(player2, 0);
            record->setString(team2, 1);
            record->add(1);
        }

        QVector<Report::Event> events = xmlFilter.report->getEvents();
        uint length = events.size();
        for (uint i = 0; i < length; i++) {
            QString eventType = events.at(i).type;
            QString player1 = events.at(i).player;
            QString player1id = events.at(i).playerid;
            QString player2 = events.at(i).player2;
            QString player2id = events.at(i).playerid2;
            QString team = events.at(i).team;
            if (eventType == EVENT_SUBSTITUTION) {
                QString key = getKeyPlayer(xmlFilter.filter->useID, player2id, player2, team);
                Record* record = Record::getInstance(hash, key);
                record->setString(player2, 0);
                record->setString(team, 1);
                record->add(1, 0);
            } else {
                QString key = getKeyPlayer(xmlFilter.filter->useID, player1id, player1, team);
                Record* record = Record::getInstance(hash, key);
                record->setString(player1, 0);
                record->setString(team, 1);
                if (eventType == EVENT_RED_CARD) {
                    record->add(1, 1);
                } else if (eventType == EVENT_RED_YELLOW_CARD) {
                    record->add(1, 2);
                } else if (eventType == EVENT_YELLOW_CARD) {
                    record->add(1, 3);
                } else if (eventType == EVENT_GOAL) {
                    record->add(1, 4);
                } else if (eventType == EVENT_GOAL_PENALTY) {
                    record->add(1, 5);
                } else if (eventType == EVENT_MISSED_PENALTY) {
                    record->add(1, 6);
                } else if (eventType == EVENT_AUTOGOAL) {
                    record->add(1, 7);
                }
            }
        }
    } else {
        StatHash hash_stat;
        int i = 0;

        foreach(StatHashValue* record, *hash) {
            if (record->getString(1) == xmlFilter.filter->filter) {
                QString key = QString("%1").arg(record->getString(0));
                Record* record_stat = Record::getInstance(hash_stat, key);
                record_stat->setString(record->getString(0), 0);
                record_stat->setString(record->getString(1), 1);
                record_stat->set(record->get(0), 0);
                delete record;
                i++;
            }
        }
        hash->clear();
        QStringList titles;
        titles << TABLE_TEAMS2_COLUMN1
                << TABLE_TEAMS2_COLUMN2
                << TABLE_TEAMS2_COLUMN3;
        xmlFilter.window->initTable(titles, 60, hash_stat.size());
        xmlFilter.window->widget.table->setColumnWidth(0, 120);
        xmlFilter.window->widget.table->setColumnWidth(1, 120);

        i = 0;
        foreach(StatHashValue* record, hash_stat) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
            xmlFilter.window->setCellValue(i, 3, QString("pl02_%1").arg(record->getString(0)));
            delete record;
            i++;
        }
        hash_stat.clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}
