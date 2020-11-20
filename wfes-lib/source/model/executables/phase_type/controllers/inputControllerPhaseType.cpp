#include "inputControllerPhaseType.h"

using namespace wfes::controllers;
using namespace wfes::config;

InputControllerPhaseType::InputControllerPhaseType(QObject *parent): QObject(parent) {
    emit input_changed();
}

QString InputControllerPhaseType::get_n() const {
    boost::format fmt = boost::format(DPFS) % (ConfigPhaseType::population_size);

    if((boost::math::isnan)(ConfigPhaseType::population_size))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerPhaseType::set_n(QString n) const {
    std::string n_str = n.toStdString();

    double n_d = boost::lexical_cast<double>(n_str);
    ConfigPhaseType::population_size = n_d;
}

QString InputControllerPhaseType::get_a() const {
    boost::format fmt = boost::format(DPFS) % (ConfigPhaseType::a);

    if((boost::math::isnan)(ConfigPhaseType::a))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerPhaseType::set_a(QString a) const {
    std::string a_str = a.toStdString();

    double a_d = boost::lexical_cast<double>(a_str);
    ConfigPhaseType::a = a_d;
}

QString InputControllerPhaseType::get_c() const {
    boost::format fmt = boost::format(DPFS) % (ConfigPhaseType::integration_cutoff);

    if((boost::math::isnan)(ConfigPhaseType::integration_cutoff))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerPhaseType::set_c(QString c) const {
    std::string c_str = c.toStdString();

    double c_d = boost::lexical_cast<double>(c_str);
    ConfigPhaseType::integration_cutoff = c_d;
}

QString InputControllerPhaseType::get_k() const {
    boost::format fmt = boost::format(DPFS) % (ConfigPhaseType::k);

    if((boost::math::isnan)(ConfigPhaseType::k))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerPhaseType::set_k(QString k) const {
    std::string k_str = k.toStdString();

    double k_d = boost::lexical_cast<double>(k_str);
    ConfigPhaseType::k = k_d;

}

QString InputControllerPhaseType::get_u() const {
    boost::format fmt = boost::format(DPFS) % (ConfigPhaseType::u);

    if((boost::math::isnan)(ConfigPhaseType::u))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerPhaseType::set_u(QString u) const {
    std::string u_str = u.toStdString();

    double u_d = boost::lexical_cast<double>(u_str);
    ConfigPhaseType::u = u_d;

}

QString InputControllerPhaseType::get_v() const {
    boost::format fmt = boost::format(DPFS) % (ConfigPhaseType::v);

    if((boost::math::isnan)(ConfigPhaseType::v))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerPhaseType::set_v(QString v) const {
    std::string v_str = v.toStdString();

    double v_d = boost::lexical_cast<double>(v_str);
    ConfigPhaseType::v = v_d;

}

QString InputControllerPhaseType::get_s() const {
    boost::format fmt = boost::format(DPFS) % (ConfigPhaseType::s);

    if((boost::math::isnan)(ConfigPhaseType::s))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerPhaseType::set_s(QString s) const {
    std::string s_str = s.toStdString();

    double s_d = boost::lexical_cast<double>(s_str);
    ConfigPhaseType::s = s_d;

}

QString InputControllerPhaseType::get_h() const {
    boost::format fmt = boost::format(DPFS) % (ConfigPhaseType::h);

    if((boost::math::isnan)(ConfigPhaseType::h))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerPhaseType::set_h(QString h) const {
    std::string h_str = h.toStdString();

    double h_d = boost::lexical_cast<double>(h_str);
    ConfigPhaseType::h = h_d;

}

QString InputControllerPhaseType::get_m() const {
    boost::format fmt = boost::format(DPFS) % (ConfigPhaseType::max_t);

    if((boost::math::isnan)(ConfigPhaseType::max_t))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerPhaseType::set_m(QString m) const {
    std::string m_str = m.toStdString();

    double m_d = boost::lexical_cast<double>(m_str);
    ConfigPhaseType::max_t = m_d;

}

QString InputControllerPhaseType::get_t() const {
    boost::format fmt = boost::format(DPFS) % (ConfigPhaseType::n_threads);

    if((boost::math::isnan)(ConfigPhaseType::n_threads))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerPhaseType::set_t(QString t) const {
    std::string t_str = t.toStdString();

    double t_d = boost::lexical_cast<double>(t_str);
    ConfigPhaseType::n_threads = t_d;

}

bool InputControllerPhaseType::get_output_P() const {
    return ConfigPhaseType::output_P;
}

void InputControllerPhaseType::set_output_P(bool output_P) const {
    ConfigPhaseType::output_P = output_P;
}

bool InputControllerPhaseType::get_output_Q() const {
    return ConfigPhaseType::output_Q;
}

void InputControllerPhaseType::set_output_Q(bool output_Q) const {
    ConfigPhaseType::output_Q = output_Q;
}

bool InputControllerPhaseType::get_output_R() const {
    return ConfigPhaseType::output_R;
}

void InputControllerPhaseType::set_output_R(bool output_R) const {
    ConfigPhaseType::output_R = output_R;
}

bool InputControllerPhaseType::get_output_Moments() const {
    return ConfigPhaseType::output_Moments;
}

void InputControllerPhaseType::set_output_Moments(bool output_Moments) const {
    ConfigPhaseType::output_Moments = output_Moments;
}

bool InputControllerPhaseType::get_output_Res() const {
    return ConfigPhaseType::output_Res;
}

void InputControllerPhaseType::set_output_Res(bool output_Res) const {
    ConfigPhaseType::output_Res = output_Res;
}

bool InputControllerPhaseType::get_r() const {
    return ConfigPhaseType::no_rem;
}

void InputControllerPhaseType::set_r(bool r) const {
    ConfigPhaseType::no_rem = r;
}

bool InputControllerPhaseType::get_force() const {
    return ConfigPhaseType::force;
}

void InputControllerPhaseType::set_force(bool force) const {
    ConfigPhaseType::force = force;
}

QString InputControllerPhaseType::get_model_type() const {
    return ModelTypePhaseTypeNames[ConfigPhaseType::ModelTypePhaseTypeToInt(ConfigPhaseType::modelType)];
}

void InputControllerPhaseType::set_model_type(QString model_type) const {
    if(model_type.compare(wfes::config::ModelTypePhaseTypeNames[ConfigPhaseType::ModelTypePhaseTypeToInt(ModelTypePhaseType::NONE)]) == 0)
        ConfigPhaseType::modelType = ModelTypePhaseType::NONE;
    if(model_type.compare(wfes::config::ModelTypePhaseTypeNames[ConfigPhaseType::ModelTypePhaseTypeToInt(ModelTypePhaseType::PHASE_TYPE_DIST)]) == 0)
        ConfigPhaseType::modelType = ModelTypePhaseType::PHASE_TYPE_DIST;
    if(model_type.compare(wfes::config::ModelTypePhaseTypeNames[ConfigPhaseType::ModelTypePhaseTypeToInt(ModelTypePhaseType::PHASE_TYPE_MOMENTS)]) == 0)
        ConfigPhaseType::modelType = ModelTypePhaseType::PHASE_TYPE_MOMENTS;
}

QString InputControllerPhaseType::get_library() const {
    return QString::fromStdString(ConfigPhaseType::library);
}

void InputControllerPhaseType::set_library(QString library) const {
    ConfigPhaseType::library = library.toStdString();
}


QString InputControllerPhaseType::get_solver() const {
    return QString::fromStdString(ConfigPhaseType::vienna_solver);
}

void InputControllerPhaseType::set_solver(QString solver) const {
    ConfigPhaseType::vienna_solver = solver.toStdString();
}
