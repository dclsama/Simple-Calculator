#ifndef WIDGET_H
#define WIDGET_H
#include<iostream>
#include <QPainter>
#include <QWidget>
#include <QStack>
#include <string.h>
#include <QAction>
#include <QKeyEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();



private slots:
    void on_onButton_clicked();

    void on_twoButton_clicked();

    void on_threButton_clicked();

    //void on_pushButton_2_clicked();

    void on_fiveButton_clicked();

    void on_sixButton_clicked();

    void on_sevenButton_clicked();

    void on_fourButton_clicked();

    void on_eightButton_clicked();

    void on_nineButton_clicked();

    void on_addButton_clicked();

    void on_minusButton_clicked();

    void on_multipleButton_clicked();

    void on_divideButton_clicked();

    void on_leftParenthesisButton_clicked();

    void on_rightParenthesisButton_clicked();

    void on_zeroButton_clicked();

    void on_allclearButton_clicked();

    void on_deleteButton_clicked();

    void on_equalButton_clicked();

    void on_threButton_2_clicked();

private:
    Ui::Widget *ui;
    QString expression;
    int Priority(char ch);
    void keyPressEvent(QKeyEvent *event);
    void applyOperation(QStack<double>& s_num, char op);
};
#endif // WIDGET_H
