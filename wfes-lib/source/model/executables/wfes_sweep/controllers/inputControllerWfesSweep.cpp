#include "inputControllerWfesSweep.h"

using namespace wfes::controllers;
using namespace wfes::config;

InputControllerWfesSweep::InputControllerWfesSweep(QObject *parent): QObject(parent){
 emit input_changed();
}

InputControllerWfesSweep::~InputControllerWfesSweep() {}

QString InputControllerWfesSweep::get_n() const
{
    boost::format fmt = boost::format(DPFS) % (ConfigWfesSweep::population_size);

    if((boost::math::isnan)(ConfigWfesSweep::population_size))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSweep::set_n(QString n) const
{
    std::string n_str = n.toStdString();
    try {
        double n_d = boost::lexical_cast<double>(n_str);
        ConfigWfesSweep::population_size = n_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(n_str.compare("") == 0) {
            errorMessage = "The field 'Population' (N) is empty." + n_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Population' (N): " + n_str + "\n";
        }
        ConfigWfesSweep::error += errorMessage;
    }
}

QString InputControllerWfesSweep::get_p() const
{
    boost::format fmt = boost::format(DPFS) % (ConfigWfesSweep::starting_copies);

    if((boost::math::isnan)(ConfigWfesSweep::starting_copies))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSweep::set_p(QString p) const
{
    std::string p_str = p.toStdString();
    try {
        double p_d = boost::lexical_cast<double>(p_str);
        ConfigWfesSweep::starting_copies = p_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(p_str.compare("") == 0) {
            errorMessage = "The field 'Starting Copies' (p) is empty." + p_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Starting Copies' (p): " + p_str + "\n";
        }
        ConfigWfesSweep::error += errorMessage;
    }
}

QString InputControllerWfesSweep::get_a() const
{
    boost::format fmt = boost::format(DPFS) % (ConfigWfesSweep::a);

    if((boost::math::isnan)(ConfigWfesSweep::a))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSweep::set_a(QString a) const
{
    std::string a_str = a.toStdString();
    try {
        double a_d = boost::lexical_cast<double>(a_str);
        ConfigWfesSweep::a = a_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(a_str.compare("") == 0) {
            errorMessage = "The field 'Tail Truncation Weight' (a) is empty." + a_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Tail Truncation Weight' (a): " + a_str + "\n";
        }
        ConfigWfesSweep::error += errorMessage;
    }
}

QString InputControllerWfesSweep::get_c() const
{
    boost::format fmt = boost::format(DPFS) % (ConfigWfesSweep::integration_cutoff);

    if((boost::math::isnan)(ConfigWfesSweep::integration_cutoff))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSweep::set_c(QString c) const
{
    std::string c_str = c.toStdString();
    try {
        double c_d = boost::lexical_cast<double>(c_str);
        ConfigWfesSweep::integration_cutoff = c_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(c_str.compare("") == 0) {
            errorMessage = "The field 'Integration Cutoff' (c) is empty." + c_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Integration Cutoff' (c): " + c_str + "\n";
        }
        ConfigWfesSweep::error += errorMessage;
    }
}

QString InputControllerWfesSweep::get_l() const
{
    boost::format fmt = boost::format(DPFS) % (ConfigWfesSweep::l);

    if((boost::math::isnan)(ConfigWfesSweep::l))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSweep::set_l(QString l) const
{
    std::string l_str = l.toStdString();
    try {
        double l_d = boost::lexical_cast<double>(l_str);
        ConfigWfesSweep::l = l_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        //TODO Descriptive error.
        if(l_str.compare("") == 0) {
            errorMessage = "The field 'l' (l) is empty." + l_str + "\n";
        } else {
            errorMessage = "Wrong value for 'l' (l): " + l_str + "\n";
        }
        ConfigWfesSweep::error += errorMessage;
    }
}

QString InputControllerWfesSweep::get_t() const
{
    boost::format fmt = boost::format(DPFS) % (ConfigWfesSweep::n_threads);

    if((boost::math::isnan)(ConfigWfesSweep::n_threads))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSweep::set_t(QString t) const
{
    std::string t_str = t.toStdString();
    try {
        double t_d = boost::lexical_cast<double>(t_str);
        ConfigWfesSweep::n_threads = t_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(t_str.compare("") == 0) {
            errorMessage = "The field 'Number of Threads' (t) is empty." + t_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Number of Threads' (t): " + t_str + "\n";
        }
        ConfigWfesSweep::error += errorMessage;
    }
}

bool InputControllerWfesSweep::get_output_Q() const
{
    return ConfigWfesSweep::output_Q;
}

void InputControllerWfesSweep::set_output_Q(bool output_Q) const
{
    ConfigWfesSweep::output_Q = output_Q;
}

bool InputControllerWfesSweep::get_output_R() const
{
    return ConfigWfesSweep::output_R;
}

void InputControllerWfesSweep::set_output_R(bool output_R) const
{
    ConfigWfesSweep::output_R = output_R;
}

bool InputControllerWfesSweep::get_output_N() const
{
    return ConfigWfesSweep::output_N;
}

void InputControllerWfesSweep::set_output_N(bool output_N) const
{
    ConfigWfesSweep::output_N = output_N;
}

bool InputControllerWfesSweep::get_output_B() const
{
    return ConfigWfesSweep::output_B;
}

void InputControllerWfesSweep::set_output_B(bool output_B) const
{
    ConfigWfesSweep::output_B = output_B;
}

bool InputControllerWfesSweep::get_output_I() const
{
    return ConfigWfesSweep::output_I;
}

void InputControllerWfesSweep::set_output_I(bool output_I) const
{
    ConfigWfesSweep::output_I = output_I;
}

bool InputControllerWfesSweep::get_output_Res() const
{
    return ConfigWfesSweep::output_Res;
}

void InputControllerWfesSweep::set_output_Res(bool output_Res) const
{
    ConfigWfesSweep::output_Res = output_Res;
}

bool InputControllerWfesSweep::get_force() const
{
    return ConfigWfesSweep::force;
}

void InputControllerWfesSweep::set_force(bool force) const
{
    ConfigWfesSweep::force = force;
}

QString InputControllerWfesSweep::get_model_type() const
{
    return ModelTypeWfesSweepNames[ConfigWfesSweep::ModelTypeWfesSweepToInt(ConfigWfesSweep::modelType)];
}

void InputControllerWfesSweep::set_model_type(QString model_type) const
{
    if(model_type.compare(ModelTypeWfesSweepNames[ConfigWfesSweep::ModelTypeWfesSweepToInt(ModelTypeWfesSweep::NONE)]) == 0)
        ConfigWfesSweep::modelType = ModelTypeWfesSweep::NONE;
    if(model_type.compare(ModelTypeWfesSweepNames[ConfigWfesSweep::ModelTypeWfesSweepToInt(ModelTypeWfesSweep::FIXATION)]) == 0)
        ConfigWfesSweep::modelType = ModelTypeWfesSweep::FIXATION;
}

QString InputControllerWfesSweep::get_library() const
{
    return QString::fromStdString(ConfigWfesSweep::library);
}

void InputControllerWfesSweep::set_library(QString library) const
{
    ConfigWfesSweep::library = library.toStdString();
}

QString InputControllerWfesSweep::get_solver() const
{
    return QString::fromStdString(ConfigWfesSweep::vienna_solver);
}

void InputControllerWfesSweep::set_solver(QString solver) const
{
    ConfigWfesSweep::vienna_solver = solver.toStdString();
}

QString InputControllerWfesSweep::get_initial_distribution_path() const
{
    return QString::fromStdString(ConfigWfesSweep::initial_distribution_csv);
}

void InputControllerWfesSweep::set_initial_distribution_path(QString initial_distribution_path) const
{
    ConfigWfesSweep::initial_distribution_csv = initial_distribution_path.toStdString();
}

QList<double> InputControllerWfesSweep::get_u_vec() const
{
    std::vector<double> temp_std_u = std::vector<double>(ConfigWfesSweep::u.data(), ConfigWfesSweep::u.data() + ConfigWfesSweep::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_u.begin(), temp_std_u.end()));
}

void InputControllerWfesSweep::set_u_vec(QList<double> u) const
{
    std::vector<double> temp_std_u = std::vector<double>(u.begin(), u.end());
    dvec temp_u(2);
    temp_u[0] = temp_std_u[0];
    temp_u[1] = temp_std_u[1];
    ConfigWfesSweep::u = temp_u;
}

QList<double> InputControllerWfesSweep::get_v_vec() const
{
    std::vector<double> temp_std_v = std::vector<double>(ConfigWfesSweep::v.data(), ConfigWfesSweep::v.data() + ConfigWfesSweep::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_v.begin(), temp_std_v.end()));
}

void InputControllerWfesSweep::set_v_vec(QList<double> v) const
{
    std::vector<double> temp_std_v = std::vector<double>(v.begin(), v.end());
    dvec temp_v(2);
    temp_v[0] = temp_std_v[0];
    temp_v[1] = temp_std_v[1];
    ConfigWfesSweep::v = temp_v;
}

QList<double> InputControllerWfesSweep::get_s_vec() const
{
    std::vector<double> temp_std_s = std::vector<double>(ConfigWfesSweep::s.data(), ConfigWfesSweep::s.data() + ConfigWfesSweep::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_s.begin(), temp_std_s.end()));
}

void InputControllerWfesSweep::set_s_vec(QList<double> s) const
{
    std::vector<double> temp_std_s = std::vector<double>(s.begin(), s.end());
    dvec temp_s(2);
    temp_s[0] = temp_std_s[0];
    temp_s[1] = temp_std_s[1];
    ConfigWfesSweep::s = temp_s;
}

QList<double> InputControllerWfesSweep::get_h_vec() const
{
    std::vector<double> temp_std_h = std::vector<double>(ConfigWfesSweep::h.data(), ConfigWfesSweep::h.data() + ConfigWfesSweep::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_h.begin(), temp_std_h.end()));
}

void InputControllerWfesSweep::set_h_vec(QList<double> h) const
{
    std::vector<double> temp_std_h = std::vector<double>(h.begin(), h.end());
    dvec temp_h(2);
    temp_h[0] = temp_std_h[0];
    temp_h[1] = temp_std_h[1];
    ConfigWfesSweep::h = temp_h;
}
