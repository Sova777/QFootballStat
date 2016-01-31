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

#include "QueryTable.h"

void listOfTable(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        const QString* score = xmlFilter.report->getScore();
        if (*score != "") {
            bool ok;
            int goal1 = 99999;
            int goal2 = 99999;
            goal1 = score->section(':', 0, 0).toInt(&ok);
            goal2 = score->section(':', 1, 1).toInt(&ok);
            Record* recordTeam1 = Record::getInstance(hash, team1);
            Record* recordTeam2 = Record::getInstance(hash, team2);
            if (recordTeam1->getString() == "") {
                recordTeam1->setString(team1);
            }
            recordTeam1->add(goal1, 3);
            recordTeam1->add(goal2, 4);
            if (recordTeam2->getString() == "") {
                recordTeam2->setString(team2);
            }
            recordTeam2->add(goal2, 3);
            recordTeam2->add(goal1, 4);
            if (goal1 > goal2) {
                recordTeam1->add(1, 0);
                recordTeam2->add(1, 2);
            } else if (goal2 > goal1) {
                recordTeam2->add(1, 0);
                recordTeam1->add(1, 2);
            } else {
                recordTeam2->add(1, 1);
                recordTeam1->add(1, 1);
            }
        }
    } else {
        QStringList titles;
        titles << TABLE_TABLE_COLUMN1
                << TABLE_TABLE_COLUMN2
                << TABLE_TABLE_COLUMN3
                << TABLE_TABLE_COLUMN4
                << TABLE_TABLE_COLUMN5
                << TABLE_TABLE_COLUMN6
                << TABLE_TABLE_COLUMN7
                << TABLE_TABLE_COLUMN8;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 180);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            int points = 3 * record->get(0) + record->get(1);
            int games = record->get(0) + record->get(1) + record->get(2);
            xmlFilter.window->setCellValue(i, 0, record->getString());
            xmlFilter.window->setCellValue(i, 1, QString::number(games));
            for (int k = 0; k < 5; k++) {
                xmlFilter.window->setCellValue(i, 2 + k, QString::number(record->get(k)));
            }
            xmlFilter.window->setCellValue(i, 7, QString("%1").arg(points, 4));
            xmlFilter.window->setCellValue(i, 8, QString("ta02_%1").arg(record->getString()));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(7, Qt::DescendingOrder);
    }

}
