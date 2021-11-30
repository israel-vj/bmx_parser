/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *filePathLineEdit;
    QPushButton *selectFilePushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *parsePushButton;
    QPlainTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(919, 490);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        filePathLineEdit = new QLineEdit(centralwidget);
        filePathLineEdit->setObjectName(QStringLiteral("filePathLineEdit"));

        horizontalLayout->addWidget(filePathLineEdit);

        selectFilePushButton = new QPushButton(centralwidget);
        selectFilePushButton->setObjectName(QStringLiteral("selectFilePushButton"));
        selectFilePushButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(selectFilePushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        parsePushButton = new QPushButton(centralwidget);
        parsePushButton->setObjectName(QStringLiteral("parsePushButton"));

        horizontalLayout->addWidget(parsePushButton);


        verticalLayout->addLayout(horizontalLayout);

        textEdit = new QPlainTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout->addWidget(textEdit);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 919, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Parser Banamex 1.0", 0));
        filePathLineEdit->setText(QApplication::translate("MainWindow", "C:\\Users\\Israel\\Desktop\\EstadodeCuenta.pdf", 0));
        selectFilePushButton->setText(QApplication::translate("MainWindow", "...", 0));
        parsePushButton->setText(QApplication::translate("MainWindow", "Procesar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
