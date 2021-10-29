#include "include/hotkeydialog.h"
#include "ui_hotkeydialog.h"

#include <QKeySequence>

HotkeyDialog::HotkeyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HotkeyDialog)
{
    ui->setupUi(this);
    ui->Layout->setAlignment(ui->ConfirmButton, Qt::AlignHCenter);  // idk how to do this in the form editor
}

HotkeyDialog::~HotkeyDialog()
{
    delete ui;
}

QKeySequence HotkeyDialog::newSequence()
{
    ui->SequenceEdit->clear();
    exec();
    return ui->SequenceEdit->keySequence();
}
