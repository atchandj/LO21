#ifndef UVEDITEUR_H
#define UVEDITEUR_H

#include"uv.h"

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

/*!
 * \class UVEditeur
 * \brief Classe créer l'interface graphique permettant de rechercher,de modifier,d'ajouter et de supprimer des UV
 */
class UVEditeur : public QWidget{
    Q_OBJECT
    UV* uv;
    QLineEdit* code;
    QLabel* codeLabel;
    QTextEdit* titre;
    QLabel* titreLabel;
    QSpinBox* credits;
    QLabel* creditsLabel;
    QComboBox* categorie;
    QLabel* categorieLabel;
    QLabel* ouvertureLabel;
    QCheckBox* automne;
    QCheckBox* printemps;
    QPushButton* rechercher;
    QPushButton* sauver;
    QPushButton* ajouter;
    QPushButton* supprimer;
    QPushButton* annuler;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
public:
    /*!
     * \brief Constructeur de la classe UVEditeur
     * \param uvToEdit : UV à éditer
     * \param parent : Widget père
     */
    explicit UVEditeur(UV& uvToEdit, QWidget *parent = 0);
signals:
public slots:
    /*!
     * \brief Sauvegarde une uv
     */
    void sauverUV();
    /*!
     * \brief Active le bouton sauver
     * \param str : chaine de caractère
     */
    void activerSauver(QString str="");
    /*!
     * \brief Cherche une uv
     */
    void chercherUV();
    /*!
     * \brief Ajoute un uv
     */
    void ajouterUV();
    /*!
     * \brief Supprime une uv
     */
    void supprimerUV();
private slots:
};
#endif // UVEDITEUR_H
