#ifndef CONFIGTIMEDISTSGV_H
#define CONFIGTIMEDISTSGV_H

#include <string>
#include "utils/types.h"

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

#include <QString>

namespace wfes {
    namespace config {
        class ConfigTimeDistSGV {
            public:

                /**
                 * @brief Backward mutation rates for each component (u).
                 */
                static dvec u;

                /**
                 * @brief Forward mutation rates for each component (u).
                 */
                static dvec v;

                /**
                 * @brief Selection coefficients for each component (s).
                 */
                static dvec s;

                /**
                 * @brief Dominance coefficients for each component (h).
                 */
                static dvec h;

                /**
                 * @brief Size of the population in the Wright Fisher Model (N).
                 */
                static int population_size;

                /**
                 * @brief Tail truncation weight (a).
                 */
                static double a;

                /**
                 * @brief No recurrent mutation (m).
                 */
                static bool no_rem;

                /**
                 * @brief Recurrent mutation.
                 */
                static bool rem;

                /**
                 * @brief Maximum number of generations.
                 */
                static int max_t;

                /**
                 * @brief Starting number of copies integration cutoff (c).
                 */
                static double integration_cutoff;

                /**
                 * @brief Number of components.
                 */
                static int num_comp;

                /**
                 * Transition probability (l).
                 */
                static double l;

                /**
                 * @brief Do not perform parameter checks.
                 */
                static bool force;

                /**
                 * @brief Default constructor for class configTimeDistSGV.
                 */
                ConfigTimeDistSGV();

                static void saveConfigTimeDistSGV();

                static void loadConfigTimeDistSGV();

                static void processLine(QString line);
        };
    }
}

#endif // CONFIGTIMEDISTSGV_H
