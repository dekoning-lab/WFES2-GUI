#ifndef INPUTCONTROLLERWFESSWITCHING_H
#define INPUTCONTROLLERWFESSWITCHING_H

#include <QString>
#include <QObject>

#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include <wfes-lib_global.h>

#include <model/executables/wfes_switching/config/configWfesSwitching.h>
#include "utils/utils.h"

namespace wfes {
    namespace controllers {

    /**
     * @brief The InputControllerWfesSwitching class is a controller for input parameters
     * of wfes switching.
     */
        class WFESLIBSHARED_EXPORT InputControllerWfesSwitching : public QObject{
            Q_OBJECT
            Q_PROPERTY(QString ui_a READ get_a WRITE set_a NOTIFY input_changed)
            Q_PROPERTY(QString ui_c READ get_c WRITE set_c NOTIFY input_changed)
            Q_PROPERTY(QString ui_t READ get_t WRITE set_t NOTIFY input_changed)
            Q_PROPERTY(QString ui_num_comp READ get_num_comp WRITE set_num_comp NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_Q READ get_output_Q WRITE set_output_Q NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_R READ get_output_R WRITE set_output_R NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_N READ get_output_N WRITE set_output_N NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_B READ get_output_B WRITE set_output_B NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_N_Fix READ get_output_N_Fix WRITE set_output_N_Fix NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_N_Ext READ get_output_N_Ext WRITE set_output_N_Ext NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_Res READ get_output_Res WRITE set_output_Res NOTIFY input_changed)
            Q_PROPERTY(bool ui_force READ get_force WRITE set_force NOTIFY input_changed)
            Q_PROPERTY(QString ui_modelType READ get_model_type WRITE set_model_type NOTIFY input_changed)
            Q_PROPERTY(QString ui_library READ get_library WRITE set_library NOTIFY input_changed)
            Q_PROPERTY(QString ui_solver READ get_solver WRITE set_solver NOTIFY input_changed)
            Q_PROPERTY(QString ui_initial_distribution READ get_initial_distribution_path WRITE set_initial_distribution_path NOTIFY input_changed)
            Q_PROPERTY(QList<int> ui_N_vec READ get_N_vec WRITE set_N_vec NOTIFY input_changed)
            Q_PROPERTY(QStringList ui_r_vec READ get_r_vec WRITE set_r_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_p_vec READ get_p_vec WRITE set_p_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_u_vec READ get_u_vec WRITE set_u_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_v_vec READ get_v_vec WRITE set_v_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_s_vec READ get_s_vec WRITE set_s_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_h_vec READ get_h_vec WRITE set_h_vec NOTIFY input_changed)

            public:
                /**
                 * @brief InputControllerWfesSwitching Constructor.
                 * @param parent To be used by Qt.
                 */
                explicit InputControllerWfesSwitching(QObject* parent = nullptr);

                /**
                 * @brief InputControllerWfesSwitching Destructor.
                 */
                ~InputControllerWfesSwitching() = default;

                /**
                 * @brief Send a to GUI.
                 * @return QString containing a.
                 */
                QString get_a() const;
                /**
                 * @brief Set a from  GUI.
                 * @param a value in GUI.
                 */
                void set_a(QString a) const;

                /**
                 * @brief Send c to GUI.
                 * @return QString containing c.
                 */
                QString get_c() const;
                /**
                 * @brief Set c from  GUI.
                 * @param c value in GUI.
                 */
                void set_c(QString c) const;

                /**
                 * @brief Send t to GUI.
                 * @return QString containing t.
                 */
                QString get_t() const;
                /**
                 * @brief Set t from  GUI.
                 * @param t value in GUI.
                 */
                void set_t(QString t) const;

                /**
                 * @brief Send number of components to GUI.
                 * @return Number of components.
                 */
                QString get_num_comp() const;
                /**
                 * @brief Set number of components from GUI.
                 * @param num_comp Number of components.
                 */
                void set_num_comp(QString num_comp) const;

                /**
                 * @brief Send if output Q to GUI.
                 * @return boolean containing if output Q.
                 */
                bool get_output_Q() const;
                /**
                 * @brief Get if output Q from GUI.
                 * @param output_Q value of output_Q in GUI.
                 */
                void set_output_Q(bool output_Q) const;

                /**
                 * @brief Send if output R to GUI.
                 * @return boolean containing if output R.
                 */
                bool get_output_R() const;
                /**
                 * @brief Get if output R from GUI.
                 * @param output_R value of output R in GUI.
                 */
                void set_output_R(bool output_R) const;

                /**
                 * @brief Send if output N to GUI.
                 * @return boolean containing if output N in GUI.
                 */
                bool get_output_N() const;
                /**
                 * @brief Get if output N from GUI.
                 * @param output_N value of output N in GUI.
                 */
                void set_output_N(bool output_N) const;

