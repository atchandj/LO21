#include "include_all.h"

#include <QFile>
#include <QXmlStreamReader>


void CategorieManager::load(const QString& f){
    if (file!=f) this->~CategorieManager();
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
            // If it's named categories, we'll go to the next.
            if(xml.name() == "categories") continue;
            // If it's named categorie, we'll dig the information from there.
            if(xml.name() == "categorie") {
                QString cat;

                xml.readNext();
                cat= xml.text().toString();
                xml.readNext();

                ajouterCategorie(cat);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier Categorie, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
}

//Sauvegarde dans un fichier
void CategorieManager::save(const QString& f){
    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("categories");
     for(int i=0; i<code.size(); i++){
         stream.writeTextElement("categorie",code[i]->CategorieToString());
     }
     stream.writeEndElement();
     stream.writeEndDocument();

     newfile.close();

}

//Destructeur
CategorieManager::~CategorieManager(){
    if (file!="") save(file);
    for(int i =0; i <code.size(); i++)
        delete code[i];
}

//Ajoute une catégorie
void CategorieManager::ajouterCategorie(const QString& c){
    if (trouverCategorie(c)) {
        throw UTProfilerException(QString("Erreur CategorieManager : Catégorie ")+c+QString("déja existante"));
    }else{
        Categorie* newcat=new Categorie(c);
        code.append(newcat);
    }
}

//Trouve une catégorie de la liste
Categorie* CategorieManager::trouverCategorie(const QString& c){
    for(int i=0; i < code.size(); i++)
        if(c == code[i]->CategorieToString()) return code[i];
    return 0;
}

Categorie& CategorieManager::getCategorie(const QString& code){
    Categorie* cat= (trouverCategorie(code));
    if (!cat) throw UTProfilerException("Erreur CategorieManager : Catégorie inexistante",__FILE__,__LINE__);
    return *cat;
}


const Categorie& CategorieManager::getCategorie(const QString& code)const{
    return const_cast<CategorieManager*>(this)->getCategorie(code);
        // on peut aussi dupliquer le code de la méthode non-const
}

CategorieManager::Handler CategorieManager::handler = Handler();

CategorieManager& CategorieManager::getInstance(){
    if (!handler.instance) handler.instance = new CategorieManager; /* instance créée une seule fois lors de la première utilisation*/
    return *handler.instance;
}

void CategorieManager::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

void CategorieManager::supprimerCategorie(const QString& f)
{
    int i =0;
    while(code[i]->CategorieToString() != f && i < code.size())
        i++;
    if(i >= code.size())
        throw UTProfilerException("Erreur ! Cette catégorie n'existe pas !");
    code.removeAt(i);
}

//Modifie une catégorie
void CategorieManager::modifierCategorie(const QString& f,const QString& NewValue)
{
    Categorie* cat = trouverCategorie(f); //Cherche catégorie à modifier
    if(!cat) throw UTProfilerException("Erreur CategorieManager : Catégorie inexistante",__FILE__,__LINE__);
    cat->StringToCategorie(NewValue); //On la modifie
}
