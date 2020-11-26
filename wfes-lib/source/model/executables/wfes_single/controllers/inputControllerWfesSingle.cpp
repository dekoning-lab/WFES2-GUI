#include "inputControllerWfesSingle.h"

using namespace wfes::controllers;

InputControllerWfesSingle::InputControllerWfesSingle(QObject* parent): QObject(parent){
    emit input_changed();
}

QString InputControllerWfesSingle::get_n() const {
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigWfesSingle::population_size);

    if((boost::math::isnan)(wfes::config::ConfigWfesSingle::population_size))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSingle::set_n(QString n) const {
    std::string n_str = n.toStdString();

    double n_d = boost::lexical_cast<double>(n_str);
    wfes::config::ConfigWfesSingle::population_size = n_d;
}

QString InputControllerWfesSingle::get_a() const {
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigWfesSingle::a);

    if((boost::math::isnan)(wfes::config::ConfigWfesSingle::a))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSingle::set_a(QString a) const {
    std::string a_str = a.toStdString();

    double a_d = boost::lexical_cast<double>(a_str);
    wfes::config::ConfigWfesSingle::a = a_d;
}

QString InputControllerWfesSingle::get_p() const {
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigWfesSingle::starting_copies);

    if((boost::math::isnan)(wfes::config::ConfigWfesSingle::starting_copies))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSingle::set_p(QString p) const {
    std::string p_str = p.toStdString();

    double p_d = boost::lexical_cast<double>(p_str);
    wfes::config::ConfigWfesSingle::starting_copies = p_d;
}

QString InputControllerWfesSingle::get_c() const {
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigWfesSingle::integration_cutoff);

    if((boost::math::isnan)(wfes::config::ConfigWfesSingle::integration_cutoff))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSingle::set_c(QString c) const {
    std::string c_str = c.toStdString();

    double c_d = boost::lexical_cast<double>(c_str);
    wfes::config::ConfigWfesSingle::integration_cutoff = c_d;
}

QString InputControllerWfesSingle::get_x() const {
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigWfesSingle::observed_copies);

    if((boost::math::isnan)(wfes::config::ConfigWfesSingle::observed_copies))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSingle::set_x(QString x) const {
    std::string x_str = x.toStdString();

    double x_d = boost::lexical_cast<double>(x_str);
    wfes::config::ConfigWfesSingle::observed_copies = x_d;

}

QString InputControllerWfesSingle::get_k() const {
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigWfesSingle::odds_ratio);

    if((boost::math::isnan)(wfes::config::ConfigWfesSingle::odds_ratio))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSingle::set_k(QString k) const {
    std::string k_str = k.toStdString();

    double k_d = boost::lexical_cast<double>(k_str);
    wfes::config::ConfigWfesSingle::odds_ratio = k_d;
}

QString InputControllerWfesSingle::get_u() const {
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigWfesSingle::u);

    if((boost::math::isnan)(wfes::config::ConfigWfesSingle::u))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSingle::set_u(QString u) const {
    std::string u_str = u.toStdString();

    double u_d = boost::lexical_cast<double>(u_str);
    wfes::config::ConfigWfesSingle::u = u_d;
}

QString InputControllerWfesSingle::get_v() const {
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigWfesSingle::v);

    if((boost::math::isnan)(wfes::config::ConfigWfesSingle::v))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSingle::set_v(QString v) const {
    std::string v_str = v.toStdString();

    double v_d = boost::lexical_cast<double>(v_str);
    wfes::config::ConfigWfesSingle::v = v_d;
}

QString InputControllerWfesSingle::get_s() const {
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigWfesSingle::s);

    if((boost::math::isnan)(wfes::config::ConfigWfesSingle::s))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSingle::set_s(QString s) const {
    std::string s_str = s.toStdString();

    double s_d = boost::lexical_cast<double>(s_str);
    wfes::config::ConfigWfesSingle::s = s_d;
}

QString InputControllerWfesSingle::get_h() const {
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigWfesSingle::h);

    if((boost::math::isnan)(wfes::config::ConfigWfesSingle::h))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSingle::set_h(QString h) const {
    std::string h_str = h.toStdString();

    double h_d = boost::lexical_cast<double>(h_str);
    wfes::config::ConfigWfesSingle::h = h_d;
}

