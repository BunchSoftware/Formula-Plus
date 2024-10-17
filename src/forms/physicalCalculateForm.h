#ifndef PHYSICALCALCULATEFORM_H
#define PHYSICALCALCULATEFORM_H

#include "plottingForm.h"
#include <QMainWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

class PhysicalCalculateForm : public QObject
{
    Q_OBJECT

public:
    explicit PhysicalCalculateForm(QObject *parent = nullptr);
signals:
    void PhysicalCalculateWindow();

private slots:

//    void on_pushButton_clicked();

//    void on_comboBox_activated(int index);

//    void Calclulate();
//    void UpdateLableAndLineInWindow(QJsonArray arrayData);
//    void UpdateDescription(QPixmap image, QString textLabel);
//    void Error();
//    QString FromFloatToString(float value);
//    void CheckLineEditIsEmpty(std::vector<double> result);
//    QJsonObject GetJsonObject(QString path);


private:
};

#endif // FISIC_H
