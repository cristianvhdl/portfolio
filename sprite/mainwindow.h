#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maineditor.h"
#include "frames.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QRgb>
#include <QStringList>
#include "startwindow.h"
#include "preview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* e);

    void showStartup();
    void resize(int&);
    int dimensions;
    QString projectName;

private slots:

    //slots for color selection
    void colorPalette();
    void setColor();

    //slots for all the tools
    void deleteCanvas();
    void penSelected();
    void eraserSelected();
    void copySelected();
    void pasteSelected();
    void setBgColor();

    //slots for the frame controls
    void addFrame();
    void deleteFrame();
    void previousFrame();
    void nextFrame();
    void cloneFrame();

    //slots for opening/saving and exporting
    void exportAsGIF();
    void newSprite();
    void openSprite();
    void saveSprite();
    void exit();

    //slots for brush size options
    void bigBrush();
    void mediumBrush();
    void smallBrush();

    //updates the gui whenever called. Useful to call whenever the frame buttons are pressed
    void updateGui();

    void startEditing();

    void on_fpsSlider_valueChanged(int value);

    void previewUpdate(QImage* image);

private:
    Ui::MainWindow *ui;
    MainEditor editor;
    Frames frames;
    void setColorHelper(QWidget* button);

    StartWindow *startup;

    Preview preview;

};

#endif // MAINWINDOW_H
