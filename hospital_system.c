/*
Criado por:
Wescley Júnior Gonçalves Navarro
Giovanni Estevam dos Santos
*/

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>

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
} DATA;

typedef struct
{
    char street[50];
    char city[50];
    char state[50];
    char zip[50];
} ADDRESS;

typedef struct
{
    char dcIdentification[50];
    char name[50];
    char specialization[50];
} DOCTOR;

typedef struct
{
    char paIdentification[50];
    char name[50];
    char id[50];
    ADDRESS address;
    char phone[50];
    char gender[50];
} PATIENT;

typedef struct
{
    int num;
    char dcIdentification[50];
    char paIdentification[50];
    HOURLY duration;
    HOURLY hourly;
    DATA date;
} SCHEDULED;

// Protótipos
void clear();
void menu(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled);
void opcoesConsulta();
void loading();
void incluirConsulta();

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

    menu(doctor, patient, scheduled);

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
            opcoesConsulta();
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
            printf("Saindo");
            loading();
            break;
        default:
            printf("Opção inválida\n");
            system("pause");
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

// Opções de consulta
void opcoesConsulta()
{
    int option;

    do
    {
        clear();

        printf("1 - Incluir consulta\n");
        printf("2 - Alterar consulta\n");
        printf("3 - Cancelar consulta\n");
        printf("4 - Pesquisar consulta\n");
        printf("5 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            // Incluir consulta
            incluirConsulta();
            break;
        case 2:
            // Alterar consulta
            break;
        case 3:
            // Cancelar consulta
            break;
        case 4:
            // Pesquisar consulta
            break;
        case 5:
            printf("Voltando");
            loading();
            break;
        default:
            printf("Opção inválida\n");
            system("pause");
            break;
        }

    } while (option != 5);
}

// Efeito carregamento
void loading()
{
    for (int i = 0; i < 3; i++)
    {
        printf(".");
        Sleep(500);
    }
    printf("\n");
}

