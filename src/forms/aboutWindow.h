#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H
#include <QDialog>

class AboutWindow : public QObject
{
  Q_OBJECT

public:
  explicit AboutWindow(QObject *parent = nullptr);

private slots:

private:
};

#endif // ABOUTWINDOW_H
