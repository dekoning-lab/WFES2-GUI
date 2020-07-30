#ifndef TESTSPARSEMATRIXPARDISO_H
#define TESTSPARSEMATRIXPARDISO_H

#include <QtTest/QtTest>
#include <QDebug>

#include "model/pardiso/sparseMatrixPardiso.h"
#include "testsuite.h"
#include "wfesLib.h"

namespace wfes {
    namespace pardiso {

        class TestSparseMatrixPardiso : public TestSuite {
            Q_OBJECT

            public:
                TestSparseMatrixPardiso();


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
                void createMatrix_createDiagMatrix();
                void testmatrix();
            private:
                SparseMatrixPardiso* sparseMatrix;
                WfesLib lib;

        };

    }
}

#endif // TESTSPARSEMATRIXPARDISO_H
