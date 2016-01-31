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

#ifndef CONSTANTS_H
#define	CONSTANTS_H

#include <QHash>
#include <QDate>
#include <QString>

class Record;
typedef QString StatHashKey;
typedef Record StatHashValue;
typedef QHash<StatHashKey, StatHashValue*> StatHash;

const QString FIRST_MESSAGE = QString::fromUtf8(
"<h1 align=\"center\">QFootballStat</h1>"
"<p>Путь к файлу со статистикой: <b>%1</b>.</p>"
"<p>Матчей в базе: <b>%2</b>.</p>"
);
const QString ALL_TOURNAMENTS = QString::fromUtf8("<Все турниры>");

const QString FIND_PLAYER = QString::fromUtf8("Найти игрока");
const QString FIND_COACH = QString::fromUtf8("Найти тренера");
const QString EDIT_REPORT = QString::fromUtf8("Редактировать отчёт");
const QString NEW_REPORT = QString::fromUtf8("Новый отчёт");

const QString EVENT_GOAL = QString::fromUtf8("Гол");
const QString EVENT_GOAL_PENALTY = QString::fromUtf8("Гол с пенальти");
const QString EVENT_AUTOGOAL = QString::fromUtf8("Гол в свои ворота");
const QString EVENT_MISSED_PENALTY = QString::fromUtf8("Незабитый пенальти");
const QString EVENT_SUBSTITUTION = QString::fromUtf8("Замена");
const QString EVENT_YELLOW_CARD = QString::fromUtf8("Предупреждение");
const QString EVENT_RED_CARD = QString::fromUtf8("Удаление");
const QString EVENT_RED_YELLOW_CARD = QString::fromUtf8("Удаление и предупреждение");
const QString EVENT_REPLACE_KEEPER= QString::fromUtf8("Замена вратаря");

const QString STATUS_TIME = QString::fromUtf8("Время: %1 мс.");
const QString STATUS_CALCULATING = QString::fromUtf8("Читаем с диска...");
const QString STATUS_CALCULATING2 = QString::fromUtf8("файлов");
const QString STATUS_CALCULATING_MEMORY = QString::fromUtf8("Читаем из памяти...");
const QString STATUS_CALCULATING_MEMORY2 = QString::fromUtf8("файлов");

const QString TABLE_TABLE_COLUMN1 = QString::fromUtf8("Команда");
const QString TABLE_TABLE_COLUMN2 = QString::fromUtf8("И");
const QString TABLE_TABLE_COLUMN3 = QString::fromUtf8("В");
const QString TABLE_TABLE_COLUMN4 = QString::fromUtf8("Н");
const QString TABLE_TABLE_COLUMN5 = QString::fromUtf8("П");
const QString TABLE_TABLE_COLUMN6 = QString::fromUtf8("Заб.");
const QString TABLE_TABLE_COLUMN7 = QString::fromUtf8("Проп.");
const QString TABLE_TABLE_COLUMN8 = QString::fromUtf8("О");

const QString TABLE_TABLE2_COLUMN1 = QString::fromUtf8("Дата");
const QString TABLE_TABLE2_COLUMN2 = QString::fromUtf8("Город");
const QString TABLE_TABLE2_COLUMN3 = QString::fromUtf8("Хозяева");
const QString TABLE_TABLE2_COLUMN4 = QString::fromUtf8("Гости");
const QString TABLE_TABLE2_COLUMN5 = QString::fromUtf8("Счёт");

const QString TABLE_REFERIES_COLUMN1 = QString::fromUtf8("Судья");
const QString TABLE_REFERIES_COLUMN2 = QString::fromUtf8("Город/Страна");
const QString TABLE_REFERIES_COLUMN3 = QString::fromUtf8("Игр");
const QString TABLE_REFERIES_COLUMN4 = QString::fromUtf8("Красная");
const QString TABLE_REFERIES_COLUMN5 = QString::fromUtf8("Ж+Кр");
const QString TABLE_REFERIES_COLUMN6 = QString::fromUtf8("Жёлтая");
const QString TABLE_REFERIES_COLUMN7 = QString::fromUtf8("Пенальти");

const QString CONTEXT_MENU_REFERIES_NAME1 = QString::fromUtf8("Все матчи");
const QString CONTEXT_MENU_REFERIES_NAME2 = QString::fromUtf8("Матчи с пенальти");
const QString CONTEXT_MENU_REFERIES_ACTION1 = QString::fromUtf8("");
const QString CONTEXT_MENU_REFERIES_ACTION2 = QString::fromUtf8("pen");

