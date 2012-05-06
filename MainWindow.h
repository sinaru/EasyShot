#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
        void actionPreferenceDialog();
        void actionQuit();
        void actionAboutDialog();
        void iconActivated(QSystemTrayIcon::ActivationReason reason);

private slots:

private:
        void init();
        void connectMenuActions();
        void loadRelatedSettings();
        void writeRelatedSettings();
        void closeEvent(QCloseEvent *event);
    Ui::MainWindow *ui;
    bool _closeToTray;
    QPoint _initialWindowPos;
};

#endif // MAINWINDOW_H
