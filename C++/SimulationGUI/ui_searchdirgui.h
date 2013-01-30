/********************************************************************************
** Form generated from reading UI file 'searchdirgui.ui'
**
** Created: Fri Jan 18 02:10:48 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDIRGUI_H
#define UI_SEARCHDIRGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_SearchDirectoryDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTextBrowser *textBrowser;
    QLabel *label;
    QToolButton *toolButton;
    QLabel *label_2;

    void setupUi(QDialog *SearchDirectoryDialog)
    {
        if (SearchDirectoryDialog->objectName().isEmpty())
            SearchDirectoryDialog->setObjectName(QString::fromUtf8("SearchDirectoryDialog"));
        SearchDirectoryDialog->resize(381, 191);
        buttonBox = new QDialogButtonBox(SearchDirectoryDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(20, 140, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        textBrowser = new QTextBrowser(SearchDirectoryDialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(20, 80, 261, 31));
        label = new QLabel(SearchDirectoryDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 50, 131, 21));
        QFont font;
        font.setPointSize(9);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);
        toolButton = new QToolButton(SearchDirectoryDialog);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(290, 80, 71, 31));
        label_2 = new QLabel(SearchDirectoryDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(120, 20, 46, 13));

        retranslateUi(SearchDirectoryDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SearchDirectoryDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SearchDirectoryDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SearchDirectoryDialog);
    } // setupUi

    void retranslateUi(QDialog *SearchDirectoryDialog)
    {
        SearchDirectoryDialog->setWindowTitle(QApplication::translate("SearchDirectoryDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SearchDirectoryDialog", "Search for Directory ...", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("SearchDirectoryDialog", "Browse..", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SearchDirectoryDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SearchDirectoryDialog: public Ui_SearchDirectoryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDIRGUI_H
