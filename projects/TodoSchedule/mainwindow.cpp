#include "mainwindow.h"

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
#include <QDir>
MainWindow::MainWindow()
{
    setWindowTitle("My To Do Schedule");
    resize(400, 500);

    QWidget *central = new QWidget;
    setCentralWidget(central);

    QCalendarWidget *calendar = new QCalendarWidget;
    tasks = new QListWidget;

    tasks->setSelectionMode(
        QAbstractItemView::SingleSelection
        );

    QPushButton *add =
        new QPushButton("Add Task");

    QPushButton *remove =
        new QPushButton("Delete Task");

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(calendar);
    layout->addWidget(tasks);
    layout->addWidget(add);
    layout->addWidget(remove);
    central->setLayout(layout);

    connect(calendar, &QCalendarWidget::selectionChanged,
            this, [=]()
            {
                QDate selected = calendar->selectedDate();

                for(int i = 0; i < tasks->count(); i++)
                {
                    QListWidgetItem *item = tasks->item(i);

                    bool visible =
                        item->data(Qt::UserRole).toDate() == selected;

                    item->setHidden(!visible);
                }
            });
    connect(add, &QPushButton::clicked,
            this, [=]()
            {
                bool ok;

                QDialog dialog(this);
                dialog.setWindowTitle("New Task");

                QFormLayout form(&dialog);

                QLineEdit *taskEdit = new QLineEdit;
                QLineEdit *locationEdit = new QLineEdit;

                QDateEdit *dateEdit = new QDateEdit(calendar->selectedDate());
                dateEdit->setCalendarPopup(true);

                QTimeEdit *timeEdit = new QTimeEdit(QTime::currentTime());

                form.addRow("Task:", taskEdit);
                form.addRow("Date:", dateEdit);
                form.addRow("Time:", timeEdit);
                form.addRow("Where:", locationEdit);

                QDialogButtonBox buttonBox(
                    QDialogButtonBox::Ok |
                    QDialogButtonBox::Cancel);

                form.addWidget(&buttonBox);

                connect(&buttonBox, &QDialogButtonBox::accepted,
                        &dialog, &QDialog::accept);

                connect(&buttonBox, &QDialogButtonBox::rejected,
                        &dialog, &QDialog::reject);

                if(dialog.exec() == QDialog::Accepted)
                {
                    QString task = taskEdit->text();
                    QString location = locationEdit->text();

                    if(!task.isEmpty())
                    {
                        QListWidgetItem *item = new QListWidgetItem(
                            QString("%1  %2  %3")
                                .arg(timeEdit->time().toString("hh:mm"))
                                .arg(task)
                                .arg(location)
                            );


                        item->setData(Qt::UserRole, dateEdit->date());
                        item->setData(Qt::UserRole + 1, timeEdit->time());
                        item->setData(Qt::UserRole + 2, locationEdit->text());

                        item->setCheckState(Qt::Unchecked);

                        tasks->addItem(item);
                        saveTasks();
                    }
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
    emit calendar->selectionChanged();

}

void MainWindow::saveTasks()
{
    QFile file("tasks.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for (int i = 0; i < tasks->count(); i++)
    {
        QListWidgetItem *item = tasks->item(i);

        QDate date = item->data(Qt::UserRole).toDate();

        QString text = item->text();

        QString time = text.left(5);
        QString task = text.mid(6);
        QString location = text.mid(7);

        out << item->checkState()
            << "|"
            << task
            << "|"
            << date.toString("dd/MM/yyyy")
            << "|"
            << time
            << "\n";
    }

    file.close();
}


void MainWindow::loadTasks()
{
    QFile file("tasks.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QStringList parts = in.readLine().split("|");

        if(parts.size() == 4)
        {
            QListWidgetItem *item =
                new QListWidgetItem(
                    parts[3] + " " + parts[1]
                    );

            item->setCheckState(
                static_cast<Qt::CheckState>(parts[0].toInt())
                );

            item->setData(
                Qt::UserRole,
                QDate::fromString(parts[2], "dd/MM/yyyy")
                );

            tasks->addItem(item);

        }
    }

    file.close();
}
