#include "configPhaseType.h"

using namespace wfes::config;

ConfigPhaseType::ConfigPhaseType() {}

int ConfigPhaseType::ModelTypePhaseTypeToInt(enum ModelTypePhaseType modelType) {
    switch(modelType){
    case ModelTypePhaseType::PHASE_TYPE_DIST:
        return 1;
    case ModelTypePhaseType::PHASE_TYPE_MOMENTS:
        return 2;
    case ModelTypePhaseType::NONE:
    default:
        return 0;
    }
}

void ConfigPhaseType::saveConfigPhaseType()
{
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/");
    QDir dir;

    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Phase_Type.cfg"));
    file.open(QIODevice::WriteOnly);

    if(!file.isOpen()) {
        qDebug() << "The file is not open.";
    }

    QTextStream outStream(&file);

    outStream << "Library: " << QString::fromStdString(ConfigPhaseType::library) << "\n";
    outStream << "ViennaCL Solver: " << QString::fromStdString(ConfigPhaseType::vienna_solver) << "\n";
    outStream << "Model Type: " << QString::fromStdString(ModelTypePhaseTypeNames[ModelTypePhaseTypeToInt(ConfigPhaseType::modelType)]) << "\n";
    outStream << "Population Size (N): " << ConfigPhaseType::population_size << "\n";
    outStream << "Selection Coefficient (s): " << ConfigPhaseType::s << "\n";
    outStream << "Dominance Coefficient (h): " << ConfigPhaseType::h << "\n";
    outStream << "Backward Mutation Rate (u): " << ConfigPhaseType::u << "\n";
    outStream << "Forward Mutation Rate (v): " << ConfigPhaseType::v << "\n";
    outStream << "No Recurrent Mutation (m): " << (ConfigPhaseType::no_rem ? QString("true") : QString("false")) << "\n";
    outStream << "Tail Truncation Weight (a): " << ConfigPhaseType::a << "\n";
    outStream << "Odds Ratio (k): " << ConfigPhaseType::odds_ratio << "\n";
    outStream << "Block Size (b): " << ConfigPhaseType::b << "\n";
    outStream << "Number of Threads (t): " << ConfigPhaseType::n_threads << "\n";
    outStream << "Integration Cutoff (c): " << ConfigPhaseType::integration_cutoff << "\n";
    outStream << "Max. Number of Generations (m): " << ConfigPhaseType::max_t << "\n";
    outStream << "Number of Moments (k): " << ConfigPhaseType::k << "\n";

    outStream << "Output Q: " << (ConfigPhaseType::output_Q ? QString("true") : QString("false")) << "\n";
    outStream << "Output R: " << (ConfigPhaseType::output_R ? QString("true") : QString("false")) << "\n";
    outStream << "Output P: " << (ConfigPhaseType::output_P ? QString("true") : QString("false")) << "\n";
    outStream << "Output Moments: " << (ConfigPhaseType::output_Moments ? QString("true") : QString("false")) << "\n";
    outStream << "Output Res: " << (ConfigPhaseType::output_Res ? QString("true") : QString("false")) << "\n";
    outStream << "Force: " << (ConfigPhaseType::force ? QString("true") : QString("false")) << "\n";

    file.close();
}

void ConfigPhaseType::loadConfigPhaseType()
{
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/" + "Phase_Type.cfg");

    QFile file(outputPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        processLine(line);
    }
}

void ConfigPhaseType::processLine(QString line)
{
    QStringList splitted = line.split(": ");
    if(splitted.at(0).compare("Library") == 0) {
        ConfigPhaseType::library = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("ViennaCL Solver") == 0) {
        ConfigPhaseType::vienna_solver = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Model Type") == 0) {
        if(splitted.at(1) == "None")
            ConfigPhaseType::modelType = ModelTypePhaseType::NONE;
        else if(splitted.at(1) == "Phase Type Dist.")
            ConfigPhaseType::modelType = ModelTypePhaseType::PHASE_TYPE_DIST;
        else if(splitted.at(1) == "Phase Type Moments")
            ConfigPhaseType::modelType = ModelTypePhaseType::PHASE_TYPE_MOMENTS;
    } else if(splitted.at(0).compare("Population Size (N)") == 0) {
        ConfigPhaseType::population_size = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Selection Coefficient (s)") == 0) {
        ConfigPhaseType::s = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Dominance Coefficient (h)") == 0) {
        ConfigPhaseType::h = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Backward Mutation Rate (u)") == 0) {
        ConfigPhaseType::u = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Forward Mutation Rate (v)") == 0) {
        ConfigPhaseType::v = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("No Recurrent Mutation (m)") == 0) {
        ConfigPhaseType::no_rem = splitted.at(1).compare("true") == 0 ? true : false;
        ConfigPhaseType::rem = !no_rem;
    } else if(splitted.at(0).compare("Tail Truncation Weight (a)") == 0) {
        ConfigPhaseType::a = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Odds Ratio (k)") == 0) {
        ConfigPhaseType::odds_ratio = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Block Size (b)") == 0) {
        ConfigPhaseType::b = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Number of Threads (t)") == 0) {
        ConfigPhaseType::n_threads = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Integration Cutoff (c)") == 0) {
        ConfigPhaseType::integration_cutoff = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Max. Number of Generations (m)") == 0) {
        ConfigPhaseType::max_t = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Number of Moments (k)") == 0) {
        ConfigPhaseType::k = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Output Q") == 0) {
        ConfigPhaseType::output_Q = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output R") == 0) {
        ConfigPhaseType::output_R = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output P") == 0) {
        ConfigPhaseType::output_P = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output Moments") == 0) {
        ConfigPhaseType::output_Moments = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output Res") == 0) {
        ConfigPhaseType::output_Res = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Force") == 0) {
        ConfigPhaseType::force = splitted.at(1).compare("true") == 0 ? true : false;
    }

}


std::string ConfigPhaseType::library = "Pardiso";
std::string ConfigPhaseType::vienna_solver = "BicGStab";
ModelTypePhaseType ConfigPhaseType::modelType = ModelTypePhaseType::PHASE_TYPE_DIST;
int ConfigPhaseType::population_size = 10000;
double ConfigPhaseType::s = 0;
double ConfigPhaseType::h = 0.5;
double ConfigPhaseType::u = 1e-9;
double ConfigPhaseType::v = 1e-9;
bool ConfigPhaseType::no_rem = false;
bool ConfigPhaseType::rem = !ConfigPhaseType::no_rem;
double ConfigPhaseType::a = 1e-20;
double ConfigPhaseType::odds_ratio = 1.0;
int ConfigPhaseType::b = 100;
int ConfigPhaseType::n_threads = 1;
double ConfigPhaseType::integration_cutoff = 1e-10;
std::string ConfigPhaseType::path_output_P = "output_P.csv";
std::string ConfigPhaseType::path_output_Q = "output_Q.csv";
std::string ConfigPhaseType::path_output_R = "output_R.csv";
std::string ConfigPhaseType::path_output_Moments = "output_Moments.csv";
std::string ConfigPhaseType::path_output_Res = "output_Res.csv";
int ConfigPhaseType::max_t = 10000;
int ConfigPhaseType::k = 20;

bool ConfigPhaseType::output_P = false;
bool ConfigPhaseType::output_Q = false;
bool ConfigPhaseType::output_R = false;
bool ConfigPhaseType::output_Moments = true;
bool ConfigPhaseType::output_Res = true;

bool ConfigPhaseType::force = false;
bool ConfigPhaseType::verbose = false;
bool ConfigPhaseType::help = false;

std::string ConfigPhaseType::error = "";
