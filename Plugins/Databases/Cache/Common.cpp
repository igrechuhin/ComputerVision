#include "Common.h"

namespace
{
  const qint64 MAX_CHUNK_SIZE(32000);
}

namespace plugins
{
  namespace databases
  {
    void fileBinStreamToQByteArray( QByteArray& Dst, d_ref<d_file_bin_stream> Src )
    {
      Src->rewind();
      Dst.clear();
      qint64 chunkSize;
      for (qint64 dataToRead(Src->size()); dataToRead; dataToRead -= chunkSize)
      {
        chunkSize = qMin(dataToRead, MAX_CHUNK_SIZE);
        d_binary imageDataFromStream;
        Src->read(d_int(chunkSize), imageDataFromStream);
        Dst.append(imageDataFromStream.get_buf(), imageDataFromStream.get_size());
      }
    }

    void qByteArrayToFileBinStream( d_ref<d_file_bin_stream> Dst, const QByteArray& Src )
    {
      Dst->rewind();
      const char* dataPtr(Src.constData());
      qint64 chunkSize;
      for (qint64 dataToSave(Src.size()); dataToSave; dataToSave -= chunkSize, dataPtr += chunkSize)
      {
        chunkSize = qMin(dataToSave, MAX_CHUNK_SIZE);
        d_binary imageDataForStream;
        imageDataForStream.assign(dataPtr, static_cast<byte_size_t>(chunkSize));
        d_status writeImageStatus(Dst->write(imageDataForStream));
        Q_ASSERT(writeImageStatus.get_code() == 0);
      }
    }
  }
}
