#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <controllers/outputController.h>
#include <controllers/inputController.h>
#include <results/results.h>
#include <config/config.h>

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Universal");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<wfes::controllers::OutputController>("WFES", 1, 0, "OutputController");
    qmlRegisterType<wfes::controllers::InputController>("WFES", 1, 0, "InputController");

    wfes::controllers::OutputController outputController;
    wfes::controllers::InputController inputController;
    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    engine.rootContext()->setContextProperty("outputController", &outputController);
    engine.rootContext()->setContextProperty("inputController", &inputController);

    const QUrl url(QStringLiteral("qrc:/views/mainview/MainView.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
