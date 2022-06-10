#include <QGridLayout>
#include <QTabWidget>
#include <QCommandLinkButton>
#include <QWidget>
#include <QVector>
#include <QRegularExpression>
#include <QStack>
#include <QMap>
#include "lab2.h"
#include "qrandom.h"
#include "qvector.h"
#include <QRandomGenerator>
Calc::Calc(QWidget *parent)
    : QWidget(parent){
       QTabWidget *tabWidget = new QTabWidget(this);
       tabWidget->setGeometry(QRect(0,0,600,600));
       QWidget *tabLab1 = new QWidget();
       QWidget *tabLab2 = new QWidget();
       QWidget *tabLab3 = new QWidget();
       QWidget *tabLab4 = new QWidget();
       tabWidget->addTab(tabLab1,QString("LAB1"));
       tabWidget->addTab(tabLab2,QString("LAB2"));
       tabWidget->addTab(tabLab3,QString("LAB3"));
       tabWidget->addTab(tabLab4,QString("LAB4"));

       lab1Num1 = new QLineEdit(tabLab1);
       lab1Num2 = new QLineEdit(tabLab1);
       lab1Num3 = new QLineEdit(tabLab1);
       QLabel *lab1Label1 = new QLabel("+",tabLab1);
       QLabel *lab1Label2 = new QLabel("+",tabLab1);
       QLabel *lab1Label3 = new QLabel("=",tabLab1);
       lab1Result = new QLabel("",tabLab1);
       QPushButton *lab1CountButton = new QPushButton("Посчитать",tabLab1);
       QGridLayout *lab1Grid = new QGridLayout(tabLab1);
       lab1Grid->addWidget(lab1Num1,0,0);
       lab1Grid->addWidget(lab1Label1,0,1);
       lab1Grid->addWidget(lab1Num2,0,2);
       lab1Grid->addWidget(lab1Label2,0,3);
       lab1Grid->addWidget(lab1Num3,0,4);
       lab1Grid->addWidget(lab1Label3,0,5);
       lab1Grid->addWidget(lab1Result,0,6);
       lab1Grid->addWidget(lab1CountButton,1,0);
       connect(lab1CountButton,&QPushButton::clicked,this,&Calc::countLab1);
       

       lab2Num1 = new QLineEdit(tabLab2);
       lab2Num2 = new QLineEdit(tabLab2);
       lab2Num3 = new QLineEdit(tabLab2);
       op1 = new QComboBox(tabLab2);
       op1->addItem("+");
       op1->addItem("-");
       op1->addItem("*");
       op1->addItem("/");
       op2 = new QComboBox(tabLab2);
       op2->addItem("+");
       op2->addItem("-");
       op2->addItem("*");
       op2->addItem("/");
       QLabel *eqLab2 = new QLabel("=",tabLab2);
       lab2Result = new QLabel("",tabLab2);
       QPushButton *lab2CountButton = new QPushButton("Посчитать",tabLab1);
       QGridLayout *lab2Grid = new QGridLayout(tabLab2);
       lab2Grid->addWidget(lab2Num1,0,0);
       lab2Grid->addWidget(op1,0,1);
       lab2Grid->addWidget(lab2Num2,0,2);
       lab2Grid->addWidget(op2,0,3);
       lab2Grid->addWidget(lab2Num3,0,4);
       lab2Grid->addWidget(eqLab2,0,5);
       lab2Grid->addWidget(lab2Result,0,6);
       lab2Grid->addWidget(lab2CountButton,1,0);
       connect(lab2CountButton,&QPushButton::clicked,this,&Calc::countLab2);

       lab3Exp = new QLineEdit(tabLab3);
       lab3Result = new QLabel(tabLab3);
       QLabel *lab3Eq = new QLabel("=",tabLab3);
       QPushButton *lab3CountButton = new QPushButton("Посчитать",tabLab3);
       QGridLayout *lab3Grid = new QGridLayout(tabLab3);
       lab3Grid->addWidget(lab3Exp,0,0);
       lab3Grid->addWidget(lab3Eq,0,1);
       lab3Grid->addWidget(lab3Result,0,2);
       lab3Grid->addWidget(lab3CountButton,1,0);
       connect(lab3CountButton,&QPushButton::clicked,this,&Calc::countLab3);

       lab4Exp = new QLabel(tabLab4);
       QVector<QString> lab4ExpVec;
       lab4Result = new QLineEdit(tabLab4);
       lab4IsEq = new QLabel(tabLab4);
       QPushButton *lab4CountButton = new QPushButton("Посчитать",tabLab4);
       QPushButton *lab4GenButton = new QPushButton("Сгенерировать",tabLab4);
       QGridLayout *lab4Grid = new QGridLayout(tabLab4);
       lab4Grid->addWidget(lab4Exp,0,0);
       lab4Grid->addWidget(lab4Result,1,0);
       lab4Grid->addWidget(lab4IsEq,1,1);
       lab4Grid->addWidget(lab4CountButton,2,0);
       lab4Grid->addWidget(lab4GenButton,2,1);
       connect(lab4GenButton,&QPushButton::clicked,this,&Calc::genLab4);
       connect(lab4CountButton,&QPushButton::clicked,this,&Calc::eqLab4);
}

