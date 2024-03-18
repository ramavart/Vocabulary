#ifndef IEXAM_H
#define IEXAM_H

#include <bitset>
#include <QVector>

#include "include/DataTypes.h"

class IDatabaseWrapper;

class IExam
{
public:
    virtual ~IExam() = default;

public:
    virtual bool prepare(int countWords, const QString &language, QVector<QString> &worstKnownWords) = 0;
    virtual std::bitset<COUNT_WORDS_TO_CHECK> check(const QVector<QString> &wordsToCheck, QVector<QString> &correctedAnswers) = 0;
    virtual void clear() = 0;
};

#endif // IEXAM_H
