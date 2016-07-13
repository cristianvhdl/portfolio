#include "welcomescreen.h"
#include "ui_welcomescreen.h"
#include <QDesktopWidget>
#include <iostream>
#include <connector.h>

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);
    // Button Connections
    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(playButtonClicked()));
    connect(ui->guestButton, SIGNAL(clicked(bool)), this, SLOT(guestButtonClicked()));
    connect(ui->statsButton, SIGNAL(clicked(bool)), this, SLOT(statsButtonClicked()));
    connect(ui->teacherStatsButton, SIGNAL(clicked(bool)), this, SLOT(teacherStatsButtonClicked()));
    gameWindow = new GameWindow();
    //gameWinow->setEnabled(false);
    this->setEnabled(true);
    this->setFocus();
    //Game Screen Connections
    connect(this, SIGNAL(playGame()), gameWindow, SLOT(startGame()));
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,800,500);
    this->ui->welcomeGraphic->setScene(scene);
    this->ui->welcomeGraphic->setBackgroundBrush(QBrush(QPixmap(":/graphics/graphics/login_background.png")));
    //this->setFocus();
    this->ui->pass_Label->setStyleSheet("QLabel { color : white; }");
    this->ui->username_label->setStyleSheet("QLabel { color : white; }");
    this->ui->teacher_label->setStyleSheet("QLabel { color : white; }");
    this->ui->teacher_label_2->setStyleSheet("QLabel { color : white; }");
    this->ui->label->setStyleSheet("QLabel { color : white; }");
    this->ui->label_2->setStyleSheet("QLabel { color : white; }");
    this->ui->teacher_label_3->setStyleSheet("QLabel { color : white; }");
    //ui->invalid_label->setStyleSheet("QLabel { color : white; }");
    //ui->teacherBox->setStyleSheet("QCheckBox { color : green;}");


    //button hovering effects:
    setButtonIcon(ui->playButton,":/graphics/graphics/play_button.png",155,60);
    setButtonIcon(ui->guestButton,":/graphics/graphics/guest_button.png",170,40);
    setButtonIcon(ui->soundButton,":/graphics/graphics/sound_button.png",85,35);
    setButtonIcon(ui->musicButton,":/graphics/graphics/music_button.png",85,35);
    setButtonIcon(ui->statsButton,":/graphics/graphics/stats_button.png",105,45);
    setButtonIcon(ui->teacherStatsButton,":/graphics/graphics/stats_button.png",105,45);


    ui->playButton->installEventFilter(this);
    ui->guestButton->installEventFilter(this);
    ui->soundButton->installEventFilter(this);
    ui->musicButton->installEventFilter(this);
    ui->statsButton->installEventFilter(this);
    ui->teacherStatsButton->installEventFilter(this);

    ui->playButton->setEnabled(false);

    ui->musicButton->hide();
    ui->soundButton->hide();
    ui->teacherStatsButton->hide();
    ui->teacher_label_2->hide();


    ui->studentBox->setChecked(true);




    connect(gameWindow, SIGNAL(mainMenu()), this, SLOT(showMainMenu()));


    difficultyOption = 0;


    //themeSong.play();
}

WelcomeScreen::~WelcomeScreen()
{
    delete ui;
}

void WelcomeScreen::setButtonIcon(QPushButton *button, QString filename, int sizeX, int sizeY)
{
    QPixmap pixmap(filename);
    pixmap = pixmap.scaled(sizeX,sizeY);
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());
}

void WelcomeScreen::showMainMenu()
{
    this->show();
    this->setEnabled(true);
    gameWindow->close();
    gameWindow = new GameWindow();
    //Game Screen Connections
    connect(this, SIGNAL(playGame()), gameWindow, SLOT(startGame()));
        connect(gameWindow, SIGNAL(mainMenu()), this, SLOT(showMainMenu()));
}

