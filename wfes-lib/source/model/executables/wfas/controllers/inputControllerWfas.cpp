#include "inputControllerWfas.h"

using namespace wfes::controllers;
using namespace wfes::config;

InputControllerWfas::InputControllerWfas(QObject *parent): QObject(parent){
    emit input_changed();
}

QString InputControllerWfas::get_a() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfas::a);

    if((boost::math::isnan)(ConfigWfas::a))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfas::set_a(QString a) const {
    std::string a_str = a.toStdString();

    double a_d = boost::lexical_cast<double>(a_str);
    ConfigWfas::a = a_d;

}

QString InputControllerWfas::get_p() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfas::p);

    if((boost::math::isnan)(ConfigWfas::p))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfas::set_p(QString p) const {
    std::string p_str = p.toStdString();

    double p_d = boost::lexical_cast<double>(p_str);
    ConfigWfas::p = p_d;
}

QString InputControllerWfas::get_t() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfas::n_threads);

    if((boost::math::isnan)(ConfigWfas::n_threads))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfas::set_t(QString t) const {
    std::string t_str = t.toStdString();

    double t_d = boost::lexical_cast<double>(t_str);
    ConfigWfas::n_threads = t_d;
}

QString InputControllerWfas::get_num_comp() const {
    return QString::fromStdString(std::to_string(ConfigWfas::num_comp));
}

void InputControllerWfas::set_num_comp(QString num_comp) const {
    std::string num_comp_str = num_comp.toStdString();

    int num_comp_d = boost::lexical_cast<int>(num_comp_str);
    ConfigWfas::num_comp = num_comp_d;

}

bool InputControllerWfas::get_output_Q() const {
    return ConfigWfas::output_Q;
}

void InputControllerWfas::set_output_Q(bool output_Q) const {
    ConfigWfas::output_Q = output_Q;
}

bool InputControllerWfas::get_output_R() const {
    return ConfigWfas::output_R;
}

void InputControllerWfas::set_output_R(bool output_R) const {
    ConfigWfas::output_R = output_R;
}

bool InputControllerWfas::get_output_N() const {
    return ConfigWfas::output_N;
}

void InputControllerWfas::set_output_N(bool output_N) const {
    ConfigWfas::output_N = output_N;
}

bool InputControllerWfas::get_output_B() const {
    return ConfigWfas::output_B;
}

void InputControllerWfas::set_output_B(bool output_B) const {
    ConfigWfas::output_B = output_B;
}

bool InputControllerWfas::get_output_N_Ext() const {
    return ConfigWfas::output_N_Ext;
}

void InputControllerWfas::set_output_N_Ext(bool output_NExt) const {
    ConfigWfas::output_N_Ext = output_NExt;
}

bool InputControllerWfas::get_output_N_Fix() const {
    return ConfigWfas::output_N_Fix;
}

void InputControllerWfas::set_output_N_Fix(bool output_NFix) const {
    ConfigWfas::output_N_Fix = output_NFix;
}

bool InputControllerWfas::get_output_N_Tmo() const {
    return ConfigWfas::output_N_Tmo;
}

void InputControllerWfas::set_output_N_Tmo(bool output_NTmo) const {
    ConfigWfas::output_N_Tmo = output_NTmo;
}

bool InputControllerWfas::get_output_Dist() const {
    return ConfigWfas::output_Dist;
}

void InputControllerWfas::set_output_Dist(bool output_Dist) const {
    ConfigWfas::output_Dist = output_Dist;
}

bool InputControllerWfas::get_force() const {
    return ConfigWfas::force;
}

void InputControllerWfas::set_force(bool force) const {
    ConfigWfas::force = force;
}

bool InputControllerWfas::get_no_proj() const {
    return ConfigWfas::no_proj;
}

void InputControllerWfas::set_no_proj(bool no_proj) const {
    ConfigWfas::no_proj = no_proj;
}

QString InputControllerWfas::get_library() const {
    return QString::fromStdString(ConfigWfas::library);
}

void InputControllerWfas::set_library(QString library) const {
    ConfigWfas::library = library.toStdString();
}

QString InputControllerWfas::get_solver() const {
    return QString::fromStdString(ConfigWfas::vienna_solver);
}

void InputControllerWfas::set_solver(QString solver) const {
    ConfigWfas::vienna_solver = solver.toStdString();
}

QString InputControllerWfas::get_initial_distribution_path() const {
    return QString::fromStdString(ConfigWfas::initial_distribution_csv);
}

void InputControllerWfas::set_initial_distribution_path(QString initial_distribution_path) const {
    ConfigWfas::initial_distribution_csv = initial_distribution_path.toStdString();
}

