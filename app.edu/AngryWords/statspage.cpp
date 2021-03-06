#include "statspage.h"
#include "ui_statspage.h"
#include <vector>
#include <string>
#include <qdebug.h>
#include <QScrollBar>
#include <QDesktopWidget>
#include <iostream>


#include <QPushButton>
using namespace std;

StatsPage::StatsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsPage)
{
    ui->setupUi(this);
    connect(ui->statsList->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(drawBack()));
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}

StatsPage::~StatsPage()
{
    delete ui;
}

void StatsPage::showEveryone()
{
    ui->statsList->setStyleSheet("QTableWidget { background: url(:/graphics/graphics/stats_background.png); background-attachment: fixed; }");

    //vector<vector<string> > everyone = server.getEntireDatabase();
    vector<vector<QString> > everyone = db.getEveryonesStats();
    //db.updateStats("1", 23, 1, 1, 1, "asdf", 1);

    int length = 0;
    int width = 0;

    if(!everyone.empty())
    {
        length = everyone.size();
        width = everyone[0].size();
    }

    ui->statsList->setRowCount(length);
    ui->statsList->setColumnCount(width);
    ui->statsList->verticalHeader()->setVisible(false);

    //ui->statsList->horizontalHeader()->setVisible(false);

    QStringList header;
    header << "Username" << "High Score" << "Total Played Time" << "Total Words Hit" << "Total Words Missed" << "Longest Word Hit" << "Longest Streak" << "Person";


    ui->statsList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->statsList->setHorizontalHeaderLabels(header);
    //ui->statsList->resizeColumnsToContents();
    //ui->statsList->resizeRowsToContents();

    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < width; j++)
        {
           QString s (everyone[i][j]);

           if(j + 1 == width)
           {
               if(s.isEmpty())
               {
                   s = QString("Student");
               }
               else
               {
                   s = QString("Teacher");
               }
           }

           QTableWidgetItem *item = new QTableWidgetItem(s);
           item->setTextAlignment(Qt::AlignCenter);

           ui->statsList->setItem(i, j, item);




        }
    }

}

void StatsPage::showStudents(QString teacher)
{
    ui->statsList->setStyleSheet("QTableWidget { background: url(:/graphics/graphics/angrywords_background.png); background-attachment: fixed; }");

    //vector<vector<string> > everyone = server.getEntireDatabase();
    vector<vector<QString> > everyone = db.getTeachersStudentsStats(teacher);
    //db.updateStats("1", 23, 1, 1, 1, "asdf", 1);

    int length = 0;
    int width = 0;

    if(!everyone.empty())
    {
        length = everyone.size();
        width = everyone[0].size();
    }

    ui->statsList->setRowCount(length);
    ui->statsList->setColumnCount(width);
    ui->statsList->verticalHeader()->setVisible(false);

    //ui->statsList->horizontalHeader()->setVisible(false);

    QStringList header;
    header << "Username" << "High Score" << "Total Played Time" << "Total Words Hit" << "Total Words Missed" << "Longest Word Hit" << "Longest Streak" << "Person";


    ui->statsList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->statsList->setHorizontalHeaderLabels(header);
    //ui->statsList->resizeColumnsToContents();
    //ui->statsList->resizeRowsToContents();

    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < width; j++)
        {
           QString s (everyone[i][j]);

           if(j + 1 == width)
           {
               if(s.isEmpty())
               {
                   s = QString("Student");
               }
               else
               {
                   s = QString("Teacher");
               }
           }

           QTableWidgetItem *item = new QTableWidgetItem(s);
           item->setTextAlignment(Qt::AlignCenter);

           ui->statsList->setItem(i, j, item);




        }
    }
}
void StatsPage::drawBack()
{
    QPixmap img(":/graphics/graphics/angrywords_background.png");
    QPalette p = ui->statsList->palette();
    p.setBrush(QPalette::Base, QBrush(img));
}

