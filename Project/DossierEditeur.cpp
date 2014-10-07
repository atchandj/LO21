#include "include_all.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QHeaderView>

DossierEditeur::DossierEditeur(QWidget *parent):QWidget(parent)
{
    this->setWindowTitle(QString("Edition du dossier"));

    cursusLabel = new QLabel("Cursus en cours : ",this);


    cursus= new QComboBox(this);

    Profil = new QPushButton("Afficher Profil",this);
    dossier = new QTableWidget(0,4,this);
    dossier->setSelectionBehavior(QAbstractItemView::SelectRows);
    QStringList labelTab;
    labelTab << "UV" <<"Semestre"<< "Note" << "Cursus";
    dossier->setHorizontalHeaderLabels(labelTab);
    dossier->resizeColumnsToContents();
    dossier->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dossier->verticalHeader()->hide();
    initialiserDossier();
    ajouterIns = new QPushButton("Ajouter Inscription",this);
    supprimerIns = new QPushButton("Supprimer Inscription",this);
    enregistrer = new QPushButton("Enregistrer",this);


    QObject::connect(ajouterIns,SIGNAL(clicked()),this,SLOT(ajouterInscription()));
    QObject::connect(supprimerIns,SIGNAL(clicked()),this,SLOT(supprimerInscription()));
    QObject::connect(enregistrer,SIGNAL(clicked()),this,SLOT(sauvegarder()));
    QObject::connect(Profil,SIGNAL(clicked()),this,SLOT(afficherProfil()));

    layout = new QGridLayout;
    layout->addWidget(cursusLabel, 0, 0,Qt::AlignHCenter);
    layout->addWidget(Profil,0,2);
    layout->addWidget(cursus, 0, 1,Qt::AlignLeft);
    layout->addWidget(dossier, 1, 0,1,3);
    layout->addWidget(ajouterIns, 2, 0);
    layout->addWidget(supprimerIns, 2, 1);
    layout->addWidget(enregistrer, 2, 2);
    setLayout(layout);
}

void DossierEditeur::initialiserDossier()
{
    for(int i = 0; i < FormationManager::getInstance().getTaille(); i++)
        cursus->addItem(FormationManager::getInstance().getElement(i).getCode());
    dossier->setRowCount(Dossier::getInstance().getTaille());
    for(int i = 0; i < Dossier::getInstance().getTaille(); i++)
    {

        QTableWidgetItem *monItem = new QTableWidgetItem(Dossier::getInstance().getElement(i).getUV().getCode());
        dossier->setItem(i,0,monItem);
        monItem = new QTableWidgetItem(Dossier::getInstance().getElement(i).getSemestre().FormeContracte());
        dossier->setItem(i,1,monItem);
        monItem = new QTableWidgetItem(NoteToString(Dossier::getInstance().getElement(i).getResultat()));
        dossier->setItem(i,2,monItem);
        monItem = new QTableWidgetItem(Dossier::getInstance().getElement(i).getCursus());
        dossier->setItem(i,3,monItem);

    }
}

