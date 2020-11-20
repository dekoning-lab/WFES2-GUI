#include "configWfesSequential.h"

using namespace wfes::config;

void ConfigWfesSequential::saveConfigWfesSequential() {
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/");

    QDir dir;
    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Wes_Sequential.cfg"));
    file.open(QIODevice::WriteOnly);

    QTextStream outStream(&file);

    outStream << "Library: " << QString::fromStdString(ConfigWfesSequential::library) << "\n";
    outStream << "ViennaCL Solver: " << QString::fromStdString(ConfigWfesSequential::vienna_solver) << "\n";

    outStream << "Tail Truncation Weight (a): " << ConfigWfesSequential::a << "\n";
    outStream << "Integration Cutoff (c): " << ConfigWfesSequential::c << "\n";
    outStream << "Number of Threads (t): " << ConfigWfesSequential::n_threads << "\n";

    outStream << "Output Q: " << (ConfigWfesSequential::output_Q ? QString("true") : QString("false")) << "\n";
    outStream << "Output R: " << (ConfigWfesSequential::output_R ? QString("true") : QString("false")) << "\n";
    outStream << "Output N: " << (ConfigWfesSequential::output_N ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Ext.: " << (ConfigWfesSequential::output_N_Ext ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Fix.: " << (ConfigWfesSequential::output_N_Fix ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Tmo.: " << (ConfigWfesSequential::output_N_Tmo ? QString("true") : QString("false")) << "\n";
    outStream << "Output B: " << (ConfigWfesSequential::output_B ? QString("true") : QString("false")) << "\n";
    outStream << "Output Res: " << (ConfigWfesSequential::output_Res ? QString("true") : QString("false")) << "\n";
    outStream << "Force: " << (ConfigWfesSequential::force ? QString("true") : QString("false")) << "\n";

    outStream << "Initial Distribution Path (I): " << QString::fromStdString(ConfigWfesSequential::initial_distribution_csv) << "\n";

    outStream << "Num. Comps.: " << ConfigWfesSequential::num_comp << "\n";

    outStream << "Population Size (N): ";
    for(int i = 0; i < ConfigWfesSequential::num_comp - 1; i++) {
        outStream << ConfigWfesSequential::N[i] << "; ";
    }
    outStream << ConfigWfesSequential::N[ConfigWfesSequential::num_comp - 1] << "\n";

    outStream << "Expected time spent in each model (t): ";
    for(int i = 0; i < ConfigWfesSequential::num_comp - 1; i++) {
        outStream << ConfigWfesSequential::t[i] << "; ";
    }
    outStream << ConfigWfesSequential::t[ConfigWfesSequential::num_comp - 1] << "\n";

    outStream << "Starting probabilities (p): ";
    for(int i = 0; i < ConfigWfesSequential::num_comp - 1; i++) {
        outStream << ConfigWfesSequential::p[i] << "; ";
    }
    outStream << ConfigWfesSequential::p[ConfigWfesSequential::num_comp - 1] << "\n";

    outStream << "Individial selection coefficient (s): ";
    for(int i = 0; i < ConfigWfesSequential::num_comp - 1; i++) {
        outStream << ConfigWfesSequential::s[i] << "; ";
    }
    outStream << ConfigWfesSequential::s[ConfigWfesSequential::num_comp - 1] << "\n";

    outStream << "Individial dominance coefficient (h): ";
    for(int i = 0; i < ConfigWfesSequential::num_comp - 1; i++) {
        outStream << ConfigWfesSequential::h[i] << "; ";
    }
    outStream << ConfigWfesSequential::h[ConfigWfesSequential::num_comp - 1] << "\n";

    outStream << "Backward Mutation Rates (u): ";
    for(int i = 0; i < ConfigWfesSequential::num_comp - 1; i++) {
        outStream << ConfigWfesSequential::u[i] << "; ";
    }
    outStream << ConfigWfesSequential::u[ConfigWfesSequential::num_comp - 1] << "\n";

    outStream << "Forward Mutation Rates (v): ";
    for(int i = 0; i < ConfigWfesSequential::num_comp - 1; i++) {
        outStream << ConfigWfesSequential::v[i] << "; ";
    }
    outStream << ConfigWfesSequential::v[ConfigWfesSequential::num_comp - 1] << "\n";

    file.close();
}

void ConfigWfesSequential::loadConfigWfesSequential() {
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/" + "Wes_Sequential.cfg");

    QFile file(outputPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        processLine(line);
    }
}

void ConfigWfesSequential::processLine(QString line) {
    QStringList splitted = line.split(": ");
    if(splitted.at(0).compare("Library") == 0) {
        ConfigWfesSequential::library = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("ViennaCL Solver") == 0) {
        ConfigWfesSequential::vienna_solver = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Tail Truncation Weight (a)") == 0) {
        ConfigWfesSequential::a = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Integration Cutoff (c)") == 0) {
        ConfigWfesSequential::c = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Number of Threads (t)") == 0) {
        ConfigWfesSequential::n_threads = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Output I") == 0) {
        ConfigWfesSequential::output_I = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output Q") == 0) {
        ConfigWfesSequential::output_Q = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output R") == 0) {
        ConfigWfesSequential::output_R = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N") == 0) {
        ConfigWfesSequential::output_N = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Ext.") == 0) {
        ConfigWfesSequential::output_N_Ext = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Fix.") == 0) {
        ConfigWfesSequential::output_N_Fix = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Tmo.") == 0) {
        ConfigWfesSequential::output_N_Tmo = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output B") == 0) {
        ConfigWfesSequential::output_B = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output Res") == 0) {
        ConfigWfesSequential::output_Res = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Force") == 0) {
        ConfigWfesSequential::force = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Num. Comps.") == 0) {
        ConfigWfesSequential::num_comp = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Initial Distribution Path (I)") == 0) {
        ConfigWfesSequential::initial_distribution_csv = splitted.at(1).toStdString();
    }else if(splitted.at(0).compare("Population Size (N)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        lvec newN(values.size());
        for(int i = 0; i < values.size(); i++) {
            newN(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSequential::N = newN;
    } else if(splitted.at(0).compare("Expected time spent in each model (t)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newt(values.size());
        for(int i = 0; i < values.size(); i++) {
            newt(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSequential::t = newt;
    } else if(splitted.at(0).compare("Starting probabilities (p)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newp(values.size());
        for(int i = 0; i < values.size(); i++) {
            newp(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSequential::p = newp;
    } else if(splitted.at(0).compare("Individial selection coefficient (s)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec news(values.size());
        for(int i = 0; i < values.size(); i++) {
            news(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSequential::s = news;
    } else if(splitted.at(0).compare("Individial dominance coefficient (h)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newh(values.size());
        for(int i = 0; i < values.size(); i++) {
            newh(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSequential::h = newh;
    } else if(splitted.at(0).compare("Backward Mutation Rates (u)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newu(values.size());
        for(int i = 0; i < values.size(); i++) {
            newu(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSequential::u = newu;
    } else if(splitted.at(0).compare("Forward Mutation Rates (v)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newv(values.size());
        for(int i = 0; i < values.size(); i++) {
            newv(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSequential::v = newv;
    }
}


////////////////////////////////
// Static initializations here//
////////////////////////////////

lvec ConfigWfesSequential::N = [] {
    lvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfesSequential::t = [] {
    dvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfesSequential::p = [] {
    dvec tmp(1);
    tmp << 1;
    return tmp;
}();

dvec ConfigWfesSequential::u = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfesSequential::v = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfesSequential::s = [] {
    dvec tmp(1);
    tmp << 0;
    return tmp;
}();

dvec ConfigWfesSequential::h = [] {
    dvec tmp(1);
    tmp << 0.5;
    return tmp;
}();

std::string ConfigWfesSequential::library = "Pardiso";
std::string ConfigWfesSequential::vienna_solver = "BicGStab";

double ConfigWfesSequential::a = 1e-20;
double ConfigWfesSequential::c = 1e-10;
int ConfigWfesSequential::n_threads = 1;

bool ConfigWfesSequential::output_Q = false;
bool ConfigWfesSequential::output_R = false;
bool ConfigWfesSequential::output_N = false;
bool ConfigWfesSequential::output_B = false;
bool ConfigWfesSequential::output_I = false;
bool ConfigWfesSequential::output_N_Fix = false;
bool ConfigWfesSequential::output_N_Ext = false;
bool ConfigWfesSequential::output_N_Tmo = false;
bool ConfigWfesSequential::output_Res = true;

std::string ConfigWfesSequential::initial_distribution_csv = "";
std::string ConfigWfesSequential::path_output_Q = "output_Q.csv";
std::string ConfigWfesSequential::path_output_R = "output_R.csv";
std::string ConfigWfesSequential::path_output_N = "output_N.csv";
std::string ConfigWfesSequential::path_output_B = "output_B.csv";
std::string ConfigWfesSequential::path_output_I = "output_I.csv";
std::string ConfigWfesSequential::path_output_N_Ext = "output_N_Ext.csv";
std::string ConfigWfesSequential::path_output_N_Fix = "output_N_Fix.csv";
std::string ConfigWfesSequential::path_output_N_Tmo = "output_N_Tmo.csv";
std::string ConfigWfesSequential::path_output_Res = "output_Res.csv";

bool ConfigWfesSequential::force = false;
int ConfigWfesSequential::num_comp = 1;


