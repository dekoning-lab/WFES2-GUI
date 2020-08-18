#ifndef TESTSOLVERVIENNACL_H
#define TESTSOLVERVIENNACL_H

#define VIENNACL_HAVE_EIGEN 1

#include <QtTest/QtTest>
#include <QDebug>

#include "model/viennacl/solverViennaCL.h"
#include "model/viennacl/sparseMatrixViennacl.h"
#include "testsuite.h"
#include "wfesLib.h"

#include <utils/types.h>

#include <math.h>

namespace wfes {
    namespace vienna {

        class TestSolverViennaCL : public TestSuite {
            Q_OBJECT

            public:
                TestSolverViennaCL();


            private slots:
                // @brief Called before fitst test function executed.
                void initTestCase();
                // @brief Called after last test function executed.
                void cleanUpTestCase();
                // @brief Called before each test function executed.
                void init();
                // @brief Called after each test function executed.
                void cleanup();

            private slots:
                void solve_solveSimple();

            private:

        };

    }
}

#endif // TESTSOLVERVIENNACL_H
