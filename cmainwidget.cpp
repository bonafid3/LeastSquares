#include "cmainwidget.h"

#include <QPainter>

cMainWidget::cMainWidget(QWidget *parent) : QWidget(parent)
{

}

void cMainWidget::paint()
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignCenter, "Qt");
}