void Calc::countLab1(){
    float val = lab1Num1->text().toFloat() +
        lab1Num2->text().toFloat() +
        lab1Num3->text().toFloat();
    lab1Result->setText(QString::number(val));
}
float opCalc(float a, float b, QString op);
float makePolish(QString exp){
    QVector<QString> polish;
    QVector<QString> expVec;
    QRegularExpression isNum("\\d+\\.\\d+|\\d+");
    QRegularExpression re("\\d+\\.\\d+|\\d+|\\d+|\\+||\\*||\\-|\\/|\\(|\\)");
    QRegularExpressionMatchIterator i = re.globalMatch(exp);
    while (i.hasNext()){
        QRegularExpressionMatch m = i.next();
        if (m.captured() != " " && m.captured() != ""){
            expVec.push_back(m.captured());
        }
    };
    QMap<QString,int> ops;
    ops["*"] = 0;
    ops["/"] = 0;
    ops["+"] = 1;
    ops["-"] = 1;
    QStack<QString> stack;
    QString x;
    for (auto s : expVec){
        if (isNum.match(s).hasMatch()){
            polish.push_back(s);
        }
        else if (s == "("){
            stack.push_back("(");
        }
        else if (s == ")"){
            while ((x=stack.pop()) != "("){
                polish.push_back(x);
            }
        }
        else{
            while (!stack.empty() && 
                    ops.keys().indexOf(stack.top()) != -1 &&
                    ops[stack.top()] <= ops[s]){
                polish.push_back(stack.pop());
            }
            stack.push(s);
        }
            
    }
    while (!stack.isEmpty()){
        polish.push_back(stack.pop());
    }
    for (auto s : polish){
        if (isNum.match(s).hasMatch()){
            stack.push(s);
        }
        else{
            stack.push(QString::number(
                        opCalc(stack.pop().toFloat(),
                            stack.pop().toFloat(),
                            s
                        )));
        }
    }
    return stack.pop().toFloat();
}
float opCalc(float a, float b, QString op){
   if (op == "+") {
       return a + b;
   }
   else if (op == "-"){
       return a - b;
   }
   else if (op == "*"){
       return a * b;
   }
   else {
       return a / b;
   }
}

void Calc::countLab2(){
    QVector<QString> ordOp;
    ordOp.push_back("*");
    ordOp.push_back("/");
    ordOp.push_back("+");
    ordOp.push_back("-");
    float res;
    if (ordOp.indexOf(op1->currentText()) <=
            ordOp.indexOf(op2->currentText())){
       res = opCalc(lab2Num1->text().toFloat(),
               lab2Num2->text().toFloat(),op1->currentText());
       res = opCalc(res,lab2Num3->text().toFloat(),
               op2->currentText());
    }
    else{
        res = opCalc(lab2Num2->text().toFloat(),
                lab2Num3->text().toFloat(),
                op2->currentText());
       res = opCalc(lab2Num1->text().toFloat(),res,
                op1->currentText());
    }
    lab2Result->setNum(res);

}
void Calc::countLab3(){
    QRegularExpression re("\\d+\\.\\d+|\\d+|\\+||\\*||\\-|\\/|\\(|\\)");
    QMap<QString,int> ops;
    ops["*"] = 0;
    ops["/"] = 0;
    ops["+"] = 1;
    ops["-"] = 1;
    QRegularExpressionMatchIterator i = re.globalMatch(lab3Exp->text());
    QVector<QString> exp;
    while (i.hasNext()){
        QRegularExpressionMatch m = i.next();
        if (m.captured() != " " && m.captured() != ""){
            exp.push_back(m.captured());
        }
    };
    QString foo;
    for (auto s : exp){
        foo.push_back(s);
    }
    lab3Result->setNum(makePolish(foo));
    
}

void Calc::genLab4(){
    lab4IsEq->clear();
    QVector<QString> ops = {"+","-","/","*"};
    QVector<QString> exp;
    QString res;
    lab4Exp->setText(ops[QRandomGenerator::global()->bounded(0,4)]);
    int n = QRandomGenerator::global()->bounded(5,12);
    if (n % 2 == 0){
        n++;
    }
    int brs = 0;
    for (int i = 0; i < n; ++i){
        if (i % 2 == 0){
            if (QRandomGenerator :: global()->bounded(0,3) == 2){
                exp.push_back("(");
                brs++;
            }
            exp.push_back(QString::number(
                        QRandomGenerator::global()->bounded(1,11) +
                        1.0/QRandomGenerator::global()->bounded(1,5)));
        }
        else {
            exp.push_back(ops[
            QRandomGenerator::global()->bounded(0,4)]);
        }
    }
    for (;brs != 0; brs--){
        exp.push_back(")");
    }
    for (auto s : exp){
        res.push_back(s);
        res.push_back(" ");
    }
    lab4Exp->setText(res);
}

void Calc :: eqLab4(){
    lab4IsEq->clear();
    if (lab4Result->text().toFloat() == makePolish(lab4Exp->text())){
        lab4IsEq->setText("КРУТО");
    }
    else{
        lab4IsEq->setText("Пересчитай");
    }
}
            
int main(int argc, char *argv[]){
    QApplication app(argc,argv);
    Calc w;
    w.resize(600,600);
    w.show();
    return app.exec();
}
