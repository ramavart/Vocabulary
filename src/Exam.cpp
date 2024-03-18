#include <QDebug>

#include "include/Exam.h"
#include "include/IDatabaseWrapper.h"

using namespace std;

Exam::Exam(IDatabaseWrapper *databaseWrapper) :m_databaseWrapper(databaseWrapper)
{
}

bool Exam::prepare(int countWords,const QString &language, QVector<QString> &worstKnownWords)
{
    if (!mPrepared)
    {
        mWorstKnownWordsRecords = m_databaseWrapper->getWorstRateWords(language, countWords);

        for (int i = 0; i < countWords; i++)
        {
            worstKnownWords[i] = mWorstKnownWordsRecords[i].word;
        }
        mPrepared = true;
    }
    return mPrepared;
}

bitset<COUNT_WORDS_TO_CHECK> Exam::check(const QVector<QString> &wordsToCheck, QVector<QString> &correctedAnswers)
{
    bitset<COUNT_WORDS_TO_CHECK> result;

    if (correctedAnswers.size()<COUNT_WORDS_TO_CHECK)
    {
        correctedAnswers.resize(COUNT_WORDS_TO_CHECK);
    }

    if (mPrepared)
    {
        for(size_t i = 0; i < wordsToCheck.size(); i++)
        {
            if (wordsToCheck[i] == mWorstKnownWordsRecords[i].translation)
            {
                result.set(i, true);
                mWorstKnownWordsRecords[i].countSuccessExams++;
            }
            else
            {
                result.set(i, false);
            }
            correctedAnswers[i] = mWorstKnownWordsRecords[i].translation;
            mWorstKnownWordsRecords[i].countExams++;
            mWorstKnownWordsRecords[i].successRate = static_cast<double>(mWorstKnownWordsRecords[i].countSuccessExams)/static_cast<double>(mWorstKnownWordsRecords[i].countExams);
            m_databaseWrapper->updateStatsForWord(SECOND_LANGUAGE, mWorstKnownWordsRecords[i]);
        }
    }
    clear();
    return result;
}

void Exam::clear()
{
    mWorstKnownWordsRecords.clear();
    mPrepared = false;
}
