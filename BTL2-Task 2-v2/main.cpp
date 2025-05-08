/*
ReLU
g++ -std=c++17 -I "./test" -I "./include" -I "./include/tensor" -I "./include/sformat" -I "./include/ann" -I "./demo" $(find ./src/ann/ -type f -iregex ".*\.cpp") ./src/tensor/*.cpp main.cpp test/unit_test/layer/unit_test_relu.cpp -o main -DTEST_LAYER
Sigmoid
g++ -std=c++17 -I "./test" -I "./include" -I "./include/tensor" -I "./include/sformat" -I "./include/ann" -I "./demo" $(find ./src/ann/ -type f -iregex ".*\.cpp") ./src/tensor/*.cpp main.cpp test/unit_test/layer/unit_test_sigmoid.cpp -o main -DTEST_LAYER
Softmax
g++ -std=c++17 -I "./test" -I "./include" -I "./include/tensor" -I "./include/sformat" -I "./include/ann" -I "./demo" $(find ./src/ann/ -type f -iregex ".*\.cpp") ./src/tensor/*.cpp main.cpp test/unit_test/layer/unit_test_softmax.cpp -o main -DTEST_LAYER
Tanh
g++ -std=c++17 -I "./test" -I "./include" -I "./include/tensor" -I "./include/sformat" -I "./include/ann" -I "./demo" $(find ./src/ann/ -type f -iregex ".*\.cpp") ./src/tensor/*.cpp main.cpp test/unit_test/layer/unit_test_tanh.cpp -o main -DTEST_LAYER
CrossEntropy
g++ -std=c++17 -I "./test" -I "./include" -I "./include/tensor" -I "./include/sformat" -I "./include/ann" -I "./demo" $(find ./src/ann/ -type f -iregex ".*\.cpp") ./src/tensor/*.cpp main.cpp test/unit_test/loss/unit_test_CrossEntropy.cpp -o main -DTEST_LOSS


./main test_unit

*/

#include "main.hpp"
#ifdef TEST_HASH
// #include "random_test/hash/random_test.hpp"
#include "unit_test/hash/unit_test.hpp"
const string TEST_CASE = "HASH";
#elif defined(TEST_HEAP)
// #include "random_test/heap/random_test.hpp"
#include "unit_test/heap/unit_test.hpp"
const string TEST_CASE = "HEAP";
#elif defined(TEST_LAYER)
// #include "random_test/heap/random_test.hpp"
#include "unit_test/layer/unit_test.hpp"
const string TEST_CASE = "LAYER";
#elif defined(TEST_LOSS)
// #include "random_test/heap/random_test.hpp"
#include "unit_test/loss/unit_test.hpp"
const string TEST_CASE = "LOSS";
#endif
void printTestCase();

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printTestCase();
    return 1;
  }

  std::string arg1 = argv[1];
  if (arg1 == "test_unit") {
    std::cout << GREEN << BOLD << "Running unit_test/" << TEST_CASE << RESET
              << "\n";
    handleTestUnit(argc, argv);
  } else if (arg1 == "test_random") {
    std::cout << GREEN << BOLD << "Running test_random/" << TEST_CASE << RESET
              << "\n";
    handleTestRandom(argc, argv);
  } else {
    printTestCase();
  }
}

#ifdef TEST_HASH
void handleTestUnit(int argc, char *argv[]) {
  UNIT_TEST_Hash unitTest;

  if (argc == 2 || (argc == 3 && std::string(argv[2]) == "all")) {
    unitTest.runAllTests();
  } else if (argc == 3) {
    unitTest.runTest(argv[2]);
  } else {
    printTestCase();
  }
}

void handleTestRandom(int argc, char *argv[]) {
  // HEAPMIT CODE
}
#elif TEST_HEAP
void handleTestUnit(int argc, char *argv[]) {
  UNIT_TEST_Heap unitTest;

  if (argc == 2 || (argc == 3 && std::string(argv[2]) == "all")) {
    std::cout << "Running all unit tests array: ----------\n";
    unitTest.runAllTests();
  } else if (argc == 3) {
    std::cout << "Running unit test array: " << argv[2] << " ----------\n";
    unitTest.runTest(argv[2]);
  } else {
    printTestCase();
  }
}

void handleTestRandom(int argc, char *argv[]) {
  // HEAPMIT CODE
}
#elif TEST_LAYER
void handleTestUnit(int argc, char *argv[]) {
  UNIT_TEST_Layer unitTest;

  if (argc == 2 || (argc == 3 && std::string(argv[2]) == "all")) {
    std::cout << "Running all unit tests array: ----------\n";
    unitTest.runAllTests();
  } else if (argc == 3) {
    std::cout << "Running unit test array: " << argv[2] << " ----------\n";
    unitTest.runTest(argv[2]);
  } else {
    printTestCase();
  }
}

void handleTestRandom(int argc, char *argv[]) {
  // HEAPMIT CODE
}
#elif TEST_LOSS
void handleTestUnit(int argc, char *argv[]) {
  UNIT_TEST_Loss unitTest;

  if (argc == 2 || (argc == 3 && std::string(argv[2]) == "all")) {
    std::cout << "Running all unit tests array: ----------\n";
    unitTest.runAllTests();
  } else if (argc == 3) {
    std::cout << "Running unit test array: " << argv[2] << " ----------\n";
    unitTest.runTest(argv[2]);
  } else {
    printTestCase();
  }
}

void handleTestRandom(int argc, char *argv[]) {
  // HEAPMIT CODE
}
#endif

void printTestCase() {
  std::cout << GREEN << BOLD << "terminal unit test" << RESET << std::endl;
  std::cout << RED << "./main test_unit" << RESET << std::endl;
  std::cout << RED << "./main test_unit nameFunctionUnitTest" << RESET
            << std::endl
            << std::endl;

  // std::cout << GREEN << BOLD << "terminal auto test" << RESET << std::endl;
  // std::cout << RED << "./main test_random number_1 number_2" << RESET
  //           << std::endl;
  // std::cout << RED << "./main test_random number" << RESET << std::endl;
}