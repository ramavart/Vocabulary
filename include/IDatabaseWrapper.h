#ifndef IDATAPROCESSOR_H
#define IDATAPROCESSOR_H

#include <QString>
#include <QStringList>
#include <QVector>

#include "include/DataTypes.h"

class IDatabaseWrapper
{

public:
    virtual ~IDatabaseWrapper() = default;
    virtual void init(const QString &databaseInstanceName, const QString &databaseName) = 0;
    virtual void addWord(const QString &wordLanguage, const QString &word, const QString &languageOfTranslation, const QString &translation) = 0;
    virtual QVector<WordTranslationRecord> getWorstRateWords(const QString &language, int countWords) = 0;
    virtual void updateStatsForWord(const QString &language, const WordTranslationRecord &wordTranslationRecord) = 0;
    virtual std::pair<QString, QString> findWordTranslation(const QString &word, const QString &languageOfTranslation) = 0;
};

#endif // IDATAPROCESSOR_H
