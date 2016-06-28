#include "maineditor.h"
#include "QPainter"
#include <QImage>
#include <QDebug>
#include <math.h>

MainEditor::MainEditor(QWidget *parent) : QWidget(parent)
{
    mainImage = new QImage(32, 32, QImage::Format_ARGB32);
    color = QColor(0, 0, 0, 255);
    penSelected=true;
    MainEditor::clear();
}

//calls whenever the user starts drawing
void MainEditor::mousePressEvent(QMouseEvent* event)
{
    penSelected ? draw(event->localPos().toPoint(), color) : erase(event->localPos().toPoint());
    lastLocation = event->localPos().toPoint();
}

//constantly draws whenevr the user is dragging their mouse. Contains algorithm for drawing
void MainEditor::mouseMoveEvent(QMouseEvent* event)
{
    //algorithm for drawing

    // en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    QPoint temp = event->localPos().toPoint();
    double dx = lastLocation.x() - temp.x(), dy = lastLocation.y() - temp.y();
    double error = 0, derror = fabs(dy / dx);
    if(dx == 0)
    {
        int x = temp.x();
        for(int y = temp.y(); y != lastLocation.y(); (temp.y() - lastLocation.y() > 0 ? y-- : y++))
        {
            if(x >= 500 || x < 0 || y >= 500 || y < 0)
            {
                return;
            }
            penSelected ? draw(QPoint(x, y), color) : erase(event->localPos().toPoint());
        }
    }
    else
    {
        int y = temp.y();
        for(int x = temp.x(); x != lastLocation.x(); (temp.x() - lastLocation.x() > 0 ? x-- : x++))
        {
            if(x >= 500 || x < 0 || y >= 500 || y < 0)
            {
                return;
            }
            penSelected ? draw(QPoint(x, y), color) : erase(event->localPos().toPoint());
            error += derror;

            while(error >= 0.5)
            {
                if(x >= 500 || x < 0 || y >= 500 || y < 0)
                {
                    return;
                }
                penSelected ? draw(QPoint(x, y), color) : erase(event->localPos().toPoint());
                lastLocation.y() - temp.y() > 0 ? y++ : y--;
                error -= 1;
            }
        }
    }
    lastLocation = event->localPos().toPoint();
}

//calls whenever the use lifts the mouse
void MainEditor::mouseReleaseEvent(QMouseEvent* event)
{
    penSelected ? draw(event->localPos().toPoint(), color) : erase(event->localPos().toPoint());
}

//manages pain events for painting on the image
void MainEditor::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect rectangle = event->rect();
    painter.drawImage(rectangle, mainImage->scaled(500, 500, Qt::KeepAspectRatio), rectangle);
}

//fills in the pixels at the given point with the given color
void MainEditor::draw(QPoint point, QColor color)
{
    double ratio = 500.0/(mainImage->width());

    if(brushSize>0) //if brush size is 1, draw 1 pixel
    {
        mainImage->setPixel(scale(point), color.rgba());
    }

    if(brushSize>1) //if brush size is 2, draw 4 pixels
    {
        mainImage->setPixel(QPoint((point.x()/ratio)+1, (point.y()/ratio)+1), color.rgba());
        mainImage->setPixel(QPoint((point.x()/ratio)+1, (point.y()/ratio)), color.rgba());
        mainImage->setPixel(QPoint((point.x()/ratio), (point.y()/ratio)+1), color.rgba());
    }

    if(brushSize>2) //if brush size is 3, draw 9 pixels
    {
        mainImage->setPixel(QPoint((point.x()/ratio)-1, (point.y()/ratio)-1), color.rgba());
        mainImage->setPixel(QPoint((point.x()/ratio)-1, (point.y()/ratio)), color.rgba());
        mainImage->setPixel(QPoint((point.x()/ratio), (point.y()/ratio)-1), color.rgba());
        mainImage->setPixel(QPoint((point.x()/ratio)+1, (point.y()/ratio)-1), color.rgba());
        mainImage->setPixel(QPoint((point.x()/ratio)-1, (point.y()/ratio)+1), color.rgba());
    }

    mainImage->alphaChannel().setPixel(scale(point), color.alpha());
    update();
}

//clears the main image
void MainEditor::clear()
{
    mainImage->fill(QColor(255, 255, 255, 0));
    update();
}

//erases the pixel at the given point
void MainEditor::erase(QPoint point)
{
    double ratio = 500.0/(mainImage->width());

    //if brushsize is 1, only erase one pixel
    if(brushSize>0)
    {
        mainImage->setPixel(scale(point), qRgba(255, 255, 255, 0));
    }

    if(brushSize>1) //if brush size is 2, erase 4 pixels
    {
        mainImage->setPixel(QPoint((point.x()/ratio)+1, (point.y()/ratio)+1), qRgba(255, 255, 255, 0));
        mainImage->setPixel(QPoint((point.x()/ratio)+1, (point.y()/ratio)), qRgba(255, 255, 255, 0));
        mainImage->setPixel(QPoint((point.x()/ratio), (point.y()/ratio)+1), qRgba(255, 255, 255, 0));
    }

    if(brushSize>2) //if brush size is 3, erase 9 pixels
    {
        mainImage->setPixel(QPoint((point.x()/ratio)-1, (point.y()/ratio)-1), qRgba(255, 255, 255, 0));
        mainImage->setPixel(QPoint((point.x()/ratio)-1, (point.y()/ratio)), qRgba(255, 255, 255, 0));
        mainImage->setPixel(QPoint((point.x()/ratio), (point.y()/ratio)-1), qRgba(255, 255, 255, 0));
        mainImage->setPixel(QPoint((point.x()/ratio)+1, (point.y()/ratio)-1), qRgba(255, 255, 255, 0));
        mainImage->setPixel(QPoint((point.x()/ratio)-1, (point.y()/ratio)+1), qRgba(255, 255, 255, 0));
    }

    mainImage->setPixel(scale(point), qRgba(255, 255, 255, 0));
    mainImage->alphaChannel().setPixel(scale(point), QColor(255, 255, 255, 0).alpha());
    update();
}

//sets the current color
void MainEditor::setColor(QColor c)
{
    color = c;
}

//returns the current color
QColor MainEditor::getColor()
{
    return color;
}

//scales the image by the correct factor (500)
QPoint MainEditor::scale(QPoint point)
{
    double ratio = 500.0/(mainImage->width());
    return QPoint((point.x()/ratio), (point.y()/ratio));
}

//boolean for tool selection determines what is drawn or erased
void MainEditor::selectTool(bool pen)
{
    if(pen)
        penSelected = true;
    else
        penSelected = false;
}

//copies the main image to the clipboard
void MainEditor::copy()
{
  clipboard = mainImage->copy();
}

//pastes whatever is on the clipboard to the main image
void MainEditor::paste()
{
    QPainter painter(mainImage);
    painter.drawImage(0,0, clipboard);
    painter.end();
    update();
}
