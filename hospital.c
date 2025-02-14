/*
Criado por:
Wescley Júnior Gonçalves Navarro
Giovanni Estevam dos Santos
*/

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

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
void pause();
int validarConsulta(SCHEDULED *scheduled, int num);
void opcoesMedico(DOCTOR *doctor, SCHEDULED *scheduled);
void incluirMedico(DOCTOR *doctor);
void alterarMedico(DOCTOR *doctor);
void excluirMedico(DOCTOR *doctor, SCHEDULED *scheduled);
void pesquisarMedico(DOCTOR *doctor);
void opcoesPaciente(PATIENT *patient, SCHEDULED *scheduled);
void incluirPaciente(PATIENT *patient);
void alterarPaciente(PATIENT *patient);
void excluirPaciente(PATIENT *patient, SCHEDULED *scheduled);
void pesquisarPaciente(PATIENT *patient);
void relatorios(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled);
void listaConsultasPaciente(PATIENT *patient, SCHEDULED *scheduled);
void listaConsultasMedico(DOCTOR *doctor, SCHEDULED *scheduled);
void listaPacientesPorEspecialidade(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled);

// Função principal
int main(void)
{
    setlocale(LC_ALL, NULL);

    DOCTOR *doctor = calloc(20, sizeof(DOCTOR));
    PATIENT *patient = calloc(50, sizeof(PATIENT));
    SCHEDULED *scheduled = calloc(100, sizeof(SCHEDULED));

    FILE *fileDoctor, *filePatient, *fileScheduled;

    fileDoctor = fopen("medicos.txt", "r+");
    filePatient = fopen("pacientes.txt", "r+");
    fileScheduled = fopen("consultas.txt", "r+");

    if (fileDoctor == NULL || filePatient == NULL || fileScheduled == NULL)
    {
        if (fileDoctor == NULL)
        {
            fileDoctor = fopen("medicos.txt", "w");
        }

        if (filePatient == NULL)
        {
            filePatient = fopen("pacientes.txt", "w");
        }

        if (fileScheduled == NULL)
        {
            fileScheduled = fopen("consultas.txt", "w");
        }

        if (fileDoctor == NULL || filePatient == NULL || fileScheduled == NULL)
        {
            printf("Erro ao abrir o arquivo\n");
            pause();
            return 1;
        }
    }

    if (doctor == NULL || patient == NULL || scheduled == NULL)
    {
        printf("Erro ao alocar memória\n");
        pause();
        return 1;
    }

    lerarquivos(fileDoctor, filePatient, fileScheduled, doctor, patient, scheduled);

    fclose(fileDoctor);
    fclose(filePatient);
    fclose(fileScheduled);

    menu(doctor, patient, scheduled);

    free(doctor);
    free(patient);
    free(scheduled);

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
        save(doctor, patient, scheduled);

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
            opcoesPaciente(patient, scheduled);
            break;
        case 3:
            // Médico
            opcoesMedico(doctor, scheduled);
            break;
        case 4:
            // Relatório
            relatorios(doctor, patient, scheduled);
            break;
        case 5:
            printf("Saindo\n");
            break;
        default:
            printf("Opção inválida\n");
            pause();
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
        save(doctor, patient, scheduled);

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
            printf("Voltando\n");
            break;
        default:
            printf("Opção inválida\n");
            pause();
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

    // Encontrar o maior número de consulta existente
    int maxNum = 0;
    for (int j = 0; scheduled[j].num != 0; j++)
    {
        if (scheduled[j].num > maxNum)
        {
            maxNum = scheduled[j].num;
        }
    }
    lastNum = maxNum;

    if (lastNum + qtdConsultas > 100)
    {
        printf("Número máximo de consultas atingido\n");
        pause();
        return;
    }

    // Verificar espaço disponível
    int espacoLivre = 0;
    while (espacoLivre < 100 && scheduled[espacoLivre].num != 0)
        espacoLivre++;
    if ((100 - espacoLivre) < qtdConsultas)
    {
        printf("Espaço insuficiente para %d consultas\n", qtdConsultas);
        pause();
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
        tempScheduled.num = lastNum + 1 + i; // Números sequenciais

        do
        {
            printf("\nConsulta %d:\n", tempScheduled.num);
            printf("Identificação do médico: ");
            scanf("%49s", tempScheduled.dcIdentification);
            getchar();
            indicador = validarMedico(doctor, tempScheduled.dcIdentification);
        } while (indicador == 0);

        do
        {
            printf("Identificação do paciente: ");
            scanf("%49s", tempScheduled.paIdentification);
            getchar();
            indicador = validarPaciente(patient, tempScheduled.paIdentification);
        } while (indicador == 0);

        do
        {
            printf("Hora da consulta (HH:MM): ");
            scanf("%d:%d", &tempScheduled.hourly.hour, &tempScheduled.hourly.minute);
            getchar();
            indicador = validarHorario(tempScheduled.hourly);
        } while (indicador == 0);

        do
        {
            printf("Data da consulta (DD/MM/AAAA): ");
            scanf("%d/%d/%d", &tempScheduled.date.day, &tempScheduled.date.month, &tempScheduled.date.year);
            getchar();
            indicador = validarData(tempScheduled.date);
        } while (indicador == 0);

        do
        {
            printf("Duração (HH:MM): ");
            scanf("%d:%d", &tempScheduled.duration.hour, &tempScheduled.duration.minute);
            getchar();
            indicador = validarDuracao(tempScheduled.duration);
        } while (indicador == 0);

        // Encontrar próxima posição livre
        int pos = 0;
        while (scheduled[pos].num != 0)
            pos++;
        scheduled[pos] = tempScheduled;
        printf("%d consulta(s) incluída(s) com sucesso!\n", qtdConsultas);
        pause();
    }
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
            printf("Voltando\n");
            break;
        default:
            printf("Opção inválida\n");
            pause();
            break;
        }

        save(doctor, patient, scheduled);

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
    getchar();

    indicador = validarMedico(doctor, tempDoctor.dcIdentification);

    if (indicador == 0)
    {
        pause();
        return;
    }

    indicador = 0;

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

    pause();
}

