#include "include/ExamController.h"
#include "include/IExam.h"
#include "include/DataTypes.h"
#include "ui_ExamController.h"
#include "include/MenuController.h"

ExamController::ExamController(Menu *menu, IExam *exam, QWidget *parent) :
    mMenuController(menu),
    mExam(exam),
    QWidget(parent),
    mUi(new Ui::ExamController)
{
    this->setVisible(false);
    mUi->setupUi(this);
    QObject::connect(mUi->pushButton_checkResults, &QPushButton::clicked, this, &ExamController::checkAnswers);
    QObject::connect(mUi->pushButton_backToMenu, &QPushButton::clicked, this, &ExamController::backToMenu);
}

ExamController::~ExamController()
{
    delete mUi;
}

void ExamController::prepareTest()
{
    QVector<QString> theWorstKnownWords(COUNT_WORDS_TO_CHECK);
    mExam->prepare(COUNT_WORDS_TO_CHECK, SECOND_LANGUAGE, theWorstKnownWords);
    mUi->lineEdit_word1->setText(theWorstKnownWords[0]);
    mUi->lineEdit_word2->setText(theWorstKnownWords[1]);
    mUi->lineEdit_word3->setText(theWorstKnownWords[2]);
    mUi->lineEdit_word4->setText(theWorstKnownWords[3]);
    mUi->lineEdit_word5->setText(theWorstKnownWords[4]);
    this->setVisible(true);

}

void ExamController::checkAnswers()
{
    QVector<QString> answers(COUNT_WORDS_TO_CHECK);
    QVector<QString> correctAnswers(COUNT_WORDS_TO_CHECK);
    answers[0] = mUi->lineEdit_translation1->text();
    answers[1] = mUi->lineEdit_translation2->text();
    answers[2] = mUi->lineEdit_translation3->text();
    answers[3] = mUi->lineEdit_translation4->text();
    answers[4] = mUi->lineEdit_translation5->text();
    auto results = mExam->check(answers, correctAnswers);

    checkAndSetAlarmColor(results[0], mUi->lineEdit_translation1, mUi->label_correctAnswer1, correctAnswers[0]);
    checkAndSetAlarmColor(results[1], mUi->lineEdit_translation2, mUi->label_correctAnswer2, correctAnswers[1]);
    checkAndSetAlarmColor(results[2], mUi->lineEdit_translation3, mUi->label_correctAnswer3, correctAnswers[2]);
    checkAndSetAlarmColor(results[3], mUi->lineEdit_translation4, mUi->label_correctAnswer4, correctAnswers[3]);
    checkAndSetAlarmColor(results[4], mUi->lineEdit_translation5, mUi->label_correctAnswer5, correctAnswers[4]);
}

void ExamController::checkAndSetAlarmColor(bool result, QWidget *lineEditTranslation, QLabel *labelCorrectAnswer, const QString &answer)
{
    if (!result)
    {
        QPalette pal = QPalette();
        pal.setColor(QPalette::Window, Qt::red);
        lineEditTranslation->setAutoFillBackground(true);
        lineEditTranslation->setPalette(pal);
        labelCorrectAnswer->setText("Correct answer: " + answer);
    }
}

void ExamController::backToMenu()
{
    this->setVisible(false);
    mExam->clear();
    mMenuController->setVisible(true);
}
