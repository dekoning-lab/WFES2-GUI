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

        class WFESLIBSHARED_EXPORT InputController : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString ui_n READ get_n WRITE set_n NOTIFY input_changed)
            Q_PROPERTY(QString ui_a READ get_a WRITE set_a NOTIFY input_changed)
            Q_PROPERTY(QString ui_p READ get_p WRITE set_p NOTIFY input_changed)
            Q_PROPERTY(QString ui_c READ get_c WRITE set_c NOTIFY input_changed)
            Q_PROPERTY(QString ui_x READ get_x WRITE set_x NOTIFY input_changed)
            Q_PROPERTY(QString ui_u READ get_u WRITE set_u NOTIFY input_changed)
            Q_PROPERTY(QString ui_v READ get_v WRITE set_v NOTIFY input_changed)
            Q_PROPERTY(QString ui_s READ get_s WRITE set_s NOTIFY input_changed)
            Q_PROPERTY(QString ui_h READ get_h WRITE set_h NOTIFY input_changed)
            Q_PROPERTY(QString ui_t READ get_t WRITE set_t NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_Q READ get_output_Q WRITE set_output_Q NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_R READ get_output_R WRITE set_output_R NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_N READ get_output_N WRITE set_output_N NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_B READ get_output_B WRITE set_output_B NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_I READ get_output_I WRITE set_output_I NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_E READ get_output_E WRITE set_output_E NOTIFY input_changed)
            Q_PROPERTY(bool ui_output_V READ get_output_V WRITE set_output_V NOTIFY input_changed)

            public:
                explicit InputController(QObject* parent = nullptr);
                ~InputController();

                QString get_n() const;
                void set_n(QString n) const;

                QString get_a() const;
                void set_a(QString a) const;

                QString get_p() const;
                void set_p(QString p) const;

                QString get_c() const;
                void set_c(QString c) const;

                QString get_x() const;
                void set_x(QString x) const;

                QString get_u() const;
                void set_u(QString u) const;

                QString get_v() const;
                void set_v(QString v) const;

                QString get_s() const;
                void set_s(QString s) const;

                QString get_h() const;
                void set_h(QString h) const;

                QString get_t() const;
                void set_t(QString h) const;

                bool get_output_Q() const;
                void set_output_Q(bool output_Q) const;

                bool get_output_R() const;
                void set_output_R(bool output_R) const;

                bool get_output_N() const;
                void set_output_N(bool output_N) const;

                bool get_output_B() const;
                void set_output_B(bool output_B) const;

                bool get_output_I() const;
                void set_output_I(bool output_I) const;

                bool get_output_E() const;
                void set_output_E(bool output_E) const;

                bool get_output_V() const;
                void set_output_V(bool output_V) const;

            signals:
                void input_changed();
        };

    }
}

#endif //INPUTCONTROLLER_H