void WelcomeScreen::playButtonClicked()
{
    //TODO: Handle Login info.

    // Close welcome window and start game
    QString username = ui->usernameTextbox->text();
    QString password = ui->passwordTextbox->text();
    QString teacher = ui->teacherTextbox->text();

    Connector c;

    if(!c.isUser(username))
    {

        if(ui->teacherBox->isChecked())
        {
            c.addUser(username, password, true);
        }
        else
        {
            c.addUser(username, password, false);
        }

        if(!teacher.isEmpty())
        {
            c.addStudent(teacher, username);
        }

        startGame(username);
    }

    if(c.login(username, password))
    {
        if(!teacher.isEmpty())
        {
            c.addStudent(teacher, username);
        }
        startGame(username);
    }
    else
    {
        ui->invalid_label->setText("Invalid Username/Password");
    }

}

int WelcomeScreen::getHighScore(QString player)
{
    vector<vector<QString> > everyone = statPage.db.getEveryonesStats();

    int length = everyone.size();
    for(int i = 0; i < length; i++)
    {
        if(player == everyone[i][1])
        {
            int toReturn;
            toReturn = everyone[i][2].toInt();
            return toReturn;
        }
        else
        {
            return 0;
        }

    }

}

void WelcomeScreen::startGame(QString username)
{
    emit playGame();
    gameWindow->setUsername(username, getHighScore(username));
    gameWindow->show();
    gameWindow->activateWindow();
    //gameWindow->m_server->sendToServer(username, password, "qweqw", "qwe");
    gameWindow->setFocusPolicy(Qt::StrongFocus);
    gameWindow->setFocus();
    gameWindow->m_server->getDictionary(difficultyOption);
    gameWindow->move(QApplication::desktop()->screen()->rect().center() - gameWindow->rect().center());
    this->setEnabled(false);
    this->hide();
    this->close();
}

// Use for testing without login data
void WelcomeScreen::guestButtonClicked()
{
    // Close welcome window and start game
//    emit playGame();
//    gameWindow->show();
//    gameWindow->activateWindow();
//    this->setEnabled(false);
//    this->hide();
//    this->close();

//    gameWindow->show();
//    gameWindow->activateWindow();
//    //gameWindow->m_server->sendToServer(username, password, "qweqw", "qwe");
//    gameWindow->setFocusPolicy(Qt::StrongFocus);
//    gameWindow->setFocus();
//    gameWindow->m_server->getDictionary(difficultyOption);
//    gameWindow->move(QApplication::desktop()->screen()->rect().center() - gameWindow->rect().center());
//    this->setEnabled(false);
//    this->hide();
//    this->close();

    startGame("");


}

void WelcomeScreen::statsButtonClicked()
{
    statPage.showEveryone();

    statPage.show();
    /*
    this->setEnabled(false);
    this->hide();
    this->close();
    */
}


void WelcomeScreen::teacherStatsButtonClicked()
{
    statPage.showStudents(ui->usernameTextbox->text());

    statPage.show();
    /*
    this->setEnabled(false);
    this->hide();
    this->close();
    */
}

void WelcomeScreen::on_playButton_pressed()
{

}

