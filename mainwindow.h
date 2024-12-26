#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "formations.h"
#include "formateurs.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:



    void on_pb_ajouter_2_clicked();

    void on_pb_ajouter_3_clicked();

    void on_pb_ajouterFormation_clicked();

    void on_ajouterformateur_clicked();

    void on_modifierformateur_clicked();

    void on_afficherformateur_clicked();

    void on_supprimerformateur_clicked();

    void on_pb_supprimerFormation_clicked();

    void on_pb_afficherFormation_clicked();

    void on_pb_modifierFormation_clicked();



    void on_lineEdit_rechercheformation_textChanged(const QString &arg1);

    void on_lineEdit_rechercheformateur_textChanged(const QString &arg1);
    void on_qrcodegen_formation_clicked();

private:
    Ui::MainWindow *ui;
    FORMATIONS F;
    FORMATEURS Fo;

};
#endif // MAINWINDOW_H
