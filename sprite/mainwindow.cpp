#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maineditor.h"
#include "Magick++.h"
#include <iostream>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startup = new StartWindow;

    //****START WINDOW CONNECTIONS***
    connect(startup, SIGNAL(projectCreated()), this, SLOT(startEditing()));
    connect(startup, SIGNAL(projectOpened()), this, SLOT(openSprite()));

    //****BUTTONS ON THE GUI*****
    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteCanvas()));
    connect(ui->colorPushButton, SIGNAL(clicked(bool)), this, SLOT(colorPalette()));
    connect(ui->penButton, SIGNAL(clicked(bool)), this, SLOT(penSelected()));
    connect(ui->eraseRadioButton, SIGNAL(clicked(bool)), this, SLOT(eraserSelected()));
    connect(ui->copyPushButton, SIGNAL(clicked(bool)), this, SLOT(copySelected()));
    connect(ui->pastePushButton, SIGNAL(clicked(bool)), this, SLOT(pasteSelected()));
    connect(ui->addFramePushButton, SIGNAL(clicked(bool)), this, SLOT(addFrame()));
    connect(ui->minusFramePushButton, SIGNAL(clicked(bool)), this, SLOT(deleteFrame()));
    connect(ui->previousFrameButton, SIGNAL(clicked(bool)), this, SLOT(previousFrame()));
    connect(ui->nextFrameButton, SIGNAL(clicked(bool)), this, SLOT(nextFrame()));
    connect(ui->cloneFrameButton, SIGNAL(clicked(bool)), this, SLOT(cloneFrame()));
    connect(ui->exportPushButton, SIGNAL(clicked(bool)), this, SLOT(exportAsGIF()));
    connect(ui->savePushButton, SIGNAL(clicked(bool)),this,SLOT(saveSprite()));

    //*****MENU OPTIONS*********
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(newSprite()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openSprite()));
    connect(ui->actionSave_As, SIGNAL(triggered(bool)), this, SLOT(saveSprite()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(exit()));

    //****SAVED COLOR BUTTONS******
    connect(ui->colorOnePresetPushButton, SIGNAL(clicked(bool)), this, SLOT(setColor()));
    connect(ui->colorTwoPresetPushButton, SIGNAL(clicked(bool)), this, SLOT(setColor()));
    connect(ui->colorThreePresetPushButton, SIGNAL(clicked(bool)), this, SLOT(setColor()));
    connect(ui->colorFourPresetPushButton, SIGNAL(clicked(bool)), this, SLOT(setColor()));
    connect(ui->colorFivePresetPushButton, SIGNAL(clicked(bool)), this, SLOT(setColor()));
    connect(ui->colorSixPresetPushButton, SIGNAL(clicked(bool)), this, SLOT(setColor()));

    //****TOOL BUTTONS*****
    connect(ui->bgFillButton, SIGNAL(clicked(bool)), this, SLOT(setBgColor()));
    connect(ui->largeBrushRadio, SIGNAL(clicked(bool)), this, SLOT(bigBrush()));
    connect(ui->mediumBrushRadio, SIGNAL(clicked(bool)), this, SLOT(mediumBrush()));
    connect(ui->smallBrushRadio, SIGNAL(clicked(bool)), this, SLOT(smallBrush()));

    // Preview connections
    connect(&preview, SIGNAL(updatePreviewWindow(QImage*)), this, SLOT(previewUpdate(QImage*)));

    //set the main image to be the first frame
    editor.mainImage = frames.frames[0];

    //set the editor as the main widget
    ui->scrollArea->setWidget(&editor);
    ui->colorOnePresetPushButton->setStyleSheet(QString("background-color: rgb(0, 0, 0)"));

    //clears the main image, updates gui
    editor.clear();
    updateGui();

    this->setWindowTitle("Spritemare Editor");

    //shows the startup window
    MainWindow::showStartup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showStartup()
{
    startup->show();
    startup->activateWindow();
    this->setEnabled(false);

    startup->move(QApplication::desktop()->screen()->rect().center() - startup->rect().center());
}

void MainWindow::deleteCanvas()
{
    editor.clear();
}

void MainWindow::colorPalette()
{
    QColor color = editor.getColor();
    color = QColorDialog::getColor(color, this, "color palette", 0);
    if (color.isValid())
    {
        editor.setColor(color);
        ui->colorOnePresetPushButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
    }
}

void MainWindow::penSelected()
{
    editor.selectTool(true);
}

void MainWindow::eraserSelected()
{
    editor.selectTool(false);
}

void MainWindow::copySelected()
{
    editor.copy();
}

void MainWindow::pasteSelected()
{
    editor.paste();
}

//adds a frame after the current frame
void MainWindow::addFrame()
{
    frames.insertFrame();
    editor.mainImage = frames.frames[frames.selectedFrame];
    editor.clear();
    editor.update();
    update();
    updateGui();
}

//deletes the current frame and sets the main image to the previous one
void MainWindow::deleteFrame()
{
    frames.deleteFrame();

    editor.mainImage = frames.frames[frames.selectedFrame];
    editor.update();
    update();

    updateGui();
}

//updates the main image to the previous frame
void MainWindow::previousFrame()
{
    if(frames.selectedFrame > 0)
    {
        editor.mainImage = frames.frames[frames.selectedFrame-1];
        editor.update();
        update();
        frames.selectedFrame = frames.selectedFrame -1;
    }
    updateGui();
}

//goes to the next avaialable frame
void MainWindow::nextFrame()
{
    if(frames.selectedFrame < frames.frames.size() - 1)
    {
        editor.mainImage = frames.frames[frames.selectedFrame+1];
        editor.update();
        update();
        frames.selectedFrame = frames.selectedFrame + 1;
    }

    updateGui();
}

//clones a frame, copied the image to the next frame, and sets the main image to the cloned frame
void MainWindow::cloneFrame()
{
    frames.copyFrame();
    editor.mainImage = frames.frames[frames.selectedFrame];
    editor.update();
    update();

    updateGui();
}

//Adjust preview frames per second
void MainWindow::on_fpsSlider_valueChanged(int value)
{
    QString label = QString("FPS: %1").arg(value);
    ui->fpsLabel->setText(label);
    preview.setFPS(value);
}

// Updates preview UI element.
void MainWindow::previewUpdate(QImage* image)
{
   QImage imageDeref = *image;
   QGraphicsScene* scene = new QGraphicsScene(this);
   QPixmap pixmap = QPixmap::fromImage(imageDeref);
   scene->addPixmap(pixmap);
   // Display provided image
   ui->previewGV->setScene(scene);
}

//updates the gui's buttons to what they need to be
void MainWindow::updateGui()
{
    // Update preview frames
    preview.updateFrames(frames.getFrames());

    //update total and current frame labels
    QString totalFramesLabel = QString("Total Frames: %1").arg(frames.getFrameCount());
    QString currentFramesLabel = QString("Frame: %1").arg(frames.getCurrentFrame() + 1);

    ui->frameNumberLabel->setText(totalFramesLabel);
    ui->currentFrameLabel->setText(currentFramesLabel);

    //if the user is on the first frame, disable the delete and previous buttons
    if(frames.selectedFrame==0)
    {
        ui->minusFramePushButton->setEnabled(false);
        ui->previousFrameButton->setEnabled(false);
    }
    else
    {
        ui->minusFramePushButton->setEnabled(true);
        ui->previousFrameButton->setEnabled(true);
    }

    //if the user is on the last frame of the sprite, disable the next button
    if(frames.selectedFrame==frames.frames.size()-1)
    {
        ui->nextFrameButton->setEnabled(false);
    }
    else
    {
        ui->nextFrameButton->setEnabled(true);
    }
}

//exports the current sprite project as an animated GIF
void MainWindow::exportAsGIF()
{
    QString path = QFileDialog::getSaveFileName(this, "Select Export Location", "/", "GIF (*.gif)");
    path.append(".gif");
    int count = frames.getFrameCount();
    std::vector<Magick::Image> framesMagick;
    std::vector<QImage*> framesDrawn = frames.getFrames();

    for(int i = 0; i < count; i++)
    {
        QImage temp = *framesDrawn[i];
        temp.save("image.jpg", 0, -1);
        Magick::Image magickImage("image.jpg");
        magickImage.animationDelay(100 / ui->fpsSlider->value());
        framesMagick.push_back(magickImage);
    }

    Magick::writeImages(framesMagick.begin(), framesMagick.end(), path.toUtf8().constData(), true);
}

//opens the new sprite dialog box and creates a new sprite object
void MainWindow::newSprite()
{
    QMessageBox::StandardButton askUser;
    askUser = QMessageBox::question(this, "New Sprite", "This will delete all data. Would you like to save your current project first?");

    if(askUser == QMessageBox::No)
    {
        frames.frames.clear();
        frames.initFrames();
        frames.selectedFrame = 0;
        updateGui();

        editor.mainImage = frames.frames[0];
        editor.clear();
        editor.update();
        update();

    }
    else if(askUser == QMessageBox::Yes)
    {
        MainWindow::saveSprite();
    }

    //open the startup window and reset the preview sizes
    MainWindow::showStartup();
    ui->previewGV->resetMatrix();
}

//opens a sprite project
void MainWindow::openSprite()
{
    frames.frames.clear();
    frames.initFrames();
    frames.selectedFrame = 0;
    updateGui();

    QString path = QFileDialog::getOpenFileName(this, "Open Image", "/home/tanner/SpriteEditor", "Sprites (*)");
    QFile file( path );
    file.open(QIODevice::ReadWrite);
    QTextStream in(&file);
    QString widthHeight = in.readLine();
    int frameCount = in.readLine().toInt();
    QStringList wHList = widthHeight.split(" ");
    int width = wHList[0].toInt();
    int height = wHList[1].toInt();
    int atRow = 0;
    int onFrame = 0;
    QImage* frame = new QImage(width, height,QImage::Format_ARGB32);

    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        int i = 0;

        while(i < fields.size()-1)
        {
            int red = fields[i].toInt(); i++;
            int green = fields[i].toInt(); i++;
            int blue = fields[i].toInt(); i++;
            int alpha = fields[i].toInt();
            int column = i/4;
            i++;
            QColor pixColor(red, green, blue, alpha);
            QPoint pixel((atRow-(height*onFrame)), column);
            frame->setPixel(pixel, pixColor.rgba());
        }

        if(atRow%height==height-1)
        {
            frames.setCurrentFrame(frame);

            if((atRow+1)/height != frameCount)
            {
                frames.insertFrame();
                frame = new QImage(width, height,QImage::Format_ARGB32);
            }
            onFrame++;
        }
        atRow++;
    }
    file.close();

    frames.resizeFrames(width);
    editor.mainImage = frames.frames[frames.getCurrentFrame()];
    editor.update();
    update();
    updateGui();

    this->setEnabled(true);

    ui->previewGV->resetMatrix();

    //updates the size and preview scale of the opened sprite project
    switch (width)
    {
       case 8:
           startup->size = 0;
           break;
       case 16:
           startup->size = 1;
           break;
       case 32:
           startup->size = 2;
           break;
       case 64:
           startup->size = 3;
           break;
       case 128:
           startup->size = 4;
           break;
       case 256:
           startup->size = 5;
           break;
       case 512:
           startup->size = 6;
           break;
     }

    //set up the sprite editor to start editing
    MainWindow::startEditing();
}

