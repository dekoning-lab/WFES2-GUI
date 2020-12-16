#include "configWfesSwitching.h"

using namespace wfes::config;

int ConfigWfesSwitching::ModelTypeWfesSwitchingToInt(ModelTypeWfesSwitching modelType) {
    switch(modelType){
        case ModelTypeWfesSwitching::FIXATION:
            return 1;
        case ModelTypeWfesSwitching::ABSORPTION:
            return 2;
        case ModelTypeWfesSwitching::NONE:
        default:
            return 0;
    }
}

void ConfigWfesSwitching::saveConfigWfesSwitching() {
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/");

    QDir dir;
    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Wfes_Switching.cfg"));
    file.open(QIODevice::WriteOnly);

    QTextStream outStream(&file);

    outStream << "Library: " << QString::fromStdString(ConfigWfesSwitching::library) << "\n";
    outStream << "ViennaCL Solver: " << QString::fromStdString(ConfigWfesSwitching::vienna_solver) << "\n";
    outStream << "Model Type: " << QString::fromStdString(ModelTypeWfesSwitchingNames[ModelTypeWfesSwitchingToInt(ConfigWfesSwitching::modelType)]) << "\n";

    outStream << "Tail Truncation Weight (a): " << ConfigWfesSwitching::a << "\n";
    outStream << "Integration Cutoff (c): " << ConfigWfesSwitching::c << "\n";
    outStream << "Number of Threads (t): " << ConfigWfesSwitching::n_threads << "\n";

    outStream << "Output I: " << (ConfigWfesSwitching::output_I ? QString("true") : QString("false")) << "\n";
    outStream << "Output Q: " << (ConfigWfesSwitching::output_Q ? QString("true") : QString("false")) << "\n";
    outStream << "Output R: " << (ConfigWfesSwitching::output_R ? QString("true") : QString("false")) << "\n";
    outStream << "Output N: " << (ConfigWfesSwitching::output_N ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Ext.: " << (ConfigWfesSwitching::output_N_Ext ? QString("true") : QString("false")) << "\n";
    outStream << "Output N Fix.: " << (ConfigWfesSwitching::output_N_Fix ? QString("true") : QString("false")) << "\n";
    outStream << "Output B: " << (ConfigWfesSwitching::output_B ? QString("true") : QString("false")) << "\n";
    outStream << "Output Res: " << (ConfigWfesSwitching::output_Res ? QString("true") : QString("false")) << "\n";
    outStream << "Force: " << (ConfigWfesSwitching::force ? QString("true") : QString("false")) << "\n";

    outStream << "Initial Distribution Path (I): " << QString::fromStdString(ConfigWfesSwitching::initial_distribution_csv) << "\n";

    outStream << "Num. Comps.: " << ConfigWfesSwitching::num_comp << "\n";

    outStream << "Population Size (N): ";
    for(int i = 0; i < ConfigWfesSwitching::num_comp - 1; i++) {
        outStream << ConfigWfesSwitching::N[i] << "; ";
    }
    outStream << ConfigWfesSwitching::N[ConfigWfesSwitching::num_comp - 1] << "\n";

    outStream << "Starting probabilities (p): ";
    for(int i = 0; i < ConfigWfesSwitching::num_comp - 1; i++) {
        outStream << ConfigWfesSwitching::p[i] << "; ";
    }
    outStream << ConfigWfesSwitching::p[ConfigWfesSwitching::num_comp - 1] << "\n";

    outStream << "Transition probability matrix between the WF component models (r): ";
    for(int i = 0; i < ConfigWfesSwitching::num_comp; i++) {
        for(int j = 0; j < ConfigWfesSwitching::num_comp - 1; j++) {
            outStream << ConfigWfesSwitching::r(i, j) << "; ";
        }
        outStream << ConfigWfesSwitching::r(i, ConfigWfesSwitching::num_comp - 1);
        if(i != ConfigWfesSwitching::num_comp - 1)
            outStream << " | ";
        else
            outStream << "\n";
    }

    if(wfes::controllers::GlobalConfiguration::populationScaled) {
        outStream << "Backward Mutation Rates (u): ";
        for(int i = 0; i < ConfigWfesSwitching::num_comp - 1; i++) {
            outStream << ConfigWfesSwitching::u[i] / (4 * ConfigWfesSwitching::N[i])  << "; ";
        }
        outStream << ConfigWfesSwitching::u[ConfigWfesSwitching::num_comp - 1] / (4 * ConfigWfesSwitching::N[ConfigWfesSwitching::num_comp - 1]) << "\n";
    
        outStream << "Forward Mutation Rates (v): ";
        for(int i = 0; i < ConfigWfesSwitching::num_comp - 1; i++) {
            outStream << ConfigWfesSwitching::v[i] / (4 * ConfigWfesSwitching::N[i]) << "; ";
        }
        outStream << ConfigWfesSwitching::v[ConfigWfesSwitching::num_comp - 1] / (4 * ConfigWfesSwitching::N[ConfigWfesSwitching::num_comp - 1]) << "\n";

        outStream << "Individial selection coefficient (s): ";
        for(int i = 0; i < ConfigWfesSwitching::num_comp - 1; i++) {
            outStream << ConfigWfesSwitching::s[i] / (2 * ConfigWfesSwitching::N[i]) << "; ";
        }
        outStream << ConfigWfesSwitching::s[ConfigWfesSwitching::num_comp - 1] / (2 * ConfigWfesSwitching::N[ConfigWfesSwitching::num_comp - 1]) << "\n";
    } else {
        outStream << "Backward Mutation Rates (u): ";
        for(int i = 0; i < ConfigWfesSwitching::num_comp - 1; i++) {
            outStream << ConfigWfesSwitching::u[i] << "; ";
        }
        outStream << ConfigWfesSwitching::u[ConfigWfesSwitching::num_comp - 1] << "\n";

        outStream << "Forward Mutation Rates (v): ";
        for(int i = 0; i < ConfigWfesSwitching::num_comp - 1; i++) {
            outStream << ConfigWfesSwitching::v[i] << "; ";
        }
        outStream << ConfigWfesSwitching::v[ConfigWfesSwitching::num_comp - 1] << "\n";

        outStream << "Individial selection coefficient (s): ";
        for(int i = 0; i < ConfigWfesSwitching::num_comp - 1; i++) {
            outStream << ConfigWfesSwitching::s[i] << "; ";
        }
        outStream << ConfigWfesSwitching::s[ConfigWfesSwitching::num_comp - 1] << "\n";
    }

    outStream << "Individial dominance coefficient (h): ";
    for(int i = 0; i < ConfigWfesSwitching::num_comp - 1; i++) {
        outStream << ConfigWfesSwitching::h[i] << "; ";
    }
    outStream << ConfigWfesSwitching::h[ConfigWfesSwitching::num_comp - 1] << "\n";

    file.close();

}

void ConfigWfesSwitching::loadConfigWfesSwitching() {
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/" + "Wfes_Switching.cfg");

    QFile file(outputPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        processLine(line);
    }
}

void ConfigWfesSwitching::processLine(QString line) {
    QStringList splitted = line.split(": ");
    if(splitted.at(0).compare("Library") == 0) {
        ConfigWfesSwitching::library = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("ViennaCL Solver") == 0) {
        ConfigWfesSwitching::vienna_solver = splitted.at(1).toStdString();
    } else if(splitted.at(0).compare("Model Type") == 0) {
        if(splitted.at(1) == "None")
            ConfigWfesSwitching::modelType = ModelTypeWfesSwitching::NONE;
        else if(splitted.at(1) == "Absorption")
            ConfigWfesSwitching::modelType = ModelTypeWfesSwitching::ABSORPTION;
        else if(splitted.at(1) == "Fixation")
            ConfigWfesSwitching::modelType = ModelTypeWfesSwitching::FIXATION;
    } else if(splitted.at(0).compare("Tail Truncation Weight (a)") == 0) {
        ConfigWfesSwitching::a = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Integration Cutoff (c)") == 0) {
        ConfigWfesSwitching::c = std::stod(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Number of Threads (t)") == 0) {
        ConfigWfesSwitching::n_threads = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Output I") == 0) {
        ConfigWfesSwitching::output_I = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output Q") == 0) {
        ConfigWfesSwitching::output_Q = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output R") == 0) {
        ConfigWfesSwitching::output_R = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N") == 0) {
        ConfigWfesSwitching::output_N = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Ext.") == 0) {
        ConfigWfesSwitching::output_N_Ext = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output N Fix.") == 0) {
        ConfigWfesSwitching::output_N_Fix = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output B") == 0) {
        ConfigWfesSwitching::output_B = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Output Res") == 0) {
        ConfigWfesSwitching::output_Res = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Force") == 0) {
        ConfigWfesSwitching::force = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Num. Comps.") == 0) {
        ConfigWfesSwitching::num_comp = std::stoi(splitted.at(1).toStdString());
    } else if(splitted.at(0).compare("Initial Distribution Path (I)") == 0) {
        ConfigWfesSwitching::initial_distribution_csv = splitted.at(1).toStdString();
    }else if(splitted.at(0).compare("Population Size (N)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        lvec newN(values.size());
        for(int i = 0; i < values.size(); i++) {
            newN(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSwitching::N = newN;
    } else if(splitted.at(0).compare("Starting probabilities (p)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newp(values.size());
        for(int i = 0; i < values.size(); i++) {
            newp(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSwitching::p = newp;
    } else if(splitted.at(0).compare("Transition probability matrix between the WF component models (r)") == 0) {
        QStringList vectors = splitted.at(1).split(" | ");
        dmat newr(vectors.size(), vectors.size());
        for(int i = 0; i < vectors.size(); i++) {
            QStringList values = vectors.at(i).split("; ");
            dvec vec(values.size());
            for(int j = 0; j < values.size(); j++) {
                newr(i, j) = std::stod(values.at(j).toStdString());
            }
        }
        ConfigWfesSwitching::r = newr;
    } else if(splitted.at(0).compare("Individial selection coefficient (s)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec news(values.size());
        for(int i = 0; i < values.size(); i++) {
            news(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSwitching::s = news;
    } else if(splitted.at(0).compare("Individial dominance coefficient (h)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newh(values.size());
        for(int i = 0; i < values.size(); i++) {
            newh(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSwitching::h = newh;
    } else if(splitted.at(0).compare("Backward Mutation Rates (u)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newu(values.size());
        for(int i = 0; i < values.size(); i++) {
            newu(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSwitching::u = newu;
    } else if(splitted.at(0).compare("Forward Mutation Rates (v)") == 0) {
        QStringList values = splitted.at(1).split("; ");
        dvec newv(values.size());
        for(int i = 0; i < values.size(); i++) {
            newv(i) = std::stod(values.at(i).toStdString());
        }
        ConfigWfesSwitching::v = newv;
    }
}


////////////////////////////////
// Static initializations here//
////////////////////////////////

lvec ConfigWfesSwitching::N = [] {
    lvec tmp(1);
    tmp << 100;
    return tmp;
}();

dmat ConfigWfesSwitching::r  = [] {
    dmat tmp(1, 1);
    tmp << 1;
    return tmp;
}();


dvec ConfigWfesSwitching::p = [] {
    dvec tmp(1);
    tmp << 1;
    return tmp;
}();

dvec ConfigWfesSwitching::u = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfesSwitching::v = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfesSwitching::s = [] {
    dvec tmp(1);
    tmp << 0;
    return tmp;
}();

dvec ConfigWfesSwitching::h = [] {
    dvec tmp(1);
    tmp << 0.5;
    return tmp;
}();

ModelTypeWfesSwitching ConfigWfesSwitching::modelType = ModelTypeWfesSwitching::ABSORPTION;

std::string ConfigWfesSwitching::library = "Pardiso";
std::string ConfigWfesSwitching::vienna_solver = "BicGStab";

double ConfigWfesSwitching::a = 1e-20;
double ConfigWfesSwitching::c = 1e-10;
int ConfigWfesSwitching::n_threads = 1;


bool ConfigWfesSwitching::output_Q = false;
bool ConfigWfesSwitching::output_R = false;
bool ConfigWfesSwitching::output_N = false;
bool ConfigWfesSwitching::output_B = false;
bool ConfigWfesSwitching::output_I = false;
bool ConfigWfesSwitching::output_N_Fix = false;
bool ConfigWfesSwitching::output_N_Ext = false;
bool ConfigWfesSwitching::output_Res = true;

std::string ConfigWfesSwitching::initial_distribution_csv = "";
std::string ConfigWfesSwitching::path_output_Q = "output_Q.csv";
std::string ConfigWfesSwitching::path_output_R = "output_R.csv";
std::string ConfigWfesSwitching::path_output_N = "output_N.csv";
std::string ConfigWfesSwitching::path_output_B = "output_B.csv";
std::string ConfigWfesSwitching::path_output_I = "output_I.csv";
std::string ConfigWfesSwitching::path_output_N_Ext = "output_N_Ext.csv";
std::string ConfigWfesSwitching::path_output_N_Fix = "output_N_Fix.csv";
std::string ConfigWfesSwitching::path_output_Res = "output_Res.csv";

bool ConfigWfesSwitching::force = false;
int ConfigWfesSwitching::num_comp = 1;