/*
 * animates the icon of each button on the login screen
*/
//event filter derived from
//http://stackoverflow.com/questions/9261175/how-to-do-that-when-the-mouse-pointer-hovers-over-a-qpushbutton-then-the-button
bool WelcomeScreen::eventFilter(QObject *obj, QEvent *event)
{
    // This function repeatedly call for those QObjects
    // which have installed eventFilter (Step 2)

    if (obj == (QObject*)ui->playButton) {
        if (event->type() == QEvent::Enter && ui->playButton->isEnabled())
        {
            setButtonIcon(ui->playButton,":/graphics/graphics/play_button.png",165,65);
        }
        if (event->type() == QEvent::Leave && ui->playButton->isEnabled())
        {
            setButtonIcon(ui->playButton,":/graphics/graphics/play_button.png",155,60);
        }
        return QWidget::eventFilter(obj, event);
    }
    else if(obj == (QObject*)ui->guestButton)
    {
        if (event->type() == QEvent::Enter)
        {
            setButtonIcon(ui->guestButton,":/graphics/graphics/guest_button.png",180,45);
        }
        if (event->type() == QEvent::Leave)
        {
            setButtonIcon(ui->guestButton,":/graphics/graphics/guest_button.png",170,40);
        }
        return QWidget::eventFilter(obj, event);

    }
    else if(obj == (QObject*)ui->soundButton)
    {
        if (event->type() == QEvent::Enter)
        {
            setButtonIcon(ui->soundButton,":/graphics/graphics/sound_button.png",90,40);
        }
        if (event->type() == QEvent::Leave)
        {
            setButtonIcon(ui->soundButton,":/graphics/graphics/sound_button.png",85,35);
        }
        return QWidget::eventFilter(obj, event);

    }
    else if(obj == (QObject*)ui->musicButton)
    {
        if (event->type() == QEvent::Enter)
        {
            setButtonIcon(ui->musicButton,":/graphics/graphics/music_button.png",90,40);
        }
        if (event->type() == QEvent::Leave)
        {
            setButtonIcon(ui->musicButton,":/graphics/graphics/music_button.png",85,35);
        }
        return QWidget::eventFilter(obj, event);

    }
    else if(obj == (QObject*)ui->statsButton)
    {
        if (event->type() == QEvent::Enter)
        {
            setButtonIcon(ui->statsButton,":/graphics/graphics/stats_button.png",110,50);
        }
        if (event->type() == QEvent::Leave)
        {
            setButtonIcon(ui->statsButton,":/graphics/graphics/stats_button.png",105,45);
        }
        return QWidget::eventFilter(obj, event);

    }
    else if(obj == (QObject*)ui->teacherStatsButton)
    {
        if (event->type() == QEvent::Enter)
        {
            setButtonIcon(ui->teacherStatsButton,":/graphics/graphics/stats_button.png",110,50);
        }
        if (event->type() == QEvent::Leave)
        {
            setButtonIcon(ui->teacherStatsButton,":/graphics/graphics/stats_button.png",105,45);
        }
        return QWidget::eventFilter(obj, event);

    }
}

void WelcomeScreen::on_usernameTextbox_textChanged(const QString &arg1)
{
    if(ui->usernameTextbox->text() =="")
    {
         ui->playButton->setEnabled(false);
    }
    else
    {
         ui->playButton->setEnabled(true);
    }
}

void WelcomeScreen::on_teacherBox_stateChanged(int arg1)
{
    if(ui->teacherBox->isChecked())
    {
//    if(ui->studentBox->isChecked())
//    {
        ui->studentBox->setChecked(false);
        ui->teacherTextbox->setEnabled(false);
        ui->teacherTextbox->setText("");
        ui->teacherTextbox->hide();
        ui->teacher_label->hide();
        ui->teacher_label_2->show();
        ui->teacherStatsButton->show();
        ui->teacherBox->setChecked(true);
        ui->studentBox->setCheckable(true);
        //ui->teacherBox->setCheckable(false);
    //}
    ui->teacherBox->setChecked(true);
    }
}

void WelcomeScreen::on_studentBox_stateChanged(int arg1)
{
    if(ui->studentBox->isChecked()){

//    if(ui->teacherBox->isChecked())
//    {
        ui->teacherBox->setChecked(false);
        ui->teacherTextbox->setEnabled(true);
        ui->teacherTextbox->show();
        ui->teacher_label->show();
        ui->teacher_label_2->hide();
        ui->teacherStatsButton->hide();
        ui->studentBox->setChecked(true);
        //ui->studentBox->setCheckable(false);
        ui->teacherBox->setCheckable(true);
    //}
    ui->studentBox->setChecked(true);
    }
}
