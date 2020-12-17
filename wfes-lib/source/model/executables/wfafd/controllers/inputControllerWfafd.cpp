#include "inputControllerWfafd.h"

using namespace wfes::controllers;
using namespace wfes::config;

InputControllerWfafd::InputControllerWfafd(QObject *parent): QObject(parent){
    emit input_changed();
}

QString InputControllerWfafd::get_a() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfafd::a);

    if((boost::math::isnan)(ConfigWfafd::a))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfafd::set_a(QString a) const {
    std::string a_str = a.toStdString();

    double a_d = boost::lexical_cast<double>(a_str);
    ConfigWfafd::a = a_d;

}

QString InputControllerWfafd::get_p() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfafd::p);

    if((boost::math::isnan)(ConfigWfafd::p))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfafd::set_p(QString p) const {
    std::string p_str = p.toStdString();

    double p_d = boost::lexical_cast<double>(p_str);
    ConfigWfafd::p = p_d;
}

QString InputControllerWfafd::get_t() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfafd::n_threads);

    if((boost::math::isnan)(ConfigWfafd::n_threads))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfafd::set_t(QString t) const {
    std::string t_str = t.toStdString();

    double t_d = boost::lexical_cast<double>(t_str);
    ConfigWfafd::n_threads = t_d;
}

bool InputControllerWfafd::get_output_Dist() const {
    return ConfigWfafd::output_Dist;
}

void InputControllerWfafd::set_output_Dist(bool output_Dist) const {
    ConfigWfafd::output_Dist = output_Dist;
}

bool InputControllerWfafd::get_force() const {
    return ConfigWfafd::force;
}

void InputControllerWfafd::set_force(bool force) const {
    ConfigWfafd::force = force;
}

QString InputControllerWfafd::get_library() const {
    return QString::fromStdString(ConfigWfafd::library);
}

void InputControllerWfafd::set_library(QString library) const {
    ConfigWfafd::library = library.toStdString();
}

QString InputControllerWfafd::get_solver() const {
    return QString::fromStdString(ConfigWfafd::vienna_solver);
}

void InputControllerWfafd::set_solver(QString solver) const {
    ConfigWfafd::vienna_solver = solver.toStdString();
}

QString InputControllerWfafd::get_initial_distribution_path() const {
    return QString::fromStdString(ConfigWfafd::initial_distribution_csv);
}

void InputControllerWfafd::set_initial_distribution_path(QString initial_distribution_path) const {
    ConfigWfafd::initial_distribution_csv = initial_distribution_path.toStdString();
}

QList<int> InputControllerWfafd::get_N_vec() const {
    std::vector<int> temp_std_N = std::vector<int>(ConfigWfafd::N.data(), ConfigWfafd::N.data() + ConfigWfafd::num_comp);
    return QList<int>::fromVector(QVector<int>(temp_std_N.begin(), temp_std_N.end()));
}

void InputControllerWfafd::set_N_vec(QList<int> N) const {
    std::vector<int> temp_std_N = std::vector<int>(N.begin(), N.end());
    ivec temp_N(N.size());
    for(int i = 0; i < N.size(); i++)
        temp_N[i] = temp_std_N[i];
    ConfigWfafd::N = temp_N;
}

QList<int> InputControllerWfafd::get_G_vec() const {
    std::vector<int> temp_std_G = std::vector<int>(ConfigWfafd::G.data(), ConfigWfafd::G.data() + ConfigWfafd::num_comp);
    return QList<int>::fromVector(QVector<int>(temp_std_G.begin(), temp_std_G.end()));
}

void InputControllerWfafd::set_G_vec(QList<int> G) const {
    std::vector<int> temp_std_G = std::vector<int>(G.begin(), G.end());
    ivec temp_G(G.size());
    for(int i = 0; i < G.size(); i++)
        temp_G[i] = temp_std_G[i];
    ConfigWfafd::G = temp_G;
}

QList<double> InputControllerWfafd::get_u_vec() const {
    std::vector<double> temp_std_u = std::vector<double>(ConfigWfafd::u.data(), ConfigWfafd::u.data() + ConfigWfafd::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_u.begin(), temp_std_u.end()));
}

void InputControllerWfafd::set_u_vec(QList<double> u) const {
    std::vector<double> temp_std_u = std::vector<double>(u.begin(), u.end());
    dvec temp_u(u.size());
    for(int i = 0; i < u.size(); i++)
        temp_u[i] = temp_std_u[i];
    ConfigWfafd::u = temp_u;
}

QList<double> InputControllerWfafd::get_v_vec() const {
    std::vector<double> temp_std_v = std::vector<double>(ConfigWfafd::v.data(), ConfigWfafd::v.data() + ConfigWfafd::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_v.begin(), temp_std_v.end()));
}

void InputControllerWfafd::set_v_vec(QList<double> v) const {
    std::vector<double> temp_std_v = std::vector<double>(v.begin(), v.end());
    dvec temp_v(v.size());
    for(int i = 0; i < v.size(); i++)
        temp_v[i] = temp_std_v[i];
    ConfigWfafd::v = temp_v;
}

QList<double> InputControllerWfafd::get_s_vec() const {
    std::vector<double> temp_std_s = std::vector<double>(ConfigWfafd::s.data(), ConfigWfafd::s.data() + ConfigWfafd::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_s.begin(), temp_std_s.end()));
}

void InputControllerWfafd::set_s_vec(QList<double> s) const {
    std::vector<double> temp_std_s = std::vector<double>(s.begin(), s.end());
    dvec temp_s(s.size());
    for(int i = 0; i < s.size(); i++)
        temp_s[i] = temp_std_s[i];
    ConfigWfafd::s = temp_s;
}

QList<double> InputControllerWfafd::get_h_vec() const {
    std::vector<double> temp_std_h = std::vector<double>(ConfigWfafd::h.data(), ConfigWfafd::h.data() + ConfigWfafd::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_h.begin(), temp_std_h.end()));
}

void InputControllerWfafd::set_h_vec(QList<double> h) const {
    std::vector<double> temp_std_h = std::vector<double>(h.begin(), h.end());
    dvec temp_h(h.size());
    for(int i = 0; i < h.size(); i++)
        temp_h[i] = temp_std_h[i];
    ConfigWfafd::h = temp_h;
}

QString InputControllerWfafd::get_num_comp() const {
    return QString::fromStdString(std::to_string(ConfigWfafd::num_comp));
}

void InputControllerWfafd::set_num_comp(QString num_comp) const {
    std::string num_comp_str = num_comp.toStdString();
    int num_comp_d = boost::lexical_cast<int>(num_comp_str);
    ConfigWfafd::num_comp = num_comp_d;
}
