#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include <QDebug>
#include <QSqlError>
#include <QDebug>

#include "QrCode.hpp"

using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouterFormation_clicked()
{


        // Réinitialisez les étiquettes d'erreur à vide
        ui->lblErreurle_ID_FORMATION->setText("");
        ui->lblErreurle_TITREFORMATION->setText("");

        ui->lblErreurDescription->setText("");
        ui->lblErreurle_DUREE->setText("");

        ui->lblErreurdateEditDATEDEBUT->setText("");
        ui->lblErreurdateEditDATEFIN->setText("");
        ui->lblErreurle_ID_FORMATEURFK->setText("");

        // Récupérez les valeurs d'entrée

        QString str_id = ui->le_ID_FORMATION->text();
        int ID_FORMATION=str_id.toInt();
        QString TITREFORMATION = ui->le_TITREFORMATION->text();
        QString DESCRIPTION = ui->le_DESCRIPTION->text();
        QString DUREEFORMATION_str = ui->le_DUREE->text();
        int DUREEFORMATION =DUREEFORMATION_str.toInt();
        QString DATEDEBUT_str = ui->dateEditDATEDEBUT->text();
        QString DATEFIN_str = ui->dateEditDATEFIN->text();

        QDate DATEDEBUT = QDate::fromString(DATEDEBUT_str, "yyyy-MM-dd");
        QDate DATEFIN = QDate::fromString(DATEFIN_str, "yyyy-MM-dd");

        QString ID_FORMATEURFK_str = ui->le_ID_FORMATEURFK->text();
        int ID_FORMATEURFK=ID_FORMATEURFK_str.toInt();

        // Validez les champs d'entrée
        bool isValid = true;

        if (str_id.isEmpty()) {
            ui->lblErreurle_ID_FORMATION->setText("<font color='red'>ID_FORMATION ne peut pas être vide!!!!</font>");
            isValid = false;
        }

        // Validation pour le titre (exemplaire, assurez-vous qu'il n'est pas vide)
        if (TITREFORMATION.isEmpty()) {
            ui->lblErreurle_TITREFORMATION->setText("<font color='red'>TITREFORMATION ne peut pas être vide!!!</font>");
            isValid = false;
        }

        if (DESCRIPTION.isEmpty()) {
            ui->lblErreurDescription->setText("<font color='red'>DESCRIPTION ne peut pas être vide!!!</font>");
            isValid = false;
        }
        if (DUREEFORMATION_str.isEmpty()) {
            ui->lblErreurle_DUREE->setText("<font color='red'>DUREEFORMATION ne peut pas être vide!!!</font>");
            isValid = false;
        }
        if (DATEDEBUT_str.isEmpty()) {
            ui->lblErreurdateEditDATEDEBUT->setText("<font color='red'>DATEDEBUT ne peut pas être vide!!!</font>");
            isValid = false;
        }
        if (DATEFIN_str.isEmpty()) {
            ui->lblErreurdateEditDATEFIN->setText("<font color='red'>DATEFIN ne peut pas être vide!!!</font>");
            isValid = false;
        }
        if (ID_FORMATEURFK_str.isEmpty()) {
            ui->lblErreurle_ID_FORMATEURFK->setText("<font color='red'>ID_FORMATEURFK ne peut pas être vide!!!</font>");
            isValid = false;
        }


        // Ajouter une vérification de l'existence de l'ID dans la base de données
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT ID_FORMATION FROM FORMATIONS WHERE ID_FORMATION = :ID_FORMATION");
        checkQuery.bindValue(":ID_FORMATION", ID_FORMATION);
        if (checkQuery.exec() && checkQuery.next()) {
            ui->lblErreurle_ID_FORMATION->setText("<font color='red'>ID_FORMATION existe déjà!!!!</font>");
            isValid = false;
        }

        // Continuez avec les autres validations d'entrée...

        if (isValid) {
            // Si l'entrée est valide et que l'ID n'existe pas, procédez à l'ajout de l'activité
            FORMATIONS F(ID_FORMATION,TITREFORMATION,DESCRIPTION,DUREEFORMATION,DATEDEBUT,DATEFIN,ID_FORMATEURFK);

            QSqlQuery query;
            bool test = F.ajouter();
            if (test) {
                ui->tab_Formation->setModel(F.afficher()); // Rafraîchir la vue

                QMessageBox::information(nullptr, QObject::tr("Ajout Formation"),
                    QObject::tr("Client ajoutée avec succès.\n"
                                "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);


            } else {
                QMessageBox::critical(nullptr, QObject::tr("Ajout Formation"),
                    QObject::tr("Erreur lors de l'ajout de Client.\n"
                                "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            }
        } else {
            // Gérez l'erreur d'entrée invalide ou d'ID existant
        }
    }



void MainWindow::on_pb_modifierFormation_clicked()
    {



    // Récupérez les valeurs d'entrée
    QString str_id = ui->le_ID_FORMATION->text();
    int ID_FORMATION=str_id.toInt();
    QString TITREFORMATION = ui->le_TITREFORMATION->text();
    QString DESCRIPTION = ui->le_DESCRIPTION->text();
    QString DUREEFORMATION_str = ui->le_DUREE->text();
    int DUREEFORMATION =DUREEFORMATION_str.toInt();
    QString DATEDEBUT_str = ui->dateEditDATEDEBUT->text();
    QString DATEFIN_str = ui->dateEditDATEFIN->text();

    QDate DATEDEBUT = QDate::fromString(DATEDEBUT_str, "yyyy-MM-dd");
    QDate DATEFIN = QDate::fromString(DATEFIN_str, "yyyy-MM-dd");

    QString ID_FORMATEURFK_str = ui->le_ID_FORMATEURFK->text();
    int ID_FORMATEURFK=ID_FORMATEURFK_str.toInt();


      // Vérification si l'ID existe
      QSqlQuery checkQuery;
      checkQuery.prepare("SELECT * FROM FORMATIONS WHERE ID_FORMATION = :ID_FORMATION");
      checkQuery.bindValue(":ID_FORMATION", ID_FORMATION);

      if (!checkQuery.exec())
      {
          // Erreur lors de l'exécution de la requête
          qDebug() << "Erreur lors de la vérification de l'ID_FORMATION n'existe pas pour le modifier :" << checkQuery.lastError().text();
          return;
      }

      if (!checkQuery.next())
      {
          // L'ID n'existe pas, affichez un message d'erreur
          QMessageBox::critical(nullptr, QObject::tr("Modifier FORMATION"),
                                QObject::tr("L'ID_FORMATION n'existe pas dans la base de données.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
          return;
      }

      // L'ID existe, vous pouvez maintenant effectuer la modification
      FORMATIONS F(ID_FORMATION,TITREFORMATION,DESCRIPTION,DUREEFORMATION,DATEDEBUT,DATEFIN,ID_FORMATEURFK);

      QSqlQuery query;

      bool test = F.modifier(ID_FORMATION);
      if (test)
      {
          ui->tab_Formation->setModel(F.afficher()); // Rafraîchir la vue

          QMessageBox::information(nullptr, QObject::tr("Modifier Formation"),
                                   QObject::tr("Client Modifiée.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
      }
      else
      {
          QMessageBox::critical(nullptr, QObject::tr("Modifier Formation"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
      }
    }




void MainWindow::on_pb_afficherFormation_clicked()
{
    ui->tab_Formation->setModel(F.afficher());

}

void MainWindow::on_pb_supprimerFormation_clicked()
{

        int ID = ui->lineEdit_suppformation->text().toInt();

        if (F.checkIfIdExists(ID)) {
            bool test = F.supprimer(ID);
            ui->tab_Formation->setModel(F.afficher());
            if (test) {
                QMessageBox::information(nullptr, QObject::tr("Suppression réussie"),
                    QObject::tr("Suppression effectuée avec succès.\n"
                                "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);



            } else {
                QMessageBox::critical(nullptr, QObject::tr("Erreur de suppression"),
                    QObject::tr("Erreur lors de la suppression de client.\n"
                                "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            }
        } else {
            QMessageBox::critical(nullptr, QObject::tr("ID Client introuvable"),
                QObject::tr("ID Client que vous avez saisi n'existe pas.\n"
                            "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
    }




void MainWindow::on_pb_ajouter_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pb_ajouter_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_ajouterformateur_clicked()
{
    // Réinitialisez les étiquettes d'erreur à vide
    ui->lblErreurle_ID_FORMATEUR->setText("");
    ui->lblErreurIdle_NOMFORMATEUR->setText("");

    ui->lblErreurle_PRENOMFORMATEUR->setText("");
    ui->lblErreurle_SPECIALITE->setText("");

    ui->lblErreurle_EXPERIENCE->setText("");
    ui->lblErreurle_EMAILFORMATEUR->setText("");
    ui->lblErreurle_TELEPHONEFORMATEUR->setText("");

    // Récupérez les valeurs d'entrée

    QString str_id = ui->le_ID_FORMATEUR->text();
    int ID_FORMATEUR=str_id.toInt();
    QString NOMFORMATEUR = ui->le_NOMFORMATEUR->text();
    QString PRENOMFORMATEUR = ui->le_PRENOMFORMATEUR->text();
    QString SPECIALITE = ui->le_SPECIALITE->text();
    QString EXPERIENCE =ui->le_EXPERIENCE->text();
    QString EMAILFORMATEUR = ui->le_EMAILFORMATEUR->text();
    QString TELEPHONEFORMATEUR = ui->le_TELEPHONEFORMATEUR->text();


    // Validez les champs d'entrée
    bool isValid = true;

    if (str_id.isEmpty()) {
        ui->lblErreurle_ID_FORMATEUR->setText("<font color='red'>ID_FORMATEUR ne peut pas être vide!!!!</font>");
        isValid = false;
    }

    // Validation pour le titre (exemplaire, assurez-vous qu'il n'est pas vide)
    if (NOMFORMATEUR.isEmpty()) {
        ui->lblErreurIdle_NOMFORMATEUR->setText("<font color='red'>NOMFORMATEUR ne peut pas être vide!!!</font>");
        isValid = false;
    }

    if (PRENOMFORMATEUR.isEmpty()) {
        ui->lblErreurle_PRENOMFORMATEUR->setText("<font color='red'>PRENOMFORMATEUR ne peut pas être vide!!!</font>");
        isValid = false;
    }
    if (SPECIALITE.isEmpty()) {
        ui->lblErreurle_SPECIALITE->setText("<font color='red'>SPECIALITE ne peut pas être vide!!!</font>");
        isValid = false;
    }
    if (EXPERIENCE.isEmpty()) {
        ui->lblErreurle_EXPERIENCE->setText("<font color='red'>EXPERIENCE ne peut pas être vide!!!</font>");
        isValid = false;
    }
    if (EMAILFORMATEUR.isEmpty()) {
        ui->lblErreurle_EMAILFORMATEUR->setText("<font color='red'>EMAILFORMATEUR ne peut pas être vide!!!</font>");
        isValid = false;
    }
    if (TELEPHONEFORMATEUR.isEmpty()) {
        ui->lblErreurle_TELEPHONEFORMATEUR->setText("<font color='red'>TELEPHONEFORMATEUR ne peut pas être vide!!!</font>");
        isValid = false;
    }


    // Ajouter une vérification de l'existence de l'ID dans la base de données
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT ID_FORMATEUR FROM FORMATEURS WHERE ID_FORMATEUR = :ID_FORMATEUR");
    checkQuery.bindValue(":ID_FORMATEUR", ID_FORMATEUR);
    if (checkQuery.exec() && checkQuery.next()) {
        ui->lblErreurle_ID_FORMATEUR->setText("<font color='red'>ID_FORMATEUR existe déjà!!!!</font>");
        isValid = false;
    }

    // Continuez avec les autres validations d'entrée...

    if (isValid) {
        // Si l'entrée est valide et que l'ID n'existe pas, procédez à l'ajout de l'activité
        FORMATEURS Fo(ID_FORMATEUR,NOMFORMATEUR,PRENOMFORMATEUR,SPECIALITE,EXPERIENCE,EMAILFORMATEUR,TELEPHONEFORMATEUR);

        QSqlQuery query;
        bool test = Fo.ajouter();
        if (test) {
            ui->tab_formateur->setModel(Fo.afficher()); // Rafraîchir la vue

            QMessageBox::information(nullptr, QObject::tr("Ajout Formateur"),
                QObject::tr("Client ajoutée avec succès.\n"
                            "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);


        } else {
            QMessageBox::critical(nullptr, QObject::tr("Ajout Formateur"),
                QObject::tr("Erreur lors de l'ajout de Client.\n"
                            "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
    } else {
        // Gérez l'erreur d'entrée invalide ou d'ID existant
    }
}


void MainWindow::on_modifierformateur_clicked()
{
// Récupérez les valeurs d'entrée

    QString str_id = ui->le_ID_FORMATEUR->text();
    int ID_FORMATEUR=str_id.toInt();
    QString NOMFORMATEUR = ui->le_NOMFORMATEUR->text();
    QString PRENOMFORMATEUR = ui->le_PRENOMFORMATEUR->text();
    QString SPECIALITE = ui->le_SPECIALITE->text();
    QString EXPERIENCE =ui->le_EXPERIENCE->text();
    QString EMAILFORMATEUR = ui->le_EMAILFORMATEUR->text();
    QString TELEPHONEFORMATEUR = ui->le_TELEPHONEFORMATEUR->text();


  // Vérification si l'ID existe
  QSqlQuery checkQuery;
  checkQuery.prepare("SELECT * FROM FORMATEURS WHERE ID_FORMATEUR = :ID_FORMATEUR");
  checkQuery.bindValue(":ID_FORMATEUR", ID_FORMATEUR);


  if (!checkQuery.exec())
  {
      // Erreur lors de l'exécution de la requête
      qDebug() << "Erreur lors de la vérification de l'ID FORMATEURS n'existe pas pour le modifier :" << checkQuery.lastError().text();
      return;
  }

  if (!checkQuery.next())
  {
      // L'ID n'existe pas, affichez un message d'erreur
      QMessageBox::critical(nullptr, QObject::tr("Modifier FORMATEURS"),
                            QObject::tr("L'ID FORMATEURS n'existe pas dans la base de données.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
      return;
  }

  // L'ID existe, vous pouvez maintenant effectuer la modification
  FORMATEURS Fo(ID_FORMATEUR,NOMFORMATEUR,PRENOMFORMATEUR,SPECIALITE,EXPERIENCE,EMAILFORMATEUR,TELEPHONEFORMATEUR);

  QSqlQuery query;

  bool test = Fo.modifier(ID_FORMATEUR);
  if (test)
  {
      ui->tab_formateur->setModel(Fo.afficher()); // Rafraîchir la vue

      QMessageBox::information(nullptr, QObject::tr("Modifier FORMATEURS"),
                               QObject::tr("Client Modifiée.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
  }
  else
  {
      QMessageBox::critical(nullptr, QObject::tr("Modifier FORMATEURS"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
  }
}




void MainWindow::on_afficherformateur_clicked()
{
    ui->tab_formateur->setModel(Fo.afficher()); // Rafraîchir la vue

}

void MainWindow::on_supprimerformateur_clicked()
{


            int ID = ui->lineEdit_supp_formateur->text().toInt();

            if (Fo.checkIfIdExists(ID)) {
                bool test = Fo.supprimer(ID);
                ui->tab_formateur->setModel(Fo.afficher());
                if (test) {
                    QMessageBox::information(nullptr, QObject::tr("Suppression réussie"),
                        QObject::tr("Suppression effectuée avec succès.\n"
                                    "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);



                } else {
                    QMessageBox::critical(nullptr, QObject::tr("Erreur de suppression"),
                        QObject::tr("Erreur lors de la suppression de client.\n"
                                    "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
                }
            } else {
                QMessageBox::critical(nullptr, QObject::tr("ID Client introuvable"),
                    QObject::tr("ID Client que vous avez saisi n'existe pas.\n"
                                "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            }
        }










void MainWindow::on_lineEdit_rechercheformation_textChanged(const QString &arg1)
{
    QString NOM=ui->lineEdit_rechercheformation->text();
   ui->tab_Formation->setModel(F.rechercher(NOM));
  ui->tab_Formation->clearSelection();
}

void MainWindow::on_lineEdit_rechercheformateur_textChanged(const QString &arg1)
{
    QString NOM=ui->lineEdit_rechercheformateur->text();
   ui->tab_formateur->setModel(Fo.rechercher(NOM));
  ui->tab_formateur->clearSelection();
}


void MainWindow::on_qrcodegen_formation_clicked()
{
    QString value = ui->qrcode->text();

    QSqlQuery qry;
    qry.prepare("SELECT * FROM FORMATIONS WHERE ID_FORMATION = :ID_FORMATION");
    qry.bindValue(":ID_FORMATION", value);
    qry.exec();

    if (qry.next()) {
        // ID exists in the database


        QString id = qry.value(0).toString();
        QString titre = qry.value(1).toString();
        QString desc = qry.value(2).toString();
        QString duree    = qry.value(3).toString();
        QString datedebut = qry.value(4).toString();
        QString datefin = qry.value(5).toString();
        QString id_formateur = qry.value(6).toString();


        QString text = "ID Formation :" + id + "\n" + "titre :" + titre + "\n" + "desc :" + desc + "\n" +
                       "duree :" + duree + "\n" + " datedebut :" + datedebut+ "\n" + "datefin :" + datefin+ "\n" + " id_formateur :" + id_formateur
             ;

        // Create the QR Code object
        QrCode qr = QrCode::encodeText(text.toUtf8().data(), QrCode::Ecc::MEDIUM);

        qint32 sz = qr.getSize();
        QImage im(sz, sz, QImage::Format_RGB32);
        QRgb black = qRgb(191, 112, 105);
        QRgb white = qRgb(255, 255, 255);

        for (int y = 0; y < sz; y++) {
            for (int x = 0; x < sz; x++) {
                im.setPixel(x, y, qr.getModule(x, y) ? black : white);
            }
        }

        ui->qrcodecommande_2->setPixmap(QPixmap::fromImage(im.scaled(200, 200, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));
    } else {
        // ID does not exist in the database
        QMessageBox::critical(nullptr, QObject::tr("ID introuvable"),
            QObject::tr("ID Client que vous avez saisi n'existe pas.\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
