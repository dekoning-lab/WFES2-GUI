#ifndef INPUTCONTROLLERPHASETYPE_H
#define INPUTCONTROLLERPHASETYPE_H

#include <QString>
#include <QObject>

#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include <wfes-lib_global.h>

#include "model/executables/phase_type/config/configPhaseType.h"
#include "utils/utils.h"

namespace wfes {
    namespace controllers {

        /**
         * @brief The InputControllerPhaseType class is a controller for input parameters
         * of phase type.
         */
        class WFESLIBSHARED_EXPORT InputControllerPhaseType : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString ui_n READ get_n WRITE set_n NOTIFY input_changed)
            Q_PROPERTY(QString ui_a READ get_a WRITE set_a NOTIFY input_changed)
            Q_PROPERTY(QString ui_c READ get_c WRITE set_c NOTIFY input_changed)
            Q_PROPERTY(QString ui_k READ get_k WRITE set_k NOTIFY input_changed)
            Q_PROPERTY(QString ui_u READ get_u WRITE set_u NOTIFY input_changed)
            Q_PROPERTY(QString ui_v READ get_v WRITE set_v NOTIFY input_changed)
            Q_PROPERTY(QString ui_s READ get_s WRITE set_s NOTIFY input_changed)
            Q_PROPERTY(QString ui_h READ get_h WRITE set_h NOTIFY input_changed)
            Q_PROPERTY(QString ui_t READ get_t WRITE set_t NOTIFY input_changed)
            Q_PROPERTY(QString ui_m READ get_m WRITE set_m NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_P READ get_output_P WRITE set_output_P NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_Q READ get_output_Q WRITE set_output_Q NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_R READ get_output_R WRITE set_output_R NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_Moments READ get_output_Moments WRITE set_output_Moments NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_Res READ get_output_Res WRITE set_output_Res NOTIFY input_changed)
            Q_PROPERTY(bool ui_r READ get_r WRITE set_r NOTIFY input_changed)
            Q_PROPERTY(bool ui_force READ get_force WRITE set_force NOTIFY input_changed)
            Q_PROPERTY(QString ui_modelType READ get_model_type WRITE set_model_type NOTIFY input_changed)
            Q_PROPERTY(QString ui_library READ get_library WRITE set_library NOTIFY input_changed)
            Q_PROPERTY(QString ui_solver READ get_solver WRITE set_solver NOTIFY input_changed)

            public:

                /**
                 * @brief InputControllerPhaseType Constructor.
                 * @param parent To be used by Qt.
                 */
                explicit InputControllerPhaseType(QObject* parent = nullptr);

                /**
                 * @brief InputControllerPhaseType Destructor.
                 */
                ~InputControllerPhaseType() = default;

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
                 * @brief Send k to GUI.
                 * @return QString containing k.
                 */
                QString get_k() const;
                /**
                 * @brief Set k from  GUI.
                 * @param k value in GUI.
                 */
                void set_k(QString k) const;

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
                 * @brief Send if output Moments to GUI.
                 * @return boolean containing if output Moments.
                 */
                bool get_output_Moments() const;
                /**
                 * @brief Get if output Moments from GUI.
                 * @param output_Moments value of output Moments in GUI.
                 */
                void set_output_Moments(bool output_Moments) const;

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
                 * @brief Send r to GUI.
                 * @return boolean containing r.
                 */
                bool get_r() const;
                /**
                 * @brief Get r from GUI.
                 * @param m value of r in GUI.
                 */
                void set_r(bool r) const;

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

            signals:
                /**
                 * @brief Signal for notifying when a value has changed in backend.
                 */
                void input_changed();
        };
    }
}
#endif // INPUTCONTROLLERPHASETYPE_H