QList<int> InputControllerWfas::get_N_vec() const {
    std::vector<llong> temp_N = std::vector<llong>(ConfigWfas::N.data(), ConfigWfas::N.data() + ConfigWfas::num_comp);
    std::vector<int> temp_int_N(temp_N.size());
    for(unsigned long i = 0; i < temp_N.size(); i++)
        temp_int_N[i] = temp_N[i];
    return QList<int>::fromVector(QVector<int>(temp_int_N.begin(), temp_int_N.end()));
}

void InputControllerWfas::set_N_vec(QList<int> N) const {
    std::vector<int> temp_int_std_N = std::vector<int>(N.begin(), N.end());
    lvec temp_N(N.size());
    for(int i = 0; i < N.size(); i++)
        temp_N[i] = temp_int_std_N[i];
    ConfigWfas::N = temp_N;
}

QList<int> InputControllerWfas::get_G_vec() const {
    std::vector<llong> temp_G = std::vector<llong>(ConfigWfas::G.data(), ConfigWfas::G.data() + ConfigWfas::num_comp);
    std::vector<int> temp_int_G(temp_G.size());
    for(unsigned long i = 0; i < temp_G.size(); i++)
        temp_int_G[i] = temp_G[i];
    return QList<int>::fromVector(QVector<int>(temp_int_G.begin(), temp_int_G.end()));
}

void InputControllerWfas::set_G_vec(QList<int> G) const {
    std::vector<int> temp_int_std_G = std::vector<int>(G.begin(), G.end());
    lvec temp_G(G.size());
    for(int i = 0; i < G.size(); i++)
        temp_G[i] = temp_int_std_G[i];
    ConfigWfas::G = temp_G;
}

QList<double> InputControllerWfas::get_f_vec() const {
    std::vector<double> temp_std_f = std::vector<double>(ConfigWfas::f.data(), ConfigWfas::f.data() + ConfigWfas::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_f.begin(), temp_std_f.end()));
}

void InputControllerWfas::set_f_vec(QList<double> f) const {
    std::vector<double> temp_std_f = std::vector<double>(f.begin(), f.end());
    dvec temp_f(f.size());
    for(int i = 0; i < f.size(); i++)
        temp_f[i] = temp_std_f[i];
    ConfigWfas::f = temp_f;
}

QList<double> InputControllerWfas::get_u_vec() const {
    std::vector<double> temp_std_u = std::vector<double>(ConfigWfas::u.data(), ConfigWfas::u.data() + ConfigWfas::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_u.begin(), temp_std_u.end()));
}

void InputControllerWfas::set_u_vec(QList<double> u) const {
    std::vector<double> temp_std_u = std::vector<double>(u.begin(), u.end());
    dvec temp_u(u.size());
    for(int i = 0; i < u.size(); i++)
        temp_u[i] = temp_std_u[i];
    ConfigWfas::u = temp_u;
}

QList<double> InputControllerWfas::get_v_vec() const {
    std::vector<double> temp_std_v = std::vector<double>(ConfigWfas::v.data(), ConfigWfas::v.data() + ConfigWfas::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_v.begin(), temp_std_v.end()));
}

void InputControllerWfas::set_v_vec(QList<double> v) const {
    std::vector<double> temp_std_v = std::vector<double>(v.begin(), v.end());
    dvec temp_v(v.size());
    for(int i = 0; i < v.size(); i++)
        temp_v[i] = temp_std_v[i];
    ConfigWfas::v = temp_v;
}

QList<double> InputControllerWfas::get_s_vec() const {
    std::vector<double> temp_std_s = std::vector<double>(ConfigWfas::s.data(), ConfigWfas::s.data() + ConfigWfas::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_s.begin(), temp_std_s.end()));
}

void InputControllerWfas::set_s_vec(QList<double> s) const {
    std::vector<double> temp_std_s = std::vector<double>(s.begin(), s.end());
    dvec temp_s(s.size());
    for(int i = 0; i < s.size(); i++)
        temp_s[i] = temp_std_s[i];
    ConfigWfas::s = temp_s;
}

QList<double> InputControllerWfas::get_h_vec() const {
    std::vector<double> temp_std_h = std::vector<double>(ConfigWfas::h.data(), ConfigWfas::h.data() + ConfigWfas::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_h.begin(), temp_std_h.end()));
}

void InputControllerWfas::set_h_vec(QList<double> h) const {
    std::vector<double> temp_std_h = std::vector<double>(h.begin(), h.end());
    dvec temp_h(h.size());
    for(int i = 0; i < h.size(); i++)
        temp_h[i] = temp_std_h[i];
    ConfigWfas::h = temp_h;
}
