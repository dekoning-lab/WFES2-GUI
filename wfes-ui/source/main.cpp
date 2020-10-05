#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <source/model/executables/wfes_single/controllers/outputControllerWfesSingle.h>
#include <source/model/executables/wfes_single/controllers/inputControllerWfesSingle.h>
#include <model/executables/wfes_single/results/resultsWfesSingle.h>
#include <source/model/executables/wfes_single/config/configWfesSingle.h>

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Universal");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    app.setOrganizationName("University of Calgary");
    app.setOrganizationDomain("www.ucalgary.ca");

    qmlRegisterType<wfes::controllers::OutputController>("WFES", 1, 0, "OutputControllerWfesSingle");
    qmlRegisterType<wfes::controllers::InputController>("WFES", 1, 0, "InputControllerWfesSingle");

    wfes::controllers::OutputController outputController;
    wfes::controllers::InputController inputController;

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    engine.rootContext()->setContextProperty("outputControllerWfesSingle", &outputController);
    engine.rootContext()->setContextProperty("inputControllerWfesSingle", &inputController);

    const QUrl url(QStringLiteral("qrc:/views/mainview/MainView.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
