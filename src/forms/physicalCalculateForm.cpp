#include "physicalCalculateForm.h"
#include <cstdio>
#include <math.h>
#include <QPixmap>
#include "errorForm.h"
#include "calculateForm.h"
#include <QLineEdit>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <vector>
#include "library/interpreter.h"

using namespace Interpreter;
int indexChoose;

PhysicalCalculateForm::PhysicalCalculateForm(QObject *parent) : QObject(parent)
{
   // ui->setupUi(this);
   // ui->pushButton->show();


   // for (int i = 0; i < ui->EditGroup->children().count() - 1; i++) {
   //     if(ui->EditGroup->children()[i]->metaObject()->className() == QString("QLineEdit")){
   //         QLineEdit *lineEdit = qobject_cast<QLineEdit*>(ui->EditGroup->children()[i]);
   //         Q_ASSERT( lineEdit != nullptr );
   //         QDoubleValidator *qDoubleValidator = new QDoubleValidator(lineEdit);
   //         qDoubleValidator->setNotation(QDoubleValidator::StandardNotation);
   //         lineEdit->setValidator(qDoubleValidator);
   //     }
   // }

   // QJsonArray jsonArray = GetJsonObject(":/source.json")["arrayData"].toArray();
   // for (int i = 0; i < jsonArray.count(); i++) {
   //     QJsonObject object = jsonArray[i].toObject();
   //     ui->comboBox->addItem(object["header"].toString());
   // }

   // on_comboBox_activated(0);

}
//double logbase(double a, double base)
//{
//   return log(a) / log(base);
//}

//PhysicalCalculateForm::~PhysicalCalculateForm()
//{
//    delete ui;
//}

//void PhysicalCalculateForm::on_pushButton_clicked()
//{
//    for (int i = 0; i < ui->EditGroup->children().count() - 1; i++) {
//        if(ui->EditGroup->children()[i]->metaObject()->className() == QString("QLineEdit") && ui->EditGroup->children()[i+1]->metaObject()->className() == QString("QLineEdit")){
//            QLineEdit *lineEdit = qobject_cast<QLineEdit*>(ui->EditGroup->children()[i]);
//            QLineEdit *lineEdit2 = qobject_cast<QLineEdit*>(ui->EditGroup->children()[i+1]);
//            Q_ASSERT( lineEdit != nullptr );
//            Q_ASSERT( lineEdit2 != nullptr );
//            if(lineEdit->isVisible() && lineEdit2->isVisible())
//            {
//                if(lineEdit->text().isEmpty() && lineEdit2->text().isEmpty()){
//                    Error();
//                    return;
//                }
//            }
//        }
//    }
//      Calclulate();
//}

//void PhysicalCalculateForm::Error(){
//    ErrorForm errorForm;
//    errorForm.setModal(true);
//    errorForm.exec();
//}


//void PhysicalCalculateForm::on_comboBox_activated(int index)
//{
//    indexChoose = index;
//    QJsonArray jsonArray = GetJsonObject(":/source.json")["arrayData"].toArray();

//    if(index <= jsonArray.count())
//    {
//        QJsonObject object = jsonArray[index].toObject();
//        ui->radioButton->setHidden(!object["radioButton"].toBool());
//        ui->radioButton_2->setHidden(!object["radioButton2"].toBool());
//        UpdateDescription(QPixmap(object["path"].toString()), object["description"].toString());
//        UpdateLableAndLineInWindow(object["symbolFormul"].toArray());
//        QJsonArray jsonArray1 = object["symbolFormul"].toArray();
//    }
//}

//void PhysicalCalculateForm::Calclulate()
//{
//  std::vector<double> value;
//  std::vector<double> result;
//  // Получаем массив данных
//  QJsonArray jsonArray = GetJsonObject(":/source.json")["arrayData"].toArray();
//  if(indexChoose <= jsonArray.count())
//  {
//      // Берем обьект по индексу
//      QJsonObject object = jsonArray[indexChoose].toObject();
//      // Берем массив значений переменных
//      QJsonArray mathValueSymbolFormul = object["mathValueSymbolFormul"].toArray();
//      // Берем массив формул
//      QJsonArray formulExpression = object["formulExpression"].toArray();
//      // Берем массив символов формул
//      QJsonArray symbolFormul = object["symbolFormul"].toArray();

