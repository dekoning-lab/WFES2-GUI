#include "inputControllerWfesSequential.h"

using namespace wfes::controllers;
using namespace wfes::config;

InputControllerWfesSequential::InputControllerWfesSequential(QObject *parent): QObject(parent){
    emit input_changed();
}

QString InputControllerWfesSequential::get_a() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfesSequential::a);

    if((boost::math::isnan)(ConfigWfesSequential::a))
        return "";
    else
        return QString::fromStdString(fmt.str());

}

void InputControllerWfesSequential::set_a(QString a) const {
    std::string a_str = a.toStdString();

    double a_d = boost::lexical_cast<double>(a_str);
    ConfigWfesSequential::a = a_d;

}

QString InputControllerWfesSequential::get_c() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfesSequential::c);

    if((boost::math::isnan)(ConfigWfesSequential::c))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSequential::set_c(QString c) const {
    std::string c_str = c.toStdString();

    double c_d = boost::lexical_cast<double>(c_str);
    ConfigWfesSequential::c = c_d;
}

QString InputControllerWfesSequential::get_t() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfesSequential::n_threads);

    if((boost::math::isnan)(ConfigWfesSequential::n_threads))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSequential::set_t(QString t) const {
    std::string t_str = t.toStdString();

     double t_d = boost::lexical_cast<double>(t_str);
     ConfigWfesSequential::n_threads = t_d;
}

QString InputControllerWfesSequential::get_num_comp() const {
    return QString::fromStdString(std::to_string(ConfigWfesSequential::num_comp));
}

void InputControllerWfesSequential::set_num_comp(QString num_comp) const {
    std::string num_comp_str = num_comp.toStdString();

    int num_comp_d = boost::lexical_cast<int>(num_comp_str);
    ConfigWfesSequential::num_comp = num_comp_d;
}

bool InputControllerWfesSequential::get_output_Q() const {
    return ConfigWfesSequential::output_Q;
}

void InputControllerWfesSequential::set_output_Q(bool output_Q) const {
    ConfigWfesSequential::output_Q = output_Q;
}

bool InputControllerWfesSequential::get_output_R() const {
    return ConfigWfesSequential::output_R;
}

void InputControllerWfesSequential::set_output_R(bool output_R) const {
    ConfigWfesSequential::output_R = output_R;
}

bool InputControllerWfesSequential::get_output_N() const {
    return ConfigWfesSequential::output_N;
}

void InputControllerWfesSequential::set_output_N(bool output_N) const {
    ConfigWfesSequential::output_N = output_N;
}

bool InputControllerWfesSequential::get_output_B() const {
    return ConfigWfesSequential::output_B;
}

void InputControllerWfesSequential::set_output_B(bool output_B) const {
    ConfigWfesSequential::output_B = output_B;
}

bool InputControllerWfesSequential::get_output_I() const {
    return ConfigWfesSequential::output_I;
}

void InputControllerWfesSequential::set_output_I(bool output_I) const {
    ConfigWfesSequential::output_I = output_I;
}

bool InputControllerWfesSequential::get_output_N_Ext() const {
    return ConfigWfesSequential::output_N_Ext;
}

void InputControllerWfesSequential::set_output_N_Ext(bool output_NExt) const {
    ConfigWfesSequential::output_N_Ext = output_NExt;
}

bool InputControllerWfesSequential::get_output_N_Fix() const {
    return ConfigWfesSequential::output_N_Fix;
}

void InputControllerWfesSequential::set_output_N_Fix(bool output_NFix) const {
    ConfigWfesSequential::output_N_Fix = output_NFix;
}

bool InputControllerWfesSequential::get_output_N_Tmo() const {
    return ConfigWfesSequential::output_N_Tmo;
}

void InputControllerWfesSequential::set_output_N_Tmo(bool output_NTmo) const {
    ConfigWfesSequential::output_N_Tmo = output_NTmo;
}

bool InputControllerWfesSequential::get_output_Res() const {
    return ConfigWfesSequential::output_Res;
}

void InputControllerWfesSequential::set_output_Res(bool output_Res) const {
    ConfigWfesSequential::output_Res = output_Res;
}

bool InputControllerWfesSequential::get_force() const {
    return ConfigWfesSequential::force;
}

void InputControllerWfesSequential::set_force(bool force) const {
    ConfigWfesSequential::force = force;
}

QString InputControllerWfesSequential::get_library() const {
    return QString::fromStdString(ConfigWfesSequential::library);
}

void InputControllerWfesSequential::set_library(QString library) const {
    ConfigWfesSequential::library = library.toStdString();
}

QString InputControllerWfesSequential::get_solver() const {
    return QString::fromStdString(ConfigWfesSequential::vienna_solver);
}

void InputControllerWfesSequential::set_solver(QString solver) const {
    ConfigWfesSequential::vienna_solver = solver.toStdString();
}

QString InputControllerWfesSequential::get_initial_distribution_path() const {
    return QString::fromStdString(ConfigWfesSequential::initial_distribution_csv);
}

void InputControllerWfesSequential::set_initial_distribution_path(QString initial_distribution_path) const {
    ConfigWfesSequential::initial_distribution_csv = initial_distribution_path.toStdString();
}

