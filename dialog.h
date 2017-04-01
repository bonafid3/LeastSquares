#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMouseEvent>
namespace Ui {
class Dialog;
}

#include <QVector>

struct sFloats {
    float b0, b1;
};

struct sData {
    sData(){throw"fuck";}
    sData(float h, float w) : height(h), weight(w){}
    float height;
    float weight;

};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void paintEvent(QPaintEvent *pe);

    void mouseMoveEvent(QMouseEvent *me);
    void mousePressEvent(QMouseEvent *me);

    sFloats calculate();
private slots:
    void on_mClearButton_clicked();

    void on_mShowSquaresCB_toggled(bool checked);

private:
    Ui::Dialog *ui;

    QVector<sData> mData;

};

#endif // DIALOG_H
