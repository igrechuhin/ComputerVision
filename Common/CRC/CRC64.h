#ifndef COMMON_CRC64_H
#define COMMON_CRC64_H

#include <QtGlobal>

namespace common
{
  // Interface definition for 64-bit CRC (cyclic redundancy check) class:
  //     Polynomial:                 E543279765927881
  //     Initial CRC register value: FFFFFFFFFFFFFFFF
  //     Reflected input and output: No
  //     Inverted final output:      No
  //     CRC of string "123456789":  44F0026F7CFAA3EC
  class CRC64
  {
  public:
    CRC64();
    CRC64( const uchar* Buffer, quint32 Size );

    void reset();

    void Compute( const uchar* Buffer, quint32 Size );

    void Compute( uchar Value );

    operator qint64() const;

  private:
    qint64 CRC;
  };
}

#endif // COMMON_CRC64_H
