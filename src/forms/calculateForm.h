#ifndef CALCULATEFORM_H
#define CALCULATEFORM_H

#include <QMainWindow>
#include "physicalCalculateForm.h"
#include "mainWindow.h"

class CalculateForm : public QObject
{
    Q_OBJECT
  Q_PROPERTY(QString textOutput READ textOutput WRITE setTextOutput NOTIFY textOutputChanged)
  Q_PROPERTY(QString textInput READ textInput WRITE setTextInput NOTIFY textInputChanged)


public:
    CalculateForm(QObject *parent = nullptr);
    QString textOutput();
    QString textInput();
    Q_INVOKABLE void setTextOutput(QString value);
    Q_INVOKABLE void setTextInput(QString value);
    Q_INVOKABLE void operations(QString contentButton);

signals:
    void textOutputChanged();
    void textInputChanged();



private:
    QString m_textOutput = "0" ;
    QString m_textInput;
};
#endif // MAINWINDOW_H
