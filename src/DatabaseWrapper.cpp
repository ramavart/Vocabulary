#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

#include "include/DatabaseWrapper.h"
#include "include/DbConfigs.h"

void DatabaseWrapper::init(const QString &databaseInstanceName, const QString &databaseName)
{
    mDb = QSqlDatabase::addDatabase(databaseName);
    mDatabaseInstanceName = databaseInstanceName;
    mDatabaseName = databaseName;
    mDb.setDatabaseName(databaseInstanceName);
    mDb.open();
    if (QFile::exists(databaseInstanceName))
    {
        qDebug() << "Database " << databaseInstanceName << " created";
    }
    mDb.close();
}

DatabaseWrapper::~DatabaseWrapper()
{
    closeDb();
}

void DatabaseWrapper::addWord(const QString &wordLanguage, const QString &word, const QString &languageOfTranslation, const QString &translation)
{
    if (!doesTableExist(wordLanguage))
    {
        createTable(wordLanguage, true);
    }

    if (!doesTableExist(languageOfTranslation))
    {
        createTable(languageOfTranslation, false);
    }

    if (openDb())
    {
        QString addWordCommad = QString("INSERT INTO %0 (%1, %2, %3, %4) VALUES (?, '0', '0', '0.0');").arg(wordLanguage).arg(WORD).arg(COUNT_EXAMS).arg(COUNT_CORRECT_ANSWERS).arg(SUCCESS_RATE);
        QSqlQuery addWord;
        addWord.prepare(addWordCommad);
        addWord.bindValue(0, word);
        if (!addWord.exec())
        {
            debugQuery(addWord, "Unable to insert word");
        }

        QString addTranslationCommand = QString("INSERT INTO %0 (%1, %2, %3, %4, %5) VALUES (?, '0', '0', '0.0', ?);").arg(languageOfTranslation).arg(TRANSLATION).arg(COUNT_EXAMS).arg(COUNT_CORRECT_ANSWERS).arg(SUCCESS_RATE).arg(WORD);
        QSqlQuery addTranslation;
        if (!addTranslation.prepare(addTranslationCommand))
        {
            qDebug() << "Cannot be executed" << endl;
        }

        addTranslation.bindValue(0, translation);
        addTranslation.bindValue(1, word);
        if (!addTranslation.exec())
        {
            debugQuery(addTranslation, "Unable to insert word");
        }
    }
    else
    {
        qDebug() << "Word cannot be added. Database failed to open";
    }
    closeDb();
}

void DatabaseWrapper::createTable(const QString &tableName, bool isPrimaryLanguage)
{
    if (openDb())
    {
        QString createTableCommand;
        if (isPrimaryLanguage)
        {
            createTableCommand = QString("CREATE TABLE %1 ( %2 %3 PRIMARY KEY, %4 %5, %6 %7, %8 %9);").arg(tableName)
                    .arg(PRIMARY_TABLE_FIELDS[0].first)
                    .arg(PRIMARY_TABLE_FIELDS[0].second)
                    .arg(PRIMARY_TABLE_FIELDS[1].first)
                    .arg(PRIMARY_TABLE_FIELDS[1].second)
                    .arg(PRIMARY_TABLE_FIELDS[2].first)
                    .arg(PRIMARY_TABLE_FIELDS[2].second)
                    .arg(PRIMARY_TABLE_FIELDS[3].first)
                    .arg(PRIMARY_TABLE_FIELDS[3].second);
        }
        else
        {
            createTableCommand = QString("CREATE TABLE %1 (%2 %3 PRIMARY KEY, %4 %5, %6 %7, %8 %9, %10 %11, FOREIGN KEY (%12) REFERENCES %13 (%14));").arg(tableName)
                    .arg(TRANSLATION_TABLE_FIELDS[0].first)
                    .arg(TRANSLATION_TABLE_FIELDS[0].second)
                    .arg(TRANSLATION_TABLE_FIELDS[1].first)
                    .arg(TRANSLATION_TABLE_FIELDS[1].second)
                    .arg(TRANSLATION_TABLE_FIELDS[2].first)
                    .arg(TRANSLATION_TABLE_FIELDS[2].second)
                    .arg(TRANSLATION_TABLE_FIELDS[3].first)
                    .arg(TRANSLATION_TABLE_FIELDS[3].second)
                    .arg(TRANSLATION_TABLE_FIELDS[4].first)
                    .arg(TRANSLATION_TABLE_FIELDS[4].second)
                    .arg(TRANSLATION_TABLE_FIELDS[4].first)
                    .arg(PRIMARY_LANGUAGE)
                    .arg(PRIMARY_TABLE_FIELDS[0].first);

        }
        QSqlQuery query(mDb);

        query.prepare(createTableCommand);
        if (!query.exec())
        {
            debugQuery(query, "Unable to create a table");
        }
    }
    else
    {
        qDebug() << "Tables cannot be created. Database openning failed";
    }
    closeDb();
}

