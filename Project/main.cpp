#include "include_all.h"

#include <QApplication>
#include <QtGui>


int main(int argc,char* argv[])
{
    QApplication app(argc, argv);
    Profiler profiler;

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    profiler.show();
    return app.exec();

}

