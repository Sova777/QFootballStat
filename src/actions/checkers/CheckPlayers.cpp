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

#include "CheckPlayers.h"

void checkListOfPlayers(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QVector<Report::Player> players1 = xmlFilter.report->getPlayers1();
        QVector<Report::Player> players2 = xmlFilter.report->getPlayers2();
        uint len1 = players1.size();
        uint len2 = players2.size();
        if ((len1 != 11) || (len2 != 11)) {
            addMatch(*(xmlFilter.report), *(xmlFilter.fileName), hash);
        }
    } else {
        QStringList titles;
        titles << TABLE_MATCHINFO_COLUMN1
                << TABLE_MATCHINFO_COLUMN2
                << TABLE_MATCHINFO_COLUMN3
                << TABLE_MATCHINFO_COLUMN4
                << TABLE_MATCHINFO_COLUMN5;
        xmlFilter.window->initTable(titles, 120, hash->size());

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, record->getString(2));
            xmlFilter.window->setCellValue(i, 3, record->getString(3));
            xmlFilter.window->setCellValue(i, 4, record->getString(4));
            xmlFilter.window->setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}
