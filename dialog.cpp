#include "dialog.h"
#include "ui_dialog.h"

#include <QPainter>

#include <QTime>

#include <QDebug>

#include <QString>

#define qd qDebug()
#define toStr(x) QString::number(x)

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    setMouseTracking(true);

    calculate();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    QPen b(QBrush(),1);
    QPen p(QBrush(Qt::blue),3);
    painter.setPen(p);
    painter.setFont(QFont("Arial", 30));
    painter.setBrush(QBrush(Qt::blue));

    sFloats f;
    f = calculate();
    float b0 = f.b0;
    float b1 = f.b1;

    float y = b1 * width();

    for(int x=0; x<width(); x+=50) {
        painter.drawLine(x,0,x,8);
    }
    for(int y=0; y<height(); y+=50) {
        painter.drawLine(0,y,8,y);
    }

    if(mData.size() >= 2) {
        painter.drawText(QRect(30,20, width(),height()),"f(x)="+ QString::number(b1,'g',2) +"x + " + QString::number(b0/50,'g',2));

        painter.drawLine(0, b0, width(), y+b0);
    }

    for(int i=0; i< mData.size(); i++) {

        painter.setPen(p);
        painter.drawEllipse(mData[i].height-3, mData[i].weight-3, 6, 6);

        if(ui->mShowSquaresCB->isChecked()) {
            y = b1 * mData[i].height;

            float diff = (y+b0) - mData[i].weight;

            painter.setPen(QPen(Qt::blue));
            painter.setBrush(QBrush());

            painter.drawRect(mData[i].height, mData[i].weight, diff, diff);
        }
    }

    QDialog::paintEvent(pe);
}

void Dialog::mouseMoveEvent(QMouseEvent *me)
{
    qd << me->pos();
}

void Dialog::mousePressEvent(QMouseEvent *me)
{
    mData.append(sData(me->pos().x(), me->pos().y()));
    update();
}

sFloats Dialog::calculate()
{
    sFloats result;
    int sum_x = 0, sum_y=0, sum_xy=0, sum_sq_x=0;
    const int n = mData.size();

    if(!n) return result;

    for(int i=0; i<n; i++) {
        sum_xy += mData[i].height * mData[i].weight;

        sum_sq_x += mData[i].height * mData[i].height;

        sum_x += mData[i].height;
        sum_y += mData[i].weight;
    }

    float numerator = sum_xy - sum_x * sum_y / n;
    float denominator = sum_sq_x - sum_x * sum_x / n;

    result.b1 = numerator / denominator;
    result.b0 = (sum_y - result.b1 * sum_x) / n;

    return result;
}

void Dialog::on_mClearButton_clicked()
{
    mData.clear();
    update();
}

void Dialog::on_mShowSquaresCB_toggled(bool checked)
{
    update();
}
