#include "include_all.h"

#include <qdebug.h>
#include <QMessageBox>
#include <QHeaderView>

/*
2 fenêtres : une pour éditer une formation et donc edit = true
             et l'autre pour ajouter une nouvelle formation : edit = false
 */
FormationEditeur::FormationEditeur(Formation& formationToEdit,bool edit,QWidget* parent):QWidget(parent),formation(&formationToEdit)
{
    this->setWindowTitle(QString("Edition de la formation ")+formation->getCode());


    codeLabel = new QLabel("Code",this);
    categorieLabel = new QLabel("Profil",this);
    filiereLabel = new QLabel("Filiere",this);

    code = new QLineEdit(formation->getCode(),this);

    //Liste des catégories
    categorie = new QTableWidget(formation->getTailleProfil(),2,this);
    categorie->setSelectionBehavior(QAbstractItemView::SelectRows);
    categorie->resizeColumnsToContents();
    categorie->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList labelCategorie;
    labelCategorie << "Catégorie" <<"Credits";
    categorie->setHorizontalHeaderLabels(labelCategorie);
    InitialisationCat();
    categorie->setMinimumHeight(200);

    //Liste des filieres
    filiere = new QTableWidget(formation->getTailleFiliere(),2,this);
    filiere->setSelectionBehavior(QAbstractItemView::SelectRows);
    filiere->resizeColumnsToContents();
    filiere->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList labelFiliere;
    labelFiliere << "Filières" <<"Credits";
    filiere->setHorizontalHeaderLabels(labelFiliere);
    InitialisationFil();
    filiere->setMinimumHeight(200);

    if(edit == true){
        rechercher = new QPushButton("Rechercher",this);
        ajouterForm = new QPushButton("Ajouter Formation",this);
        supprimerForm = new QPushButton("Supprimer Formation",this);
    }
    else{
        sauver = new QPushButton("Sauver",this);
        annuler= new QPushButton("Annuler", this);
    }
    ajouterCat = new QPushButton("Ajouter une Catégorie",this);
    supprimerCat = new QPushButton("Supprimer Catégorie",this);
    ajouterFil = new QPushButton("Ajouter une Filière",this);
    supprimerFil = new QPushButton("Supprimer Filière",this);


    if(edit == true){
        QObject::connect(rechercher,SIGNAL(clicked()),this,SLOT(rechercherFormation()));
        QObject::connect(ajouterForm,SIGNAL(clicked()),this,SLOT(ajouterFormation()));
        QObject::connect(supprimerForm,SIGNAL(clicked()),this,SLOT(supprimerFormation()));
    }
    else
    {
        QObject::connect(sauver,SIGNAL(clicked()),parent,SLOT(/*sauverFormation()*/accept()));
        QObject::connect(annuler,SIGNAL(clicked()),parent,SLOT(close()));
    }
    QObject::connect(ajouterCat,SIGNAL(clicked()),this,SLOT(ajouterCategorie()));
    QObject::connect(supprimerCat,SIGNAL(clicked()),this,SLOT(supprimerCategorie()));
    QObject::connect(ajouterFil,SIGNAL(clicked()),this,SLOT(ajouterFiliere()));
    QObject::connect(supprimerFil,SIGNAL(clicked()),this,SLOT(supprimerFiliere()));


    // diposition des couches
    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(codeLabel);
    coucheH1->addWidget(code);
    if(edit == true)
        coucheH1->addWidget(rechercher);

    coucheH2 = new QVBoxLayout;
    coucheH2->addWidget(categorieLabel);
    coucheH2->addWidget(categorie);

    coucheH3 = new QVBoxLayout;
    coucheH3->addWidget(filiereLabel);
    coucheH3->addWidget(filiere);



    coucheH6 = new QVBoxLayout;
    coucheH6->addLayout(coucheH2);
    coucheH6->addWidget(ajouterCat);
    coucheH6->addWidget(supprimerCat);

    coucheH7 = new QVBoxLayout;
    coucheH7->addLayout(coucheH3);
    coucheH7->addWidget(ajouterFil);
    coucheH7->addWidget(supprimerFil);

    coucheH4 = new QHBoxLayout;
    coucheH4->addLayout(coucheH6);
    coucheH4->addLayout(coucheH7);

    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH4);
    couche->addSpacing(10);
    if(edit == true){
        couche->addWidget(ajouterForm);
        couche->addWidget(supprimerForm);
    }
    else
    {
        coucheH5 = new QHBoxLayout;
        coucheH5->addWidget(annuler);
        coucheH5->addWidget(sauver);
        couche->addLayout(coucheH5);
    }
    setLayout(couche);
}

