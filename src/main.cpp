#include <QApplication>
#include <QFile>
#include <forms/mainWindow.h>
#include "QQmlApplicationEngine"
#include "QGuiApplication"
#include "forms/parserForm.h"
#include "forms/calculateForm.h"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  qmlRegisterType<ParserForm>("Forms", 1, 0, "ParserForm");
  qmlRegisterType<CalculateForm>("Forms", 1, 0, "CalculateForm");
  qmlRegisterType<MainWindow>("Forms", 1, 0, "MainWindow");

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/mainWindow.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);

  app.setWindowIcon(QIcon(":/images/logotype.png"));
  return app.exec();
}
