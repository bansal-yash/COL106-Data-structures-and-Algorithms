#include "Chaining.h"
#include "LinearProbing.h"
#include "QuadraticProbing.h"
#include "CubicProbing.h"
#include "Comp.h"
#include <cassert>

void testDatabase(BaseClass *db) {
    db->createAccount("HDRJ2671637_2748164828", 1000);
    db->createAccount("KAUN6873643_1837490284", 1500);
    db->createAccount("HDRJ2671637_2748164882", 2000);

    assert(db->getBalance("HDRJ2671637_2748164828") == 1000);
    assert(db->getBalance("KAUN6873643_1837490284") == 1500);
    assert(db->getBalance("HDRJ2671637_2748164882") == 2000);

    db->addTransaction("HDRJ2671637_2748164828", -200);
    db->addTransaction("KAUN6873643_1837490284", 300);
    db->addTransaction("HDRJ2671637_2748164882", -400);

    assert(db->getBalance("HDRJ2671637_2748164828") == 800);
    assert(db->getBalance("KAUN6873643_1837490284") == 1800);
    assert(db->getBalance("HDRJ2671637_2748164882") == 1600);

    std::vector<int> topBalances = db->getTopK(2);
    assert(topBalances.size() == 2);
    assert(topBalances[0] == 1800);
    assert(topBalances[1] == 1600);

    assert(db->databaseSize() == 3);

    assert(db->doesExist("HDRJ2671637_2748164828"));
    assert(!db->doesExist("MDUF4816839_0197826749"));
}


int main() {
    Chaining chainingDB;
    LinearProbing linearProbingDB;
    QuadraticProbing quadraticProbingDB;
    CubicProbing cubicProbingDB;
    Comp compDB;

    std::cout << "Testing Chaining:" << std::endl;
    testDatabase(&chainingDB);

    std::cout << "\nTesting Linear Probing:" << std::endl;
    testDatabase(&linearProbingDB);

    std::cout << "\nTesting Quadratic Probing:" << std::endl;
    testDatabase(&quadraticProbingDB);

    std::cout << "\nTesting Cubic Probing:" << std::endl;
    testDatabase(&cubicProbingDB);

    std::cout << "\nTesting Comp:" << std::endl;
    testDatabase(&compDB);
    return 0;
}
