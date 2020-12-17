#include "configWfafd.h"

using namespace wfes::config;

void ConfigWfafd::saveConfigWfafd() {
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/");

    QDir dir;
    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Wfafd.cfg"));

    file.open(QIODevice::WriteOnly);

    QTextStream outStream(&file);

    outStream << "Library: " << QString::fromStdString(ConfigWfafd::library) << "\n";
    outStream << "ViennaCL Solver: " << QString::fromStdString(ConfigWfafd::vienna_solver) << "\n";

    outStream << "Tail Truncation Weight (a): " << ConfigWfafd::a << "\n";
    outStream << "Initial number of alleles (p): " << ConfigWfafd::p << "\n";
    outStream << "Number of Threads (t): " << ConfigWfafd::n_threads << "\n";
    outStream << "Initial Distribution Path (I): " << QString::fromStdString(ConfigWfafd::initial_distribution_csv) << "\n";

    outStream << "Output Dist.: " << (ConfigWfafd::output_Dist ? QString("true") : QString("false")) << "\n";
    outStream << "Force: " << (ConfigWfafd::force ? QString("true") : QString("false")) << "\n";

    outStream << "Num. Comps.: " << ConfigWfafd::num_comp << "\n";

    outStream << "Population Size (N): ";
    for(int i = 0; i < ConfigWfafd::num_comp - 1; i++) {
        outStream << ConfigWfafd::N[i] << "; ";
    }
    outStream << ConfigWfafd::N[ConfigWfafd::num_comp - 1] << "\n";

    outStream << "Number of generations (G): ";
    for(int i = 0; i < ConfigWfafd::num_comp - 1; i++) {
        outStream << ConfigWfafd::G[i] << "; ";
    }
    outStream << ConfigWfafd::G[ConfigWfafd::num_comp - 1] << "\n";

    if(wfes::controllers::GlobalConfiguration::populationScaled) {
        outStream << "Backward Mutation Rates (u): ";
        for(int i = 0; i < ConfigWfafd::num_comp - 1; i++) {
            outStream << ConfigWfafd::u[i] / (4 * ConfigWfafd::N[i]) << "; ";
        }
        outStream << ConfigWfafd::u[ConfigWfafd::num_comp - 1] / (4 * ConfigWfafd::N[ConfigWfafd::num_comp - 1]) << "\n";

        outStream << "Forward Mutation Rates (v): ";
        for(int i = 0; i < ConfigWfafd::num_comp - 1; i++) {
            outStream << ConfigWfafd::v[i] / (4 * ConfigWfafd::N[i]) << "; ";
        }
        outStream << ConfigWfafd::v[ConfigWfafd::num_comp - 1] / (4 * ConfigWfafd::N[ConfigWfafd::num_comp - 1]) << "\n";

        outStream << "Individial selection coefficient (s): ";
        for(int i = 0; i < ConfigWfafd::num_comp - 1; i++) {
            outStream << ConfigWfafd::s[i] / (2 * ConfigWfafd::N[i]) << "; ";
        }
        outStream << ConfigWfafd::s[ConfigWfafd::num_comp - 1] / (2 * ConfigWfafd::N[ConfigWfafd::num_comp - 1]) << "\n";
    } else {
        outStream << "Backward Mutation Rates (u): ";
        for(int i = 0; i < ConfigWfafd::num_comp - 1; i++) {
            outStream << ConfigWfafd::u[i] << "; ";
        }
        outStream << ConfigWfafd::u[ConfigWfafd::num_comp - 1] << "\n";

        outStream << "Forward Mutation Rates (v): ";
        for(int i = 0; i < ConfigWfafd::num_comp - 1; i++) {
            outStream << ConfigWfafd::v[i] << "; ";
        }
        outStream << ConfigWfafd::v[ConfigWfafd::num_comp - 1] << "\n";

        outStream << "Individial selection coefficient (s): ";
        for(int i = 0; i < ConfigWfafd::num_comp - 1; i++) {
            outStream << ConfigWfafd::s[i] << "; ";
        }
        outStream << ConfigWfafd::s[ConfigWfafd::num_comp - 1] << "\n";
    }

    outStream << "Individial dominance coefficient (h): ";
    for(int i = 0; i < ConfigWfafd::num_comp - 1; i++) {
        outStream << ConfigWfafd::h[i] << "; ";
    }
    outStream << ConfigWfafd::h[ConfigWfafd::num_comp - 1] << "\n";

    file.close();
}

void ConfigWfafd::loadConfigWfafd() {
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/" + "Wfafd.cfg");

    QFile file(outputPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        processLine(line);
    }
}

void ConfigWfafd::processLine(QString line) {
    QStringList splitted = line.split(": ");
    if(splitted.at(0).compare("Library") == 0) {
        ConfigWfafd::library = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("ViennaCL Solver") == 0) {
        ConfigWfafd::vienna_solver = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Tail Truncation Weight (a)") == 0) {
        ConfigWfafd::a = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Initial number of alleles (p)") == 0) {
        ConfigWfafd::p = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Number of Threads (t)") == 0) {
        ConfigWfafd::n_threads = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Initial Distribution Path (I)") == 0) {
        ConfigWfafd::initial_distribution_csv = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Output Dist.") == 0) {
        ConfigWfafd::output_Dist = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Force") == 0) {
        ConfigWfafd::force = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Num. Comps.") == 0) {
        ConfigWfafd::num_comp = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Population Size (N)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        ivec newN(values.size());
        for(int i = 0; i < values.size(); i++) {
            newN(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafd::N = newN;
    } else if(splitted.at(0).compare("Number of generations (G)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        ivec newG(values.size());
        for(int i = 0; i < values.size(); i++) {
            newG(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafd::G = newG;
    } else if(splitted.at(0).compare("Individial selection coefficient (s)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec news(values.size());
        for(int i = 0; i < values.size(); i++) {
            news(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafd::s = news;
    } else if(splitted.at(0).compare("Individial dominance coefficient (h)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newh(values.size());
        for(int i = 0; i < values.size(); i++) {
            newh(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafd::h = newh;
    } else if(splitted.at(0).compare("Backward Mutation Rates (u)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newu(values.size());
        for(int i = 0; i < values.size(); i++) {
            newu(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafd::u = newu;
    } else if(splitted.at(0).compare("Forward Mutation Rates (v)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newv(values.size());
        for(int i = 0; i < values.size(); i++) {
            newv(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafd::v = newv;
    }
}


////////////////////////////////
// Static initializations here//
////////////////////////////////

ivec ConfigWfafd::N = [] {
    ivec tmp(1);
    tmp << 100;
    return tmp;
}();

ivec ConfigWfafd::G = [] {
    ivec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfafd::u = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfafd::v = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfafd::s = [] {
    dvec tmp(1);
    tmp << 0;
    return tmp;
}();

dvec ConfigWfafd::h = [] {
    dvec tmp(1);
    tmp << 0.5;
    return tmp;
}();

std::string ConfigWfafd::library = "Pardiso";
std::string ConfigWfafd::vienna_solver = "BicGStab";

double ConfigWfafd::a = 1e-20;
int ConfigWfafd::p = 0;
int ConfigWfafd::n_threads = 1;

bool ConfigWfafd::output_I = false;
bool ConfigWfafd::output_Dist = true;

std::string ConfigWfafd::initial_distribution_csv = "";
std::string ConfigWfafd::path_output_I = "output_I.csv";
std::string ConfigWfafd::path_output_Dist = "output_Dist.csv";

bool ConfigWfafd::force = false;
int ConfigWfafd::num_comp = 1;
