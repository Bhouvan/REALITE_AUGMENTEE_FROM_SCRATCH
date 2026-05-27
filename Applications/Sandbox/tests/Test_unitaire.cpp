#include <Unitest/Unitest.h>
#include <Unitest/TestMacro.h>

#include "NKMath/NKMath.h"


using namespace NkMath;

TEST_CASE(NKMathisFloat, isFiniteValidFunctions) {
    ASSERT_FALSE(isFiniteValid(sqrt(-1)));
    ASSERT_FALSE(isFiniteValid(INFINITY));
    ASSERT_FALSE(isFiniteValid(-std::numeric_limits<float>::infinity()));
    ASSERT_FALSE(isFiniteValid(-std::numeric_limits<double>::infinity()));
    ASSERT_FALSE(isFiniteValid(std::numeric_limits<double>::infinity()));

    ASSERT_TRUE(isFiniteValid(0.0f));
    ASSERT_TRUE(isFiniteValid(1.0f));
    ASSERT_TRUE(isFiniteValid(1.0));
    ASSERT_TRUE(isFiniteValid(1.0));
}

TEST_CASE(NKMathFloat, NearlyZeroFunctions) {
   ASSERT_FALSE(nearlyZero(1.2f));
   ASSERT_FALSE(nearlyZero(2.1));

   ASSERT_TRUE(nearlyZero(1e-10));
   ASSERT_TRUE(nearlyZero(1e-8f));
}

TEST_CASE(NKMathFloat, BitAndIntegerUtilities) {
    ASSERT_TRUE (approxEq(0.141592653,0.141592654));
    ASSERT_TRUE (approxEq(0.141592,0.141593,1e-5));
    ASSERT_FALSE (approxEq(0.141592,0.141595,1e-6));
}

TEST_CASE(NKMathFloat, KahanSumvsStdAccumulate) {

    // -------------------------------------------------------------------------
    // CAS 1 : Grand nombre + multitude de petits nombres (L'effet "goutte d'eau")
    // -------------------------------------------------------------------------
   {
    int size = 10000000;
    double* data = new double[size];
    RemplirTab(data, size, 0.1);

    double naive = sommeNaive(data, size);
    double kahan = kahanSum(data, size);

    ASSERT_TRUE(std::abs(kahan - 1000000.0)<=std::abs(naive - 1000000.0));

    delete[] data;
    } 

   
    {
        double data[] = { 1e15, 1.0, -1e15 };

        double naive = sommeNaive(data, 3);
        double kahan = kahanSum(data, 3);

        ASSERT_TRUE(std::abs(kahan - 1.0)<=std::abs(naive - 1.0));
    } 

    // -------------------------------------------------------------------------
    // CAS 3 : Série harmonique 1/k  (k = 1..10000)
    // -------------------------------------------------------------------------
  
    {
        int size = 10000;
        double* data = new double[size];
        for (int i = 0; i < size; i++) data[i] = 1.0 / (i + 1);

        double naive = sommeNaive(data, size);
        double kahan = kahanSum(data, size);

        // Référence mathématique connue
        // sum(1/k, k=1..10000) = nombre harmonique H_10000
        // calculé avec un outil haute précision (Wolfram Alpha, Python mpmath)
        double ref = 9.78760603604438;  // depuis mpmath avec 50 chiffres significatifs

        
        // juste vérifier que Kahan est MEILLEUR que naive
        ASSERT_TRUE(std::abs(kahan - ref) < std::abs(naive - ref));

        // vérifier la propriété connue de Kahan
        ASSERT_NEAR(kahan, ref, 1e-10);   // Kahan très précis
       

        delete[] data;
    }

    
    // CAS 4 : Tableau vide — les deux renvoient 0
  
    {
        double kahan = kahanSum(nullptr, 0);
        double naive = sommeNaive(nullptr, 0);

        ASSERT_NEAR(kahan, 0.0, kEps);
        ASSERT_NEAR(naive, 0.0, kEps);
    }


    // CAS 5 : Un seul élément — résultat trivial identique
    
    {
        double data[] = { 42.0 };

        ASSERT_NEAR(kahanSum(data, 1),   42.0, kEps);
        ASSERT_NEAR(sommeNaive(data, 1), 42.0, kEps);
    }

    
    // CAS 6 : Entiers 1..100 — somme exacte = 5050
   
    {
        int size = 100;
        double* data = new double[size];
        for (int i = 0; i < size; i++) data[i] = i + 1.0;

        ASSERT_NEAR(kahanSum(data, size),   5050.0, kEps);
        ASSERT_NEAR(sommeNaive(data, size), 5050.0, kEps);

        delete[] data;
    }

    
    // CAS 7 : Alternance +1 / -1  (N=1000, pair → somme = 0)
    
    {
        int size = 1000;
        double* data = new double[size];
        for (int i = 0; i < size; i++) data[i] = (i % 2 == 0) ? 1.0 : -1.0;

        ASSERT_NEAR(kahanSum(data, size),   0.0, kEps);
        ASSERT_NEAR(sommeNaive(data, size), 0.0, kEps);

        delete[] data;
    }

    
    // CAS 8 : Valeurs proches de l'epsilon machine (sous-ulp)
   
    {
        int size = 1000;
        double eps = std::numeric_limits<double>::epsilon();
        double* data = new double[size];
        for (int i = 0; i < size; i++) data[i] = eps / 2.0;

        double exact = size * (eps / 2.0);
        double kahan = kahanSum(data, size);
        double naive = sommeNaive(data, size);

        ASSERT_TRUE(std::abs(kahan - exact) <= std::abs(naive - exact));

        delete[] data;
    }

    
    // CAS 9 : Valeurs négatives répétées — somme = -100
    
    {
        int size = 100;
        double* data = new double[size];
        for (int i = 0; i < size; i++) data[i] = -1.0;

        ASSERT_NEAR(kahanSum(data, size),   -100.0, kEps);
        ASSERT_NEAR(sommeNaive(data, size), -100.0, kEps);
        

        delete[] data;
    }

    
    // CAS 10 : Limite absolue — perte totale au-delà de 1e16 (ULP > 1)
    //          Kahan ne peut rien récupérer ; on vérifie qu'il ne fait pas pire
   
    {
        double data[] = { 1e16, 1.0, -1e16 };

        double kahan = kahanSum(data, 3);
        double naive = sommeNaive(data, 3);

        // Les deux perdent le terme 1 ; Kahan doit rester aussi précis que naive
        ASSERT_TRUE(std::abs(kahan - 1.0) <= std::abs(naive - 1.0) + kEps);
    }
}