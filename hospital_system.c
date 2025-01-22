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
void lerarquivos(FILE *fileDoctor, FILE *filePatient, FILE *fileScheduled, DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled);
void clear();
void menu(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled);
void opcoesConsulta(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled);
void loading();
void incluirConsulta(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled);
void menuPesquisarConsulta(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled);
void pesquisarConsultaMedico(DOCTOR *doctor, SCHEDULED *scheduled);
void pesquisarConsultaPaciente(PATIENT *patient, SCHEDULED *scheduled);
void pesquisarConsultaData(SCHEDULED *scheduled);
void pesquisarConsultaHorario(SCHEDULED *scheduled);
void cancelarConsulta(SCHEDULED *scheduled);
void alterarConsulta(SCHEDULED *scheduled, DOCTOR *doctor, PATIENT *patient);
void save(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled);
int validarMedico(DOCTOR *doctor, const char *id);
int validarPaciente(PATIENT *patient, const char *id);
int validarData(DATA data);
int validarHorario(HOURLY hourly);
int validarDuracao(HOURLY duration);
void imprimirConsulta(SCHEDULED *scheduled, int i);

// Função principal
int main(void)
{
    setlocale(LC_ALL, NULL);

    DOCTOR *doctor = calloc(20, sizeof(DOCTOR));
    PATIENT *patient = calloc(50, sizeof(PATIENT));
    SCHEDULED *scheduled = calloc(100, sizeof(SCHEDULED));

    FILE *fileDoctor, *filePatient, *fileScheduled;

    fileDoctor = fopen("medicos.txt", "r");
    filePatient = fopen("pacientes.txt", "r");
    fileScheduled = fopen("consultas.txt", "r");

    if (fileDoctor == NULL || filePatient == NULL || fileScheduled == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        system("pause");
        return 1;
    }

    if (doctor == NULL || patient == NULL || scheduled == NULL)
    {
        printf("Erro ao alocar memória\n");
        system("pause");
        return 1;
    }

    lerarquivos(fileDoctor, filePatient, fileScheduled, doctor, patient, scheduled);

    fclose(fileDoctor);
    fclose(filePatient);
    fclose(fileScheduled);

    menu(doctor, patient, scheduled);

    // Salvar arquivos
    save(doctor, patient, scheduled);

    return 0;
}

// Funções
// Ler arquivos
void lerarquivos(FILE *fileDoctor, FILE *filePatient, FILE *fileScheduled, DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled)
{
    int i = 0;

    while (fscanf(fileDoctor, " %s %s %s", doctor[i].dcIdentification, doctor[i].name, doctor[i].specialization) == 3)
    {
        i++;
    }

    i = 0;

    while (fscanf(filePatient, " %s %s %s %s %s %s %s %s %s", patient[i].paIdentification, patient[i].name, patient[i].id,
                  patient[i].address.street, patient[i].address.city, patient[i].address.state, patient[i].address.zip,
                  patient[i].phone, patient[i].gender) == 9)
    {
        i++;
    }

    i = 0;

    while (fscanf(fileScheduled, "%d %s %s %d:%d %d/%d/%d %d:%d", &scheduled[i].num, scheduled[i].dcIdentification, scheduled[i].paIdentification,
                  &scheduled[i].hourly.hour, &scheduled[i].hourly.minute, &scheduled[i].date.day,
                  &scheduled[i].date.month, &scheduled[i].date.year, &scheduled[i].duration.hour, &scheduled[i].duration.minute) == 10)
    {
        i++;
    }
}

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
            opcoesConsulta(doctor, patient, scheduled);
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

// Opções de consulta
void opcoesConsulta(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled)
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
            incluirConsulta(doctor, patient, scheduled);
            break;
        case 2:
            // Alterar consulta
            alterarConsulta(scheduled, doctor, patient);
            break;
        case 3:
            // Cancelar consulta
            cancelarConsulta(scheduled);
            break;
        case 4:
            // Pesquisar consulta
            menuPesquisarConsulta(doctor, patient, scheduled);
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

