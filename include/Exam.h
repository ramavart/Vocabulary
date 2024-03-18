#ifndef EXAM_H
#define EXAM_H

#include "include/IExam.h"

class IDatabaseWrapper;

class Exam : public IExam
{
public:
    Exam(IDatabaseWrapper *databaseWrapper);

public:
    bool prepare(int countWords, const QString &language, QVector<QString> &worstKnownWords) override;
    std::bitset<COUNT_WORDS_TO_CHECK> check(const QVector<QString> &wordsToCheck, QVector<QString> &correctedAnswers) override;
    void clear() override;

private:
    bool mPrepared = false;
    IDatabaseWrapper *m_databaseWrapper;
    QVector<WordTranslationRecord> mWorstKnownWordsRecords;
};

#endif // EXAM_H
