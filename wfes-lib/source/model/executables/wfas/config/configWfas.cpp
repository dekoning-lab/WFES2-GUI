#include "configWfas.h"

using namespace wfes::config;

ConfigWfas::ConfigWfas() {}

void ConfigWfas::saveConfigWfas()
{
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/");
    QDir dir;

    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Wfas.cfg"));
    file.open(QIODevice::WriteOnly);

    if(!file.isOpen()) {
        qDebug() << "The file is not open.";
    }

    QTextStream outStream(&file);

    outStream << "Library: " << QString::fromStdString(ConfigWfas::library) << "\n";
    outStream << "ViennaCL Solver: " << QString::fromStdString(ConfigWfas::vienna_solver) << "\n";

    outStream << "Tail Truncation Weight (a): " << ConfigWfas::a << "\n";
    outStream << "Initial number of alleles (p): " << ConfigWfas::p << "\n";
    outStream << "Number of Threads (t): " << ConfigWfas::n_threads << "\n";
    outStream << "No proj: " << (ConfigWfas::no_proj ? QString("true") : QString("false")) << "\n";
    outStream << "Initial Distribution Path (I): " << QString::fromStdString(ConfigWfas::initial_distribution_csv) << "\n";

    outStream << "Output Q: " << (ConfigWfas::output_Q ? QString("true") : QString("false")) << "\n";
    outStream << "Output R: " << (ConfigWfas::output_R ? QString("true") : QString("false")) << "\n";
    outStream << "Output N: " << (ConfigWfas::output_N ? QString("true") : QString("false")) << "\n";
    outStream << "Output B: " << (ConfigWfas::output_B ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Ext.: " << (ConfigWfas::output_N_Ext ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Fix.: " << (ConfigWfas::output_N_Fix ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Tmo.: " << (ConfigWfas::output_N_Tmo ? QString("true") : QString("false")) << "\n";
    outStream << "Output Dist.: " << (ConfigWfas::output_Dist ? QString("true") : QString("false")) << "\n";
    outStream << "Force: " << (ConfigWfas::force ? QString("true") : QString("false")) << "\n";

    outStream << "Num. Comps.: " << ConfigWfas::num_comp << "\n";

    outStream << "Population Size (N): ";
    for(int i = 0; i < ConfigWfas::num_comp - 1; i++) {
        outStream << ConfigWfas::N[i] << "; ";
    }
    outStream << ConfigWfas::N[ConfigWfas::num_comp - 1] << "\n";

    outStream << "Number of generations (G): ";
    for(int i = 0; i < ConfigWfas::num_comp - 1; i++) {
        outStream << ConfigWfas::G[i] << "; ";
    }
    outStream << ConfigWfas::G[ConfigWfas::num_comp - 1] << "\n";

    outStream << "Approximating (down) factor for each population size (f): ";
    for(int i = 0; i < ConfigWfas::num_comp - 1; i++) {
        outStream << ConfigWfas::f[i] << "; ";
    }
    outStream << ConfigWfas::f[ConfigWfas::num_comp - 1] << "\n";

    outStream << "Individial selection coefficient (s): ";
    for(int i = 0; i < ConfigWfas::num_comp - 1; i++) {
        outStream << ConfigWfas::s[i] << "; ";
    }
    outStream << ConfigWfas::s[ConfigWfas::num_comp - 1] << "\n";

    outStream << "Individial dominance coefficient (h): ";
    for(int i = 0; i < ConfigWfas::num_comp - 1; i++) {
        outStream << ConfigWfas::h[i] << "; ";
    }
    outStream << ConfigWfas::h[ConfigWfas::num_comp - 1] << "\n";

    outStream << "Backward Mutation Rates (u): ";
    for(int i = 0; i < ConfigWfas::num_comp - 1; i++) {
        outStream << ConfigWfas::u[i] << "; ";
    }
    outStream << ConfigWfas::u[ConfigWfas::num_comp - 1] << "\n";

    outStream << "Forward Mutation Rates (v): ";
    for(int i = 0; i < ConfigWfas::num_comp - 1; i++) {
        outStream << ConfigWfas::v[i] << "; ";
    }
    outStream << ConfigWfas::v[ConfigWfas::num_comp - 1] << "\n";


    file.close();

}

void ConfigWfas::loadConfigWfas()
{
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/" + "Wfas.cfg");

    QFile file(outputPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        processLine(line);
    }
}

void ConfigWfas::processLine(QString line)
{
    QStringList splitted = line.split(": ");
    if(splitted.at(0).compare("Library") == 0) {
        ConfigWfas::library = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("ViennaCL Solver") == 0) {
        ConfigWfas::vienna_solver = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Tail Truncation Weight (a)") == 0) {
        ConfigWfas::a = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Initial number of alleles (p)") == 0) {
        ConfigWfas::p = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Number of Threads (t)") == 0) {
        ConfigWfas::n_threads = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("No proj") == 0) {
        ConfigWfas::no_proj = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Initial Distribution Path (I)") == 0) {
        ConfigWfas::initial_distribution_csv = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Output Q") == 0) {
        ConfigWfas::output_Q = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output R") == 0) {
        ConfigWfas::output_R = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N") == 0) {
        ConfigWfas::output_N = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output B") == 0) {
        ConfigWfas::output_B = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Ext.") == 0) {
        ConfigWfas::output_N_Ext = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Fix.") == 0) {
        ConfigWfas::output_N_Fix = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Tmo.") == 0) {
        ConfigWfas::output_N_Tmo = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output Dist.") == 0) {
        ConfigWfas::output_Dist = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Force") == 0) {
        ConfigWfas::force = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Num. Comps.") == 0) {
        ConfigWfas::num_comp = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Population Size (N)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        lvec newN(values.size());
        for(int i = 0; i < values.size(); i++) {
            newN(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfas::N = newN;
    } else if(splitted.at(0).compare("Number of generations (G)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        lvec newG(values.size());
        for(int i = 0; i < values.size(); i++) {
            newG(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfas::G = newG;
    } else if(splitted.at(0).compare("Approximating (down) factor for each population size (f)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newf(values.size());
        for(int i = 0; i < values.size(); i++) {
            newf(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfas::f = newf;
    } else if(splitted.at(0).compare("Individial selection coefficient (s)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec news(values.size());
        for(int i = 0; i < values.size(); i++) {
            news(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfas::s = news;
    } else if(splitted.at(0).compare("Individial dominance coefficient (h)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newh(values.size());
        for(int i = 0; i < values.size(); i++) {
            newh(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfas::h = newh;
    } else if(splitted.at(0).compare("Backward Mutation Rates (u)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newu(values.size());
        for(int i = 0; i < values.size(); i++) {
            newu(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfas::u = newu;
    } else if(splitted.at(0).compare("Forward Mutation Rates (v)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newv(values.size());
        for(int i = 0; i < values.size(); i++) {
            newv(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfas::v = newv;
    }



}

lvec ConfigWfas::N = [] {
    lvec tmp(1);
    tmp << 100;
    return tmp;
}();

lvec ConfigWfas::G = [] {
    lvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfas::f = [] {
    dvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfas::u = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfas::v = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfas::s = [] {
    dvec tmp(1);
    tmp << 0;
    return tmp;
}();

dvec ConfigWfas::h = [] {
    dvec tmp(1);
    tmp << 0.6;
    return tmp;
}();

std::string ConfigWfas::library = "Pardiso";
std::string ConfigWfas::vienna_solver = "BicGStab";

double ConfigWfas::a = 1e-20;
int ConfigWfas::p = 1;
int ConfigWfas::n_threads = 1;
bool ConfigWfas::no_proj = false;

bool ConfigWfas::output_Q = false;
bool ConfigWfas::output_R = false;
bool ConfigWfas::output_N = false;
bool ConfigWfas::output_B = false;
bool ConfigWfas::output_N_Ext = false;
bool ConfigWfas::output_N_Fix = false;
bool ConfigWfas::output_N_Tmo = false;
bool ConfigWfas::output_Dist = true;

std::string ConfigWfas::initial_distribution_csv = "";
std::string ConfigWfas::path_output_Q = "output_Q.csv";
std::string ConfigWfas::path_output_R = "output_R.csv";
std::string ConfigWfas::path_output_N = "output_N.csv";
std::string ConfigWfas::path_output_B = "output_B.csv";
std::string ConfigWfas::path_output_N_Ext = "output_N_Ext.csv";
std::string ConfigWfas::path_output_N_Fix = "output_N_Fix.csv";
std::string ConfigWfas::path_output_N_Tmo = "output_N_Tmo.csv";
std::string ConfigWfas::path_output_Dist = "output_Dist.csv";

bool ConfigWfas::force = false;
bool ConfigWfas::verbose = false;
std::string ConfigWfas::error = "";
int ConfigWfas::num_comp = 1;
