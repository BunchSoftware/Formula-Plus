#include "aboutprogramm.h"
#include "ui_aboutprogramm.h"

AboutProgramm::AboutProgramm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AboutProgramm)
{
  ui->setupUi(this);
}

AboutProgramm::~AboutProgramm()
{
  delete ui;
}
