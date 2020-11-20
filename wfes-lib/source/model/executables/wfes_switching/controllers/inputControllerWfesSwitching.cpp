#include "inputControllerWfesSwitching.h"

using namespace wfes::controllers;
using namespace wfes::config;

InputControllerWfesSwitching::InputControllerWfesSwitching(QObject *parent): QObject(parent){
    emit input_changed();
}

QString InputControllerWfesSwitching::get_a() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfesSwitching::a);

    if((boost::math::isnan)(ConfigWfesSwitching::a))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSwitching::set_a(QString a) const {
    std::string a_str = a.toStdString();

    double a_d = boost::lexical_cast<double>(a_str);
    ConfigWfesSwitching::a = a_d;

}

QString InputControllerWfesSwitching::get_c() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfesSwitching::c);

    if((boost::math::isnan)(ConfigWfesSwitching::c))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSwitching::set_c(QString c) const {
    std::string c_str = c.toStdString();

    double c_d = boost::lexical_cast<double>(c_str);
    ConfigWfesSwitching::c = c_d;
}

QString InputControllerWfesSwitching::get_t() const {
    boost::format fmt = boost::format(DPFS) % (ConfigWfesSwitching::n_threads);

    if((boost::math::isnan)(ConfigWfesSwitching::n_threads))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSwitching::set_t(QString t) const {
    std::string t_str = t.toStdString();

    double t_d = boost::lexical_cast<double>(t_str);
    ConfigWfesSwitching::n_threads = t_d;
}

QString InputControllerWfesSwitching::get_num_comp() const {
    return QString::fromStdString(std::to_string(ConfigWfesSwitching::num_comp));
}

void InputControllerWfesSwitching::set_num_comp(QString num_comp) const {
    std::string num_comp_str = num_comp.toStdString();

    int num_comp_d = boost::lexical_cast<int>(num_comp_str);
    ConfigWfesSwitching::num_comp = num_comp_d;
}

bool InputControllerWfesSwitching::get_output_Q() const {
    return ConfigWfesSwitching::output_Q;
}

void InputControllerWfesSwitching::set_output_Q(bool output_Q) const {
    ConfigWfesSwitching::output_Q = output_Q;
}

bool InputControllerWfesSwitching::get_output_R() const {
    return ConfigWfesSwitching::output_R;
}

void InputControllerWfesSwitching::set_output_R(bool output_R) const {
    ConfigWfesSwitching::output_R = output_R;
}

bool InputControllerWfesSwitching::get_output_N() const {
    return ConfigWfesSwitching::output_N;
}

void InputControllerWfesSwitching::set_output_N(bool output_N) const {
    ConfigWfesSwitching::output_N = output_N;
}

bool InputControllerWfesSwitching::get_output_B() const {
    return ConfigWfesSwitching::output_B;
}

void InputControllerWfesSwitching::set_output_B(bool output_B) const {
    ConfigWfesSwitching::output_B = output_B;
}

bool InputControllerWfesSwitching::get_output_N_Ext() const {
    return ConfigWfesSwitching::output_N_Ext;
}

void InputControllerWfesSwitching::set_output_N_Ext(bool output_NExt) const {
    ConfigWfesSwitching::output_N_Ext = output_NExt;
}

bool InputControllerWfesSwitching::get_output_N_Fix() const {
    return ConfigWfesSwitching::output_N_Fix;
}

void InputControllerWfesSwitching::set_output_N_Fix(bool output_NFix) const {
    ConfigWfesSwitching::output_N_Fix = output_NFix;
}

bool InputControllerWfesSwitching::get_output_Res() const {
    return ConfigWfesSwitching::output_Res;
}

void InputControllerWfesSwitching::set_output_Res(bool output_Res) const {
    ConfigWfesSwitching::output_Res = output_Res;
}

bool InputControllerWfesSwitching::get_force() const {
    return ConfigWfesSwitching::force;
}

void InputControllerWfesSwitching::set_force(bool force) const {
    ConfigWfesSwitching::force = force;
}

QString InputControllerWfesSwitching::get_model_type() const {
    return wfes::config::ModelTypeWfesSwitchingNames[wfes::config::ConfigWfesSwitching::ModelTypeWfesSwitchingToInt(wfes::config::ConfigWfesSwitching::modelType)];
}

void InputControllerWfesSwitching::set_model_type(QString model_type) const {
    if(model_type.compare(wfes::config::ModelTypeWfesSwitchingNames[wfes::config::ConfigWfesSwitching::ModelTypeWfesSwitchingToInt(wfes::config::ModelTypeWfesSwitching::NONE)]) == 0)
        wfes::config::ConfigWfesSwitching::modelType = wfes::config::ModelTypeWfesSwitching::NONE;
    if(model_type.compare(wfes::config::ModelTypeWfesSwitchingNames[wfes::config::ConfigWfesSwitching::ModelTypeWfesSwitchingToInt(wfes::config::ModelTypeWfesSwitching::FIXATION)]) == 0)
        wfes::config::ConfigWfesSwitching::modelType = wfes::config::ModelTypeWfesSwitching::FIXATION;
    if(model_type.compare(wfes::config::ModelTypeWfesSwitchingNames[wfes::config::ConfigWfesSwitching::ModelTypeWfesSwitchingToInt(wfes::config::ModelTypeWfesSwitching::ABSORPTION)]) == 0)
        wfes::config::ConfigWfesSwitching::modelType = wfes::config::ModelTypeWfesSwitching::ABSORPTION;
}

QString InputControllerWfesSwitching::get_library() const {
    return QString::fromStdString(ConfigWfesSwitching::library);
}

void InputControllerWfesSwitching::set_library(QString library) const {
    ConfigWfesSwitching::library = library.toStdString();
}

QString InputControllerWfesSwitching::get_solver() const {
    return QString::fromStdString(ConfigWfesSwitching::vienna_solver);
}

void InputControllerWfesSwitching::set_solver(QString solver) const {
    ConfigWfesSwitching::vienna_solver = solver.toStdString();
}

QString InputControllerWfesSwitching::get_initial_distribution_path() const {
    return QString::fromStdString(ConfigWfesSwitching::initial_distribution_csv);
}

void InputControllerWfesSwitching::set_initial_distribution_path(QString initial_distribution_path) const {
    ConfigWfesSwitching::initial_distribution_csv = initial_distribution_path.toStdString();
}

QList<int> InputControllerWfesSwitching::get_N_vec() const {
    std::vector<llong> temp_N = std::vector<llong>(ConfigWfesSwitching::N.data(), ConfigWfesSwitching::N.data() + ConfigWfesSwitching::num_comp);
    std::vector<int> temp_int_N(temp_N.size());
    for(unsigned long i = 0; i < temp_N.size(); i++)
        temp_int_N[i] = temp_N[i];
    return QList<int>::fromVector(QVector<int>(temp_int_N.begin(), temp_int_N.end()));
}

void InputControllerWfesSwitching::set_N_vec(QList<int> N) const {
    std::vector<int> temp_int_std_N = std::vector<int>(N.begin(), N.end());
    lvec temp_N(N.size());
    for(int i = 0; i < N.size(); i++)
        temp_N[i] = temp_int_std_N[i];
    ConfigWfesSwitching::N = temp_N;
}

QStringList InputControllerWfesSwitching::get_r_vec() const {
    QString str = "";
    QStringList list;
    for(int i = 0; i < ConfigWfesSwitching::r.rows(); i++) {
        for(int j = 0; j < ConfigWfesSwitching::r.cols() - 1; j++) {
            str += QString::fromStdString(std::to_string(ConfigWfesSwitching::r(i, j)) + ", ");
        }
        str += QString::fromStdString(std::to_string(ConfigWfesSwitching::r(i, ConfigWfesSwitching::r.cols() - 1)));
        list.append(str);
        str = "";
    }
    return list;
}

void InputControllerWfesSwitching::set_r_vec(QStringList r) const {
    QStringList parts;
    dmat r_temp(r.size(), r[0].split(", ").size());
    dvec values;
    for(int i = 0; i < r.size(); i++) {
        parts = r[i].split(", ");
        for(int j = 0; j < parts.size(); j++) {
            r_temp(i, j) = std::stod(parts[j].toStdString());
        }
    }
    ConfigWfesSwitching::r = r_temp;
}

QList<double> InputControllerWfesSwitching::get_p_vec() const {
    std::vector<double> temp_p = std::vector<double>(ConfigWfesSwitching::p.data(), ConfigWfesSwitching::p.data() + ConfigWfesSwitching::num_comp);
    std::vector<double> temp_int_p(temp_p.size());
    for(unsigned long i = 0; i < temp_p.size(); i++)
        temp_int_p[i] = temp_p[i];
    return QList<double>::fromVector(QVector<double>(temp_int_p.begin(), temp_int_p.end()));
}

void InputControllerWfesSwitching::set_p_vec(QList<double> p) const {
    std::vector<double> temp_int_std_p = std::vector<double>(p.begin(), p.end());
    dvec temp_p(p.size());
    for(int i = 0; i < p.size(); i++)
        temp_p[i] = temp_int_std_p[i];
    ConfigWfesSwitching::p = temp_p;
}

QList<double> InputControllerWfesSwitching::get_u_vec() const {
    std::vector<double> temp_std_u = std::vector<double>(ConfigWfesSwitching::u.data(), ConfigWfesSwitching::u.data() + ConfigWfesSwitching::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_u.begin(), temp_std_u.end()));
}

