#include "startup.h"
#include "ui_startup.h"

tartup::Startup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Startup)
{
    ui->setupUi(this);
}

Startup::~Startup()
{
    delete ui;
}
