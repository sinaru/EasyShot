#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QtGui>


enum EasyShotConfiguration
{
    CloseToTray,
    CustomSaveLocation,
    PlaySound,
    FileType,
    LastSavedLocation,
    ShootingMode,
    StartMinimized,
    SaveAtLastSavedLocation,
    MainWindowPos
};

class AppSettings
{
public:
    AppSettings();
    const QSettings& getSettings();
    QVariant getSetting(EasyShotConfiguration type,
                        const QVariant &defaultValue = QVariant());

    void setSetting(EasyShotConfiguration type, QVariant value);

private:
    void initSettings();
    std::map<EasyShotConfiguration, QString> settingsMap;
    QSettings _appSettings;
};
#endif // APPSETTINGS_H
