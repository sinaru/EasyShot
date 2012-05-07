#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "PreferenceDialog.h"
#include "AboutDialog.h"

#include "EasyShot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectMenuActions();
    loadRelatedSettings();
    init();

    connect(ui->screenshotButton, SIGNAL(clicked()), EasyShot::app(), SLOT(takeScreenshot()));
}

void MainWindow::init()
{
    // It is important to set the location of the window.
    // When the tray icon is left clicked, the main window hides. If this was not
    // done the window is always shown in at the left top corner of the screen,
    // when tray icon is clicked again.
    move(_initialWindowPos);
}

MainWindow::~MainWindow()
{
    writeRelatedSettings();
    delete ui;
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        setVisible(!isVisible());
        break;
    default:
        ;
    }
}

void MainWindow::loadRelatedSettings()
{
    _closeToTray = EasyShot::app()->settings()->getSetting(CloseToTray).toBool();
    _initialWindowPos = EasyShot::app()->settings()->getSetting(MainWindowPos, QPoint(200,200))
            .toPoint();
}

void MainWindow::writeRelatedSettings()
{
    EasyShot::app()->settings()->setSetting(MainWindowPos, pos());
}

void MainWindow::actionPreferenceDialog()
{
    PreferenceDialog * dialog = new PreferenceDialog(this);

    // If 'OK' is clicked on preference dialog, load the settings again relavent
    // to the main window
    if(dialog->exec())
        loadRelatedSettings();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(_closeToTray)
    {
        hide();
        event->ignore();
    }
}

void MainWindow::actionAboutDialog()
{
    AboutDialog *dialog = new AboutDialog(this);
    dialog->exec();
}

void MainWindow::actionQuit()
{
    qApp->exit();
}

void MainWindow::connectMenuActions()
{
    connect(ui->actionAbout, SIGNAL(triggered()),this,SLOT(actionAboutDialog()));
    connect(ui->actionPreference,SIGNAL(triggered()),this,SLOT(actionPreferenceDialog()));
    connect(ui->actionQuit, SIGNAL(triggered()),this, SLOT(actionQuit()));
}
