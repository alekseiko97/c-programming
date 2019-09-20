#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "administration.h"

void createDummyAnimals(ANIMAL animalArray[])
{
    // 1
     strcpy(animalArray[0].Name, "Rax");
     animalArray[0].Species = Dog;
     animalArray[0].Age = 17;

    // 2
     strcpy(animalArray[1].Name, "Kitty");
     animalArray[1].Species = Cat;
     animalArray[1].Age = 11;

    // 3
     strcpy(animalArray[2].Name, "Guinea");
     animalArray[2].Species = GuineaPig;
     animalArray[2].Age = 9;

    // 4
     strcpy(animalArray[3].Name, "Kitty");
     animalArray[3].Species = Cat;
     animalArray[3].Age = 17;

     size = 4;
}

int addAnimal(ANIMAL *animalPtr, ANIMAL animalArray[]) 
{
    if (size < MAX_SIZE)
    {
       animalArray[size] = *animalPtr; 
       ++size; // increase the value of 'size' in animal_shelter.c
       return 0; // successfully added
    } 

    return -1; // array is full
}

void showAnimals(ANIMAL animalArray[]) 
{
    char species[15];

    int i;
    for (i = 0; i < size; i++)
    {
        int number = animalArray[i].Species;

        switch (number) {
        case 0:
            strcpy(species, "Cat");
            break;
        case 1:
            strcpy(species, "Dog");
            break;
        case 2:
            strcpy(species, "Guinea Pig");
            break;
        case 3:
            strcpy(species, "Parrot");
            break;
        default:
            strcpy(species, "Unknown");
            break;
        }

        printf("Name: %s, Species: %s, Age: %d\n", animalArray[i].Name, species, animalArray[i].Age);
    }
}

int removeAnimal(char name[], ANIMAL animalArray[]) 
{
    int i;
    int counter = 0;

    for (i = 0; i < size; i++) 
    {
        // animal with the specified name was found
        if (strcmp(animalArray[i].Name, name) == 0) // compare strings
        {
            int c;
            for (c = i; c <= size; c++)
            {
                animalArray[c] = animalArray[c + 1]; // shift all animals by one
            }
            // 1. reduce the size of the array by one
            --size; 
            // 2. if next iteration occurs, start one position earlier because of a shift
            --i; 
            // 3. count how many times an animal with a given name was found
            ++counter; 
        }
    }

    if (counter > 0){
        return 0; // at least one animal has been removed
    }

    return -1; // not found
}

int findAnimalByName(char name[], ANIMAL animalArray[]) // returns animal's index
{
    int i;
    // first find an animal to delete
    for (i = 0; i < size; i++) 
    {
        // animal with the specified name was found
        if (strcmp(animalArray[i].Name, name) == 0) // compare strings
        {
            return i; // found
        }
    }

    return -1;
}

int countAnimals(ANIMAL animalArray[])
{
    return size;
}

int countSpacesLeft(ANIMAL animalArray[])
{
    return MAX_SIZE - size;
}
