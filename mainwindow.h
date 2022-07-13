#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "dipendente.h"
#include "dipendentejunior.h"
#include "dipendentesenior.h"
#include "dipendenteqlistwidgetitem.h"
#include "progettoqlistwidgetitem.h"
#include "dipendentejuniorqlistwidgetitem.h"
#include "dipendenteseniorqlistwidgetitem.h"
#include "gestore.h"


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
    void aggiornaOnlySeniorList();
    void aggiornaOnlyJuniorList();
    void aggiornaListeDipendenti();
    void aggiornaListeProgetti();
    void AlertAttenzione(QWidget* widget);
    void deleteAll(QListWidget* widget);

    void on_HOME_btn_clicked();

    void on_Opzioni_btn_clicked();

    void on_CaricaDaFile_btn_clicked();

    void on_AggiungiProgetto_btn_clicked();

    void on_AggiungiDipendente_btn_clicked();

    void on_AddDipendenteSenior_btn_clicked();

    void on_AddDipendenteJunior_btn_clicked();

    void on_AddProject_btn_clicked();

    void on_GetInfoAbout_btn_clicked();

    void on_SearchOpzioni_btn_clicked();

    void on_actionChiudi_triggered();

    void on_Clean_btn_clicked();

    void on_actionFile_txt_triggered();

    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;
    Gestore gestore;

};
#endif // MAINWINDOW_H