// Incluir consulta
void incluirConsulta(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled)
{
    clear();

    SCHEDULED tempScheduled;

    int qtdConsultas, lastNum = 0, indicador, option, i = 0;

    printf("Quantas consultas deseja incluir? ");
    scanf("%d", &qtdConsultas);

    // Buscar o último número da struct consulta
    while (scheduled[i].num != 0)
    {
        lastNum = scheduled[i].num;
        i++;
    }

    if (lastNum + qtdConsultas > 100)
    {
        printf("Número máximo de consultas atingido\n");
        printf("Retornando ao menu");
        loading();
        return;
    }

    printf("Deseja ver a lista de médicos? (1 - Sim, 2 - Não): ");
    scanf("%d", &option);

    if (option == 1)
    {
        i = 0;
        while (doctor[i].dcIdentification[0] != '\0')
        {
            printf("%s %s %s\n", doctor[i].dcIdentification, doctor[i].name, doctor[i].specialization);
            i++;
        }
    }

    printf("Deseja ver a lista de pacientes? (1 - Sim, 2 - Não): ");
    scanf("%d", &option);

    if (option == 1)
    {
        i = 0;
        while (patient[i].paIdentification[0] != '\0')
        {
            printf("%s %s %s\n", patient[i].paIdentification, patient[i].name, patient[i].id);
            i++;
        }
    }

    for (int i = 0; i < qtdConsultas; i++)
    {
        tempScheduled.num = lastNum + 1; // Garante um novo número de consulta único

        do
        {
            printf("Identificação do médico: ");
            scanf(" %s", tempScheduled.dcIdentification);

            indicador = verificarMedico(doctor, tempScheduled.dcIdentification);

        } while (indicador == 0);

        do
        {
            printf("Identificação do paciente: ");
            scanf(" %s", tempScheduled.paIdentification);

            indicador = verificarPaciente(patient, tempScheduled.paIdentification);

        } while (indicador == 0);

        do
        {
            printf("Hora da consulta (HH:MM): ");
            scanf("%d:%d", &tempScheduled.hourly.hour, &tempScheduled.hourly.minute);

            indicador = validarHorario(tempScheduled.hourly);

        } while (indicador == 0);

        do
        {
            printf("Data da consulta (DD/MM/AAAA): ");
            scanf("%d/%d/%d", &tempScheduled.date.day, &tempScheduled.date.month, &tempScheduled.date.year);

            indicador = validarData(tempScheduled.date);

        } while (indicador == 0);

        do
        {
            printf("Duração (HH:MM): ");
            scanf("%d:%d", &tempScheduled.duration.hour, &tempScheduled.duration.minute);

            indicador = validarDuracao(tempScheduled.duration);

        } while (indicador == 0);

        scheduled[lastNum] = tempScheduled;

        lastNum++;
    }

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
    getchar();

    system("pause");
}