QList<int> InputControllerWfesSequential::get_N_vec() const {
    std::vector<llong> temp_N = std::vector<llong>(ConfigWfesSequential::N.data(), ConfigWfesSequential::N.data() + ConfigWfesSequential::num_comp);
    std::vector<int> temp_int_N(temp_N.size());
    for(unsigned long i = 0; i < temp_N.size(); i++)
        temp_int_N[i] = temp_N[i];
    return QList<int>::fromVector(QVector<int>(temp_int_N.begin(), temp_int_N.end()));
}

void InputControllerWfesSequential::set_N_vec(QList<int> N) const {
    std::vector<int> temp_int_std_N = std::vector<int>(N.begin(), N.end());
    lvec temp_N(N.size());
    for(int i = 0; i < N.size(); i++)
        temp_N[i] = temp_int_std_N[i];
    ConfigWfesSequential::N = temp_N;
}

QList<double> InputControllerWfesSequential::get_t_vec() const {
    std::vector<double> temp_t = std::vector<double>(ConfigWfesSequential::t.data(), ConfigWfesSequential::t.data() + ConfigWfesSequential::num_comp);
    std::vector<int> temp_int_t(temp_t.size());
    for(unsigned long i = 0; i < temp_t.size(); i++)
        temp_int_t[i] = temp_t[i];
    return QList<double>::fromVector(QVector<double>(temp_int_t.begin(), temp_int_t.end()));
}

void InputControllerWfesSequential::set_t_vec(QList<double> t) const {
    std::vector<double> temp_int_std_t = std::vector<double>(t.begin(), t.end());
    dvec temp_t(t.size());
    for(int i = 0; i < t.size(); i++)
        temp_t[i] = temp_int_std_t[i];
    ConfigWfesSequential::t = temp_t;
}

QList<double> InputControllerWfesSequential::get_p_vec() const {
    std::vector<double> temp_p = std::vector<double>(ConfigWfesSequential::p.data(), ConfigWfesSequential::p.data() + ConfigWfesSequential::num_comp);
    std::vector<double> temp_int_p(temp_p.size());
    for(unsigned long i = 0; i < temp_p.size(); i++)
        temp_int_p[i] = temp_p[i];
    return QList<double>::fromVector(QVector<double>(temp_int_p.begin(), temp_int_p.end()));
}

void InputControllerWfesSequential::set_p_vec(QList<double> p) const {
    std::vector<int> temp_int_std_p = std::vector<int>(p.begin(), p.end());
    dvec temp_p(p.size());
    for(int i = 0; i < p.size(); i++)
        temp_p[i] = temp_int_std_p[i];
    ConfigWfesSequential::p = temp_p;
}

QList<double> InputControllerWfesSequential::get_u_vec() const {
    std::vector<double> temp_std_u = std::vector<double>(ConfigWfesSequential::u.data(), ConfigWfesSequential::u.data() + ConfigWfesSequential::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_u.begin(), temp_std_u.end()));
}

void InputControllerWfesSequential::set_u_vec(QList<double> u) const {
    std::vector<double> temp_std_u = std::vector<double>(u.begin(), u.end());
    dvec temp_u(u.size());
    for(int i = 0; i < u.size(); i++)
        temp_u[i] = temp_std_u[i];
    ConfigWfesSequential::u = temp_u;
}

QList<double> InputControllerWfesSequential::get_v_vec() const {
    std::vector<double> temp_std_v = std::vector<double>(ConfigWfesSequential::v.data(), ConfigWfesSequential::v.data() + ConfigWfesSequential::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_v.begin(), temp_std_v.end()));
}

void InputControllerWfesSequential::set_v_vec(QList<double> v) const {
    std::vector<double> temp_std_v = std::vector<double>(v.begin(), v.end());
    dvec temp_v(v.size());
    for(int i = 0; i < v.size(); i++)
        temp_v[i] = temp_std_v[i];
    ConfigWfesSequential::v = temp_v;
}

QList<double> InputControllerWfesSequential::get_s_vec() const {
    std::vector<double> temp_std_s = std::vector<double>(ConfigWfesSequential::s.data(), ConfigWfesSequential::s.data() + ConfigWfesSequential::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_s.begin(), temp_std_s.end()));
}

void InputControllerWfesSequential::set_s_vec(QList<double> s) const {
    std::vector<double> temp_std_s = std::vector<double>(s.begin(), s.end());
    dvec temp_s(s.size());
    for(int i = 0; i < s.size(); i++)
        temp_s[i] = temp_std_s[i];
    ConfigWfesSequential::s = temp_s;
}

QList<double> InputControllerWfesSequential::get_h_vec() const {
    std::vector<double> temp_std_h = std::vector<double>(ConfigWfesSequential::h.data(), ConfigWfesSequential::h.data() + ConfigWfesSequential::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_h.begin(), temp_std_h.end()));
}

void InputControllerWfesSequential::set_h_vec(QList<double> h) const {
    std::vector<double> temp_std_h = std::vector<double>(h.begin(), h.end());
    dvec temp_h(h.size());
    for(int i = 0; i < h.size(); i++)
        temp_h[i] = temp_std_h[i];
    ConfigWfesSequential::h = temp_h;
}