//Rempli tableau des catégories
void FormationEditeur::InitialisationCat()
{
    QList<QString> Profil = formation->ListeProfil();
    int i = 0;
    QTableWidgetItem *monItem;
    for(QList<QString>::Iterator it = Profil.begin(); it < Profil.end(); it++)
    {
        monItem = new QTableWidgetItem(*it);
        categorie->setItem(i,0,monItem);
        char credit[4];
        sprintf(credit,"%d",formation->getProfil(*it));
        monItem = new QTableWidgetItem(credit);
        categorie->setItem(i,1,monItem);
        i++;
    };
}

//Rempli le tableau des filieres
void FormationEditeur::InitialisationFil()
{
    QList<QString> Filiere = formation->ListeFiliere();
    int i = 0;
    QTableWidgetItem *monItem;
    for(QList<QString>::Iterator it = Filiere.begin(); it < Filiere.end(); it++)
    {
        monItem = new QTableWidgetItem(*it);
        filiere->setItem(i,0,monItem);
        char credit[4];
        sprintf(credit,"%d",formation->getFiliere(*it));
        monItem = new QTableWidgetItem(credit);
        filiere->setItem(i,1,monItem);
        i++;
    };
}

//Recherche une formation

void FormationEditeur::rechercherFormation()
{
    QString newcode = code->text();

    try
    {
        formation = &FormationManager::getInstance().getFormation(newcode);//Cherche la formation dans FormationManager
        //Mise à jour des Widgets avec les valeurs de l'UV que l'on a recherché
        categorie->clearContents();
        categorie->setRowCount(formation->getTailleProfil());
        filiere->clearContents();
        filiere->setRowCount(formation->getTailleFiliere());
        InitialisationCat();
        InitialisationFil();
        QMessageBox::information(this,"Recherche", QString("Recherche de la formation ")+newcode+" réussie.");
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Recherche", QString("Erreur : la formation ")+newcode+" n’existe pas.");
    }
}

