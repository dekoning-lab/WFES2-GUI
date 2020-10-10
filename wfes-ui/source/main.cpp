#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <source/model/executables/wfes_single/controllers/outputControllerWfesSingle.h>
#include <source/model/executables/wfes_single/controllers/inputControllerWfesSingle.h>
#include <source/model/executables/wfes_single/config/configWfesSingle.h>
#include <source/model/executables/time_dist/controllers/inputControllerTimeDist.h>
#include <source/model/executables/time_dist/controllers/outputControllerTimeDist.h>
#include <model/executables/wfes_sweep/controllers/inputControllerWfesSweep.h>
#include <model/executables/wfes_sweep/controllers/outputControllerWfesSweep.h>

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Universal");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    app.setOrganizationName("University of Calgary");
    app.setOrganizationDomain("www.ucalgary.ca");

    qmlRegisterType<wfes::controllers::OutputControllerWfesSingle>("WFES", 1, 0, "OutputControllerWfesSingle");
    qmlRegisterType<wfes::controllers::InputControllerWfesSingle>("WFES", 1, 0, "InputControllerWfesSingle");
    qmlRegisterType<wfes::controllers::OutputControllerTimeDist>("WFES", 1, 0, "OutputControllerTimeDist");
    qmlRegisterType<wfes::controllers::InputControllerTimeDist>("WFES", 1, 0, "InputControllerTimeDist");
    qmlRegisterType<wfes::controllers::OutputControllerWfesSweep>("WFES", 1, 0, "OutputControllerWfesSweep");
    qmlRegisterType<wfes::controllers::InputControllerWfesSweep>("WFES", 1, 0, "InputControllerWfesSweep");

    wfes::controllers::OutputControllerWfesSingle outputControllerWfesSingle;
    wfes::controllers::InputControllerWfesSingle inputControllerWfesSingle;
    wfes::controllers::OutputControllerTimeDist outputControllerTimeDist;
    wfes::controllers::InputControllerTimeDist inputControllerTimeDist;
    wfes::controllers::OutputControllerWfesSweep outputControllerWfesSweep;
    wfes::controllers::InputControllerWfesSweep inputControllerWfesSweep;

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    engine.rootContext()->setContextProperty("outputControllerWfesSingle", &outputControllerWfesSingle);
    engine.rootContext()->setContextProperty("inputControllerWfesSingle", &inputControllerWfesSingle);
    engine.rootContext()->setContextProperty("outputControllerTimeDist", &outputControllerTimeDist);
    engine.rootContext()->setContextProperty("inputControllerTimeDist", &inputControllerTimeDist);
    engine.rootContext()->setContextProperty("outputControllerWfesSweep", &outputControllerWfesSweep);
    engine.rootContext()->setContextProperty("inputControllerWfesSweep", &inputControllerWfesSweep);

    const QUrl url(QStringLiteral("qrc:/views/mainview/MainView.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
