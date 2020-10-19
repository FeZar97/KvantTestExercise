#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "kvanttablemodel.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("Kvant");
    app.setOrganizationName("Kvant.com");
    app.setApplicationName("KvantTestExercise");
    QQmlApplicationEngine engine;

    KvantTableModel kvantTableModel;
    qmlRegisterType<KvantTableModel>("KvantTableModel", 0, 1, "KvantTableModel");

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("kvantTableModel", &kvantTableModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    &app, [url](QObject * obj, const QUrl & objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
