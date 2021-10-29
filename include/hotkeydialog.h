#ifndef HOTKEYDIALOG_H
#define HOTKEYDIALOG_H

#include <QDialog>

namespace Ui {
class HotkeyDialog;
}

class QKeySequence;

class HotkeyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HotkeyDialog(QWidget *parent = nullptr);
    ~HotkeyDialog();

    QKeySequence newSequence();

private:
    Ui::HotkeyDialog *ui;
};

#endif // HOTKEYDIALOG_H
