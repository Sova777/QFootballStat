TEMPLATE = app
TARGET = qfootballstat
VERSION = 1.0.0
QT += core gui xml
greaterThan(QT_MAJOR_VERSION, 4) {
           QT += widgets
}
#QMAKE_CXXFLAGS = -Wno-unused-parameter
#CONFIG += console
DEPENDPATH += . src
INCLUDEPATH += . src

HEADERS += src/constants.h \
           src/ContextMenu.h \
           src/DumpToHtml.h \
           src/EditReport.h \
           src/Filter.h \
           src/Find.h \
           src/MainWindow.h \
           src/Record.h \
           src/Report.h \
           src/XmlFileReader.h \
           src/XmlFilter.h \
           src/actions/Actions.h \
           src/actions/checkers/CheckAttendance.h \
           src/actions/checkers/CheckPlayers.h \
           src/actions/checkers/CheckPlayers2.h \
           src/actions/queries/QueryCoaches.h \
           src/actions/queries/QueryCoaches2.h \
           src/actions/queries/QueryCoaches3.h \
           src/actions/queries/QueryGoals.h \
           src/actions/queries/QueryGoals2.h \
           src/actions/queries/QueryMatches.h \
           src/actions/queries/QueryPlayers.h \
           src/actions/queries/QueryPlayers2.h \
           src/actions/queries/QueryPlayers3.h \
           src/actions/queries/QueryReferies.h \
           src/actions/queries/QueryReferies2.h \
           src/actions/queries/QueryStadiums.h \
           src/actions/queries/QueryStadiums2.h \
           src/actions/queries/QueryTable.h \
           src/actions/queries/QueryTable2.h \
           src/actions/queries/QueryTeams.h \
           src/actions/queries/QueryTeams2.h

FORMS += src/MainWindow.ui \
         src/EditReport.ui \
         src/Find.ui

SOURCES += src/main.cpp \
           src/ContextMenu.cpp \
           src/DumpToHtml.cpp \
           src/EditReport.cpp \
           src/Filter.cpp \
           src/Find.cpp \
           src/MainWindow.cpp \
           src/Record.cpp \
           src/Report.cpp \
           src/XmlFileReader.cpp \
           src/XmlFilter.cpp \
           src/actions/checkers/CheckAttendance.cpp \
           src/actions/checkers/CheckPlayers.cpp \
           src/actions/checkers/CheckPlayers2.cpp \
           src/actions/queries/QueryCoaches.cpp \
           src/actions/queries/QueryCoaches2.cpp \
           src/actions/queries/QueryCoaches3.cpp \
           src/actions/queries/QueryGoals.cpp \
           src/actions/queries/QueryGoals2.cpp \
           src/actions/queries/QueryMatches.cpp \
           src/actions/queries/QueryPlayers.cpp \
           src/actions/queries/QueryPlayers2.cpp \
           src/actions/queries/QueryPlayers3.cpp \
           src/actions/queries/QueryReferies.cpp \
           src/actions/queries/QueryReferies2.cpp \
           src/actions/queries/QueryStadiums.cpp \
           src/actions/queries/QueryStadiums2.cpp \
           src/actions/queries/QueryTable.cpp \
           src/actions/queries/QueryTable2.cpp \
           src/actions/queries/QueryTeams.cpp \
           src/actions/queries/QueryTeams2.cpp

RESOURCES += src/resources.qrc
RC_FILE += src/QFootballStat.rc
