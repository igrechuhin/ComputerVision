#ifndef FACEDBSHELL_H
#define FACEDBSHELL_H

#include "../../Plugins/Sources/Interface.h"
#include "../../Plugins/Databases/Interface.h"

#include "../../Algorithms/Interface.h"

#include <QtGui/QMainWindow>
#include "ui_FaceDBShell.h"

class FaceDBShell : public QMainWindow
{
  Q_OBJECT

public:
  FaceDBShell(QWidget *parent = 0, Qt::WFlags flags = 0);

  ~FaceDBShell();

private:
  void initContext();
  void loadPlugins();
  void loadAlgorithms();
  void openDBConnection();
  void initUI();
  QString getFilters();

  QString getImageIDinDB();
  void processImage();
  void processFaces();
  void processDetectors();

  void processShapes();

  void setNewImageInfo();

  void setDefaultLocations();
  void setRestLocations();
  void setShapes();

  void findFaces();
  qint16 getFacesCount();
  AlgType getMaxFacesCountDetector();
  qint16 getFaceIndex();

  void uiUpdateImageInfo();
  void uiUpdateFacesInfo();
  void uiUpdatePersonsInfo();
  void uiUpdateDetectorsInfo();
  void uiUpdateShapesInfo();
  void uiEnableControls();

public slots:
  void log( int Severity, const QString& LogMessage );

private slots:
  void on_openImage_clicked();
  void on_selectDetector_currentIndexChanged( int Index );
  void on_minFaceSizeSlider_valueChanged( int Value );
  void on_gender_stateChanged( int State );
  void on_glasses_stateChanged( int State );
  void on_closedForehead_stateChanged( int State );
  void on_moustache_stateChanged( int State );
  void on_closedEyebrow_stateChanged( int State );
  void on_beard_stateChanged( int State );
  void on_orientation12_clicked();
  void on_orientation13_clicked();
  void on_orientation14_clicked();
  void on_orientation21_clicked();
  void on_orientation22_clicked();
  void on_orientation23_clicked();
  void on_orientation24_clicked();
  void on_orientation25_clicked();
  void on_orientation32_clicked();
  void on_orientation33_clicked();
  void on_orientation34_clicked();
  void on_age_valueChanged( int Value );


private:
  Ui::FaceDBShellClass ui;

  SrcInterface* Source;
  DBInterface* Database;
  AlgMap Algorithms;

  QScopedPointer<AlgContext> Context;

  QSharedPointer<DBPhotos> Image;
  quint8 photoMiddleBrightness; // for speedup

  bool IsNewImage;
};

#endif // FACEDBSHELL_H
