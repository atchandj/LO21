#ifndef FORMATIONEDITEUR_H
#define FORMATIONEDITEUR_H

#include "Formation.h"
#include "UV.h"
#include "formationmanager.h"
#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>


/*!
 * \class FormationEditeur
 * \brief Classe créer l'interface graphique permettant de rechercher,de modifier,d'ajouter et de supprimer des formations
 */

class FormationEditeur : public QWidget{
    Q_OBJECT
    Formation* formation;
    QLineEdit* code;
    QLabel* codeLabel;
    QLabel* categorieLabel;
    QTableWidget* categorie;
    QLabel* filiereLabel;
    QTableWidget* filiere;
    QPushButton* rechercher;
    QPushButton* ajouterForm;
    QPushButton* sauver;
    QPushButton* ajouterCat;
    QPushButton* supprimerCat;
    QPushButton* ajouterFil;
    QPushButton* supprimerFil;
    QPushButton* supprimerForm;
    QPushButton* annuler;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QVBoxLayout* coucheH2;
    QVBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;
    QVBoxLayout* coucheH6;
    QVBoxLayout* coucheH7;

public:
    /*!
     * \brief Constructeur de la classe FormationEditeur
     * \param uvToEdit : Formation à éditer
     * \param parent : Widget père
     * \param edit : Booléen permettant de savoir quel widget on doit faire apparaître : true = mode edition, false = mode d'ajout
     */
    explicit FormationEditeur(Formation& formationToEdit,bool edit= true,QWidget *parent = 0);
    /*!
     * \brief Remplie le TabWidget categorie contenant toutes les catégories de la formation ainsi que lescrédits associés
     */
    void InitialisationCat();
    /*!
     * \brief Remplie le TabWidget contenant toutes les filières de la formation ainsi que les crédits associés
     */
    void InitialisationFil();

signals:
public slots:
    //Pas besoin de fonction save parce que l'on utilise des pointeurs vers l'objet
    /*!
     * \brief Recherche une formation
     */
    void rechercherFormation();
    /*!
     * \brief Supprime une categorie de la formation
     */
    void supprimerCategorie();
    /*!
     * \brief Ajoute une categorie de la formation
     */
    void ajouterCategorie();
    /*!
     * \brief Supprime une filiere de la formation
     */
    void supprimerFiliere();
    /*!
     * \brief Ajoute une filiere de la formation
     */
    void ajouterFiliere();
    /*!
     * \brief Ajoute une nouvelle formation
     */
    void ajouterFormation();
    /*!
     * \brief Supprime une formation
     */
    void supprimerFormation();
private slots:
};



#endif // FORMATIONEDITEUR_H