const QString TABLE_REFERIES2_COLUMN1 = QString::fromUtf8("Дата");
const QString TABLE_REFERIES2_COLUMN2 = QString::fromUtf8("Город");
const QString TABLE_REFERIES2_COLUMN3 = QString::fromUtf8("Хозяева");
const QString TABLE_REFERIES2_COLUMN4 = QString::fromUtf8("Гости");
const QString TABLE_REFERIES2_COLUMN5 = QString::fromUtf8("Счёт");

const QString TABLE_GOALS_COLUMN1 = QString::fromUtf8("Игрок");
const QString TABLE_GOALS_COLUMN2 = QString::fromUtf8("Команда");
const QString TABLE_GOALS_COLUMN3 = QString::fromUtf8("Мячей");

const QString TABLE_GOALS2_COLUMN1 = QString::fromUtf8("Дата");
const QString TABLE_GOALS2_COLUMN2 = QString::fromUtf8("Город");
const QString TABLE_GOALS2_COLUMN3 = QString::fromUtf8("Хозяева");
const QString TABLE_GOALS2_COLUMN4 = QString::fromUtf8("Гости");
const QString TABLE_GOALS2_COLUMN5 = QString::fromUtf8("Счёт");
const QString TABLE_GOALS2_COLUMN6 = QString::fromUtf8("Мячей");

const QString TABLE_COACHES_COLUMN1 = QString::fromUtf8("Тренер");
const QString TABLE_COACHES_COLUMN2 = QString::fromUtf8("Команда");
const QString TABLE_COACHES_COLUMN3 = QString::fromUtf8("И");
const QString TABLE_COACHES_COLUMN4 = QString::fromUtf8("В");
const QString TABLE_COACHES_COLUMN5 = QString::fromUtf8("Н");
const QString TABLE_COACHES_COLUMN6 = QString::fromUtf8("П");
const QString TABLE_COACHES_COLUMN7 = QString::fromUtf8("Заб.");
const QString TABLE_COACHES_COLUMN8 = QString::fromUtf8("Проп.");
const QString TABLE_COACHES_COLUMN9 = QString::fromUtf8("О");

const QString TABLE_COACHES2_COLUMN1 = QString::fromUtf8("Дата");
const QString TABLE_COACHES2_COLUMN2 = QString::fromUtf8("Город");
const QString TABLE_COACHES2_COLUMN3 = QString::fromUtf8("Хозяева");
const QString TABLE_COACHES2_COLUMN4 = QString::fromUtf8("Гости");
const QString TABLE_COACHES2_COLUMN5 = QString::fromUtf8("Счёт");

const QString TABLE_MATCHES_COLUMN1 = QString::fromUtf8("Дата");
const QString TABLE_MATCHES_COLUMN2 = QString::fromUtf8("Хозяева");
const QString TABLE_MATCHES_COLUMN3 = QString::fromUtf8("Гости");
const QString TABLE_MATCHES_COLUMN4 = QString::fromUtf8("Счёт");

const QString TABLE_STADIUMS_COLUMN1 = QString::fromUtf8("Стадион");
const QString TABLE_STADIUMS_COLUMN2 = QString::fromUtf8("Город");
const QString TABLE_STADIUMS_COLUMN3 = QString::fromUtf8("Матчей");
const QString TABLE_STADIUMS_COLUMN4 = QString::fromUtf8("Зрит(средн)");
const QString TABLE_STADIUMS_COLUMN5 = QString::fromUtf8("Зрит(макс)");
const QString TABLE_STADIUMS_COLUMN6 = QString::fromUtf8("Зрит(мин)");

const QString TABLE_STADIUMS2_COLUMN1 = QString::fromUtf8("Дата");
const QString TABLE_STADIUMS2_COLUMN2 = QString::fromUtf8("Город");
const QString TABLE_STADIUMS2_COLUMN3 = QString::fromUtf8("Хозяева");
const QString TABLE_STADIUMS2_COLUMN4 = QString::fromUtf8("Гости");
const QString TABLE_STADIUMS2_COLUMN5 = QString::fromUtf8("Счёт");

