#include "inputControllerTimeDist.h"

using namespace wfes::controllers;
using namespace wfes::config;

InputControllerTimeDist::InputControllerTimeDist(QObject *parent): QObject(parent){
    emit input_changed();
}

QString InputControllerTimeDist::get_n() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDist::population_size);

    if((boost::math::isnan)(ConfigTimeDist::population_size))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_n(QString n) const {
    std::string n_str = n.toStdString();

    double n_d = boost::lexical_cast<double>(n_str);
    ConfigTimeDist::population_size = n_d;
}

QString InputControllerTimeDist::get_n_sgv() const {

    boost::format fmt = boost::format(DPFS) % (ConfigTimeDistSGV::population_size);

    if((boost::math::isnan)(ConfigTimeDistSGV::population_size))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_n_sgv(QString n) const
{
    std::string n_str = n.toStdString();

    double n_d = boost::lexical_cast<double>(n_str);
    ConfigTimeDistSGV::population_size = n_d;
}

QString InputControllerTimeDist::get_a() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDist::a);

    if((boost::math::isnan)(ConfigTimeDist::a))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_a(QString a) const {
    std::string a_str = a.toStdString();

    double a_d = boost::lexical_cast<double>(a_str);
    ConfigTimeDist::a = a_d;
}

QString InputControllerTimeDist::get_a_sgv() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDistSGV::a);

    if((boost::math::isnan)(ConfigTimeDistSGV::a))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_a_sgv(QString a) const {
    std::string a_str = a.toStdString();

    double a_d = boost::lexical_cast<double>(a_str);
    ConfigTimeDistSGV::a = a_d;
}

QString InputControllerTimeDist::get_l() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDistSGV::l);

    if((boost::math::isnan)(ConfigTimeDistSGV::l))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_l(QString l) const {
    std::string l_str = l.toStdString();

    double l_d = boost::lexical_cast<double>(l_str);
    ConfigTimeDistSGV::l = l_d;
}

QString InputControllerTimeDist::get_c() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDist::integration_cutoff);

    if((boost::math::isnan)(ConfigTimeDist::integration_cutoff))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_c(QString c) const {
    std::string c_str = c.toStdString();

    double c_d = boost::lexical_cast<double>(c_str);
    ConfigTimeDist::integration_cutoff = c_d;
}

QString InputControllerTimeDist::get_c_sgv() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDistSGV::integration_cutoff);

    if((boost::math::isnan)(ConfigTimeDistSGV::integration_cutoff))
        return "";
    else
        return QString::fromStdString(fmt.str());

}

void InputControllerTimeDist::set_c_sgv(QString c) const {
    std::string c_str = c.toStdString();

    double c_d = boost::lexical_cast<double>(c_str);
    ConfigTimeDistSGV::integration_cutoff = c_d;
}

QString InputControllerTimeDist::get_m() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDist::max_t);

    if((boost::math::isnan)(ConfigTimeDist::max_t))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_m(QString m) const {
    std::string m_str = m.toStdString();

    double m_d = boost::lexical_cast<double>(m_str);
    ConfigTimeDist::max_t = m_d;
}

QString InputControllerTimeDist::get_m_sgv() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDistSGV::max_t);

    if((boost::math::isnan)(ConfigTimeDistSGV::max_t))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_m_sgv(QString m) const {
    std::string m_str = m.toStdString();

    double m_d = boost::lexical_cast<double>(m_str);
    ConfigTimeDistSGV::max_t = m_d;
}


QString InputControllerTimeDist::get_u() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDist::u);

    if((boost::math::isnan)(ConfigTimeDist::u))
        return "";
    else
        return QString::fromStdString(fmt.str());

}

void InputControllerTimeDist::set_u(QString u) const {
    std::string u_str = u.toStdString();

    double u_d = boost::lexical_cast<double>(u_str);
    ConfigTimeDist::u = u_d;
}

QString InputControllerTimeDist::get_v() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDist::v);

    if((boost::math::isnan)(ConfigTimeDist::v))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_v(QString v) const {
    std::string v_str = v.toStdString();

    double v_d = boost::lexical_cast<double>(v_str);
    ConfigTimeDist::v = v_d;
}

QString InputControllerTimeDist::get_s() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDist::s);

    if((boost::math::isnan)(ConfigTimeDist::s))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_s(QString s) const {
    std::string s_str = s.toStdString();

    double s_d = boost::lexical_cast<double>(s_str);
    ConfigTimeDist::s = s_d;
}

QString InputControllerTimeDist::get_h() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDist::h);

    if((boost::math::isnan)(ConfigTimeDist::h))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_h(QString h) const {
    std::string h_str = h.toStdString();

    double h_d = boost::lexical_cast<double>(h_str);
    ConfigTimeDist::h = h_d;
}

