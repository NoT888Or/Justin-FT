#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int choice1,choice2,type;
    double border;
    double tW;
    QVector<double>IV,TG,IVW;
    double a,b,C,v0;
    double e=2.71828;
    double result;

    double t=0.0;
    double temp;
    double temp1;
    int post=0;
    int posts=0;

    void plot(QCustomPlot *customPlot);
    void integralProcess();
    void derivativeProcess();
    void noChange();
    void input();
    void plotting();
    void capacitorCase();
    void inductorCase();
    void initializeTable();
    void saveData();
private slots:
    void on_current_clicked();

    void on_voltage_clicked();

    void on_current2_clicked();

    void on_voltage2_clicked();

    void on_pushButton_clicked();

    void on_capacitor_clicked();

    void on_inductor_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
