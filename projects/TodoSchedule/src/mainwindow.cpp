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
    locations << "Home"
              << "School"
              << "Work"
              << "Gym";
    setWindowTitle("My To Do Schedule");
    resize(400, 500);
    //QStringList locations;
    QWidget *central = new QWidget;
    setCentralWidget(central);
    QCalendarWidget *calendar = new QCalendarWidget;
    tasks = new QListWidget;

    tasks->setSelectionMode(
        QAbstractItemView::SingleSelection
        );

    QPushButton *add =
        new QPushButton("Add Task");
    QPushButton *edit =
        new QPushButton("Edit Task");
    QPushButton *remove =
        new QPushButton("Delete Task");

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(calendar);
    layout->addWidget(tasks);
    layout->addWidget(add);
    layout->addWidget(edit);
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
                TaskData data;

                data.date = calendar->selectedDate();
                data.time = QTime::currentTime();

                if (showTaskDialog(data, "New Task"))
                {
                    //if (!data.location.isEmpty() &&
                      //  !locations.contains(data.location))
                    {
                        locations.append(data.location);
                        saveLocations();   // if you have this function
                    }

                    QListWidgetItem *item = new QListWidgetItem(
                        QString("%1  %2  %3")
                            .arg(data.time.toString("hh:mm"))
                            .arg(data.task)
                            .arg(data.location)
                        );

                    item->setData(Qt::UserRole, data.date);
                    item->setData(Qt::UserRole + 1, data.time);
                    item->setData(Qt::UserRole + 2, data.location);

                    item->setCheckState(Qt::Unchecked);

                    tasks->addItem(item);
                    saveTasks();
                }
            });
    connect(edit, &QPushButton::clicked,
            this, &MainWindow::editTask);

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

bool MainWindow::showTaskDialog(TaskData &data,const QString &title)
{
    QDialog dialog(this);
    dialog.setWindowTitle(title);

    QFormLayout form(&dialog);

    QLineEdit *taskEdit = new QLineEdit(data.task);

    QComboBox *locationBox = new QComboBox;
    locationBox->setEditable(true);
    locationBox->addItems(locations);
    locationBox->setCurrentText(data.location);

    QDateEdit *dateEdit = new QDateEdit(data.date);
    dateEdit->setCalendarPopup(true);

    QTimeEdit *timeEdit = new QTimeEdit(data.time);

    form.addRow("Task:", taskEdit);
    form.addRow("Date:", dateEdit);
    form.addRow("Time:", timeEdit);
    form.addRow("Where:", locationBox);

    QDialogButtonBox buttonBox(
        QDialogButtonBox::Ok |
        QDialogButtonBox::Cancel
        );

    form.addWidget(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted,
            &dialog, &QDialog::accept);

    connect(&buttonBox, &QDialogButtonBox::rejected,
            &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted)
        return false;

    data.task = taskEdit->text();
    data.location = locationBox->currentText();
    data.date = dateEdit->date();
    data.time = timeEdit->time();

    return !data.task.isEmpty();
}

void MainWindow::editTask()
{
    QListWidgetItem *item = tasks->currentItem();

    if (!item)
        return;

    TaskData data;

    data.task = item->text().section("  ", 1, 1);
    data.date = item->data(Qt::UserRole).toDate();
    data.time = item->data(Qt::UserRole + 1).toTime();
    data.location = item->data(Qt::UserRole + 2).toString();

    if (showTaskDialog(data, "Edit Task"))
    {
        item->setText(
            QString("%1  %2  %3")
                .arg(data.time.toString("hh:mm"))
                .arg(data.task)
                .arg(data.location)
            );

        item->setData(Qt::UserRole, data.date);
        item->setData(Qt::UserRole + 1, data.time);
        item->setData(Qt::UserRole + 2, data.location);

        saveTasks();
    }
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
void MainWindow::saveLocations()
{
    QFile file("locations.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        for (const QString &location : locations)
            out << location << '\n';
    }
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
