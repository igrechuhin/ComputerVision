#ifndef COMMON_SETTINGS_H
#define COMMON_SETTINGS_H

#include <QSettings>

namespace common
{
  class Settings : private QSettings
  {
  public:

    enum Parameters
    {
      SettingsPath,
      SettingsSourcePath,
      SettingsPluginsPath,
      SettingsDataPath,
      SettingsDataDetectionPath,
      SettingsDataVectorizationPath,

      SettingsAlgorithms,
      SettingsAlgorithmsPath,
      SettingsDetection,
      SettingsDetectionViolaJonesClassifier,
      SettingsDetectionScaleFactor,
      SettingsVectorization,
      SettingsVectorizationActiveShapeModel,
      SettingsVectorizationActiveShapeModelFileName,
      SettingsVectorizationActiveShapeModelMatlabDll,

      SettingsDatabase,
      SettingsDatabaseHost,
      SettingsDatabasePort,
      SettingsDatabaseNamespace,
      SettingsDatabaseUser,
      SettingsDatabasePassword
    };

    Settings();
    ~Settings();

    QVariant get( Parameters Key, const QVariant& DefaultValue = QVariant() );
    void set( Parameters Key, QVariant Value );

  private:
    void encrypt( QByteArray& Value );
    void decrypt( QByteArray& Value );

    QString getKeyPath( Parameters Key );
  };
}

#endif // COMMON_SETTINGS_H
