#ifndef INPUTCONTROLLERWFAFD_H
#define INPUTCONTROLLERWFAFD_H

#include <QObject>

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include <wfes-lib_global.h>

#include "model/executables/wfafd/config/configWfafd.h"

namespace wfes {
    namespace controllers {

        /**
         * @brief The InputControllerWfafd class is a controller for input parameters
         * of wfafd.
         */
        class WFESLIBSHARED_EXPORT InputControllerWfafd : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString ui_a READ get_a WRITE set_a NOTIFY input_changed)
            Q_PROPERTY(QString ui_p READ get_p WRITE set_p NOTIFY input_changed)
            Q_PROPERTY(QString ui_t READ get_t WRITE set_t NOTIFY input_changed)
            Q_PROPERTY(QString ui_num_comp READ get_num_comp WRITE set_num_comp NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_Dist READ get_output_Dist WRITE set_output_Dist NOTIFY input_changed)
            Q_PROPERTY(bool ui_force READ get_force WRITE set_force NOTIFY input_changed)
            Q_PROPERTY(QString ui_library READ get_library WRITE set_library NOTIFY input_changed)
            Q_PROPERTY(QString ui_solver READ get_solver WRITE set_solver NOTIFY input_changed)
            Q_PROPERTY(QString ui_initial_distribution READ get_initial_distribution_path WRITE set_initial_distribution_path NOTIFY input_changed)
            Q_PROPERTY(QList<int> ui_N_vec READ get_N_vec WRITE set_N_vec NOTIFY input_changed)
            Q_PROPERTY(QList<int> ui_G_vec READ get_G_vec WRITE set_G_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_u_vec READ get_u_vec WRITE set_u_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_v_vec READ get_v_vec WRITE set_v_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_s_vec READ get_s_vec WRITE set_s_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_h_vec READ get_h_vec WRITE set_h_vec NOTIFY input_changed)


            public:
                /**
                 * @brief InputControllerWfafd Constructor.
                 * @param parent To be used by Qt.
                 */
                explicit InputControllerWfafd(QObject* parent = nullptr);

                /**
                 * @brief InputControllerWfafd Destructor.
                 */
                ~InputControllerWfafd() = default;

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
                 * @brief Send p to GUI.
                 * @return QString containing p.
                 */
                QString get_p() const;
                /**
                 * @brief Set p from  GUI.
                 * @param p value in GUI.
                 */
                void set_p(QString p) const;

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
                 * @brief Send if output Dist to GUI.
                 * @return boolean containing if output Dist.
                 */
                bool get_output_Dist() const;
                /**
                 * @brief Get if output Dist from GUI.
                 * @param output_Dist value of output_Dist in GUI.
                 */
                void set_output_Dist(bool output_Dist) const;

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
                 * @brief Send vector of G to GUI.
                 * @return QList<double> containing G.
                 */
                QList<int> get_G_vec() const;
                /**
                 * @brief Set vector of G from  GUI.
                 * @param G value in GUI.
                 */
                void set_G_vec(QList<int> G) const;

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

#endif // INPUTCONTROLLERWFAFD_H
