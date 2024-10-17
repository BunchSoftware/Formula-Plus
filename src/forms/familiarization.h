#ifndef FAMILIARIZATIONFORM_H
#define FAMILIARIZATIONFORM_H

#include <QWidget>

class FamiliarizationForm : public QObject
{
  Q_OBJECT

public:
  explicit FamiliarizationForm(QObject *parent = nullptr);
  ~FamiliarizationForm();

private:
};

#endif // FAMILIARIZATION_H
