#include "include/SearchController.h"
#include "include/IDatabaseWrapper.h"
#include "include/MenuController.h"
#include "ui_SearchController.h"

const QString ERROR_MSG = "error_no_such_word";

SearchController::SearchController(Menu *menu, IDatabaseWrapper *databaseWrapper, QWidget *parent) :
    mMenuController(menu),
    mDatabase(databaseWrapper),
    QWidget(parent),
    mUi(new Ui::SearchController)
{
    this->setVisible(false);
    mUi->setupUi(this);
    QObject::connect(mUi->pushButton_search, &QPushButton::clicked, this, &SearchController::search);
    QObject::connect(mUi->pushButton_backToMenu, &QPushButton::clicked, this, &SearchController::backToMenu);
}

void SearchController::search()
{
    if (mUi->lineEdit_word->isModified() || mUi->lineEdit_translation->isModified())
    {
        auto translationPair = mDatabase->findWordTranslation(mUi->lineEdit_word->text().toLower(), SECOND_LANGUAGE);

        if (!translationPair.second.isNull())
        {
            mUi->lineEdit_translation->setText(translationPair.second);
        }
        else
        {
            mUi->lineEdit_translation->setText(ERROR_MSG);
        }

    }
}

void SearchController::backToMenu()
{
    this->setVisible(false);
    mUi->lineEdit_word->clear();
    mUi->lineEdit_translation->clear();
    mMenuController->setVisible(true);
}

SearchController::~SearchController()
{
    delete mUi;
}
