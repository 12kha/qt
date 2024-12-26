#include "formations.h"

#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QtDebug>
#include <QObject>
#include<QDate>
#include<QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

FORMATIONS::FORMATIONS()
{

}

FORMATIONS::FORMATIONS(int ID_FORMATION,QString TITREFORMATION,QString DESCRIPTIONFORMATION,int DUREEFORMATION,QDate DATEDEBUT,QDate DATEFIN,int ID_FORMATEUR)
{this->ID_FORMATION=ID_FORMATION;
    this->TITREFORMATION = TITREFORMATION;
    this->DESCRIPTIONFORMATION = DESCRIPTIONFORMATION;
    this->DUREEFORMATION=DUREEFORMATION;
    this->DATEDEBUT = DATEDEBUT;
    this->DATEFIN = DATEFIN;
    this->ID_FORMATEUR = ID_FORMATEUR;

}

  int FORMATIONS::getID_FORMATION(){return ID_FORMATION;}
  QString FORMATIONS::getTITREFORMATION(){return TITREFORMATION;}
  QString FORMATIONS::getDESCRIPTIONFORMATION(){return DESCRIPTIONFORMATION;}
  int FORMATIONS::getDUREEFORMATION(){return DUREEFORMATION;}
  QDate FORMATIONS::getDATEDEBUT(){return DATEDEBUT;}
  QDate FORMATIONS::getDATEFIN(){return DATEFIN;}
  int FORMATIONS::getID_FORMATEUR(){return ID_FORMATEUR;}

  void FORMATIONS::setID_FORMATION(int ID_FORMATION){this->ID_FORMATION=ID_FORMATION;}
  void FORMATIONS::setTITREFORMATION(QString TITREFORMATION){this->TITREFORMATION=TITREFORMATION;}
  void FORMATIONS::setDESCRIPTIONFORMATION(QString DESCRIPTIONFORMATION){this->DESCRIPTIONFORMATION=DESCRIPTIONFORMATION;}
  void FORMATIONS::setDATEDEBUT(QDate DATEDEBUT){this->DATEDEBUT=DATEDEBUT;}
  void FORMATIONS::setDATEFIN(QDate DATEFIN ){this->DATEFIN=DATEFIN;}
  void FORMATIONS::setID_FORMATEUR(int ID_FORMATEUR){this->ID_FORMATEUR=ID_FORMATEUR;}



bool FORMATIONS::ajouter()
{

    QSqlQuery query;

    query.prepare("INSERT INTO FORMATIONS (ID_FORMATION,TITREFORMATION,DESCRIPTIONFORMATION,DUREEFORMATION,DATEDEBUT,DATEFIN,ID_FORMATEUR)"
                  "values(:ID_FORMATION,:TITREFORMATION,:DESCRIPTIONFORMATION,:DUREEFORMATION,:DATEDEBUT,:DATEFIN,:ID_FORMATEUR)");
    query.bindValue(":ID_FORMATION",ID_FORMATION);
        query.bindValue(":TITREFORMATION",TITREFORMATION);
         query.bindValue(":DESCRIPTIONFORMATION",DESCRIPTIONFORMATION);
         query.bindValue(":DUREEFORMATION",DUREEFORMATION);
         query.bindValue(":DATEDEBUT",DATEDEBUT);
         query.bindValue(":DATEFIN",DATEFIN);
         query.bindValue(":ID_FORMATEUR",ID_FORMATEUR);


          return query.exec();

   };



QSqlQueryModel * FORMATIONS::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from FORMATIONS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_FORMATION"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TITREFORMATION"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTIONFORMATION"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DUREEFORMATION"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DATEDEBUT"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATEFIN"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID_FORMATEUR"));

    return model;
}
bool FORMATIONS::supprimer(int ID)
{
    QSqlQuery query;
         query.prepare("Delete from FORMATIONS where ID_FORMATION=:ID_FORMATION");
         query.bindValue(":ID_FORMATION",ID_FORMATION);
         return query.exec();
}

bool FORMATIONS::modifier(int ID)
{
QSqlQuery query;


        query.prepare("UPDATE FORMATIONS SET TITREFORMATION=:TITREFORMATION,DESCRIPTIONFORMATION=:DESCRIPTIONFORMATION,DUREEFORMATION=:DUREEFORMATION,DATEDEBUT=:DATEDEBUT,DATEFIN=:DATEFIN,ID_FORMATEUR=:ID_FORMATEUR where ID_FORMATION=:ID_FORMATION");
        query.bindValue(":ID_FORMATION", ID_FORMATION);
        query.bindValue(":TITREFORMATION",TITREFORMATION);
         query.bindValue(":DESCRIPTIONFORMATION",DESCRIPTIONFORMATION);
         query.bindValue(":DUREEFORMATION",DUREEFORMATION);
         query.bindValue(":DATEDEBUT",DATEDEBUT);
          query.bindValue(":DATEFIN",DATEFIN);
            query.bindValue(":ID_FORMATEUR",ID_FORMATEUR);

        return    query.exec();
}
bool FORMATIONS::checkIfIdExists(int id)
{
    QSqlQuery query;
    query.prepare("SELECT ID_FORMATION FROM FORMATIONS WHERE ID_FORMATION = :ID_FORMATION");
    query.bindValue(":ID_FORMATION", ID_FORMATION);

    if (query.exec() && query.next()) {
        // The ID exists in the database
        return true;
    } else {
        // The ID does not exist in the database
        return false;
    }
}

QSqlQueryModel* FORMATIONS::rechercher(QString a)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATIONS WHERE id LIKE '" + a + "%'");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUMTEL"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE INSC"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("CARTE CREDIT"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("SOLDE COMPTE"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("COMPTE ACTIF"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("REDUCTION"));
    return model;
}
QSqlQueryModel *FORMATIONS::trier(QString x)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    qDebug()<<x<<endl;

    if(x=="ID (DES)")
        model->setQuery("select*  from FORMATIONS order by id desc");
    else if(x=="Nom (A->Z)")
        model->setQuery("select*  from FORMATIONS order by nom");  //tri par defaut asc
    else if (x=="Solde (Asc)")
        model->setQuery("select*  from FORMATIONS order by soldecompte");
    else if (x=="Default")
            model->setQuery("select * from FORMATIONS");


    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUMTEL"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DATE INSC"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("CARTE CREDIT"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("SOLDE COMPTE"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("COMPTE ACTIF"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("REDUCTION"));
        return model;

}
