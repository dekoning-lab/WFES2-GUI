#ifndef INPUTCONTROLLERTIMEDIST_H
#define INPUTCONTROLLERTIMEDIST_H

#include <QObject>

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include <wfes-lib_global.h>

#include <model/executables/time_dist/config/configTimeDistSGV.h>
#include <model/executables/time_dist/config/configTimeDist.h>

namespace wfes {
    namespace controllers {

        /**
         * @brief The InputControllerTimeDist class is a controller for input parameters
         * of time dist.
         */
        class WFESLIBSHARED_EXPORT InputControllerTimeDist : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString ui_n READ get_n WRITE set_n NOTIFY input_changed)
            Q_PROPERTY(QString ui_n_sgv READ get_n_sgv WRITE set_n_sgv NOTIFY input_changed)
            Q_PROPERTY(QString ui_a READ get_a WRITE set_a NOTIFY input_changed)
            Q_PROPERTY(QString ui_a_sgv READ get_a_sgv WRITE set_a_sgv NOTIFY input_changed)
            Q_PROPERTY(QString ui_l READ get_l WRITE set_l NOTIFY input_changed)
            Q_PROPERTY(QString ui_c READ get_c WRITE set_c NOTIFY input_changed)
            Q_PROPERTY(QString ui_c_sgv READ get_c_sgv WRITE set_c_sgv NOTIFY input_changed)
            Q_PROPERTY(QString ui_m READ get_m WRITE set_m NOTIFY input_changed)
            Q_PROPERTY(QString ui_m_sgv READ get_m_sgv WRITE set_m_sgv NOTIFY input_changed)
            Q_PROPERTY(QString ui_u READ get_u WRITE set_u NOTIFY input_changed)
            Q_PROPERTY(QString ui_v READ get_v WRITE set_v NOTIFY input_changed)
            Q_PROPERTY(QString ui_s READ get_s WRITE set_s NOTIFY input_changed)
            Q_PROPERTY(QString ui_h READ get_h WRITE set_h NOTIFY input_changed)
            Q_PROPERTY(QString ui_t READ get_t WRITE set_t NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_P READ get_output_P WRITE set_output_P NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_Q READ get_output_Q WRITE set_output_Q NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_R READ get_output_R WRITE set_output_R NOTIFY input_changed)
            Q_PROPERTY(bool ui_r READ get_r WRITE set_r NOTIFY input_changed)
            Q_PROPERTY(bool ui_r_sgv READ get_r_sgv WRITE set_r_sgv NOTIFY input_changed)
            Q_PROPERTY(QString ui_modelType READ get_model_type WRITE set_model_type NOTIFY input_changed)
            Q_PROPERTY(QString ui_library READ get_library WRITE set_library NOTIFY input_changed)
            Q_PROPERTY(QString ui_solver READ get_solver WRITE set_solver NOTIFY input_changed)
            Q_PROPERTY(bool ui_force READ get_force WRITE set_force NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_u_vec READ get_u_vec WRITE set_u_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_v_vec READ get_v_vec WRITE set_v_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_s_vec READ get_s_vec WRITE set_s_vec NOTIFY input_changed)
            Q_PROPERTY(QList<double> ui_h_vec READ get_h_vec WRITE set_h_vec NOTIFY input_changed)

        public:

            /**
             * @brief InputControllerTimeDist Constructor.
             * @param parent To be used by Qt.
             */
            explicit InputControllerTimeDist(QObject* parent = nullptr);

            /**
             * @brief InputControllerTimeDist Destructor.
             */
            ~InputControllerTimeDist() = default;

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
             * @brief Send N to GUI.
             * @return QString containing N.
             */
            QString get_n_sgv() const;
            /**
             * @brief Set N from  GUI.
             * @param N value in GUI.
             */
            void set_n_sgv(QString n) const;

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
             * @brief Send a to GUI.
             * @return QString containing a.
             */
            QString get_a_sgv() const;
            /**
             * @brief Set a from  GUI.
             * @param a value in GUI.
             */
            void set_a_sgv(QString a) const;

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
             * @brief Send c to GUI.
             * @return QString containing c.
             */
            QString get_c_sgv() const;
            /**
             * @brief Set c from  GUI.
             * @param c value in GUI.
             */
            void set_c_sgv(QString c) const;

            /**
             * @brief Send m to GUI.
             * @return QString containing m.
             */
            QString get_m() const;
            /**
             * @brief Set m from  GUI.
             * @param m value in GUI.
             */
            void set_m(QString m) const;

            /**
             * @brief Send m to GUI.
             * @return QString containing m.
             */
            QString get_m_sgv() const;
            /**
             * @brief Set m from  GUI.
             * @param m value in GUI.
             */
            void set_m_sgv(QString m) const;

            /**
             * @brief Send u to GUI.
             * @return QString containing u.
             */
            QString get_u() const;
            /**
             * @brief Set u from  GUI.
             * @param u value in GUI.
             */
            void set_u(QString u) const;

            /**
             * @brief Send v to GUI.
             * @return QString containing v.
             */
            QString get_v() const;
            /**
             * @brief Set v from  GUI.
             * @param v value in GUI.
             */
            void set_v(QString v) const;

            /**
             * @brief Send s to GUI.
             * @return QString containing s.
             */
            QString get_s() const;
            /**
             * @brief Set s from  GUI.
             * @param s value in GUI.
             */
            void set_s(QString s) const;

            /**
             * @brief Send h to GUI.
             * @return QString containing h.
             */
            QString get_h() const;
            /**
             * @brief Set h from  GUI.
             * @param h value in GUI.
             */
            void set_h(QString h) const;

            /**
             * @brief Send t to GUI.
             * @return QString containing t.
             */
            QString get_t() const;
            /**
             * @brief Set t from  GUI.
             * @param t value in GUI.
             */
            void set_t(QString h) const;


            /**
             * @brief Send if output P to GUI.
             * @return boolean containing if output P.
             */
            bool get_output_P() const;
            /**
             * @brief Get if output P from GUI.
             * @param output_P value of output_P in GUI.
             */
            void set_output_P(bool output_P) const;


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
             * @brief Send r to GUI.
             * @return boolean containing r.
             */
            bool get_r() const;
            /**
             * @brief Get r from GUI.
             * @param r value of r in GUI.
             */
            void set_r(bool r) const;


            /**
             * @brief Send r to GUI.
             * @return boolean containing r.
             */
            bool get_r_sgv() const;
            /**
             * @brief Get r from GUI.
             * @param r value of r in GUI.
             */
            void set_r_sgv(bool r) const;


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
             * @brief Send if output R to GUI.
             * @return boolean containing if output R.
             */
            bool get_force() const;
            /**
             * @brief Get if output R from GUI.
             * @param output_R value of output R in GUI.
             */
            void set_force(bool output_R) const;


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
#endif // INPUTCONTROLLERTIMEDIST_H
