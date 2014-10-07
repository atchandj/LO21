#include "include_all.h"

#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>

Dossier::Dossier():file(""),cursus(""){}

void Dossier::ChoisirFichier(const QString& f)
{
    if(file == "")
        file = f;
}

void Dossier::load(const QString& f){
    if(file!=f) this->~Dossier();
        file=f;

    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UTProfilerException("Erreur ouverture fichier Dossier");
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
            // If it's named dossier, we'll go to the next.
            if(xml.name() == "dossier") continue;
            // If it's named dossier, we'll dig the information from there.
            if(xml.name() == "cursus"){
                xml.readNext(); cursus = xml.text().toString(); xml.readNext();
                xml.readNext();
            }
            if(xml.name() == "inscription") {
                QString code;
                QString cursusInscrip;
                Note note;
                Saison saison;
                unsigned int annee;
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named inscription.


                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "inscription")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found code.
                        if(xml.name() == "code") {
                            xml.readNext(); code=xml.text().toString();
                        }
                        if(xml.name() == "note") {
                            xml.readNext(); note = StringToNote(xml.text().toString());
                        }
                        if(xml.name() == "saison") {
                            xml.readNext(); saison = StringToSaison(xml.text().toString());
                        }
                        if(xml.name() == "annee") {
                            xml.readNext(); annee = xml.text().toString().toUInt();
                        }
                        if(xml.name() == "cursusInscription") {
                            xml.readNext(); cursusInscrip = xml.text().toString();
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                Semestre semestre(saison,annee);
                UV* uv = &UVManager::getInstance().getUV(code);
                ajouterInscription(*uv,note,semestre,cursusInscrip);

            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw UTProfilerException(QString("Erreur lecteur fichier ")+file+QString(", parser xml"));
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
}


Dossier::~Dossier(){
    if (file!="") save(file);
    for(int i =0; i <inscriptions.size(); i++)
        delete inscriptions[i];
}

void Dossier::save(const QString& f)
{
    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("Dossier");
     stream.writeTextElement("cursus",cursus);
     for(int i=0; i<inscriptions.size(); i++){
         stream.writeStartElement("inscription");
         stream.writeTextElement("code",inscriptions[i]->getUV().getCode());
         stream.writeTextElement("note",NoteToString(inscriptions[i]->getResultat()));
         stream.writeTextElement("saison",SaisonToString(inscriptions[i]->getSemestre().getSaison()));
         QString cr; cr.setNum(inscriptions[i]->getSemestre().getAnnee());
         stream.writeTextElement("annee",cr);
         stream.writeTextElement("cursusInscription",inscriptions[i]->getCursus());
         stream.writeEndElement();
     }
     stream.writeEndElement();
     stream.writeEndDocument();

     newfile.close();
}

//Ajoute une catégorie
void Dossier::ajouterInscription(UV& uv, Note n, Semestre& s, const QString& c){
    if (trouverInscription(uv.getCode())) {
        throw UTProfilerException(QString("Erreur Dossier : Inscription ")+uv.getCode()+QString(" avec une note différente de F/FX ")+QString(" déja existante"));
    }else{
        Inscription* newIns=new Inscription(uv,s,c,n);
        inscriptions.append(newIns);
    }
}

//Trouve une catégorie de la liste
Inscription* Dossier::trouverInscription(const QString& c)/*const*/{
    for(int i=0; i < inscriptions.size(); i++)
        if(c == inscriptions[i]->getUV().getCode()&& (inscriptions[i]->getResultat() != F || inscriptions[i]->getResultat() != FX) ) return inscriptions[i];
    return 0;
}

Inscription& Dossier::getInscription(const QString& code){
    Inscription* cat= (trouverInscription(code));
    if (!cat) throw UTProfilerException("Erreur Dossier: Inscription inexistante",__FILE__,__LINE__);
    return *cat;
}


const Inscription& Dossier::getInscription(const QString& code)const{
    return const_cast<Dossier*>(this)->getInscription(code);
        // on peut aussi dupliquer le code de la méthode non-const
}

Dossier::Handler Dossier::handler = Handler();

Dossier& Dossier::getInstance(){
    if (!handler.instance) handler.instance = new Dossier; /* instance créée une seule fois lors de la première utilisation*/
    return *handler.instance;
}

void Dossier::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

void Dossier::supprimerInscription(const Inscription& i)
{
    int j =0;
    while(inscriptions[j]->getUV() != i.getUV() && inscriptions[j]->getSemestre() != i.getSemestre() && j < inscriptions.size())
        j++;
    if(j >= inscriptions.size())
        throw UTProfilerException("Erreur ! Cette inscription n'existe pas !");
    inscriptions.removeAt(j);
}

bool Dossier::isEmpty()
{
    if(file == "")
        return true;
    return false;
}

QMap<QString, unsigned int> Dossier::ListeProfil(const QString& c)
{
    QMap<QString, unsigned int> Profil;
    Formation& f = FormationManager::getInstance().getFormation(c);
    QStringList P = f.ListeProfil();
    for(int i =0; i < P.size(); i++)
        Profil[P[i]]= 0;
    for(int i = 0; i < inscriptions.size(); i++)
    {
        QString cat = inscriptions[i]->getUV().getCategorie().CategorieToString();
        if(inscriptions[i]->getCursus() == c && P.contains(cat) && inscriptions[i]->getResultat() != EC && inscriptions[i]->getResultat() != F && inscriptions[i]->getResultat() != FX && inscriptions[i]->getResultat() != RES && inscriptions[i]->getResultat() != ABS ) //Selectionne UV seulement du cursus courant
            Profil[cat] += inscriptions[i]->getUV().getNbCredits();
    }
    return Profil;
}

QStringList Dossier::ListeCursus()
{
    QStringList Cursus;
    for(int i = 0; i < inscriptions.size(); i++)
    {
        if(!Cursus.contains(inscriptions[i]->getCursus()))
            Cursus.append(inscriptions[i]->getCursus());
    }
    return Cursus;
}
