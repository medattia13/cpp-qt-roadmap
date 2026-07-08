#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    QListWidget *tasks;

    void saveTasks();
    void loadTasks();
};

#endif
