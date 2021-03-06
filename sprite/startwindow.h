#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>

namespace Ui {
class StartWindow;
}

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = 0);
    ~StartWindow();

    int size;
    QString name;

public slots:
    void createProject();
    void openProject();
    void setSize();
    void setName();

signals:
    void projectCreated();
    void projectOpened();

private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H
