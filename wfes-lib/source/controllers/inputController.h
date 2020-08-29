#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>
#include "model/wfes_single.h"

#include "results/results.h"

#include <QString>
#include "math.h"
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

namespace wfes {
    namespace controllers {

        /**
         * @brief The InputController class contains a set of configuration values that can be set in the GUI by the user.
         * It has methods for setting GUI values from backend (for example, when starting the application and loading a previous configuration),
         * or getting input values set by the user in the GUI.
         */
        class WFESLIBSHARED_EXPORT InputController : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString ui_n READ get_n WRITE set_n NOTIFY input_changed)
            Q_PROPERTY(QString ui_a READ get_a WRITE set_a NOTIFY input_changed)
            Q_PROPERTY(QString ui_p READ get_p WRITE set_p NOTIFY input_changed)
            Q_PROPERTY(QString ui_c READ get_c WRITE set_c NOTIFY input_changed)
            Q_PROPERTY(QString ui_x READ get_x WRITE set_x NOTIFY input_changed)
            Q_PROPERTY(QString ui_k READ get_k WRITE set_k NOTIFY input_changed)
            Q_PROPERTY(QString ui_u READ get_u WRITE set_u NOTIFY input_changed)
            Q_PROPERTY(QString ui_v READ get_v WRITE set_v NOTIFY input_changed)
            Q_PROPERTY(QString ui_s READ get_s WRITE set_s NOTIFY input_changed)
            Q_PROPERTY(QString ui_h READ get_h WRITE set_h NOTIFY input_changed)
            Q_PROPERTY(QString ui_t READ get_t WRITE set_t NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_Q READ get_output_Q WRITE set_output_Q NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_R READ get_output_R WRITE set_output_R NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_N READ get_output_N WRITE set_output_N NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_NExt READ get_output_NExt WRITE set_output_NExt NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_NFix READ get_output_NFix WRITE set_output_NFix NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_B READ get_output_B WRITE set_output_B NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_I READ get_output_I WRITE set_output_I NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_E READ get_output_E WRITE set_output_E NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_V READ get_output_V WRITE set_output_V NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_Res READ get_output_Res WRITE set_output_Res NOTIFY input_changed)
            Q_PROPERTY(bool ui_m READ get_m WRITE set_m NOTIFY input_changed)
            Q_PROPERTY(bool ui_force READ get_force WRITE set_force NOTIFY input_changed)
            Q_PROPERTY(QString ui_modelType READ get_model_type WRITE set_model_type NOTIFY input_changed)
            Q_PROPERTY(QString ui_library READ get_library WRITE set_library NOTIFY input_changed)
            Q_PROPERTY(QString ui_solver READ get_solver WRITE set_solver NOTIFY input_changed)
            Q_PROPERTY(QString ui_initial_distribution READ get_initial_distribution_path WRITE set_initial_distribution_path NOTIFY input_changed)

            public:

                /**
                 * @brief InputController Constructor.
                 * @param parent To be used by Qt.
                 */
                explicit InputController(QObject* parent = nullptr);


                /**
                 * @brief InputController Destructor.
                 */
                ~InputController();

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
                 * @brief Send x to GUI.
                 * @return QString containing x.
                 */
                QString get_x() const;
                /**
                 * @brief Set x from  GUI.
                 * @param x value in GUI.
                 */
                void set_x(QString x) const;

                /**
                 * @brief Send k to GUI.
                 * @return QString containing x.
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
                 * @brief Send if output NExt to GUI.
                 * @return boolean containing if output NExt.
                 */
                bool get_output_NExt() const;
                /**
                 * @brief Get if output NExt from GUI.
                 * @param output_NExt value of output NExt in GUI.
                 */
                void set_output_NExt(bool output_NExt) const;


                /**
                 * @brief Send if output NFix to GUI.
                 * @return boolean containing if output NFix.
                 */
                bool get_output_NFix() const;
                /**
                 * @brief Get if output NFix from GUI.
                 * @param output_NFix value of output NFix in GUI.
                 */
                void set_output_NFix(bool output_NFix) const;


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
                 * @brief Send if output E to GUI.
                 * @return boolean containing if output E.
                 */
                bool get_output_E() const;
                /**
                 * @brief Get if output E from GUI.
                 * @param output_E value of output E in GUI.
                 */
                void set_output_E(bool output_E) const;


                /**
                 * @brief Send if output V to GUI.
                 * @return boolean containing if output V.
                 */
                bool get_output_V() const;
                /**
                 * @brief Get if output V from GUI.
                 * @param output_V value of output V in GUI.
                 */
                void set_output_V(bool output_V) const;


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
                 * @brief Send m to GUI.
                 * @return boolean containing m.
                 */
                bool get_m() const;
                /**
                 * @brief Get m from GUI.
                 * @param m value of m in GUI.
                 */
                void set_m(bool m) const;

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

            signals:
                /**
                 * @brief Signal for notifying when a value has changed in backend.
                 */
                void input_changed();
        };

    }
}

#endif //INPUTCONTROLLER_H
