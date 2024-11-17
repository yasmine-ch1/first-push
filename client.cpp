#include "client.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>


client::client() {}
client::client(int Id_cl, int tel, QString nom, QString prenom, QDate date_n, QDate date_insc, QString sexe, QString fid, QString mail)
{
    this->Id_cl = Id_cl;
    this->tel = tel;
    this->date_n = date_n;
    this->date_insc = date_insc;
    this->nom = nom;
    this->prenom = prenom;
    this->sexe = sexe;
    this->fid = fid;
    this->mail = mail;
}

bool client::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (ID_CL, TEL, DATE_N, DATE_INSC, NOM, PRENOM, SEXE, FID, MAIL) "
                  "VALUES (:Id_cl, :tel, :date_n, :date_insc, :nom, :prenom, :sexe, :fid, :mail)");

    query.bindValue(":Id_cl", Id_cl);
    query.bindValue(":tel", tel);
    query.bindValue(":date_n", date_n);
    query.bindValue(":date_insc", date_insc);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":sexe", sexe);
    query.bindValue(":fid", fid);
    query.bindValue(":mail", mail);

    return query.exec(); // Retourne true si l'insertion réussit, false sinon
}

QSqlQueryModel *client::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("FID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_INC"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DATE_N"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SEX"));
    return model;
}

bool client::supprimer(int Id_cl)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE ID_CL = :Id_cl");
    query.bindValue(":Id_cl", Id_cl);

    return query.exec();
}

bool client::modifier(int Id_cl)
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET DATE_INSC = :date_insc, NOM = :nom, PRENOM = :prenom, SEXE = :sexe, "
                  "FID = :fid, DATE_N = :date_n, MAIL = :mail, TEL = :tel WHERE ID_CL = :Id_cl");

    query.bindValue(":Id_cl", Id_cl);
    query.bindValue(":date_insc", date_insc);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":sexe", sexe);
    query.bindValue(":fid", fid);
    query.bindValue(":date_n", date_n);
    query.bindValue(":mail", mail);
    query.bindValue(":tel", tel);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la modification :" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* client::rechercher(const QString& critere, const QString& valeur)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
   /* if (critere == "NOM") {
        query.prepare("SELECT * FROM CLIENT WHERE NOM LIKE :valeur");
        query.bindValue(":valeur", "%" + valeur + "%");
    } else*/
if (critere == "Prénom") {
        query.prepare("SELECT * FROM CLIENT WHERE PRENOM  LIKE :valeur");
        query.bindValue(":valeur", "%" + valeur + "%");
    } else if (critere == "ID") {
        query.prepare("SELECT * FROM CLIENT WHERE ID_CL = :valeur");
        query.bindValue(":valeur", valeur.toInt());
    }

    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche :" << query.lastError().text();
        delete model;  // Supprime le modèle en cas d'échec de la requête
        return nullptr;
    }
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("FID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_INC"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DATE_N"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SEX"));

    return model;
}


QSqlQueryModel* client::trierClients(const QString &critere)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    QString orderByColumn;
    if (critere == "date d'incri") {
        orderByColumn = "DATE_INSC";
    } else if (critere == "Nom") {
        orderByColumn = "Nom";
    } else {
        qDebug() << "Critère de tri non valide";
        delete model;
        return nullptr;
    }
    query.prepare("SELECT * FROM CLIENT ORDER BY " + orderByColumn + " ASC");

    if (!query.exec()) {
        qDebug() << "Erreur lors du tri :" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("FID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_INC"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DATE_N"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SEX"));

    return model;
}
QMap<QString, int> client::statistiquesParFid() {
    QMap<QString, int> stats;
    QSqlQuery query("SELECT FID, COUNT(*) FROM CLIENT GROUP BY FID");
    while (query.next()) {
        QString FID = query.value(0).toString();
        int count = query.value(1).toInt();
        stats[FID] = count;
    }
    return stats;
}
