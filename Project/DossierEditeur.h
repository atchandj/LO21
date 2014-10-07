#ifndef DOSSIEREDITEUR_H
#define DOSSIEREDITEUR_H

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

class DossierEditeur: public QWidget {
    Q_OBJECT
    QTableWidget* dossier;
    QComboBox *cursus;
    QLabel* cursusLabel;
    QPushButton* ajouterIns;
    QPushButton* supprimerIns;
    QPushButton* enregistrer;
    QGridLayout *layout;
    QPushButton* Profil;
public:
    /*!
     * \brief Constructeur de la classe DossierEditeur
     * \param parent : Widget père
     */
    explicit DossierEditeur(QWidget *parent = 0);

signals:
public slots:
    /*!
     * \brief Ajoute une inscription
     */
    void ajouterInscription();
    /*!
     * \brief Supprime une inscription
     */
    void supprimerInscription();
    /*!
     * \brief Initialiser le QTableWidget dossier avec les données contenu dans le dossier ouvert
     */
    void initialiserDossier();
    /*!
     * \brief Sauvegarde les données dans un fichier
     */
    void sauvegarder();
    /*!
     * \brief Affiche le profil
     */
    void afficherProfil();
private slots:
};
#endif // DOSSIEREDITEUR_H

