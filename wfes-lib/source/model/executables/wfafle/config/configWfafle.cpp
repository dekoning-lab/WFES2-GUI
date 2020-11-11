#include "configWfafle.h"

using namespace wfes::config;

ConfigWfafle::ConfigWfafle() {}

void ConfigWfafle::saveConfigWfafle()
{
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/");
    QDir dir;

    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Wfafle.cfg"));
    file.open(QIODevice::WriteOnly);

    if(!file.isOpen()) {
        qDebug() << "The file is not open.";
    }

    QTextStream outStream(&file);

    outStream << "Library: " << QString::fromStdString(ConfigWfafle::library) << "\n";
    outStream << "ViennaCL Solver: " << QString::fromStdString(ConfigWfafle::vienna_solver) << "\n";

    outStream << "Tail Truncation Weight (a): " << ConfigWfafle::a << "\n";
    outStream << "Initial number of alleles (p): " << ConfigWfafle::p << "\n";
    outStream << "Number of Threads (t): " << ConfigWfafle::n_threads << "\n";
    outStream << "Initial Distribution Path (I): " << QString::fromStdString(ConfigWfafle::initial_distribution_csv) << "\n";

    outStream << "Output Dist.: " << (ConfigWfafle::output_Dist ? QString("true") : QString("false")) << "\n";
    outStream << "Force: " << (ConfigWfafle::force ? QString("true") : QString("false")) << "\n";

    outStream << "Num. Comps.: " << ConfigWfafle::num_comp << "\n";

    outStream << "Population Size (N): ";
    for(int i = 0; i < ConfigWfafle::num_comp - 1; i++) {
        outStream << ConfigWfafle::N[i] << "; ";
    }
    outStream << ConfigWfafle::N[ConfigWfafle::num_comp - 1] << "\n";

    outStream << "Number of generations (G): ";
    for(int i = 0; i < ConfigWfafle::num_comp - 1; i++) {
        outStream << ConfigWfafle::G[i] << "; ";
    }
    outStream << ConfigWfafle::G[ConfigWfafle::num_comp - 1] << "\n";

    outStream << "Individial selection coefficient (s): ";
    for(int i = 0; i < ConfigWfafle::num_comp - 1; i++) {
        outStream << ConfigWfafle::s[i] << "; ";
    }
    outStream << ConfigWfafle::s[ConfigWfafle::num_comp - 1] << "\n";

    outStream << "Individial dominance coefficient (h): ";
    for(int i = 0; i < ConfigWfafle::num_comp - 1; i++) {
        outStream << ConfigWfafle::h[i] << "; ";
    }
    outStream << ConfigWfafle::h[ConfigWfafle::num_comp - 1] << "\n";

    outStream << "Backward Mutation Rates (u): ";
    for(int i = 0; i < ConfigWfafle::num_comp - 1; i++) {
        outStream << ConfigWfafle::u[i] << "; ";
    }
    outStream << ConfigWfafle::u[ConfigWfafle::num_comp - 1] << "\n";

    outStream << "Forward Mutation Rates (v): ";
    for(int i = 0; i < ConfigWfafle::num_comp - 1; i++) {
        outStream << ConfigWfafle::v[i] << "; ";
    }
    outStream << ConfigWfafle::v[ConfigWfafle::num_comp - 1] << "\n";

    file.close();

}

void ConfigWfafle::loadConfigWfafle()
{
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/" + "Wfafle.cfg");

    QFile file(outputPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        processLine(line);
    }
}

void ConfigWfafle::processLine(QString line)
{
    QStringList splitted = line.split(": ");
    if(splitted.at(0).compare("Library") == 0) {
        ConfigWfafle::library = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("ViennaCL Solver") == 0) {
        ConfigWfafle::vienna_solver = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Tail Truncation Weight (a)") == 0) {
        ConfigWfafle::a = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Initial number of alleles (p)") == 0) {
        ConfigWfafle::p = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Number of Threads (t)") == 0) {
        ConfigWfafle::n_threads = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Initial Distribution Path (I)") == 0) {
        ConfigWfafle::initial_distribution_csv = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Output Dist.") == 0) {
        ConfigWfafle::output_Dist = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Force") == 0) {
        ConfigWfafle::force = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Num. Comps.") == 0) {
        ConfigWfafle::num_comp = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Population Size (N)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        ivec newN(values.size());
        for(int i = 0; i < values.size(); i++) {
            newN(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafle::N = newN;
    } else if(splitted.at(0).compare("Number of generations (G)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        ivec newG(values.size());
        for(int i = 0; i < values.size(); i++) {
            newG(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafle::G = newG;
    } else if(splitted.at(0).compare("Individial selection coefficient (s)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec news(values.size());
        for(int i = 0; i < values.size(); i++) {
            news(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafle::s = news;
    } else if(splitted.at(0).compare("Individial dominance coefficient (h)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newh(values.size());
        for(int i = 0; i < values.size(); i++) {
            newh(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafle::h = newh;
    } else if(splitted.at(0).compare("Backward Mutation Rates (u)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newu(values.size());
        for(int i = 0; i < values.size(); i++) {
            newu(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafle::u = newu;
    } else if(splitted.at(0).compare("Forward Mutation Rates (v)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newv(values.size());
        for(int i = 0; i < values.size(); i++) {
            newv(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafle::v = newv;
    }

}

ivec ConfigWfafle::N = [] {
    ivec tmp(1);
    tmp << 100;
    return tmp;
}();

ivec ConfigWfafle::G = [] {
    ivec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfafle::u = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfafle::v = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfafle::s = [] {
    dvec tmp(1);
    tmp << 0;
    return tmp;
}();

dvec ConfigWfafle::h = [] {
    dvec tmp(1);
    tmp << 0.5;
    return tmp;
}();

std::string ConfigWfafle::library = "Pardiso";
std::string ConfigWfafle::vienna_solver = "BicGStab";

double ConfigWfafle::a = 1e-20;
int ConfigWfafle::p = 0;
int ConfigWfafle::n_threads = 1;

bool ConfigWfafle::output_I = false;
bool ConfigWfafle::output_Dist = true;

std::string ConfigWfafle::initial_distribution_csv = "";
std::string ConfigWfafle::path_output_I = "output_I.csv";
std::string ConfigWfafle::path_output_Dist = "output_Dist.csv";

bool ConfigWfafle::force = false;
bool ConfigWfafle::verbose = false;
std::string ConfigWfafle::error = "";
int ConfigWfafle::num_comp = 1;
