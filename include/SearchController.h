#ifndef SEARCHCONTROLLER_H
#define SEARCHCONTROLLER_H

#include <QWidget>

class IDatabaseWrapper;
class Menu;

namespace Ui {
class SearchController;
}

class SearchController : public QWidget
{
    Q_OBJECT

public:
    explicit SearchController(Menu* menuController, IDatabaseWrapper* database, QWidget *parent = nullptr);
    ~SearchController();

private Q_SLOTS:
    void search();
    void backToMenu();

private:
    Ui::SearchController *mUi;
    IDatabaseWrapper *mDatabase;
    Menu *mMenuController;
};

#endif // TRANSLATIONSEARCHCONTROLLER_H
