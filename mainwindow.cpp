#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QSqlQuery>
#include"connection.h"
#include <QPdfWriter>
#include <QPainter>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QPageSize>
#include"generateurpdf.h"
#include <QtCharts>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   Connection c;
    if(c.createconnect())QMessageBox::information(this,"","connected");
    else QMessageBox::information(this,"","non connected");
    ui->statwidget->hide();

    ui->tableView1->setModel(cl.afficher());
    connect(ui->tableView1, &QTableView::clicked, this, &MainWindow::onTableView1Clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_clicked()
{
    radio=0;
}
void MainWindow::on_radioButton_2_clicked()
{
    radio=1;
}
void MainWindow::on_pushButton_clicked()
{

        int id_cl = ui->lineEdit_id_10->text().toInt();
        int tel = ui->lineEdit_6->text().toInt();
        QDate date_n = ui->dateEdit->date();  // Date de commande
        QDate date_insc = ui->dateEdit_2->date();  // Date de livraison
        QString nom = ui->lineEdit_2->text();
        QString prenom = ui->lineEdit_3->text();
         QString fid = ui->id_idcombox->currentText();// Mode de paiement
          QString mail = ui->lineEdit_4->text();

        client cl(id_cl,tel,nom,prenom,date_n,date_insc,"",fid,mail);
        // Appeler la méthode ajouter() pour insérer la commande dans la base de données
        bool test = cl.ajouter();
        if (test) {

            ui->tableView1->setModel(cl.afficher());

            QMessageBox::information(this, "","ajout succes");
        } else {
            QMessageBox::critical(this,"","ajout failed");

        }
}


void MainWindow::on_pushButton_4_clicked()
{
    int id_cl = ui->lineEdit_id_10->text().toInt();
    bool test = cl.supprimer(id_cl);
    if (test) {
        //Refresh (Actualiser)
        ui->tableView1->setModel(cl.afficher());

        QMessageBox::information(this,"","supppession succes" );

    } else {
        QMessageBox::critical(this,"","supp failed");

    }
}

void MainWindow::on_pushButton_5_clicked()
{
    int id_cl = ui->lineEdit_id_10->text().toInt();
    int tel = ui->lineEdit_6->text().toInt();
    QDate date_n = ui->dateEdit->date();
    QDate date_insc = ui->dateEdit_2->date();
    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_3->text();
     QString fid = ui->id_idcombox->currentText();
      QString mail = ui->lineEdit_4->text();

       QString sex;
      if(ui->radioButton->isChecked()){
            sex="homme";
      }
      else if(ui->radioButton_2->isChecked())
      {
          sex="femme";
      }

    client cl(id_cl,tel,nom,prenom,date_n,date_insc,"",fid,mail);
    if(cl.modifier(id_cl)){
        ui->tableView1->setModel(cl.afficher());

        QMessageBox::information(this,"","modification succes" );
    }
    else QMessageBox::critical(this,"","modif failed");
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString val=ui->lineEdit->text();
    if(val.isNull()){
        ui->tableView1->setModel(cl.afficher());
    }
    else{
                ui->tableView1->setModel(cl.rechercher(ui->comboBox->currentText(),val));
    }
}
void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
            ui->tableView1->setModel(cl.trierClients(ui->comboBox_2->currentText()));
}

void MainWindow::on_pushButton_3_clicked()
{
    QString nomFichierPDF = QFileDialog::getSaveFileName(this, "Enregistrer PDF", "", "Fichiers PDF (*.pdf)");
// annuler pas
            if (!nomFichierPDF.isEmpty()) {
                QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView1->model());
//verification
                if (model) {
                    GenerateurPDF::genererPDF(model, nomFichierPDF);
                } else {
                    QMessageBox::warning(this, "Erreur", "Le modèle n'est pas de type QSqlQueryModel.");
                }
            }
}

//QR
void MainWindow::onTableView1Clicked(const QModelIndex &index) {
    if (index.isValid()) {
        QSqlQueryModel *model = qobject_cast<QSqlQueryModel *>(ui->tableView1->model());
        if (model) {
            QStringList donneesLigne;
            QModelIndex cellIndex = model->index(index.row(), 5);
            donneesLigne << model->data(cellIndex).toString();
            QString donnees = "Email: "+donneesLigne.join(" ");
            //Génération du QR code
            GenerateurQRCode generateurQR;
            QImage qrCodeImage = generateurQR.genererCodeQR(donnees);
            //Affichage du QR code dans une QMessageBox
            QMessageBox msgBox;
                        msgBox.setIconPixmap(QPixmap::fromImage(qrCodeImage));
                        msgBox.exec();        }
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->statwidget->show();
         client cl;
         QMap<QString, int> stats = cl.statistiquesParFid();

        QPieSeries *series = new QPieSeries();
        for (auto it = stats.begin(); it != stats.end(); ++it) {
            series->append(it.key(), it.value());
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques des Client par F_ID");

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFixedSize(611, 401);

        QGraphicsScene *scene = new QGraphicsScene(this);
        scene->addWidget(chartView);
        ui->layoutGraph->setScene(scene);
}
void MainWindow::on_pushButton_8_clicked()
{
    ui->statwidget->hide();

}