// Pesquisar consulta por paciente
void pesquisarConsultaPaciente(PATIENT *patient, SCHEDULED *scheduled)
{
    clear();

    int i = 0, indicador = 0;

    PATIENT tempPatient;

    printf("Identificação do paciente: ");
    scanf("%s", tempPatient.paIdentification);
    getchar();

    indicador = validarPaciente(patient, tempPatient.paIdentification);

    if (indicador == 0)
    {
        pause();
        return;
    }

    indicador = 0;

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

    pause();
}

// Pesquisar consulta por data
void pesquisarConsultaData(SCHEDULED *scheduled)
{
    clear();

    int i = 0, indicador = 0;

    DATA tempData;

    printf("Data da consulta (DD/MM/AAAA): ");
    scanf("%d/%d/%d", &tempData.day, &tempData.month, &tempData.year);
    getchar();

    indicador = validarData(tempData);

    if (indicador == 0)
    {
        pause();
        return;
    }

    indicador = 0;

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

    pause();
}

// Pesquisar consulta por horário
void pesquisarConsultaHorario(SCHEDULED *scheduled)
{
    clear();

    HOURLY tempHourly;
    int i = 0, indicador = 0;

    printf("Horário da consulta (HH:MM): ");
    scanf("%d:%d", &tempHourly.hour, &tempHourly.minute);
    getchar();

    indicador = validarHorario(tempHourly);

    if (indicador == 0)
    {
        pause();
        return;
    }

    indicador = 0;

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

    pause();
}

// Cancelar consulta
void cancelarConsulta(SCHEDULED *scheduled)
{
    clear();

    int num, indicador = 0, i = 0, totalConsultas = 0;
    int c; // Para limpeza do buffer

    // Determinar o total de consultas cadastradas
    while (totalConsultas < 100 && scheduled[totalConsultas].num != 0)
    {
        totalConsultas++;
    }

    if (totalConsultas == 0)
    {
        printf("Nenhuma consulta cadastrada.\n");
        pause();
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
                // Substituir pela última consulta válida
                scheduled[i] = scheduled[totalConsultas - 1];
                // Limpar última posição
                scheduled[totalConsultas - 1].num = 0;
                scheduled[totalConsultas - 1].dcIdentification[0] = '\0';
                scheduled[totalConsultas - 1].paIdentification[0] = '\0';

                printf("Consulta cancelada com sucesso!\n");
                pause();
                return;
            }
        }
    }

    printf("Consulta não encontrada.\n");
    pause();
}

