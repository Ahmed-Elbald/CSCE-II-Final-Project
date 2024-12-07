
#ifndef CSCE_II_FINAL_PROJECT_SETTINGSMANAGER_H
#define CSCE_II_FINAL_PROJECT_SETTINGSMANAGER_H

#include <QSettings>

class SettingsManager {
public:
    SettingsManager();
    ~SettingsManager();
    QSettings * settings = nullptr;

};

extern SettingsManager SM;

#endif //CSCE_II_FINAL_PROJECT_SETTINGSMANAGER_H
