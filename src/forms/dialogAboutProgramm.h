#ifndef DIALOGABOUTPROGRAMM_H
#define DIALOGABOUTPROGRAMM_H

#include <QDialog>

namespace Ui {
  class DialogAboutProgramm;
}

class DialogAboutProgramm : public QDialog
{
  Q_OBJECT

public:
  explicit DialogAboutProgramm(QWidget *parent = nullptr);
  ~DialogAboutProgramm();

private:
  Ui::DialogAboutProgramm *ui;
};

#endif // DIALOGABOUTPROGRAMM_H
