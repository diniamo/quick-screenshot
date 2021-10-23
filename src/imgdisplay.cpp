#include "./include/imgdisplay.h"
#include "./ui_imgdisplay.h"

ImgDisplay::ImgDisplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ImgDisplay)
{
    ui->setupUi(this);
}

ImgDisplay::~ImgDisplay()
{
    delete ui;
}