//saves a sprite project
void MainWindow::saveSprite()
{
    QString path = QFileDialog::getSaveFileName(this, "Select Name/Location", "/home", "Sprite (*)");
    int width = editor.mainImage->width();
    int height = editor.mainImage->height();
    int frameCount = frames.getFrameCount();
    QFile file( path );

    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        //stream << startup->name << endl;
        stream << width << " " << height << endl;
        stream <<  frameCount << endl;

        for(int frame=0; frame<frameCount; frame++)
        {
            QImage* image = frames.getFrame(frame);

            for(int row=0; row<width; row++)
            {
                for(int column=0; column<height; column++)
                {
                    QColor color = image->pixel(row, column);
                    //QColor color = image->pixelColor(row, column);
                    stream << color.red() << " " << color.green() << " " << color.blue() << " " << color.alpha() << " ";
                }
                stream << endl;
            }
        }
        file.close();
    }
}

//closes the main window
void MainWindow::exit()
{
    this->close();
}

//sets the current color of the editor
void MainWindow::setColor()
{
    QObject* sender = QObject::sender();

    if(qobject_cast<QWidget*>(sender) != 0)
    {
        QWidget* button = qobject_cast<QWidget*>(sender);
        setColorHelper(button);
    }

}

//helps with color picking buttons
void MainWindow::setColorHelper(QWidget* button)
{
    QString r = QString::number(editor.getColor().red());
    QString g = QString::number(editor.getColor().green());
    QString b = QString::number(editor.getColor().blue());

    button->setStyleSheet(QString("background-color: rgb(" + r + ", " + g + ", " + b +")"));
    button->update();
}

