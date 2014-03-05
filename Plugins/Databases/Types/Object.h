#ifndef PLUGINS_DATABASES_TYPES_OBJECTS_H
#define PLUGINS_DATABASES_TYPES_OBJECTS_H

#include <QString>

namespace plugins
{
  namespace databases
  {
    class Object
    {
    public:
      Object( bool SaveOnDestroy = false )
        : CanSave(SaveOnDestroy)
      {}

      virtual QString getID() = 0;
      
      void setCanSaveOnDestroy( bool Value )
      {
        CanSave = Value;
      }

    protected:
      bool CanSave;
    };
  }
}

typedef plugins::databases::Object DBObject;

#endif // PLUGINS_DATABASES_TYPES_OBJECTS_H