#ifndef DATABASEWRAPPER_H
#define DATABASEWRAPPER_H

#include <QSqlDatabase>

#include "IDatabaseWrapper.h"

class DatabaseWrapper : public IDatabaseWrapper
{
public:
    ~DatabaseWrapper() override;

public:
    void init(const QString &databaseInstanceName, const QString &databaseName) override;
    void addWord(const QString &wordLanguage, const QString &word, const QString &languageOfTranslation, const QString &translation) override;
    QVector<WordTranslationRecord> getWorstRateWords(const QString &language, int countWords) override;
    void updateStatsForWord(const QString &language, const WordTranslationRecord &wordTranslationRecord) override;
    std::pair<QString, QString> findWordTranslation(const QString &word, const QString &languageOfTranslation) override;

private:
    bool openDb();
    void closeDb();
    void createTable(const QString &tableName, bool isPrimaryLanguage);
    bool doesTableExist(const QString &tableName);
    void debugQuery(const QSqlQuery &query, const QString &contextLog);

private:
    QSqlDatabase mDb;
    QString mDatabaseInstanceName;
    QString mDatabaseName;
    QString mPrimaryTableName;
};

#endif // DATABASEWRAPPER_H
