#include "inputControllerWfafs.h"

using namespace wfes::controllers;
using namespace wfes::config;

InputControllerWfafs::InputControllerWfafs(QObject *parent): QObject(parent){
    emit input_changed();
}

QString InputControllerWfafs::get_a() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfafs::a);

    if((boost::math::isnan)(ConfigWfafs::a))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfafs::set_a(QString a) const {
    std::string a_str = a.toStdString();

    double a_d = boost::lexical_cast<double>(a_str);
    ConfigWfafs::a = a_d;

}

QString InputControllerWfafs::get_p() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfafs::p);

    if((boost::math::isnan)(ConfigWfafs::p))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfafs::set_p(QString p) const {
    std::string p_str = p.toStdString();

    double p_d = boost::lexical_cast<double>(p_str);
    ConfigWfafs::p = p_d;
}

QString InputControllerWfafs::get_t() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfafs::n_threads);

    if((boost::math::isnan)(ConfigWfafs::n_threads))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfafs::set_t(QString t) const {
    std::string t_str = t.toStdString();

    double t_d = boost::lexical_cast<double>(t_str);
    ConfigWfafs::n_threads = t_d;
}

QString InputControllerWfafs::get_num_comp() const {
    return QString::fromStdString(std::to_string(ConfigWfafs::num_comp));
}

void InputControllerWfafs::set_num_comp(QString num_comp) const {
    std::string num_comp_str = num_comp.toStdString();

    int num_comp_d = boost::lexical_cast<int>(num_comp_str);
    ConfigWfafs::num_comp = num_comp_d;

}

bool InputControllerWfafs::get_output_Q() const {
    return ConfigWfafs::output_Q;
}

void InputControllerWfafs::set_output_Q(bool output_Q) const {
    ConfigWfafs::output_Q = output_Q;
}

bool InputControllerWfafs::get_output_R() const {
    return ConfigWfafs::output_R;
}

void InputControllerWfafs::set_output_R(bool output_R) const {
    ConfigWfafs::output_R = output_R;
}

bool InputControllerWfafs::get_output_N() const {
    return ConfigWfafs::output_N;
}

void InputControllerWfafs::set_output_N(bool output_N) const {
    ConfigWfafs::output_N = output_N;
}

bool InputControllerWfafs::get_output_B() const {
    return ConfigWfafs::output_B;
}

void InputControllerWfafs::set_output_B(bool output_B) const {
    ConfigWfafs::output_B = output_B;
}

bool InputControllerWfafs::get_output_N_Ext() const {
    return ConfigWfafs::output_N_Ext;
}

void InputControllerWfafs::set_output_N_Ext(bool output_NExt) const {
    ConfigWfafs::output_N_Ext = output_NExt;
}

bool InputControllerWfafs::get_output_N_Fix() const {
    return ConfigWfafs::output_N_Fix;
}

void InputControllerWfafs::set_output_N_Fix(bool output_NFix) const {
    ConfigWfafs::output_N_Fix = output_NFix;
}

bool InputControllerWfafs::get_output_N_Tmo() const {
    return ConfigWfafs::output_N_Tmo;
}

void InputControllerWfafs::set_output_N_Tmo(bool output_NTmo) const {
    ConfigWfafs::output_N_Tmo = output_NTmo;
}

bool InputControllerWfafs::get_output_Dist() const {
    return ConfigWfafs::output_Dist;
}

void InputControllerWfafs::set_output_Dist(bool output_Dist) const {
    ConfigWfafs::output_Dist = output_Dist;
}

bool InputControllerWfafs::get_force() const {
    return ConfigWfafs::force;
}

void InputControllerWfafs::set_force(bool force) const {
    ConfigWfafs::force = force;
}

bool InputControllerWfafs::get_no_proj() const {
    return ConfigWfafs::no_proj;
}

void InputControllerWfafs::set_no_proj(bool no_proj) const {
    ConfigWfafs::no_proj = no_proj;
}

QString InputControllerWfafs::get_library() const {
    return QString::fromStdString(ConfigWfafs::library);
}

void InputControllerWfafs::set_library(QString library) const {
    ConfigWfafs::library = library.toStdString();
}

QString InputControllerWfafs::get_solver() const {
    return QString::fromStdString(ConfigWfafs::vienna_solver);
}

void InputControllerWfafs::set_solver(QString solver) const {
    ConfigWfafs::vienna_solver = solver.toStdString();
}

QString InputControllerWfafs::get_initial_distribution_path() const {
    return QString::fromStdString(ConfigWfafs::initial_distribution_csv);
}

void InputControllerWfafs::set_initial_distribution_path(QString initial_distribution_path) const {
    ConfigWfafs::initial_distribution_csv = initial_distribution_path.toStdString();
}

