#include "ActiveShapeModel.h"

#include "Matrix.h"
#include "QPointF.h"

#include "../../Common/Models/ActiveShapeModel/ActiveShapeModel.h"

#include <QtGlobal>

#include <mclcppclass.h>

using namespace common::models;
using namespace adapters;

void Convert( mwArray& Output, const Scale& Input )
{
  const char* fields[] = {"levels", "factor"};
  mwArray scale(1, 1, 2, fields);
  scale.Get(fields[0], 1, 1).Set(mwArray(static_cast<qreal>(Input.Levels)));
  scale.Get(fields[1], 1, 1).Set(mwArray(Input.Factor));
  Output.Set(scale);
}

void Convert( mwArray& Output, const QVector<LandmarkTriangle>& Input )
{
  mwArray tmp(Input.size(), 2, mxINT16_CLASS);
  for (int index(1); index <= Input.size(); index++)
  {
    tmp.Get(2, index, 1).Set(mwArray(Input[index-1].iPrev));
    tmp.Get(2, index, 2).Set(mwArray(Input[index-1].iNext));
  }
  Output.Set(tmp);
}

void Convert( mwArray& Output, const QVector<Profile::PointStatistic>& Input )
{
  const char* fields[] = {"mean", "invCovar"};
  mwArray tmp(Input.size(), Profile::ProfilesCount, mxCELL_CLASS);
  for (int index(0); index < Input.size(); index++)
  {
    for (quint8 profileIndex(Profile::Profile1D); profileIndex < Profile::ProfilesCount; profileIndex++)
    {
      mwArray pointProfile(1, 1, 2, fields);
      Convert(pointProfile.Get(fields[0], 1, 1), Input[index].ProfileType[profileIndex].Mean);
      Convert(pointProfile.Get(fields[1], 1, 1), Input[index].ProfileType[profileIndex].InvCovar);
      tmp.Get(2, index+1, profileIndex+1).Set(pointProfile);
    }
  }
  Output.Set(tmp);
}

void Convert( mwArray& Output, const Profile& Input )
{
  const char* fields[] = {"type", "pointProfile", "maxSearchIters", "quialifyingDisp", "pixSearch"};
  mwArray profile(1, 1, 5, fields);
  profile.Get(fields[0], 1, 1).Set(mwArray(Input.PointType+1)); // workaround for matlab simplification
  Convert(profile.Get(fields[1], 1, 1), Input.Points);
  profile.Get(fields[2], 1, 1).Set(mwArray(Input.MaxSearchIters));
  profile.Get(fields[3], 1, 1).Set(mwArray(Input.QuialifyingDisp));
  mwArray pixSearch(Profile::ProfilesCount, 1, mxDOUBLE_CLASS);
  for (quint8 index(Profile::Profile1D); index < Profile::ProfilesCount; index++)
  {
    pixSearch.Get(2, index + 1, 1).Set(mwArray(Input.PixSearch[index]));
  }
  profile.Get(fields[4], 1, 1).Set(pixSearch);
  Output.Set(profile);
}

void Convert( mwArray& Output, const QVector<Profile>& Input )
{
  mwArray tmp(Input.size(), 1, mxCELL_CLASS);
  for (int index(1); index <= Input.size(); index++)
  {
    Convert(tmp.Get(2, index, 1), Input[index-1]);
  }
  Output.Set(tmp);
}

void Convert( mwArray& Output, const PrincipalComponents& Input )
{
  const char* fields[] = {"eigenValues", "eigenVectors", "eigenVectorsInverse",
    "nEigs", "nEigs2D", "nEigsFinal",
    "bMax", "bMaxFinal"};
  mwArray principalComponents(1, 1, 8, fields);
  Convert(principalComponents.Get(fields[0], 1, 1), Input.EigenValues);
  Convert(principalComponents.Get(fields[1], 1, 1), Input.EigenVectors);
  Convert(principalComponents.Get(fields[2], 1, 1), Input.EigenVectors.transposed());
  principalComponents.Get(fields[3], 1, 1).Set(mwArray(Input.NEigs));
  principalComponents.Get(fields[4], 1, 1).Set(mwArray(Input.NEigs2D));
  principalComponents.Get(fields[5], 1, 1).Set(mwArray(Input.NEigsFinal));
  principalComponents.Get(fields[6], 1, 1).Set(mwArray(Input.BMax));
  principalComponents.Get(fields[7], 1, 1).Set(mwArray(Input.BMaxFinal));
  Output.Set(principalComponents);
}

void Convert( mwArray& Output, const MeanShape& Input )
{
  const char* fields[] = {"mean", "standardFaceWidth", "detector"};
  mwArray modelShape(1, 1, 3, fields);
  Convert(modelShape.Get(fields[0], 1, 1), Input.Value);
  modelShape.Get(fields[1], 1, 1).Set(mwArray(Input.FaceWidth));
  mwArray detectors(algorithms::AlgorithmsDetectorsEnd, 1, mxCELL_CLASS);
  for (int index(algorithms::AlgorithmsDetectorsBegin); index < algorithms::AlgorithmsDetectorsEnd; index++)
  {
    const char* detectorFields[] = {"scale", "shift"};
    mwArray detector(1, 1, 2, detectorFields);
    detector.Get(detectorFields[0], 1, 1).Set(mwArray(Input.Detectors[index].Scale));
    mwArray shift(1, 2, mxDOUBLE_CLASS);
    Convert(shift, Input.Detectors[index].Shift);
    detector.Get(detectorFields[1], 1, 1).Set(shift);
    detectors.Get(2, index+1, 1).Set(detector);
  }
  modelShape.Get(fields[2], 1, 1).Set(detectors);
  Output.Set(modelShape);
}

namespace adapters
{
  void Convert( mwArray& Output, ActiveShapeModel& Input )
  {
    const char* fields[] = {"principalComponents", "shape", "profile", "landmarks", "scale", "type"};
    mwArray matlabModel(1, 1, 6, fields);
    Convert(matlabModel.Get(fields[0], 1, 1), Input.PrincComp);
    Convert(matlabModel.Get(fields[1], 1, 1), Input.Shape);
    Convert(matlabModel.Get(fields[2], 1, 1), Input.PyrLevels);
    Convert(matlabModel.Get(fields[3], 1, 1), Input.Landmarks);
    Convert(matlabModel.Get(fields[4], 1, 1), Input.ScaleObj);
    matlabModel.Get(fields[5], 1, 1).Set(mwArray(Input.Complexity));
    Output.Set(matlabModel);
  }
}
