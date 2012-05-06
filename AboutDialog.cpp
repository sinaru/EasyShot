#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    //set the window size into a fixed size
    setFixedSize(250,120);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
