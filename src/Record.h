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

#ifndef _RECORD_H
#define	_RECORD_H

#include <QMap>
#include <QString>
#include "constants.h"

class Record {
private:
    static const int max = 10;
    static const int maxText = 6;
    static int id;
    QString text[maxText];
    int field[max];
    QString key;
    QMap<QString, int> map;
    Record();
public:
    void add(int add, int index = 0);
    int get(int index = 0);
    void set(int value, int index = 0);
    QMap<QString, int>* getMap();
    QString getString(int index = 0);
    void setString(const QString& value, int index = 0);
    static Record* getInstance(StatHash& hash, const StatHashKey& key);
    static Record* getInstance(StatHash* hash, const StatHashKey& key);
    static Record* newInstance(StatHash& hash);
    static Record* newInstance(StatHash* hash);
    static bool less(const Record* left, const Record* right);
};

#endif /* _RECORD_H */
