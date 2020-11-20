#ifndef CONFIGTIMEDISTSGV_H
#define CONFIGTIMEDISTSGV_H

#include <QStandardPaths>
#include <QTextStream>
#include <QString>
#include <QDir>

#include <string>

#include "utils/types.h"

namespace wfes {
    namespace config {

        /**
         * @brief The ConfigTimeDistSGV class contains the configuration parameters specific of Time Dist SGV, as well as some functions for
         * saving and loading the configuration.
         */
        class ConfigTimeDistSGV {
            public:

                /**
                 * @brief Default constructor for class configTimeDistSGV.
                 */
                ConfigTimeDistSGV() = default;

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
                 * @brief No recurrent mutation (r).
                 */
                static bool no_rem;

                /**
                 * @brief Recurrent mutation.
                 */
                static bool rem;

                /**
                 * @brief Maximum number of generations (m).
                 */
                static int max_t;

                /**
                 * @brief Integration cutoff (c).
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
                 * @brief Save configuration into a file.
                 */
                static void saveConfigTimeDistSGV();

                /**
                 * @brief Load configuration from a file.
                 */
                static void loadConfigTimeDistSGV();

                /**
                 * @brief Process a line from the configuration file.
                 * @param line Current line being processed in the configuration file.
                 */
                static void processLine(QString line);
        };
    }
}

#endif // CONFIGTIMEDISTSGV_H
