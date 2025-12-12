#include "widget.h"
#include "./ui_widget.h"
#include <QPainter>
#include <QStack>
#include <QAction>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("计算器");
}

Widget::~Widget()
{
    delete ui;
}

//按键绑定
void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_1:
            expression += "1";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_2:
            expression += "2";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_3:
            expression += "3";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_4:
            expression += "4";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_5:
            expression += "5";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_6:
            expression += "6";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_7:
            expression += "7";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_8:
            expression += "8";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_9:
            expression += "9";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_0:
            expression += "0";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_Undo:
        case Qt::Key_Backspace:
            expression.chop(1);
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_Return:
        case Qt::Key_Enter:
            Widget::on_equalButton_clicked();
            break;
        case Qt::Key_Plus:
            expression += "+";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_Minus:
            expression += "-";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_Asterisk:
            expression += "*";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_Slash:
            expression += "/";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_ParenLeft:
            expression += "(";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_ParenRight:
            expression += ")";
            ui->mainLineEdit->setText(expression);
            break;
        case Qt::Key_Period :
            expression += ".";
            ui->mainLineEdit->setText(expression);
        default:

            break;
    }
}


void Widget::on_onButton_clicked()
{
    expression += "1";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_twoButton_clicked()
{
    expression += "2";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_threButton_clicked()
{
    expression += "3";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_fourButton_clicked()
{
    expression += "4";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_fiveButton_clicked()
{
    expression += "5";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_sixButton_clicked()
{
    expression += "6";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_sevenButton_clicked()
{
    expression += "7";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_eightButton_clicked()
{
    expression += "8";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_nineButton_clicked()
{
    expression += "9";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_addButton_clicked()
{
    expression += "+";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_minusButton_clicked()
{
    expression += "-";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_multipleButton_clicked()
{
    expression += "*";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_divideButton_clicked()
{
    expression += "/";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_leftParenthesisButton_clicked()
{
    expression += "(";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_rightParenthesisButton_clicked()
{
    expression += ")";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_zeroButton_clicked()
{
    expression += "0";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_allclearButton_clicked()
{
    expression.clear();
    ui->mainLineEdit->clear();
}


void Widget::on_deleteButton_clicked()
{
    expression.chop(1);
    ui->mainLineEdit->setText(expression);
}

void Widget::on_threButton_2_clicked()
{
    expression += ".";
    ui->mainLineEdit->setText(expression);
}

void Widget::applyOperation(QStack<double>& s_num, char op)
{
    // 确保栈中有足够的操作数（至少需要2个）
    if (s_num.size() < 2) {
        //qDebug() << "Error: Not enough operands for operation" << op;
        return;
    }

    // 从栈中取出操作数
    double num2 = s_num.pop(); // 第二个操作数（后入栈）
    double num1 = s_num.pop(); // 第一个操作数（先入栈）
    double result = 0;

    // 根据运算符执行相应计算
    switch (op)
    {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            // 检查除零错误（使用Qt的浮点数零值检查）
            if (qFuzzyIsNull(num2)) {
                //qDebug() << "Error: Division by zero";

                // 恢复原始操作数到栈中
                s_num.push(num1);
                s_num.push(num2);

                // 在UI上显示错误信息
                ui->mainLineEdit->setText("Error: Division by zero");
                return;
            }
            result = num1 / num2;
            break;
        default:
            //qDebug() << "Error: Unknown operator" << op;

            // 恢复原始操作数到栈中
            s_num.push(num1);
            s_num.push(num2);
            return;
    }

    // 将计算结果压回栈中
    s_num.push(result);

    //qDebug() << "Applied operation:" << num1 << op << num2 << "=" << result;
}

void Widget::on_equalButton_clicked()
{
    // 检查空表达式
    if (expression.isEmpty()) {
        ui->mainLineEdit->setText("0");
        return;
    }

    QStack<double> s_num;  // 改为double类型
    QStack<char> s_opt;    // 改为char类型

    QByteArray ba = expression.toUtf8();
    const char* opt = ba.constData();

    int i = 0;
    double tmp = 0;
    bool readingNumber = false;
    bool hasDecimal = false;//处理小数
    double decimalFactor = 0.1;//处理小数

    while (i < ba.size() || !s_opt.empty())
    {
        if (i < ba.size() && opt[i] >= '0' && opt[i] <= '9')  // 包含数字0
        {
            readingNumber = true;
            if (hasDecimal) {
                tmp += (opt[i] - '0') * decimalFactor;
                decimalFactor *= 0.1;
            } else {
                tmp = tmp * 10 + (opt[i] - '0');
            }
            i++;
        }
        else if (i < ba.size() && opt[i] == '.')
        {
            hasDecimal = true;
            decimalFactor = 0.1;
            i++;
        }
        else
        {
            if (readingNumber) {
                s_num.push(tmp);
                tmp = 0;
                readingNumber = false;
                hasDecimal = false;
            }

            if (i >= ba.size()) {
                // 表达式结束，处理剩余运算符
                while (!s_opt.empty()) {
                    applyOperation(s_num, s_opt.pop());
                }
                break;
            }

            // 处理运算符
            if (opt[i] == '(') {
                s_opt.push(opt[i]);
                i++;
            } else if (opt[i] == ')') {
                // 处理括号内的运算
                while (!s_opt.empty() && s_opt.top() != '(') {
                    applyOperation(s_num, s_opt.pop());
                }
                if (!s_opt.empty() && s_opt.top() == '(') {
                    s_opt.pop(); // 弹出 '('
                }
                i++;
            } else if (opt[i] == '+' || opt[i] == '-' ||
                       opt[i] == '*' || opt[i] == '/') {
                // 处理运算符优先级
                while (!s_opt.empty() && Priority(s_opt.top()) >= Priority(opt[i])) {
                    applyOperation(s_num, s_opt.pop());
                }
                s_opt.push(opt[i]);
                i++;
            } else {
                // 跳过空格或其他无效字符
                i++;
            }
        }
    }

    // 处理最后一个数字
    if (readingNumber) {
        s_num.push(tmp);
    }

    // 处理剩余运算符
    while (!s_opt.empty()) {
        applyOperation(s_num, s_opt.pop());
    }

    // 检查最终结果
    if (s_num.size() == 1) {
        ui->mainLineEdit->setText(QString::number(s_num.top()));
    } else {
        ui->mainLineEdit->setText("Error: Invalid expression");
    }

    expression.clear();
}

// Priority函数
int Widget::Priority(char ch)
{
    switch (ch) {
    case '(': return 0; // 括号优先级最低
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    default: return -1;
    }
}

