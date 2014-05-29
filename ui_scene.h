/********************************************************************************
** Form generated from reading UI file 'scene.ui'
**
** Created: Thu May 29 11:36:04 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENE_H
#define UI_SCENE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Scene
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Scene)
    {
        if (Scene->objectName().isEmpty())
            Scene->setObjectName(QString::fromUtf8("Scene"));
        Scene->resize(800, 600);
        centralwidget = new QWidget(Scene);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);

        Scene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Scene);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        Scene->setMenuBar(menubar);
        statusbar = new QStatusBar(Scene);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Scene->setStatusBar(statusbar);

        retranslateUi(Scene);

        QMetaObject::connectSlotsByName(Scene);
    } // setupUi

    void retranslateUi(QMainWindow *Scene)
    {
        Scene->setWindowTitle(QApplication::translate("Scene", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Scene", "Draw", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Scene: public Ui_Scene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENE_H
