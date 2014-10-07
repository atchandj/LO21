#ifndef UT_PROFILER_h
#define UT_PROFILER_h

#include <QString>
#include <QTextStream>
#include <QList>
using namespace std;


/*!
 * \brief Note d'une UV
 */
enum Note { A, B, C, D, E, F, FX, RES, ABS, /* en cours */ EC , first=A, last=EC};
/*!
 * \brief Saison
 */
enum Saison { Automne, Printemps };
/*!
 * \brief Surcharge de l'opérator << : Retourne le saison dans un flux
 * \param f : flux à retourner
 * \param s : saison dont veut retourner le flux
 * \return un flux
 */
inline QTextStream& operator<<(QTextStream& f, const Saison& s) { if (s==Automne) f<<"A"; else f<<"P"; return f;}

/*!
 * \brief Transforme une chaine de caractère en variable de type Saison
 * \param str : chaine dont on veut retourner la Saison
 * \return une Saison
 */
Saison StringToSaison(const QString& str);
/*!
 * \brief Transforme une variable de type Saison en QString
 * \param s : Saison dont on veut la chaine de caractères
 * \return un QString
 */
QString SaisonToString(const Saison s);
/*!
 * \brief Transforme une variable de type Note en QString
 * \param n : Note dont on veut la chaine de caractères
 * \return un QString
 */
QString NoteToString(const Note n);
/*!
 * \brief Transforme une chaine de caractère en variable de type Note
 * \param n : Chaine dont on veut retourner la note
 * \return une Note
 */
Note StringToNote(const QString& n);


#endif
