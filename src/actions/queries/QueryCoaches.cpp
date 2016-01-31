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

#include "QueryCoaches.h"

void listOfCoaches(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QString coach1 = xmlFilter.report->getCoach1();
        QString coach1id = xmlFilter.report->getCoach1id();    
        QString coach2 = xmlFilter.report->getCoach2();
        QString coach2id = xmlFilter.report->getCoach2id();
        const QString* score = xmlFilter.report->getScore();
        QString expr = xmlFilter.filter->filter;
        QString key1 = getKeyCoach(xmlFilter.filter->useID, coach1id, coach1, team1);
        QString key2 = getKeyCoach(xmlFilter.filter->useID, coach2id, coach2, team2);
        Record* record1 = NULL;
        if ((expr == "") || coach1.contains(expr)) {
            record1 = Record::getInstance(hash, key1);
            record1->setString(coach1, 0);
            record1->setString(team1, 1);
            record1->add(1);
        }
        Record* record2 = NULL;
        if ((expr == "") || coach2.contains(expr)) {
            record2 = Record::getInstance(hash, key2);
            record2->setString(coach2, 0);
            record2->setString(team2, 1);
            record2->add(1);
        }

        if (*score != "") {
            bool ok;
            int goal1 = 99999;
            int goal2 = 99999;
            goal1 = score->section(':', 0, 0).toInt(&ok);
            goal2 = score->section(':', 1, 1).toInt(&ok);
            if (record1 != NULL) {
                record1->add(goal1, 4);
                record1->add(goal2, 5);
            }
            if (record2 != NULL) {
                record2->add(goal2, 4);
                record2->add(goal1, 5);
            }
            if (goal1 > goal2) {
                if (record1 != NULL) {record1->add(1, 1);}
                if (record2 != NULL) {record2->add(1, 3);}
            } else if (goal2 > goal1) {
                if (record2 != NULL) {record2->add(1, 1);}
                if (record1 != NULL) {record1->add(1, 3);}
            } else {
                if (record2 != NULL) {record2->add(1, 2);}
                if (record1 != NULL) {record1->add(1, 2);}
            }
        }
    } else {
        QStringList titles;
        titles << TABLE_COACHES_COLUMN1
                << TABLE_COACHES_COLUMN2
                << TABLE_COACHES_COLUMN3
                << TABLE_COACHES_COLUMN4
                << TABLE_COACHES_COLUMN5
                << TABLE_COACHES_COLUMN6
                << TABLE_COACHES_COLUMN7
                << TABLE_COACHES_COLUMN8
                << TABLE_COACHES_COLUMN9;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 180);
        xmlFilter.window->widget.table->setColumnWidth(1, 180);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
            xmlFilter.window->setCellValue(i, 3, QString("%1").arg(record->get(1), 4));
            xmlFilter.window->setCellValue(i, 4, QString("%1").arg(record->get(2), 4));
            xmlFilter.window->setCellValue(i, 5, QString("%1").arg(record->get(3), 4));
            xmlFilter.window->setCellValue(i, 6, QString("%1").arg(record->get(4), 4));
            xmlFilter.window->setCellValue(i, 7, QString("%1").arg(record->get(5), 4));
            xmlFilter.window->setCellValue(i, 8, QString("%1").arg(3 * record->get(1) + record->get(2), 4));
            xmlFilter.window->setCellValue(i, 9, QString("co02_%1").arg(record->getString(0)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}
