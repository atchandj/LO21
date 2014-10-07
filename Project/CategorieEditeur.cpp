#include "include_all.h"

#include <QMessageBox>
#include <QHeaderView>

CategorieEditeur::CategorieEditeur(QWidget *parent) :QWidget(parent){
    this->setWindowTitle(QString("Edition des catégories"));
    //parent->setFixedSize(450, 300);

     // création des composants éditables
        categorie = new QTableWidget(CategorieManager::getInstance().getTaille(),1,this);
        //categorie->setMinimumHeight(200);
        QStringList label;
        label << "Catégorie";
        categorie->setHorizontalHeaderLabels(label);
        categorie->resizeColumnsToContents();
        categorie->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        QTableWidgetItem *monItem;
        for(int i = 0; i < CategorieManager::getInstance().getTaille() ;i++)
        {
            monItem = new QTableWidgetItem(CategorieManager::getInstance().getElement(i).CategorieToString());
            categorie->setItem(i,0,monItem);
        }
        categorie->setMinimumHeight(200);
        modifier = new QPushButton("Modifier cette catégorie",this);
        QObject::connect(modifier,SIGNAL(clicked()),this,SLOT(modifierCategorie()));
        supprimer = new QPushButton("Supprimer une catégorie",this);
        QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(supprimerCategorie()));
        ajouter = new QPushButton("Ajouter une catégorie",this);
        QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterCategorie()));

       layout = new QGridLayout;
       layout->addWidget(categorie, 0, 0);
       layout->addWidget(ajouter, 1, 0);
       layout->addWidget(modifier, 2, 0);
       layout->addWidget(supprimer, 3, 0);
       setLayout(layout);
}

void CategorieEditeur::modifierCategorie()
{
    try
    {
        QTableWidgetItem *ItemModif = categorie->currentItem();
        if(ItemModif == NULL)
            throw UTProfilerException("Sélectionner une catégorie !");
        QString c = QInputDialog::getText(this,"Editeur de Catégorie","Entrez la nouvelle catégorie");
        CategorieManager::getInstance().modifierCategorie(ItemModif->text(),c);
        ItemModif->setText(c);
        QMessageBox::information(this,"Modification Catégorie","Catégorie modifiée");
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this,"Editeur de Catégorie",e.getInfo());
    }
}

void CategorieEditeur::ajouterCategorie()
{
    try
    {
        QString c = QInputDialog::getText(this,"Editeur de Catégorie","Entrez la nouvelle catégorie");
        if(c.isEmpty())
            throw UTProfilerException("La catégorie doit avoir un nom !");
        CategorieManager::getInstance().ajouterCategorie(c);
        QTableWidgetItem *monItem = new QTableWidgetItem(c);
        categorie->setRowCount(CategorieManager::getInstance().getTaille());
        categorie->setItem(CategorieManager::getInstance().getTaille() - 1,0,monItem);
        QMessageBox::information(this,"Ajout Catégorie","Catégorie ajoutée");
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this,"Editeur de Catégorie",e.getInfo());
    }
}

void CategorieEditeur::supprimerCategorie()
{
    try
    {
        QTableWidgetItem *ItemSupp = categorie->currentItem();
        if(ItemSupp == NULL)
            throw UTProfilerException("Sélectionner une catégorie !");
        QString c = ItemSupp->text();

        //Demande à l'utilisateur s'il es sûr de son choix
        int reponse = QMessageBox::question(this,"Suppression de " + c, "Voulez vous vraiment supprimer cette catégorie ?", QMessageBox::Yes | QMessageBox::No);
        if(reponse == QMessageBox::Yes) //Vérifie si l'utilisateur a choisi oui
        {
            CategorieManager::getInstance().supprimerCategorie(c);
            categorie->clearContents();
            categorie->setRowCount(CategorieManager::getInstance().getTaille());
            QTableWidgetItem *monItem;
            for(int i = 0; i < CategorieManager::getInstance().getTaille() ;i++)
            {
                monItem = new QTableWidgetItem(CategorieManager::getInstance().getElement(i).CategorieToString());
                categorie->setItem(i,0,monItem);
            }
            QMessageBox::information(this,"Suppression Catégorie","Catégorie supprimée");
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this,"Editeur de Catégorie",e.getInfo());
    }
}