QList<int> InputControllerWfafs::get_N_vec() const {
    std::vector<llong> temp_N = std::vector<llong>(ConfigWfafs::N.data(), ConfigWfafs::N.data() + ConfigWfafs::num_comp);
    std::vector<int> temp_int_N(temp_N.size());
    for(unsigned long i = 0; i < temp_N.size(); i++)
        temp_int_N[i] = temp_N[i];
    return QList<int>::fromVector(QVector<int>(temp_int_N.begin(), temp_int_N.end()));
}

void InputControllerWfafs::set_N_vec(QList<int> N) const {
    std::vector<int> temp_int_std_N = std::vector<int>(N.begin(), N.end());
    lvec temp_N(N.size());
    for(int i = 0; i < N.size(); i++)
        temp_N[i] = temp_int_std_N[i];
    ConfigWfafs::N = temp_N;
}

QList<int> InputControllerWfafs::get_G_vec() const {
    std::vector<llong> temp_G = std::vector<llong>(ConfigWfafs::G.data(), ConfigWfafs::G.data() + ConfigWfafs::num_comp);
    std::vector<int> temp_int_G(temp_G.size());
    for(unsigned long i = 0; i < temp_G.size(); i++)
        temp_int_G[i] = temp_G[i];
    return QList<int>::fromVector(QVector<int>(temp_int_G.begin(), temp_int_G.end()));
}

void InputControllerWfafs::set_G_vec(QList<int> G) const {
    std::vector<int> temp_int_std_G = std::vector<int>(G.begin(), G.end());
    lvec temp_G(G.size());
    for(int i = 0; i < G.size(); i++)
        temp_G[i] = temp_int_std_G[i];
    ConfigWfafs::G = temp_G;
}

QList<double> InputControllerWfafs::get_f_vec() const {
    std::vector<double> temp_std_f = std::vector<double>(ConfigWfafs::f.data(), ConfigWfafs::f.data() + ConfigWfafs::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_f.begin(), temp_std_f.end()));
}

void InputControllerWfafs::set_f_vec(QList<double> f) const {
    std::vector<double> temp_std_f = std::vector<double>(f.begin(), f.end());
    dvec temp_f(f.size());
    for(int i = 0; i < f.size(); i++)
        temp_f[i] = temp_std_f[i];
    ConfigWfafs::f = temp_f;
}

QList<double> InputControllerWfafs::get_u_vec() const {
    std::vector<double> temp_std_u = std::vector<double>(ConfigWfafs::u.data(), ConfigWfafs::u.data() + ConfigWfafs::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_u.begin(), temp_std_u.end()));
}

void InputControllerWfafs::set_u_vec(QList<double> u) const {
    std::vector<double> temp_std_u = std::vector<double>(u.begin(), u.end());
    dvec temp_u(u.size());
    for(int i = 0; i < u.size(); i++)
        temp_u[i] = temp_std_u[i];
    ConfigWfafs::u = temp_u;
}

QList<double> InputControllerWfafs::get_v_vec() const {
    std::vector<double> temp_std_v = std::vector<double>(ConfigWfafs::v.data(), ConfigWfafs::v.data() + ConfigWfafs::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_v.begin(), temp_std_v.end()));
}

void InputControllerWfafs::set_v_vec(QList<double> v) const {
    std::vector<double> temp_std_v = std::vector<double>(v.begin(), v.end());
    dvec temp_v(v.size());
    for(int i = 0; i < v.size(); i++)
        temp_v[i] = temp_std_v[i];
    ConfigWfafs::v = temp_v;
}

QList<double> InputControllerWfafs::get_s_vec() const {
    std::vector<double> temp_std_s = std::vector<double>(ConfigWfafs::s.data(), ConfigWfafs::s.data() + ConfigWfafs::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_s.begin(), temp_std_s.end()));
}

void InputControllerWfafs::set_s_vec(QList<double> s) const {
    std::vector<double> temp_std_s = std::vector<double>(s.begin(), s.end());
    dvec temp_s(s.size());
    for(int i = 0; i < s.size(); i++)
        temp_s[i] = temp_std_s[i];
    ConfigWfafs::s = temp_s;
}

QList<double> InputControllerWfafs::get_h_vec() const {
    std::vector<double> temp_std_h = std::vector<double>(ConfigWfafs::h.data(), ConfigWfafs::h.data() + ConfigWfafs::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_h.begin(), temp_std_h.end()));
}

void InputControllerWfafs::set_h_vec(QList<double> h) const {
    std::vector<double> temp_std_h = std::vector<double>(h.begin(), h.end());
    dvec temp_h(h.size());
    for(int i = 0; i < h.size(); i++)
        temp_h[i] = temp_std_h[i];
    ConfigWfafs::h = temp_h;
}
