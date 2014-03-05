#ifndef PLUGINS_DATABASES_CACHE_COMMON_H
#define PLUGINS_DATABASES_CACHE_COMMON_H

#include <QByteArray>

#include <obj_types.h>
#include <streams.h>

namespace plugins
{
  namespace databases
  {
    void fileBinStreamToQByteArray( QByteArray& Dst, d_ref<d_file_bin_stream> Src );
    void qByteArrayToFileBinStream( d_ref<d_file_bin_stream> Dst, const QByteArray& Src );
  }
}

#endif // PLUGINS_DATABASES_CACHE_COMMON_H
