#ifndef INPUTCONTROLLERWFESSWEEP_H
#define INPUTCONTROLLERWFESSWEEP_H

#include <QString>
#include <QObject>

#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include <wfes-lib_global.h>

#include "model/executables/wfes_sweep/config/configWfesSweep.h"
#include "utils/utils.h"

namespace wfes {
    namespace controllers {

        /**
         * @brief The InputControllerWfesSweep class is a controller for input parameters
         * of wfes sweep.
         */
        class WFESLIBSHARED_EXPORT InputControllerWfesSweep : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString ui_n READ get_n WRITE set_n NOTIFY input_changed)
            Q_PROPERTY(QString ui_p READ get_p WRITE set_p NOTIFY input_changed)
            Q_PROPERTY(QString ui_a READ get_a WRITE set_a NOTIFY input_changed)
            Q_PROPERTY(QString ui_c READ get_c WRITE set_c NOTIFY input_changed)
            Q_PROPERTY(QString ui_l READ get_l WRITE set_l NOTIFY input_changed)
            Q_PROPERTY(QString ui_t READ get_t WRITE set_t NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_Q READ get_output_Q WRITE set_output_Q NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_R READ get_output_R WRITE set_output_R NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_N READ get_output_N WRITE set_output_N NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_B READ get_output_B WRITE set_output_B NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_I READ get_output_I WRITE set_output_I NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_Res READ get_output_Res WRITE set_output_Res NOTIFY input_changed)
            Q_PROPERTY(bool ui_force READ get_force WRITE set_force NOTIFY input_changed)
            Q_PROPERTY(QString ui_modelType READ get_model_type WRITE set_model_type NOTIFY input_changed)
            Q_PROPERTY(QString ui_library READ get_library WRITE set_library NOTIFY input_changed)
            Q_PROPERTY(QString ui_solver READ get_solver WRITE set_solver NOTIFY input_changed)
            Q_PROPERTY(QString ui_initial_distribution READ get_initial_distribution_path WRITE set_initial_distribution_path NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_u_vec READ get_u_vec WRITE set_u_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_v_vec READ get_v_vec WRITE set_v_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_s_vec READ get_s_vec WRITE set_s_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_h_vec READ get_h_vec WRITE set_h_vec NOTIFY input_changed)

        public:
            /**
             * @brief InputControllerWfesSweep Constructor.
             * @param parent To be used by Qt.
             */
            explicit InputControllerWfesSweep(QObject* parent = nullptr);

            /**
             * @brief InputControllerWfesSweep Destructor.
             */
            ~InputControllerWfesSweep() = default;

            /**
             * @brief Send N to GUI.
             * @return QString containing N.
             */
            QString get_n() const;
            /**
             * @brief Set N from  GUI.
             * @param N value in GUI.
             */
            void set_n(QString n) const;

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
             * @brief Send l to GUI.
             * @return QString containing l.
             */
            QString get_l() const;

            /**
             * @brief Set l from  GUI.
             * @param l value in GUI.
             */
            void set_l(QString l) const;

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
             * @brief Send if output I to GUI.
             * @return boolean containing if output I.
             */
            bool get_output_I() const;
            /**
             * @brief Get if output I from GUI.
             * @param output_I value of output I in GUI.
             */
            void set_output_I(bool output_I) const;

            /**
             * @brief Send if output Res to GUI.
             * @return boolean containing if output Res.
             */
            bool get_output_Res() const;
            /**
             * @brief Get if output Res from GUI.
             * @param output_Res value of output Res in GUI.
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


#endif // INPUTCONTROLLERWFESSWEEP_H
