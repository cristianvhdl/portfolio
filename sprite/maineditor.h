#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include <QWidget>
#include <QColor>
#include <QMouseEvent>
#include <QColorDialog>

class MainEditor : public QWidget
{
    Q_OBJECT
public:
    // constructor
    explicit MainEditor(QWidget *parent = 0);

    // event managers
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void paintEvent(QPaintEvent *);


    // get & set color
    void setColor(QColor);
    QColor getColor();

    int brushSize = 1;

    // toolbox methods
    void draw(QPoint, QColor);
    void clear();
    void selectTool(bool pen);
    void copy();
    void paste();

    // image objects
    QImage* mainImage;
    QImage clipboard;

    // public global variables
    bool penSelected;

public slots:

private:
    // selected color
    QColor color;

    // erase pixel
    void erase(QPoint);

    // helper method for calculating pixel scale
    QPoint scale(QPoint);

    // location of last known mouse location
    QPoint lastLocation;
};

#endif // MAINEDITOR_H
