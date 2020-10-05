#include "inputControllerWfesSingle.h"

using namespace wfes::controllers;

InputController::InputController(QObject* parent): QObject(parent){
    emit input_changed();
}

InputController::~InputController(){}

QString InputController::get_n() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::population_size);

    if((boost::math::isnan)(wfes::config::Config::population_size))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_n(QString n) const
{
    std::string n_str = n.toStdString();
    try {
        double n_d = boost::lexical_cast<double>(n_str);
        wfes::config::Config::population_size = n_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(n_str.compare("") == 0) {
            errorMessage = "The field 'Population' (N) is empty." + n_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Population' (N): " + n_str + "\n";
        }
        wfes::config::Config::error += errorMessage;
    }
}

QString InputController::get_a() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::a);

    if((boost::math::isnan)(wfes::config::Config::a))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_a(QString a) const
{
    std::string a_str = a.toStdString();
    try {
        double a_d = boost::lexical_cast<double>(a_str);
        wfes::config::Config::a = a_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(a_str.compare("") == 0) {
            errorMessage = "The field 'Tail Truncation Weight' (a) is empty." + a_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Tail Truncation Weight' (a): " + a_str + "\n";
        }
        wfes::config::Config::error += errorMessage;
    }
}

QString InputController::get_p() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::starting_copies);

    if((boost::math::isnan)(wfes::config::Config::starting_copies))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_p(QString p) const
{
    std::string p_str = p.toStdString();
    try {
        double p_d = boost::lexical_cast<double>(p_str);
        wfes::config::Config::starting_copies = p_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(p_str.compare("") == 0) {
            errorMessage = "The field 'Starting Copies' (p) is empty." + p_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Starting Copies' (p): " + p_str + "\n";
        }
        wfes::config::Config::error += errorMessage;
    }
}

QString InputController::get_c() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::integration_cutoff);

    if((boost::math::isnan)(wfes::config::Config::integration_cutoff))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_c(QString c) const
{
    std::string c_str = c.toStdString();
    try {
        double c_d = boost::lexical_cast<double>(c_str);
        wfes::config::Config::integration_cutoff = c_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(c_str.compare("") == 0) {
            errorMessage = "The field 'Integration Cutoff' (c) is empty." + c_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Integration Cutoff' (c): " + c_str + "\n";
        }
        wfes::config::Config::error += errorMessage;
    }
}

QString InputController::get_x() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::observed_copies);

    if((boost::math::isnan)(wfes::config::Config::observed_copies))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_x(QString x) const
{
    std::string x_str = x.toStdString();
    try {
        double x_d = boost::lexical_cast<double>(x_str);
        wfes::config::Config::observed_copies = x_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(x_str.compare("") == 0) {
            errorMessage = "The field 'Observed Copies' (x) is empty." + x_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Observed Copies' (x): " + x_str + "\n";
        }
        wfes::config::Config::error += errorMessage;
    }
}

QString InputController::get_k() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::odds_ratio);

    if((boost::math::isnan)(wfes::config::Config::odds_ratio))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_k(QString k) const
{
    std::string k_str = k.toStdString();
    try {
        double k_d = boost::lexical_cast<double>(k_str);
        wfes::config::Config::odds_ratio = k_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(k_str.compare("") == 0) {
            errorMessage = "The field 'Odds Ratio' (k) is empty." + k_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Odds Ratio' (k): " + k_str + "\n";
        }
        wfes::config::Config::error += errorMessage;
    }
}

QString InputController::get_u() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::u);

    if((boost::math::isnan)(wfes::config::Config::u))
        return "Error";
    else
        return QString::fromStdString(fmt.str());

}

void InputController::set_u(QString u) const
{
    std::string u_str = u.toStdString();
    try {
        double u_d = boost::lexical_cast<double>(u_str);
        wfes::config::Config::u = u_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(u_str.compare("") == 0) {
            errorMessage = "The field 'Backward Mutation Rate' (u) is empty." + u_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Backward Mutation Rate' (u): " + u_str + "\n";
        }
        wfes::config::Config::error += errorMessage;
    }
}

QString InputController::get_v() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::v);

    if((boost::math::isnan)(wfes::config::Config::v))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_v(QString v) const
{
    std::string v_str = v.toStdString();
    try {
        double v_d = boost::lexical_cast<double>(v_str);
        wfes::config::Config::v = v_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(v_str.compare("") == 0) {
            errorMessage = "The field 'Forward Mutation Rate' (v) is empty." + v_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Forward Mutation Rate' (v): " + v_str + "\n";
        }
        wfes::config::Config::error += errorMessage;
    }
}

QString InputController::get_s() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::s);

    if((boost::math::isnan)(wfes::config::Config::s))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_s(QString s) const
{
    std::string s_str = s.toStdString();
    try {
        double s_d = boost::lexical_cast<double>(s_str);
        wfes::config::Config::s = s_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(s_str.compare("") == 0) {
            errorMessage = "The field 'Selection Coefficient' (s) is empty." + s_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Selection Coefficient' (s): " + s_str + "\n";
        }
        wfes::config::Config::error += errorMessage;
    }
}

QString InputController::get_h() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::h);

    if((boost::math::isnan)(wfes::config::Config::h))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_h(QString h) const
{
    std::string h_str = h.toStdString();
    try {
        double h_d = boost::lexical_cast<double>(h_str);
        wfes::config::Config::h = h_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(h_str.compare("") == 0) {
            errorMessage = "The field 'Dominance Coefficient' (h) is empty." + h_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Dominance Coefficient' (h): " + h_str + "\n";
        }
        wfes::config::Config::error += errorMessage;
    }
}

