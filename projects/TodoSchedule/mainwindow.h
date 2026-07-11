#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QDate>
#include <QTime>
#include <QCalendarWidget>
#include <QDebug>
#include <QComboBox>
#include <QDir>
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    struct TaskData
    {
        QString task;
        QString location;
        QDate date;
        QTime time;
    };
    QStringList locations;

private:
    QListWidget *tasks;
    void editTask();
    void saveTasks();
    void loadTasks();
    bool showTaskDialog(TaskData &data, const QString &title);
    void saveLocations();


};

#endif
