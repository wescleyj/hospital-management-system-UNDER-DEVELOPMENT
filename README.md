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
   hospital_system
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