// Alterar consulta
void alterarConsulta(SCHEDULED *scheduled, DOCTOR *doctor, PATIENT *patient)
{
    clear();

    int num, choice, validador = 0;

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
                    scanf("%s", scheduled[i].dcIdentification);
                    getchar();

                    validador = validarMedico(doctor, scheduled[i].dcIdentification);

                } while (validador == 0);

                break;
            case 2:
                do
                {
                    printf("Identificação do paciente: ");
                    scanf("%s", scheduled[i].paIdentification);
                    getchar();

                    validador = validarPaciente(patient, scheduled[i].paIdentification);

                } while (validador == 0);

                break;
            case 3:
                do
                {
                    printf("Horário da consulta (HH:MM): ");
                    scanf("%d:%d", &scheduled[i].hourly.hour, &scheduled[i].hourly.minute);
                    getchar();

                    validador = validarHorario(scheduled[i].hourly);

                } while (validador == 0);

                break;
            case 4:
                do
                {
                    printf("Data da consulta (DD/MM/AAAA): ");
                    scanf("%d/%d/%d", &scheduled[i].date.day, &scheduled[i].date.month, &scheduled[i].date.year);
                    getchar();

                    validador = validarData(scheduled[i].date);

                } while (validador == 0);

                break;
            case 5:
                do
                {
                    printf("Duração da consulta (HH:MM): ");
                    scanf("%d:%d", &scheduled[i].duration.hour, &scheduled[i].duration.minute);
                    getchar();

                    validador = validarDuracao(scheduled[i].duration);

                } while (validador == 0);

                break;
            case 6:
                do
                {
                    printf("Identificação do médico: ");
                    scanf("%s", scheduled[i].dcIdentification);
                    getchar();

                    validador = validarMedico(doctor, scheduled[i].dcIdentification);

                } while (validador == 0);

                do
                {
                    printf("Identificação do paciente: ");
                    scanf("%s", scheduled[i].paIdentification);
                    getchar();

                    validador = validarPaciente(patient, scheduled[i].paIdentification);

                } while (validador == 0);

                do
                {
                    printf("Horário da consulta (HH:MM): ");
                    scanf("%d:%d", &scheduled[i].hourly.hour, &scheduled[i].hourly.minute);
                    getchar();

                    validador = validarHorario(scheduled[i].hourly);

                } while (validador == 0);

                do
                {
                    printf("Data da consulta (DD/MM/AAAA): ");
                    scanf("%d/%d/%d", &scheduled[i].date.day, &scheduled[i].date.month, &scheduled[i].date.year);
                    getchar();

                    validador = validarData(scheduled[i].date);

                } while (validador == 0);

                do
                {
                    printf("Duração da consulta (HH:MM): ");
                    scanf("%d:%d", &scheduled[i].duration.hour, &scheduled[i].duration.minute);
                    getchar();

                    validador = validarDuracao(scheduled[i].duration);

                } while (validador == 0);

                printf("Consulta alterada com sucesso!\n");
                pause();
                return;

            default:
                printf("Opção inválida\n");
                printf("Tente novamente\n");
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

// Validar consulta
int validarConsulta(SCHEDULED *scheduled, int num)
{
    for (int i = 0; scheduled[i].num != 0; i++)
    {
        if (scheduled[i].num == num)
            return 1;
    }
    return 0;
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
        pause();
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

    fclose(fileDoctor);
    fclose(filePatient);
    fclose(fileScheduled);
}

// Pausar
void pause()
{
    printf("Pressione qualquer tecla para continuar...");
    getchar();
}

// Opções de Médico
void opcoesMedico(DOCTOR *doctor, SCHEDULED *scheduled)
{
    int option;

    do
    {
        clear();

        printf("1 - Incluir médico\n");
        printf("2 - Alterar médico\n");
        printf("3 - Excluir médico\n");
        printf("4 - Pesquisar médico\n");
        printf("5 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            incluirMedico(doctor);
            break;
        case 2:
            alterarMedico(doctor);
            break;
        case 3:
            excluirMedico(doctor, scheduled);
            break;
        case 4:
            pesquisarMedico(doctor);
            break;
        case 5:
            printf("Voltando\n");
            break;
        default:
            printf("Opção inválida\n");
            pause();
            break;
        }

    } while (option != 5);
}

