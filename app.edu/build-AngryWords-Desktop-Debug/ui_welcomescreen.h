/********************************************************************************
** Form generated from reading UI file 'welcomescreen.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMESCREEN_H
#define UI_WELCOMESCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomeScreen
{
public:
    QWidget *centralwidget;
    QGraphicsView *welcomeGraphic;
    QLabel *pass_Label;
    QLabel *username_label;
    QPushButton *guestButton;
    QPushButton *playButton;
    QPushButton *musicButton;
    QPushButton *soundButton;
    QPushButton *statsButton;
    QLabel *teacher_label;
    QLineEdit *teacherTextbox;
    QLineEdit *usernameTextbox;
    QLineEdit *passwordTextbox;
    QLabel *invalid_label;
    QCheckBox *teacherBox;
    QCheckBox *studentBox;
    QPushButton *teacherStatsButton;
    QLabel *teacher_label_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *teacher_label_3;
    QMenuBar *menubar;

    void setupUi(QMainWindow *WelcomeScreen)
    {
        if (WelcomeScreen->objectName().isEmpty())
            WelcomeScreen->setObjectName(QString::fromUtf8("WelcomeScreen"));
        WelcomeScreen->resize(800, 500);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WelcomeScreen->sizePolicy().hasHeightForWidth());
        WelcomeScreen->setSizePolicy(sizePolicy);
        WelcomeScreen->setMinimumSize(QSize(800, 500));
        WelcomeScreen->setMaximumSize(QSize(800, 500));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/graphics/graphics/Red_square_bird.png"), QSize(), QIcon::Normal, QIcon::Off);
        WelcomeScreen->setWindowIcon(icon);
        WelcomeScreen->setDocumentMode(false);
        centralwidget = new QWidget(WelcomeScreen);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        welcomeGraphic = new QGraphicsView(centralwidget);
        welcomeGraphic->setObjectName(QString::fromUtf8("welcomeGraphic"));
        welcomeGraphic->setGeometry(QRect(0, -10, 800, 500));
        welcomeGraphic->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        welcomeGraphic->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        pass_Label = new QLabel(centralwidget);
        pass_Label->setObjectName(QString::fromUtf8("pass_Label"));
        pass_Label->setGeometry(QRect(250, 190, 120, 25));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        pass_Label->setFont(font);
        username_label = new QLabel(centralwidget);
        username_label->setObjectName(QString::fromUtf8("username_label"));
        username_label->setGeometry(QRect(250, 160, 120, 25));
        username_label->setFont(font);
        guestButton = new QPushButton(centralwidget);
        guestButton->setObjectName(QString::fromUtf8("guestButton"));
        guestButton->setGeometry(QRect(300, 360, 201, 51));
        QFont font1;
        font1.setPointSize(20);
        guestButton->setFont(font1);
        guestButton->setFlat(true);
        playButton = new QPushButton(centralwidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setGeometry(QRect(310, 290, 181, 71));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy1);
        playButton->setFont(font1);
        playButton->setCursor(QCursor(Qt::PointingHandCursor));
        playButton->setFlat(true);
        musicButton = new QPushButton(centralwidget);
        musicButton->setObjectName(QString::fromUtf8("musicButton"));
        musicButton->setGeometry(QRect(210, 340, 91, 41));
        musicButton->setFlat(true);
        soundButton = new QPushButton(centralwidget);
        soundButton->setObjectName(QString::fromUtf8("soundButton"));
        soundButton->setGeometry(QRect(210, 380, 91, 41));
        soundButton->setFlat(true);
        statsButton = new QPushButton(centralwidget);
        statsButton->setObjectName(QString::fromUtf8("statsButton"));
        statsButton->setGeometry(QRect(490, 360, 111, 51));
        statsButton->setFlat(true);
        teacher_label = new QLabel(centralwidget);
        teacher_label->setObjectName(QString::fromUtf8("teacher_label"));
        teacher_label->setGeometry(QRect(410, 220, 141, 31));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        teacher_label->setFont(font2);
        teacher_label->setAlignment(Qt::AlignCenter);
        teacher_label->setWordWrap(true);
        teacherTextbox = new QLineEdit(centralwidget);
        teacherTextbox->setObjectName(QString::fromUtf8("teacherTextbox"));
        teacherTextbox->setGeometry(QRect(410, 250, 141, 28));
        QFont font3;
        font3.setPointSize(14);
        teacherTextbox->setFont(font3);
        usernameTextbox = new QLineEdit(centralwidget);
        usernameTextbox->setObjectName(QString::fromUtf8("usernameTextbox"));
        usernameTextbox->setGeometry(QRect(390, 160, 180, 28));
        usernameTextbox->setFont(font3);
        passwordTextbox = new QLineEdit(centralwidget);
        passwordTextbox->setObjectName(QString::fromUtf8("passwordTextbox"));
        passwordTextbox->setGeometry(QRect(390, 190, 180, 28));
        passwordTextbox->setFont(font3);
        invalid_label = new QLabel(centralwidget);
        invalid_label->setObjectName(QString::fromUtf8("invalid_label"));
        invalid_label->setGeometry(QRect(390, 130, 181, 21));
        invalid_label->setAlignment(Qt::AlignCenter);
        teacherBox = new QCheckBox(centralwidget);
        teacherBox->setObjectName(QString::fromUtf8("teacherBox"));
        teacherBox->setGeometry(QRect(250, 250, 181, 31));
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(true);
        font4.setWeight(75);
        teacherBox->setFont(font4);
        teacherBox->setAutoFillBackground(false);
        teacherBox->setIconSize(QSize(32, 32));
        studentBox = new QCheckBox(centralwidget);
        studentBox->setObjectName(QString::fromUtf8("studentBox"));
        studentBox->setGeometry(QRect(250, 230, 181, 21));
        studentBox->setFont(font4);
        studentBox->setAutoFillBackground(false);
        studentBox->setIconSize(QSize(32, 32));
        teacherStatsButton = new QPushButton(centralwidget);
        teacherStatsButton->setObjectName(QString::fromUtf8("teacherStatsButton"));
        teacherStatsButton->setGeometry(QRect(430, 230, 111, 51));
        teacherStatsButton->setFlat(true);
        teacher_label_2 = new QLabel(centralwidget);
        teacher_label_2->setObjectName(QString::fromUtf8("teacher_label_2"));
        teacher_label_2->setGeometry(QRect(430, 220, 111, 21));
        teacher_label_2->setFont(font2);
        teacher_label_2->setAlignment(Qt::AlignCenter);
        teacher_label_2->setWordWrap(true);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 230, 131, 21));
        label->setFont(font4);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(280, 250, 131, 31));
        label_2->setFont(font4);
        teacher_label_3 = new QLabel(centralwidget);
        teacher_label_3->setObjectName(QString::fromUtf8("teacher_label_3"));
        teacher_label_3->setGeometry(QRect(490, 340, 111, 31));
        teacher_label_3->setFont(font2);
        teacher_label_3->setAlignment(Qt::AlignCenter);
        teacher_label_3->setWordWrap(true);
        WelcomeScreen->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WelcomeScreen);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        WelcomeScreen->setMenuBar(menubar);

        retranslateUi(WelcomeScreen);

        QMetaObject::connectSlotsByName(WelcomeScreen);
    } // setupUi

    void retranslateUi(QMainWindow *WelcomeScreen)
    {
        WelcomeScreen->setWindowTitle(QApplication::translate("WelcomeScreen", "Welcome to Angry Words!", 0, QApplication::UnicodeUTF8));
        pass_Label->setText(QApplication::translate("WelcomeScreen", "Password:", 0, QApplication::UnicodeUTF8));
        username_label->setText(QApplication::translate("WelcomeScreen", "Username:", 0, QApplication::UnicodeUTF8));
        guestButton->setText(QString());
        playButton->setText(QString());
        musicButton->setText(QString());
        soundButton->setText(QString());
        statsButton->setText(QString());
        teacher_label->setText(QApplication::translate("WelcomeScreen", "Enter your teacher's Name:", 0, QApplication::UnicodeUTF8));
        invalid_label->setText(QString());
        teacherBox->setText(QString());
        studentBox->setText(QString());
        teacherStatsButton->setText(QString());
        teacher_label_2->setText(QApplication::translate("WelcomeScreen", "<html><head/><body><p>See Class Stats</p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WelcomeScreen", "I am a Student", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("WelcomeScreen", "I am a Teacher", 0, QApplication::UnicodeUTF8));
        teacher_label_3->setText(QApplication::translate("WelcomeScreen", "<html><head/><body><p>See All Stats</p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WelcomeScreen: public Ui_WelcomeScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMESCREEN_H
