#include "chifoumivue.h"
#include "ui_chifoumivue.h"
#include "modele.h"

#include <QMetaObject>
#include <QMessageBox>

ChifoumiVue ::ChifoumiVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChifoumiVue)
{
    ui->setupUi(this);

    //Conection des actions aux slots
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()),qApp,SLOT(quit()));     //Permet de fermer l'application
    QObject::connect(ui->actionA_propos, SIGNAL(triggered()),this,SLOT(aPropos())); //Permet d'afficher une box indiquant la version et les créateurs
}
ChifoumiVue ::~ChifoumiVue()
{
    delete ui;
}
void ChifoumiVue::conexionPresentation(QObject *p)
{
    //pour se connecter avec la presentation
     QObject::connect(ui->boutonPartie,SIGNAL(clicked()),p,SLOT(demanderNouvellePartie()));
     QObject::connect(ui->boutonCiseau, SIGNAL(clicked()),p,SLOT(demanderCiseau()));
     QObject::connect(ui->boutonPierre, SIGNAL(clicked()),p,SLOT(demanderPierre()));
     QObject::connect(ui->boutonPapier, SIGNAL(clicked()),p,SLOT(demanderPapier()));
}
void ChifoumiVue::deconexionPresentation(QObject *p)
{
    //pour se deconnecter de la presentation
     QObject::disconnect(ui->boutonPartie,SIGNAL(clicked()),p,SLOT(demanderNouvellePartie()));
     QObject::disconnect(ui->boutonCiseau, SIGNAL(clicked()),p,SLOT(demanderCiseau()));
     QObject::disconnect(ui->boutonPierre, SIGNAL(clicked()),p,SLOT(demanderPierre()));
     QObject::disconnect(ui->boutonPapier, SIGNAL(clicked()),p,SLOT(demanderPapier()));
}


void ChifoumiVue::setEtatBoutonsJeux(bool b)
{
    ui->boutonCiseau->setEnabled(b);
    ui->boutonPapier->setEnabled(b);
    ui->boutonPierre->setEnabled(b);
}


void ChifoumiVue::majImageCoupMachine(Modele::UnCoup c)
{
    /*Mise à jour de l'image de la machine*/
    switch (c) {
    case Modele::pierre:
        ui->imageCoupMachine->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/pierre.gif")));
        break;
    case Modele::ciseau:
        ui->imageCoupMachine->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/ciseau.gif")));
        break;
    case Modele::papier:
        ui->imageCoupMachine->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/papier.gif")));
        break;
    case Modele::rien:
        ui->imageCoupMachine->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/rien.gif")));
        break;
    default: break;
    }
}
void ChifoumiVue::majImageCoupJoueur(Modele::UnCoup c)
{
    /*Mise à jour de l'image du coup du joueur*/
    switch (c) {
    case Modele::pierre:
        ui->imageCoupJoueur->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/pierre.gif")));
        break;
    case Modele::ciseau:
        ui->imageCoupJoueur->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/ciseau.gif")));
        break;
    case Modele::papier:
        ui->imageCoupJoueur->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/papier.gif")));
        break;
    case Modele::rien:
        ui->imageCoupJoueur->setPixmap(QPixmap(QString::fromUtf8(":/chifoumi/images/rien.gif")));
        break;
    default: break;
    }
}
void ChifoumiVue::majLabelScoreMachine(unsigned int scoreMachine)
{
    ui->labelScoreMachine->setText(QString::number(scoreMachine));
}
void ChifoumiVue::majLabelScoreJoueur(unsigned int scoreJoueur)
{
    ui->labelScoreJoueur->setText(QString::number(scoreJoueur));
}
void ChifoumiVue::majScoresCoups(int unsigned scoreJoueur, int unsigned scoreMachine, Modele::UnCoup coupJoueur, Modele::UnCoup coupMachine)
{
    //Met a jour les elements graphiques
    majImageCoupMachine(coupMachine);
    majImageCoupJoueur(coupJoueur);
    majLabelScoreMachine(scoreMachine);
    majLabelScoreJoueur(scoreJoueur);
}
void ChifoumiVue::initScoreFin(unsigned int scoreFin)
{
    ui->labelScoreFin->setText(QString::number(scoreFin));
}


void ChifoumiVue::setJoueurEnBleu(bool bleu)
{
    if (bleu)
    {
        ui->labelScoreJoueur->setStyleSheet("color : #2986CC;");
        ui->labelVous->setStyleSheet("color : #2986CC;");
    }
    else
    {
        ui->labelScoreJoueur->setStyleSheet(styleSheet());
        ui->labelVous->setStyleSheet(styleSheet());
    }
}
void ChifoumiVue::focusBJouer()
{
    ui->boutonPartie->setFocus();
}
void ChifoumiVue::affichageFin(unsigned int scoreJoueur, unsigned int scoreMachine)
{
    // -- Maj de l interface --
    QMessageBox boiteFin;
    boiteFin.setWindowTitle("Game over");
    QString messageFin;


    //Gestion des scores finaux
    if (scoreJoueur > scoreMachine)
    {
        //Joueur gagne
        messageFin.append("Joueur gagne avec " + QString::number(scoreJoueur) + " points.");
    }
    else if (scoreJoueur < scoreMachine)
    {
        //Machine gagne
        messageFin.append("Machine gagne avec " + QString::number(scoreMachine) + " points.");
    }
    else
    {
        //Aucun gagnant (scores egaux)
        messageFin.append(" aucun gagnant.");
    }

    boiteFin.setText(messageFin);
    boiteFin.exec();
}


void ChifoumiVue::aPropos()
{
    QMessageBox maBox;
    maBox.setWindowTitle("A propos de cette application");
    maBox.setText("Auteurs: Robin Alonzo, Nicolas Delahaie & Alexandre Pascal \nVersion : V3");
    maBox.exec();
}
