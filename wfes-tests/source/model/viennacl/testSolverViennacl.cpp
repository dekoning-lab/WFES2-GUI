#include "testSolverViennacl.h"

using namespace wfes::vienna;

static TestSolverViennaCL instance;

TestSolverViennaCL::TestSolverViennaCL() : TestSuite("TestSolverViennaCL")
{

}

void TestSolverViennaCL::initTestCase()
{

}

void TestSolverViennaCL::cleanUpTestCase()
{

}

void TestSolverViennaCL::init()
{

}

void TestSolverViennaCL::cleanup()
{

}

void TestSolverViennaCL::solve_solveSimple()
{
    bool test = true;

    dmat eigen_mat = dmat(3, 3);

    eigen_mat(0,0) = 1;
    eigen_mat(0,1) = 2;
    eigen_mat(0,2) = -2;

    eigen_mat(1,0) = 2;
    eigen_mat(1,1) = 1;
    eigen_mat(1,2) = -5;

    eigen_mat(2,0) = 1;
    eigen_mat(2,1) = -4;
    eigen_mat(2,2) = 1;

    SparseMatrixViennaCL* mat = new SparseMatrixViennaCL(eigen_mat);

    dvec right = dvec(3);

    right(0) = -15;
    right(1) = -21;
    right(2) = 18;

    dvec res = dvec(3);

    SolverViennaCL solver = SolverViennaCL(*mat, "GMRes", "");

    res = solver.solve(right, false);

    for(int i = 0; i < res.size(); i++)
        qDebug() << res(i);

    if(std::abs(-1 - res(0)) > 0.1)
        test = false;
    if(std::abs(-4 - res(1)) > 0.1)
        test = false;
    if(std::abs(3 - res(2)) > 0.1)
        test = false;

    SparseMatrixViennaCL* mat2 = new SparseMatrixViennaCL(eigen_mat);

    SolverViennaCL solver2 = SolverViennaCL(*mat2, "GMRes", "");

    res = solver2.solve(right, true);

    for(int i = 0; i < res.size(); i++)
        qDebug() << res(i);

    if(std::abs(-18 - res(0)) > 0.1)
        test = false;
    if(std::abs(3 - res(1)) > 0.1)
        test = false;
    if(std::abs(-3 - res(2)) > 0.1)
        test = false;


    QVERIFY(test);
}
