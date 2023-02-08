#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "animehandler.h"
#include "animecompletedmodel.h"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    qmlRegisterType<AnimeCompletedModel> ("AnimeCompleted",1,0,"AnimeCompletedModel");
    QQmlApplicationEngine engine;
    qmlRegisterType<AnimeHandler>("Anime",1,0,"AnimeHandler");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
