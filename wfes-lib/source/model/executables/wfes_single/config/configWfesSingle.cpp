#include "configWfesSingle.h"

using namespace wfes::config;

std::string ConfigWfesSingle::library = "Pardiso";
std::string ConfigWfesSingle::vienna_solver = "BicGStab";
ModelTypeWfesSingle ConfigWfesSingle::modelType = ModelTypeWfesSingle::ABSORPTION;
int ConfigWfesSingle::population_size = 10000;
double ConfigWfesSingle::s = 0.005;
double ConfigWfesSingle::h = 0.5;
double ConfigWfesSingle::u = 1.2e-8;
double ConfigWfesSingle::v = 1.2e-8;
bool ConfigWfesSingle::no_rem = false;
bool ConfigWfesSingle::rem = !ConfigWfesSingle::no_rem;
double ConfigWfesSingle::a = 1e-20;
double ConfigWfesSingle::odds_ratio = 1.0;
int ConfigWfesSingle::b = 100;
int ConfigWfesSingle::n_threads = 1;
double ConfigWfesSingle::integration_cutoff = 1e-10;
int ConfigWfesSingle::starting_copies = 0;

int ConfigWfesSingle::observed_copies = 1;

std::string ConfigWfesSingle::initial_distribution_csv = "";
std::string ConfigWfesSingle::path_output_Q = "output_Q.csv";
std::string ConfigWfesSingle::path_output_R = "output_R.csv";
std::string ConfigWfesSingle::path_output_N = "output_N.csv";
std::string ConfigWfesSingle::path_output_N_ext = "output_N_ext.csv";
std::string ConfigWfesSingle::path_output_N_fix = "output_N_fix.csv";
std::string ConfigWfesSingle::path_output_B = "output_B.csv";
std::string ConfigWfesSingle::path_output_I = "output_I.csv";
std::string ConfigWfesSingle::path_output_E = "output_E.csv";
std::string ConfigWfesSingle::path_output_V = "output_V.csv";
std::string ConfigWfesSingle::path_output_Res = "output_Res.csv";

bool ConfigWfesSingle::output_Q = false;
bool ConfigWfesSingle::output_R = false;
bool ConfigWfesSingle::output_N = false;
bool ConfigWfesSingle::output_N_ext = false;
bool ConfigWfesSingle::output_N_fix = false;
bool ConfigWfesSingle::output_B = false;
bool ConfigWfesSingle::output_I = false;
bool ConfigWfesSingle::output_E = false;
bool ConfigWfesSingle::output_V = false;
bool ConfigWfesSingle::output_Res = true;

bool ConfigWfesSingle::force = false;
bool ConfigWfesSingle::verbose = false;
bool ConfigWfesSingle::help = false;

bool ConfigWfesSingle::saveImageI = false;
bool ConfigWfesSingle::saveImageQ = false;
bool ConfigWfesSingle::saveImageR = false;
bool ConfigWfesSingle::saveImageN = false;
bool ConfigWfesSingle::saveImageNExt = false;
bool ConfigWfesSingle::saveImageNFix = false;
bool ConfigWfesSingle::saveImageB = false;
bool ConfigWfesSingle::saveImageV = false;
bool ConfigWfesSingle::saveImageE = false;

std::string ConfigWfesSingle::error = "";

ConfigWfesSingle::ConfigWfesSingle() {
}


int ConfigWfesSingle::ModelTypeWfesSingleToInt(ModelTypeWfesSingle modelType){
    switch(modelType){
    case ModelTypeWfesSingle::ABSORPTION:
        return 1;
    case ModelTypeWfesSingle::FIXATION:
        return 2;
    case ModelTypeWfesSingle::ESTABLISHMENT:
        return 3;
    case ModelTypeWfesSingle::FUNDAMENTAL:
        return 4;
    case ModelTypeWfesSingle::EQUILIBRIUM:
        return 5;
    case ModelTypeWfesSingle::NON_ABSORBING:
        return 6;
    case ModelTypeWfesSingle::ALLELE_AGE:
        return 7;
    case ModelTypeWfesSingle::NONE:
    default:
        return 0;
    }
}