// Incluir médico
void incluirMedico(DOCTOR *doctor)
{
    clear();

    int i = 0;

    while (doctor[i].dcIdentification[0] != '\0')
    {
        i++;
    }

    if (i >= 20)
    {
        printf("Número máximo de médicos atingido\n");
        pause();
        return;
    }

    printf("Identificação do médico: ");
    scanf("%s", doctor[i].dcIdentification);
    getchar();

    printf("Nome do médico: ");
    fgets(doctor[i].name, 50, stdin);
    doctor[i].name[strcspn(doctor[i].name, "\n")] = '\0';

    printf("Especialidade do médico: ");
    scanf("%s", doctor[i].specialization);
    getchar();

    printf("Médico incluído com sucesso!\n");

    pause();
}

// Alterar médico
void alterarMedico(DOCTOR *doctor)
{
    clear();

    int i = 0, indicador = 0, choice;
    char id[50];

    printf("Deseja ver a lista de médicos? (1 - Sim, 2 - Não): ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Médicos cadastrados:\n");
        for (i = 0; doctor[i].name[0] != '\0'; ++i)
        {
            if (doctor[i].name[0] != '\0')
            {
                printf("ID: %s\nNome: %s\nEspecialização: %s\n\n", doctor[i].dcIdentification, doctor[i].name, doctor[i].specialization);
            }
        }
    }

    i = 0;

    printf("Identificação do médico que deseja alterar (Digite 0 para cancelar): ");
    scanf("%s", id);
    getchar();

    if (id[0] == '0')
    {
        printf("Retornando ao menu");
        return;
    }

    while (doctor[i].dcIdentification[0] != '\0')
    {
        if (strcmp(doctor[i].dcIdentification, id) == 0)
        {
            printf("O que deseja alterar?\n1 - Nome do médico\n2 - Especialidade do médico\n3 - Todas as opções\n");
            scanf("%d", &choice);
            getchar();

            switch (choice)
            {
            case 1:
                printf("Nome do médico: ");
                fgets(doctor[i].name, 50, stdin);
                doctor[i].name[strcspn(doctor[i].name, "\n")] = '\0';
                printf("Médico alterado com sucesso!\n");
                break;
            case 2:
                printf("Especialidade do médico: ");
                scanf("%s", doctor[i].specialization);
                getchar();
                printf("Médico alterado com sucesso!\n");
                break;
            case 3:
                printf("Nome do médico: ");
                fgets(doctor[i].name, 50, stdin);
                doctor[i].name[strcspn(doctor[i].name, "\n")] = '\0';
                printf("Especialidade do médico: ");
                scanf("%s", doctor[i].specialization);
                getchar();
                printf("Médico alterado com sucesso!\n");
                break;
            default:
                printf("Opção inválida\nTente novamente\n");
                break;
            }

            indicador = 1;
            break;
        }
        i++;
    }

    if (indicador == 0)
    {
        printf("Médico não encontrado\n");
    }

    pause();
}

// Excluir médico
void excluirMedico(DOCTOR *doctor, SCHEDULED *scheduled)
{
    clear();

    int i = 0, j = 0, indicador = 0;
    char id[50];

    printf("Identificação do médico: ");
    scanf("%s", id);
    getchar();

    while (doctor[i].dcIdentification[0] != '\0')
    {
        if (strcmp(doctor[i].dcIdentification, id) == 0)
        {
            // Excluir todas as consultas do médico
            int totalConsultas = 0;
            while (scheduled[totalConsultas].num != 0)
                totalConsultas++;

            for (j = 0; j < totalConsultas; j++)
            {
                if (strcmp(scheduled[j].dcIdentification, id) == 0)
                {
                    for (int k = j; k < totalConsultas - 1; k++)
                    {
                        scheduled[k] = scheduled[k + 1];
                    }
                    scheduled[totalConsultas - 1].num = 0;
                    totalConsultas--;
                    j--;
                }
            }

            for (int k = i; k < 19; k++)
            {
                doctor[k] = doctor[k + 1];
            }

            printf("Médico excluído com sucesso!\n");
            indicador = 1;
            break;
        }
        i++;
    }

    if (indicador == 0)
    {
        printf("Médico não encontrado\n");
    }

    pause();
}

