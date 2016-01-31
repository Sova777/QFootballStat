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

#include "QueryReferies.h"

void listOfReferies(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString name = xmlFilter.report->getReferee();
        QString location = xmlFilter.report->getRefereeLocation();
        QVector<Report::Event> events = xmlFilter.report->getEvents();
        QString key = QString("%1 (%2)").arg(name).arg(location);
        Record* record = Record::getInstance(hash, key);
        record->setString(name, 0);
        record->setString(location, 1);
        record->add(1);

        uint length = events.size();
        for (uint i = 0; i < length; i++) {
            QString eventType = events.at(i).type;
            if (eventType == EVENT_RED_CARD) {
                record->add(1, 1);
            } else if (eventType == EVENT_RED_YELLOW_CARD) {
                record->add(1, 2);
            } else if (eventType == EVENT_YELLOW_CARD) {
                record->add(1, 3);
            } else if ((eventType == EVENT_GOAL_PENALTY) || (eventType == EVENT_MISSED_PENALTY)) {
                record->add(1, 4);
            }
        }
    } else {
        xmlFilter.window->popupMenu.clearMenuItems();
        xmlFilter.window->popupMenu.addMenuItem(CONTEXT_MENU_REFERIES_NAME1, CONTEXT_MENU_REFERIES_ACTION1);
        xmlFilter.window->popupMenu.addMenuItem(CONTEXT_MENU_REFERIES_NAME2, CONTEXT_MENU_REFERIES_ACTION2);
        QStringList titles;
        titles << TABLE_REFERIES_COLUMN1
                << TABLE_REFERIES_COLUMN2
                << TABLE_REFERIES_COLUMN3
                << TABLE_REFERIES_COLUMN4
                << TABLE_REFERIES_COLUMN5
                << TABLE_REFERIES_COLUMN6
                << TABLE_REFERIES_COLUMN7;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 180);
        xmlFilter.window->widget.table->setColumnWidth(1, 180);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, QString("%1").arg(record->get(), 4));
            xmlFilter.window->setCellValue(i, 3, QString("%1").arg(record->get(1), 4));
            xmlFilter.window->setCellValue(i, 4, QString("%1").arg(record->get(2), 4));
            xmlFilter.window->setCellValue(i, 5, QString("%1").arg(record->get(3), 4));
            xmlFilter.window->setCellValue(i, 6, QString("%1").arg(record->get(4), 4));
            xmlFilter.window->setCellValue(i, 7, QString("re02_%1").arg(record->getString(0)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(2, Qt::DescendingOrder);
    }
}