//manages key shortcuts (color selections)
void MainWindow::keyPressEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_1)
    {
        editor.setColor(ui->colorTwoPresetPushButton->palette().color(ui->colorTwoPresetPushButton->backgroundRole()));
        setColorHelper(ui->colorOnePresetPushButton);
    }
    else if(e->key() == Qt::Key_2)
    {
        editor.setColor(ui->colorThreePresetPushButton->palette().color(ui->colorThreePresetPushButton->backgroundRole()));
        setColorHelper(ui->colorOnePresetPushButton);
    }
    else if(e->key() == Qt::Key_3)
    {
        editor.setColor(ui->colorFourPresetPushButton->palette().color(ui->colorFourPresetPushButton->backgroundRole()));
        setColorHelper(ui->colorOnePresetPushButton);
    }
    else if(e->key() == Qt::Key_4)
    {
        editor.setColor(ui->colorFivePresetPushButton->palette().color(ui->colorFivePresetPushButton->backgroundRole()));
        setColorHelper(ui->colorOnePresetPushButton);
    }
    else if(e->key() == Qt::Key_5)
    {
        editor.setColor(ui->colorSixPresetPushButton->palette().color(ui->colorSixPresetPushButton->backgroundRole()));
        setColorHelper(ui->colorOnePresetPushButton);
    }
}

