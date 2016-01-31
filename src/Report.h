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

#ifndef REPORT_H
#define	REPORT_H

#include <QDate>
#include <QFile>
#include <QString>
#include <QXmlStreamReader>

class Report {
public:
    struct Player {
        QString id;
        QString player;
    };
    struct Event {
        QString time;
        QString type;
        QString comment;
        QString team;
        QString playerid;
        QString player;
        QString playerid2;
        QString player2;
    };
    void addPlayer1(QXmlStreamReader& xml, QString& id);
    void addPlayer2(QXmlStreamReader& xml, QString& id);
    void addEvent(QXmlStreamReader& xml);
    const QVector<Event>& getEvents() const;
    const QVector<Player>& getPlayers1() const;
    const QVector<Player>& getPlayers2() const;

    void setScoreAttributes(QXmlStreamReader& xml);
    const QString* getScore() const;
    const QString& getGoals1() const;
    const QString& getGoals2() const;
    const QString& getExtra1() const;
    const QString& getExtra2() const;
    const QString& getPenalties1() const;
    const QString& getPenalties2() const;
    void setDateAttributes(QXmlStreamReader& xml);
    const QString& getTime() const;
    void setDate(QXmlStreamReader& xml);
    const QDate& getDate() const;
    void setCoach2Attributes(QXmlStreamReader& xml);
    const QString& getCoach2id() const;
    void setCoach1Attributes(QXmlStreamReader& xml);
    const QString& getCoach1id() const;
    void setCoach2(QXmlStreamReader& xml);
    const QString& getCoach2() const;
    void setCoach1(QXmlStreamReader& xml);
    const QString& getCoach1() const;
    void setTeam2Attributes(QXmlStreamReader& xml);
    const QString& getTeam2id() const;
    void setTeam1Attributes(QXmlStreamReader& xml);
    const QString& getTeam1id() const;
    void setTeam2(QXmlStreamReader& xml);
    const QString& getTeam2() const;
    void setTeam1(QXmlStreamReader& xml);
    const QString& getTeam1() const;
    void setStadium(QXmlStreamReader& xml);
    const QString& getStadium() const;
    void setStadiumAttributes(QXmlStreamReader& xml);
    const QString& getStadiumId() const;
    const QString& getStadiumCity() const;
    const QString& getStadiumAttendance() const;
    void setRefereeAttributes(QXmlStreamReader& xml);
    const QString& getRefereeId() const;
    const QString& getRefereeCity() const;
    const QString& getRefereeCountry() const;
    const QString getRefereeLocation() const;
    void setReferee(QXmlStreamReader& xml);
    const QString& getReferee() const;
    void setMatchAttributes(QXmlStreamReader& xml);
    const QString& getMatchId() const;
    const QString& getMatchRound() const;
    const QString& getMatchTournament() const;
    void setReportId(QFile& file);
    const QString& getReportId() const;

    void setReportId(const QString&);
    void setMatchId(const QString&);
    void setMatchRound(const QString&);
    void setMatchTournament(const QString&);
    void setGoals1(const QString&);
    void setGoals2(const QString&);
    void setExtra1(const QString&);
    void setExtra2(const QString&);
    void setPenalties1(const QString&);
    void setPenalties2(const QString&);
    void setTime(const QString&);
    void setDate(const QDate&);
    void setCoach1id(const QString&);
    void setCoach1(const QString&);
    void setCoach2id(const QString&);
    void setCoach2(const QString&);
    void setTeam1id(const QString&);
    void setTeam1(const QString&);
    void setTeam2id(const QString&);
    void setTeam2(const QString&);
    void setStadiumId(const QString&);
    void setStadium(const QString&);
    void setStadiumCity(const QString&);
    void setStadiumAttendance(const QString&);
    void setRefereeId(const QString&);
    void setReferee(const QString&);
    void setRefereeCity(const QString&);
    void setRefereeCountry(const QString& refereeCountry_);
    void addPlayer1(const QString& id, const QString& player);
    void addPlayer2(const QString& id, const QString& player);
    void addEvent(const QString& type, const QString& time, const QString& team, const QString& comment, const QString& playerid, const QString& player, const QString& playerid2, const QString& player2);

private:
    QString reportId;
    QString team1;
    QString team2;
    QString team1id;
    QString team2id;
    QString coach1;
    QString coach2;
    QString coach1id;
    QString coach2id;
    QDate date;
    QString time;
    QString goals1;
    QString goals2;
    QString extra1;
    QString extra2;
    QString penalties1;
    QString penalties2;
    QString stadium;
    QString stadiumId;
    QString stadiumCity;
    QString stadiumAttendance;
    QString referee;
    QString refereeId;
    QString refereeCity;
    QString refereeCountry;
    QString matchId;
    QString matchRound;
    QString matchTournament;
    QVector<Player> players1;
    QVector<Player> players2;
    QVector<Event> events;
};

#endif	/* REPORT_H */
