/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "openglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_File;
    QAction *actionOpen_File_2;
    QAction *actionTest;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QDoubleSpinBox *scaley;
    QSlider *Sliderz;
    OpenGLWidget *openGLWidget;
    QLabel *label;
    QSlider *Sliderx;
    QLabel *label_7;
    QLabel *label_10;
    QCheckBox *AutoRotateX;
    QDoubleSpinBox *scalex;
    QLabel *label_4;
    QLabel *label_2;
    QSlider *Slidery;
    QLabel *label_8;
    QLabel *label_11;
    QCheckBox *AutoRotateY;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_9;
    QLabel *label_12;
    QCheckBox *AutoRotateZ;
    QDoubleSpinBox *scalez;
    QLabel *label_6;
    QComboBox *comboBox;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuCarregar_Labirinto;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(858, 387);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionOpen_File = new QAction(MainWindow);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        actionOpen_File_2 = new QAction(MainWindow);
        actionOpen_File_2->setObjectName(QStringLiteral("actionOpen_File_2"));
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        scaley = new QDoubleSpinBox(centralWidget);
        scaley->setObjectName(QStringLiteral("scaley"));
        scaley->setSingleStep(0.5);
        scaley->setValue(1);

        gridLayout->addWidget(scaley, 8, 2, 1, 2);

        Sliderz = new QSlider(centralWidget);
        Sliderz->setObjectName(QStringLiteral("Sliderz"));
        Sliderz->setMaximum(359);
        Sliderz->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Sliderz, 11, 1, 1, 3);

        openGLWidget = new OpenGLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);

        gridLayout->addWidget(openGLWidget, 0, 0, 16, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        Sliderx = new QSlider(centralWidget);
        Sliderx->setObjectName(QStringLiteral("Sliderx"));
        Sliderx->setMaximum(359);
        Sliderx->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Sliderx, 1, 1, 1, 3);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 1, 1, 1);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 2, 3, 1, 1);

        AutoRotateX = new QCheckBox(centralWidget);
        AutoRotateX->setObjectName(QStringLiteral("AutoRotateX"));

        gridLayout->addWidget(AutoRotateX, 3, 1, 1, 1);

        scalex = new QDoubleSpinBox(centralWidget);
        scalex->setObjectName(QStringLiteral("scalex"));
        scalex->setSingleStep(0.5);
        scalex->setValue(1);

        gridLayout->addWidget(scalex, 3, 2, 1, 2);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 2, 2, 2);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 5, 1, 1, 1);

        Slidery = new QSlider(centralWidget);
        Slidery->setObjectName(QStringLiteral("Slidery"));
        Slidery->setMaximum(359);
        Slidery->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Slidery, 6, 1, 1, 3);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 7, 1, 1, 1);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 7, 3, 1, 1);

        AutoRotateY = new QCheckBox(centralWidget);
        AutoRotateY->setObjectName(QStringLiteral("AutoRotateY"));

        gridLayout->addWidget(AutoRotateY, 8, 1, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 9, 2, 2, 2);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 10, 1, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 12, 1, 1, 1);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 12, 3, 1, 1);

        AutoRotateZ = new QCheckBox(centralWidget);
        AutoRotateZ->setObjectName(QStringLiteral("AutoRotateZ"));

        gridLayout->addWidget(AutoRotateZ, 13, 1, 1, 1);

        scalez = new QDoubleSpinBox(centralWidget);
        scalez->setObjectName(QStringLiteral("scalez"));
        scalez->setSingleStep(0.5);
        scalez->setValue(1);

        gridLayout->addWidget(scalez, 13, 2, 1, 2);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 14, 2, 1, 2);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 15, 1, 1, 3);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 858, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuCarregar_Labirinto = new QMenu(menuBar);
        menuCarregar_Labirinto->setObjectName(QStringLiteral("menuCarregar_Labirinto"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuCarregar_Labirinto->menuAction());
        menuFile->addAction(actionOpen_File);
        menuCarregar_Labirinto->addAction(actionOpen_File_2);

        retranslateUi(MainWindow);
        QObject::connect(actionOpen_File, SIGNAL(triggered()), openGLWidget, SLOT(showFileOpenDialog()));
        QObject::connect(openGLWidget, SIGNAL(statusBarMessage(QString)), statusBar, SLOT(showMessage(QString)));
        QObject::connect(Sliderx, SIGNAL(valueChanged(int)), openGLWidget, SLOT(rotatex()));
        QObject::connect(Slidery, SIGNAL(valueChanged(int)), openGLWidget, SLOT(rotatey()));
        QObject::connect(Sliderz, SIGNAL(sliderMoved(int)), openGLWidget, SLOT(rotatez()));
        QObject::connect(AutoRotateY, SIGNAL(toggled(bool)), openGLWidget, SLOT(autoRotatey(bool)));
        QObject::connect(AutoRotateX, SIGNAL(toggled(bool)), openGLWidget, SLOT(autoRotatex(bool)));
        QObject::connect(AutoRotateZ, SIGNAL(toggled(bool)), openGLWidget, SLOT(autoRotatez(bool)));
        QObject::connect(scalex, SIGNAL(valueChanged(double)), openGLWidget, SLOT(rescalex()));
        QObject::connect(scaley, SIGNAL(valueChanged(double)), openGLWidget, SLOT(rescaley()));
        QObject::connect(scalez, SIGNAL(valueChanged(double)), openGLWidget, SLOT(rescalez()));
        QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), openGLWidget, SLOT(changeShader(int)));
        QObject::connect(openGLWidget, SIGNAL(enableComboShaders(bool)), comboBox, SLOT(setEnabled(bool)));
        QObject::connect(actionOpen_File_2, SIGNAL(triggered()), openGLWidget, SLOT(loadMaze()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen_File->setText(QApplication::translate("MainWindow", "Open File", 0));
        actionOpen_File_2->setText(QApplication::translate("MainWindow", "Open File", 0));
        actionTest->setText(QApplication::translate("MainWindow", "test", 0));
        label->setText(QApplication::translate("MainWindow", "Eixo X", 0));
        label_7->setText(QApplication::translate("MainWindow", "0", 0));
        label_10->setText(QApplication::translate("MainWindow", "359", 0));
        AutoRotateX->setText(QApplication::translate("MainWindow", "Auto Rotate X", 0));
        label_4->setText(QApplication::translate("MainWindow", "Scala em X", 0));
        label_2->setText(QApplication::translate("MainWindow", "Eixo Y", 0));
        label_8->setText(QApplication::translate("MainWindow", "0", 0));
        label_11->setText(QApplication::translate("MainWindow", "359", 0));
        AutoRotateY->setText(QApplication::translate("MainWindow", "Auto Rotate Y", 0));
        label_5->setText(QApplication::translate("MainWindow", "Scala em Y", 0));
        label_3->setText(QApplication::translate("MainWindow", "Eixo Z", 0));
        label_9->setText(QApplication::translate("MainWindow", "0", 0));
        label_12->setText(QApplication::translate("MainWindow", "359", 0));
        AutoRotateZ->setText(QApplication::translate("MainWindow", "Auto Rotate Z", 0));
        label_6->setText(QApplication::translate("MainWindow", "Scala em Z", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "0 -vShader1", 0)
         << QApplication::translate("MainWindow", "1 - Flat", 0)
         << QApplication::translate("MainWindow", "2 - Gouraud", 0)
         << QApplication::translate("MainWindow", "3 - Phong", 0)
        );
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuCarregar_Labirinto->setTitle(QApplication::translate("MainWindow", "Carregar Labirinto", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
