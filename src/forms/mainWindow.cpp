#include "mainWindow.h"
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QUrl>
#include <qdesktopservices.h>

MainWindow::MainWindow(QObject *parent)
{
}

void MainWindow::onReportProblemTriggered()
{
   QDesktopServices::openUrl(QUrl("https://github.com/BunchSoftware/Formula-Plus/issues/new"));
}

void MainWindow::onSuggestFeatureTriggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/BunchSoftware/Formula-Plus/issues/new"));
}


void on_about_programm_triggered(){

}

void MainWindow::onGetReviewTriggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/BunchSoftware/Formula-Plusr/issues/new"));
}

void MainWindow::onAboutDocumentationTriggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/BunchSoftware/Formula-Plus/blob/master/doc/ru/index.md"));
}

void MainWindow::onAboutProgramTriggered()
{

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
