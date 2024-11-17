#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include <QMainWindow>
#include "generateurqrcode.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:


    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    //void on_radioButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void exporterEnPDF();



    void on_pushButton_6_clicked();



    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_pushButton_3_clicked();
    void  onTableView1Clicked(const QModelIndex &index);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
     client cl;
     int columnwidth;
     int radio;
};
#endif // MAINWINDOW_H

