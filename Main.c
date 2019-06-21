#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


struct lista		// <---   Tworzenie struktury na której bazuje lista 
{
	int s;
	struct lista *next;
} lista;
struct lista *head=NULL, *x=NULL, *oldhead=NULL, *temp = NULL; 


struct lista *add(struct lista *head, int liczba)		// <---   Dodawanie elementu do listy
{
  struct lista *element=NULL;
  
  while(head -> next != NULL) head = head -> next;
  element = (struct lista *)malloc(sizeof(struct lista));
  element -> s = liczba;
  element -> next = NULL;
  head -> next = element;
  head = element;
  return head;
}


struct lista *del(struct lista *head, int x)			// <---   Usuwanie elementu z listy
{ 
  struct lista *temp = head; 
  struct lista *prev = head;
 
while (temp != NULL) 
{ 
    	if (temp -> s == x) 
    	if (temp == head) 
   		 { 
    		  head = head -> next; 
     		  free(temp); 
      		  temp = head ; 
      		  prev = head; 
    	 } 
		else 
    	{ 
     	prev -> next = temp -> next; 
    	free(temp); 
     	temp = prev -> next;
    	} 
	  	else 
    	{ 
     	prev = temp; 
     	temp = temp -> next; 
    	} 
}
  return head;
}


int main()			// <---   Poczatek dzialania funkcji main()
{
int i, a;
struct lista *oldhead, *temp;
int n;

	FILE * plik;			// <--- Otworzenie pliku
	plik = fopen("SE.txt", "w");

  printf("Prosze podac liczbe wieksza od 1: ");			// <--- Prosba o podanie gornego kresu przedzialu
  scanf("%d", &n);
  

  while(n < 2)				// <--- Zabezpieczenie przed podawaniem liczby mniejszej od 2
  {
    printf("Podano nieprawidlowy przedzial! Sprobuj jeszcze raz: ");
    scanf("%d", &n);
  }

  head = (struct lista *)malloc(sizeof(struct lista));		// <--- Tworzenie heada listy
  head -> s = 2;
  head -> next = NULL;

  oldhead = head; 			// <--- Zapewniam staly kontakt z lista za pomoca oldheada
 
  for(i = 3; i < n+1; i++)		// <--- Wypelniam liste zgodnie kolejnymi liczbami z przedzialu <2,n>
  { 
    add(head,i); 
  }
  head = oldhead;


  for(a = 2; a != n; a++)		// <--- Szukam liczb pierwszych jednoczesnie zerujac wszystkie te które liczbami pierwszymi nie sa.
  {
    while(head != NULL)
    {
      if( (head -> s % a == 0) && (head -> s != a ))
      {
      head -> s = 0;
      }
      head = head -> next;
    }
    head = oldhead;
  }

  head = oldhead;

  while(head != NULL)		// <--- Usuwam wyzerowane elementy z listy
  {
    del(head, 0);
    head = head -> next;
  }
  head = oldhead;

  while(head != NULL)		// <--- Zapisuje liczby pierwsze od nowej linijki w pliku SE.txt
  {
    temp = head;
	fprintf(plik, "%d\n", head -> s);
    head = head -> next;
    free(temp);		// <--- Uwalniam pamiec
  }

	fclose(plik);		// <--- Zamykam plik

	printf("\n");
	printf("Zapisano liczby pierwsze z przedzialu od 2 do %d w pliku SE.txt", n);

  fflush(stdin); 			// <--- Czyszcze bufor wejscia
	getch();
}
