#ifndef TESTSPARSEMATRIXPARDISO_H
#define TESTSPARSEMATRIXPARDISO_H

#include <QtTest/QtTest>
#include <QDebug>

#include "model/viennacl/sparseMatrixViennacl.h"
#include "testsuite.h"
#include "wfesLib.h"

#include <utils/types.h>

namespace wfes {
    namespace vienna {

        class TestSparseMatrixViennaCL : public TestSuite {
            Q_OBJECT

            public:
                TestSparseMatrixViennaCL();


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
                void createViennaCL_createEmpty();
                void createViennaCL_createWithSize();
                void createViennaCL_createFromEigenDense();
                void createMatrix_createDiagMatrix();
                void destructMatrix_destructor();
            private:

        };

    }
}

#endif // TESTSPARSEMATRIXPARDISO_H