void MainWindow::smallBrush()
{
    editor.brushSize=1;
}

void MainWindow::mediumBrush()
{
    editor.brushSize=2;
}

void MainWindow::bigBrush()
{
    editor.brushSize=3;
}

//sets the background to the current color
void MainWindow::setBgColor(){

    editor.mainImage->fill(editor.getColor());

    editor.update();
    update();
}

//setup the sprite editor for the user to start editing
void MainWindow::startEditing()
{
    QString dim;

    switch (startup->size)
    {
       case 0:
           frames.resizeFrames(8);
           ui->previewGV->scale(21, 21);
           dim = "8 x 8 pixels";
           break;
       case 1:
           frames.resizeFrames(16);
           ui->previewGV->scale(10.5, 10.5);
           dim = "16 x 16 pixels";
           break;
       case 2:
           frames.resizeFrames(32);
           ui->previewGV->scale(5.2, 5.2);
           dim = "32 x 32 pixels";
           break;
       case 3:
           frames.resizeFrames(64);
           ui->previewGV->scale(2.6, 2.6);
           dim = "64 x 64 pixels";
           break;
       case 4:
           frames.resizeFrames(128);
           ui->previewGV->scale(1.3, 1.3);
           dim = "128 x 128 pixels";
           break;
       case 5:
           frames.resizeFrames(256);
           ui->previewGV->scale(0.66, 0.66);
           dim = "256 x 256 pixels";
           break;
       case 6:
           frames.resizeFrames(512);
           ui->previewGV->scale(0.33, 0.33);
           dim = "512 x 512 pixels";
           break;
     }

    QString label = QString("Sprite Size: %1").arg(dim);
    ui->sizeLabel->setText(label);

    projectName = startup->name;

    editor.update();
    update();

    updateGui();

    //enable the main gui
    this->setEnabled(true);
}
