#ifndef DATATYPES_H
#define DATATYPES_H

struct WordTranslationRecord
{
    int countExams;
    int countSuccessExams;
    double successRate;
    QString translation;
    QString word;
};

const int COUNT_WORDS_TO_CHECK = 5;
const QString SECOND_LANGUAGE = "en";
const QString PRIMARY_LANGUAGE = "primaryLanguage";

#endif // DATATYPES_H
