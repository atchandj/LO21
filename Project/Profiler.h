#ifndef PROFILER_H
#define PROFILER_H

#include "UVEditeur.h"

#include <QApplication>
#include <QMainWindow>
#include <QInputDialog>

/*!
 * \class Profiler
 * \brief Fenêtre principale du programme
 */
class Profiler : public QMainWindow{
    Q_OBJECT
public:
    /*!
     * \brief Constructeur
     * \param parent : Widget père
     */
    explicit Profiler(QWidget *parent = 0);
signals:
public slots:
    void openFormation();
    /*!
     * \brief Charge un catalogue d'uv à partir d'un fichier
     */
    void openChargerUV();
    /*!
     * \brief Ouvre l'éditeur des uvs
     */
    void openUV();
    /*!
     * \brief Charge les catégories à partir d'un fichier
     */
    void openChargerCategorie();
    /*!
     * \brief Ouvre l'éditeur des catégories
     */
    void openCategorie();
    /*!
     * \brief Charge les formations à partir d'un fichier
     */
    void openChargerFormation();
    /*!
     * \brief Créer un nouveau dossier
     */
    void NouveauDossier();
    /*!
     * \brief Charge le dosier d'un étudiant à partir d'un fichier
     */
    void OpenChargerDossier();
    /*!
     * \brief Ouvre l'éditeur du dossier
     */
    void OpenDossier();
};

#endif // PROFILER_H
