#ifndef EXAMCONTROLLER_H
#define EXAMCONTROLLER_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class ExamController;
}

class Menu;
class IExam;

class ExamController : public QWidget
{
    Q_OBJECT

public:
    explicit ExamController(Menu *menu, IExam *exam, QWidget *parent = nullptr);
    ~ExamController();

public Q_SLOTS:
    void prepareTest();
    void checkAnswers();
    void backToMenu();

private:
    void checkAndSetAlarmColor(bool result, QWidget *widget, QLabel *labelCorrectAnswer, const QString &answer);
private:
    Menu *mMenuController;
    IExam *mExam;
    Ui::ExamController *mUi;
};

#endif // EXAMCONTROLLER_H
