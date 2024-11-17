#ifndef CLIENT_H
#define CLIENT_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>
class client
{
    int Id_cl,tel;
    QString nom,prenom,sexe,fid,mail;
    QDate date_n,date_insc;
public:
    //constructeur
    client();
    client(int,int,QString,QString,QDate,QDate,QString,QString,QString);

    //Getteurs

    int getId_cl(){return Id_cl;}
    int gettel(){return tel;}
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    QDate getdate_n(){return date_n;}
    QDate getdate_insc(){return date_insc;}
    QString getsexe(){return sexe;}
    QString getfid(){return fid;}
    QString getmail(){return mail;}


    //Setteurs
    void setId_cl(int id){Id_cl=id;}
    void settel(int tell){tel=tell;}
    void setnom(QString nomm){nom=nomm;}
    void setprenom(QString prenomm){prenom=prenomm;}
    void setdate_n(  QDate naiss){date_n=naiss;}
    void setdate_insc(  QDate insc){date_insc=insc;}
    void setsexe(QString  sexee){sexe=sexee;}
    void setfid(QString  fidd){fid=fidd;}
    void setmail(QString  maill){mail=maill;}

    //fonction
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int );
    QSqlQueryModel* rechercher(const QString& critere, const QString& valeur);
    QSqlQueryModel* trierClients(const QString &critere);
    void exporterEnPDF();
    QMap<QString, int> statistiquesParFid();

};

#endif // CLIENT_H
