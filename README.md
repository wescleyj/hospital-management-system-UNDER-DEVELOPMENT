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
