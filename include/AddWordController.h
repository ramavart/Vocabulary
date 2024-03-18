#ifndef ADDWORDCONTROLLER_H
#define ADDWORDCONTROLLER_H

#include <QWidget>

namespace Ui {
class AddWordController;
}

class IDatabaseWrapper;
class Menu;

class AddWordController : public QWidget
{
    Q_OBJECT

public:
    explicit AddWordController(Menu *menu, IDatabaseWrapper *database, QWidget *parent = nullptr);
    ~AddWordController();

private Q_SLOTS:
    void addWord();
    void backToMenu();

private:
    Menu *mMenuController;
    Ui::AddWordController *mUi;
    IDatabaseWrapper *mDatabase;
};

#endif // ADDWORDCONTROLLER_H