                /**
                 * @brief Send if output B to GUI.
                 * @return boolean containing if output B.
                 */
                bool get_output_B() const;
                /**
                 * @brief Get if output B from GUI.
                 * @param output_B value of output B in GUI.
                 */
                void set_output_B(bool output_B) const;

                /**
                 * @brief Send if output NExt to GUI.
                 * @return boolean containing if output NExt.
                 */
                bool get_output_N_Ext() const;
                /**
                 * @brief Get if output NExt from GUI.
                 * @param output_NExt value of output NExt in GUI.
                 */
                void set_output_N_Ext(bool output_NExt) const;

                /**
                 * @brief Send if output NFix to GUI.
                 * @return boolean containing if output NFix.
                 */
                bool get_output_N_Fix() const;
                /**
                 * @brief Get if output NFix from GUI.
                 * @param output_NFix value of output NFix in GUI.
                 */
                void set_output_N_Fix(bool output_NFix) const;

                /**
                 * @brief Send if output Res to GUI.
                 * @return boolean containing if output Res.
                 */
                bool get_output_Res() const;
                /**
                 * @brief Get if output Res from GUI.
                 * @param output_Res value of output_Res in GUI.
                 */
                void set_output_Res(bool output_Res) const;

                /**
                 * @brief Send force to GUI.
                 * @return boolean containing force.
                 */
                bool get_force() const;
                /**
                 * @brief Get force from GUI.
                 * @param force value of force in GUI.
                 */
                void set_force(bool force) const;

                /**
                 * @brief Send model type to GUI.
                 * @return QString containing model type.
                 */
                QString get_model_type() const;
                /**
                 * @brief Get model type from GUI.
                 * @param model_type value of model type in GUI.
                 */
                void set_model_type(QString model_type) const;

                /**
                 * @brief Send library to GUI.
                 * @return QString containing library.
                 */
                QString get_library() const;
                /**
                 * @brief Get library from GUI.
                 * @param library value of library in GUI.
                 */
                void set_library(QString library) const;

                /**
                 * @brief Send solver to GUI.
                 * @return QString containing solver.
                 */
                QString get_solver() const;
                /**
                 * @brief Get solver from GUI.
                 * @param solver value of solver in GUI.
                 */
                void set_solver(QString solver) const;

                /**
                 * @brief Send initial_distribution_path to GUI.
                 * @return QString containing initial_distribution_path.
                 */
                QString get_initial_distribution_path() const;
                /**
                 * @brief Get initial_distribution_path from GUI.
                 * @param initial_distribution_path value of initial_distribution_path in GUI.
                 */
                void set_initial_distribution_path(QString initial_distribution_path) const;

                /**
                 * @brief Send vector of N to GUI.
                 * @return QList<double> containing N.
                 */
                QList<int> get_N_vec() const;
                /**
                 * @brief Set vector of N from  GUI.
                 * @param N value in GUI.
                 */
                void set_N_vec(QList<int> N) const;

                /**
                 * @brief Send vector of r to GUI.
                 * @return QString containing r.
                 */
                QStringList get_r_vec() const;
                /**
                 * @brief Set vector of r from  GUI.
                 * @param r value in GUI.
                 */
                void set_r_vec(QStringList r) const;

                /**
                 * @brief Send vector of p to GUI.
                 * @return QList<double> containing p.
                 */
                QList<double> get_p_vec() const;
                /**
                 * @brief Set vector of p from  GUI.
                 * @param p value in GUI.
                 */
                void set_p_vec(QList<double> p) const;

                /**
                 * @brief Send vector of u to GUI.
                 * @return QList<double> containing u.
                 */
                QList<double> get_u_vec() const;
                /**
                 * @brief Set vector of u from  GUI.
                 * @param u value in GUI.
                 */
                void set_u_vec(QList<double> u) const;

                /**
                 * @brief Send vector of v to GUI.
                 * @return QList<double> containing v.
                 */
                QList<double> get_v_vec() const;
                /**
                 * @brief Set vector of v from  GUI.
                 * @param v value in GUI.
                 */
                void set_v_vec(QList<double> v) const;

                /**
                 * @brief Send vector of s to GUI.
                 * @return QList<double> containing s.
                 */
                QList<double> get_s_vec() const;
                /**
                 * @brief Set vector of s from  GUI.
                 * @param s value in GUI.
                 */
                void set_s_vec(QList<double> s) const;

                /**
                 * @brief Send vector of h to GUI.
                 * @return QList<double> containing h.
                 */
                QList<double> get_h_vec() const;
                /**
                 * @brief Set vector of h from  GUI.
                 * @param h value in GUI.
                 */
                void set_h_vec(QList<double> h) const;


            signals:
                /**
                 * @brief Signal for notifying when a value has changed in backend.
                 */
                void input_changed();
            };
    }
}
#endif // INPUTCONTROLLERWFESSWITCHING_H
