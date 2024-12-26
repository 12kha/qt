#ifndef FORMATIONS_H
#define FORMATIONS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class FORMATIONS
{
public:
        FORMATIONS();
        FORMATIONS(int,QString,QString,int,QDate,QDate,int);

        int getID_FORMATION();
        QString getTITREFORMATION();
        QString getDESCRIPTIONFORMATION();
        int getDUREEFORMATION();

        QDate getDATEDEBUT();
        QDate getDATEFIN();
        int getID_FORMATEUR();


        void setID_FORMATION(int);
        void setTITREFORMATION(QString);
        void setDESCRIPTIONFORMATION(QString );
        void setDUREEFORMATION(int );
        void setDATEDEBUT(QDate );
        void setDATEFIN(QDate);
        void setID_FORMATEUR(int);


        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(int);
        bool checkIfIdExists(int);


        QSqlQueryModel *rechercher(QString);
        QSqlQueryModel *trier(QString);




private:

       int ID_FORMATION,ID_FORMATEUR,DUREEFORMATION;
       QString TITREFORMATION,DESCRIPTIONFORMATION;
       QDate DATEDEBUT,DATEFIN;

};

#endif // FORMATIONS_H
