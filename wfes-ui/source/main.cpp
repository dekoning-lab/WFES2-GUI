#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <csignal>

#include <source/model/executables/wfes_single/controllers/outputControllerWfesSingle.h>
#include <source/model/executables/wfes_single/controllers/inputControllerWfesSingle.h>
#include <source/model/executables/wfes_single/config/configWfesSingle.h>
#include <source/model/executables/time_dist/controllers/inputControllerTimeDist.h>
#include <source/model/executables/time_dist/controllers/outputControllerTimeDist.h>
#include <model/executables/wfes_sweep/controllers/inputControllerWfesSweep.h>
#include <model/executables/wfes_sweep/controllers/outputControllerWfesSweep.h>
#include <model/executables/phase_type/controllers/inputControllerPhaseType.h>
#include <model/executables/phase_type/controllers/outputControllerPhaseType.h>
#include <model/executables/wfafd/controllers/inputControllerWfafd.h>
#include <model/executables/wfafd/controllers/outputControllerWfafd.h>
#include <model/executables/wfas/controllers/inputControllerWfas.h>
#include <model/executables/wfas/controllers/outputControllerWfas.h>
#include <model/executables/wfes_sequential/controllers/inputControllerWfesSequential.h>
#include <model/executables/wfes_sequential/controllers/outputControllerWfesSequential.h>
#include <model/executables/wfes_switching/controllers/inputControllerWfesSwitching.h>
#include <model/executables/wfes_switching/controllers/outputControllerWfesSwitching.h>
#include <model/visualization/imageOutputController.h>
#include <model/visualization/visualizationImageProvider.h>
#include <model/visualization/charts/chartResults.h>
#include <model/config/globalConfiguration.h>
#include <model/config/systemoperations.h>

void signalHandler( int signum ) {
   std::cout << "Interrupt signal (" << signum << ") received.\n";

   exit(signum);
}

