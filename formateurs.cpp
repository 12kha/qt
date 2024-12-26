#include "formateurs.h"

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




FORMATEURS::FORMATEURS()
{

}

FORMATEURS::FORMATEURS(int ID_FORMATEUR,QString NOMFORMATEUR,QString PRENOMFORMATEUR,QString SPECIALITE,QString EXPERIENCE,QString EMAILFORMATEUR,QString TELEPHONEFORMATEUR)
{this->ID_FORMATEUR=ID_FORMATEUR;
    this->NOMFORMATEUR = NOMFORMATEUR;
    this->PRENOMFORMATEUR = PRENOMFORMATEUR;
    this->SPECIALITE=SPECIALITE;
    this->EXPERIENCE = EXPERIENCE;
    this->EMAILFORMATEUR = EMAILFORMATEUR;
    this->TELEPHONEFORMATEUR = TELEPHONEFORMATEUR;

}

  int FORMATEURS::getID_FORMATEUR(){return ID_FORMATEUR;}
  QString FORMATEURS::getNOMFORMATEUR(){return NOMFORMATEUR;}
  QString FORMATEURS::getPRENOMFORMATEUR(){return PRENOMFORMATEUR;}
  QString FORMATEURS::getSPECIALITE(){return SPECIALITE;}
  QString FORMATEURS::getEXPERIENCE(){return EXPERIENCE;}
  QString FORMATEURS::getEMAILFORMATEUR(){return EMAILFORMATEUR;}
  QString FORMATEURS::getTELEPHONEFORMATEUR(){return TELEPHONEFORMATEUR;}

  void FORMATEURS::setID_FORMATEUR(int ID_FORMATEUR){this->ID_FORMATEUR=ID_FORMATEUR;}
  void FORMATEURS::setNOMFORMATEUR(QString NOMFORMATEUR){this->NOMFORMATEUR=NOMFORMATEUR;}
  void FORMATEURS::setPRENOMFORMATEUR(QString PRENOMFORMATEUR){this->PRENOMFORMATEUR=PRENOMFORMATEUR;}
  void FORMATEURS::setSPECIALITE(QString SPECIALITE){this->SPECIALITE=SPECIALITE;}
  void FORMATEURS::setEXPERIENCE(QString EXPERIENCE ){this->EXPERIENCE=EXPERIENCE;}
  void FORMATEURS::setEMAILFORMATEUR(QString EMAILFORMATEUR){this->EMAILFORMATEUR=EMAILFORMATEUR;}
  void FORMATEURS::setTELEPHONEFORMATEUR(QString TELEPHONEFORMATEUR){this->TELEPHONEFORMATEUR=TELEPHONEFORMATEUR;}



bool FORMATEURS::ajouter()
{

    QSqlQuery query;

    query.prepare("INSERT INTO FORMATEURS (ID_FORMATEUR,NOMFORMATEUR,PRENOMFORMATEUR,SPECIALITE,EXPERIENCE,EMAILFORMATEUR,TELEPHONEFORMATEUR)"
                  "values(:ID_FORMATEUR,:NOMFORMATEUR,:PRENOMFORMATEUR,:SPECIALITE,:EXPERIENCE,:EMAILFORMATEUR,:TELEPHONEFORMATEUR)");
    query.bindValue(":ID_FORMATEUR",ID_FORMATEUR);
        query.bindValue(":NOMFORMATEUR",NOMFORMATEUR);
         query.bindValue(":PRENOMFORMATEUR",PRENOMFORMATEUR);
         query.bindValue(":SPECIALITE",SPECIALITE);
         query.bindValue(":EXPERIENCE",EXPERIENCE);
         query.bindValue(":EMAILFORMATEUR",EMAILFORMATEUR);
         query.bindValue(":TELEPHONEFORMATEUR",TELEPHONEFORMATEUR);


          return query.exec();

   };



QSqlQueryModel * FORMATEURS::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from FORMATEURS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_FORMATEUR"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMFORMATEUR"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOMFORMATEUR"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("SPECIALITE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("EXPERIENCE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("EMAILFORMATEUR"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("TELEPHONEFORMATEUR"));

    return model;
}
bool FORMATEURS::supprimer(int ID_FORMATEUR)
{
    QSqlQuery query;
         query.prepare("Delete from FORMATEURS where ID_FORMATEUR=:ID_FORMATEUR");
         query.bindValue(":ID_FORMATEUR",ID_FORMATEUR);
         return query.exec();
}

bool FORMATEURS::modifier(int ID_FORMATEUR)
{
QSqlQuery query;


        query.prepare("UPDATE FORMATEURS SET NOMFORMATEUR=:NOMFORMATEUR,PRENOMFORMATEUR=:PRENOMFORMATEUR,SPECIALITE=:SPECIALITE,EXPERIENCE=:EXPERIENCE,EMAILFORMATEUR=:EMAILFORMATEUR,TELEPHONEFORMATEUR=:TELEPHONEFORMATEUR where ID_FORMATEUR=:ID_FORMATEUR");
        query.bindValue(":ID_FORMATEUR",ID_FORMATEUR);
            query.bindValue(":NOMFORMATEUR",NOMFORMATEUR);
             query.bindValue(":PRENOMFORMATEUR",PRENOMFORMATEUR);
             query.bindValue(":SPECIALITE",SPECIALITE);
             query.bindValue(":EXPERIENCE",EXPERIENCE);
             query.bindValue(":EMAILFORMATEUR",EMAILFORMATEUR);
             query.bindValue(":TELEPHONEFORMATEUR",TELEPHONEFORMATEUR);


        return    query.exec();
}

bool FORMATEURS::checkIfIdExists(int ID_FORMATEUR)
{
    QSqlQuery query;
    query.prepare("SELECT ID_FORMATEUR FROM FORMATEURS WHERE ID_FORMATEUR = :ID_FORMATEUR");
    query.bindValue(":ID_FORMATEUR", ID_FORMATEUR);

    if (query.exec() && query.next()) {
        // The ID exists in the database
        return true;
    } else {
        // The ID does not exist in the database
        return false;
    }
}


QSqlQueryModel* FORMATEURS::rechercher(QString a)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM FORMATEURS WHERE ID_FORMATEUR LIKE '" + a + "%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_FORMATEUR"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMFORMATEUR"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOMFORMATEUR"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("SPECIALITE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("EXPERIENCE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("EMAILFORMATEUR"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("TELEPHONEFORMATEUR"));
    return model;
}
QSqlQueryModel *FORMATEURS::trier(QString x)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    qDebug()<<x<<endl;

    if(x=="ID (DES)")
        model->setQuery("select*  from FORMATEURS order by ID_FORMATEUR desc");
    else if(x=="Nom (A->Z)")
        model->setQuery("select*  from FORMATEURS order by NOMFORMATEUR");  //tri par defaut asc
    else if (x=="Solde (Asc)")
        model->setQuery("select*  from FORMATEURS order by EXPERIENCE");
    else if (x=="Default")
            model->setQuery("select * from FORMATEURS");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_FORMATEUR"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMFORMATEUR"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOMFORMATEUR"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("SPECIALITE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("EXPERIENCE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("EMAILFORMATEUR"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("TELEPHONEFORMATEUR"));

        return model;

}
