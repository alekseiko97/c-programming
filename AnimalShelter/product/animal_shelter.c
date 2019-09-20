/*
 * Menu animal_shelter.c
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animal.h"
#include "administration.h"

int main (void)
{
     printf ("PRC assignment 'Animal Shelter' (version april 2019)\n");
     MAX_SIZE = 5;
     ANIMAL animalArray[MAX_SIZE];
     createDummyAnimals(animalArray);

    int choice = -1;
    while (choice != 0)
    {
        printf ("\nMENU\n====\n");
        printf ("1: Show Animals \n");
        printf ("2: Add Animal \n");
        printf ("3: Remove Animal \n");
        printf ("4: Find Animal by name \n");
        printf ("5: Get number of animals \n");
        printf ("6: Check space for one more animal \n");
        printf ("0: quit \n");

        scanf ("%d", &choice);

        switch (choice)
        {
            case 1: //Show Animals
                printf ("show Animals\n\n");
                showAnimals(animalArray);
                break;
            case 2: //Add Animal
                printf ("add Animal\n");

                if (size >= MAX_SIZE) {
                    printf("Can't add a new animal. The shelter is full");
                    break;
                }

                // Animal to be added
                ANIMAL a;

                // Enter name
                printf ("Enter animal name: ");
                char name[15]; 
                scanf ("%s", name);
                
                // to <-- from
                strcpy(a.Name, name);

                // Enter species
                printf ("\nEnter animal species: \n");
                int index = -1;

                printf("\n0: Cat\n");
                printf("1: Dog\n");
                printf("2: Guinea Pig\n");
                printf("3: Parrot\n");
                scanf ("%d", &index);

                switch (index) {
                    case 0: a.Species = Cat;
                        break;
                    case 1: a.Species = Dog;
                        break;
                    case 2: a.Species = GuineaPig;
                        break;
                    case 3: a.Species = Parrot;
                        break;
                    default:
                    printf("ERROR. Invalid choice: %d\n", index);
                        break;
                }
                    
                // Enter age
                printf ("\nEnter animal age: ");
                scanf ("%d", &a.Age);

                int result = addAnimal(&a, animalArray);

                // if the function returns 0 (successfully added an animal)
                if (result == 0) 
                {
                    printf ("\nSuccessfully added an animal with the name: %s", a.Name);
                } 
                else 
                {
                    printf ("Error");
                }
                break;
            case 3: //Remove Animal
                 printf ("remove Animal\n");

                 printf("Enter animal name to be removed: ");
                 scanf("%s", name);

                 int removed = removeAnimal(name, animalArray);

                 if (removed == 0) {
                     printf("Successfully deleted animal with the name %s", name);
                 } else {
                     printf("Error. Animal with this name wasn't found");
                 }
                 break;
            case 4://find by name
                 printf ("find by name\n");
                 scanf("%s", name);

                 int found = findAnimalByName(name, animalArray);

                 if (found > -1) 
                 {
                     printf("Animal with a name %s was found", name);
                 } else 
                 {
                     printf("Animal with such a name wasn't found in the shelter");
                 }
                 break;
            case 5:
                printf ("Amount of animals: %d \n", countAnimals(animalArray));
                break;
            case 6:
                printf ("You can still add %d animal(s) to the shelter\n", countSpacesLeft(animalArray));
                break;
            case 0:
                break;
            default:
                printf ("ERROR: invalid choice: %d\n", choice);
                break;
		}
	}
    return 0;
}
