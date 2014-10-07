#ifndef CATEGORIEEDITEUR_H
#define CATEGORIEEDITEUR_H

#include"UTProfiler.h"

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
 * \class CategorieEditeur
 * \brief Classe créer l'interface graphique permettant de rechercher,de modifier,d'ajouter et de supprimer des catégories
 */
class CategorieEditeur : public QWidget{
    Q_OBJECT
    QTableWidget* categorie;
    QLabel* categorieLabel;
    QPushButton* ajouter;
    QPushButton* supprimer;
    QPushButton* modifier;
    QGridLayout *layout;
public:
    /*!
     * \brief Constructeur
     * \param parent : Widget père
     */
    explicit CategorieEditeur(QWidget *parent = 0);
signals:
public slots:
    /*!
     * \brief Modifie une catégorie
     */
    void modifierCategorie();
    /*!
     * \brief Supprime une catégorie
     */
    void supprimerCategorie();
    /*!
     * \brief Ajoute une categorie
     */
    void ajouterCategorie();
private slots:
};

#endif // CATEGORIEEDITEUR_H
