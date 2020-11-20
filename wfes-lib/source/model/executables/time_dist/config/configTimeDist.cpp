#include "configTimeDist.h"

using namespace wfes::config;

int ConfigTimeDist::ModelTypeTimeDistToInt(ModelTypeTimeDist modelType) {
    switch(modelType){
        case ModelTypeTimeDist::TIME_DIST:
            return 1;
        case ModelTypeTimeDist::TIME_DIST_SGV:
            return 2;
        case ModelTypeTimeDist::TIME_DIST_SKIP:
            return 3;
        case ModelTypeTimeDist::TIME_DIST_DUAL:
            return 4;
        case ModelTypeTimeDist::NONE:
        default:
            return 0;
    }
}

void ConfigTimeDist::saveConfigTimeDist() {
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/");
    QDir dir;

    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Time_Dist.cfg"));

    file.open(QIODevice::WriteOnly);

    QTextStream outStream(&file);

    outStream << "Library: " << QString::fromStdString(ConfigTimeDist::library) << "\n";
    outStream << "Model Type: " << QString::fromStdString(ModelTypeTimeDistNames[ModelTypeTimeDistToInt(ConfigTimeDist::modelType)]) << "\n";
    outStream << "Population Size (N): " << ConfigTimeDist::population_size << "\n";
    outStream << "Selection Coefficient (s): " << ConfigTimeDist::s << "\n";
    outStream << "Dominance Coefficient (h): " << ConfigTimeDist::h << "\n";
    outStream << "Backward Mutation Rate (u): " << ConfigTimeDist::u << "\n";
    outStream << "Forward Mutation Rate (v): " << ConfigTimeDist::v << "\n";
    outStream << "No Recurrent Mutation (m): " << (ConfigTimeDist::no_rem ? QString("true") : QString("false")) << "\n";
    outStream << "Tail Truncation Weight (a): " << ConfigTimeDist::a << "\n";
    outStream << "Block Size (b): " << ConfigTimeDist::b << "\n";
    outStream << "Max. Number of Generations (m): " << ConfigTimeDist::max_t << "\n";
    outStream << "Number of Threads (t): " << ConfigTimeDist::n_threads << "\n";
    outStream << "Integration Cutoff (c): " << ConfigTimeDist::integration_cutoff << "\n";

    outStream << "Initial Distribution Path (I): " << QString::fromStdString(ConfigTimeDist::initial_distribution_csv) << "\n";
    outStream << "Output Q: " << (ConfigTimeDist::output_Q ? QString("true") : QString("false")) << "\n";
    outStream << "Output R: " << (ConfigTimeDist::output_R ? QString("true") : QString("false")) << "\n";
    outStream << "Output P: " << (ConfigTimeDist::output_P ? QString("true") : QString("false")) << "\n";

    file.close();
}

void ConfigTimeDist::loadConfigTimeDist() {
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/" + "Time_Dist.cfg");

    QFile file(outputPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        processLine(line);
    }
}

void ConfigTimeDist::processLine(QString line) {
    QStringList splitted = line.split(": ");
    if(splitted.at(0).compare("Library") == 0) {
        ConfigTimeDist::library = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Model Type") == 0) {
        if(splitted.at(1) == "None")
            ConfigTimeDist::modelType = ModelTypeTimeDist::NONE;
        else if(splitted.at(1) == "Time Dist.")
            ConfigTimeDist::modelType = ModelTypeTimeDist::TIME_DIST;
        else if(splitted.at(1) == "Time Dist. SGV")
            ConfigTimeDist::modelType = ModelTypeTimeDist::TIME_DIST_SGV;
        else if(splitted.at(1) == "Time Dist. Skip")
            ConfigTimeDist::modelType = ModelTypeTimeDist::TIME_DIST_SKIP;
        else if(splitted.at(1) == "Time Dist. Dual")
            ConfigTimeDist::modelType = ModelTypeTimeDist::TIME_DIST_DUAL;
    } else if(splitted.at(0).compare("Population Size (N)") == 0) {
        ConfigTimeDist::population_size = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Selection Coefficient (s)") == 0) {
        ConfigTimeDist::s = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Dominance Coefficient (h)") == 0) {
        ConfigTimeDist::h = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Backward Mutation Rate (u)") == 0) {
        ConfigTimeDist::u = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Forward Mutation Rate (v)") == 0) {
        ConfigTimeDist::v = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("No Recurrent Mutation (m)") == 0) {
        ConfigTimeDist::no_rem = splitted.at(1).compare("true") == 0 ? true : false;
        ConfigTimeDist::rem = !no_rem;
    } else if(splitted.at(0).compare("Tail Truncation Weight (a)") == 0) {
        ConfigTimeDist::a = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Block Size (b)") == 0) {
        ConfigTimeDist::b = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Max. Number of Generations (m)") == 0) {
        ConfigTimeDist::max_t = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Number of Threads (t)") == 0) {
        ConfigTimeDist::n_threads = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Integration Cutoff (c)") == 0) {
        ConfigTimeDist::integration_cutoff = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Initial Distribution Path (I)") == 0) {
        ConfigTimeDist::initial_distribution_csv = splitted.at(1).toStdString();
    }  else if(splitted.at(0).compare("Output I") == 0) {
        ConfigTimeDist::output_I = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output Q") == 0) {
        ConfigTimeDist::output_Q = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output R") == 0) {
        ConfigTimeDist::output_R = splitted.at(1).compare("true") == 0 ? true : false;
    }  else if(splitted.at(0).compare("Output P") == 0) {
        ConfigTimeDist::output_P = splitted.at(1).compare("true") == 0 ? true : false;
    }
}


////////////////////////////////
// Static initializations here//
////////////////////////////////

ModelTypeTimeDist ConfigTimeDist::modelType = ModelTypeTimeDist::TIME_DIST;
std::string ConfigTimeDist::library = "Pardiso";
std::string ConfigTimeDist::vienna_solver = "BicGStab";
int ConfigTimeDist::population_size = 100;
double ConfigTimeDist::s = 0;
double ConfigTimeDist::h = 0.5;
double ConfigTimeDist::u = 1e-9;
double ConfigTimeDist::v = 1e-9;
bool ConfigTimeDist::no_rem = false;
bool ConfigTimeDist::rem = !ConfigTimeDist::no_rem;
double ConfigTimeDist::a = 1e-20;
int ConfigTimeDist::b = 100;
int ConfigTimeDist::max_t = 100;

int ConfigTimeDist::n_threads = 1;
double ConfigTimeDist::integration_cutoff = 1-1e-8;

std::string ConfigTimeDist::initial_distribution_csv = "";
std::string ConfigTimeDist::path_output_P = "output_P.csv";
std::string ConfigTimeDist::path_output_Q = "output_Q.csv";
std::string ConfigTimeDist::path_output_R = "output_R.csv";

bool ConfigTimeDist::output_P = true;
bool ConfigTimeDist::output_Q = false;
bool ConfigTimeDist::output_R = false;
bool ConfigTimeDist::output_I = false;
