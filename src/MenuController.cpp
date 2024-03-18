#include "include/MenuController.h"
#include "ui_MenuController.h"

#include "include/AddWordController.h"
#include "include/SearchController.h"
#include "include/ExamController.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::Menu)
{
    mUi->setupUi(this);
    QObject::connect(mUi->pushButton_AddWord, &QPushButton::clicked, this, &Menu::addWord);
    QObject::connect(mUi->pushButton_findTranslation, &QPushButton::clicked, this, &Menu::search);
    QObject::connect(mUi->pushButton_Test, &QPushButton::clicked, this, &Menu::test);
}

Menu::~Menu()
{
    delete mUi;
}

void Menu::setUpControllers(AddWordController *wordAdder, SearchController *searhController, ExamController *examController)
{
    mWordAddController = wordAdder;
    mSearchController = searhController;
    mExamController = examController;
}

void Menu::addWord()
{
    this->setVisible(false);
    mWordAddController->setVisible(true);
}

void Menu::search()
{
    this->setVisible(false);
    mSearchController->setVisible(true);
}

void Menu::test()
{
    mExamController->prepareTest();
    this->setVisible(false);
    mExamController->setVisible(true);
}
