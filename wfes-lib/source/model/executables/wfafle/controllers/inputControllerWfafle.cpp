#include "inputControllerWfafle.h"

using namespace wfes::controllers;
using namespace wfes::config;

InputControllerWfafle::InputControllerWfafle(QObject *parent): QObject(parent){
    emit input_changed();
}

InputControllerWfafle::~InputControllerWfafle() {}

QString InputControllerWfafle::get_a() const
{
    boost::format fmt = boost::format(DPFS) % (ConfigWfafle::a);

    if((boost::math::isnan)(ConfigWfafle::a))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfafle::set_a(QString a) const
{
    std::string a_str = a.toStdString();
    try {
        double a_d = boost::lexical_cast<double>(a_str);
        ConfigWfafle::a = a_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(a_str.compare("") == 0) {
            errorMessage = "The field 'Tail Truncation Weight' (a) is empty." + a_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Tail Truncation Weight' (a): " + a_str + "\n";
        }
        ConfigWfafle::error += errorMessage;
    }
}

QString InputControllerWfafle::get_p() const
{
    boost::format fmt = boost::format(DPFS) % (ConfigWfafle::p);

    if((boost::math::isnan)(ConfigWfafle::p))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfafle::set_p(QString p) const
{
    std::string p_str = p.toStdString();
    try {
        double p_d = boost::lexical_cast<double>(p_str);
        ConfigWfafle::p = p_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(p_str.compare("") == 0) {
            errorMessage = "The field 'Starting Copies' (p) is empty." + p_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Starting Copies' (p): " + p_str + "\n";
        }
        ConfigWfafle::error += errorMessage;
    }
}

QString InputControllerWfafle::get_t() const
{
    boost::format fmt = boost::format(DPFS) % (ConfigWfafle::n_threads);

    if((boost::math::isnan)(ConfigWfafle::n_threads))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfafle::set_t(QString t) const
{
    std::string t_str = t.toStdString();
    try {
        double t_d = boost::lexical_cast<double>(t_str);
        ConfigWfafle::n_threads = t_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(t_str.compare("") == 0) {
            errorMessage = "The field 'Number of Threads' (t) is empty." + t_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Number of Threads' (t): " + t_str + "\n";
        }
        ConfigWfafle::error += errorMessage;
    }
}

bool InputControllerWfafle::get_output_Dist() const
{
    return ConfigWfafle::output_Dist;
}

void InputControllerWfafle::set_output_Dist(bool output_Dist) const
{
    ConfigWfafle::output_Dist = output_Dist;
}

bool InputControllerWfafle::get_force() const
{
    return ConfigWfafle::force;
}

void InputControllerWfafle::set_force(bool force) const
{
    ConfigWfafle::force = force;
}

QString InputControllerWfafle::get_library() const
{
    return QString::fromStdString(ConfigWfafle::library);
}

void InputControllerWfafle::set_library(QString library) const
{
    ConfigWfafle::library = library.toStdString();
}

QString InputControllerWfafle::get_solver() const
{
    return QString::fromStdString(ConfigWfafle::vienna_solver);
}

void InputControllerWfafle::set_solver(QString solver) const
{
    ConfigWfafle::vienna_solver = solver.toStdString();
}

QString InputControllerWfafle::get_initial_distribution_path() const
{
    return QString::fromStdString(ConfigWfafle::initial_distribution_csv);
}

void InputControllerWfafle::set_initial_distribution_path(QString initial_distribution_path) const
{
    ConfigWfafle::initial_distribution_csv = initial_distribution_path.toStdString();
}

QList<int> InputControllerWfafle::get_N_vec() const
{
    std::vector<int> temp_std_N = std::vector<int>(ConfigWfafle::N.data(), ConfigWfafle::N.data() + ConfigWfafle::num_comp);
    return QList<int>::fromVector(QVector<int>(temp_std_N.begin(), temp_std_N.end()));
}

void InputControllerWfafle::set_N_vec(QList<int> N) const
{
    std::vector<int> temp_std_N = std::vector<int>(N.begin(), N.end());
    ivec temp_N(N.size());
    for(int i = 0; i < N.size(); i++)
        temp_N[i] = temp_std_N[i];
    ConfigWfafle::N = temp_N;
}

QList<int> InputControllerWfafle::get_G_vec() const
{
    std::vector<int> temp_std_G = std::vector<int>(ConfigWfafle::G.data(), ConfigWfafle::G.data() + ConfigWfafle::num_comp);
    return QList<int>::fromVector(QVector<int>(temp_std_G.begin(), temp_std_G.end()));
}

void InputControllerWfafle::set_G_vec(QList<int> G) const
{
    std::vector<int> temp_std_G = std::vector<int>(G.begin(), G.end());
    ivec temp_G(G.size());
    for(int i = 0; i < G.size(); i++)
        temp_G[i] = temp_std_G[i];
    ConfigWfafle::G = temp_G;
}

QList<double> InputControllerWfafle::get_u_vec() const
{
    std::vector<double> temp_std_u = std::vector<double>(ConfigWfafle::u.data(), ConfigWfafle::u.data() + ConfigWfafle::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_u.begin(), temp_std_u.end()));
}

void InputControllerWfafle::set_u_vec(QList<double> u) const
{
    std::vector<double> temp_std_u = std::vector<double>(u.begin(), u.end());
    dvec temp_u(u.size());
    for(int i = 0; i < u.size(); i++)
        temp_u[i] = temp_std_u[i];
    ConfigWfafle::u = temp_u;
}

QList<double> InputControllerWfafle::get_v_vec() const
{
    std::vector<double> temp_std_v = std::vector<double>(ConfigWfafle::v.data(), ConfigWfafle::v.data() + ConfigWfafle::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_v.begin(), temp_std_v.end()));
}

void InputControllerWfafle::set_v_vec(QList<double> v) const
{
    std::vector<double> temp_std_v = std::vector<double>(v.begin(), v.end());
    dvec temp_v(v.size());
    for(int i = 0; i < v.size(); i++)
        temp_v[i] = temp_std_v[i];
    ConfigWfafle::v = temp_v;
}

QList<double> InputControllerWfafle::get_s_vec() const
{
    std::vector<double> temp_std_s = std::vector<double>(ConfigWfafle::s.data(), ConfigWfafle::s.data() + ConfigWfafle::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_s.begin(), temp_std_s.end()));
}