// Pesquisar médico
void pesquisarMedico(DOCTOR *doctor)
{
    clear();

    int i = 0, indicador = 0;
    char id[50];

    printf("Identificação do médico: ");
    scanf("%s", id);
    getchar();

    while (doctor[i].dcIdentification[0] != '\0')
    {
        if (strcmp(doctor[i].dcIdentification, id) == 0)
        {
            printf("Nome: %s\n", doctor[i].name);
            printf("Especialidade: %s\n", doctor[i].specialization);
            indicador = 1;
            break;
        }
        i++;
    }

    if (indicador == 0)
    {
        printf("Médico não encontrado\n");
    }

    pause();
}

// Opções de Paciente
void opcoesPaciente(PATIENT *patient, SCHEDULED *scheduled)
{
    int option;

    do
    {
        clear();

        printf("1 - Incluir paciente\n");
        printf("2 - Alterar paciente\n");
        printf("3 - Excluir paciente\n");
        printf("4 - Pesquisar paciente\n");
        printf("5 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            incluirPaciente(patient);
            break;
        case 2:
            alterarPaciente(patient);
            break;
        case 3:
            excluirPaciente(patient, scheduled);
            break;
        case 4:
            pesquisarPaciente(patient);
            break;
        case 5:
            printf("Voltando\n");
            break;
        default:
            printf("Opção inválida\n");
            pause();
            break;
        }

    } while (option != 5);
}

// Incluir paciente
void incluirPaciente(PATIENT *patient)
{
    clear();

    int i = 0;

    while (patient[i].paIdentification[0] != '\0')
    {
        i++;
    }

    if (i >= 50)
    {
        printf("Número máximo de pacientes atingido\n");
        pause();
        return;
    }

    printf("Identificação do paciente: ");
    scanf("%s", patient[i].paIdentification);
    getchar();

    printf("Nome do paciente: ");
    fgets(patient[i].name, 50, stdin);
    patient[i].name[strcspn(patient[i].name, "\n")] = '\0';

    printf("Identidade do paciente: ");
    scanf("%s", patient[i].id);
    getchar();

    printf("Endereço do paciente (Rua): ");
    fgets(patient[i].address.street, 50, stdin);
    patient[i].address.street[strcspn(patient[i].address.street, "\n")] = '\0';

    printf("Endereço do paciente (Cidade): ");
    fgets(patient[i].address.city, 50, stdin);
    patient[i].address.city[strcspn(patient[i].address.city, "\n")] = '\0';

    printf("Endereço do paciente (Estado): ");
    fgets(patient[i].address.state, 50, stdin);
    patient[i].address.state[strcspn(patient[i].address.state, "\n")] = '\0';

    printf("Endereço do paciente (CEP): ");
    scanf("%s", patient[i].address.zip);
    getchar();

    printf("Telefone do paciente: ");
    fgets(patient[i].phone, 50, stdin);
    patient[i].phone[strcspn(patient[i].phone, "\n")] = '\0';

    printf("Sexo do paciente: ");
    scanf("%s", patient[i].gender);
    getchar();

    printf("Paciente incluído com sucesso!\n");

    pause();
}