void InputControllerWfesSwitching::set_u_vec(QList<double> u) const {
    std::vector<double> temp_std_u = std::vector<double>(u.begin(), u.end());
    dvec temp_u(u.size());
    for(int i = 0; i < u.size(); i++)
        temp_u[i] = temp_std_u[i];
    ConfigWfesSwitching::u = temp_u;
}

QList<double> InputControllerWfesSwitching::get_v_vec() const {
    std::vector<double> temp_std_v = std::vector<double>(ConfigWfesSwitching::v.data(), ConfigWfesSwitching::v.data() + ConfigWfesSwitching::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_v.begin(), temp_std_v.end()));
}

void InputControllerWfesSwitching::set_v_vec(QList<double> v) const {
    std::vector<double> temp_std_v = std::vector<double>(v.begin(), v.end());
    dvec temp_v(v.size());
    for(int i = 0; i < v.size(); i++)
        temp_v[i] = temp_std_v[i];
    ConfigWfesSwitching::v = temp_v;
}

QList<double> InputControllerWfesSwitching::get_s_vec() const {
    std::vector<double> temp_std_s = std::vector<double>(ConfigWfesSwitching::s.data(), ConfigWfesSwitching::s.data() + ConfigWfesSwitching::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_s.begin(), temp_std_s.end()));
}

void InputControllerWfesSwitching::set_s_vec(QList<double> s) const
{
    std::vector<double> temp_std_s = std::vector<double>(s.begin(), s.end());
    dvec temp_s(s.size());
    for(int i = 0; i < s.size(); i++)
        temp_s[i] = temp_std_s[i];
    ConfigWfesSwitching::s = temp_s;
}

QList<double> InputControllerWfesSwitching::get_h_vec() const {
    std::vector<double> temp_std_h = std::vector<double>(ConfigWfesSwitching::h.data(), ConfigWfesSwitching::h.data() + ConfigWfesSwitching::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_h.begin(), temp_std_h.end()));
}

void InputControllerWfesSwitching::set_h_vec(QList<double> h) const {
    std::vector<double> temp_std_h = std::vector<double>(h.begin(), h.end());
    dvec temp_h(h.size());
    for(int i = 0; i < h.size(); i++)
        temp_h[i] = temp_std_h[i];
    ConfigWfesSwitching::h = temp_h;
}
