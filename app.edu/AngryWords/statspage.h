#ifndef STATSPAGE_H
#define STATSPAGE_H

#include <QWidget>
#include <gameserver.h>
#include <connector.h>

namespace Ui {
class StatsPage;
}

class StatsPage : public QWidget
{
    Q_OBJECT

public:
    explicit StatsPage(QWidget *parent = 0);
    ~StatsPage();
    void showEveryone();
    void showStudents(QString teacher);

    GameServer server;
    Connector db;

signals:
    void valueChanged(int);

private slots:
    void drawBack();

private:
    Ui::StatsPage *ui;
};

#endif // STATSPAGE_H
