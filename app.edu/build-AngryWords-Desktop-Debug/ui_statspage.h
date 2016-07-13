/********************************************************************************
** Form generated from reading UI file 'statspage.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATSPAGE_H
#define UI_STATSPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatsPage
{
public:
    QTableWidget *statsList;

    void setupUi(QWidget *StatsPage)
    {
        if (StatsPage->objectName().isEmpty())
            StatsPage->setObjectName(QString::fromUtf8("StatsPage"));
        StatsPage->resize(780, 440);
        statsList = new QTableWidget(StatsPage);
        statsList->setObjectName(QString::fromUtf8("statsList"));
        statsList->setGeometry(QRect(0, 0, 800, 500));

        retranslateUi(StatsPage);

        QMetaObject::connectSlotsByName(StatsPage);
    } // setupUi

    void retranslateUi(QWidget *StatsPage)
    {
        StatsPage->setWindowTitle(QApplication::translate("StatsPage", "Angry Words Stats", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StatsPage: public Ui_StatsPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATSPAGE_H
