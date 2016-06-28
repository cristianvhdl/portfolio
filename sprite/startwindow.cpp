#include "startwindow.h"
#include "ui_startwindow.h"
#include <QDesktopWidget>

StartWindow::StartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Welcome to Spritemare!");

    //****COMBO BOX OPTIONS****
    ui->spriteSizeComboBox->addItem("8 x 8 pixels");
    ui->spriteSizeComboBox->addItem("16 x 16 pixels");
    ui->spriteSizeComboBox->addItem("32 x 32 pixels");
    ui->spriteSizeComboBox->addItem("64 x 64 pixels");
    ui->spriteSizeComboBox->addItem("128 x 128 pixels");
    ui->spriteSizeComboBox->addItem("256 x 256 pixels");
    ui->spriteSizeComboBox->addItem("512 x 512 pixels");

    ui->spriteSizeComboBox->setCurrentIndex(2);

    //****CONNECTIONS FROM THE BUTTONS TO TO THE MAIN WINDOW****
    connect(ui->createProjectButton, SIGNAL(clicked(bool)), this, SLOT(createProject()));
    connect(ui->openProjectButton, SIGNAL(clicked(bool)), this, SLOT(openProject()));

    //****SETS THE NAME AND SIZE THAT THE USER CHOOSES****
    connect(ui->projectNameTextBox, SIGNAL(textChanged()), this, SLOT(setName()));
    connect(ui->spriteSizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setSize()));

    //setting default values
    name = "Untitled";
    size = 2;
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::setName()
{
    name = this->ui->projectNameTextBox->toPlainText();
}

void StartWindow::setSize()
{
    size = this->ui->spriteSizeComboBox->currentIndex();
}

//emits the signal to the main window to create a project and closes the startup window
void StartWindow::createProject()
{
    emit projectCreated();
    this->close();
}

//emits the signal to the mainwindow to open a project and closes the startup window
void StartWindow::openProject()
{
    emit projectOpened();
    this->close();
}