void ConfigWfesSingle::saveConfigWfesSingle()
{
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/");
    QDir dir;

    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Wfes_Single.cfg"));
    file.open(QIODevice::WriteOnly);

    if(!file.isOpen()) {
        qDebug() << "The file is not open.";
    }

    QTextStream outStream(&file);

    outStream << "Library: " << QString::fromStdString(ConfigWfesSingle::library) << "\n";
    outStream << "ViennaCL Solver: " << QString::fromStdString(ConfigWfesSingle::vienna_solver) << "\n";
    outStream << "Model Type: " << QString::fromStdString(ModelTypeNames[ModelTypeWfesSingleToInt(ConfigWfesSingle::modelType)]) << "\n";
    outStream << "Population Size (N): " << ConfigWfesSingle::population_size << "\n";
    outStream << "Selection Coefficient (s): " << ConfigWfesSingle::s << "\n";
    outStream << "Dominance Coefficient (h): " << ConfigWfesSingle::h << "\n";
    outStream << "Backward Mutation Rate (u): " << ConfigWfesSingle::u << "\n";
    outStream << "Forward Mutation Rate (v): " << ConfigWfesSingle::v << "\n";
    outStream << "No Recurrent Mutation (m): " << (ConfigWfesSingle::no_rem ? QString("true") : QString("false")) << "\n";
    outStream << "Tail Truncation Weight (a): " << ConfigWfesSingle::a << "\n";
    outStream << "Odds Ratio (k): " << ConfigWfesSingle::odds_ratio << "\n";
    outStream << "Block Size (b): " << ConfigWfesSingle::b << "\n";
    outStream << "Number of Threads (t): " << ConfigWfesSingle::n_threads << "\n";
    outStream << "Integration Cutoff (c): " << ConfigWfesSingle::integration_cutoff << "\n";
    outStream << "Starting Copies (p): " << ConfigWfesSingle::starting_copies << "\n";
    outStream << "Observed Copies (x): " << ConfigWfesSingle::observed_copies << "\n";
    outStream << "Initial Distribution Path (I): " << QString::fromStdString(ConfigWfesSingle::initial_distribution_csv) << "\n";

    outStream << "Output I: " << (ConfigWfesSingle::output_I ? QString("true") : QString("false")) << "\n";
    outStream << "Output Q: " << (ConfigWfesSingle::output_Q ? QString("true") : QString("false")) << "\n";
    outStream << "Output R: " << (ConfigWfesSingle::output_R ? QString("true") : QString("false")) << "\n";
    outStream << "Output N: " << (ConfigWfesSingle::output_N ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Ext.: " << (ConfigWfesSingle::output_N_ext ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Fix.: " << (ConfigWfesSingle::output_N_fix ? QString("true") : QString("false")) << "\n";
    outStream << "Output B: " << (ConfigWfesSingle::output_B ? QString("true") : QString("false")) << "\n";
    outStream << "Output E: " << (ConfigWfesSingle::output_E ? QString("true") : QString("false")) << "\n";
    outStream << "Output V: " << (ConfigWfesSingle::output_V ? QString("true") : QString("false")) << "\n";
    outStream << "Output Res: " << (ConfigWfesSingle::output_Res ? QString("true") : QString("false")) << "\n";
    outStream << "Force: " << (ConfigWfesSingle::force ? QString("true") : QString("false")) << "\n";


    file.close();
}

void ConfigWfesSingle::loadConfigWfesSingle()
{
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/" + "Wfes_Single.cfg");

    QFile file(outputPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        processLine(line);
    }
}

void ConfigWfesSingle::processLine(QString line) {
    QStringList splitted = line.split(": ");
    if(splitted.at(0).compare("Library") == 0) {
        ConfigWfesSingle::library = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("ViennaCL Solver") == 0) {
        ConfigWfesSingle::vienna_solver = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Model Type") == 0) {
        if(splitted.at(1) == "None")
            ConfigWfesSingle::modelType = ModelTypeWfesSingle::NONE;
        else if(splitted.at(1) == "Absorption")
            ConfigWfesSingle::modelType = ModelTypeWfesSingle::ABSORPTION;
        else if(splitted.at(1) == "Fixation")
            ConfigWfesSingle::modelType = ModelTypeWfesSingle::FIXATION;
        else if(splitted.at(1) == "Establishment")
            ConfigWfesSingle::modelType = ModelTypeWfesSingle::ESTABLISHMENT;
        else if(splitted.at(1) == "Fundamental")
            ConfigWfesSingle::modelType = ModelTypeWfesSingle::FUNDAMENTAL;
        else if(splitted.at(1) == "Equilibrium")
            ConfigWfesSingle::modelType = ModelTypeWfesSingle::EQUILIBRIUM;
        else if(splitted.at(1) == "Non Absorbing")
            ConfigWfesSingle::modelType = ModelTypeWfesSingle::NON_ABSORBING;
        else if(splitted.at(1) == "Allele Age")
            ConfigWfesSingle::modelType = ModelTypeWfesSingle::ALLELE_AGE;
    } else if(splitted.at(0).compare("Population Size (N)") == 0) {
        ConfigWfesSingle::population_size = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Selection Coefficient (s)") == 0) {
        ConfigWfesSingle::s = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Dominance Coefficient (h)") == 0) {
        ConfigWfesSingle::h = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Backward Mutation Rate (u)") == 0) {
        ConfigWfesSingle::u = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Forward Mutation Rate (v)") == 0) {
        ConfigWfesSingle::v = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("No Recurrent Mutation (m)") == 0) {
        ConfigWfesSingle::no_rem = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Tail Truncation Weight (a)") == 0) {
        ConfigWfesSingle::a = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Odds Ratio (k)") == 0) {
        ConfigWfesSingle::odds_ratio = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Block Size (b)") == 0) {
        ConfigWfesSingle::b = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Number of Threads (t)") == 0) {
        ConfigWfesSingle::n_threads = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Integration Cutoff (c)") == 0) {
        ConfigWfesSingle::integration_cutoff = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Starting Copies (p)") == 0) {
        ConfigWfesSingle::starting_copies = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Observed Copies (x)") == 0) {
        ConfigWfesSingle::observed_copies = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Initial Distribution Path (I)") == 0) {
        ConfigWfesSingle::initial_distribution_csv = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Output I") == 0) {
        ConfigWfesSingle::output_I = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output Q") == 0) {
        ConfigWfesSingle::output_Q = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output R") == 0) {
        ConfigWfesSingle::output_R = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N") == 0) {
        ConfigWfesSingle::output_N = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Ext.") == 0) {
        ConfigWfesSingle::output_N_ext = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Fix.") == 0) {
        ConfigWfesSingle::output_N_fix = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output B") == 0) {
        ConfigWfesSingle::output_B = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output E") == 0) {
        ConfigWfesSingle::output_E = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output V") == 0) {
        ConfigWfesSingle::output_V = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output Res") == 0) {
        ConfigWfesSingle::output_Res = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Force") == 0) {
        ConfigWfesSingle::force = splitted.at(1).compare("true") == 0 ? true : false;
    }
}

