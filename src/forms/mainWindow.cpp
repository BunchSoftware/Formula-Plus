#include "mainWindow.h"
#include <QUrl>
#include <qdesktopservices.h>

MainWindow::MainWindow(QObject *parent)
{
}

void MainWindow::onReportProblemTriggered()
{
   QDesktopServices::openUrl(QUrl("https://github.com/BunchSoftware/Physical-Calculator/issues/new"));
}

void MainWindow::onSuggestFeatureTriggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/BunchSoftware/Physical-Calculator/issues/new"));
}


void on_about_programm_triggered(){

}

void MainWindow::onGetReviewTriggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/BunchSoftware/Physical-Calculator/issues/new"));
}

void MainWindow::onAboutDocumentationTriggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/BunchSoftware/Physical-Calculator/blob/master/Documentation/ru/index.md"));
}

void MainWindow::onAboutProgrammTriggered(){

}

void MainWindow::onLastProjectTriggered()
{

}

void MainWindow::onOpenProjectTriggered()
{

}

void MainWindow::onSaveProjectTriggered()
{

}

void MainWindow::onCloseProjectTriggered()
{

}

void MainWindow::onCreateProjectTriggered()
{

}
