#include "include_all.h"

#include <QMenuBar>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <qdebug.h>
#include "FormationEditeur.h"


Profiler::Profiler(QWidget *parent):QMainWindow(parent){

    setWindowTitle("UT-Profiler");

    QLabel *bienvenue1 = new QLabel("Veuillez choisir une action dans le menu.",this);
    QLabel  *label_img  = new QLabel(this);
    QPixmap *pixmap_img = new QPixmap(":Image/utc.png");
         label_img->setPixmap(*pixmap_img);
    QLabel *bienvenue2 = new QLabel("Vos modifications seront automatiquement sauvegardées lors de la fermeture du programme.",this);
    QWidget *conteneur = new QWidget();
    QVBoxLayout *mainCouche = new QVBoxLayout;

    setWindowIcon( QPixmap( ":Image/utc.png") ); // fonctionne
    mainCouche->addWidget(bienvenue1);
    mainCouche->addWidget(bienvenue2);
    mainCouche->addWidget(label_img,0,Qt::AlignHCenter);

    conteneur->setLayout(mainCouche);
    setCentralWidget(conteneur);

    //Onglet Fichier
    QMenu* mFichier = menuBar()->addMenu("&Fichier");
    QMenu* mNouveau=mFichier->addMenu("&Nouveau");
    mFichier->addSeparator();
    QMenu* mCharger=mFichier->addMenu("&Charger");

    QAction *actionNewDossier = mNouveau->addAction("&Dossier");

    QAction * actionChargerUV=mCharger->addAction("Catalogue UVs");
    QAction * actionChargerCategorie=mCharger->addAction("Catégorie");
    QAction * actionChargerFormation=mCharger->addAction("Formation");
    QAction * actionChargerDossier=mCharger->addAction("Dossier");

    mFichier->addSeparator();

    QAction *actionQuitter = mFichier->addAction("&Quitter");

    QMenu* mEdition = menuBar()->addMenu("&Edition");
    QAction* actionUV=mEdition->addAction("&UV");
    QAction* actionCategorie=mEdition->addAction("&Categorie");
    QAction* actionFormation=mEdition->addAction("&Formation");
    QAction* actionDossier=mEdition->addAction("&Dossier");

    // connections
    connect(actionChargerUV, SIGNAL(triggered()),this,SLOT(openChargerUV()));
    connect(actionChargerCategorie, SIGNAL(triggered()),this,SLOT(openChargerCategorie()));
    connect(actionChargerFormation, SIGNAL(triggered()),this,SLOT(openChargerFormation()));
    connect(actionChargerDossier, SIGNAL(triggered()),this,SLOT(OpenChargerDossier()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionUV, SIGNAL(triggered()),this,SLOT(openUV()));
    connect(actionCategorie, SIGNAL(triggered()),this,SLOT(openCategorie()));
    connect(actionFormation, SIGNAL(triggered()),this,SLOT(openFormation()));
    connect(actionNewDossier, SIGNAL(triggered()),this,SLOT(NouveauDossier()));
    connect(actionDossier, SIGNAL(triggered()),this,SLOT(OpenDossier()));

    UVManager& m = UVManager::getInstance();
    m.setWorkspace();
    m.load(m.getPath()+"/UV_XML.xml");
    CategorieManager::getInstance().load(m.getPath()+"/Categorie.xml");
    FormationManager::getInstance().load(m.getPath()+"/Formation.xml");
    Dossier::getInstance();

}

//Charge les UVs
void Profiler::openChargerUV(){
    QString chemin = QFileDialog::getOpenFileName(this,"Sélectionner un fichier",UVManager::getInstance().getPath()); //Demande le chemin
    try {
        if (chemin!="")
        {
            UVManager::libererInstance();
            UVManager::getInstance().load(chemin);
            QMessageBox::information(this, "Chargement Catalogue", "Le catalogue d’UVs a été chargé."); //Ouvre fenêtre d'information
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Chargement Catalogue", e.getInfo());
    }
}


//Charge Categorie
void Profiler::openChargerCategorie()
{
    QString chemin = QFileDialog::getOpenFileName();
    try {
        if (chemin!="")
        {
            CategorieManager::libererInstance();
            CategorieManager::getInstance().load(chemin);
            QMessageBox::information(this, "Chargement Catégorie", "Les catégories ont été chargé.");
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Chargement Catégorie", "Erreur lors du chargement du fichier (non valide ?)");
    }
}
void Profiler::openChargerFormation()
{
    QString chemin = QFileDialog::getOpenFileName();
    try {
        if (chemin!="")
        {
            FormationManager::libererInstance();
            FormationManager::getInstance().load(chemin);
            QMessageBox::information(this, "Chargement Formation", "Les formations ont été chargé.");
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Chargement Formation", "Erreur lors du chargement du fichier (non valide ?)");
    }
}

//Ouvre editeur UV
void Profiler::openUV(){
    QDialog* window = new QDialog(this);
    QGridLayout* lay = new QGridLayout;
    QPushButton* ok = new QPushButton("Ok");
    QComboBox *ListeUV= new QComboBox(this);
    window->setFixedSize(200, 100);

    lay->addWidget(ListeUV,0,0);
    lay->addWidget(ok,1,0);

    window->setLayout(lay);
    //Transforme les 2 premières lettres en majuscules => On est pas onliger de mettre le code en majuscule
    UV** uvs = UVManager::getInstance().getUVs();
    for(unsigned int i=0;i<UVManager::getInstance().getNbUV(); i++)
    {
        ListeUV->addItem(uvs[i]->getCode());
    }
    connect(ok,SIGNAL(clicked()),window,SLOT(accept()));
    window->exec();

    if(window->result())
    {
        UV& uv=UVManager::getInstance().getUV(ListeUV->currentText());
        UVEditeur* fenetreUV=new UVEditeur(uv,this);
        setCentralWidget(fenetreUV);
    }

}

void Profiler::openCategorie()
{
    try
    {
        CategorieEditeur* fenetreCat = new CategorieEditeur(this);
        setCentralWidget(fenetreCat);
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Edition Categorie", e.getInfo());
    }
}

void Profiler::openFormation()
{
    try
    {

        QDialog* window = new QDialog(this);
        QGridLayout* lay = new QGridLayout;
        QPushButton* ok = new QPushButton("Ok");
        QComboBox *ListeFormation= new QComboBox(this);
        window->setFixedSize(200, 100);

        lay->addWidget(ListeFormation,0,0);
        lay->addWidget(ok,1,0);

        window->setLayout(lay);
        //Transforme les 2 premières lettres en majuscules => On est pas onliger de mettre le code en majuscule
        QList<Formation*> formations = *FormationManager::getInstance().getFormations();
        for(int i=0;i<FormationManager::getInstance().getTaille(); i++)
        {
            ListeFormation->addItem(formations[i]->getCode());
        }
        connect(ok,SIGNAL(clicked()),window,SLOT(accept()));
        window->exec();

        if(window->result())
        {
            Formation& formation=FormationManager::getInstance().getFormation(ListeFormation->currentText());
            FormationEditeur* fenetreFormation=new FormationEditeur(formation,this);
            setCentralWidget(fenetreFormation);
        }

    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Edition Categorie", e.getInfo());
    }
}

void Profiler::NouveauDossier()
{
    try
    {
        Dossier::libererInstance();
        DossierEditeur* fenetreDossier = new DossierEditeur(this);
        setCentralWidget(fenetreDossier);
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Nouveau Dossier", e.getInfo());
    }
}

void Profiler::OpenChargerDossier()
{
    QString chemin = QFileDialog::getOpenFileName(this,"Sélectionner un fichier",UVManager::getInstance().getPath()); //Demande le chemin
    try {
        if (chemin!="")
        {
            Dossier::libererInstance();
            Dossier::getInstance().load(chemin);
            QMessageBox::information(this, "Chargement du dossier", "Le dossier a été chargé."); //Ouvre fenêtre d'information
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Chargement Dossier", e.getInfo());
    }
}

//Ouvre l'editeur de dossier
void Profiler::OpenDossier()
{
    try
    {
        if(Dossier::getInstance().isEmpty())
            throw UTProfilerException("Charger un dosssier qui n'est pas vide!");
        DossierEditeur* fenetreDossier = new DossierEditeur(this);
        setCentralWidget(fenetreDossier);

    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Chargement Dossier", e.getInfo());
    }
}
