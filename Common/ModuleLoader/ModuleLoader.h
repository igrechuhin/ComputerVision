#ifndef COMMON_MODULELOADER_H
#define COMMON_MODULELOADER_H

class QDir;

namespace common
{
  template <typename T, typename ContainerT>
  ContainerT loadModules( const QDir& Folder );
}

#endif // COMMON_MODULELOADER_H
