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

#include "CheckPlayers2.h"

void checkListOfPlayers2(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QVector<Report::Player> players1 = xmlFilter.report->getPlayers1();
        QVector<Report::Player> players2 = xmlFilter.report->getPlayers2();
        uint len1 = players1.size();
        for (uint i = 0; i < len1; i++) {
            QString player = players1.at(i).player;
            QString id = players1.at(i).id;
            QString key = QString("%1,%2").arg(player).arg(team1);
            Record* record = Record::getInstance(hash, key);
            QString real_id = record->getString();
            int counter = record->get();
            if ((real_id == "") && (counter == 0)) {
                record->setString(id, 0);
                record->setString(player, 1);
                record->setString(team1, 2);
                record->setString(id, 3);
                record->add(1);
            } else {
                if (real_id != id) {
                    record->setString(id, 4);
                    record->add(1);
                }
            }
        }
        uint len2 = players2.size();
        for (uint i = 0; i < len2; i++) {
            QString player = players2.at(i).player;
            QString id = players2.at(i).id;
            QString key = QString("%1,%2").arg(player).arg(team2);
            Record* record = Record::getInstance(hash, key);
            QString real_id = record->getString();
            int counter = record->get();
            if ((real_id == "") && (counter == 0)) {
                record->setString(id, 0);
                record->setString(player, 1);
                record->setString(team2, 2);
                record->setString(id, 3);
                record->add(1);
            } else {
                if (real_id != id) {
                    record->setString(id, 4);
                    record->add(1);
                }
            }
        }
        QVector<Report::Event> events = xmlFilter.report->getEvents();
        uint length = events.size();
        for (uint i = 0; i < length; i++) {
            QString team = events.at(i).team;
            QString eventType = events.at(i).type;
            QString player = events.at(i).player;
            QString playerid = events.at(i).playerid;
            QString key = QString("%1,%2").arg(player).arg(team);
            Record* record = Record::getInstance(hash, key);
            QString real_id = record->getString();
            int counter = record->get();
            if ((real_id == "") && (counter == 0)) {
                record->setString(playerid, 0);
                record->setString(player, 1);
                record->setString(team, 2);
                record->setString(playerid, 3);
                record->add(1);
            } else {
                if (real_id != playerid) {
                    record->setString(playerid, 4);
                    record->add(1);
                }
            }
            if (eventType == EVENT_SUBSTITUTION) {
                QString player2 = events.at(i).player2;
                QString playerid2 = events.at(i).playerid2;
                QString key = QString("%1,%2").arg(player2).arg(team);
                Record* record = Record::getInstance(hash, key);
                QString real_id = record->getString();
                int counter = record->get();
                if ((real_id == "") && (counter == 0)) {
                    record->setString(playerid2, 0);
                    record->setString(player2, 1);
                    record->setString(team, 2);
                    record->setString(playerid2, 3);
                    record->add(1);
                } else {
                    if (real_id != playerid2) {
                        record->setString(playerid2, 4);
                        record->add(1);
                    }
                }
            }
        }
    } else {
        QStringList titles;
        titles << TABLE_CHECKPLAYERS2_COLUMN1
                << TABLE_CHECKPLAYERS2_COLUMN2
                << TABLE_CHECKPLAYERS2_COLUMN3
                << TABLE_CHECKPLAYERS2_COLUMN4;
        xmlFilter.window->initTable(titles, 120, hash->size());

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            if (record->get() > 1) {
                i++;
            }
        }
        xmlFilter.window->widget.table->setRowCount(i);
        i = 0;

        foreach(StatHashValue* record, *hash) {
            if (record->get() > 1) {
                xmlFilter.window->setCellValue(i, 0, record->getString(1));
                xmlFilter.window->setCellValue(i, 1, record->getString(2));
                xmlFilter.window->setCellValue(i, 2, record->getString(3));
                xmlFilter.window->setCellValue(i, 3, record->getString(4));
                xmlFilter.window->setCellValue(i, 4, QString(""));
                delete record;
                i++;
            }
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}
