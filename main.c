#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>

struct Data
{
   int size;
   void * A;
   int el_size;
  };
struct Complex
{
   int Re;
   int Im;
}  ;
const int N=50;
void sort(struct Data* array, int (* srav)(int, int), void(* swap)(int*, int*)) //универсальная сортировка
{
 int minPosition;
 int i;
      for (i = 0; i < array->size; i++)
    {
        minPosition = i;
        int j;
        for (j = i + 1; j < array->size; j++)
            if (  srav( (char*)array->A+minPosition*(array->el_size), ((char*)array->A+j*(array->el_size)) ) > 0  )
                minPosition = j;
        swap((char*)array->A+minPosition*(array->el_size), (char*)array->A+i*(array->el_size));
    }
}
int srav_int(int* a, int* b) //функция сравнения для целых
{
    return(*a - *b);
}
void swap_int(int* a, int* b) //меняет местами целые
{
    int sw = *a;
    *a = *b;
    *b = sw;
}
int srav_float(float* a, float* b) //Функция сравнения вещ
{
    return(*a - *b);
}
void swap_float(float* a, float* b) //меняет местами вещ
{
    float sw = *a;
    *a = *b;
    *b = sw;
}
int srav_Com(struct Complex* a, struct Complex* b) //Функция сравнения для компл
{
    return(a->Re - b->Re);
}
void swap_Com(struct Complex* a, struct Complex* b) //меняе местами компл
{
    int sw = a->Re;
    a->Re = b->Re;
    b->Re = sw;

    sw = a->Im;
    a->Im = b->Im;
    b->Im = sw;
}
void map( struct Data* array, void(*function)(int, struct Data*)) //универсальная на весь массив
{
    int i;
    for (i=0; i<array->size; i++)
        function(i, array);
}
 void fun_int (int i, struct Data* array ) //возводит в квадрат целые
{
    *((int*)array->A+i) *= *((int*)array->A+i);
}
void fun_float (int i, struct Data* array ) //возводит  в квадрат вещ
{
    *((float*)array->A+i) *= *((float*)array->A+i);
}
void fun_com (int i, struct Data* array ) //возводит в квадрат действитльную часть компл
{
     struct Complex* C =(struct Complex*)array->A+i;
     C->Re *= C->Re;
}
void readCom (struct Complex* T) //вводит комплексное
{
    scanf("%d", &(T->Re));
    scanf("%d", &(T->Im));
}
void writeCom (struct Complex* T) //выводит копл
{
    printf("{%d", T->Re);
    printf(" + i*%d} ", T->Im);
}
int whereInInt ( struct Data* array) //поиск в целых
{
    printf("\n Write the element for searching:\n");
    int x;
    scanf("%d", &x);
    int i = 0;
    while ((*((int*)array->A+i)!= x) && (i<array->size))
    {
      i++;
    }
    int* Index;
    Index = i+1;
    if (i<=array->size-1)
     printf("The number of this element is %d",Index);
        else printf("This element isn't found ");
        return Index;
}
void whereInFloat ( struct Data* array) //поиск в вещ
{
    printf("Write the element for searching:\n");
    float x;
    scanf("%f", &x);
    int i = 0;
    while ((*((float*)array->A+i)!= x) && (i<array->size))
    {
      i++;
    }
    if (i<=array->size-1)
        printf("The number of this element is %d",i+1);
        else printf("This element isn't found ");
}
void whereInComplex ( struct Data* array) //поиск в компл
{
    printf("\n Write the element for searching:\n");
    int x;
    int y;
    scanf("%d%d", &x,&y);
    int i = 0;
    while ((((((struct Complex*)array->A+i)->Re)!= x) || ((((struct Complex*)array->A+i)->Im)!= y)) && (i<array->size))
    {
      i++;
    }
    if (i<=array->size-1)
        printf("The number of this element is %d",i+1);
        else printf("This element isn't found ");
}
int communication() //выбор действия
{
     printf("\n");
     printf("Choose an operation you'd like to do: \n");
     printf(" to sort click 1 \n");
     printf(" for map click 2 \n");
     printf(" for where click 3 \n");
     int t;
     scanf("%d",&t);
     return t;
}
void test_sort(struct Data* array)
{
    int* T = malloc(5*sizeof(int));
    T[0]=1;
    T[1]=2;
    T[2]=4;
    T[3]=7;
    T[4]=9;
    int i=0;
    while ( ((T[i]) == (*((int*)array->A+i)) ) && (i<5) )
    {
        i++;
    }
    if (i == 5)
        printf("Perfectly!");
        else printf("\n Something is wrong...");
}
void test_map(struct Data* array)
{
    int* T = malloc(5*sizeof(int));
    T[0]=49;
    T[1]=16;
    T[2]=4;
    T[3]=81;
    T[4]=1;
    int i=0;
    while ( ((T[i]) == (*((int*)array->A+i)) ) && (i<5) )
    {
        i++;
    }
    if (i == 5)
        printf("\n Perfectly!");
        else printf("\n Something is wrong...");
}
void test_where (struct Data* array)
{

    int M=4;
    if (whereInInt(array) == M)
        printf("\n Perfectly!");
        else printf("\n Something is wrong...");
}
            //Complex
