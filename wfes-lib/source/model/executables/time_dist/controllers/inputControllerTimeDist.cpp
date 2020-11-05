#include "inputControllerTimeDist.h"

using namespace wfes::controllers;

InputControllerTimeDist::InputControllerTimeDist(QObject *parent): QObject(parent){
    emit input_changed();
}

InputControllerTimeDist::~InputControllerTimeDist() {}

QString InputControllerTimeDist::get_n() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDist::population_size);

    if((boost::math::isnan)(wfes::config::ConfigTimeDist::population_size))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_n(QString n) const
{
    std::string n_str = n.toStdString();
    try {
        double n_d = boost::lexical_cast<double>(n_str);
        wfes::config::ConfigTimeDist::population_size = n_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(n_str.compare("") == 0) {
            errorMessage = "The field 'Population' (N) is empty." + n_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Population' (N): " + n_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

QString InputControllerTimeDist::get_n_sgv() const
{

    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDistSGV::population_size);

    if((boost::math::isnan)(wfes::config::ConfigTimeDistSGV::population_size))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_n_sgv(QString n) const
{
    std::string n_str = n.toStdString();
    try {
        double n_d = boost::lexical_cast<double>(n_str);
        wfes::config::ConfigTimeDistSGV::population_size = n_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(n_str.compare("") == 0) {
            errorMessage = "The field 'Population' (N) is empty." + n_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Population' (N): " + n_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

QString InputControllerTimeDist::get_a() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDist::a);

    if((boost::math::isnan)(wfes::config::ConfigTimeDist::a))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_a(QString a) const
{
    std::string a_str = a.toStdString();
    try {
        double a_d = boost::lexical_cast<double>(a_str);
        wfes::config::ConfigTimeDist::a = a_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(a_str.compare("") == 0) {
            errorMessage = "The field 'Tail Truncation Weight' (a) is empty." + a_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Tail Truncation Weight' (a): " + a_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

QString InputControllerTimeDist::get_a_sgv() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDistSGV::a);

    if((boost::math::isnan)(wfes::config::ConfigTimeDistSGV::a))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_a_sgv(QString a) const
{
    std::string a_str = a.toStdString();
    try {
        double a_d = boost::lexical_cast<double>(a_str);
        wfes::config::ConfigTimeDistSGV::a = a_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(a_str.compare("") == 0) {
            errorMessage = "The field 'Tail Truncation Weight' (a) is empty." + a_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Tail Truncation Weight' (a): " + a_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

QString InputControllerTimeDist::get_l() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDistSGV::l);

    if((boost::math::isnan)(wfes::config::ConfigTimeDistSGV::l))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_l(QString l) const
{
    std::string l_str = l.toStdString();
    try {
        double l_d = boost::lexical_cast<double>(l_str);
        wfes::config::ConfigTimeDistSGV::l = l_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        //TODO Descriptive error.
        if(l_str.compare("") == 0) {
            errorMessage = "The field 'l' (l) is empty." + l_str + "\n";
        } else {
            errorMessage = "Wrong value for 'l' (l): " + l_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

QString InputControllerTimeDist::get_c() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDist::integration_cutoff);

    if((boost::math::isnan)(wfes::config::ConfigTimeDist::integration_cutoff))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_c(QString c) const
{
    std::string c_str = c.toStdString();
    try {
        double c_d = boost::lexical_cast<double>(c_str);
        wfes::config::ConfigTimeDist::integration_cutoff = c_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(c_str.compare("") == 0) {
            errorMessage = "The field 'Integration Cutoff' (c) is empty." + c_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Integration Cutoff' (c): " + c_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

QString InputControllerTimeDist::get_c_sgv() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDistSGV::integration_cutoff);

    if((boost::math::isnan)(wfes::config::ConfigTimeDistSGV::integration_cutoff))
        return "Error";
    else
        return QString::fromStdString(fmt.str());

}

void InputControllerTimeDist::set_c_sgv(QString c) const
{
    std::string c_str = c.toStdString();
    try {
        double c_d = boost::lexical_cast<double>(c_str);
        wfes::config::ConfigTimeDistSGV::integration_cutoff = c_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(c_str.compare("") == 0) {
            errorMessage = "The field 'Integration Cutoff' (c) is empty." + c_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Integration Cutoff' (c): " + c_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

QString InputControllerTimeDist::get_m() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDist::max_t);

    if((boost::math::isnan)(wfes::config::ConfigTimeDist::max_t))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_m(QString m) const
{
    std::string m_str = m.toStdString();
    try {
        double m_d = boost::lexical_cast<double>(m_str);
        wfes::config::ConfigTimeDist::max_t = m_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(m_str.compare("") == 0) {
            errorMessage = "The field 'Max. num. generations' (m) is empty." + m_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Max. num. generations' (m): " + m_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

QString InputControllerTimeDist::get_m_sgv() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDistSGV::max_t);

    if((boost::math::isnan)(wfes::config::ConfigTimeDistSGV::max_t))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_m_sgv(QString m) const
{
    std::string m_str = m.toStdString();
    try {
        double m_d = boost::lexical_cast<double>(m_str);
        wfes::config::ConfigTimeDistSGV::max_t = m_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(m_str.compare("") == 0) {
            errorMessage = "The field 'Max. num. generations' (m) is empty." + m_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Max. num. generations' (m): " + m_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}


QString InputControllerTimeDist::get_u() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDist::u);

    if((boost::math::isnan)(wfes::config::ConfigTimeDist::u))
        return "Error";
    else
        return QString::fromStdString(fmt.str());

}

void InputControllerTimeDist::set_u(QString u) const
{
    std::string u_str = u.toStdString();
    try {
        double u_d = boost::lexical_cast<double>(u_str);
        wfes::config::ConfigTimeDist::u = u_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(u_str.compare("") == 0) {
            errorMessage = "The field 'Backward Mutation Rate' (u) is empty." + u_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Backward Mutation Rate' (u): " + u_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

QString InputControllerTimeDist::get_v() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDist::v);

    if((boost::math::isnan)(wfes::config::ConfigTimeDist::v))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_v(QString v) const
{
    std::string v_str = v.toStdString();
    try {
        double v_d = boost::lexical_cast<double>(v_str);
        wfes::config::ConfigTimeDist::v = v_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(v_str.compare("") == 0) {
            errorMessage = "The field 'Forward Mutation Rate' (v) is empty." + v_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Forward Mutation Rate' (v): " + v_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

QString InputControllerTimeDist::get_s() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDist::s);

    if((boost::math::isnan)(wfes::config::ConfigTimeDist::s))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_s(QString s) const
{
    std::string s_str = s.toStdString();
    try {
        double s_d = boost::lexical_cast<double>(s_str);
        wfes::config::ConfigTimeDist::s = s_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(s_str.compare("") == 0) {
            errorMessage = "The field 'Selection Coefficient' (s) is empty." + s_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Selection Coefficient' (s): " + s_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

QString InputControllerTimeDist::get_h() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDist::h);

    if((boost::math::isnan)(wfes::config::ConfigTimeDist::h))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_h(QString h) const
{
    std::string h_str = h.toStdString();
    try {
        double h_d = boost::lexical_cast<double>(h_str);
        wfes::config::ConfigTimeDist::h = h_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(h_str.compare("") == 0) {
            errorMessage = "The field 'Dominance Coefficient' (h) is empty." + h_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Dominance Coefficient' (h): " + h_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

QString InputControllerTimeDist::get_t() const
{
    boost::format fmt = boost::format(DPFS) % (wfes::config::ConfigTimeDist::n_threads);

    if((boost::math::isnan)(wfes::config::ConfigTimeDist::n_threads))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputControllerTimeDist::set_t(QString t) const
{
    std::string t_str = t.toStdString();
    try {
        double t_d = boost::lexical_cast<double>(t_str);
        wfes::config::ConfigTimeDist::n_threads = t_d;
    } catch(boost::exception const&  ex) {
        std::string errorMessage = "";
        if(t_str.compare("") == 0) {
            errorMessage = "The field 'Number of Threads' (t) is empty." + t_str + "\n";
        } else {
            errorMessage = "Wrong value for 'Number of Threads' (t): " + t_str + "\n";
        }
        wfes::config::ConfigTimeDist::error += errorMessage;
    }
}

bool InputControllerTimeDist::get_output_P() const
{
    return wfes::config::ConfigTimeDist::output_P;
}

void InputControllerTimeDist::set_output_P(bool output_P) const
{
    wfes::config::ConfigTimeDist::output_P = output_P;
}

bool InputControllerTimeDist::get_output_Q() const
{
    return wfes::config::ConfigTimeDist::output_Q;
}

void InputControllerTimeDist::set_output_Q(bool output_Q) const
{
    wfes::config::ConfigTimeDist::output_Q = output_Q;
}

bool InputControllerTimeDist::get_output_R() const
{
    return wfes::config::ConfigTimeDist::output_R;
}

void InputControllerTimeDist::set_output_R(bool output_R) const
{
    wfes::config::ConfigTimeDist::output_R = output_R;
}

bool InputControllerTimeDist::get_r() const
{
    return wfes::config::ConfigTimeDist::no_rem;
}

void InputControllerTimeDist::set_r(bool r) const
{
    wfes::config::ConfigTimeDist::no_rem = r;
}

bool InputControllerTimeDist::get_r_sgv() const
{
    return wfes::config::ConfigTimeDistSGV::no_rem;
}

void InputControllerTimeDist::set_r_sgv(bool r) const
{
    wfes::config::ConfigTimeDistSGV::no_rem = r;
}

QString InputControllerTimeDist::get_model_type() const
{
    return wfes::config::ModelTypeTimeDistNames[wfes::config::ConfigTimeDist::ModelTypeTimeDistToInt(wfes::config::ConfigTimeDist::modelType)];
}

void InputControllerTimeDist::set_model_type(QString model_type) const
{
    if(model_type.compare(wfes::config::ModelTypeTimeDistNames[wfes::config::ConfigTimeDist::ModelTypeTimeDistToInt(wfes::config::ModelTypeTimeDist::NONE)]) == 0)
        wfes::config::ConfigTimeDist::modelType = wfes::config::ModelTypeTimeDist::NONE;
    if(model_type.compare(wfes::config::ModelTypeTimeDistNames[wfes::config::ConfigTimeDist::ModelTypeTimeDistToInt(wfes::config::ModelTypeTimeDist::TIME_DIST)]) == 0)
        wfes::config::ConfigTimeDist::modelType = wfes::config::ModelTypeTimeDist::TIME_DIST;
    if(model_type.compare(wfes::config::ModelTypeTimeDistNames[wfes::config::ConfigTimeDist::ModelTypeTimeDistToInt(wfes::config::ModelTypeTimeDist::TIME_DIST_SGV)]) == 0)
        wfes::config::ConfigTimeDist::modelType = wfes::config::ModelTypeTimeDist::TIME_DIST_SGV;
    if(model_type.compare(wfes::config::ModelTypeTimeDistNames[wfes::config::ConfigTimeDist::ModelTypeTimeDistToInt(wfes::config::ModelTypeTimeDist::TIME_DIST_SKIP)]) == 0)
        wfes::config::ConfigTimeDist::modelType = wfes::config::ModelTypeTimeDist::TIME_DIST_SKIP;
    if(model_type.compare(wfes::config::ModelTypeTimeDistNames[wfes::config::ConfigTimeDist::ModelTypeTimeDistToInt(wfes::config::ModelTypeTimeDist::TIME_DIST_DUAL)]) == 0)
        wfes::config::ConfigTimeDist::modelType = wfes::config::ModelTypeTimeDist::TIME_DIST_DUAL;

}

QString InputControllerTimeDist::get_library() const
{
    return QString::fromStdString(wfes::config::ConfigTimeDist::library);
}

void InputControllerTimeDist::set_library(QString library) const
{
    wfes::config::ConfigTimeDist::library = library.toStdString();
}

QString InputControllerTimeDist::get_solver() const
{
    return QString::fromStdString(wfes::config::ConfigTimeDist::vienna_solver);
}

void InputControllerTimeDist::set_solver(QString solver) const
{
    wfes::config::ConfigTimeDist::vienna_solver = solver.toStdString();
}

bool InputControllerTimeDist::get_force() const
{
    return wfes::config::ConfigTimeDistSGV::force;
}

void InputControllerTimeDist::set_force(bool force) const
{
    wfes::config::ConfigTimeDistSGV::force = force;
}

QList<double> InputControllerTimeDist::get_u_vec() const
{
    std::vector<double> temp_std_u = std::vector<double>(wfes::config::ConfigTimeDistSGV::u.data(), wfes::config::ConfigTimeDistSGV::u.data() + wfes::config::ConfigTimeDistSGV::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_u.begin(), temp_std_u.end()));
}

void InputControllerTimeDist::set_u_vec(QList<double> u) const
{
    std::vector<double> temp_std_u = std::vector<double>(u.begin(), u.end());
    dvec temp_u(2);
    temp_u[0] = temp_std_u[0];
    temp_u[1] = temp_std_u[1];
    wfes::config::ConfigTimeDistSGV::u = temp_u;
}

QList<double> InputControllerTimeDist::get_v_vec() const
{
    std::vector<double> temp_std_v = std::vector<double>(wfes::config::ConfigTimeDistSGV::v.data(), wfes::config::ConfigTimeDistSGV::v.data() + wfes::config::ConfigTimeDistSGV::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_v.begin(), temp_std_v.end()));
}

void InputControllerTimeDist::set_v_vec(QList<double> v) const
{
    std::vector<double> temp_std_v = std::vector<double>(v.begin(), v.end());
    dvec temp_v(2);
    temp_v[0] = temp_std_v[0];
    temp_v[1] = temp_std_v[1];
    wfes::config::ConfigTimeDistSGV::v = temp_v;
}

QList<double> InputControllerTimeDist::get_s_vec() const
{
    std::vector<double> temp_std_s = std::vector<double>(wfes::config::ConfigTimeDistSGV::s.data(), wfes::config::ConfigTimeDistSGV::s.data() + wfes::config::ConfigTimeDistSGV::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_s.begin(), temp_std_s.end()));
}

void InputControllerTimeDist::set_s_vec(QList<double> s) const
{
    std::vector<double> temp_std_s = std::vector<double>(s.begin(), s.end());
    dvec temp_s(2);
    temp_s[0] = temp_std_s[0];
    temp_s[1] = temp_std_s[1];
    wfes::config::ConfigTimeDistSGV::s = temp_s;
}

QList<double> InputControllerTimeDist::get_h_vec() const
{
    std::vector<double> temp_std_h = std::vector<double>(wfes::config::ConfigTimeDistSGV::h.data(), wfes::config::ConfigTimeDistSGV::h.data() + wfes::config::ConfigTimeDistSGV::num_comp);
    return QList<double>::fromVector(QVector<double>(temp_std_h.begin(), temp_std_h.end()));
}

void InputControllerTimeDist::set_h_vec(QList<double> h) const
{
    std::vector<double> temp_std_h = std::vector<double>(h.begin(), h.end());
    dvec temp_h(2);
    temp_h[0] = temp_std_h[0];
    temp_h[1] = temp_std_h[1];
    wfes::config::ConfigTimeDistSGV::h = temp_h;
}