void DossierEditeur::ajouterInscription()
{
    try
    {
        QDialog* window = new QDialog(this);
        QGridLayout* lay = new QGridLayout;
        QPushButton* ok = new QPushButton("Ok");
        QComboBox *ListeUV= new QComboBox(this);
        QComboBox *ListeCursus= new QComboBox(this);
        QComboBox *ListeResultat= new QComboBox(this);
        QComboBox *ListeSaison= new QComboBox(this);
        QLineEdit *Annee= new QLineEdit(this);
        QLabel* UVLabel= new QLabel("UV : ",this);
        QLabel* cursusLabel= new QLabel("Cursus : ",this);
        QLabel* resultatLabel= new QLabel("Note : ",this);
        QLabel* saisonLabel= new QLabel("Saison : ",this);
        QLabel* anneeLabel = new QLabel("Année : ",this);
        window->setFixedSize(300, 400);

        UV** uvs = UVManager::getInstance().getUVs();
        for(unsigned int i=0;i<UVManager::getInstance().getNbUV(); i++)
        {
            ListeUV->addItem(uvs[i]->getCode());
        }


        for(Note n = first; n <= last; n = Note(n+1))
            ListeResultat->addItem(NoteToString(n));

        for(int i = 0; i < FormationManager::getInstance().getTaille(); i++)
            ListeCursus->addItem(FormationManager::getInstance().getElement(i).getCode());
        ListeSaison->addItem("Automne");
        ListeSaison->addItem("Printemps");

        lay->addWidget(UVLabel,0,0);
        lay->addWidget(cursusLabel,1,0);
        lay->addWidget(resultatLabel,2,0);
        lay->addWidget(saisonLabel,3,0);
        lay->addWidget(anneeLabel,4,0);
        lay->addWidget(ListeUV,0,1);
        lay->addWidget(ListeCursus,1,1);
        lay->addWidget(ListeResultat,2,1);
        lay->addWidget(ListeSaison,3,1);
        lay->addWidget(Annee,4,1);
        lay->addWidget(ok,5,1,Qt::AlignHCenter);

        window->setLayout(lay);

        connect(ok,SIGNAL(clicked()),window,SLOT(accept()));
        window->exec();

        if(window->result())
        {
            if(Annee->text().isEmpty())
                throw UTProfilerException("Ne laissez pas l'année vide !");

            UV& uv = UVManager::getInstance().getUV(ListeUV->currentText());
            Semestre s(StringToSaison(ListeSaison->currentText()),Annee->text().toUInt());
            Dossier::getInstance().ajouterInscription(uv,StringToNote(ListeResultat->currentText()),s,ListeCursus->currentText());
            QMessageBox::information(this,"Ajout d'une inscription", QString("Ajout de la catégorie ")+ListeUV->currentText()+" réussie.");
            dossier->setRowCount(Dossier::getInstance().getTaille());

            QTableWidgetItem *monItem = new QTableWidgetItem(ListeUV->currentText());
            dossier->setItem(Dossier::getInstance().getTaille() -1,0,monItem);

            monItem = new QTableWidgetItem(s.FormeContracte());
            dossier->setItem(Dossier::getInstance().getTaille() -1,1,monItem);

            monItem = new QTableWidgetItem(ListeResultat->currentText());
            dossier->setItem(Dossier::getInstance().getTaille() -1,2,monItem);

            monItem = new QTableWidgetItem(ListeCursus->currentText());
            dossier->setItem(Dossier::getInstance().getTaille() -1,3,monItem);
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Ajout d'inscription", e.getInfo());
    }
}


void DossierEditeur::supprimerInscription()
{
    try
    {
        QTableWidgetItem* ItemSupp = dossier->item(dossier->currentRow(),0);
        if(ItemSupp==NULL || !ItemSupp->isSelected())
            throw UTProfilerException("Sélectionner une inscription !");
        QString c = ItemSupp->text();

        //Demande à l'utilisateur s'il es sûr de son choix
        int reponse = QMessageBox::question(this,"Suppression de " + c, "Voulez vous vraiment supprimer cette inscription ?", QMessageBox::Yes | QMessageBox::No);
        if(reponse == QMessageBox::Yes) //Vérifie si l'utilisateur a choisi oui
        {
            Inscription i = Dossier::getInstance().getInscription(c);
            Dossier::getInstance().supprimerInscription(i);
            dossier->clearContents();
            dossier->setRowCount(Dossier::getInstance().getTaille());
            initialiserDossier();
            //InitialisationCat();
            QMessageBox::information(this,"Suppression d'inscription","Inscription supprimée");
        }
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this,"Suppression d'inscription",e.getInfo());
    }
}

