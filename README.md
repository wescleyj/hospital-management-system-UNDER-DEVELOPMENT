<<<<<<< HEAD
# Hospital Management System in C

## Descrição
Este projeto implementa um sistema de gerenciamento hospitalar utilizando a linguagem C. Ele permite o cadastro, controle e geração de relatórios de médicos, pacientes e consultas. O programa é modular, garantindo organização e facilidade de manutenção.

## Funcionalidades
- **Cadastro e Gerenciamento:**
  - Inclusão, alteração e exclusão de médicos, pacientes e consultas.
  - Exclusão automática de consultas associadas a médicos ou pacientes removidos.
- **Relatórios:**
  - Lista de consultas agendadas para um paciente específico.
  - Lista de consultas agendadas para um médico específico.
  - Lista de pacientes filtrados por especialidade médica.
- **Limites de Armazenamento:**
  - Até 50 pacientes.
  - Até 20 médicos.
  - Até 100 consultas.

## Estrutura do Menu Principal
1. Consulta
2. Paciente
3. Médico
4. Relatórios
5. Sair

## Tecnologias Utilizadas
- Linguagem C

## Como Usar
1. Clone este repositório:
   ```bash
   git clone https://github.com/wescleyj/hospital-management-system.git
   ```
2. Entre na pasta do repositório clonado:
   ```bash
   cd hospital-management-system
   
4. Compile o programa:
   ```bash
   gcc hospital_system.c -o hospital_system
   ```
5. Execute o programa:
   ```bash
   ./hospital_system
   ```

## Estrutura do Código
- **Médico:**
  - Identificador
  - Nome
  - Especialidade
- **Paciente:**
  - Identificador
  - Nome
  - Identidade
  - Endereço completo
  - Telefone
  - Sexo
- **Consulta:**
  - Número
  - Identificador do médico
  - Identificador do paciente
  - Horário
  - Duração
  - Data

## Validações Implementadas
- Exclusão automática de consultas ao remover médicos ou pacientes associados.
- Exibição de campos antes da alteração para facilitar edições.

## Contribuição
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests com melhorias e correções.

## Licença
Este projeto está sob a licença MIT. Consulte o arquivo [LICENSE](LICENSE) para mais detalhes.
```

Se precisar de alguma alteração ou adaptação, é só avisar!
=======
# Hospital Management System in C

## Description
This project implements a hospital management system using the C programming language. It allows for the registration, management, and report generation of doctors, patients, and appointments. The program is modular, ensuring organization and easy maintenance.

## Features
- **Registration and Management:**
  - Adding, updating, and deleting doctors, patients, and appointments.
  - Automatic deletion of appointments associated with removed doctors or patients.
- **Reports:**
  - List of scheduled appointments for a specific patient.
  - List of scheduled appointments for a specific doctor.
  - List of patients filtered by medical specialty.
- **Storage Limits:**
  - Up to 50 patients.
  - Up to 20 doctors.
  - Up to 100 appointments.

## Main Menu Structure
1. Appointments
2. Patients
3. Doctors
4. Reports
5. Exit

## Technologies Used
- C Programming Language

## How to Use
1. Clone this repository:
   ```bash
   git clone https://github.com/wescleyj/hospital-management-system-UNDER-DEVELOPMENT.git
   ```
2. Navigate to the cloned repository folder:
   ```bash
   cd hospital-management-system-UNDER-DEVELOPMENT
   ```
3. Compile the program:
   ```bash
   gcc hospital_system.c -o hospital_system
   ```
4. Run the program:
   ```bash
   ./hospital_system
   ```

## Code Structure
- **Doctor:**
  - ID
  - Name
  - Specialty
- **Patient:**
  - ID
  - Name
  - ID number
  - Full address
  - Phone number
  - Gender
- **Appointment:**
  - Number
  - Doctor ID
  - Patient ID
  - Time
  - Duration
  - Date

## Implemented Validations
- Automatic deletion of appointments when removing associated doctors or patients.
- Display of fields before editing to simplify updates.

## Contribution
Contributions are welcome! Feel free to open issues or pull requests with improvements and fixes.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
>>>>>>> 97d322fb335b8b3799a61ecd26421cff22413d6b
