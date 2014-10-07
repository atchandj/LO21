#include "include_all.h"

#include <QFile>
#include <QXmlStreamReader>
#include<QTextStream>


//Sauvegarde dans un fichier
void FormationManager::save(const QString& f){
    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("Formations");
     for(int i=0; i<liste.size(); i++){
         stream.writeStartElement("Formation");
         stream.writeTextElement("code",liste[i]->getCode());
         QList<QString> Profil = liste[i]->ListeProfil();
         for(QList<QString>::Iterator it = Profil.begin(); it < Profil.end(); it++)
         {
             stream.writeStartElement("categorie");
             stream.writeTextElement("codeCat",*it);
             QString cr; cr.setNum(liste[i]->getProfil(*it));
             stream.writeTextElement("creditCat",cr);
             stream.writeEndElement();
         }
         QList<QString> Filiere = liste[i]->ListeFiliere();
         for(QList<QString>::Iterator it = Filiere.begin(); it < Filiere.end(); it++)
         {
             stream.writeStartElement("Filiere");
             stream.writeTextElement("code",*it);
             QString cr; cr.setNum(liste[i]->getFiliere(*it));
             stream.writeTextElement("credit",cr);
             stream.writeEndElement();
         }
         stream.writeEndElement();

     }
     stream.writeEndElement();
     stream.writeEndDocument();

     newfile.close();
}

void FormationManager::load(const QString& f){
    if (file!=f)
        this->~FormationManager();
    file=f;

    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UTProfilerException("Erreur ouverture fichier UV");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named Formations, we'll go to the next.
            if(xml.name() == "Formations") continue;
            // If it's named Formation, we'll dig the information from there.
            if(xml.name() == "Formation") {
                QString code;
                QString cat;
                unsigned int nbCreditsCat;
                QString fil;
                unsigned int nbCreditsFil;
                QMap<QString, unsigned int> Filiere;
                QMap<QString, unsigned int> Categorie;
                xml.readNext();

                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Formation")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        //Chargement du code de la formation
                        if(xml.name() == "code") {
                            xml.readNext(); code=xml.text().toString();
                        }

                        //Chargement des catégories
                        if(xml.name() == "categorie") {
                            xml.readNext();
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "categorie")){
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if(xml.name() == "codeCat") {
                                        xml.readNext(); cat=xml.text().toString();
                                    }
                                    if(xml.name() == "creditCat") {
                                        xml.readNext(); nbCreditsCat=xml.text().toString().toUInt();
                                     }

                                  }
                                xml.readNext();
                            }

                            Categorie[cat] = nbCreditsCat;
                        }
                        //Chargement des filières
                        if(xml.name() == "Filiere") {
                            xml.readNext();
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Filiere")){
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if(xml.name() == "code") {
                                        xml.readNext(); fil=xml.text().toString();
                                    }
                                    if(xml.name() == "credit") {
                                        xml.readNext(); nbCreditsFil=xml.text().toString().toUInt();
                                     }

                                  }
                                xml.readNext();
                            }

                            Filiere[fil] = nbCreditsFil;
                        }
                    }
                    xml.readNext();
                }
                ajouterFormation(code,Categorie,Filiere);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier formation, parser xml");
   }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
}

//Sauvegarde dans un fichier

////Destructeur
FormationManager::~FormationManager(){
    if (file!="") save(file);
    for(int i =0; i <liste.size(); i++)
        delete liste[i];
}

////Ajoute une catégorie
void FormationManager::ajouterFormation(const QString& c,QMap<QString, unsigned int> P,QMap<QString, unsigned int> F){
    if (trouverFormation(c)) {
        throw UTProfilerException(QString("Erreur FormationManager : Formation ")+c+QString("déja existante"));
    }else{
        Formation* newcat=new Formation(c,P,F);
        liste.append(newcat);
    }
}

//Trouve une catégorie de la liste

Formation* FormationManager::trouverFormation(const QString& c){
    for(int i=0; i < liste.size(); i++)
        if(c == liste[i]->getCode()) return liste[i];
    return 0;
}

Formation& FormationManager::getFormation(const QString& code){
    Formation* form= (trouverFormation(code));
    if (!form) throw UTProfilerException("Erreur FormationManager : Formation inexistante",__FILE__,__LINE__);
    return *form;
}


const Formation& FormationManager::getFormation(const QString& code)const{
    return const_cast<FormationManager*>(this)->getFormation(code);
        // on peut aussi dupliquer le code de la méthode non-const
}

FormationManager::Handler FormationManager::handler = Handler();


FormationManager& FormationManager::getInstance(){
    if (!handler.instance) handler.instance = new FormationManager; /* instance créée une seule fois lors de la première utilisation*/
    return *handler.instance;
}

void FormationManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

void FormationManager::supprimerFormation(const QString& f)
{
    int i =0;
    while(i < liste.size() && liste[i]->getCode() != f)
        i++;
    if(i >= liste.size())
        throw UTProfilerException("Erreur ! Cette formation n'existe pas !");
    liste.removeAt(i);
}

bool FormationManager::isFinished(const QString& formation,const QString cat, unsigned int nbc)
{
    Formation* form= (trouverFormation(formation));
    if (!form) throw UTProfilerException("Erreur FormationManager : Formation inexistante",__FILE__,__LINE__);
    return (nbc >= form->getProfil(cat));
}
