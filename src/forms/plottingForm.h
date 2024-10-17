#ifndef PLOTTINGFORM_H
#define PLOTTINGFORM_H

#include <QWidget>
#include <QTimer>
#include "library/qcustomplot.h"

class PlottingForm : public QObject
{
    Q_OBJECT

public:
    explicit PlottingForm(QObject *parent = nullptr);
signals:
    void PlottingFormWindow();

public slots:
//    void on_pushButton_clicked();
//    void TimerSlot();

//    void on_comboBox_activated(int index);
//    void UpdateLableAndLineInWindow(QString textLabel1, QString textLabel2, QString textLabel3);

private:
    double xBegin , xEnd,h,X;
    int N;
    QVector<double> x,y;
    QTimer *timer;
    int time;
};

#endif // GRAF_H
