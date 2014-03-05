#ifndef PLUGINS_DATABASES_CACHE_OBJECT_H
#define PLUGINS_DATABASES_CACHE_OBJECT_H

#include "../Types/Object.h"

#include <QString>

#include <obj_types.h>
#include <database.h>

namespace plugins
{
  namespace databases
  {
    namespace cache
    {
      template <typename T>
      class Object : virtual public DBObject
      {
      public:
        Object( Database* Connection, const QString& ID, bool SaveOnDestroy );
        Object( Database* Connection, d_ref<T> Other );
        virtual ~Object();

        virtual QString getID();

        bool save(); 

        operator d_ref<T>();

      protected:
        d_ref<T> DBObj;
        Database* DBConnection;
      };

      template <typename T>
      QString Object<T>::getID()
      {
        return QString::fromStdString(DBObj->get_id());
      }

      template <typename T>
      bool Object<T>::save()
      {
        d_status dbSaveResult(DBObj->save());
        Q_ASSERT(dbSaveResult.get_code() == 0);
        return dbSaveResult.get_code() == 0;
      }

      template <typename T>
      Object<T>::Object( Database* Connection, const QString& ID , bool SaveOnDestroy )
        : DBObject(SaveOnDestroy),
          DBObj( ID.isEmpty() ? 
                  T::create_new(Connection) :
                  T::openid(Connection, reinterpret_cast<const wchar_t*>(ID.utf16()))),
          DBConnection(Connection)
      {
      }

      template <typename T>
      Object<T>::Object( Database* Connection, d_ref<T> Other )
        : DBObject(false),
          DBObj(Other),
          DBConnection(Connection)
      {
      }

      template <typename T>
      Object<T>::~Object()
      {
        if (CanSave)
        {
          int i = 0;
//           save();
        }
      }

      template <typename T>
      Object<T>::operator d_ref<T>()
      {
        return DBObj;
      }
    }
  }
}

#endif // PLUGINS_DATABASES_CACHE_OBJECT_H
