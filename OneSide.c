//String Length
#define SIZE 31

//Libraries
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct myElement {
	char *word;
	int arity;
	struct myElement *next;
} myElement;

/**
 * Create new node (allocate memory)
 */
myElement *createNewNode(char *slowo)
{
    myElement *newElement = malloc(sizeof(myElement));
	if (NULL == newElement)
    {
        printf("Pamieć nie mogla zostac zarezerowana poprawnie.\n");
		return NULL;
	}

	newElement->word = malloc(SIZE);
	if(NULL == newElement->word)
    {
		printf("Pamiec nie mogla zostac zarezerwowana pomyslnie dla ->word\n");
		free(newElement);
		return NULL;
	}

    //Kopiowanie znakow z jednego chara do drugiego
	strncpy(newElement->word,slowo,30);
	newElement->arity = 1;
	newElement->next = NULL;

	return newElement;
}

/**
 * Add node to list
 */
myElement *addNodeToList(myElement *head, char *slowo)
{
  myElement *newElement;
  myElement *previous = NULL;
  myElement *current;

  if (NULL == head)
  {
    myElement *newElement = createNewNode(slowo);
    if(newElement == NULL) return head;
    head = newElement;
  } else {
    current = head;
    while (current != NULL)
    {
      if (0 == strcmp(slowo,current->word))
      {
        current->arity += 1;
        return head;
      }

      if(strcmp(current->word,slowo) > 0)
      {
        newElement = createNewNode(slowo);
        if(NULL == newElement)
        {
          return head;
        }

        newElement->next = current;

        if (NULL == previous)
        {
          head = newElement;
        } else {
          previous->next = newElement;
          return head;
        }
      }

    previous = current;
    current = current->next;

    }
    previous->next = createNewNode(slowo);
  }
  return head;
}

/**
 * Deletes old node from list (or arity)
 */
myElement *deleteOldNode(myElement *head, char *slowo)
{
  myElement *current;
  myElement *previous = NULL;//element wskazujacy na element ktory chcemy usunac

  if (NULL == head)
  {
      printf("Lista jest pusta.\n");
      return head;
  } else {
      current = head;
      while(current != NULL)
      {
        if(0 == strcmp(slowo, current->word))
        {
            if (current->arity>1)
            {
                current->arity--;
                return head;
            } else {
                if (NULL == previous)
                {
                    head=current->next;
                } else {
                    previous->next = current->next;
                }

                free(current->word);
                free(current);
                return head;
            }
        }

        previous = current;
        current = current->next;

      }
  }
  printf("Nie ma takiego slowa.\n");
  return head;
}

/**
 * Show the list
 */
void viewNodesList(myElement *head)
{
	myElement *current;
	if(NULL == head)
  {
		printf("Lista jest pusta.\n");
	} else {
		current = head;
		while (current != NULL)
    {
  		printf("Slowo: %s || Wystepuje razy: %i\n",current->word,current->arity);
  		current = current->next;
    }
  }
}

/**
 * Main program
 */
int main()
{
	char myWord[SIZE];
  int myChoice;
	myElement *headElement = NULL;

	do
  {
    printf("=============================\n");
  	printf("1 - Dopisanie wyrazu\n");
  	printf("2 - Usuniecie wyrazu\n");
  	printf("3 - Wyswietlenie zawartosci listy\n");
    printf("0 - Wyjscie z programu...\n");
    printf("=============================\n\n");
  	scanf("%i",&myChoice);

  	switch(myChoice)
    {
  		case 0 :
    			printf("Wyjście z programu...");
    			break;
  		case 1 :
    			printf("Dodaj kolejne słowo: ");
    			scanf("%s",myWord);
    			headElement = addNodeToList(headElement, myWord);
    			break;
  		case 2 :
    			printf("Które słowo chcesz usunąć");
    			scanf("%s",myWord);
    			headElement = deleteOldNode(headElement, myWord);
    			break;
  		case 3 :
    			viewNodesList(headElement);
    			break;
  		default :
    			printf("Nie ma takiej pozycji w menu.\n");
  	}
	} while(myChoice != 0);
	return 0;
}
