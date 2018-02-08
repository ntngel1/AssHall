#include "aboutprogramdialog.h"
#include "ui_aboutprogramdialog.h"

AboutProgramDialog::AboutProgramDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutProgramDialog)
{
    ui->setupUi(this);
}

AboutProgramDialog::~AboutProgramDialog()
{
    delete ui;
}
