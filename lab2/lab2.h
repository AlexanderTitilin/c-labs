#pragma once
#include "qlabel.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QApplication>
#include <QGridLayout>
#include <QComboBox>

class Calc : public QWidget {
    Q_OBJECT
    public:
        Calc(QWidget *parent = 0);
    private slots:
        void countLab1();
        void countLab2();
        void countLab3();
        void genLab4();
        void eqLab4();
    private:
        QLabel *lab1Result;
        QLabel *lab2Result;
        QLabel *lab3Result;
        QLabel *lab4Exp;
        QLabel *lab4IsEq;
        QLineEdit *lab1Num1;
        QLineEdit *lab1Num2;
        QLineEdit *lab1Num3;
        QLineEdit *lab2Num1;
        QLineEdit *lab2Num2;
        QLineEdit *lab2Num3;
        QLineEdit *lab3Exp;
        QLineEdit *lab4Result;
        QComboBox *op1;
        QComboBox *op2;
};