QString InputController::get_t() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::n_threads);

    if((boost::math::isnan)(wfes::config::Config::n_threads))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_t(QString t) const
{
    std::string t_str = t.toStdString();
    try {
        double t_d = boost::lexical_cast<double>(t_str);
        wfes::config::Config::n_threads = t_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(t_str.compare("") == 0) {
            errorMessage = "The field 'Number of Threads' (t) is empty." + t_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Number of Threads' (t): " + t_str + "\n";
        }
        wfes::config::Config::error += errorMessage;
    }
}

bool InputController::get_output_Q() const
{
    return wfes::config::Config::output_Q;
}

void InputController::set_output_Q(bool output_Q) const
{
    wfes::config::Config::output_Q = output_Q;
}

bool InputController::get_output_R() const
{
    return wfes::config::Config::output_R;
}

void InputController::set_output_R(bool output_R) const
{
    wfes::config::Config::output_R = output_R;
}

bool InputController::get_output_N() const
{
    return wfes::config::Config::output_N;
}

void InputController::set_output_N(bool output_N) const
{
    wfes::config::Config::output_N = output_N;
}

bool InputController::get_output_NExt() const
{
    return wfes::config::Config::output_N_ext;
}

void InputController::set_output_NExt(bool output_NExt) const
{
    wfes::config::Config::output_N_ext = output_NExt;
}

bool InputController::get_output_NFix() const
{
    return wfes::config::Config::output_N_fix;
}

void InputController::set_output_NFix(bool output_NFix) const
{
    wfes::config::Config::output_N_fix = output_NFix;
}

bool InputController::get_output_B() const
{
    return wfes::config::Config::output_B;
}

void InputController::set_output_B(bool output_B) const
{
    wfes::config::Config::output_B = output_B;
}

bool InputController::get_output_I() const
{
    return wfes::config::Config::output_I;
}

void InputController::set_output_I(bool output_I) const
{
    wfes::config::Config::output_I = output_I;
}

bool InputController::get_output_E() const
{
    return wfes::config::Config::output_E;
}

void InputController::set_output_E(bool output_E) const
{
    wfes::config::Config::output_E = output_E;
}

bool InputController::get_output_V() const
{
    return wfes::config::Config::output_V;
}

void InputController::set_output_V(bool output_V) const
{
    wfes::config::Config::output_V = output_V;
}

bool InputController::get_output_Res() const
{
    return wfes::config::Config::output_Res;
}

void InputController::set_output_Res(bool output_Res) const
{
    wfes::config::Config::output_Res = output_Res;
}

bool InputController::get_m() const
{
    return wfes::config::Config::no_rem;
}

void InputController::set_m(bool m) const
{
    wfes::config::Config::no_rem = m;
}

bool InputController::get_force() const
{
    return wfes::config::Config::force;
}

void InputController::set_force(bool force) const
{
    wfes::config::Config::force = force;
}

QString InputController::get_model_type() const
{
    return wfes::config::ModelTypeNames[wfes::config::Config::modelType];
}

void InputController::set_model_type(QString model_type) const
{
    if(model_type.compare(wfes::config::ModelTypeNames[wfes::config::ModelType::NONE]) == 0)
        wfes::config::Config::modelType = wfes::config::ModelType::NONE;
    else if (model_type.compare(wfes::config::ModelTypeNames[wfes::config::ModelType::FIXATION]) == 0)
        wfes::config::Config::modelType = wfes::config::ModelType::FIXATION;
    else if (model_type.compare(wfes::config::ModelTypeNames[wfes::config::ModelType::ABSORPTION]) == 0)
        wfes::config::Config::modelType = wfes::config::ModelType::ABSORPTION;
    else if (model_type.compare(wfes::config::ModelTypeNames[wfes::config::ModelType::ESTABLISHMENT]) == 0)
        wfes::config::Config::modelType = wfes::config::ModelType::ESTABLISHMENT;
    else if (model_type.compare(wfes::config::ModelTypeNames[wfes::config::ModelType::FUNDAMENTAL]) == 0)
        wfes::config::Config::modelType = wfes::config::ModelType::FUNDAMENTAL;
    else if (model_type.compare(wfes::config::ModelTypeNames[wfes::config::ModelType::EQUILIBRIUM]) == 0)
        wfes::config::Config::modelType = wfes::config::ModelType::EQUILIBRIUM;
    else if (model_type.compare(wfes::config::ModelTypeNames[wfes::config::ModelType::NON_ABSORBING]) == 0)
        wfes::config::Config::modelType = wfes::config::ModelType::NON_ABSORBING;
    else if (model_type.compare(wfes::config::ModelTypeNames[wfes::config::ModelType::ALLELE_AGE]) == 0)
        wfes::config::Config::modelType = wfes::config::ModelType::ALLELE_AGE;

}

QString InputController::get_library() const
{
    return QString::fromStdString(wfes::config::Config::library);
}

void InputController::set_library(QString library) const
{
    wfes::config::Config::library = library.toStdString();
}

QString InputController::get_solver() const
{
    return QString::fromStdString(wfes::config::Config::vienna_solver);
}

void InputController::set_solver(QString solver) const
{
    wfes::config::Config::vienna_solver = solver.toStdString();
}

QString InputController::get_initial_distribution_path() const
{
    return QString::fromStdString(wfes::config::Config::initial_distribution_csv);
}

void InputController::set_initial_distribution_path(QString initial_distribution_path) const
{
    wfes::config::Config::initial_distribution_csv = initial_distribution_path.toStdString();
}





