/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hlMainView;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *grpFile;
    QFormLayout *formLayout_2;
    QPushButton *butOpenFile;
    QLabel *lblFileName_Label;
    QLineEdit *leFileName;
    QLabel *lblLoadTime_Label;
    QLabel *lblLoadTime;
    QFrame *line;
    QPushButton *butExport;
    QLabel *lblExportTime_Label;
    QLabel *lblExportTime;
    QGroupBox *grpInfo;
    QFormLayout *formLayout_4;
    QLabel *lblRenderTime_Label;
    QLabel *lblRenderTime;
    QLabel *lblMeshCount_Label;
    QLabel *lblFaceCount_Label;
    QLabel *lblMeshCount;
    QLabel *lblFaceCount;
    QLabel *lblVertexCount_Label;
    QLabel *lblVertexCount;
    QLabel *lblLightCount_Label;
    QLabel *lblCameraCount_Label;
    QLabel *lblHasAnimation_Label;
    QLabel *lblShaderCount_Label;
    QLabel *lblLightCount;
    QLabel *lblCameraCount;
    QLabel *lblShaderCount;
    QLabel *lblHasAnimation;
    QLabel *lblDistance_Label;
    QLabel *lblDistance;
    QGroupBox *grpDynamics;
    QGridLayout *gridLayout;
    QPushButton *butAnimationStart;
    QPushButton *butAnimationStop;
    QTabWidget *tabInfoAndControl;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QTextBrowser *tbLog;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout;
    QListWidget *lstLight;
    QListWidget *lstCamera;
    QWidget *tab_3;
    QGridLayout *gridLayout_3;
    QCheckBox *cbxLighting;
    QCheckBox *cbxBBox;
    QCheckBox *cbxTextures;
    QCheckBox *cbxDrawAxes;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(641, 778);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        hlMainView = new QHBoxLayout();
        hlMainView->setSpacing(6);
        hlMainView->setObjectName(QString::fromUtf8("hlMainView"));
        hlMainView->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        grpFile = new QGroupBox(centralWidget);
        grpFile->setObjectName(QString::fromUtf8("grpFile"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(grpFile->sizePolicy().hasHeightForWidth());
        grpFile->setSizePolicy(sizePolicy);
        grpFile->setFocusPolicy(Qt::NoFocus);
        formLayout_2 = new QFormLayout(grpFile);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        butOpenFile = new QPushButton(grpFile);
        butOpenFile->setObjectName(QString::fromUtf8("butOpenFile"));
        butOpenFile->setFocusPolicy(Qt::NoFocus);

        formLayout_2->setWidget(0, QFormLayout::SpanningRole, butOpenFile);

        lblFileName_Label = new QLabel(grpFile);
        lblFileName_Label->setObjectName(QString::fromUtf8("lblFileName_Label"));
        lblFileName_Label->setFocusPolicy(Qt::NoFocus);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, lblFileName_Label);

        leFileName = new QLineEdit(grpFile);
        leFileName->setObjectName(QString::fromUtf8("leFileName"));
        leFileName->setMaximumSize(QSize(160, 16777215));
        leFileName->setFocusPolicy(Qt::NoFocus);
        leFileName->setFrame(false);
        leFileName->setReadOnly(true);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, leFileName);

        lblLoadTime_Label = new QLabel(grpFile);
        lblLoadTime_Label->setObjectName(QString::fromUtf8("lblLoadTime_Label"));
        lblLoadTime_Label->setFocusPolicy(Qt::NoFocus);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, lblLoadTime_Label);

        lblLoadTime = new QLabel(grpFile);
        lblLoadTime->setObjectName(QString::fromUtf8("lblLoadTime"));
        lblLoadTime->setFocusPolicy(Qt::NoFocus);
        lblLoadTime->setAlignment(Qt::AlignCenter);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lblLoadTime);

        line = new QFrame(grpFile);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFocusPolicy(Qt::NoFocus);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(4, QFormLayout::SpanningRole, line);

        butExport = new QPushButton(grpFile);
        butExport->setObjectName(QString::fromUtf8("butExport"));
        butExport->setFocusPolicy(Qt::NoFocus);

        formLayout_2->setWidget(5, QFormLayout::SpanningRole, butExport);

        lblExportTime_Label = new QLabel(grpFile);
        lblExportTime_Label->setObjectName(QString::fromUtf8("lblExportTime_Label"));
        lblExportTime_Label->setFocusPolicy(Qt::NoFocus);

        formLayout_2->setWidget(6, QFormLayout::LabelRole, lblExportTime_Label);

        lblExportTime = new QLabel(grpFile);
        lblExportTime->setObjectName(QString::fromUtf8("lblExportTime"));
        lblExportTime->setFocusPolicy(Qt::NoFocus);

        formLayout_2->setWidget(6, QFormLayout::FieldRole, lblExportTime);


        verticalLayout_3->addWidget(grpFile);

        grpInfo = new QGroupBox(centralWidget);
        grpInfo->setObjectName(QString::fromUtf8("grpInfo"));
        sizePolicy.setHeightForWidth(grpInfo->sizePolicy().hasHeightForWidth());
        grpInfo->setSizePolicy(sizePolicy);
        grpInfo->setFocusPolicy(Qt::NoFocus);
        formLayout_4 = new QFormLayout(grpInfo);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        lblRenderTime_Label = new QLabel(grpInfo);
        lblRenderTime_Label->setObjectName(QString::fromUtf8("lblRenderTime_Label"));
        lblRenderTime_Label->setFocusPolicy(Qt::NoFocus);

        formLayout_4->setWidget(0, QFormLayout::LabelRole, lblRenderTime_Label);

        lblRenderTime = new QLabel(grpInfo);
        lblRenderTime->setObjectName(QString::fromUtf8("lblRenderTime"));
        lblRenderTime->setFocusPolicy(Qt::NoFocus);
        lblRenderTime->setAlignment(Qt::AlignCenter);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, lblRenderTime);

        lblMeshCount_Label = new QLabel(grpInfo);
        lblMeshCount_Label->setObjectName(QString::fromUtf8("lblMeshCount_Label"));
        lblMeshCount_Label->setFocusPolicy(Qt::NoFocus);

        formLayout_4->setWidget(1, QFormLayout::LabelRole, lblMeshCount_Label);

        lblFaceCount_Label = new QLabel(grpInfo);
        lblFaceCount_Label->setObjectName(QString::fromUtf8("lblFaceCount_Label"));
        lblFaceCount_Label->setFocusPolicy(Qt::NoFocus);

        formLayout_4->setWidget(2, QFormLayout::LabelRole, lblFaceCount_Label);

        lblMeshCount = new QLabel(grpInfo);
        lblMeshCount->setObjectName(QString::fromUtf8("lblMeshCount"));
        lblMeshCount->setFocusPolicy(Qt::NoFocus);
        lblMeshCount->setAlignment(Qt::AlignCenter);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, lblMeshCount);

        lblFaceCount = new QLabel(grpInfo);
        lblFaceCount->setObjectName(QString::fromUtf8("lblFaceCount"));
        lblFaceCount->setFocusPolicy(Qt::NoFocus);
        lblFaceCount->setAlignment(Qt::AlignCenter);

        formLayout_4->setWidget(2, QFormLayout::FieldRole, lblFaceCount);

        lblVertexCount_Label = new QLabel(grpInfo);
        lblVertexCount_Label->setObjectName(QString::fromUtf8("lblVertexCount_Label"));
        lblVertexCount_Label->setFocusPolicy(Qt::NoFocus);

        formLayout_4->setWidget(3, QFormLayout::LabelRole, lblVertexCount_Label);

        lblVertexCount = new QLabel(grpInfo);
        lblVertexCount->setObjectName(QString::fromUtf8("lblVertexCount"));
        lblVertexCount->setFocusPolicy(Qt::NoFocus);
        lblVertexCount->setAlignment(Qt::AlignCenter);

        formLayout_4->setWidget(3, QFormLayout::FieldRole, lblVertexCount);

        lblLightCount_Label = new QLabel(grpInfo);
        lblLightCount_Label->setObjectName(QString::fromUtf8("lblLightCount_Label"));
        lblLightCount_Label->setFocusPolicy(Qt::NoFocus);

        formLayout_4->setWidget(4, QFormLayout::LabelRole, lblLightCount_Label);

        lblCameraCount_Label = new QLabel(grpInfo);
        lblCameraCount_Label->setObjectName(QString::fromUtf8("lblCameraCount_Label"));
        lblCameraCount_Label->setFocusPolicy(Qt::NoFocus);

        formLayout_4->setWidget(5, QFormLayout::LabelRole, lblCameraCount_Label);

        lblHasAnimation_Label = new QLabel(grpInfo);
        lblHasAnimation_Label->setObjectName(QString::fromUtf8("lblHasAnimation_Label"));
        lblHasAnimation_Label->setFocusPolicy(Qt::NoFocus);

        formLayout_4->setWidget(7, QFormLayout::LabelRole, lblHasAnimation_Label);

        lblShaderCount_Label = new QLabel(grpInfo);
        lblShaderCount_Label->setObjectName(QString::fromUtf8("lblShaderCount_Label"));
        lblShaderCount_Label->setEnabled(false);
        lblShaderCount_Label->setFocusPolicy(Qt::NoFocus);

        formLayout_4->setWidget(6, QFormLayout::LabelRole, lblShaderCount_Label);

        lblLightCount = new QLabel(grpInfo);
        lblLightCount->setObjectName(QString::fromUtf8("lblLightCount"));
        lblLightCount->setFocusPolicy(Qt::NoFocus);
        lblLightCount->setAlignment(Qt::AlignCenter);

        formLayout_4->setWidget(4, QFormLayout::FieldRole, lblLightCount);

        lblCameraCount = new QLabel(grpInfo);
        lblCameraCount->setObjectName(QString::fromUtf8("lblCameraCount"));
        lblCameraCount->setFocusPolicy(Qt::NoFocus);
        lblCameraCount->setAlignment(Qt::AlignCenter);

        formLayout_4->setWidget(5, QFormLayout::FieldRole, lblCameraCount);

        lblShaderCount = new QLabel(grpInfo);
        lblShaderCount->setObjectName(QString::fromUtf8("lblShaderCount"));
        lblShaderCount->setEnabled(false);
        lblShaderCount->setFocusPolicy(Qt::NoFocus);
        lblShaderCount->setAlignment(Qt::AlignCenter);

        formLayout_4->setWidget(6, QFormLayout::FieldRole, lblShaderCount);

        lblHasAnimation = new QLabel(grpInfo);
        lblHasAnimation->setObjectName(QString::fromUtf8("lblHasAnimation"));
        lblHasAnimation->setFocusPolicy(Qt::NoFocus);
        lblHasAnimation->setAlignment(Qt::AlignCenter);

        formLayout_4->setWidget(7, QFormLayout::FieldRole, lblHasAnimation);

        lblDistance_Label = new QLabel(grpInfo);
        lblDistance_Label->setObjectName(QString::fromUtf8("lblDistance_Label"));

        formLayout_4->setWidget(8, QFormLayout::LabelRole, lblDistance_Label);

        lblDistance = new QLabel(grpInfo);
        lblDistance->setObjectName(QString::fromUtf8("lblDistance"));
        lblDistance->setAlignment(Qt::AlignCenter);

        formLayout_4->setWidget(8, QFormLayout::FieldRole, lblDistance);


        verticalLayout_3->addWidget(grpInfo);

        grpDynamics = new QGroupBox(centralWidget);
        grpDynamics->setObjectName(QString::fromUtf8("grpDynamics"));
        grpDynamics->setEnabled(false);
        grpDynamics->setFocusPolicy(Qt::NoFocus);
        gridLayout = new QGridLayout(grpDynamics);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        butAnimationStart = new QPushButton(grpDynamics);
        butAnimationStart->setObjectName(QString::fromUtf8("butAnimationStart"));
        butAnimationStart->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(butAnimationStart, 0, 0, 1, 1);

        butAnimationStop = new QPushButton(grpDynamics);
        butAnimationStop->setObjectName(QString::fromUtf8("butAnimationStop"));
        butAnimationStop->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(butAnimationStop, 1, 0, 1, 1);


        verticalLayout_3->addWidget(grpDynamics);


        hlMainView->addLayout(verticalLayout_3);


        verticalLayout->addLayout(hlMainView);

        tabInfoAndControl = new QTabWidget(centralWidget);
        tabInfoAndControl->setObjectName(QString::fromUtf8("tabInfoAndControl"));
        tabInfoAndControl->setFocusPolicy(Qt::NoFocus);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tbLog = new QTextBrowser(tab);
        tbLog->setObjectName(QString::fromUtf8("tbLog"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tbLog->sizePolicy().hasHeightForWidth());
        tbLog->setSizePolicy(sizePolicy1);
        tbLog->setMinimumSize(QSize(0, 0));
        tbLog->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(tbLog, 0, 0, 1, 1);

        tabInfoAndControl->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout = new QHBoxLayout(tab_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lstLight = new QListWidget(tab_2);
        lstLight->setObjectName(QString::fromUtf8("lstLight"));
        lstLight->setFocusPolicy(Qt::NoFocus);
        lstLight->setEditTriggers(QAbstractItemView::SelectedClicked);
        lstLight->setProperty("showDropIndicator", QVariant(false));
        lstLight->setSelectionMode(QAbstractItemView::MultiSelection);

        horizontalLayout->addWidget(lstLight);

        lstCamera = new QListWidget(tab_2);
        lstCamera->setObjectName(QString::fromUtf8("lstCamera"));
        lstCamera->setFocusPolicy(Qt::NoFocus);
        lstCamera->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lstCamera->setProperty("showDropIndicator", QVariant(false));

        horizontalLayout->addWidget(lstCamera);

        tabInfoAndControl->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_3 = new QGridLayout(tab_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        cbxLighting = new QCheckBox(tab_3);
        cbxLighting->setObjectName(QString::fromUtf8("cbxLighting"));
        cbxLighting->setChecked(true);

        gridLayout_3->addWidget(cbxLighting, 0, 0, 1, 1);

        cbxBBox = new QCheckBox(tab_3);
        cbxBBox->setObjectName(QString::fromUtf8("cbxBBox"));

        gridLayout_3->addWidget(cbxBBox, 1, 0, 1, 1);

        cbxTextures = new QCheckBox(tab_3);
        cbxTextures->setObjectName(QString::fromUtf8("cbxTextures"));

        gridLayout_3->addWidget(cbxTextures, 2, 0, 1, 1);

        cbxDrawAxes = new QCheckBox(tab_3);
        cbxDrawAxes->setObjectName(QString::fromUtf8("cbxDrawAxes"));
        cbxDrawAxes->setChecked(true);

        gridLayout_3->addWidget(cbxDrawAxes, 3, 0, 1, 1);

        tabInfoAndControl->addTab(tab_3, QString());

        verticalLayout->addWidget(tabInfoAndControl);

        verticalLayout->setStretch(0, 5);
        verticalLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabInfoAndControl->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        grpFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        butOpenFile->setText(QApplication::translate("MainWindow", "Open file", nullptr));
        lblFileName_Label->setText(QApplication::translate("MainWindow", "File name", nullptr));
        lblLoadTime_Label->setText(QApplication::translate("MainWindow", "Load time, s", nullptr));
        lblLoadTime->setText(QString());
        butExport->setText(QApplication::translate("MainWindow", "Export", nullptr));
        lblExportTime_Label->setText(QApplication::translate("MainWindow", "Export time, s", nullptr));
        lblExportTime->setText(QString());
        grpInfo->setTitle(QApplication::translate("MainWindow", "Info", nullptr));
        lblRenderTime_Label->setText(QApplication::translate("MainWindow", "Render time, ms", nullptr));
        lblRenderTime->setText(QString());
        lblMeshCount_Label->setText(QApplication::translate("MainWindow", "Meshes", nullptr));
        lblFaceCount_Label->setText(QApplication::translate("MainWindow", "Faces", nullptr));
        lblMeshCount->setText(QString());
        lblFaceCount->setText(QString());
        lblVertexCount_Label->setText(QApplication::translate("MainWindow", "Vertices", nullptr));
        lblVertexCount->setText(QString());
        lblLightCount_Label->setText(QApplication::translate("MainWindow", "Lights", nullptr));
        lblCameraCount_Label->setText(QApplication::translate("MainWindow", "Cameras", nullptr));
        lblHasAnimation_Label->setText(QApplication::translate("MainWindow", "Animation", nullptr));
        lblShaderCount_Label->setText(QApplication::translate("MainWindow", "Shaders", nullptr));
        lblLightCount->setText(QString());
        lblCameraCount->setText(QString());
        lblShaderCount->setText(QString());
        lblHasAnimation->setText(QString());
        lblDistance_Label->setText(QApplication::translate("MainWindow", "Distance", nullptr));
        lblDistance->setText(QString());
        grpDynamics->setTitle(QApplication::translate("MainWindow", "Dynamics", nullptr));
        butAnimationStart->setText(QApplication::translate("MainWindow", "Animation start", nullptr));
        butAnimationStop->setText(QApplication::translate("MainWindow", "Animation stop", nullptr));
        tabInfoAndControl->setTabText(tabInfoAndControl->indexOf(tab), QApplication::translate("MainWindow", "Log", nullptr));
#ifndef QT_NO_TOOLTIP
        lstLight->setToolTip(QApplication::translate("MainWindow", "Light sources of the scene", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lstCamera->setToolTip(QApplication::translate("MainWindow", "Cameras of the scene", nullptr));
#endif // QT_NO_TOOLTIP
        tabInfoAndControl->setTabText(tabInfoAndControl->indexOf(tab_2), QApplication::translate("MainWindow", "Lights and cameras", nullptr));
#ifndef QT_NO_TOOLTIP
        cbxLighting->setToolTip(QApplication::translate("MainWindow", "Enable/Disable OpenGL lighting", nullptr));
#endif // QT_NO_TOOLTIP
        cbxLighting->setText(QApplication::translate("MainWindow", "Lighting", nullptr));
        cbxBBox->setText(QApplication::translate("MainWindow", "Scene BBox", nullptr));
        cbxTextures->setText(QApplication::translate("MainWindow", "Textures", nullptr));
        cbxDrawAxes->setText(QApplication::translate("MainWindow", "Show Axes", nullptr));
        tabInfoAndControl->setTabText(tabInfoAndControl->indexOf(tab_3), QApplication::translate("MainWindow", "Control", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