//      for (int i = 0; i < ui->EditGroup->children().count() - 1; i++)
//      {
//          // Проверяем, если переменная равна нулю, то записываем значение из строки, иначе берем переменную из файла
//          if(mathValueSymbolFormul[i].toDouble() == 0)
//          {
//            if(ui->EditGroup->children()[i+1]->metaObject()->className() == QString("QLineEdit")){
//                QLineEdit *lineEdit = qobject_cast<QLineEdit*>(ui->EditGroup->children()[i+1]);
//                Q_ASSERT(lineEdit != nullptr );
//                value.push_back(lineEdit->text().toDouble());
//            }
//          }
//          else
//          {
//             value.push_back(mathValueSymbolFormul[i].toDouble());
//          }
//      }
//      if(formulExpression.count() == symbolFormul.count())
//      {
//          for (int i = 0; i < formulExpression.count(); i++)
//          {
//                 QString expression = formulExpression[i].toString();
//                 for (int j = 0; j < value.size(); j++)
//                 {
//                     if(symbolFormul[j].toString().isEmpty())
//                       continue;
//                     else
//                       expression.replace(symbolFormul[j].toString(), QString::number(value[j]));
//                 }
//                 try {
//                    result.push_back(InterpreteExperssion(expression.toStdWString()));
//                 } catch (...) {

//                 }
//          }
//      }
//      else
//      {
//          throw std::logic_error("Количество переменных не равно количесту значений переменных. Исправьте JSON файл");
//      }
//  }
//  else
//    {
//      throw std::logic_error("Индекс формулы больше, чем иммееться формул");
//    }
//  CheckLineEditIsEmpty(result);
//}
//void PhysicalCalculateForm::UpdateLableAndLineInWindow(QJsonArray arrayData){
//  for (int i = 0; i < arrayData.count(); i++) {
//      if(arrayData[i].toString() == ""){
//          if(ui->LabelEditGroup->children()[i+1]->metaObject()->className() == QString("QLabel")){
//              QLabel *label = qobject_cast<QLabel*>(ui->LabelEditGroup->children()[i+1]);
//              Q_ASSERT( label != nullptr );
//              label->setText("");
//              label->hide();

//              if(ui->EditGroup->children()[i+1]->metaObject()->className() == QString("QLineEdit")){
//                  QLineEdit *lineEdit = qobject_cast<QLineEdit*>(ui->EditGroup->children()[i+1]);
//                  Q_ASSERT(lineEdit != nullptr );
//                  lineEdit->hide();
//              }
//          }
//        }
//      else
//        {
//          if(ui->LabelEditGroup->children()[i+1]->metaObject()->className() == QString("QLabel")){
//              QLabel *label = qobject_cast<QLabel*>(ui->LabelEditGroup->children()[i+1]);
//              Q_ASSERT( label != nullptr );

//              label->setText(arrayData[i].toString());
//              label->show();

//              if(ui->EditGroup->children()[i+1]->metaObject()->className() == QString("QLineEdit")){
//                  QLineEdit *lineEdit = qobject_cast<QLineEdit*>(ui->EditGroup->children()[i+1]);
//                  Q_ASSERT(lineEdit != nullptr );
//                  lineEdit->show();
//              }
//          }
//        }
//    }
//  }
//  void PhysicalCalculateForm::UpdateDescription(QPixmap image, QString textLabel){
//      if(image.isNull()){
//        ui->DescriptionImage->hide();
//      }
//      else{
//        ui->DescriptionImage->show();
//        ui->DescriptionImage->setPixmap(image);
//      }
//      if(textLabel.isEmpty()){
//          ui->Description->hide();
//      }
//      else{
//        ui->Description->setText(textLabel);
//        ui->Description->show();
//      }
//    }
//QString PhysicalCalculateForm::FromFloatToString(float value){
//    return QString::number(value);
//}
//void PhysicalCalculateForm::CheckLineEditIsEmpty(std::vector<double> result)
//{
//  for (int i = 0; i < ui->EditGroup->children().count() - 1; i++)
//     {
//          if(ui->EditGroup->children()[i+1]->metaObject()->className() == QString("QLineEdit")){
//              QLineEdit *lineEdit = qobject_cast<QLineEdit*>(ui->EditGroup->children()[i+1]);
//              Q_ASSERT(lineEdit != nullptr );
//              if(lineEdit->text().isEmpty())
//              {
//                lineEdit->setText(QString::number(result[i]));
//                return;
//              }
//          }
//      }
//}
//QJsonObject PhysicalCalculateForm::GetJsonObject(QString path){
//  QFile file(path);
//  file.open(QIODevice::ReadOnly | QIODevice::Text);
//  QString jsonValue = file.readAll();
//  QJsonDocument doc = QJsonDocument::fromJson(jsonValue.toUtf8());
//  return doc.object();
//}
