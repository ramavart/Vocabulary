#ifndef DBCONFIGS_H
#define DBCONFIGS_H

#include <QString>
#include <QStringList>

const QString DATABASE_INSTANCE_NAME =                "vocabulary_test.db";
const QString DATABASE_NAME =                         "QSQLITE";

const QString WORD =                                   "word";
const QString COUNT_EXAMS =                            "countExams";
const QString COUNT_CORRECT_ANSWERS =                  "countCorrectAnswers";
const QString SUCCESS_RATE =                           "successRate";
const QString TRANSLATION =                            "translation";

const QVector<std::pair<QString, QString>> PRIMARY_TABLE_FIELDS = {{WORD, "VARCHAR(30)"},
                                                                   {COUNT_EXAMS, "INT"},
                                                                   {COUNT_CORRECT_ANSWERS, "INT"},
                                                                   {SUCCESS_RATE, "DOUBLE"}};

const QVector<std::pair<QString, QString>> TRANSLATION_TABLE_FIELDS = {{TRANSLATION, "VARCHAR(30)"},
                                                                       {COUNT_EXAMS, "INT"},
                                                                       {COUNT_CORRECT_ANSWERS, "INT"},
                                                                       {SUCCESS_RATE, "DOUBLE"},
                                                                       {WORD, "VARCHAR(30)"}};

#endif // DBCONFIGS_H