// Alterar paciente
void alterarPaciente(PATIENT *patient)
{
    clear();

    int i = 0, indicador = 0, choice;
    char id[50];

    printf("Identificação do paciente que deseja alterar: ");
    scanf("%s", id);
    getchar();

    while (patient[i].paIdentification[0] != '\0')
    {
        if (strcmp(patient[i].paIdentification, id) == 0)
        {

            printf("Deseja ver as informações do paciente? (1 - Sim, 2 - Não): ");
            scanf("%d", &choice);

            if (choice == 1)
            {
                printf("ID: %s\nNome: %s\nIdentidade: %s\nEndereço: Rua %s, %s - %s, CEP: %s\nTelefone %s\nSexo: %s\n\n", patient[i].paIdentification, patient[i].name, patient[i].id, patient[i].address.street, patient[i].address.city, patient[i].address.state, patient[i].address.zip, patient[i].phone, patient[i].gender);
            }

            printf("O que deseja alterar?\n1 - Nome do paciente\n2 - Identidade do paciente\n3 - Endereço do paciente\n4 - Telefone do paciente\n5 - Sexo do paciente\n6 - Todos os dados\n");
            scanf("%d", &choice);
            getchar();

            switch (choice)
            {
            case 1:
                fgets(patient[i].name, 50, stdin);
                patient[i].name[strcspn(patient[i].name, "\n")] = '\0';
                break;
            case 2:
                scanf("%s", patient[i].id);
                getchar();
                break;
            case 3:
                printf("Digite a rua: ");
                fgets(patient[i].address.street, 50, stdin);
                patient[i].address.street[strcspn(patient[i].address.street, "\n")] = '\0';

                printf("Digite a cidade: ");
                fgets(patient[i].address.city, 50, stdin);
                patient[i].address.city[strcspn(patient[i].address.city, "\n")] = '\0';

                printf("Digite o estado: ");
                fgets(patient[i].address.state, 50, stdin);
                patient[i].address.state[strcspn(patient[i].address.state, "\n")] = '\0';

                printf("Digite o CEP: ");
                scanf("%s", patient[i].address.zip);
                getchar();
                break;
            case 4:
                fgets(patient[i].phone, 50, stdin);
                patient[i].phone[strcspn(patient[i].phone, "\n")] = '\0';
                break;
            case 5:
                scanf("%s", patient[i].gender);
                getchar();
                break;
            case 6:
                printf("Nome: ");
                fgets(patient[i].name, 50, stdin);
                patient[i].name[strcspn(patient[i].name, "\n")] = '\0';

                printf("Identidade: ");
                scanf("%s", patient[i].id);
                getchar();

                printf("Digite a rua: ");
                fgets(patient[i].address.street, 50, stdin);
                patient[i].address.street[strcspn(patient[i].address.street, "\n")] = '\0';

                printf("Digite a cidade: ");
                fgets(patient[i].address.city, 50, stdin);
                patient[i].address.city[strcspn(patient[i].address.city, "\n")] = '\0';

                printf("Digite o estado: ");
                fgets(patient[i].address.state, 50, stdin);
                patient[i].address.state[strcspn(patient[i].address.state, "\n")] = '\0';

                printf("Digite o CEP: ");
                scanf("%s", patient[i].address.zip);
                getchar();

                printf("Telefone: ");
                scanf("%s", patient[i].phone);
                getchar();

                printf("Sexo: ");
                scanf("%s", patient[i].gender);
                getchar();

                break;
            default:
                printf("Opção inválida\nTente novamente\n");
                break;
            }
            indicador = 1;
            break;
        }
        i++;
    }

    if (indicador == 0)
    {
        printf("Paciente não encontrado\n");
    }

    pause();
}

// Excluir paciente
void excluirPaciente(PATIENT *patient, SCHEDULED *scheduled)
{
    clear();

    int i = 0, j = 0, indicador = 0;
    char id[50];

    printf("Identificação do paciente: ");
    scanf("%s", id);
    getchar();

    while (patient[i].paIdentification[0] != '\0')
    {
        if (strcmp(patient[i].paIdentification, id) == 0)
        {
            // Excluir todas as consultas do paciente
            int totalConsultas = 0;
            while (scheduled[totalConsultas].num != 0)
                totalConsultas++;

            for (j = 0; j < totalConsultas; j++)
            {
                if (strcmp(scheduled[j].paIdentification, id) == 0)
                {
                    scheduled[j].num = 0;
                    scheduled[j].dcIdentification[0] = '\0';
                    scheduled[j].paIdentification[0] = '\0';

                    for (int k = j; k < totalConsultas - 1; k++)
                    {
                        scheduled[k] = scheduled[k + 1];
                    }
                    scheduled[totalConsultas - 1].num = 0;
                    totalConsultas--;
                    j--;
                }
            }

            for (int k = i; k < 49; k++)
            {
                patient[k] = patient[k + 1];
            }

            printf("Paciente excluído com sucesso!\n");
            indicador = 1;
            break;
        }
        i++;
    }

    if (indicador == 0)
    {
        printf("Paciente não encontrado\n");
    }

    pause();
}

// Pesquisar paciente
void pesquisarPaciente(PATIENT *patient)
{
    clear();

    int i = 0, indicador = 0;
    char id[50];

    printf("Identificação do paciente: ");
    scanf("%s", id);
    getchar();

    while (patient[i].paIdentification[0] != '\0')
    {
        if (strcmp(patient[i].paIdentification, id) == 0)
        {
            printf("Nome: %s\n", patient[i].name);
            printf("Identidade: %s\n", patient[i].id);
            printf("Endereço: %s, %s, %s, %s\n", patient[i].address.street, patient[i].address.city, patient[i].address.state, patient[i].address.zip);
            printf("Telefone: %s\n", patient[i].phone);
            printf("Sexo: %s\n", patient[i].gender);
            indicador = 1;
            break;
        }
        i++;
    }

    if (indicador == 0)
    {
        printf("Paciente não encontrado\n");
    }

    pause();
}

