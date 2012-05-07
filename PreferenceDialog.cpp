#include <QtGui>
#include <iostream>
#include "PreferenceDialog.h"
#include "ScreenShotter.h"
#include "ui_PreferenceDialog.h"
#include "EasyShot.h"

PreferenceDialog::PreferenceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferenceDialog)
{
    ui->setupUi(this);

    //Add items for comboBoxShootingMode
    ui->comboBoxShootingMode->addItem("Full Screen",ScreenShotter::Fullscreen);
    ui->comboBoxShootingMode->addItem("Mouse Selection",ScreenShotter::MouseSelection);
    connect(ui->buttonBox,SIGNAL(accepted()), this,SLOT(writeSettings()));

    initSettings();
}

PreferenceDialog::~PreferenceDialog()
{
    delete ui;
}

void PreferenceDialog::initSettings()
{
    AppSettings* settings = EasyShot::app()->settings();
    //mode tab
    ui->comboBoxShootingMode->setCurrentIndex(settings->getSetting(ShootingMode,0).toInt());

    //interface tab
    ui->checkBoxCloseToTray->setChecked(settings->getSetting(CloseToTray,false).toBool());
    ui->checkBoxStartMinimized->setChecked(settings->getSetting(StartMinimized, false).toBool());
    ui->checkBoxPlaySound->setChecked(settings->getSetting(PlaySound, false).toBool());
}


void PreferenceDialog::writeSettings()
{
    AppSettings* settings = EasyShot::app()->settings();
    //mode tab
    settings->setSetting(ShootingMode, ui->comboBoxShootingMode->currentIndex());

    //inteface tab
    settings->setSetting(CloseToTray,ui->checkBoxCloseToTray->isChecked());
    settings->setSetting(StartMinimized, ui->checkBoxStartMinimized->isChecked());
    settings->setSetting(PlaySound, ui->checkBoxPlaySound->isChecked());
}