void DossierEditeur::sauvegarder()
{
    try
    {
        Dossier::getInstance().setCursus(cursus->currentText());
        if(Dossier::getInstance().isEmpty())
        {
            QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "XML(*.xml)");
            if(!fichier.contains(".xml"))
                fichier += ".xml";
            Dossier::getInstance().ChoisirFichier(fichier);
        }
        Dossier::getInstance().save(Dossier::getInstance().getFile());
        QMessageBox::information(this,"Sauvegarde","Dossier sauvegardé avec succès.");
    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this,"Sauvegarde",e.getInfo());
    }
}

void DossierEditeur::afficherProfil()
{
    try
    {
        QDialog* window = new QDialog(this);
        QGridLayout* lay = new QGridLayout;
        QPushButton* ok = new QPushButton("Ok");
        window->setWindowTitle("Profil");
        window->setFixedSize(400, 400);

        QStringList Formation = Dossier::getInstance().ListeCursus();
        int j = 1;
        QTableWidget* valide = new QTableWidget(1,1,this);
        QTableWidget* non_valide = new QTableWidget(1,1,this);
        QLabel* valideLabel = new QLabel("Validé :",this);
        QLabel* NonvalideLabel = new QLabel("A Valider :",this);
        valide->horizontalHeader()->hide();
        non_valide->horizontalHeader()->hide();
        valide->verticalHeader()->hide();
        non_valide->verticalHeader()->hide();
        valide->setMaximumSize(50,25);
        non_valide->setMaximumSize(50,25);

        QTableWidgetItem* ItemValide = new QTableWidgetItem("");
        ItemValide->setBackground(Qt::red);
        valide->setItem(0,0,ItemValide);

        QTableWidgetItem* ItemNonValide = new QTableWidgetItem("");
        ItemNonValide ->setBackground(Qt::gray);
        non_valide->setItem(0,0,ItemNonValide);
        //Tableaus affichant le nombre de crédits obtenu par catégorie
        for(QList<QString>::iterator it1 = Formation.begin(); it1 < Formation.end(); ++it1)
        {
            QMap<QString, unsigned int> ListeProfil = Dossier::getInstance().ListeProfil(*it1);
            QStringList P = ListeProfil.keys();
            QTableWidget* tab = new QTableWidget(1,ListeProfil.size(),this);
            tab->setHorizontalHeaderLabels(P);
            tab->setSelectionBehavior(QAbstractItemView::SelectRows);
            tab->verticalHeader()->hide();


            int i = 0;
            for(QList<QString>::iterator it2 = P.begin(); it2 < P.end(); ++it2)
            {
                QString cr; cr.setNum(ListeProfil[*it2]);
                QString creditFormation; creditFormation.setNum(FormationManager::getInstance().getFormation(*it1).getProfil(*it2));
                QString credit = cr +QString("(")+creditFormation+QString(")");
                QTableWidgetItem* monItem = new QTableWidgetItem(credit);
                if(FormationManager::getInstance().isFinished(*it1,*it2,ListeProfil[*it2]))
                    monItem->setBackground(Qt::red);
                else
                    monItem->setBackground(Qt::gray);
                tab->setItem(0,i,monItem);
                i++;
            }
            QLabel* form = new QLabel(*it1,this);
            lay->addWidget(form,j,0,1,3,Qt::AlignLeft);
            lay->addWidget(tab,j,1,1,3,Qt::AlignJustify);
            j++;
        }

        lay->addWidget(valideLabel,0,0);
        lay->addWidget(valide,0,1);
        lay->addWidget(NonvalideLabel,0,2);
        lay->addWidget(non_valide,0,3);
        lay->addWidget(ok,j,1,Qt::AlignHCenter);
        window->setLayout(lay);

        connect(ok,SIGNAL(clicked()),window,SLOT(accept()));
        window->exec();

        if(window->result())
        {

        }

    }
    catch(UTProfilerException& e)
    {
        QMessageBox::warning(this, "Ajout d'inscription", e.getInfo());
    }
}
