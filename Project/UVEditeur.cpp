#include "include_all.h"

#include <QMessageBox>

UVEditeur::UVEditeur(UV& uvToEdit, QWidget *parent) :QWidget(parent),uv(&uvToEdit){
    this->setWindowTitle(QString("Edition de l’UV ")+uv->getCode());
    //parent->setFixedSize(400, 300);

    if(CategorieManager::getInstance().getTaille() == 0)
    {
        QMessageBox::warning(this,"Chargement Catégorie","Erreur lors du chargement des Categories.\nRecharger le fichier");
        this->close();
    }
    else
    {
        // creation des labels
        codeLabel = new QLabel("code",this);
        titreLabel = new QLabel("titre",this);
        creditsLabel = new QLabel("credits",this);
        categorieLabel = new QLabel("categorie",this);
        ouvertureLabel = new QLabel("ouverture",this);

        // création des composants éditables
        code = new QLineEdit(uv->getCode(),this);
        titre = new QTextEdit(uv->getTitre(),this);
        credits=new QSpinBox(this);
        credits->setRange(1,8);
        credits->setValue(uv->getNbCredits());
        categorie=new QComboBox(this);

        for(int i = 0; i < CategorieManager::getInstance().getTaille() ;i++)
            categorie->addItem(CategorieManager::getInstance().getElement(i).CategorieToString());
        categorie->setCurrentText((uv->getCategorie().CategorieToString()));

        automne=new QCheckBox("automne",this);
        automne->setChecked(uv->ouvertureAutomne());
        printemps=new QCheckBox("printemps",this);
        printemps->setChecked(uv->ouverturePrintemps());
        if(uv->getCode() == ""){
            sauver= new QPushButton("Enregistrer", this);
            connect(sauver,SIGNAL(clicked()),parent,SLOT(accept()));
        }
        else{
            sauver= new QPushButton("Sauver", this);
            sauver->setEnabled(false);
            QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverUV()));
            annuler= new QPushButton("Annuler", this);
            QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
            rechercher = new QPushButton("Rechercher", this);
            QObject::connect(rechercher,SIGNAL(clicked()),this,SLOT(chercherUV()));
            ajouter = new QPushButton("Ajouter une UV",this);
            QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterUV()));
            supprimer = new QPushButton("Supprimer cette UV",this);
            QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(supprimerUV()));
        }
        /*->->->*/
        // connections
        QObject::connect(code,SIGNAL(textEdited(QString)),this,SLOT(activerSauver(QString)));
        QObject::connect(titre,SIGNAL(textChanged()),this,SLOT(activerSauver()));
        QObject::connect(categorie,SIGNAL(currentIndexChanged(QString)),this,SLOT(activerSauver(QString)));
        QObject::connect(credits,SIGNAL(valueChanged(QString)),this,SLOT(activerSauver(QString)));
        QObject::connect(automne,SIGNAL(clicked()),this,SLOT(activerSauver()));
        QObject::connect(printemps,SIGNAL(clicked()),this,SLOT(activerSauver()));

        // diposition des couches
        coucheH1 = new QHBoxLayout;
        coucheH1->addWidget(codeLabel);
        coucheH1->addWidget(code);
        if(uv->getCode() != ""){
            coucheH1->addWidget(rechercher);
         }
        coucheH1->addWidget(categorieLabel);
        coucheH1->addWidget(categorie);
        coucheH1->addWidget(creditsLabel);
        coucheH1->addWidget(credits);

        coucheH2 = new QHBoxLayout;
        coucheH2->addWidget(titreLabel);
        coucheH2->addWidget(titre);

        coucheH3 = new QHBoxLayout;
        coucheH3->addWidget(ouvertureLabel);
        coucheH3->addWidget(automne);
        coucheH3->addWidget(printemps);

        coucheH4 = new QHBoxLayout;
        if(uv->getCode() != ""){
            coucheH4->addWidget(annuler);
            coucheH4->addWidget(ajouter);
            coucheH4->addWidget(supprimer);
        }
        coucheH4->addWidget(sauver);

        couche = new QVBoxLayout;
        couche->addLayout(coucheH1);
        couche->addLayout(coucheH2);
        couche->addLayout(coucheH3);
        couche->addLayout(coucheH4);
        setLayout(couche);
    }

}

//Sauvegarde les changements sur l'uv
void UVEditeur::sauverUV()
{
    uv->setCode(code->text());
    uv->setTitre(titre->toPlainText());
    uv->setNbCredits(credits->value());
    uv->setCategorie(Categorie(categorie->currentText()));
    uv->setOuverturePrintemps(printemps->isChecked());
    uv->setOuvertureAutomne(automne->isChecked());
    QMessageBox::information(this, "Sauvegarde", "UV sauvegardée");
    sauver->setEnabled(false);
}

//Active le bouton sauver
void UVEditeur::activerSauver(QString)
{
    sauver->setEnabled(true);
}

//Cherche une UV
void UVEditeur::chercherUV()
{
    QString newcode = code->text();
    //Transforme les 2 premières lettres en majuscules => On est pas obliger de mettre le code en majuscule
    newcode[0] = newcode[0].toUpper();
    newcode[1] = newcode[1].toUpper();
    try
    {
        uv = &UVManager::getInstance().getUV(newcode);//Cherche l'uv dans UVManager
        //Mise à jour des Widgets avec les valeurs de l'UV que l'on a recherché
        code->setText(uv->getCode());
        titre->setText(uv->getTitre());
        credits->setValue(uv->getNbCredits());
        categorie->setCurrentText((uv->getCategorie().CategorieToString()));
        automne->setChecked(uv->ouvertureAutomne());
        printemps->setChecked(uv->ouverturePrintemps());
        sauver->setEnabled(false);
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Recherche", QString("Erreur : l’UV ")+newcode+" n’existe pas.");
    }

}

//Ajoute une UV
void UVEditeur::ajouterUV()
{
    try
    {
        QDialog* window = new QDialog(this);
        window->setWindowTitle("Ajout d'une nouvelle UV");
        UV* uv = new UV("","",0,Categorie(""),false,false);
        window->setFixedSize(450, 300);
        UVEditeur* fenetreUV=new UVEditeur(*uv,window);
        window->exec();
        if(window->result())
        {
            if(fenetreUV->code->text().isEmpty() || fenetreUV->titre->toPlainText().isEmpty())
                throw UTProfilerException("Remplisser toutes les cases !");
            if(!fenetreUV->automne->isChecked() && !fenetreUV->printemps->isChecked())
                throw UTProfilerException("Au moins une des 2 saisons doit être cochés (Automne/Printemps) !");
            UVManager::getInstance().ajouterUV(fenetreUV->code->text(),fenetreUV->titre->toPlainText(),fenetreUV->credits->value(),Categorie(fenetreUV->categorie->currentText()),fenetreUV->automne->isChecked(),fenetreUV->printemps->isChecked());
            QMessageBox::information(this,"Ajout UV","UV ajoutée avec succès");
        }

    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this,"Ajout UV", e.getInfo());
    }
}

//Supprime une UV
void UVEditeur::supprimerUV()
{
    try
    {
        UVManager::getInstance().deleteUV(code->text());
        QMessageBox::information(this,"Suppression UV","UV supprimée avec succès");
        sauver->setEnabled(false);

        code->clear();
        titre->clear();
        automne->setChecked(false);
        printemps->setChecked(false);
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this,"Suppression UV",e.getInfo());
    }
}
