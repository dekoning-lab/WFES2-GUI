#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <source/model/executables/wfes_single/controllers/outputControllerWfesSingle.h>
#include <source/model/executables/wfes_single/controllers/inputControllerWfesSingle.h>
#include <source/model/executables/wfes_single/config/configWfesSingle.h>
#include <model/executables/time_dist/controllers/inputControllerTimeDist.h>

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Universal");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    app.setOrganizationName("University of Calgary");
    app.setOrganizationDomain("www.ucalgary.ca");

    qmlRegisterType<wfes::controllers::OutputControllerWfesSingle>("WFES", 1, 0, "OutputControllerWfesSingle");
    qmlRegisterType<wfes::controllers::InputControllerWfesSingle>("WFES", 1, 0, "InputControllerWfesSingle");
    qmlRegisterType<wfes::controllers::InputControllerTimeDist>("WFES", 1, 0, "InputControllerTimeDist");

    wfes::controllers::OutputControllerWfesSingle outputControllerWfesSingle;
    wfes::controllers::InputControllerWfesSingle inputControllerWfesSingle;

    wfes::controllers::InputControllerTimeDist inputControllerTimeDist;

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    engine.rootContext()->setContextProperty("outputControllerWfesSingle", &outputControllerWfesSingle);
    engine.rootContext()->setContextProperty("inputControllerWfesSingle", &inputControllerWfesSingle);

    engine.rootContext()->setContextProperty("inputControllerTimeDist", &inputControllerTimeDist);

    const QUrl url(QStringLiteral("qrc:/views/mainview/MainView.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
