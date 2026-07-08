#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>


MainWindow::MainWindow()
{
    setWindowTitle("My To Do Schedule");
    resize(400, 500);

    QWidget *central = new QWidget;
    setCentralWidget(central);


    tasks = new QListWidget;

    tasks->setSelectionMode(
        QAbstractItemView::SingleSelection
        );


    QPushButton *add =
        new QPushButton("Add Task");

    QPushButton *remove =
        new QPushButton("Delete Task");


    QVBoxLayout *layout =
        new QVBoxLayout;


    layout->addWidget(tasks);
    layout->addWidget(add);
    layout->addWidget(remove);


    central->setLayout(layout);


    connect(add, &QPushButton::clicked,
            this, [=]()
            {
                bool ok;

                QString text =
                    QInputDialog::getText(
                        this,
                        "New Task",
                        "Task:",
                        QLineEdit::Normal,
                        "",
                        &ok
                        );


                if(ok && !text.isEmpty())
                {
                    QListWidgetItem *item =
                        new QListWidgetItem(text);

                    item->setCheckState(
                        Qt::Unchecked
                        );

                    tasks->addItem(item);

                    saveTasks();
                }
            });


    connect(remove, &QPushButton::clicked,
            this, [=]()
            {
                delete tasks->takeItem(
                    tasks->currentRow()
                    );

                saveTasks();
            });


    connect(tasks,
            &QListWidget::itemChanged,
            this,
            [=]()
            {
                saveTasks();
            });


    loadTasks();
}



void MainWindow::saveTasks()
{
    QFile file("tasks.txt");

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);


        for(int i=0;i<tasks->count();i++)
        {
            auto item = tasks->item(i);

            out
                << item->checkState()
                << "|"
                << item->text()
                << "\n";
        }
    }
}



void MainWindow::loadTasks()
{
    QFile file("tasks.txt");

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);


        while(!in.atEnd())
        {
            QString line =
                in.readLine();


            QStringList parts =
                line.split("|");


            if(parts.size()==2)
            {
                QListWidgetItem *item =
                    new QListWidgetItem(
                        parts[1]
                        );


                item->setCheckState(
                    static_cast<Qt::CheckState>(
                        parts[0].toInt()
                        )
                    );


                tasks->addItem(item);
            }
        }
    }
}
