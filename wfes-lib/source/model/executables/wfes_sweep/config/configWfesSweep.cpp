#include "configWfesSweep.h"


using namespace wfes::config;

ModelTypeWfesSweep ConfigWfesSweep::modelType = ModelTypeWfesSweep::FIXATION;
std::string ConfigWfesSweep::library = "Pardiso";
std::string ConfigWfesSweep::vienna_solver = "BicGStab";
int ConfigWfesSweep::population_size = 10000;
double ConfigWfesSweep::a = 1e-20;
int ConfigWfesSweep::b = 100;
int ConfigWfesSweep::starting_copies = 0;
int ConfigWfesSweep::n_threads = 1;
double ConfigWfesSweep::integration_cutoff = 1 - 1e-8;
double ConfigWfesSweep::l = 1e-20;

bool ConfigWfesSweep::output_Q = false;
bool ConfigWfesSweep::output_R = false;
bool ConfigWfesSweep::output_N = false;
bool ConfigWfesSweep::output_B = false;
bool ConfigWfesSweep::output_I = false;
bool ConfigWfesSweep::output_Res = true;

std::string ConfigWfesSweep::initial_distribution_csv = "";
std::string ConfigWfesSweep::path_output_Q = "output_Q.csv";
std::string ConfigWfesSweep::path_output_R = "output_R.csv";
std::string ConfigWfesSweep::path_output_N = "output_N.csv";
std::string ConfigWfesSweep::path_output_B = "output_B.csv";
std::string ConfigWfesSweep::path_output_I = "output_I.csv";
std::string ConfigWfesSweep::path_output_Res = "output_Res.csv";

bool ConfigWfesSweep::force = false;
bool ConfigWfesSweep::verbose = false;
std::string ConfigWfesSweep::error = "";
int ConfigWfesSweep::num_comp = 2;

dvec ConfigWfesSweep::u = [] {
    dvec tmp(2);
    tmp << 1e-9, 1e-9;
    return tmp;
}();

dvec ConfigWfesSweep::v = [] {
    dvec tmp(2);
    tmp << 1e-9, 1e-9;
    return tmp;
}();

dvec ConfigWfesSweep::s = [] {
    dvec tmp(2);
    tmp << 0, 0;
    return tmp;
}();

dvec ConfigWfesSweep::h = [] {
    dvec tmp(2);
    tmp << 0.5, 0.5;
    return tmp;
}();

ConfigWfesSweep::ConfigWfesSweep() {}

int ConfigWfesSweep::ModelTypeWfesSweepToInt(ModelTypeWfesSweep modelType)
{
    switch(modelType){
        case ModelTypeWfesSweep::FIXATION:
            return 1;
        case ModelTypeWfesSweep::NONE:
        default:
            return 0;
    }
}

void ConfigWfesSweep::saveConfigWfesSweep()
{
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/");
    QDir dir;

    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Wfes_Sweep.cfg"));
    file.open(QIODevice::WriteOnly);

    if(!file.isOpen()) {
        qDebug() << "The file is not open.";
    }

    QTextStream outStream(&file);

    outStream << "Library: " << QString::fromStdString(ConfigWfesSweep::library) << "\n";
    outStream << "ViennaCL Solver: " << QString::fromStdString(ConfigWfesSweep::vienna_solver) << "\n";
    outStream << "Model Type: " << QString::fromStdString(ModelTypeWfesSweepNames[ModelTypeWfesSweepToInt(ConfigWfesSweep::modelType)]) << "\n";
    outStream << "Population Size (N): " << ConfigWfesSweep::population_size << "\n";

    outStream << "Backward Mutation Rates (u): " << ConfigWfesSweep::u[0] << "; " << ConfigWfesSweep::u[1] << "\n";
    outStream << "Forward Mutation Rates (v): " << ConfigWfesSweep::v[0] << "; " << ConfigWfesSweep::v[1] << "\n";
    outStream << "Selection Coefficients (s): " << ConfigWfesSweep::s[0] << "; " << ConfigWfesSweep::s[1] << "\n";
    outStream << "Dominance Coefficients (h): " << ConfigWfesSweep::h[0] << "; " << ConfigWfesSweep::h[1] << "\n";
    outStream << "Initial Distribution Path (I): " << QString::fromStdString(ConfigWfesSweep::initial_distribution_csv) << "\n";

    outStream << "Tail Truncation Weight (a): " << ConfigWfesSweep::a << "\n";
    outStream << "Block Size (b): " << ConfigWfesSweep::b << "\n";
    outStream << "Starting Copies (p): " << ConfigWfesSweep::starting_copies << "\n";
    outStream << "Number of Threads (t): " << ConfigWfesSweep::n_threads << "\n";
    outStream << "Integration Cutoff (c): " << ConfigWfesSweep::integration_cutoff << "\n";
    outStream << "Transition Probability (l): " << ConfigWfesSweep::l << "\n";

    outStream << "Output Q: " << (ConfigWfesSweep::output_Q ? QString("true") : QString("false")) << "\n";
    outStream << "Output R: " << (ConfigWfesSweep::output_R ? QString("true") : QString("false")) << "\n";
    outStream << "Output N: " << (ConfigWfesSweep::output_N ? QString("true") : QString("false")) << "\n";
    outStream << "Output B: " << (ConfigWfesSweep::output_B ? QString("true") : QString("false")) << "\n";
    outStream << "Output I: " << (ConfigWfesSweep::output_I ? QString("true") : QString("false")) << "\n";
    outStream << "Output Res: " << (ConfigWfesSweep::output_Res ? QString("true") : QString("false")) << "\n";

    outStream << "Num. Comps.: " << ConfigWfesSweep::num_comp << "\n";

    file.close();
}