QString InputControllerWfesSingle::get_t() const {
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigWfesSingle::n_threads);

    if((boost::math::isnan)(wfes::config::ConfigWfesSingle::n_threads))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerWfesSingle::set_t(QString t) const {
    std::string t_str = t.toStdString();

    double t_d = boost::lexical_cast<double>(t_str);
    wfes::config::ConfigWfesSingle::n_threads = t_d;

}

bool InputControllerWfesSingle::get_output_Q() const {
    return wfes::config::ConfigWfesSingle::output_Q;
}

void InputControllerWfesSingle::set_output_Q(bool output_Q) const {
    wfes::config::ConfigWfesSingle::output_Q = output_Q;
}

bool InputControllerWfesSingle::get_output_R() const {
    return wfes::config::ConfigWfesSingle::output_R;
}

void InputControllerWfesSingle::set_output_R(bool output_R) const {
    wfes::config::ConfigWfesSingle::output_R = output_R;
}

bool InputControllerWfesSingle::get_output_N() const {
    return wfes::config::ConfigWfesSingle::output_N;
}

void InputControllerWfesSingle::set_output_N(bool output_N) const {
    wfes::config::ConfigWfesSingle::output_N = output_N;
}

bool InputControllerWfesSingle::get_output_NExt() const {
    return wfes::config::ConfigWfesSingle::output_N_ext;
}

void InputControllerWfesSingle::set_output_NExt(bool output_NExt) const {
    wfes::config::ConfigWfesSingle::output_N_ext = output_NExt;
}

bool InputControllerWfesSingle::get_output_NFix() const {
    return wfes::config::ConfigWfesSingle::output_N_fix;
}

void InputControllerWfesSingle::set_output_NFix(bool output_NFix) const {
    wfes::config::ConfigWfesSingle::output_N_fix = output_NFix;
}

bool InputControllerWfesSingle::get_output_B() const {
    return wfes::config::ConfigWfesSingle::output_B;
}

void InputControllerWfesSingle::set_output_B(bool output_B) const {
    wfes::config::ConfigWfesSingle::output_B = output_B;
}

bool InputControllerWfesSingle::get_output_I() const {
    return wfes::config::ConfigWfesSingle::output_I;
}

void InputControllerWfesSingle::set_output_I(bool output_I) const {
    wfes::config::ConfigWfesSingle::output_I = output_I;
}

bool InputControllerWfesSingle::get_output_E() const {
    return wfes::config::ConfigWfesSingle::output_E;
}

void InputControllerWfesSingle::set_output_E(bool output_E) const {
    wfes::config::ConfigWfesSingle::output_E = output_E;
}

bool InputControllerWfesSingle::get_output_V() const {
    return wfes::config::ConfigWfesSingle::output_V;
}

void InputControllerWfesSingle::set_output_V(bool output_V) const {
    wfes::config::ConfigWfesSingle::output_V = output_V;
}

bool InputControllerWfesSingle::get_output_Res() const {
    return wfes::config::ConfigWfesSingle::output_Res;
}

void InputControllerWfesSingle::set_output_Res(bool output_Res) const {
    wfes::config::ConfigWfesSingle::output_Res = output_Res;
}

bool InputControllerWfesSingle::get_m() const {
    return wfes::config::ConfigWfesSingle::no_rem;
}

void InputControllerWfesSingle::set_m(bool m) const {
    wfes::config::ConfigWfesSingle::no_rem = m;
}

bool InputControllerWfesSingle::get_force() const {
    return wfes::config::ConfigWfesSingle::force;
}

void InputControllerWfesSingle::set_force(bool force) const {
    wfes::config::ConfigWfesSingle::force = force;
}

QString InputControllerWfesSingle::get_model_type() const {
    return wfes::config::ModelTypeWfesSingleNames[wfes::config::ConfigWfesSingle::ModelTypeWfesSingleToInt(wfes::config::ConfigWfesSingle::modelType)];
}

