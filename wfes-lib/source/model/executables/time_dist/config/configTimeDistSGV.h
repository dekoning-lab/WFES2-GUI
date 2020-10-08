#ifndef CONFIGTIMEDISTSGV_H
#define CONFIGTIMEDISTSGV_H

#include "utils/types.h"

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
        };
    }
}

#endif // CONFIGTIMEDISTSGV_H