// Pesquisar consulta
void menuPesquisarConsulta(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled)
{
    int option;

    do
    {
        clear();

        printf("1 - Por médico\n");
        printf("2 - Por paciente\n");
        printf("3 - Por data\n");
        printf("4 - Por horário\n");
        printf("5 - Voltar\n");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            pesquisarConsultaMedico(doctor, scheduled);
            break;
        case 2:
            pesquisarConsultaPaciente(patient, scheduled);
            break;
        case 3:
            pesquisarConsultaData(scheduled);
            break;
        case 4:
            pesquisarConsultaHorario(scheduled);
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

// Pesquisar consulta por médico
void pesquisarConsultaMedico(DOCTOR *doctor, SCHEDULED *scheduled)
{
    clear();

    DOCTOR tempDoctor;

    int i = 0, indicador = 0;

    printf("Identificação do médico: ");
    scanf("%s", tempDoctor.dcIdentification);

    while (scheduled[i].num != 0)
    {
        if (strcmp(scheduled[i].dcIdentification, tempDoctor.dcIdentification) == 0)
        {
            imprimirConsulta(scheduled, i);
            indicador = 1;
        }
        i++;
    }

    if (indicador == 0)
    {
        printf("Nenhuma consulta encontrada\n");
    }

    system("pause");
}

// Pesquisar consulta por paciente
void pesquisarConsultaPaciente(PATIENT *patient, SCHEDULED *scheduled)
{
    clear();

    int i = 0, indicador = 0;

    PATIENT tempPatient;

    printf("Identificação do paciente: ");
    scanf("%s", tempPatient.paIdentification);

    while (scheduled[i].num != 0)
    {
        if (strcmp(scheduled[i].paIdentification, tempPatient.paIdentification) == 0)
        {
            imprimirConsulta(scheduled, i);
            indicador = 1;
        }
        i++;
    }

    if (indicador == 0)
    {
        printf("Nenhuma consulta encontrada\n");
    }

    system("pause");
}

// Pesquisar consulta por data
void pesquisarConsultaData(SCHEDULED *scheduled)
{
    clear();

    int i = 0, indicador = 0;

    DATA tempData;

    printf("Data da consulta (DD/MM/AAAA): ");
    scanf("%d/%d/%d", &tempData.day, &tempData.month, &tempData.year);

    while (scheduled[i].num != 0)
    {
        if (scheduled[i].date.day == tempData.day && scheduled[i].date.month == tempData.month && scheduled[i].date.year == tempData.year)
        {
            imprimirConsulta(scheduled, i);
            indicador = 1;
        }
        i++;
    }

    if (indicador == 0)
    {
        printf("Nenhuma consulta encontrada\n");
    }

    system("pause");
}

// Pesquisar consulta por horário
void pesquisarConsultaHorario(SCHEDULED *scheduled)
{
    clear();

    HOURLY tempHourly;
    int i = 0, indicador = 0;

    printf("Horário da consulta (HH:MM): ");
    scanf("%d:%d", &tempHourly.hour, &tempHourly.minute);

    while (scheduled[i].num != 0)
    {
        if (scheduled[i].hourly.hour == tempHourly.hour && scheduled[i].hourly.minute == tempHourly.minute)
        {
            imprimirConsulta(scheduled, i);
            indicador = 1;
        }
        i++;
    }

    if (indicador == 0)
    {
        printf("Nenhuma consulta encontrada\n");
    }

    system("pause");
}

// Cancelar consulta
void cancelarConsulta(SCHEDULED *scheduled)
{
    clear();

    int num, indicador = 0, i = 0, found = 0, totalConsultas = 0;

    // Determinar o total de consultas cadastradas
    while (scheduled[totalConsultas].num != 0)
    {
        totalConsultas++;
    }

    if (totalConsultas == 0)
    {
        printf("Nenhuma consulta cadastrada.\n");
        return;
    }

    printf("Número da consulta: ");
    scanf("%d", &num);

    // Buscar a consulta pelo número
    for (i = 0; i < totalConsultas; i++)
    {
        if (scheduled[i].num == num)
        {
            imprimirConsulta(scheduled, i);
            printf("Deseja cancelar a consulta? (1 - Sim, 2 - Não): ");
            scanf("%d", &indicador);

            if (indicador == 1)
            {
                found = 1;

                // Deslocar as consultas seguintes para preencher o espaço removido
                for (int j = i; j < totalConsultas - 1; j++)
                {
                    scheduled[j] = scheduled[j + 1]; // Copia a próxima consulta para a posição atual
                    scheduled[j].num = j + 1;        // Ajusta a numeração para ficar sequencial
                }

                // Marcar a última posição como vazia
                scheduled[totalConsultas - 1].num = 0;
                scheduled[totalConsultas - 1].dcIdentification[0] = '\0';
                scheduled[totalConsultas - 1].paIdentification[0] = '\0';

                for (int k = i; k < totalConsultas - 1; k++)
                {
                    scheduled[k].num = k + 1; // Ajusta a numeração para ficar sequencial
                }

                printf("Consulta cancelada com sucesso!\n");
                system("pause");
                break;
            }
        }
    }

    if (!found)
    {
        printf("Consulta não encontrada.\n");
        printf("Retornando ao menu");
        loading();
    }
}

// Alterar consulta
void alterarConsulta(SCHEDULED *scheduled, DOCTOR *doctor, PATIENT *patient)
{
    clear();

    int num, choice, validador = 0, j = 0;

    printf("Deseja ver a lista de consultas? (1 - Sim, 2 - Não): ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Consultas cadastradas:\n");
        for (int i = 0; scheduled[i].num != 0; i++)
        {
            if (scheduled[i].num != 0)
            {
                imprimirConsulta(scheduled, i);
            }
        }
    }

    printf("Número da consulta que deseja alterar(Digite 0 para cancelar): ");
    scanf("%d", &num);

    if (num == 0)
    {
        printf("Retornando ao menu");
        loading();
        return;
    }

    for (int i = 0; scheduled[i].num != 0; i++)
    {
        if (scheduled[i].num == num)
        {
            imprimirConsulta(scheduled, i);

            printf("Deseja alterar a consulta? (1 - Sim, 2 - Não): ");
            scanf("%d", &choice);

            if (choice == 2)
            {
                printf("Retornando ao menu");
                loading();
                return;
            }

            printf("O que deseja alterar?\n");
            printf("1 - Identificação do médico\n");
            printf("2 - Identificação do paciente\n");
            printf("3 - Horário da consulta\n");
            printf("4 - Data da consulta\n");
            printf("5 - Duração da consulta\n");
            printf("6 - Todos os dados\n");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                do
                {
                    printf("Identificação do médico: ");
                    scanf(" %s", scheduled[i].dcIdentification);

                    validador = encontrarMedico(doctor, scheduled[i].dcIdentification);

                } while (validador == 0);

                break;
            case 2:
                do
                {
                    printf("Identificação do paciente: ");
                    scanf(" %s", scheduled[i].paIdentification);

                    validador = encontrarPaciente(patient, scheduled[i].paIdentification);

                } while (validador == 0);

                break;
            case 3:
                do
                {
                    printf("Horário da consulta (HH:MM): ");
                    scanf("%d:%d", &scheduled[i].hourly.hour, &scheduled[i].hourly.minute);

                    validador = validarHorario(scheduled[i].hourly);

                } while (validador == 0);

                break;
            case 4:
                do
                {
                    printf("Data da consulta (DD/MM/AAAA): ");
                    scanf("%d/%d/%d", &scheduled[i].date.day, &scheduled[i].date.month, &scheduled[i].date.year);

                    validador = validarData(scheduled[i].date);

                } while (validador == 0);

                break;
            case 5:
                do
                {
                    printf("Duração da consulta (HH:MM): ");
                    scanf("%d:%d", &scheduled[i].duration.hour, &scheduled[i].duration.minute);

                    validador = validarDuracao(scheduled[i].duration);

                } while (validador == 0);

                break;
            case 6:
                do
                {
                    printf("Identificação do médico: ");
                    scanf(" %s", scheduled[i].dcIdentification);

                    validador = encontrarMedico(doctor, scheduled[i].dcIdentification);

                } while (validador == 0);

                do
                {
                    printf("Identificação do paciente: ");
                    scanf(" %s", scheduled[i].paIdentification);

                    validador = validarPaciente(patient, scheduled[i].paIdentification);

                } while (validador == 0);

                do
                {
                    printf("Horário da consulta (HH:MM): ");
                    scanf("%d:%d", &scheduled[i].hourly.hour, &scheduled[i].hourly.minute);

                    validador = validarHorario(scheduled[i].hourly);

                } while (validador == 0);

                do
                {
                    printf("Data da consulta (DD/MM/AAAA): ");
                    scanf("%d/%d/%d", &scheduled[i].date.day, &scheduled[i].date.month, &scheduled[i].date.year);

                    validador = validarData(scheduled[i].date);

                } while (validador == 0);

                do
                {
                    printf("Duração da consulta (HH:MM): ");
                    scanf("%d:%d", &scheduled[i].duration.hour, &scheduled[i].duration.minute);

                    validador = validarDuracao(scheduled[i].duration);

                } while (validador == 0);

                getchar();
                printf("Consulta alterada com sucesso!\n");
                system("pause");
                return;

            default:
                printf("Opção inválida\n");
                printf("Tente novamente\n");
                loading();
                break;
            }
        }
    }
}

