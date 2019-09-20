#include <string.h>
#include "administration.h"
#include "unity.h"

void setUp(void)
{
    // This is run before EACH test
    // Shared variables
    MAX_SIZE = 5;
    size = 0;
}

void tearDown(void)
{
    // This is run after EACH test
}

void test_addAnimal() 
{
    ANIMAL animalArray[MAX_SIZE];
    ANIMAL animal = { "Testy", Dog, 12 };

    int result = addAnimal(&animal, animalArray);
    TEST_ASSERT_EQUAL(0, result);
}

void test_addToFullArray()
{
    ANIMAL animalArray[MAX_SIZE];
    size = 0; // reset the size

    ANIMAL animal1 = { "Rax", Dog, 12 };

    addAnimal(&animal1, animalArray);
    addAnimal(&animal1, animalArray);
    addAnimal(&animal1, animalArray);
    addAnimal(&animal1, animalArray);
    addAnimal(&animal1, animalArray);

    int toBeAdded = addAnimal(&animal1, animalArray);
    TEST_ASSERT_EQUAL(-1, toBeAdded);
}

void test_removeAnimal()
{
    ANIMAL animalArray[MAX_SIZE];
    size = 0; // reset the size

    ANIMAL animal1 = { "Rax", Dog, 12 };
    ANIMAL animal2 = { "Kitty", Cat, 12 };
    ANIMAL animal3 = { "Guinea", GuineaPig, 12 };
    ANIMAL animal4 = { "Puppy", Dog, 12 };

    addAnimal(&animal1, animalArray);
    addAnimal(&animal2, animalArray);
    addAnimal(&animal3, animalArray);
    addAnimal(&animal4, animalArray);

    int result = removeAnimal("Guinea", animalArray);

    TEST_ASSERT_EQUAL(0, result);
}

void test_removeUnexistingAnimal()
{
    ANIMAL animalArray[MAX_SIZE];
    size = 0; // reset the size

    ANIMAL animal1 = { "Rax", Dog, 12 };
    ANIMAL animal2 = { "Kitty", Cat, 12 };
    ANIMAL animal3 = { "Guinea", GuineaPig, 12 };
    ANIMAL animal4 = { "Puppy", Dog, 12 };

    addAnimal(&animal1, animalArray);
    addAnimal(&animal2, animalArray);
    addAnimal(&animal3, animalArray);
    addAnimal(&animal4, animalArray);

    int result = removeAnimal("Testy", animalArray);

    TEST_ASSERT_EQUAL(-1, result);
}

void test_countAnimalsAfterRemove()
{
    ANIMAL animalArray[MAX_SIZE];
    size = 0; // reset the size

    ANIMAL animal1 = { "Testy", Dog, 12 };
    ANIMAL animal2 = { "Dig", Cat, 12 };
    ANIMAL animal3 = { "Kit", GuineaPig, 12 };
    ANIMAL animal4 = { "Testy", Dog, 12 };

    addAnimal(&animal1, animalArray);
    addAnimal(&animal2, animalArray);
    addAnimal(&animal3, animalArray);
    addAnimal(&animal4, animalArray);

    removeAnimal("Testy", animalArray);

    int animalCounter = countAnimals(animalArray);

    TEST_ASSERT_EQUAL(2, animalCounter);
}

int main (void)
{
    UnityBegin("administration.c");
    RUN_TEST(test_addAnimal, 1);
    RUN_TEST(test_addToFullArray, 2);
    RUN_TEST(test_removeAnimal, 3);
    RUN_TEST(test_removeUnexistingAnimal, 4);
    RUN_TEST(test_countAnimalsAfterRemove, 5);
    return UnityEnd();
}