int main(int argc, char *argv[]) {
    std::set_terminate([](){ std::cout << "Unhandled exception" << std::endl; std::abort();});
    signal(SIGINT, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGFPE, signalHandler);
    signal(SIGILL, signalHandler);
    signal(SIGSEGV, signalHandler);
    signal(SIGTERM, signalHandler);

    QQuickStyle::setStyle("Universal");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    app.setOrganizationName("University of Calgary");
    app.setOrganizationDomain("www.ucalgary.ca");

    // Load global configuration.
    wfes::controllers::GlobalConfiguration::loadGlobalConfiguration();

    qmlRegisterType<wfes::controllers::OutputControllerWfesSingle>("WFES", 1, 0, "OutputControllerWfesSingle");
    qmlRegisterType<wfes::controllers::InputControllerWfesSingle>("WFES", 1, 0, "InputControllerWfesSingle");
    qmlRegisterType<wfes::controllers::OutputControllerTimeDist>("WFES", 1, 0, "OutputControllerTimeDist");
    qmlRegisterType<wfes::controllers::InputControllerTimeDist>("WFES", 1, 0, "InputControllerTimeDist");
    qmlRegisterType<wfes::controllers::OutputControllerWfesSweep>("WFES", 1, 0, "OutputControllerWfesSweep");
    qmlRegisterType<wfes::controllers::InputControllerWfesSweep>("WFES", 1, 0, "InputControllerWfesSweep");
    qmlRegisterType<wfes::controllers::OutputControllerPhaseType>("WFES", 1, 0, "OutputControllerPhaseType");
    qmlRegisterType<wfes::controllers::InputControllerPhaseType>("WFES", 1, 0, "InputControllerPhaseType");
    qmlRegisterType<wfes::controllers::OutputControllerWfafd>("WFES", 1, 0, "OutputControllerWfafd");
    qmlRegisterType<wfes::controllers::InputControllerWfafd>("WFES", 1, 0, "InputControllerWfafd");
    qmlRegisterType<wfes::controllers::OutputControllerWfas>("WFES", 1, 0, "OutputControllerWfas");
    qmlRegisterType<wfes::controllers::InputControllerWfas>("WFES", 1, 0, "InputControllerWfas");
    qmlRegisterType<wfes::controllers::OutputControllerWfesSequential>("WFES", 1, 0, "OutputControllerWfesSequential");
    qmlRegisterType<wfes::controllers::InputControllerWfesSequential>("WFES", 1, 0, "InputControllerWfesSequential");
    qmlRegisterType<wfes::controllers::OutputControllerWfesSwitching>("WFES", 1, 0, "OutputControllerWfesSwitching");
    qmlRegisterType<wfes::controllers::InputControllerWfesSwitching>("WFES", 1, 0, "InputControllerWfesSwitching");
    qmlRegisterType<wfes::controllers::ImageOutputController>("WFES", 1, 0, "ImageOutputController");
    qmlRegisterType<wfes::controllers::ChartResults>("WFES", 1, 0, "ChartResults");
    qmlRegisterType<wfes::controllers::ChartResults>("WFES", 1, 0, "ChartResults");
    qmlRegisterType<wfes::controllers::GlobalConfiguration>("WFES", 1, 0, "GlobalConfiguration");
    qmlRegisterType<wfes::controllers::SystemOperations>("WFES", 1, 0, "SystemOperations");

    wfes::controllers::OutputControllerWfesSingle outputControllerWfesSingle;
    wfes::controllers::InputControllerWfesSingle inputControllerWfesSingle;
    wfes::controllers::OutputControllerTimeDist outputControllerTimeDist;
    wfes::controllers::InputControllerTimeDist inputControllerTimeDist;
    wfes::controllers::OutputControllerWfesSweep outputControllerWfesSweep;
    wfes::controllers::InputControllerWfesSweep inputControllerWfesSweep;
    wfes::controllers::OutputControllerPhaseType outputControllerPhaseType;
    wfes::controllers::InputControllerPhaseType inputControllerPhaseType;
    wfes::controllers::OutputControllerWfafd outputControllerWfafd;
    wfes::controllers::InputControllerWfafd inputControllerWfafd;
    wfes::controllers::OutputControllerWfas outputControllerWfas;
    wfes::controllers::InputControllerWfas inputControllerWfas;
    wfes::controllers::OutputControllerWfesSequential outputControllerWfesSequential;
    wfes::controllers::InputControllerWfesSequential inputControllerWfesSequential;
    wfes::controllers::OutputControllerWfesSwitching outputControllerWfesSwitching;
    wfes::controllers::InputControllerWfesSwitching inputControllerWfesSwitching;
    wfes::controllers::ImageOutputController imageOutputController;
    wfes::controllers::ChartResults chartResults;
    wfes::controllers::GlobalConfiguration globalConfiguration;
    wfes::controllers::SystemOperations systemOperations;

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    engine.addImageProvider(QLatin1String("visualizationImageProvider"), new VisualizationImageProvider());

    engine.rootContext()->setContextProperty("outputControllerWfesSingle", &outputControllerWfesSingle);
    engine.rootContext()->setContextProperty("inputControllerWfesSingle", &inputControllerWfesSingle);
    engine.rootContext()->setContextProperty("outputControllerTimeDist", &outputControllerTimeDist);
    engine.rootContext()->setContextProperty("inputControllerTimeDist", &inputControllerTimeDist);
    engine.rootContext()->setContextProperty("outputControllerWfesSweep", &outputControllerWfesSweep);
    engine.rootContext()->setContextProperty("inputControllerWfesSweep", &inputControllerWfesSweep);
    engine.rootContext()->setContextProperty("outputControllerPhaseType", &outputControllerPhaseType);
    engine.rootContext()->setContextProperty("inputControllerPhaseType", &inputControllerPhaseType);
    engine.rootContext()->setContextProperty("outputControllerWfafd", &outputControllerWfafd);
    engine.rootContext()->setContextProperty("inputControllerWfafd", &inputControllerWfafd);
    engine.rootContext()->setContextProperty("outputControllerWfas", &outputControllerWfas);
    engine.rootContext()->setContextProperty("inputControllerWfas", &inputControllerWfas);
    engine.rootContext()->setContextProperty("outputControllerWfesSequential", &outputControllerWfesSequential);
    engine.rootContext()->setContextProperty("inputControllerWfesSequential", &inputControllerWfesSequential);
    engine.rootContext()->setContextProperty("outputControllerWfesSwitching", &outputControllerWfesSwitching);
    engine.rootContext()->setContextProperty("inputControllerWfesSwitching", &inputControllerWfesSwitching);
    engine.rootContext()->setContextProperty("imageOutputController", &imageOutputController);
    engine.rootContext()->setContextProperty("chartResults", &chartResults);
    engine.rootContext()->setContextProperty("globalConfiguration", &globalConfiguration);
    engine.rootContext()->setContextProperty("systemOperations", &systemOperations);

    const QUrl url(QStringLiteral("qrc:/views/mainview/MainView.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

