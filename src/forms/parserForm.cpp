#include "parserForm.h"
#include "library/interpreter.h"

using namespace std;

ParserForm::ParserForm(QObject *parent)
{

}

QString ParserForm::textOutput()
{
  return m_textOutput;
}

QString ParserForm::textInput()
{
  return m_textInput;
}

void ParserForm::setTextOutput(QString value)
{
  if(m_textOutput != value)
  {
      m_textOutput = value;
      emit textOutputChanged();
  }
}

void ParserForm::setTextInput(QString value)
{
  if(m_textInput != value)
  {
      m_textInput = value;
      emit textInputChanged();
    }
}

void ParserForm::calculate()
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
