#include "Settings.h"

namespace
{
const int COMPRESSION_LEVEL(9);
}

namespace common
{
  Settings::Settings()
  {
  }

  Settings::~Settings()
  {
  }

  QVariant Settings::get( Parameters Key, const QVariant& DefaultValue /*= QVariant() */ )
  {
    switch (Key)
    {
    case SettingsDataDetectionPath: return get(SettingsDataPath, "Data").toString().append("/Detection");
    case SettingsDataVectorizationPath: return get(SettingsDataPath, "Data").toString().append("/Vectorization");
    default: break;
    }
    QString keyPath(getKeyPath(Key));
    if (!contains(keyPath))
      set(Key, DefaultValue);
    QVariant val(value(keyPath));
    switch (Key)
    {
    case SettingsDatabaseUser:
    case SettingsDatabasePassword:
      {
        QByteArray byteValue(val.toByteArray());
        decrypt(byteValue);
        val = byteValue;
      }
    default:
      return val;
    }
  }

  void Settings::set( Parameters Key, QVariant Value )
  {
    switch (Key)
    {
    case SettingsDatabaseUser:
    case SettingsDatabasePassword:
      {
        QByteArray byteValue(Value.toByteArray());
        encrypt(byteValue);
        Value = byteValue;
      } break;
    case SettingsDataDetectionPath: 
    case SettingsDataVectorizationPath: Q_ASSERT(false);
    default: break;
    }
    setValue(getKeyPath(Key), Value);
  }

  void Settings::encrypt( QByteArray& Value )
  {
    Value = qCompress(Value, COMPRESSION_LEVEL);
  }

  void Settings::decrypt( QByteArray& Value )
  {
    Value = qUncompress(Value);
  }

  QString Settings::getKeyPath( Parameters Key )
  {

    switch (Key)
    {
    case SettingsPath:
      return "Path";
    case SettingsSourcePath:
      return getKeyPath(SettingsPath).prepend("Source/");
    case SettingsPluginsPath:
      return getKeyPath(SettingsPath).prepend("Plugins/");
    case SettingsDataPath:
      return getKeyPath(SettingsPath).prepend("Data/");
    case SettingsAlgorithms:
      return "Algorithms";
    case SettingsAlgorithmsPath:
      return getKeyPath(SettingsAlgorithms).append("/").append(getKeyPath(SettingsPath));
    case SettingsDetection:
      return "Detection";
    case SettingsDetectionViolaJonesClassifier:
      return getKeyPath(SettingsAlgorithms).append("/").append(getKeyPath(SettingsDetection)).append("/VJClassifier");
    case SettingsDetectionScaleFactor:
      return getKeyPath(SettingsAlgorithms).append("/").append(getKeyPath(SettingsDetection)).append("/ScaleFactor");
    case SettingsVectorization:
      return "Vectorization";
    case SettingsVectorizationActiveShapeModel:
      return "ActiveShapeModel";
    case SettingsVectorizationActiveShapeModelFileName:
      return getKeyPath(SettingsAlgorithms).append("/").append(getKeyPath(SettingsVectorization)).append("/").append(getKeyPath(SettingsVectorizationActiveShapeModel)).append("/FileName");
    case SettingsVectorizationActiveShapeModelMatlabDll:
      return getKeyPath(SettingsAlgorithms).append("/").append(getKeyPath(SettingsVectorization)).append("/").append(getKeyPath(SettingsVectorizationActiveShapeModel)).append("/DllName");
    case SettingsDatabase:
      return "Database";
    case SettingsDatabaseHost:
      return getKeyPath(SettingsDatabase).append("/Host");
    case SettingsDatabasePort:
      return getKeyPath(SettingsDatabase).append("/Port");
    case SettingsDatabaseNamespace:
      return getKeyPath(SettingsDatabase).append("/Namespace");
    case SettingsDatabaseUser:
      return getKeyPath(SettingsDatabase).append("/User");
    case SettingsDatabasePassword:
      return getKeyPath(SettingsDatabase).append("/Password");
    default: Q_ASSERT(false);
    }
    return QString();
  }
}
