/********************************************************************************
** Form generated from reading UI file 'LoadFileProcessL77053.ui'
**
** Created: Mon Jan 28 00:07:16 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LOADFILEPROCESSL77053_H
#define LOADFILEPROCESSL77053_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadingForm
{
public:
    QProgressBar *LoadProgressBar;
    QLabel *FileNameLabel;
    QLabel *LoadPercentLabel;

    void setupUi(QWidget *LoadingForm)
    {
        if (LoadingForm->objectName().isEmpty())
            LoadingForm->setObjectName(QString::fromUtf8("LoadingForm"));
        LoadingForm->resize(350, 91);
        LoadProgressBar = new QProgressBar(LoadingForm);
        LoadProgressBar->setObjectName(QString::fromUtf8("LoadProgressBar"));
        LoadProgressBar->setGeometry(QRect(40, 50, 271, 16));
        LoadProgressBar->setValue(24);
        FileNameLabel = new QLabel(LoadingForm);
        FileNameLabel->setObjectName(QString::fromUtf8("FileNameLabel"));
        FileNameLabel->setGeometry(QRect(40, 30, 62, 16));
        LoadPercentLabel = new QLabel(LoadingForm);
        LoadPercentLabel->setObjectName(QString::fromUtf8("LoadPercentLabel"));
        LoadPercentLabel->setGeometry(QRect(150, 50, 62, 16));
        LoadPercentLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(LoadingForm);

        QMetaObject::connectSlotsByName(LoadingForm);
    } // setupUi

    void retranslateUi(QWidget *LoadingForm)
    {
        LoadingForm->setWindowTitle(QApplication::translate("LoadingForm", "Loading Files...", 0, QApplication::UnicodeUTF8));
        FileNameLabel->setText(QApplication::translate("LoadingForm", "TextLabel", 0, QApplication::UnicodeUTF8));
        LoadPercentLabel->setText(QApplication::translate("LoadingForm", "0%", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LoadingForm: public Ui_LoadingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LOADFILEPROCESSL77053_H
