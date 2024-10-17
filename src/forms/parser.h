#ifndef PARSER_H
#define PARSER_H

#include <QWidget>

class ParserForm : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString textOutput READ textOutput WRITE setTextOutput NOTIFY textOutputChanged)
  Q_PROPERTY(QString textInput READ textInput WRITE setTextInput NOTIFY textInputChanged)

public:
  explicit ParserForm(QObject *parent = nullptr);
  QString textOutput();
  QString textInput();
  Q_INVOKABLE void setTextOutput(QString value);
  Q_INVOKABLE void setTextInput(QString value);

signals:
  void textOutputChanged();
  void textInputChanged();

public slots:
  void calculate();

private:
  QString m_textOutput = "Результат: 0";
  QString m_textInput;
};

#endif // PARSER_H
