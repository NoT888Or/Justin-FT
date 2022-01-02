#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include "QMessageBox"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plot(QCustomPlot *customPlot)
{
  const char *demoName = "Simple Demo";

  // add two new graphs and set their look:
  customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
  customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
  customPlot->addGraph();
  customPlot->graph(2)->setPen(QPen(Qt::green));
  // generate some points of data (y0 for first, y1 for second graph):
//  QVector<double> x(251), y0(251), y1(251);
//  for (int i=0; i<251; ++i)
//  {
//    x[i] = i;
//    y0[i] = qCos(i/10.0); // exponentially decaying cosine
//    y1[i] = qExp(-i/150.0);              // exponential envelope
//  }
  // configure right and top axis to show ticks but no labels:
  // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
  customPlot->xAxis2->setVisible(true);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setVisible(true);
  customPlot->yAxis2->setTickLabels(false);
  // make left and bottom axes always transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
  // pass data points to graphs:
  customPlot->graph(0)->setData(TG,IV);
  customPlot->graph(1)->setData(TG,IV);
  customPlot->graph(2)->setData(TG,IVW);
  // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  customPlot->graph(0)->rescaleAxes();
  // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
  customPlot->graph(1)->rescaleAxes(true);
  customPlot->graph(2)->rescaleAxes(true);
  // Note: we could have also just called customPlot->rescaleAxes(); instead
  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
  customPlot->replot();
}


void MainWindow::on_capacitor_clicked()
{
    type=1;
}


void MainWindow::on_inductor_clicked()
{
    type=2;
}

void MainWindow::on_current_clicked()
{
    choice1=1;
}


void MainWindow::on_voltage_clicked()
{
    choice1=2;
}


void MainWindow::on_current2_clicked()
{
    choice2=1;
}


void MainWindow::on_voltage2_clicked()
{
    choice2=2;
}

void MainWindow::input()
{
    a=ui->doubleSpinBox->value();
    b=ui->doubleSpinBox_2->value();
    C=ui->doubleSpinBox_3->value();
    v0=ui->doubleSpinBox_4->value();
    tW=ui->doubleSpinBox_5->value();
}
void MainWindow::integralProcess()
{
// v(t)= 1/C * integgral(t,0) I(t) + v(0)
// the integral process:c ae^-bt ->integral -> a/-b * e^-bt
// integral (t,0) (a/-b * e^-bt)-(a/-b * e^-b*0) = a/-b * (e^-bt - 1)

    for(int i=0; i< border; i++)
    {
        TG.append(t);
        temp=-1*b*t;
        temp1=pow(e,temp);
        result= (a/(-1*b) * (temp1-1) / C)+v0;
        IV.append(result);
        if(t==0.00)
        {
            ui->lcdNumber->display(result);
        }
        else if (i==border-1)
        {
            ui->lcdNumber_2->display(result);
        }
        t=t+0.01;

    }
}

void MainWindow::derivativeProcess()
{
// i(t)= C * dv(t)/dt
// dv(t)/dt = d(ae^-bt)/dt -> derivative -> -b*ae^-bt

    for(int i=0; i< border; i++)
    {
        TG.append(t);
        temp=-1*b*t;
        temp1=pow(e,temp);
        result=C * (-1*b) * a * temp1;
        IV.append(result);
        if(t==0.00)
        {
            ui->lcdNumber->display(result);
        }
        else if (i==border-1)
        {
            ui->lcdNumber_2->display(result);
        }
        t=t+0.01;

    }
}


void MainWindow::noChange()
{
 //no need to conver, count as it is

    for(int i=0; i< border; i++)
    {
        TG.append(t);
        temp=-1*b*t;
        temp1=pow(e,temp);
        result=a*temp1;
        IV.append(result);
        if(t==0.00)
        {
            ui->lcdNumber->display(result);
        }
        else if (i==border-1)
        {
            ui->lcdNumber_2->display(result);
        }
        t=t+0.01;

    }
}

void MainWindow::capacitorCase()
{
    if((choice1==1)&&(choice2==1))
    {
        noChange();
        ui->textBrowser->append("This is a current graph.\n""The x axis is the time in s.\n""The y axis is the current in A.");
    }
    else if ((choice1==1)&&(choice2==2))
    {
        integralProcess();
        ui->textBrowser->append("This is a voltage graph.\n""The x axis is the time in s.\n""The y axis is the voltage in V.");
    }
    else if ((choice1==2)&&(choice2==2))
    {
        noChange();
        ui->textBrowser->append("This is a voltage graph.\n""The x axis is the time in s.\n""The y axis is the voltage in V.");
    }
    else if ((choice1==2)&&(choice2==1))
    {
        derivativeProcess();
        ui->textBrowser->append("This is a current graph.\n""The x axis is the time in s.\n""The y axis is the current in A.");
    }
}

