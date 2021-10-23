#ifndef IMGDISPLAY_H
#define IMGDISPLAY_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ImgDisplay; }
QT_END_NAMESPACE

class ImgDisplay : public QWidget
{
    Q_OBJECT

public:
    ImgDisplay(QWidget *parent = nullptr);
    ~ImgDisplay();

private:
    Ui::ImgDisplay *ui;
};
#endif // IMGDISPLAY_H
