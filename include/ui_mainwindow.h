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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *CentralWidget;
    QGridLayout *s_gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QSlider *m_Zoom;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QSlider *m_y_trn_slider;
    QSlider *m_z_trn_slider;
    QLabel *yTrnLabel;
    QLabel *xTrnLabel;
    QLabel *zTrnLabel;
    QSlider *m_x_trn_slider;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLabel *xRotLabel_2;
    QLabel *yRotLabel_2;
    QLabel *zRotLabel_2;
    QSlider *m_x_rotation;
    QSlider *m_y_rotation;
    QSlider *m_z_rotation;
    QPushButton *m_Spin_Button;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_6;
    QSlider *m_roughSlider;
    QLabel *label;
    QLabel *label_2;
    QSlider *m_shineySlider;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_7;
    QSlider *m_lightY;
    QLabel *label_4;
    QLabel *label_3;
    QSlider *m_lightZ;
    QLabel *label_5;
    QSlider *m_lightX;
    QPushButton *m_colourButton;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1072, 694);
        CentralWidget = new QWidget(MainWindow);
        CentralWidget->setObjectName(QStringLiteral("CentralWidget"));
        s_gridLayout = new QGridLayout(CentralWidget);
        s_gridLayout->setSpacing(6);
        s_gridLayout->setContentsMargins(11, 11, 11, 11);
        s_gridLayout->setObjectName(QStringLiteral("s_gridLayout"));
        groupBox = new QGroupBox(CentralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setAlignment(Qt::AlignCenter);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setAlignment(Qt::AlignCenter);
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox_5 = new QGroupBox(groupBox_4);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setAlignment(Qt::AlignCenter);
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        m_Zoom = new QSlider(groupBox_5);
        m_Zoom->setObjectName(QStringLiteral("m_Zoom"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_Zoom->sizePolicy().hasHeightForWidth());
        m_Zoom->setSizePolicy(sizePolicy);
        m_Zoom->setMinimum(1);
        m_Zoom->setMaximum(32);
        m_Zoom->setValue(16);
        m_Zoom->setOrientation(Qt::Horizontal);
        m_Zoom->setInvertedControls(true);

        gridLayout_5->addWidget(m_Zoom, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_5, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setAlignment(Qt::AlignCenter);
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_y_trn_slider = new QSlider(groupBox_3);
        m_y_trn_slider->setObjectName(QStringLiteral("m_y_trn_slider"));
        sizePolicy.setHeightForWidth(m_y_trn_slider->sizePolicy().hasHeightForWidth());
        m_y_trn_slider->setSizePolicy(sizePolicy);
        m_y_trn_slider->setMinimum(-20);
        m_y_trn_slider->setMaximum(20);
        m_y_trn_slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_y_trn_slider, 1, 1, 1, 1);

        m_z_trn_slider = new QSlider(groupBox_3);
        m_z_trn_slider->setObjectName(QStringLiteral("m_z_trn_slider"));
        sizePolicy.setHeightForWidth(m_z_trn_slider->sizePolicy().hasHeightForWidth());
        m_z_trn_slider->setSizePolicy(sizePolicy);
        m_z_trn_slider->setMinimum(-20);
        m_z_trn_slider->setMaximum(20);
        m_z_trn_slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_z_trn_slider, 1, 2, 1, 1);

        yTrnLabel = new QLabel(groupBox_3);
        yTrnLabel->setObjectName(QStringLiteral("yTrnLabel"));
        yTrnLabel->setFont(font);
        yTrnLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(yTrnLabel, 0, 1, 1, 1);

        xTrnLabel = new QLabel(groupBox_3);
        xTrnLabel->setObjectName(QStringLiteral("xTrnLabel"));
        xTrnLabel->setFont(font);
        xTrnLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(xTrnLabel, 0, 0, 1, 1);

        zTrnLabel = new QLabel(groupBox_3);
        zTrnLabel->setObjectName(QStringLiteral("zTrnLabel"));
        zTrnLabel->setFont(font);
        zTrnLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(zTrnLabel, 0, 2, 1, 1);

        m_x_trn_slider = new QSlider(groupBox_3);
        m_x_trn_slider->setObjectName(QStringLiteral("m_x_trn_slider"));
        sizePolicy.setHeightForWidth(m_x_trn_slider->sizePolicy().hasHeightForWidth());
        m_x_trn_slider->setSizePolicy(sizePolicy);
        m_x_trn_slider->setMinimum(-20);
        m_x_trn_slider->setMaximum(20);
        m_x_trn_slider->setSingleStep(1);
        m_x_trn_slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_x_trn_slider, 1, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(groupBox_4);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setAlignment(Qt::AlignCenter);
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        xRotLabel_2 = new QLabel(groupBox_2);
        xRotLabel_2->setObjectName(QStringLiteral("xRotLabel_2"));
        xRotLabel_2->setFont(font);
        xRotLabel_2->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(xRotLabel_2, 0, 0, 1, 1);

        yRotLabel_2 = new QLabel(groupBox_2);
        yRotLabel_2->setObjectName(QStringLiteral("yRotLabel_2"));
        yRotLabel_2->setFont(font);
        yRotLabel_2->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(yRotLabel_2, 0, 1, 1, 1);

        zRotLabel_2 = new QLabel(groupBox_2);
        zRotLabel_2->setObjectName(QStringLiteral("zRotLabel_2"));
        zRotLabel_2->setFont(font);
        zRotLabel_2->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(zRotLabel_2, 0, 2, 1, 1);

        m_x_rotation = new QSlider(groupBox_2);
        m_x_rotation->setObjectName(QStringLiteral("m_x_rotation"));
        sizePolicy.setHeightForWidth(m_x_rotation->sizePolicy().hasHeightForWidth());
        m_x_rotation->setSizePolicy(sizePolicy);
        m_x_rotation->setMinimum(-180);
        m_x_rotation->setMaximum(180);
        m_x_rotation->setSingleStep(1);
        m_x_rotation->setOrientation(Qt::Horizontal);
        m_x_rotation->setInvertedControls(false);

        gridLayout_3->addWidget(m_x_rotation, 1, 0, 1, 1);

        m_y_rotation = new QSlider(groupBox_2);
        m_y_rotation->setObjectName(QStringLiteral("m_y_rotation"));
        sizePolicy.setHeightForWidth(m_y_rotation->sizePolicy().hasHeightForWidth());
        m_y_rotation->setSizePolicy(sizePolicy);
        m_y_rotation->setMinimum(-180);
        m_y_rotation->setMaximum(180);
        m_y_rotation->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(m_y_rotation, 1, 1, 1, 1);

        m_z_rotation = new QSlider(groupBox_2);
        m_z_rotation->setObjectName(QStringLiteral("m_z_rotation"));
        sizePolicy.setHeightForWidth(m_z_rotation->sizePolicy().hasHeightForWidth());
        m_z_rotation->setSizePolicy(sizePolicy);
        m_z_rotation->setMinimum(-180);
        m_z_rotation->setMaximum(180);
        m_z_rotation->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(m_z_rotation, 1, 2, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 1, 0, 1, 1);

        m_Spin_Button = new QPushButton(groupBox_4);
        m_Spin_Button->setObjectName(QStringLiteral("m_Spin_Button"));

        gridLayout_4->addWidget(m_Spin_Button, 3, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_4, 0, 0, 1, 1);

        groupBox_7 = new QGroupBox(groupBox);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setAlignment(Qt::AlignCenter);
        gridLayout_6 = new QGridLayout(groupBox_7);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        m_roughSlider = new QSlider(groupBox_7);
        m_roughSlider->setObjectName(QStringLiteral("m_roughSlider"));
        sizePolicy.setHeightForWidth(m_roughSlider->sizePolicy().hasHeightForWidth());
        m_roughSlider->setSizePolicy(sizePolicy);
        m_roughSlider->setMaximum(100);
        m_roughSlider->setValue(50);
        m_roughSlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(m_roughSlider, 1, 0, 1, 1);

        label = new QLabel(groupBox_7);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox_7);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_2, 2, 0, 1, 1);

        m_shineySlider = new QSlider(groupBox_7);
        m_shineySlider->setObjectName(QStringLiteral("m_shineySlider"));
        sizePolicy.setHeightForWidth(m_shineySlider->sizePolicy().hasHeightForWidth());
        m_shineySlider->setSizePolicy(sizePolicy);
        m_shineySlider->setMaximum(100);
        m_shineySlider->setValue(50);
        m_shineySlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(m_shineySlider, 3, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_7, 4, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 0, 1, 1);

        groupBox_6 = new QGroupBox(groupBox);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setAlignment(Qt::AlignCenter);
        gridLayout_7 = new QGridLayout(groupBox_6);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        m_lightY = new QSlider(groupBox_6);
        m_lightY->setObjectName(QStringLiteral("m_lightY"));
        sizePolicy.setHeightForWidth(m_lightY->sizePolicy().hasHeightForWidth());
        m_lightY->setSizePolicy(sizePolicy);
        m_lightY->setMaximum(10);
        m_lightY->setValue(5);
        m_lightY->setOrientation(Qt::Horizontal);

        gridLayout_7->addWidget(m_lightY, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox_6);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_4, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_6);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_3, 0, 0, 1, 1);

        m_lightZ = new QSlider(groupBox_6);
        m_lightZ->setObjectName(QStringLiteral("m_lightZ"));
        sizePolicy.setHeightForWidth(m_lightZ->sizePolicy().hasHeightForWidth());
        m_lightZ->setSizePolicy(sizePolicy);
        m_lightZ->setMaximum(10);
        m_lightZ->setValue(5);
        m_lightZ->setOrientation(Qt::Horizontal);

        gridLayout_7->addWidget(m_lightZ, 1, 2, 1, 1);

        label_5 = new QLabel(groupBox_6);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_5, 0, 2, 1, 1);

        m_lightX = new QSlider(groupBox_6);
        m_lightX->setObjectName(QStringLiteral("m_lightX"));
        sizePolicy.setHeightForWidth(m_lightX->sizePolicy().hasHeightForWidth());
        m_lightX->setSizePolicy(sizePolicy);
        m_lightX->setMaximum(10);
        m_lightX->setValue(5);
        m_lightX->setOrientation(Qt::Horizontal);

        gridLayout_7->addWidget(m_lightX, 1, 0, 1, 1);

        m_colourButton = new QPushButton(groupBox_6);
        m_colourButton->setObjectName(QStringLiteral("m_colourButton"));

        gridLayout_7->addWidget(m_colourButton, 2, 0, 1, 3);


        gridLayout_2->addWidget(groupBox_6, 2, 0, 1, 1);


        s_gridLayout->addWidget(groupBox, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        MainWindow->setCentralWidget(CentralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1072, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Controls", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Transform Controls", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Zoom", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Translate", 0));
        yTrnLabel->setText(QApplication::translate("MainWindow", "Y", 0));
        xTrnLabel->setText(QApplication::translate("MainWindow", "X", 0));
        zTrnLabel->setText(QApplication::translate("MainWindow", "Z", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Rotation", 0));
        xRotLabel_2->setText(QApplication::translate("MainWindow", "X", 0));
        yRotLabel_2->setText(QApplication::translate("MainWindow", "Y", 0));
        zRotLabel_2->setText(QApplication::translate("MainWindow", "Z", 0));
        m_Spin_Button->setText(QApplication::translate("MainWindow", "Spin", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Shader Parameters", 0));
        label->setText(QApplication::translate("MainWindow", "Roughness", 0));
        label_2->setText(QApplication::translate("MainWindow", "Shineyness", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Light Parameters", 0));
        label_4->setText(QApplication::translate("MainWindow", "Y", 0));
        label_3->setText(QApplication::translate("MainWindow", "X", 0));
        label_5->setText(QApplication::translate("MainWindow", "Z", 0));
        m_colourButton->setText(QApplication::translate("MainWindow", "Colour", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