QString InputControllerTimeDist::get_t() const {
    boost::format fmt = boost::format(DPFS) % (ConfigTimeDist::n_threads);

    if((boost::math::isnan)(ConfigTimeDist::n_threads))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_t(QString t) const {
    std::string t_str = t.toStdString();

    double t_d = boost::lexical_cast<double>(t_str);
    ConfigTimeDist::n_threads = t_d;
}

bool InputControllerTimeDist::get_output_P() const {
    return ConfigTimeDist::output_P;
}

void InputControllerTimeDist::set_output_P(bool output_P) const {
    ConfigTimeDist::output_P = output_P;
}

bool InputControllerTimeDist::get_output_Q() const {
    return ConfigTimeDist::output_Q;
}

void InputControllerTimeDist::set_output_Q(bool output_Q) const {
    ConfigTimeDist::output_Q = output_Q;
}

bool InputControllerTimeDist::get_output_R() const {
    return ConfigTimeDist::output_R;
}

void InputControllerTimeDist::set_output_R(bool output_R) const {
    ConfigTimeDist::output_R = output_R;
}

bool InputControllerTimeDist::get_r() const {
    return ConfigTimeDist::no_rem;
}

void InputControllerTimeDist::set_r(bool r) const {
    ConfigTimeDist::no_rem = r;
}

bool InputControllerTimeDist::get_r_sgv() const {
    return ConfigTimeDistSGV::no_rem;
}

void InputControllerTimeDist::set_r_sgv(bool r) const {
    ConfigTimeDistSGV::no_rem = r;
}

QString InputControllerTimeDist::get_model_type() const {
    return ModelTypeTimeDistNames[ConfigTimeDist::ModelTypeTimeDistToInt(ConfigTimeDist::modelType)];
}

void InputControllerTimeDist::set_model_type(QString model_type) const {
    if(model_type.compare(ModelTypeTimeDistNames[ConfigTimeDist::ModelTypeTimeDistToInt(ModelTypeTimeDist::NONE)]) == 0)
        ConfigTimeDist::modelType = ModelTypeTimeDist::NONE;
    if(model_type.compare(ModelTypeTimeDistNames[ConfigTimeDist::ModelTypeTimeDistToInt(ModelTypeTimeDist::TIME_DIST)]) == 0)
        ConfigTimeDist::modelType = ModelTypeTimeDist::TIME_DIST;
    if(model_type.compare(ModelTypeTimeDistNames[ConfigTimeDist::ModelTypeTimeDistToInt(ModelTypeTimeDist::TIME_DIST_SGV)]) == 0)
        ConfigTimeDist::modelType = ModelTypeTimeDist::TIME_DIST_SGV;
    if(model_type.compare(ModelTypeTimeDistNames[ConfigTimeDist::ModelTypeTimeDistToInt(ModelTypeTimeDist::TIME_DIST_SKIP)]) == 0)
        ConfigTimeDist::modelType = ModelTypeTimeDist::TIME_DIST_SKIP;
    if(model_type.compare(ModelTypeTimeDistNames[ConfigTimeDist::ModelTypeTimeDistToInt(ModelTypeTimeDist::TIME_DIST_DUAL)]) == 0)
        ConfigTimeDist::modelType = ModelTypeTimeDist::TIME_DIST_DUAL;

}

QString InputControllerTimeDist::get_library() const {
    return QString::fromStdString(ConfigTimeDist::library);
}

void InputControllerTimeDist::set_library(QString library) const {
    ConfigTimeDist::library = library.toStdString();
}

QString InputControllerTimeDist::get_solver() const {
    return QString::fromStdString(ConfigTimeDist::vienna_solver);
}

void InputControllerTimeDist::set_solver(QString solver) const {
    ConfigTimeDist::vienna_solver = solver.toStdString();
}

bool InputControllerTimeDist::get_force() const {
    return ConfigTimeDistSGV::force;
}

void InputControllerTimeDist::set_force(bool force) const {
    ConfigTimeDistSGV::force = force;
}

QList<double> InputControllerTimeDist::get_u_vec() const {
    std::vector<double> temp_std_u = std::vector<double>(ConfigTimeDistSGV::u.data(), ConfigTimeDistSGV::u.data() + ConfigTimeDistSGV::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_u.begin(), temp_std_u.end()));
}

void InputControllerTimeDist::set_u_vec(QList<double> u) const {
    std::vector<double> temp_std_u = std::vector<double>(u.begin(), u.end());
    dvec temp_u(2);
    temp_u[0] = temp_std_u[0];
    temp_u[1] = temp_std_u[1];
    ConfigTimeDistSGV::u = temp_u;
}

QList<double> InputControllerTimeDist::get_v_vec() const {
    std::vector<double> temp_std_v = std::vector<double>(ConfigTimeDistSGV::v.data(), ConfigTimeDistSGV::v.data() + ConfigTimeDistSGV::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_v.begin(), temp_std_v.end()));
}

void InputControllerTimeDist::set_v_vec(QList<double> v) const {
    std::vector<double> temp_std_v = std::vector<double>(v.begin(), v.end());
    dvec temp_v(2);
    temp_v[0] = temp_std_v[0];
    temp_v[1] = temp_std_v[1];
    ConfigTimeDistSGV::v = temp_v;
}

QList<double> InputControllerTimeDist::get_s_vec() const {
    std::vector<double> temp_std_s = std::vector<double>(ConfigTimeDistSGV::s.data(), ConfigTimeDistSGV::s.data() + ConfigTimeDistSGV::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_s.begin(), temp_std_s.end()));
}

void InputControllerTimeDist::set_s_vec(QList<double> s) const {
    std::vector<double> temp_std_s = std::vector<double>(s.begin(), s.end());
    dvec temp_s(2);
    temp_s[0] = temp_std_s[0];
    temp_s[1] = temp_std_s[1];
    ConfigTimeDistSGV::s = temp_s;
}

QList<double> InputControllerTimeDist::get_h_vec() const {
    std::vector<double> temp_std_h = std::vector<double>(ConfigTimeDistSGV::h.data(), ConfigTimeDistSGV::h.data() + ConfigTimeDistSGV::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_h.begin(), temp_std_h.end()));
}

void InputControllerTimeDist::set_h_vec(QList<double> h) const {
    std::vector<double> temp_std_h = std::vector<double>(h.begin(), h.end());
    dvec temp_h(2);
    temp_h[0] = temp_std_h[0];
    temp_h[1] = temp_std_h[1];
    ConfigTimeDistSGV::h = temp_h;
}
