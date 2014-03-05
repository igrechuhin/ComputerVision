#include "ActiveShapeModel.h"

#include "../../../../Common/Settings/Settings.h"

#ifdef MATLAB
#include "../../../../Adapters/Matlab/ActiveShapeModel.h"
#include "../../../../Adapters/Matlab/Frame.h"
#include "../../../../Adapters/Matlab/AlgDetOutput.h"
#include "../../../../Adapters/Matlab/AlgVecShpOutput.h"
#endif // MATLAB

#include <QApplication>
#include <QDir>

namespace
{
  const QString MODEL_FILE_NAME("Model.asm");
#ifdef MATLAB
  const QString MATLAB_ASM_DLL("MatlabASM.dll");
  const QString MATLAB_INIT("MatlabASMInitialize");
  const QString MATLAB_DEINIT("MatlabASMTerminate");
  const QString MATLAB_RUN("?ASM@@YAXHAAVmwArray@@ABV1@111@Z");
#endif // MATLAB
}

namespace algorithms
{
  namespace vectorization
  {
    namespace shape
    {
      ActiveShapeModel::ActiveShapeModel()
        : Model()
#ifdef MATLAB
       ,MatlabDll(),
        MatlabInitFunc(NULL),
        MatlabDeInitFunc(NULL),
        MatlabRunFunc(NULL),
        MatlabModel()
#endif // MATLAB
      {
      }

      ActiveShapeModel::~ActiveShapeModel()
      {
#ifdef MATLAB
        deinitMATLAB();
#endif // MATLAB
      }

      bool ActiveShapeModel::init( ContextType& Context )
      {
        using namespace common;
        QDir dataDir(qApp->applicationDirPath());
        Settings settings;
        QString dataPath(settings.get(Settings::SettingsDataVectorizationPath).toString());
        dataPath += getName().prepend("/");
        bool dirExist(dataDir.cd(dataPath));
        Q_ASSERT(dirExist);
        dataPath = dataDir.absolutePath() + "/";
        if (dirExist)
        {
          QString modelFilePath(settings.get(Settings::SettingsVectorizationActiveShapeModelFileName, MODEL_FILE_NAME).toString());
          bool initOK(Model.read(dataPath + modelFilePath) == models::ActiveShapeModel::StateOK);
          Q_ASSERT(initOK);
#ifdef MATLAB
          QString dllFilePath(dataPath + settings.get(Settings::SettingsVectorizationActiveShapeModelMatlabDll, MATLAB_ASM_DLL).toString());
          initOK &= initMATLAB(dllFilePath);
          Q_ASSERT(initOK);
          adapters::Convert(MatlabModel, Model);
#endif // MATLAB
          return initOK;
        }
        return false;
      }

      void ActiveShapeModel::process( ContextType& Context, const Frame& Image )
      {
        Context.Vectorization.Shape.Out.remove(getType());
#ifdef MATLAB
        return runMATLAB(Context, Image);
#endif // MATLAB
      }

#ifdef MATLAB
      bool ActiveShapeModel::initMATLAB( const QString& DllPath )
      {
        MatlabDll.setFileName(DllPath);
        MatlabInitFunc  = static_cast<MatlabInitPtr>(MatlabDll.resolve(MATLAB_INIT.toAscii().constData()));
        MatlabDeInitFunc  = static_cast<MatlabDeInitPtr>(MatlabDll.resolve(MATLAB_DEINIT.toAscii().constData()));
        MatlabRunFunc  = static_cast<MatlabRunPtr>(MatlabDll.resolve(MATLAB_RUN.toAscii().constData()));
        if (MatlabInitFunc && MatlabDeInitFunc && MatlabRunFunc)
        {
          try
          {
            MatlabInitFunc();
          }
          catch(...)
          {
            Q_ASSERT(false);
          }
          return true;
        }
        else
          return false;
      }

      void ActiveShapeModel::deinitMATLAB()
      {
        if (!MatlabDll.isLoaded() || !MatlabDeInitFunc)
          return;
        MatlabDeInitFunc();
      }

      void ActiveShapeModel::runMATLAB( ContextType& Context, const Frame& Image )
      {
        const AlgType& detector(Context.Vectorization.Shape.In.Detector);
        mwArray grayImage;
        adapters::Convert(grayImage, Image);
        int faceIndex(1);
        int facesCount(Context.Detection.Out.count(detector));
        mwArray faces(facesCount, 1, mxCELL_CLASS);
        foreach(const AlgDetOutput& detOut, Context.Detection.Out.values(detector))
        {
          Q_ASSERT(faceIndex <= facesCount);
          adapters::Convert(faces.Get(2, faceIndex++, 1), detOut);
        }
        mwArray detectorToUse(detector);
        int nargout(1);
        mwArray shapes;
        try
        {
          MatlabRunFunc(nargout, shapes, grayImage, MatlabModel, faces, detectorToUse);
          QVector<AlgVecShpOutput> shapesOut;
          adapters::Convert(shapesOut, shapes);
          foreach(const AlgVecShpOutput& shp, shapesOut)
          {
            Context.Vectorization.Shape.Out.insert(getType(), shp);
          }
        }
        catch (const std::exception& e)
        {
          const char *errorMessage(e.what());
          Q_ASSERT(false);
        }
      }
#endif // MATLAB
    }
  }
}
Q_EXPORT_PLUGIN2(ActiveShapeModel, algorithms::vectorization::shape::ActiveShapeModel);
