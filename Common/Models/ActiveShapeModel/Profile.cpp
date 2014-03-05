#include "Profile.h"

#include <QDataStream>

QDataStream& operator >> (QDataStream& Stream, common::models::Profile::PointStatistic& Value)
{
  for (quint8 index(0); index < common::models::Profile::ProfilesCount; index++)
  {
    Stream >> Value.ProfileType[index].Mean;
    Stream >> Value.ProfileType[index].InvCovar;
  }
  return Stream;
}

QDataStream& operator << (QDataStream& Stream, const common::models::Profile::PointStatistic& Value)
{
  for (quint8 index(0); index < common::models::Profile::ProfilesCount; index++)
  {
    Stream << Value.ProfileType[index].Mean;
    Stream << Value.ProfileType[index].InvCovar;
  }
  return Stream;
}

QDataStream& operator>>( QDataStream& Stream, common::models::Profile& Value )
{
  quint8 type;
  Stream >> type;
  Value.PointType = static_cast<common::models::Profile::TypeOption>(type);
  Stream >> Value.Points;
  for (quint8 index(0); index < common::models::Profile::ProfilesCount; index++)
  {
    Stream >> Value.PixSearch[index];
  }
  Stream >> Value.MaxSearchIters;
  Stream >> Value.QuialifyingDisp;
  return Stream;
}

QDataStream& operator<<( QDataStream& Stream, const common::models::Profile& Value )
{
  Stream << quint8(Value.PointType);
  Stream << Value.Points;
  for (quint8 index(0); index < common::models::Profile::ProfilesCount; index++)
  {
    Stream << Value.PixSearch[index];
  }
  Stream << Value.MaxSearchIters;
  Stream << Value.QuialifyingDisp;
  return Stream;
}
