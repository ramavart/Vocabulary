#include <QApplication>

#include "include/MainWindow.h"
#include "include/MenuController.h"
#include "include/DatabaseWrapper.h"
#include "include/AddWordController.h"
#include "include/SearchController.h"
#include "include/ExamController.h"
#include "include/DbConfigs.h"
#include "include/Exam.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Menu menu(&w);

    DatabaseWrapper databaseWrapper;
    databaseWrapper.init(DATABASE_INSTANCE_NAME, DATABASE_NAME);
    SearchController searchController(&menu, &databaseWrapper, &w);
    AddWordController wordAdder(&menu, &databaseWrapper, &w);
    Exam exam(&databaseWrapper);
    ExamController examController(&menu, &exam, &w);
    menu.setUpControllers(&wordAdder, &searchController, &examController);

    w.show();
    return a.exec();
}
