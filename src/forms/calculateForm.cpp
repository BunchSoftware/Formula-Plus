#include "calculateForm.h"
#include "library/interpreter.h"

using namespace Interpreter;

CalculateForm::CalculateForm(QObject *parent)
{

}

QString CalculateForm::textOutput()
{
  return m_textOutput;
}

QString CalculateForm::textInput()
{
  return m_textInput;
}

void CalculateForm::setTextOutput(QString value)
{
  if(m_textOutput != value)
  {
      m_textOutput = value;
      emit textOutputChanged();
  }
}

void CalculateForm::setTextInput(QString value)
{
  if(m_textInput != value)
  {
      m_textInput = value;
      emit textInputChanged();
    }
}

void CalculateForm::operations(QString contentButton)
{
    double result = 0;
    if(contentButton == "Del")
    {
         QString text = textInput();
         text.chop(1);
         setTextInput(text);
    }
    else if(contentButton == "1/x")
      setTextInput("1/" + textInput());
    else if(contentButton == "sqrt")
      setTextInput(textInput() + "sqrt(");
    else
    {
        setTextInput(textInput() + contentButton);
    }

    try {
       result = InterpreteExperssion(textInput().toStdWString());
       setTextOutput(QString::number(result));
    }
    catch (...)
    {
      setTextOutput("");
    }

    if(contentButton == "=")
    {    
        setTextInput(textOutput());
        setTextOutput("");
    }

    if(contentButton == "C")
    {
        setTextOutput("0");
        setTextInput("");
    }
}


