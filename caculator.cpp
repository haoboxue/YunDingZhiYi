#include "caculator.h"
#include "ui_caculator.h"
#include <QDebug>
#include <QString>
#include <QtMath>
#include <QQueue>
#include <QStack>

#define RATE 0.0174533
#define PI 3.1415926535898
#define E 2.718281828459045

QStack<QString> av;
bool mark=true;

caculator::caculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::caculator)
{
    ui->setupUi(this);

    connect(ui->label_11,&key::clicked,this,[=](){RecOpe('(');});
    connect(ui->label_12,&key::clicked,this,[=](){RecOpe(')');});
    connect(ui->label_13,&key::clicked,this,[=](){Recfunc("sin");});
    connect(ui->label_14,&key::clicked,this,[=](){Recfunc("cos");});
    connect(ui->label_15,&key::clicked,this,[=](){Recfunc("tan");});
    connect(ui->label_16,&key::clicked,this,[=](){RecNum(7);});
    connect(ui->label_17,&key::clicked,this,[=](){RecNum(8);});
    connect(ui->label_18,&key::clicked,this,[=](){RecNum(9);});
    connect(ui->label_19,&key::clicked,this,[=](){Recfunc("DEL");});
    connect(ui->label_20,&key::clicked,this,[=](){Recfunc("AC");});
    connect(ui->label_21,&key::clicked,this,[=](){RecNum(4);});
    connect(ui->label_22,&key::clicked,this,[=](){RecNum(5);});
    connect(ui->label_23,&key::clicked,this,[=](){RecNum(6);});
    connect(ui->label_24,&key::clicked,this,[=](){RecOpe('*');});
    connect(ui->label_25,&key::clicked,this,[=](){RecOpe('/');});
    connect(ui->label_26,&key::clicked,this,[=](){RecNum(1);});
    connect(ui->label_27,&key::clicked,this,[=](){RecNum(2);});
    connect(ui->label_28,&key::clicked,this,[=](){RecNum(3);});
    connect(ui->label_29,&key::clicked,this,[=](){RecOpe('+');});
    connect(ui->label_30,&key::clicked,this,[=](){RecOpe('-');});
    connect(ui->label_31,&key::clicked,this,[=](){RecNum(0);});
    connect(ui->label_32,&key::clicked,this,[=](){RecOpe('.');});
    connect(ui->label_33,&key::clicked,this,[=](){Recfunc("x10");});
    connect(ui->label_34,&key::clicked,this,[=](){Recfunc("Ans");});
    connect(ui->label_35,&key::clicked,this,&caculator::caculate);

}

caculator::~caculator()
{
    delete ui;
}

void caculator::caculate()
{
    qDebug()<<"计算";
    trans(ui->lineEdit->text());
    reverseAv();
    float a = compute();
    ui->lineEdit_2->setText(QString::number(a));

}

void caculator::RecNum(int num)
{
    QString input_num = ui->lineEdit->text();

//    if(input_num == "0")
//    {
//        ui->lineEdit->setText(QString::number(num));          //去掉前导0,并添加num
//    }
 //   else
 //  {
        if(ui->lineEdit_2->text() != ""&&ui->lineEdit->text() != "")
        {
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();


        }

        ui->lineEdit->insert(QString::number(num));          //在末尾插入数字num
//    }

    ui->lineEdit->setFocus ();      //继续追加光标
}


//接收输入运算符信号需要进行的操作
void caculator::RecOpe(QChar ch)
{

    ui->lineEdit->insert(ch);
    ui->lineEdit_2->clear();
}

int caculator::Recfunc(QString fun)
{

    if(ui->lineEdit_2->text() != ""&&ui->lineEdit->text() != "")
    {
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();

    }
    ui->lineEdit->insert(fun+"(");
    ui->lineEdit->setFocus ();      //继续追加光标
}

void caculator::reverseAv()
{//逆波兰式栈翻转函数
    QQueue<QString> temp;
    while(!av.empty()){
        temp.push_back(av.top());
        av.pop();
    }
    while(!temp.empty()){
        av.push(temp.front());
        temp.pop_front();
    }

}