// Pesquisar existência de Medico
int validarMedico(DOCTOR *doctor, const char *id)
{
    for (int i = 0; doctor[i].dcIdentification[0] != '\0'; i++)
    {
        if (strcmp(doctor[i].dcIdentification, id) == 0)
            return 1;
    }
    printf("Médico não encontrado\n");
    printf("Tente novamente\n");
    return 0;
}

// Pesquisar existência de Paciente
int validarPaciente(PATIENT *patient, const char *id)
{
    for (int i = 0; patient[i].paIdentification[0] != '\0'; i++)
    {
        if (strcmp(patient[i].paIdentification, id) == 0)
            return 1;
    }
    printf("Paciente não encontrado\n");
    printf("Tente novamente\n");
    return 0;
}

// Pesquisar data valida
int validarData(DATA data)
{
    if (data.day < 1 || data.day > 31 || data.month < 1 || data.month > 12 || data.year < 2025)
    {
        printf("Data inválida\n");
        printf("Tente novamente\n");
        return 0;
    }
    return 1;
}

// Pesquisar horário válido
int validarHorario(HOURLY hourly)
{
    if (hourly.hour < 0 || hourly.hour > 23 || hourly.minute < 0 || hourly.minute > 59)
    {
        printf("Hora inválida\n");
        printf("Tente novamente\n");
        return 0;
    }
    return 1;
}