void ConfigWfesSweep::loadConfigWfesSweep()
{
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/" + "Wfes_Sweep.cfg");

    QFile file(outputPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        processLine(line);
    }
}

void ConfigWfesSweep::processLine(QString line)
{
    QStringList splitted = line.split(": ");
    if(splitted.at(0).compare("Library") == 0) {
        ConfigWfesSweep::library = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("ViennaCL Solver") == 0) {
        ConfigWfesSweep::vienna_solver = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Model Type") == 0) {
        if(splitted.at(1) == "None")
            ConfigWfesSweep::modelType = ModelTypeWfesSweep::NONE;
        else if(splitted.at(1) == "Fixation")
            ConfigWfesSweep::modelType = ModelTypeWfesSweep::FIXATION;
    } else if(splitted.at(0).compare("Population Size (N)") == 0) {
        ConfigWfesSweep::population_size = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Selection Coefficients (s)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        ConfigWfesSweep::s[0] = std::stod(values.at(0).toStdString());
        ConfigWfesSweep::s[1] = std::stod(values.at(1).toStdString());
    } else if(splitted.at(0).compare("Dominance Coefficients (h)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        ConfigWfesSweep::h[0] = std::stod(values.at(0).toStdString());
        ConfigWfesSweep::h[1] = std::stod(values.at(1).toStdString());
    } else if(splitted.at(0).compare("Backward Mutation Rates (u)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        ConfigWfesSweep::u[0] = std::stod(values.at(0).toStdString());
        ConfigWfesSweep::u[1] = std::stod(values.at(1).toStdString());
    } else if(splitted.at(0).compare("Forward Mutation Rates (v)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        ConfigWfesSweep::v[0] = std::stod(values.at(0).toStdString());
        ConfigWfesSweep::v[1] = std::stod(values.at(1).toStdString());
    } else if(splitted.at(0).compare("Tail Truncation Weight (a)") == 0) {
        ConfigWfesSweep::a = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Block Size (b)") == 0) {
        ConfigWfesSweep::b = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Starting Copies (p)") == 0) {
        ConfigWfesSweep::starting_copies = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Number of Threads (t)") == 0) {
        ConfigWfesSweep::n_threads = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Integration Cutoff (c)") == 0) {
        ConfigWfesSweep::integration_cutoff = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Transition Probability (l)") == 0) {
        ConfigWfesSweep::l = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Initial Distribution Path (I)") == 0) {
        ConfigWfesSweep::initial_distribution_csv = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Output Q") == 0) {
        ConfigWfesSweep::output_Q = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output R") == 0) {
        ConfigWfesSweep::output_R = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N") == 0) {
        ConfigWfesSweep::output_N = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output B") == 0) {
        ConfigWfesSweep::output_B = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output I") == 0) {
        ConfigWfesSweep::output_I = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output Res") == 0) {
        ConfigWfesSweep::output_Res = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Num. Comps.") == 0) {
        ConfigWfesSweep::num_comp = std::stoi(splitted.at(1).toStdString());
    }


}