float caculator::compute()//计算逆波兰式函数
{
    bool flag = true;
    QStack <float> calcv;  //存储中间值的栈
    while(!av.empty()){
        QString valueStr = av.top();
        av.pop();
        if(valueStr[0]=='~'){
            float tempF = calcv.top();
            calcv.pop();
            //float tempF = atof(str1.c_str());
            calcv.push((-1)*tempF);
        }

        if(valueStr[0]=='@');

        if(valueStr[0]=='!'){
            float tempF = calcv.top();
            calcv.pop();
            //float tempF = atof(str1);
            if((tempF<0)||(int(tempF)!=tempF)){
//                cout<<"负数或小数不能阶乘！！！"<<endl;
//                cout<<endl;
                flag=false;
                break;
            }
       /*    float fact = fac(tempF);
            calcv.push(fact)*/;
        }

        if(valueStr[0]=='%'){
            float tempF = calcv.top();
            calcv.pop();
            //float tempF = atof(str1);
            float fact = tempF*0.01;
            calcv.push(fact);
        }

        if((valueStr[0]=='+')||(valueStr[0]=='-')
           ||(valueStr[0]=='*')||(valueStr[0]=='/')||(valueStr[0]=='^')){
            float tempF1 = calcv.top();
            calcv.pop();
            float tempF2 = calcv.top();
            calcv.pop();
            //float tempF1 = atof(str1);
            //float tempF1 = atof(str2);
            float con = 0;
            if(valueStr[0]=='+'){
                con = tempF2 + tempF1;
            }
            if(valueStr[0]=='-'){
                con = tempF2 - tempF1;
            }
            if(valueStr[0]=='*'){
                con = tempF2 * tempF1;
            }
            if(valueStr[0]=='/'){
                if(tempF1==0){
//                    cout<<"除数不能为零！！！"<<endl;
//                    cout<<endl;
                    flag =false;
                    break;
                }
                con = tempF2/tempF1;
                //cout<<con<<endl;
            }
            if(valueStr[0]=='^'){
                con = pow(tempF2,tempF1);
            }
            //cout<<con<<endl;
            calcv.push(con);
        }

        if(((valueStr[0]>='0')&&(valueStr[0]<='9'))||(valueStr[0]=='.')){
            calcv.push(valueStr.toFloat());
        }

        if(((valueStr[0]>='a')&&(valueStr[0]<='z'))||
           ((valueStr[0]>='A')&&(valueStr[0]<='Z'))){
            float tempF = calcv.top();
            calcv.pop();
            //float tempF = atof(str1);
            bool  flage = false;
            float con = 0;
            if(valueStr=="sin"){
                if(mark==false){tempF = tempF*RATE;};
                con = sin(tempF);
                if(fabs(con)<0.00001)con=0;
                flage = true;
            }
            if(valueStr=="cos"){
                if(mark==false){tempF=tempF*RATE;};
                con = cos(tempF);
                if(fabs(con)<0.00001)con=0;
                flage = true;
                //cout<<con<<endl;
            }
            if(valueStr=="tan"){
                if(mark==false){tempF=tempF*RATE;};
                con =  tan(tempF);
                if(fabs(con)<0.00001)con=0;
                flage = true;
            }
            if(valueStr=="arctan"){
                con = atan(tempF);
                if(mark==false){con=con/RATE;}
                flage = true;
            }
            if(valueStr=="exp"){
                con = exp(tempF) ;
                flage = true;
            }
            if(valueStr=="fabs"){
                con = fabs(tempF);
                flage = true;
            }
            if(valueStr=="sqrt"){
                if(tempF<0){

                    flag = false;
                    break;
                }
                con = sqrt(tempF);
                flage = true;
            }
            if(valueStr=="arccos"){
                if((tempF<-1)||(tempF>1)){

                    flag = false;
                    break;
                }
                con = acos(tempF);
                if(mark==false){con=con/RATE;}
                flage = true;
            }
            if(valueStr=="arcsin"){
                if((tempF<-1)||(tempF>1)){

                    flag = false;
                    break;
                }
                con = asin(tempF);
                if(mark==false){con=con/RATE;}

                flage = true;
            }
            if(valueStr=="log2"){
                if(tempF<=0){

                    flag = false;
                    break;
                }
                con = log10(tempF)/log10(2);
                flage = true;
            }
            if(valueStr=="log10"){
                if(tempF<=0){

                    flag = false;
                    break;
                }
                con = log10(tempF);
                flage = true;
            }
            if(valueStr=="ln"){
                if(tempF<0){

                    flag = false;
                    break;
                }
                con = log(tempF);
                flage = true;
            }
            if(flage==false){

                flag = false;
                break;
            }
            calcv.push(con);
        }
        if(flag==false){
            break;
        }
    }
    if(flag==false){
        return 123456789;//错误标志
    }
    return calcv.top();
}


