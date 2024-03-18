#include<QDebug>

#include "include/AddWordController.h"
#include "ui_AddWordController.h"
#include "include/MenuController.h"
#include "include/IDatabaseWrapper.h"

using namespace std;

AddWordController::AddWordController(Menu * menu, IDatabaseWrapper *database, QWidget *parent) :
    mMenuController(menu),
    mDatabase(database),
    QWidget(parent),
    mUi(new Ui::AddWordController)
{
    this->setVisible(false);
    mUi->setupUi(this);

    QObject::connect(mUi->pushButton_wordSender, &QPushButton::clicked, this, &AddWordController::addWord);
    QObject::connect(mUi->pushButton_backToMenu, &QPushButton::clicked, this, &AddWordController::backToMenu);
}

void AddWordController::addWord()
{
    if (mUi->lineEdit_word->isModified() && mUi->lineEdit_translation->isModified())
    {
        mDatabase->addWord(PRIMARY_LANGUAGE, mUi->lineEdit_word->text().toLower(), SECOND_LANGUAGE, mUi->lineEdit_translation->text().toLower());
        mUi->lineEdit_word->clear();
        mUi->lineEdit_translation->clear();
    }
}

void AddWordController::backToMenu()
{
    this->setVisible(false);
    mMenuController->setVisible(true);
}

AddWordController::~AddWordController()
{
    delete mUi;
}
