#include "parser.h"
#include "library/interpreter.h"

using namespace std;

Parser::Parser(QObject *parent) : QObject(parent)
{

}

QString Parser::textOutput()
{
  return m_textOutput;
}

QString Parser::textInput()
{
  return m_textInput;
}

void Parser::setTextOutput(QString value)
{
  if(m_textOutput != value)
  {
      m_textInput = value;
      emit textOutputChanged();
  }
}

void Parser::setTextInput(QString value)
{
  if(m_textInput != value)
  {
         qDebug("123");
      m_textInput = value;
      emit textInputChanged();
    }
}

void Parser::calculate()
{
  try {
    std::wstring text = textInput().toStdWString();
    double result = Interpreter::InterpreteExperssion(text);
    setTextOutput("Результат: " + QString::number(result));
  }
  catch (...) {
    setTextOutput("Ошибка в выражении");
  }
}
