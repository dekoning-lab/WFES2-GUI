#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <controllers/outputController.h>
#include <controllers/inputController.h>
#include <results/results.h>
#include <config/config.h>

#include "thread/threadwfessingle.h"

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Universal");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    app.setOrganizationName("University of Calgary");
    app.setOrganizationDomain("www.ucalgary.ca");

    //qmlRegisterType<wfes::controllers::OutputController>("WFES", 1, 0, "OutputController");
    //qmlRegisterType<wfes::controllers::InputController>("WFES", 1, 0, "InputController");
    //qmlRegisterType<WorkerThread>("WFES", 1, 0, "WorkerThread");

    //wfes::controllers::OutputController outputController;
    //wfes::controllers::InputController inputController;
    WorkerThread workerThread;

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    //engine.rootContext()->setContextProperty("outputController", &outputController);
    //engine.rootContext()->setContextProperty("inputController", &inputController);
    //engine.rootContext()->setContextProperty("workerThread", &workerThread);

    const QUrl url(QStringLiteral("qrc:/views/mainview/MainView.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
