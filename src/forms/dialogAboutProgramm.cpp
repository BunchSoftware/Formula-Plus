#include "dialogaboutprogramm.h"
#include "ui_dialogaboutprogramm.h"

DialogAboutProgramm::DialogAboutProgramm(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogAboutProgramm)
{
  ui->setupUi(this);
}

DialogAboutProgramm::~DialogAboutProgramm()
{
  delete ui;
}
