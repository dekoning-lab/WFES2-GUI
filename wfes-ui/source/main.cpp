#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <controllers/outputController.h>
#include <results/results.h>

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Universal");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<wfes::controllers::OutputController>("WFES", 1, 0, "OutputController");

    wfes::controllers::OutputController outputController;
    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    engine.rootContext()->setContextProperty("outputController", &outputController);

    const QUrl url(QStringLiteral("qrc:/views/mainview/MainView.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
