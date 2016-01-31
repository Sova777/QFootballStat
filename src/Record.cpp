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

#include <QHash>
#include "XmlFileReader.h"
#include "Record.h"

int Record::id = 0;

Record::Record() {
    for (int i = 0; i < maxText; i++) {
        this->text[i] = "";
    }
    for (int i = 0; i < max; i++) {
        field[i] = 0;
    }
}

void Record::add(int add, int index) {
    if (index >= max) {
        throw 0;
    }
    field[index] += add;
}

int Record::get(int index) {
    if (index >= max) {
        throw 0;
    }
    return field[index];
}

void Record::set(int value, int index) {
    if (index >= max) {
        throw 0;
    }
    field[index] = value;
}

QString Record::getString(int index) {
    if (index >= maxText) {
        throw 0;
    }
    return text[index];
}

void Record::setString(const QString& value, int index) {
    if (index >= maxText) {
        throw 0;
    }
    text[index] = value;
}

bool Record::less(const Record* left, const Record* right) {
    return (right->field[0]) < (left->field[0]);
}

Record* Record::getInstance(StatHash& hash, const StatHashKey& key) {
    if (!hash.contains(key)) {
        hash.insert(key, new Record());
    }
    Record* record = hash.value(key);
    record->key = key;
    return record;
}

Record* Record::getInstance(StatHash* hash, const StatHashKey& key) {
    if (!hash->contains(key)) {
        hash->insert(key, new Record());
    }
    Record* record = hash->value(key);
    record->key = key;
    return record;
}

Record* Record::newInstance(StatHash& hash) {
    QString key = QString::number(id);
    while (hash.contains(key)) {
        id++;
        key = QString::number(id);
    }
    hash.insert(key, new Record());
    Record* record = hash.value(key);
    record->key = key;
    return record;
}

Record* Record::newInstance(StatHash* hash) {
    QString key = QString::number(id);
    while (hash->contains(key)) {
        id++;
        key = QString::number(id);
    }
    hash->insert(key, new Record());
    Record* record = hash->value(key);
    record->key = key;
    return record;
}

QMap<QString, int>* Record::getMap() {
    return &map;
}
