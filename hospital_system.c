/*
Criado por:
Wescley Júnior Gonçalves Navarro
Giovanni Estevam dos Santos
*/

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Structs
typedef struct
{
    int hour;
    int minute;
} HOURLY;

typedef struct
{
    int day;
    int month;
    int year;
} DATE;

typedef struct
{
    char street[50];
    char city[50];
    char state[50];
    char zip[50];
} ANDRESS;

typedef struct
{
    char dcIndentification[50];
    char name[50];
    char specialization[50];
} DOCTOR;

typedef struct
{
    char paIndentification[50];
    char name[50];
    char id[50];
    ANDRESS address;
    char phone[50];
    char gender[50];
} PATIENT;

typedef struct
{
    int num;
    char dcIdentification[50];
    char paIdentification[50];
    HOURLY hourly;
    DATE date;
} SCHEDULED;

// Protótipos
void clear();
void menu(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled);

// Função principal
int main(void)
{
    setlocale(LC_ALL, NULL);

    PATIENT *patient = (PATIENT *)malloc(50 * sizeof(PATIENT));
    DOCTOR *doctor = (DOCTOR *)malloc(20 * sizeof(DOCTOR));
    SCHEDULED *scheduled = (SCHEDULED *)malloc(100 * sizeof(SCHEDULED));

    if (patient == NULL || doctor == NULL || scheduled == NULL)
    {
        printf("Falha na alocação de memória\n");
        return 1;
    }

    menu(&doctor, &patient, &scheduled);

    free(patient);
    free(doctor);
    free(scheduled);

    return 0;
}

// Funções
// Menu
void menu(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled)
{
    int option;

    do
    {
        clear();

        printf("1 - Consulta\n");
        printf("2 - Paciente\n");
        printf("3 - Médico\n");
        printf("4 - Relatório\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            // Consulta
            break;
        case 2:
            // Paciente
            break;
        case 3:
            // Médico
            break;
        case 4:
            // Relatório
            break;
        case 5:
            // Sair
            break;
        default:
            printf("Opção inválida\n");
            break;
        }
    } while (option != 5);
}

// Limpar tela
void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}