const QString TABLE_PLAYERS_COLUMN1 = QString::fromUtf8("Игрок");
const QString TABLE_PLAYERS_COLUMN2 = QString::fromUtf8("Команда");
const QString TABLE_PLAYERS_COLUMN3 = QString::fromUtf8("Матчей");
const QString TABLE_PLAYERS_COLUMN4 = QString::fromUtf8("Красная");
const QString TABLE_PLAYERS_COLUMN5 = QString::fromUtf8("Ж+Кр");
const QString TABLE_PLAYERS_COLUMN6 = QString::fromUtf8("Жёлтая");
const QString TABLE_PLAYERS_COLUMN7 = QString::fromUtf8("Голы");
const QString TABLE_PLAYERS_COLUMN8 = QString::fromUtf8("Пен(заб)");
const QString TABLE_PLAYERS_COLUMN9 = QString::fromUtf8("Пен(не заб)");
const QString TABLE_PLAYERS_COLUMN10 = QString::fromUtf8("Автогол");

const QString TABLE_PLAYERS2_COLUMN1 = QString::fromUtf8("Дата");
const QString TABLE_PLAYERS2_COLUMN2 = QString::fromUtf8("Город");
const QString TABLE_PLAYERS2_COLUMN3 = QString::fromUtf8("Хозяева");
const QString TABLE_PLAYERS2_COLUMN4 = QString::fromUtf8("Гости");
const QString TABLE_PLAYERS2_COLUMN5 = QString::fromUtf8("Счёт");

const QString TABLE_TEAMS_COLUMN1 = QString::fromUtf8("Команда");
const QString TABLE_TEAMS_COLUMN2 = QString::fromUtf8("Игроков");
const QString TABLE_TEAMS_COLUMN3 = QString::fromUtf8("Красная");
const QString TABLE_TEAMS_COLUMN4 = QString::fromUtf8("Ж+Кр");
const QString TABLE_TEAMS_COLUMN5 = QString::fromUtf8("Жёлтая");
const QString TABLE_TEAMS_COLUMN6 = QString::fromUtf8("Голы");
const QString TABLE_TEAMS_COLUMN7 = QString::fromUtf8("Пен(заб)");
const QString TABLE_TEAMS_COLUMN8 = QString::fromUtf8("Пен(не заб)");
const QString TABLE_TEAMS_COLUMN9 = QString::fromUtf8("Автогол");
const QString TABLE_TEAMS_COLUMN10 = QString::fromUtf8("Пен(соперн)");

const QString TABLE_TEAMS2_COLUMN1 = QString::fromUtf8("Игрок");
const QString TABLE_TEAMS2_COLUMN2 = QString::fromUtf8("Команда");
const QString TABLE_TEAMS2_COLUMN3 = QString::fromUtf8("Матчей");

const QString TABLE_MATCHINFO_COLUMN1 = QString::fromUtf8("Дата");
const QString TABLE_MATCHINFO_COLUMN2 = QString::fromUtf8("Город");
const QString TABLE_MATCHINFO_COLUMN3 = QString::fromUtf8("Хозяева");
const QString TABLE_MATCHINFO_COLUMN4 = QString::fromUtf8("Гости");
const QString TABLE_MATCHINFO_COLUMN5 = QString::fromUtf8("Счёт");

const QString TABLE_CHECKPLAYERS2_COLUMN1 = QString::fromUtf8("Фамилия");
const QString TABLE_CHECKPLAYERS2_COLUMN2 = QString::fromUtf8("Команда");
const QString TABLE_CHECKPLAYERS2_COLUMN3 = QString::fromUtf8("ID1");
const QString TABLE_CHECKPLAYERS2_COLUMN4 = QString::fromUtf8("ID2");

const QString TABLE_SQUAD_COLUMN1 = QString::fromUtf8("Игрок");

const QString TABLE_EVENT_COLUMN1 = QString::fromUtf8("Время");
const QString TABLE_EVENT_COLUMN2 = QString::fromUtf8("Тип события");
const QString TABLE_EVENT_COLUMN3 = QString::fromUtf8("Комментарий");
const QString TABLE_EVENT_COLUMN4 = QString::fromUtf8("Команда");
const QString TABLE_EVENT_COLUMN5 = QString::fromUtf8("Игрок");
const QString TABLE_EVENT_COLUMN6 = QString::fromUtf8("Вышедш.игрок");

const QString CONTEXT_MENU_DEFAULT_NAME = QString::fromUtf8("Подробности");
const QString CONTEXT_MENU_DEFAULT_ACTION = QString::fromUtf8("");

const QDate FIRST_DAY(1800, 1, 1);
const QDate LAST_DAY(2999, 12, 31);

#endif	/* CONSTANTS_H */