///Ajoute une Catégorie dans le profil de la formation
void FormationEditeur::ajouterCategorie()
{
    try
    {
        QDialog* window = new QDialog(this);
        QGridLayout* lay = new QGridLayout;
        QPushButton* ok = new QPushButton("Ok");
        QLineEdit* code= new QLineEdit(this);
        QLabel* codeLabel= new QLabel("Code : ",this);
        QLineEdit* credit= new QLineEdit(this);
        QLabel* creditLabel= new QLabel("Crédit : ",this);
        window->setFixedSize(200, 100);

        lay->addWidget(codeLabel,0,0);
        lay->addWidget(creditLabel,1,0);
        lay->addWidget(code,0,1);
        lay->addWidget(credit,1,1);
        lay->addWidget(ok,2,1);

        window->setLayout(lay);

        connect(ok,SIGNAL(clicked()),window,SLOT(accept()));
        window->exec();

        if(window->result())
        {
            if(credit->text().isEmpty() || code->text().isEmpty())//Vérifie que les cases ont été remplis
                throw UTProfilerException("Remplissez toutes les cases !");

            //Appel de la fonction getCategorie() pour vérifier que la catégorie existe
            CategorieManager::getInstance().getCategorie(code->text());
            if(!formation->isEmptyProfil()){
                QList<QString> Profil = formation->ListeProfil();
                if(Profil.contains(code->text()))
                    throw UTProfilerException("Catégorie déjà présente dans le profil");

                if(credit->text().toUInt() == 0) //Vérifie que c'est des chiffres
                    throw UTProfilerException("Les crédits sont des nombres !");
            }
            formation->ajouterCategorie(code->text(),credit->text().toUInt());
            categorie->setRowCount(formation->getTailleProfil());
            QTableWidgetItem *monItem = new QTableWidgetItem(code->text());
            categorie->setItem(formation->getTailleProfil() - 1,0,monItem);
            monItem = new QTableWidgetItem(credit->text());
            categorie->setItem(formation->getTailleProfil() -1,1,monItem);
            QMessageBox::information(this,"Ajout d'une catégorie", QString("Ajout de la catégorie ")+code->text()+" réussie.");
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Edition Categorie", e.getInfo());
    }
}

///Suprime une catégorie
void FormationEditeur::supprimerCategorie()
{
    try
    {
        QTableWidgetItem* ItemSupp = categorie->item(categorie->currentRow(),0);
        if(ItemSupp==NULL || !ItemSupp->isSelected())
            throw UTProfilerException("Sélectionner une catégorie !");
        QString c = ItemSupp->text();

        //Demande à l'utilisateur s'il es sûr de son choix
        int reponse = QMessageBox::question(this,"Suppression de " + c, "Voulez vous vraiment supprimer cette catégorie ?", QMessageBox::Yes | QMessageBox::No);
        if(reponse == QMessageBox::Yes) //Vérifie si l'utilisateur a choisi oui
        {
            formation->supprimerCategorie(c);
            categorie->clearContents();
            categorie->setRowCount(formation->getTailleProfil());
            InitialisationCat();
            QMessageBox::information(this,"Suppression Catégorie","Catégorie supprimée");
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this,"Editeur de Formation",e.getInfo());
    }
}

///Ajoute une filière
void FormationEditeur::ajouterFiliere()
{
    try
    {
        QDialog* window = new QDialog(this);
        QGridLayout* lay = new QGridLayout;
        QPushButton* ok = new QPushButton("Ok");
        QLineEdit* code= new QLineEdit(this);
        QLabel* codeLabel= new QLabel("Code : ",this);
        QLineEdit* credit= new QLineEdit(this);
        QLabel* creditLabel= new QLabel("Crédit : ",this);
        window->setFixedSize(200, 100);

        lay->addWidget(codeLabel,0,0);
        lay->addWidget(creditLabel,1,0);
        lay->addWidget(code,0,1);
        lay->addWidget(credit,1,1);
        lay->addWidget(ok,2,1);

        window->setLayout(lay);

        connect(ok,SIGNAL(clicked()),window,SLOT(accept()));
        window->exec();

        if(window->result())
        {
            if(credit->text().isEmpty() || code->text().isEmpty())//Vérifie que les cases ont été remplis
                throw UTProfilerException("Remplisser toutes les cases !");

            if(!formation->isEmptyFiliere()){
                QStringList F = formation->ListeFiliere();
                if(F.contains(code->text()))
                    throw UTProfilerException("Filière déjà existante !");

                if(credit->text().toUInt() == 0) //Vérifie que c'est des chiffres
                    throw UTProfilerException("Les crédits sont des nombres !");
            }

            formation->ajouterFiliere(code->text(),credit->text().toUInt());
            filiere->setRowCount(formation->getTailleFiliere());
            QTableWidgetItem *monItem = new QTableWidgetItem(code->text());
            filiere->setItem(formation->getTailleFiliere() - 1,0,monItem);
            monItem = new QTableWidgetItem(credit->text());
            filiere->setItem(formation->getTailleFiliere() - 1,1,monItem);
            QMessageBox::information(this,"Ajout Filière", QString("Ajout de la filière ")+code->text()+" réussie.");
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Edition Filière", e.getInfo());
    }
}

///Supprime une filière
void FormationEditeur::supprimerFiliere()
{
    try
    {
        QTableWidgetItem* ItemSupp = filiere->item(filiere->currentRow(),0);
        if(ItemSupp==NULL || !ItemSupp->isSelected())
            throw UTProfilerException("Sélectionner une Filière !");
        QString c = ItemSupp->text();

        //Demande à l'utilisateur s'il est sûr de son choix
        int reponse = QMessageBox::question(this,"Suppression de " + c, "Voulez vous vraiment supprimer cette filière ?", QMessageBox::Yes | QMessageBox::No);
        if(reponse == QMessageBox::Yes) //Vérifie si l'utilisateur a choisi oui
        {
            formation->supprimerFiliere(c);
            filiere->clearContents();
            filiere->setRowCount(formation->getTailleFiliere());
            InitialisationFil();
            QMessageBox::information(this,"Suppression Filière","Filière supprimée");
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this,"Editeur de Formation",e.getInfo());
    }
}

void FormationEditeur::ajouterFormation()
{
    try
    {
        QDialog* window = new QDialog(this);
        window->setWindowTitle("Ajout d'une nouvelle Formation");
        QMap<QString, unsigned int> P;
        QMap<QString, unsigned int> F;
        Formation* f = new Formation("",P,F);
        window->setFixedSize(550, 425);
        FormationEditeur* newFormation = new FormationEditeur(*f,false,window);
        window->exec();

        if(window->result())
        {
            if(newFormation->code->text().isEmpty())
                throw UTProfilerException("Remplissez le code de la formation !");
            FormationManager::getInstance().ajouterFormation(newFormation->code->text(),newFormation->formation->getAllProfil(),newFormation->formation->getAllFiliere());
            QMessageBox::information(this, "Ajout", "Formation ajoutée");
            newFormation->close();
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this,"Editeur de Formation",e.getInfo());
    }
}

void FormationEditeur::supprimerFormation()
{
    try
    {
        if(code->text().isEmpty())
            throw UTProfilerException("Remplissez le code de la formation !");
        int reponse = QMessageBox::question(this,"Suppression de " + code->text(), "Voulez vous vraiment supprimer cette Formation ?", QMessageBox::Yes | QMessageBox::No);
        if(reponse == QMessageBox::Yes) //Vérifie si l'utilisateur a choisi oui
        {
            FormationManager::getInstance().supprimerFormation(code->text());
            QMessageBox::information(this,"Suppression de Formation","Formation supprimée");
            code->clear();
            categorie->clearContents();
            filiere->clearContents();
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this,"Suppression de Formation",e.getInfo());
    }
}
