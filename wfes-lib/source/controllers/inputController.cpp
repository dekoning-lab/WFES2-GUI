#include "inputController.h"

using namespace wfes::controllers;

InputController::InputController(QObject* parent): QObject(parent){
    emit input_changed();
}

InputController::~InputController(){}

QString InputController::get_n() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::population_size);

    if(isnan(wfes::config::Config::population_size))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_n(QString n) const
{
    std::string n_str = n.toStdString();
    double n_d = boost::lexical_cast<double>(n_str);
    wfes::config::Config::population_size = n_d;
}

QString InputController::get_a() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::a);

    if(isnan(wfes::config::Config::a))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_a(QString a) const
{
    std::string a_str = a.toStdString();
    double a_d = boost::lexical_cast<double>(a_str);
    wfes::config::Config::a = a_d;
}

QString InputController::get_p() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::starting_copies);

    if(isnan(wfes::config::Config::starting_copies))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_p(QString p) const
{
    std::string p_str = p.toStdString();
    double p_d = boost::lexical_cast<double>(p_str);
    wfes::config::Config::starting_copies = p_d;
}

QString InputController::get_c() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::integration_cutoff);

    if(isnan(wfes::config::Config::integration_cutoff))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_c(QString c) const
{
    std::string c_str = c.toStdString();
    double c_d = boost::lexical_cast<double>(c_str);
    wfes::config::Config::integration_cutoff = c_d;
}

QString InputController::get_x() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::observed_copies);

    if(isnan(wfes::config::Config::observed_copies))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_x(QString x) const
{
    std::string x_str = x.toStdString();
    double x_d = boost::lexical_cast<double>(x_str);
    wfes::config::Config::observed_copies = x_d;
}

QString InputController::get_u() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::u);

    if(isnan(wfes::config::Config::u))
        return "Error";
    else
        return QString::fromStdString(fmt.str());

}

void InputController::set_u(QString u) const
{
    std::string u_str = u.toStdString();
    double u_d = boost::lexical_cast<double>(u_str);
    wfes::config::Config::u = u_d;
}

QString InputController::get_v() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::v);

    if(isnan(wfes::config::Config::v))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_v(QString v) const
{
    std::string v_str = v.toStdString();
    double v_d = boost::lexical_cast<double>(v_str);
    wfes::config::Config::v = v_d;
}

QString InputController::get_s() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::s);

    if(isnan(wfes::config::Config::s))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_s(QString s) const
{
    std::string s_str = s.toStdString();
    double s_d = boost::lexical_cast<double>(s_str);
    wfes::config::Config::s = s_d;
}

QString InputController::get_h() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::h);

    if(isnan(wfes::config::Config::h))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_h(QString h) const
{
    std::string h_str = h.toStdString();
    double h_d = boost::lexical_cast<double>(h_str);
    wfes::config::Config::h = h_d;
}

QString InputController::get_t() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::Config::n_threads);

    if(isnan(wfes::config::Config::n_threads))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_t(QString t) const
{
    std::string t_str = t.toStdString();
    double t_d = boost::lexical_cast<double>(t_str);
    wfes::config::Config::n_threads = t_d;
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