void InputControllerWfesSingle::set_model_type(QString model_type) const {
    if(model_type.compare(wfes::config::ModelTypeWfesSingleNames[wfes::config::ConfigWfesSingle::ModelTypeWfesSingleToInt(wfes::config::ModelTypeWfesSingle::NONE)]) == 0)
        wfes::config::ConfigWfesSingle::modelType = wfes::config::ModelTypeWfesSingle::NONE;
    if(model_type.compare(wfes::config::ModelTypeWfesSingleNames[wfes::config::ConfigWfesSingle::ModelTypeWfesSingleToInt(wfes::config::ModelTypeWfesSingle::FIXATION)]) == 0)
        wfes::config::ConfigWfesSingle::modelType = wfes::config::ModelTypeWfesSingle::FIXATION;
    if(model_type.compare(wfes::config::ModelTypeWfesSingleNames[wfes::config::ConfigWfesSingle::ModelTypeWfesSingleToInt(wfes::config::ModelTypeWfesSingle::ABSORPTION)]) == 0)
        wfes::config::ConfigWfesSingle::modelType = wfes::config::ModelTypeWfesSingle::ABSORPTION;
    if(model_type.compare(wfes::config::ModelTypeWfesSingleNames[wfes::config::ConfigWfesSingle::ModelTypeWfesSingleToInt(wfes::config::ModelTypeWfesSingle::ESTABLISHMENT)]) == 0)
        wfes::config::ConfigWfesSingle::modelType = wfes::config::ModelTypeWfesSingle::ESTABLISHMENT;
    if(model_type.compare(wfes::config::ModelTypeWfesSingleNames[wfes::config::ConfigWfesSingle::ModelTypeWfesSingleToInt(wfes::config::ModelTypeWfesSingle::FUNDAMENTAL)]) == 0)
        wfes::config::ConfigWfesSingle::modelType = wfes::config::ModelTypeWfesSingle::FUNDAMENTAL;
    if(model_type.compare(wfes::config::ModelTypeWfesSingleNames[wfes::config::ConfigWfesSingle::ModelTypeWfesSingleToInt(wfes::config::ModelTypeWfesSingle::EQUILIBRIUM)]) == 0)
        wfes::config::ConfigWfesSingle::modelType = wfes::config::ModelTypeWfesSingle::EQUILIBRIUM;
    if(model_type.compare(wfes::config::ModelTypeWfesSingleNames[wfes::config::ConfigWfesSingle::ModelTypeWfesSingleToInt(wfes::config::ModelTypeWfesSingle::NON_ABSORBING)]) == 0)
        wfes::config::ConfigWfesSingle::modelType = wfes::config::ModelTypeWfesSingle::NON_ABSORBING;
    if(model_type.compare(wfes::config::ModelTypeWfesSingleNames[wfes::config::ConfigWfesSingle::ModelTypeWfesSingleToInt(wfes::config::ModelTypeWfesSingle::ALLELE_AGE)]) == 0)
        wfes::config::ConfigWfesSingle::modelType = wfes::config::ModelTypeWfesSingle::ALLELE_AGE;
}

QString InputControllerWfesSingle::get_library() const {
    return QString::fromStdString(wfes::config::ConfigWfesSingle::library);
}

void InputControllerWfesSingle::set_library(QString library) const {
    wfes::config::ConfigWfesSingle::library = library.toStdString();
}

QString InputControllerWfesSingle::get_solver() const {
    return QString::fromStdString(wfes::config::ConfigWfesSingle::vienna_solver);
}

void InputControllerWfesSingle::set_solver(QString solver) const {
    wfes::config::ConfigWfesSingle::vienna_solver = solver.toStdString();
}

QString InputControllerWfesSingle::get_initial_distribution_path() const {
    return QString::fromStdString(wfes::config::ConfigWfesSingle::initial_distribution_csv);
}

void InputControllerWfesSingle::set_initial_distribution_path(QString initial_distribution_path) const {
    wfes::config::ConfigWfesSingle::initial_distribution_csv = initial_distribution_path.toStdString();
}





