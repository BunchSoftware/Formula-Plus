#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QObject
{
  Q_OBJECT

public:
  explicit MainWindow(QObject *parent = nullptr);
  Q_INVOKABLE void onReportProblemTriggered();
  Q_INVOKABLE void onSuggestFeatureTriggered();
  Q_INVOKABLE void onGetReviewTriggered();
  Q_INVOKABLE void onAboutDocumentationTriggered();
  Q_INVOKABLE void onAboutProgrammTriggered();
  Q_INVOKABLE void onLastProjectTriggered();
  Q_INVOKABLE void onOpenProjectTriggered();
  Q_INVOKABLE void onSaveProjectTriggered();
  Q_INVOKABLE void onCloseProjectTriggered();
  Q_INVOKABLE void onCreateProjectTriggered();

private:
};

#endif // MAINWINDOW_H