void Create_Complex()
{
 struct Data* Z = malloc(sizeof(struct Data));
    printf("Enter the number of elements in the array \n" );
    scanf("%d", &(Z->size) );
    Z->el_size=sizeof(struct Complex);
	Z->A = malloc(Z->size*sizeof(struct Complex));
	int i;
	for (i = 0; i < Z->size; i++)
	{
		readCom((struct Complex*)Z->A+i);
		writeCom((struct Complex*)Z->A+i);
    }
     int type = communication();
     switch(type)
     {
        case 1:
        {
          sort(Z, srav_Com, swap_Com);
          printf("\n Sorted array:\n");
          for (i = 0; i < Z->size; i++)
          writeCom((struct Complex*)Z->A+i);
          break;
          free(Z);
        }
        case 2:
        {
          map( Z, fun_com);
          for (i = 0; i < Z->size; i++)
           writeCom((struct Complex*)Z->A+i);
          break;
          free(Z);
        }
        case 3:
        {
         whereInComplex (Z);
         break;
         free(Z);
        }
     }
}
            //Float
void Create_Float()
{
 struct Data* Z = malloc(sizeof(struct Data));
    printf("Enter the number of elements in the array \n" );
    scanf("%d", &(Z->size) );
    Z->el_size=sizeof(float);
	Z->A = malloc(Z->size*sizeof(float));
	int i;
	for (i = 0; i < Z->size; i++)
	{
		scanf("%f", ((float*)Z->A+i));
        printf("%f\t", *((float*)Z->A+i));
    }
     int type = communication();
     switch(type)
     {
        case 1:
        {
          sort(Z, srav_float, swap_float);
          printf("\n Sorted array:\n");
          for (i = 0; i < Z->size; i++)
            {
                printf("%f\t", *((float*)Z->A + i));
            }
          break;
          free(Z);
        }
        case 2:
        {
          map( Z, fun_float);
          for (i = 0; i < Z->size; i++)
            {
                printf("%f\t", *((float*)Z->A + i));
            }
          break;
          free(Z);
        }
        case 3:
        {
         whereInFloat (Z);
         break;
         free(Z);
        }
     }
}
                // Int
void Create_Int()
{
 struct Data* Z = malloc(sizeof(struct Data));
    printf("Enter the number of elements in the array \n" );
    scanf("%d", &(Z->size) );
    Z->el_size=sizeof(int);
	Z->A = malloc(Z->size*sizeof(int));
	int i;
	for (i = 0; i < Z->size; i++)
	{
		scanf("%d", ((int*)Z->A+i));
        printf("%d\t", *((int*)Z->A+i));
    }
     int type = communication();
     switch(type)
     {
        case 1:
        {
          sort(Z, srav_int, swap_int);
          printf("\n Sorted array:\n");
          for (i = 0; i < Z->size; i++)
            {
                printf("%d\t", *((int*)Z->A + i));
            }
          break;
          free(Z);
        }
        case 2:
        {
          map( Z, fun_int);
          for (i = 0; i < Z->size; i++)
            {
                printf("%d\t", *((int*)Z->A + i));
            }
          break;
          free(Z);
        }
        case 3:
        {
         whereInInt (Z);
         break;
         free(Z);
        }
     }
}
void Create_Int_Test() //тестирующая
{
 struct Data* Z = malloc(sizeof(struct Data));
    printf("Enter the number of elements in the array \n" );
    scanf("%d", &(Z->size) );
    Z->el_size=sizeof(int);
    int Index;
    Index = 0;
	Z->A = malloc(Z->size*sizeof(int));
	int i;
	for (i = 0; i < Z->size; i++)
	{
		scanf("%d", ((int*)Z->A+i));
        printf("%d\t", *((int*)Z->A+i));
    }
     int type = communication();
     switch(type)
     {
        case 1:
        {
          sort(Z, srav_int, swap_int);
          printf("\n Sorted array:\n");
          for (i = 0; i < Z->size; i++)
            {
                printf("%d\t", *((int*)Z->A + i));
            }
         printf("\n");
          test_sort(Z) ;
          break;
          free(Z);
        }
        case 2:
        {
          map( Z, fun_int);
          for (i = 0; i < Z->size; i++)
            {
                printf("%d\t", *((int*)Z->A + i));
            }
          test_map(Z);
          break;
          free(Z);
        }
         case 3:
        {
         test_where(Z);
         break;
         free(Z);
        }
       }
}
 void main()
 {
     printf("Select the item type that you would like to work: \n");
     printf(" for working with integer click 1 \n");
     printf(" for working with real click 2 \n");
     printf(" for working with complex click 3 \n");
     printf(" if you want to check on integer array click 4 \n");
     int type;
     scanf("%d",&type);
     switch(type)
     {
        case 1:
        {
          Create_Int();
          break;
        }
        case 2:
        {
          Create_Float();
          break;
        }
        case 3:
        {
          Create_Complex();
          break;
        }
        case 4:
        {
          Create_Int_Test();
          break;
        }
     }
 }
