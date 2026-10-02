# Student Management Record System

A C++ console-based Student Management System with file-based data persistence and local AI integration using Ollama.

## Features

- Add student records
- Display all student records
- Search students by Student ID
- Update student details
- Delete student records
- Prevent duplicate Student IDs
- Validate age and marks
- Save student data to a text file
- Load saved student data when the program starts
- AI-based individual student analysis
- AI-based identification of students who may need academic attention

## Technologies Used

- **C++**
- **Object-Oriented Programming (OOP)**
- **STL** — `vector`, `find_if`
- **File Handling** — `fstream`, `stringstream`
- **JSON** — nlohmann/json
- **WinHTTP** — communication with the local AI service
- **Ollama**
- **Qwen 3.5 4B**

## Project Structure

```text
Student-Management-Record-system/
│
├── student_management.cpp
├── json.hpp
├── student.txt
├── README.md
└── .gitignore
```

## How It Works

The program stores student records in a C++ `vector`.

Each student contains:

- Student ID
- Name
- Age
- Branch
- Semester
- Marks

Student records are saved in `student.txt`, allowing data to persist after the program closes.

The AI features send student information from the C++ program to a locally running Ollama model through the Ollama API.

```text
C++ Program
     │
     ├── Student Management
     │
     ├── File Handling
     │
     └── AI Assistant
             │
             ▼
          WinHTTP
             │
             ▼
     Local Ollama API
             │
             ▼
        Qwen 3.5 4B
```

## AI Features

### 1. Analyze Student

Enter a Student ID and the program sends that student's information to the local AI model.

The AI provides a short academic analysis based on the student's details and marks.

### 2. Find Weak Students

The program sends the marks of all stored students to the AI model.

The AI identifies students who may need academic attention and provides a reason for each one.

## Requirements

Before running the AI features, install:

- A C++ compiler such as MinGW/G++
- [Ollama](https://ollama.com/)
- The `qwen3.5:4b` model

Pull the model with:

```bash
ollama pull qwen3.5:4b
```

Make sure Ollama is running before using the AI features.

## Compilation

From the project directory:

```bash
g++ student_management.cpp -o student.exe -lwinhttp
```

## Run

```powershell
.\student.exe
```

## Main Menu

```text
1. Insert Student Details
2. Display all student
3. Update Details & Search Student
4. Delete Student
5. AI Helper
6. Exit
```

## Data Format

Student data is stored in the following format:

```text
StudentID|Name|Age|Branch|Marks|Semester
```

Example:

```text
101|Rahul|20|CSE|75|3
```

## What I Learned

This project was built to practice and combine:

- Classes and objects
- Constructors
- Encapsulation
- Member functions
- `vector`
- Iterators
- `find_if`
- Lambda expressions
- File input/output
- Searching, updating and deleting records
- JSON handling
- HTTP requests from C++
- Connecting a C++ application with a local AI model

## Future Improvements

Possible future improvements:

- Add a graphical user interface
- Add login/authentication
- Add more student statistics
- Add class performance reports
- Add marks update functionality
- Improve input validation
- Add more AI-assisted features
- Move from text-file storage to a database

## Author

**Bhavesh**

GitHub: [BhaveshEngine](https://github.com/BhaveshEngine)