bool caculator::isCalFun(QString str){//检查当前字符串是否为数学函数
    if(str=="sin")return true;
    if(str=="cos")return true;
    if(str=="tan")return true;
    if(str=="arcsin")return true;
    if(str=="arccos")return true;
    if(str=="arctan")return true;
    if(str=="exp")return true;
    if(str=="fabs")return true;
    if(str=="log2")return true;
    if(str=="log10")return true;
    if(str=="ln")return true;
    if(str=="sqrt")return true;
    return false;
}

void caculator::trans(QString str)
{/*将算术表达式转化为后缀表达式*/
    QString valueString="";
    QString functionString="";

    QStack<QString> sy;/*存储符号栈*/
    QChar ch;
    int i=0;
    QString s="#";
    str=str+"#";//表达式后加入#
    //cout<<str<<endl;
    //检测表达式中的正负号
    if(str[0]=='+'){str.remove(0,1);}
    if(str[0]=='-'){str[0]='~';}
    for(i=str.length();i>=0;i--)
    {
       if((str[i]=='+'))
       {
               if((str[i-1]=='+')||(str[i-1]=='-')||(str[i-1]=='(')
                   ||(str[i-1]=='*')||(str[i-1]=='/')||(str[i-1]=='^'))
               {
                   str.remove(i,1);
               }
           }
       if(str[i]=='-')
       {
          if((str[i-1]=='+')||(str[i-1]=='-')||(str[i-1]=='(')
               ||(str[i-1]=='*')||(str[i-1]=='/')||(str[i-1]=='^'))
          {
                   str[i]='~';
          }
       }
    }

    sy.push(s);

    i=0;
    while(i<str.length()){
        ch=str[i];
        while((valueString!="")&&(ch<'0'||ch>'9')&&(ch!='.')){
            av.push(valueString);
            while(sy.top()=="@"||sy.top()=="~"){
                av.push(sy.top());
                sy.pop();
            }
            valueString="";
        }
        if((functionString!="")&&((ch<'a')||(ch>'z'))&&
           ((ch<'A'||ch>'Z'))&&((ch<'0'||ch>'9'))){
            sy.push(functionString);
            functionString="";
        }
        if(ch=='#'){
            while((sy.top()!="#")&&(sy.top()!="")){
                av.push(sy.top());
                sy.pop();
            }
        }
        if(ch=='~'||ch=='@'){
            QString temp="";
            temp=temp+ch;
            sy.push(temp);
        }
        if(ch=='!'||ch=='%'){
            QString temp="";
            temp=temp+ch;
            av.push(temp);
        }
        if(ch=='('){
           QString temp="";
           temp=temp+ch;
            sy.push(temp);
        }
        if(ch==')'){
            while((sy.top()!="#")&&(sy.top()!="(")&&(sy.top()!="")){
                av.push(sy.top());
                sy.pop();
            }
            while(sy.top()=="("){
                sy.pop();
            }
            QString strTop = sy.top();
            while((strTop=="~")||((strTop[0]>='a')&&(strTop[0]<='z'))
                  ||((strTop[0]>='A')&&(strTop[0]<='Z'))){
                av.push(strTop);
                sy.pop();
                strTop = sy.top();
            }
        }
        if((ch=='+')||(ch=='-')||(ch=='*')||(ch=='/')||(ch=='^')){
            QString strTop=sy.top();
            //cout<<sy.top()<<endl;
            while(getpriority(ch)<=getpriority(strTop[0])){
            av.push(strTop);
            sy.pop();
            strTop =sy.top();
            }
            QString temp ="";
            temp=temp+ch;
            //cout<<ch<<endl;
            //cout<<temp<<endl;
            sy.push(temp);
            //cout<<sy.top()<<endl;
        }
        if(ch=='.'){
            valueString=valueString+ch;
        }
        if(ch>='0'&&ch<='9'){
            if(functionString=="")
            {valueString=valueString+ch;}
            else{
                functionString = functionString+ch;
            }
        }
        if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){
            functionString=functionString+ch;
        }
        i++;
    }
}

int caculator::getpriority(QChar ch)
{

    if(ch == '#') return 0;
    if(ch == '(') return 1;
    if(ch == ',') return 2;
    if(ch == '+') return 3;
    if(ch == '-') return 3;
    if(ch == '*') return 5;
    if(ch == '/') return 5;
    if(ch == '~') return 7;
    if(ch == '@') return 7;
    if(ch == '!') return 9;
    if(ch == '%') return 9;
    if(ch == '^') return 9;
    if(ch == ')') return 10;
    return -1;

}