// Relatórios
void relatorios(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled)
{
    int option;

    do
    {
        clear();

        printf("1 - Lista de consultas agendadas para o paciente\n");
        printf("2 - Lista de consultas agendadas para o médico\n");
        printf("3 - Lista de pacientes por especialidade\n");
        printf("4 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            listaConsultasPaciente(patient, scheduled);
            break;
        case 2:
            listaConsultasMedico(doctor, scheduled);
            break;
        case 3:
            listaPacientesPorEspecialidade(doctor, patient, scheduled);
            break;
        case 4:
            printf("Voltando\n");
            break;
        default:
            printf("Opção inválida\n");
            pause();
            break;
        }

    } while (option != 4);
}

// Lista de consultas agendadas para o paciente
void listaConsultasPaciente(PATIENT *patient, SCHEDULED *scheduled)
{
    clear();

    int i = 0, indicador = 0;
    char id[50];

    printf("Identificação do paciente: ");
    scanf("%s", id);
    getchar();

    while (patient[i].paIdentification[0] != '\0')
    {
        if (strcmp(patient[i].paIdentification, id) == 0)
        {
            indicador = 1;
            break;
        }
        i++;
    }

    if (indicador == 0)
    {
        printf("Paciente não encontrado\n");
        pause();
        return;
    }

    i = 0;
    indicador = 0;

    while (scheduled[i].num != 0)
    {
        if (strcmp(scheduled[i].paIdentification, id) == 0)
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

    pause();
}

// Lista de consultas agendadas para o médico
void listaConsultasMedico(DOCTOR *doctor, SCHEDULED *scheduled)
{
    clear();

    int i = 0, indicador = 0;
    char id[50];

    printf("Identificação do médico: ");
    scanf("%s", id);
    getchar();

    while (doctor[i].dcIdentification[0] != '\0')
    {
        if (strcmp(doctor[i].dcIdentification, id) == 0)
        {
            indicador = 1;
            break;
        }
        i++;
    }

    if (indicador == 0)
    {
        printf("Médico não encontrado\n");
        pause();
        return;
    }

    i = 0;
    indicador = 0;

    while (scheduled[i].num != 0)
    {
        if (strcmp(scheduled[i].dcIdentification, id) == 0)
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

    pause();
}

// Lista de pacientes por especialidade
void listaPacientesPorEspecialidade(DOCTOR *doctor, PATIENT *patient, SCHEDULED *scheduled)
{
    clear();

    int i = 0, j = 0, k = 0;
    int indicadorp = 0, indicadorm = 0, cont = 0;
    char especialidade[50];
    char temp[50][50];

    printf("Especialidade: ");
    scanf("%s", especialidade);
    getchar();

    while (doctor[i].dcIdentification[0] != '\0')
    {
        if (strcmp(doctor[i].specialization, especialidade) == 0)
        {
            for (j = 0; scheduled[j].num != 0; j++)
            {
                if (strcmp(scheduled[j].dcIdentification, doctor[i].dcIdentification) == 0)
                {
                    indicadorm = 1;
                    for (k = 0; patient[k].paIdentification[0] != '\0'; k++)
                    {
                        if (strcmp(scheduled[j].paIdentification, patient[k].paIdentification) == 0)
                        {
                            int duplicata = 0;
                            for (int x = 0; x < cont; x++)
                            {
                                if (strcmp(temp[x], patient[k].paIdentification) == 0)
                                {
                                    duplicata = 1;
                                    break;
                                }
                            }
                            if (!duplicata)
                            {
                                printf("%s\n", patient[k].name);
                                strcpy(temp[cont], patient[k].paIdentification);
                                cont++;
                                indicadorp = 1;
                            }
                        }
                    }
                }
            }
        }
        i++;
    }

    if (indicadorm == 0)
    {
        printf("Nenhum médico nessa especialidade possui consulta marcada\n");
        pause();
        return;
    }
    else if (indicadorp == 0)
    {
        printf("Nenhum paciente agendado para essa especialidade\n");
    }

    pause();
}