// Pesquisar duração válida
int validarDuracao(HOURLY duration)
{
    if (duration.hour < 0 || duration.hour > 23 || duration.minute < 0 || duration.minute > 59)
    {
        printf("Duração inválida\n");
        printf("Tente novamente\n");
        return 0;
    }
    return 1;
}

// Imprimir consulta
void imprimirConsulta(SCHEDULED *scheduled, int i)
{
    printf("Consulta %d\n", scheduled[i].num);
    printf("Médico: %s\n", scheduled[i].dcIdentification);
    printf("Paciente: %s\n", scheduled[i].paIdentification);
    printf("Horário: %02d:%02d\n", scheduled[i].hourly.hour, scheduled[i].hourly.minute);
    printf("Data: %02d/%02d/%04d\n", scheduled[i].date.day, scheduled[i].date.month, scheduled[i].date.year);
    printf("Duração: %02d:%02d\n", scheduled[i].duration.hour, scheduled[i].duration.minute);
    printf("\n");
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

// Salvar arquivos
void save(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled)
{
    int i = 0;

    FILE *fileDoctor, *filePatient, *fileScheduled;

    fileDoctor = fopen("medicos.txt", "w");
    filePatient = fopen("pacientes.txt", "w");
    fileScheduled = fopen("consultas.txt", "w");

    if (fileDoctor == NULL || filePatient == NULL || fileScheduled == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        system("pause");
        return;
    }

    while (doctor[i].dcIdentification[0] != '\0')
    {
        fprintf(fileDoctor, "%s %s %s\n", doctor[i].dcIdentification, doctor[i].name, doctor[i].specialization);
        i++;
    }

    i = 0;

    while (patient[i].paIdentification[0] != '\0')
    {
        fprintf(filePatient, "%s %s %s %s %s %s %s %s %s\n", patient[i].paIdentification, patient[i].name, patient[i].id,
                patient[i].address.street, patient[i].address.city, patient[i].address.state, patient[i].address.zip,
                patient[i].phone, patient[i].gender);
        i++;
    }

    i = 0;

    while (scheduled[i].num != 0)
    {
        fprintf(fileScheduled, "%d %s %s %d:%d %d/%d/%d %d:%d\n", scheduled[i].num, scheduled[i].dcIdentification, scheduled[i].paIdentification,
                scheduled[i].hourly.hour, scheduled[i].hourly.minute, scheduled[i].date.day,
                scheduled[i].date.month, scheduled[i].date.year, scheduled[i].duration.hour, scheduled[i].duration.minute);
        i++;
    }

    free(doctor);
    free(patient);
    free(scheduled);

    fclose(fileDoctor);
    fclose(filePatient);
    fclose(fileScheduled);
}