#include "configTimeDistSGV.h"

using namespace wfes::config;

dvec ConfigTimeDistSGV::u = [] {
    dvec tmp(2);
    tmp << 1e-9, 1e-9;
    return tmp;
}();

dvec ConfigTimeDistSGV::v = [] {
    dvec tmp(2);
    tmp << 1e-9, 1e-9;
    return tmp;
}();

dvec ConfigTimeDistSGV::s = [] {
    dvec tmp(2);
    tmp << 0, 0;
    return tmp;
}();

dvec ConfigTimeDistSGV::h = [] {
    dvec tmp(2);
    tmp << 0.5, 0.5;
    return tmp;
}();

int ConfigTimeDistSGV::population_size = 10000;
double ConfigTimeDistSGV::a = 1e-20;
double ConfigTimeDistSGV::integration_cutoff = 1e-10;
int ConfigTimeDistSGV::max_t = 10000;
bool ConfigTimeDistSGV::no_rem = false;
bool ConfigTimeDistSGV::rem = !ConfigTimeDistSGV::no_rem;

double ConfigTimeDistSGV::l = 1e-20;

int ConfigTimeDistSGV::num_comp = 2;

bool ConfigTimeDistSGV::force = false;

ConfigTimeDistSGV::ConfigTimeDistSGV(){}

void ConfigTimeDistSGV::saveConfigTimeDistSGV()
{

    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/");
    QDir dir;

    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Time_Dist.cfg"));
    file.open(QIODevice::WriteOnly | QIODevice::Append);

    if(!file.isOpen()) {
        qDebug() << "The file is not open.";
    }

    QTextStream outStream(&file);

    outStream << "# Time Dist. SGV Options" << "\n";

    outStream << "Population Size SGV (N): " << ConfigTimeDistSGV::population_size << "\n";

    outStream << "Backward Mutation Rates (u): " << ConfigTimeDistSGV::u[0] << "; " << ConfigTimeDistSGV::u[1] << "\n";
    outStream << "Forward Mutation Rates (v): " << ConfigTimeDistSGV::v[0] << "; " << ConfigTimeDistSGV::v[1] << "\n";
    outStream << "Selection Coefficients (s): " << ConfigTimeDistSGV::s[0] << "; " << ConfigTimeDistSGV::s[1] << "\n";
    outStream << "Dominance Coefficients (h): " << ConfigTimeDistSGV::h[0] << "; " << ConfigTimeDistSGV::h[1] << "\n";
    outStream << "Tail Truncation Weight SGV (a): " << ConfigTimeDistSGV::a << "\n";
    outStream << "Integration Cutoff SGV (c): " << ConfigTimeDistSGV::integration_cutoff << "\n";
    outStream << "Max. Number of Generations SGV (m): " << ConfigTimeDistSGV::max_t << "\n";
    outStream << "No Recurrent Mutation SGV (m): " << (ConfigTimeDistSGV::no_rem ? QString("true") : QString("false")) << "\n";

    outStream << "Transition Probability (l): " << ConfigTimeDistSGV::l << "\n";
    outStream << "Force: " << (ConfigTimeDistSGV::force ? QString("true") : QString("false")) << "\n";

    outStream << "Num. Comps.: " << ConfigTimeDistSGV::num_comp << "\n";

    file.close();
}

void ConfigTimeDistSGV::loadConfigTimeDistSGV()
{
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

void ConfigTimeDistSGV::processLine(QString line) {
    QStringList splitted = line.split(": ");
    if(splitted.at(0).compare("Selection Coefficients (s)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        ConfigTimeDistSGV::s[0] = std::stod(values.at(0).toStdString());
        ConfigTimeDistSGV::s[1] = std::stod(values.at(1).toStdString());
    } else if(splitted.at(0).compare("Dominance Coefficients (h)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        ConfigTimeDistSGV::h[0] = std::stod(values.at(0).toStdString());
        ConfigTimeDistSGV::h[1] = std::stod(values.at(1).toStdString());
    } else if(splitted.at(0).compare("Backward Mutation Rates (u)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        ConfigTimeDistSGV::u[0] = std::stod(values.at(0).toStdString());
        ConfigTimeDistSGV::u[1] = std::stod(values.at(1).toStdString());
    } else if(splitted.at(0).compare("Forward Mutation Rates (v)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        ConfigTimeDistSGV::v[0] = std::stod(values.at(0).toStdString());
        ConfigTimeDistSGV::v[1] = std::stod(values.at(1).toStdString());
    } else if(splitted.at(0).compare("Transition Probability (l)") == 0) {
        ConfigTimeDistSGV::l = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Num. Comps.") == 0) {
        ConfigTimeDistSGV::num_comp = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Force") == 0) {
        ConfigTimeDistSGV::force = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Population Size SGV (N)") == 0) {
        ConfigTimeDistSGV::population_size = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Tail Truncation Weight SGV (a)") == 0) {
        ConfigTimeDistSGV::a = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Integration Cutoff SGV (c)") == 0) {
        ConfigTimeDistSGV::integration_cutoff = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Max. Number of Generations SGV (m)") == 0) {
        ConfigTimeDistSGV::max_t = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("No Recurrent Mutation SGV (m)") == 0) {
        ConfigTimeDistSGV::no_rem = splitted.at(1).compare("true") == 0 ? true : false;
        ConfigTimeDistSGV::rem = !no_rem;
    }
}