// Incluir consulta
void incluirConsulta()
{
    clear();

    FILE *file, *fileDoctor, *filePatient;
    int qtdConsultas, option, indicador, lastNum = 0;
    SCHEDULED scheduled;
    PATIENT patient;
    DOCTOR doctor;

    file = fopen("consultas.txt", "a+"); // "a+" permite leitura e escrita
    fileDoctor = fopen("medicos.txt", "r");
    filePatient = fopen("pacientes.txt", "r");

    if (file == NULL || fileDoctor == NULL || filePatient == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        system("pause");
        return;
    }

    printf("Quantas consultas deseja incluir? ");
    scanf("%d", &qtdConsultas);

    // Buscar o último número de consulta
    rewind(file);
    while (fscanf(file, " %d %s %s %d:%d %d/%d/%d", &lastNum, scheduled.dcIdentification, scheduled.paIdentification,
                  &scheduled.hourly.hour, &scheduled.hourly.minute, &scheduled.date.day,
                  &scheduled.date.month, &scheduled.date.year) == 8)
    {
        // Continua lendo até o final, lastNum sempre será atualizado com o último valor lido
    }

    if (lastNum + qtdConsultas > 100)
    {
        printf("Número máximo de consultas atingido\n");
        printf("Retornando ao menu");
        fclose(file);
        fclose(fileDoctor);
        fclose(filePatient);
        loading();
        return;
    }

    printf("Deseja ver a lista de médicos? (1 - Sim, 2 - Não): ");
    scanf("%d", &option);

    rewind(fileDoctor);
    if (option == 1)
    {
        while (fscanf(fileDoctor, " %s %s %s", doctor.dcIdentification, doctor.name, doctor.specialization) == 3)
        {
            printf("%s %s %s\n", doctor.dcIdentification, doctor.name, doctor.specialization);
        }
    }

    printf("Deseja ver a lista de pacientes? (1 - Sim, 2 - Não): ");
    scanf("%d", &option);

    rewind(filePatient);
    if (option == 1)
    {
        while (fscanf(filePatient, " %s %s %s %s %s %s %s %s %s", patient.paIdentification, patient.name, patient.id,
                      patient.address.street, patient.address.city, patient.address.state, patient.address.zip,
                      patient.phone, patient.gender) == 9)
        {
            printf("%s %s %s\n", patient.paIdentification, patient.name, patient.id);
        }
    }

    for (int i = 0; i < qtdConsultas; i++)
    {
        scheduled.num = lastNum + 1; // Garante um novo número de consulta único

        do
        {
            printf("Identificação do médico: ");
            scanf("%s", scheduled.dcIdentification);

            // Verifica se o médico existe
            indicador = 0;

            rewind(fileDoctor);
            while (fscanf(fileDoctor, " %s %s %s", doctor.dcIdentification, doctor.name, doctor.specialization) == 3)
            {
                if (strcmp(doctor.dcIdentification, scheduled.dcIdentification) == 0)
                {
                    indicador = 1;
                    break;
                }
            }

            if (indicador == 0)
            {
                printf("Médico não encontrado\n");
                printf("Tente novamente\n");
            }

        } while (indicador == 0);

        do
        {
            printf("Identificação do paciente: ");
            scanf("%s", scheduled.paIdentification);

            // Verifica se o paciente existe
            indicador = 0;

            rewind(filePatient);
            while (fscanf(filePatient, " %s %s %s %s %s %s %s %s %s", patient.paIdentification, patient.name, patient.id,
                          patient.address.street, patient.address.city, patient.address.state, patient.address.zip,
                          patient.phone, patient.gender) == 9)
            {
                if (strcmp(scheduled.paIdentification, patient.paIdentification) == 0)
                {
                    indicador = 1;
                    break;
                }
            }

            if (indicador == 0)
            {
                printf("Paciente não encontrado\n");
                printf("Tente novamente\n");
            }

        } while (indicador == 0);

        do
        {
            indicador = 1;
            printf("Hora da consulta (HH:MM): ");
            scanf("%d:%d", &scheduled.hourly.hour, &scheduled.hourly.minute);

            if (scheduled.hourly.hour < 0 || scheduled.hourly.hour > 23 || scheduled.hourly.minute < 0 || scheduled.hourly.minute > 59)
            {
                printf("Hora inválida\n");
                printf("Tente novamente\n");
                indicador = 0;
            }
        } while (indicador == 0);

        do
        {
            indicador = 1;
            printf("Data da consulta (DD/MM/AAAA): ");
            scanf("%d/%d/%d", &scheduled.date.day, &scheduled.date.month, &scheduled.date.year);

            if (scheduled.date.day < 1 || scheduled.date.day > 31 || scheduled.date.month < 1 || scheduled.date.month > 12 || scheduled.date.year < 2021)
            {
                printf("Data inválida\n");
                printf("Tente novamente\n");
                indicador = 0;
            }

            do
            {
                indicador = 1;
                printf("Duração (HH:MM): ");
                scanf("%d:%d", &scheduled.duration.hour, &scheduled.duration.minute);

                if (scheduled.hourly.hour < 0 || scheduled.hourly.hour > 23 || scheduled.hourly.minute < 0 || scheduled.hourly.minute > 59)
                {
                    printf("Hora inválida\n");
                    printf("Tente novamente\n");
                    indicador = 0;
                }
            } while (indicador == 0);

        } while (indicador == 0);

        // Adicionar ao arquivo
        fprintf(file, "%d %s %s %02d:%02d %02d/%02d/%04d %02d:%02d\n", scheduled.num, scheduled.dcIdentification, 
                scheduled.paIdentification, scheduled.hourly.hour, scheduled.hourly.minute, scheduled.date.day, 
                scheduled.date.month, scheduled.date.year, scheduled.duration.hour, scheduled.duration.minute);

        lastNum++; // Incrementa para a próxima consulta
    }

    fclose(file);
    fclose(fileDoctor);
    fclose(filePatient);

    if (qtdConsultas > 0)
    {
        printf("Consultas incluídas com sucesso!\n");
    }
    else
    {
        printf("Nenhuma consulta incluída.\n");
    }

    printf("Retornando ao menu...");
    loading();

    system("pause");
}
