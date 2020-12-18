#include "configWfafs.h"

using namespace wfes::config;

void ConfigWfafs::saveConfigWfafs() {
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/");

    QDir dir;
    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Wfafs.cfg"));

    file.open(QIODevice::WriteOnly);

    QTextStream outStream(&file);

    outStream << "Library: " << QString::fromStdString(ConfigWfafs::library) << "\n";
    outStream << "ViennaCL Solver: " << QString::fromStdString(ConfigWfafs::vienna_solver) << "\n";

    outStream << "Tail Truncation Weight (a): " << ConfigWfafs::a << "\n";
    outStream << "Initial number of alleles (p): " << ConfigWfafs::p << "\n";
    outStream << "Number of Threads (t): " << ConfigWfafs::n_threads << "\n";
    outStream << "No proj: " << (ConfigWfafs::no_proj ? QString("true") : QString("false")) << "\n";
    outStream << "Initial Distribution Path (I): " << QString::fromStdString(ConfigWfafs::initial_distribution_csv) << "\n";

    outStream << "Output Q: " << (ConfigWfafs::output_Q ? QString("true") : QString("false")) << "\n";
    outStream << "Output R: " << (ConfigWfafs::output_R ? QString("true") : QString("false")) << "\n";
    outStream << "Output N: " << (ConfigWfafs::output_N ? QString("true") : QString("false")) << "\n";
    outStream << "Output B: " << (ConfigWfafs::output_B ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Ext.: " << (ConfigWfafs::output_N_Ext ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Fix.: " << (ConfigWfafs::output_N_Fix ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Tmo.: " << (ConfigWfafs::output_N_Tmo ? QString("true") : QString("false")) << "\n";
    outStream << "Output Dist.: " << (ConfigWfafs::output_Dist ? QString("true") : QString("false")) << "\n";
    outStream << "Force: " << (ConfigWfafs::force ? QString("true") : QString("false")) << "\n";

    outStream << "Num. Comps.: " << ConfigWfafs::num_comp << "\n";

    outStream << "Population Size (N): ";
    for(int i = 0; i < ConfigWfafs::num_comp - 1; i++) {
        outStream << ConfigWfafs::N[i] << "; ";
    }
    outStream << ConfigWfafs::N[ConfigWfafs::num_comp - 1] << "\n";

    outStream << "Number of generations (G): ";
    for(int i = 0; i < ConfigWfafs::num_comp - 1; i++) {
        outStream << ConfigWfafs::G[i] << "; ";
    }
    outStream << ConfigWfafs::G[ConfigWfafs::num_comp - 1] << "\n";

    outStream << "Approximating (down) factor for each population size (f): ";
    for(int i = 0; i < ConfigWfafs::num_comp - 1; i++) {
        outStream << ConfigWfafs::f[i] << "; ";
    }
    outStream << ConfigWfafs::f[ConfigWfafs::num_comp - 1] << "\n";

    if(wfes::controllers::GlobalConfiguration::populationScaled) {
        outStream << "Backward Mutation Rates (u): ";
        for(int i = 0; i < ConfigWfafs::num_comp - 1; i++) {
            outStream << ConfigWfafs::u[i] / (4 * ConfigWfafs::N[i]) << "; ";
        }
        outStream << ConfigWfafs::u[ConfigWfafs::num_comp - 1] / (4 * ConfigWfafs::N[ConfigWfafs::num_comp - 1]) << "\n";

        outStream << "Forward Mutation Rates (v): ";
        for(int i = 0; i < ConfigWfafs::num_comp - 1; i++) {
            outStream << ConfigWfafs::v[i] / (4 * ConfigWfafs::N[i]) << "; ";
        }
        outStream << ConfigWfafs::v[ConfigWfafs::num_comp - 1] / (4 * ConfigWfafs::N[ConfigWfafs::num_comp - 1]) << "\n";

        outStream << "Individial selection coefficient (s): ";
        for(int i = 0; i < ConfigWfafs::num_comp - 1; i++) {
            outStream << ConfigWfafs::s[i] / (2 * ConfigWfafs::N[i])<< "; ";
        }
        outStream << ConfigWfafs::s[ConfigWfafs::num_comp - 1] / (2 * ConfigWfafs::N[ConfigWfafs::num_comp - 1]) << "\n";
    } else {
        outStream << "Backward Mutation Rates (u): ";
        for(int i = 0; i < ConfigWfafs::num_comp - 1; i++) {
            outStream << ConfigWfafs::u[i] << "; ";
        }
        outStream << ConfigWfafs::u[ConfigWfafs::num_comp - 1] << "\n";

        outStream << "Forward Mutation Rates (v): ";
        for(int i = 0; i < ConfigWfafs::num_comp - 1; i++) {
            outStream << ConfigWfafs::v[i] << "; ";
        }
        outStream << ConfigWfafs::v[ConfigWfafs::num_comp - 1] << "\n";

        outStream << "Individial selection coefficient (s): ";
        for(int i = 0; i < ConfigWfafs::num_comp - 1; i++) {
            outStream << ConfigWfafs::s[i] << "; ";
        }
        outStream << ConfigWfafs::s[ConfigWfafs::num_comp - 1] << "\n";
    }





    outStream << "Individial dominance coefficient (h): ";
    for(int i = 0; i < ConfigWfafs::num_comp - 1; i++) {
        outStream << ConfigWfafs::h[i] << "; ";
    }
    outStream << ConfigWfafs::h[ConfigWfafs::num_comp - 1] << "\n";


    file.close();
}

void ConfigWfafs::loadConfigWfafs() {
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/" + "Wfafs.cfg");

    QFile file(outputPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        processLine(line);
    }
}

void ConfigWfafs::processLine(QString line) {
    QStringList splitted = line.split(": ");
    if(splitted.at(0).compare("Library") == 0) {
        ConfigWfafs::library = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("ViennaCL Solver") == 0) {
        ConfigWfafs::vienna_solver = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Tail Truncation Weight (a)") == 0) {
        ConfigWfafs::a = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Initial number of alleles (p)") == 0) {
        ConfigWfafs::p = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Number of Threads (t)") == 0) {
        ConfigWfafs::n_threads = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("No proj") == 0) {
        ConfigWfafs::no_proj = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Initial Distribution Path (I)") == 0) {
        ConfigWfafs::initial_distribution_csv = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Output Q") == 0) {
        ConfigWfafs::output_Q = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output R") == 0) {
        ConfigWfafs::output_R = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N") == 0) {
        ConfigWfafs::output_N = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output B") == 0) {
        ConfigWfafs::output_B = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Ext.") == 0) {
        ConfigWfafs::output_N_Ext = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Fix.") == 0) {
        ConfigWfafs::output_N_Fix = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Tmo.") == 0) {
        ConfigWfafs::output_N_Tmo = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output Dist.") == 0) {
        ConfigWfafs::output_Dist = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Force") == 0) {
        ConfigWfafs::force = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Num. Comps.") == 0) {
        ConfigWfafs::num_comp = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Population Size (N)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        lvec newN(values.size());
        for(int i = 0; i < values.size(); i++) {
            newN(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafs::N = newN;
    } else if(splitted.at(0).compare("Number of generations (G)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        lvec newG(values.size());
        for(int i = 0; i < values.size(); i++) {
            newG(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafs::G = newG;
    } else if(splitted.at(0).compare("Approximating (down) factor for each population size (f)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newf(values.size());
        for(int i = 0; i < values.size(); i++) {
            newf(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafs::f = newf;
    } else if(splitted.at(0).compare("Individial selection coefficient (s)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec news(values.size());
        for(int i = 0; i < values.size(); i++) {
            news(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafs::s = news;
    } else if(splitted.at(0).compare("Individial dominance coefficient (h)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newh(values.size());
        for(int i = 0; i < values.size(); i++) {
            newh(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafs::h = newh;
    } else if(splitted.at(0).compare("Backward Mutation Rates (u)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newu(values.size());
        for(int i = 0; i < values.size(); i++) {
            newu(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafs::u = newu;
    } else if(splitted.at(0).compare("Forward Mutation Rates (v)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newv(values.size());
        for(int i = 0; i < values.size(); i++) {
            newv(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfafs::v = newv;
    }
}


////////////////////////////////
// Static initializations here//
////////////////////////////////

lvec ConfigWfafs::N = [] {
    lvec tmp(1);
    tmp << 100;
    return tmp;
}();

lvec ConfigWfafs::G = [] {
    lvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfafs::f = [] {
    dvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfafs::u = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfafs::v = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfafs::s = [] {
    dvec tmp(1);
    tmp << 0;
    return tmp;
}();

dvec ConfigWfafs::h = [] {
    dvec tmp(1);
    tmp << 0.5;
    return tmp;
}();

std::string ConfigWfafs::library = "Pardiso";
std::string ConfigWfafs::vienna_solver = "BicGStab";

double ConfigWfafs::a = 1e-20;
int ConfigWfafs::p = 0;
int ConfigWfafs::n_threads = 1;
bool ConfigWfafs::no_proj = false;

bool ConfigWfafs::output_Q = false;
bool ConfigWfafs::output_R = false;
bool ConfigWfafs::output_N = false;
bool ConfigWfafs::output_B = false;
bool ConfigWfafs::output_N_Ext = false;
bool ConfigWfafs::output_N_Fix = false;
bool ConfigWfafs::output_N_Tmo = false;
bool ConfigWfafs::output_Dist = true;

std::string ConfigWfafs::initial_distribution_csv = "";
std::string ConfigWfafs::path_output_Q = "output_Q.csv";
std::string ConfigWfafs::path_output_R = "output_R.csv";
std::string ConfigWfafs::path_output_N = "output_N.csv";
std::string ConfigWfafs::path_output_B = "output_B.csv";
std::string ConfigWfafs::path_output_N_Ext = "output_N_Ext.csv";
std::string ConfigWfafs::path_output_N_Fix = "output_N_Fix.csv";
std::string ConfigWfafs::path_output_N_Tmo = "output_N_Tmo.csv";
std::string ConfigWfafs::path_output_Dist = "output_Dist.csv";

bool ConfigWfafs::force = false;
int ConfigWfafs::num_comp = 1;