QVector<WordTranslationRecord> DatabaseWrapper::getWorstRateWords(const QString &language, int countWords)
{
    QVector<WordTranslationRecord> translationRecors(countWords);
    if (openDb())
    {
        QString queryString = QString("SELECT * FROM %1 ORDER BY %2 ASC LIMIT %3;").arg(language).arg(SUCCESS_RATE).arg(countWords);
        QSqlQuery query;
        query.prepare(queryString);
        if (!query.exec())
        {
            debugQuery(query, "Unable to get worst rating words");
        }
        else
        {
            for(int i = 0; i < countWords; i++)
            {
                query.next();
                QSqlRecord rec = query.record();
                translationRecors[i].countExams = rec.value(1).toInt();
                translationRecors[i].countSuccessExams = rec.value(2).toInt();
                translationRecors[i].successRate = rec.value(3).toInt();
                translationRecors[i].translation = rec.value(0).toString();
                translationRecors[i].word = rec.value(4).toString();
            }
        }
    }
    else
    {
        qDebug() << "Cannot receive word and rating. Database failed to open";
    }

    closeDb();
    return translationRecors;
}

void DatabaseWrapper::updateStatsForWord(const QString &language, const WordTranslationRecord &wordTranslationRecord)
{
    if (openDb())
    {
        QString updateQuery = QString("UPDATE %1 SET %2 = ? , %3 = ? , %4 = ? WHERE %5 == ?").arg(language).arg(COUNT_EXAMS).arg(COUNT_CORRECT_ANSWERS).arg(SUCCESS_RATE).arg(WORD);
        QSqlQuery query;
        query.prepare(updateQuery);
        query.bindValue(0, wordTranslationRecord.countExams);
        query.bindValue(1, wordTranslationRecord.countSuccessExams);
        query.bindValue(2, wordTranslationRecord.successRate);
        query.bindValue(3, wordTranslationRecord.word);

        if (!query.exec())
        {
            debugQuery(query, "Unable to update stats for word");
        }
    }
    else
    {
        qDebug() << "Cannot update stats for word. Database failed to open";
    }

    closeDb();
}

std::pair<QString, QString> DatabaseWrapper::findWordTranslation(const QString &word, const QString &languageOfTranslation)
{
    QString translationResult;
    if (openDb())
    {
        QString searchCommand= QString("SELECT %1 FROM %2 WHERE %3 == ?;").arg(TRANSLATION).arg(languageOfTranslation).arg(WORD);

        QSqlQuery query;
        query.prepare(searchCommand);
        query.bindValue(0,word);
        if (!query.exec())
        {
            debugQuery(query, "Unable to transalte word");
        }
        else
        {
            while (query.next())
            {
                QSqlRecord rec = query.record();
                translationResult = rec.value(0).toString();
            }
        }
    }
    else
    {
        qDebug() << "Cannot translate word. Database failed to open";
    }
    closeDb();

    return {word, translationResult};
}

bool DatabaseWrapper::openDb()
{
    bool res;
    if (!mDb.isOpen())
    {
        res = mDb.open();
    }
    else
    {
        res = true;
    }
    return res;

}
void DatabaseWrapper::closeDb()
{
    if (mDb.isOpen())
    {
        mDb.close();
    }
}

bool DatabaseWrapper::doesTableExist(const QString &tableName)
{
    openDb();
    auto tablesList = mDb.tables();
    closeDb();
    return tablesList.contains(tableName);
}

void DatabaseWrapper::debugQuery(const QSqlQuery &query, const QString &contextLog)
{
    qDebug() << contextLog;
    qDebug() << query.executedQuery().toLatin1().data();
    qDebug() << query.lastError().number() << " " <<query.lastError().text();
}
