#include "ModuleLoader.h"

#include "../../Algorithms/Interface.h"
#include "../../Plugins/Sources/Interface.h"
#include "../../Plugins/Databases/Interface.h"

#include <QMap>
#include <QDir>
#include <QPluginLoader>

namespace
{
  void addToContainer( AlgMap& Container, AlgInterface* ModulePtr )
  {
    Container.insert(ModulePtr->getType(), ModulePtr);
  }

  template <typename T>
  void addToContainer( QList<T*>& Container, T* ModulePtr )
  {
    Container.append(ModulePtr);
  }
}

namespace common
{
  template <typename T, typename ContainerT>
  ContainerT loadModules( const QDir& Folder )
  {
    ContainerT container;
    foreach (QString fileName, Folder.entryList(QDir::Files))
    {
      QPluginLoader loader(Folder.absoluteFilePath(fileName));
      T* modulePtr(qobject_cast<T*>(loader.instance()));
      if (modulePtr)
      {
        addToContainer(container, modulePtr);
      }
    }
    return container;
  }
}

namespace
{
  void inst()
  {
    QDir dir;
    common::loadModules<AlgInterface, AlgMap>(dir);
    common::loadModules<SrcInterface, SrcList>(dir);
    common::loadModules<DBInterface, DBList>(dir);
  }
}