#ifndef MENU_H
#define MENU_H

#include <QWidget>

class SearchController;
class AddWordController;
class ExamController;

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    ~Menu();
public:
    explicit Menu(QWidget *parent = nullptr);
    void setUpControllers(AddWordController *wordAdder, SearchController *searhController, ExamController *examControlle);

private:
    Ui::Menu *mUi;
    AddWordController *mWordAddController;
    SearchController *mSearchController;
    ExamController *mExamController;

private Q_SLOTS:
    void addWord();
    void search();
    void test();
};

#endif // MENU_H
