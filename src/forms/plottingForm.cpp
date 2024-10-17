#include "plottingForm.h"
#include <math.h>
int indexChoosePlottingForm;

PlottingForm::PlottingForm(QObject *parent)
{

   // h=0.1;
   // xBegin = -3;
   // xEnd = 3+h;
   // ui->widget->xAxis->setRange(-6,6);
   // ui->widget->yAxis->setRange(0,12);
   // N=(xEnd-xBegin)/h+2;

   // ui->widget->setInteraction(QCP::iRangeDrag);
   // ui->widget->setInteraction(QCP::iRangeZoom);

   // for (int i = 0; i < ui->LineEditGroup->children().count() - 1; i++) {
   //     if(ui->LineEditGroup->children()[i]->metaObject()->className() == QString("QLineEdit")){
   //         QLineEdit *lineEdit = qobject_cast<QLineEdit*>(ui->LineEditGroup->children()[i]);
   //         Q_ASSERT( lineEdit != nullptr );
   //         lineEdit->setValidator(new QDoubleValidator(0, 100, 6, this) );
   //     }
   // }

   // on_comboBox_activated(0);
}
//void PlottingForm::on_pushButton_clicked()
//{
//    timer = new QTimer(this);
//    connect(timer,SIGNAL(timeout()),this,SLOT(TimerSlot()));
//    ui->widget->clearGraphs();
//    timer->start(20);
//    X = xBegin;
//    x.clear();
//    y.clear();
//}

//void PlottingForm::TimerSlot()
//{
//  if (indexChoosePlottingForm == 0){
//      float a = ui->lineEdit->text().toFloat();
//      float b = ui->lineEdit_2->text().toFloat();
//      float c = ui->lineEdit_3->text().toFloat();
//      if(time <= 20*N){
//          if (X<=xEnd)
//          {
//              x.push_back(X);
//              float c= (a*pow(X,2))+b*X+c;
//              y.push_back(c);
//              X+=h;

//           }
//          time+=20;
//      }
//      else{
//          time=0;
//          timer->stop();
//      }
//  }
//  else if (indexChoosePlottingForm == 1){
//      float a = ui->lineEdit->text().toFloat();
//      float b = ui->lineEdit_2->text().toFloat();
//      if(time <= 20*N){
//          if (X<=xEnd)
//          {
//              x.push_back(X);
//              float c= a*X+b;
//              y.push_back(c);
//              X+=h;

//           }
//          time+=20;
//      }
//      else{
//          time=0;
//          timer->stop();
//      }
//  }
//    ui->widget->addGraph();
//    ui->widget->graph(0)->addData(x,y);
//    ui->widget->replot();
//}

//void PlottingForm::on_comboBox_activated(int index)
//{
//    indexChoosePlottingForm = index;
//    if(indexChoosePlottingForm == 0)
//    {
//        UpdateLableAndLineInWindow("a", "b", "c");
//    }
//    else if(indexChoosePlottingForm == 1)
//    {
//        UpdateLableAndLineInWindow("a", "b", "");
//    }
//}
//void PlottingForm::UpdateLableAndLineInWindow(QString textLabel1, QString textLabel2, QString textLabel3){
//    if(textLabel1.isEmpty())
//    {
//      ui->lineEdit->hide();
//      ui->label->hide();
//    }
//    else
//    {
//      ui->label->show();
//      ui->label->setText(textLabel1);
//      ui->lineEdit->show();
//    }
//    if(textLabel2.isEmpty())
//    {
//      ui->lineEdit_2->hide();
//      ui->label_2->hide();
//    }
//    else
//    {
//      ui->label_2->show();
//      ui->label_2->setText(textLabel2);
//      ui->lineEdit_2->show();
//    }
//    if(textLabel3.isEmpty())
//    {
//      ui->lineEdit_3->hide();
//      ui->label_3->hide();
//    }
//    else
//    {
//      ui->label_3->show();
//      ui->label_3->setText(textLabel3);
//      ui->lineEdit_3->show();
//    }
//}
