#ifndef FORMATEURS_H
#define FORMATEURS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class FORMATEURS
{
public:
FORMATEURS();
        FORMATEURS(int,QString,QString,QString,QString,QString,QString);

        int getID_FORMATEUR();
        QString getNOMFORMATEUR();
        QString getPRENOMFORMATEUR();
        QString getSPECIALITE();

        QString getEXPERIENCE();
        QString getEMAILFORMATEUR();
        QString getTELEPHONEFORMATEUR();


        void setID_FORMATEUR(int);
        void setNOMFORMATEUR(QString);
        void setPRENOMFORMATEUR(QString );
        void setSPECIALITE(QString );
        void setEXPERIENCE(QString );
        void setEMAILFORMATEUR(QString);
        void setTELEPHONEFORMATEUR(QString);


        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(int);
        bool checkIfIdExists(int);


        QSqlQueryModel *rechercher(QString);
        QSqlQueryModel *trier(QString);

private:

       int ID_FORMATEUR;
       QString NOMFORMATEUR,PRENOMFORMATEUR,SPECIALITE,EXPERIENCE,EMAILFORMATEUR,TELEPHONEFORMATEUR;

};


#endif // FORMATEURS_H
