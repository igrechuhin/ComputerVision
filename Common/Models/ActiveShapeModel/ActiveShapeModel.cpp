#include "ActiveShapeModel.h"

#include <QFile>

namespace
{
  const QDataStream::ByteOrder BYTE_ORDER = QDataStream::LittleEndian;
}

namespace common
{
  namespace models
  {
    ActiveShapeModel::ActiveShapeModel()
      : Complexity(RealFlag),
        PrincComp(),
        Shape(),
        PyrLevels(),
        Landmarks(),
        ScaleObj()
    {
    }

    ActiveShapeModel::~ActiveShapeModel()
    {
    }

    ActiveShapeModel::State ActiveShapeModel::read( const QString& FilePath )
    {
      QFile modelFile(FilePath);
      if (!modelFile.exists())
        return StateFileNotFound;

      if (!modelFile.open(QIODevice::ReadOnly))
        return StatePermissionError;

      QDataStream modelFileStream(&modelFile);
      modelFileStream.setByteOrder(BYTE_ORDER);

      quint32 type;
      modelFileStream >> type;
      if (type != Complexity)
        return StateInvalidModel;

      modelFileStream >> PrincComp;
      modelFileStream >> Shape;
      modelFileStream >> PyrLevels;
      modelFileStream >> Landmarks;
      modelFileStream >> ScaleObj;
      return StateOK;
    }

    ActiveShapeModel::State ActiveShapeModel::write( const QString& FilePath )
    {
      QFile modelFile(FilePath);
      if (!modelFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return StatePermissionError;

      QDataStream modelFileStream(&modelFile);
      modelFileStream.setByteOrder(BYTE_ORDER);

      modelFileStream << quint32(Complexity);
      modelFileStream << PrincComp;
      modelFileStream << Shape;
      modelFileStream << PyrLevels;
      modelFileStream << Landmarks;
      modelFileStream << ScaleObj;
      return StateOK;
    }
  }
}