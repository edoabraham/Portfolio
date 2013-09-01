/********************************************************************************
** Form generated from reading UI file 'mainui.ui'
**
** Created: Thu Jul 25 20:19:20 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINUI_H
#define UI_MAINUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainUIClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionClear;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *MainLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuRecent;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainUIClass)
    {
        if (MainUIClass->objectName().isEmpty())
            MainUIClass->setObjectName(QString::fromUtf8("MainUIClass"));
        MainUIClass->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainUIClass->sizePolicy().hasHeightForWidth());
        MainUIClass->setSizePolicy(sizePolicy);
        actionNew = new QAction(MainUIClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(MainUIClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainUIClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionClear = new QAction(MainUIClass);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        centralWidget = new QWidget(MainUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 0, 0, 0);
        MainLayout = new QVBoxLayout();
        MainLayout->setSpacing(0);
        MainLayout->setObjectName(QString::fromUtf8("MainLayout"));
        MainLayout->setContentsMargins(0, -1, -1, -1);

        gridLayout->addLayout(MainLayout, 0, 0, 1, 1);

        MainUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuRecent = new QMenu(menuFile);
        menuRecent->setObjectName(QString::fromUtf8("menuRecent"));
        MainUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainUIClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(menuRecent->menuAction());

        retranslateUi(MainUIClass);

        QMetaObject::connectSlotsByName(MainUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainUIClass)
    {
        MainUIClass->setWindowTitle(QApplication::translate("MainUIClass", "MainUI", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainUIClass", "New...", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainUIClass", "Open...", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainUIClass", "Save", 0, QApplication::UnicodeUTF8));
        actionClear->setText(QApplication::translate("MainUIClass", "Clear", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        centralWidget->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_ACCESSIBILITY
        centralWidget->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_STATUSTIP
        menuBar->setStatusTip(QApplication::translate("MainUIClass", "Ready", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_STATUSTIP
        menuFile->setStatusTip(QApplication::translate("MainUIClass", "FileShit", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        menuFile->setTitle(QApplication::translate("MainUIClass", "File", 0, QApplication::UnicodeUTF8));
        menuRecent->setTitle(QApplication::translate("MainUIClass", "Recent", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainUIClass: public Ui_MainUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINUI_H