void MainWindow::inductorCase()
{
    if((choice1==1)&&(choice2==1))
    {
        noChange();
        ui->textBrowser->append("This is a current graph.\n""The x axis is the time in s.\n""The y axis is the current in A.");
    }
    else if ((choice1==1)&&(choice2==2))
    {
        derivativeProcess();
        ui->textBrowser->append("This is a voltage graph.\n""The x axis is the time in s.\n""The y axis is the voltage in V.");
    }
    else if ((choice1==2)&&(choice2==2))
    {
        noChange();
        ui->textBrowser->append("This is a voltage graph.\n""The x axis is the time in s.\n""The y axis is the voltage in V.");
    }
    else if ((choice1==2)&&(choice2==1))
    {
        integralProcess();
        ui->textBrowser->append("This is a current graph.\n""The x axis is the time in s.\n""The y axis is the current in A.");
    }
}

void MainWindow::plotting()
{
    plot(ui->customPlot);
}

void MainWindow::on_pushButton_clicked()
{
    if(TG.size()>0)  TG.clear();
    if(IV.size()>0)  IV.clear();
    t=0;
    ui->lcdNumber_2->display(0);
    ui->lcdNumber->display(0);
    ui->textBrowser->clear();
    input();

    if (tW!=0.00)
    {
        border=tW*100+1;
    }
    else
    {
        border=301.00;
    }

    switch (type)
    {
    case 1:{
    ui->textBrowser->setText("Capactior");
    capacitorCase();
    break;
}

    case 2:{
     ui->textBrowser->setText("Inductor");
     inductorCase();
     break;
    }

    }
    plotting();
}


void MainWindow::initializeTable()
{
    for(int o=0; o < ui->data->rowCount();o++)
        {
            for(int h=0; h< ui->data->columnCount();h++)
            {
                ui->data->setItem(o,h, new QTableWidgetItem(" "));
            }
        }
}

void MainWindow::saveData()
{

    QString b = QString::number(t-0.01);
    ui->data->item(post,0)->setText(b);
    ui->data->item(post,1)->setText(QString::number(ui->lcdNumber_2->value()));
    post=post+1;
    posts=post-1;

}


void MainWindow::on_pushButton_2_clicked()
{
   saveData();
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->data->item(posts,0)->setText(QString::number(0));
    ui->data->item(posts,1)->setText(QString::number(0));
    posts=posts-1;
    post=posts+1;

}


void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox::about(this,"Algorithm","This is a storage element calculator, that are consist of capacitor and inductor.\n"
                       "This algorithm take the value from input in the spinbox, which is the function(the a,b component), the storage element, and initial V or I.\n"
                                        "Depending on the what storage element it is, what function it is, and what you want to convert it to,\n"
                                        "There are 3 possible out come, which is no change,integral conversion, and dervative conversion.\n"
                                        "In no change, the function is counted normaly.\n"
                                        "In a integral conversion, the function is change using a integral formula, with the storage element value, and initial V or I.\n"
                                        "For example, v(t)= 1/C * integral(t,0) I(t) + v(0), this is a integral conversion for capacitor, from current into voltage.\n"
                                        "The same conversion is also used for inductor, from voltage to current.\n"
                                        "In a derivative conversion, the function is change using a derivative formula, with the storage element value.\n"
                                        "For example, i(t)= C * dv(t)/dt, this is a derivaitve conversion for capacitor, from voltage to current.\n"
                                        "The same conversion is also used for inductor, from current to voltage.\n"
                                        "The function is then counted from 0->3 second, and  be put in a graph.\n"
                                        "When t=0, and t=final, is showed in the LCD.\n"
                                        "Noted that the time interval can be change, to find specific value, and the data also could be saved.\n");
}


void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox::about(this,"Program's description","This program is a storage element calculator, and it is inspired and made similarly to what Mr. Erikson’s material about storage elements in Electrical Engineering Class, which is about Capacitor and Inductor.\n"
                                                    "This program calculates the storage element function and then shows it in a graph from 0->3 second time intervals (3 second is the default time, and the time interval can be changed from the spin box) . \n"
                                                    "This program doesn’t just calculate the function, but can also convert the function, from a current function into a voltage function, or from a voltage function into a current function.\n"
                                                    "The initial result (time=0), and final result (time=final) is also shown in the form of an LCD numbers beside the graph, so this program could also be used to find specific value on a certain time, by changing the time interval, and seeing the result in the lcd numbers.\n"
                                                    "The description about the graph is above the graph in the text browser, which provides information about the graph such as what storage element, what graph it is, and the x,y axis.\n"
                                                    "The result can be saved in a table widget on the left of the graph. Up to 8 data can be saved, and the save data can be deleted without restarting the program.\n"
                       "The program uses a little bit of everything that has been taught in the first semester. This program used the qcustomplot class to make a graph.This program uses a lot of if-else statements, switch case, break, loop,a little bit of array for the graph, logical operators, and math formula.\n"
                                                    " Other than that, this program implements the use of QWidget, QWidgetTable, TextBrowser, and LCD display all together.");

}