void InputControllerWfafle::set_s_vec(QList<double> s) const
{
    std::vector<double> temp_std_s = std::vector<double>(s.begin(), s.end());
    dvec temp_s(s.size());
    for(int i = 0; i < s.size(); i++)
        temp_s[i] = temp_std_s[i];
    ConfigWfafle::s = temp_s;
}

QList<double> InputControllerWfafle::get_h_vec() const
{
    std::vector<double> temp_std_h = std::vector<double>(ConfigWfafle::h.data(), ConfigWfafle::h.data() + ConfigWfafle::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_h.begin(), temp_std_h.end()));
}

void InputControllerWfafle::set_h_vec(QList<double> h) const
{
    std::vector<double> temp_std_h = std::vector<double>(h.begin(), h.end());
    dvec temp_h(h.size());
    for(int i = 0; i < h.size(); i++)
        temp_h[i] = temp_std_h[i];
    ConfigWfafle::h = temp_h;
}

QString InputControllerWfafle::get_num_comp() const
{
    return QString::fromStdString(std::to_string(ConfigWfafle::num_comp));
}

void InputControllerWfafle::set_num_comp(QString num_comp) const
{
    std::string num_comp_str = num_comp.toStdString();
    try {
        int num_comp_d = boost::lexical_cast<int>(num_comp_str);
        ConfigWfafle::num_comp = num_comp_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(num_comp_str.compare("") == 0) {
            errorMessage = "The field 'Starting Copies' (p) is empty." + num_comp_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Starting Copies' (p): " + num_comp_str + "\n";
        }
        ConfigWfafle::error += errorMessage;
    }
}
