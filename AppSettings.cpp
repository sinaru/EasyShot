#include "AppSettings.h"

AppSettings::AppSettings()
{
    initSettings();
}


/**
  @note Use to set the string values of the application  settings
*/
void AppSettings::initSettings()
{
    //insert({EasyShotConfiguration, string})
    settingsMap.insert({ShootingMode,"ShootingMode"});
    settingsMap.insert({CloseToTray,"CloseToTray"});
    settingsMap.insert({StartMinimized, "StartMinimized"});
    settingsMap.insert({FileType, "FileType"});
    settingsMap.insert({LastSavedLocation,"LastSavedLocation"});
    settingsMap.insert({SaveAtLastSavedLocation, "SaveAtLastSavedLocation"});
    settingsMap.insert({CustomSaveLocation, "CustomSaveLocation"});
    settingsMap.insert({MainWindowPos,"MainWindowPos"});
}

const QSettings& AppSettings::getSettings()
{
    return _appSettings;
}

QVariant AppSettings::getSetting(EasyShotConfiguration type,
                                 const QVariant &defaultValue)
{
     return _appSettings.value(settingsMap[type].toUtf8().constData(),
                               defaultValue);
}

void AppSettings::setSetting(EasyShotConfiguration type, QVariant value)
{
    _appSettings.setValue((settingsMap[type]), value);
}
