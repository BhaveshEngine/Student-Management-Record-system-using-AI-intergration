#include <iostream>

#include <string>

#include <vector>

#include <algorithm>

#include <fstream>

#include <sstream>

#include <windows.h>

#include <winhttp.h>

#include "json.hpp"

#pragma comment(lib, "winhttp.lib")

using json = nlohmann::json;

using namespace std;

// ==================== UI FUNCTIONS ====================

void clear_screen()

{

    system("cls");
}

void line()

{

    cout << "========================================\n";
}

void title(string text)

{

    line();

    cout << "        " << text << "\n";

    line();
}

// ==================== STUDENT CLASS ====================

class Student

{

    int Student_id;

    string Name;

    int Age;

    string Branch;

    int Semester;

    float marks;

public:
    Student() {}

    Student(int Student_id, string Name, int Age, string Branch, int Semester, float Marks)

        : Student_id(Student_id),

          Name(Name),

          Age(Age),

          Branch(Branch),

          Semester(Semester),

          marks(Marks)

    {
    }

    void insert_details(const vector<Student> &Student_record);

    void student_info();

    void Detail_update(const vector<Student> &Student_record, int current_index);

    int student_id();

    void Search_Student(vector<Student> &Student_record);

    void delete_student(vector<Student> &Student_record);

    void save_to_file(ofstream &File) const;

    void AI_Assistant(vector<Student> &Student_record);

    int get_id() const

    {

        return Student_id;
    }

    string get_name() const

    {

        return Name;
    }

    int get_age() const

    {

        return Age;
    }

    string get_branch() const

    {

        return Branch;
    }

    int get_semester() const

    {

        return Semester;
    }

    float get_marks() const

    {

        return marks;
    }
};

// ==================== INSERT DETAILS ====================

void Student::insert_details(const vector<Student> &Student_record)

{

    cin.ignore();

    cout << "  Student Name : ";

    getline(cin, Name);

    // ID duplication check

    while (true)

    {

        cout << "  Student ID   : ";

        cin >> Student_id;

        auto it = find_if(

            Student_record.begin(),

            Student_record.end(),

            [this](const Student &student)

            {
                return student.Student_id == this->Student_id;
            });

        if (it == Student_record.end())

            break;

        cout << "\n  [ERROR] ID already exists!\n";

        cout << "  Enter a different ID.\n\n";
    }

    // Age checking

    while (true)

    {

        int temp;

        cout << "  Age          : ";

        cin >> temp;

        if (temp >= 18 && temp <= 30)

        {

            Age = temp;

            break;
        }

        else

            cout << "\n  [ERROR] Age must be between 18 and 30.\n\n";
    }

    cout << "  Branch       : ";

    cin >> Branch;

    cout << "  Semester     : ";

    cin >> Semester;

    while (true)

    {

        int tmp;

        cout << " Marks       : ";

        cin >> tmp;

        if (tmp >= 0 && tmp <= 100)

        {

            marks = tmp;

            break;
        }

        else

            cout << "Marks should not greater than the 100" << endl;
    }
}

// ===================./ DISPLAY DETAILS ====================

void Student::student_info()

{

    line();

    cout << "  Student ID   : " << Student_id << endl;

    cout << "  Name         : " << Name << endl;

    cout << "  Age          : " << Age << endl;

    cout << "  Branch       : " << Branch << endl;

    cout << "  Semester     : " << Semester << endl;

    cout << "  marks        :  " << marks << endl;

    line();
}

// ==================== UPDATE DETAILS ====================

void Student::Detail_update(

    const vector<Student> &Student_record,

    int current_index)

{

    int choices;

    title("UPDATE STUDENT");

    cout << "  1. Name\n";

    cout << "  2. Student ID\n";

    cout << "  3. Age\n";

    cout << "  4. Branch\n";

    cout << "  5. Semester\n";

    line();

    cout << "  Enter choice : ";

    cin >> choices;

    switch (choices)

    {

    case 1:

        cin.ignore();

        cout << "  New Name : ";

        getline(cin, Name);

        cout << "\n  [SUCCESS] Name updated.\n";

        break;

    case 2:

    {

        int temp;

        cout << "  New ID : ";

        cin >> temp;

        auto dup = find_if(

            Student_record.begin(),

            Student_record.end(),

            [temp, current_index, &Student_record](const Student &str)

            {
                // Ignore the student currently being updated

                if (&str == &Student_record[current_index])

                    return false;

                // Check other students for duplicate ID

                return str.Student_id == temp;
            });

        if (dup == Student_record.end())

        {

            Student_id = temp;

            cout << "\n  [SUCCESS] Student ID updated.\n";
        }

        else

        {

            cout << "\n  [ERROR] Student ID already exists!\n";
        }

        break;
    }

    case 3:

        cout << "  New Age : ";

        cin >> Age;

        if (Age >= 18 && Age <= 30)

            cout << "\n  [SUCCESS] Age updated.\n";

        else

            cout << "\n  [ERROR] Age must be between 18 and 30.\n";

        break;

    case 4:

        cout << "  New Branch : ";

        cin >> Branch;

        cout << "\n  [SUCCESS] Branch updated.\n";

        break;

    case 5:

        cout << "  New Semester : ";

        cin >> Semester;

        cout << "\n  [SUCCESS] Semester updated.\n";

        break;

    default:

        cout << "\n  [ERROR] Invalid choice.\n";

        break;
    }
    save_data(Student_record);
}

// ==================== GET STUDENT ID ====================

int Student::student_id()

{

    return Student_id;
}

// ==================== SEARCH STUDENT ====================

void Student::Search_Student(vector<Student> &Student_record)

{

    int temp;

    title("SEARCH STUDENT");

    cout << "  Enter Student ID : ";

    cin >> temp;

    auto search = find_if(

        Student_record.begin(),

        Student_record.end(),

        [temp](const Student &student)

        {
            return student.Student_id == temp;
        });

    if (search == Student_record.end())

    {

        cout << "\n  [ERROR] Student not found.\n";

        return;
    }

    int index = search - Student_record.begin();

    cout << "\n  [SUCCESS] Student found.\n";

    Student_record[index].student_info();

    bool check = true;

    while (check)

    {

        cout << "\n";

        cout << "  1. Update Details\n";

        cout << "  2. Exit\n";

        line();

        int choices;

        cout << "  Enter choice : ";

        cin >> choices;

        if (choices == 1)

        {

            Student_record[index].Detail_update(

                Student_record,

                index);

            cout << "\n";

            Student_record[index].student_info();
        }

        else if (choices == 2)

        {

            check = false;
        }

        else

        {

            cout << "\n  [ERROR] Invalid choice.\n";
        }
    }
}

// ==================== DELETE STUDENT ====================

void save_data(const vector<Student> &Student_record);
void Student::delete_student(vector<Student> &Student_record)

{

    int temp = 0;

    cout << "Enter the Student ID to Delete : " << endl;

    cin >> temp;

    // Its search of the student inside the temp and return it iterator

    auto search = find_if(Student_record.begin(),

                          Student_record.end(),

                          [temp](const Student &st)

                          {
                              return st.Student_id == temp;
                          });

    // its check the student is present or not

    if (search == Student_record.end())

    {

        cout << "Student is not found to Delete : ";

        return;
    }

    int index = search - Student_record.begin();

    cout << "Studnet is found --- deleting in progress" << endl;

    // this will delete the index inside the vector

    Student_record.erase(Student_record.begin() + index);
    save_data(Student_record);
}

// ==================== FILE HANDLING ====================

void save_data(const vector<Student> &Student_record)
{
    ofstream file("student.txt");

    if (!file)
    {
        cout << "\n[ERROR] Could not open student.txt for writing.\n";
        return;
    }

    for (const Student &student : Student_record)
    {
        student.save_to_file(file);
    }

    file.close();

    cout << "\n[DATA SAVED] " << Student_record.size()
         << " student(s) saved.\n";
}

void Student::save_to_file(ofstream &file) const

{

    file << Student_id << "|"

         << Name << "|"

         << Age << "|"

         << Branch << "|"

         << marks << "|"

         << Semester << "\n";
}

void load_data(vector<Student> &Student_record)

{

    ifstream file("student.txt");

    if (!file)

    {

        cout << "File Not found!" << endl;

        return;
    }

    int id;

    int age;

    int semester;

    string name;

    string branch;

    string line;

    float marks;

    while (getline(file, line))

    {

        stringstream ss(line);

        ss >> id;

        ss.ignore();

        getline(ss, name, '|');

        ss >> age;

        ss.ignore();

        getline(ss, branch, '|');

        ss >> marks;

        ss.ignore();

        ss >> semester;

        Student student(id, name, age, branch, semester, marks);

        Student_record.push_back(student);
        
    }

    file.close();
}

// ==================== AI ANALYZER ====================

void analyze_student(Student &student);
void find_weak_students(vector<Student> &Student_record);

void Student::AI_Assistant(vector<Student> &Student_record)

{

    title("AI ASSISTANT");

    cout << " 1. Analyze Student\n";

    cout << " 2. Find Weak Students\n";

    cout << " 3. Back\n";

    cout << "\n Enter choice : ";

    int choice;

    cin >> choice;

    switch (choice)

    {

    case 1:

    {

        int id;

        cout << "\nEnter Student ID: ";

        cin >> id;

        auto student = find_if(

            Student_record.begin(),

            Student_record.end(),

            [id](const Student &student)

            {
                return student.Student_id == id;
            });

        if (student == Student_record.end())

        {

            cout << "\nStudent not found!\n";

            break;
        }

        cout << "\nStudent found.\n";
        student->student_info();

        analyze_student(*student);

        break;
    }

    case 2:

        find_weak_students(Student_record);

        break;

    case 3:

        cout << "Exiting........." << endl;
        break;

    

    default:

        cout << "Invalid choice!\n";
    }
}

void analyze_student(Student &student)

{

    string prompt =

        "Analyze this student and give a short academic analysis.\n\n"

        "Student ID: " +
        to_string(student.get_id()) + "\n"

                                      "Name: " +
        student.get_name() + "\n"

                             "Age: " +
        to_string(student.get_age()) + "\n"

                                       "Branch: " +
        student.get_branch() + "\n"

                               "Semester: " +
        to_string(student.get_semester()) + "\n"

                                            "Marks: " +
        to_string(student.get_marks());

    // Connect to Ollama

    HINTERNET session = WinHttpOpen(

        L"StudentAI",

        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,

        WINHTTP_NO_PROXY_NAME,

        WINHTTP_NO_PROXY_BYPASS,

        0

    );

    HINTERNET connect = WinHttpConnect(

        session,

        L"localhost",

        11434,

        0

    );

    HINTERNET request = WinHttpOpenRequest(

        connect,

        L"POST",

        L"/api/generate",

        NULL,

        WINHTTP_NO_REFERER,

        WINHTTP_DEFAULT_ACCEPT_TYPES,

        0

    );

    // Create JSON request

    json requestData = {

        {"model", "qwen3.5:4b"},

        {"prompt", prompt},

        {"stream", false}

    };

    string requestBody = requestData.dump();

    WinHttpSendRequest(

        request,

        L"Content-Type: application/json",

        -1,

        (LPVOID)requestBody.c_str(),

        requestBody.size(),

        requestBody.size(),

        0

    );

    WinHttpReceiveResponse(request, NULL);

    // Read response

    char buffer[4096];

    DWORD bytesRead;

    string result;

    while (WinHttpReadData(

        request,

        buffer,

        sizeof(buffer) - 1,

        &bytesRead))

    {

        if (bytesRead == 0)

            break;

        buffer[bytesRead] = '\0';

        result += buffer;
    }

    // Parse Ollama JSON

    json responseData = json::parse(result);

    cout << "\n================ AI ANALYSIS ================\n";

    cout << responseData["response"].get<string>();

    cout << "\n=============================================\n";

    WinHttpCloseHandle(request);

    WinHttpCloseHandle(connect);

    WinHttpCloseHandle(session);
}

// Weak student
void find_weak_students(vector<Student> &Student_record)
{
    if (Student_record.empty())
    {
        cout << "\nNo students available.\n";
        return;
    }

    string prompt =
        "Analyze the following students based on their marks.\n"
        "Identify students who may need academic attention.\n"
        "For each student, give their ID, name, marks, and a short reason.\n\n";

    for (const Student &student : Student_record)
    {
        prompt +=
            "ID: " + to_string(student.get_id()) +
            ", Name: " + student.get_name() +
            ", Marks: " + to_string(student.get_marks()) +
            "\n";
    }

    cout << "\nAI is analyzing all students...\n";

    HINTERNET session = WinHttpOpen(
        L"StudentAI",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);

    HINTERNET connect = WinHttpConnect(
        session,
        L"localhost",
        11434,
        0);

    HINTERNET request = WinHttpOpenRequest(
        connect,
        L"POST",
        L"/api/generate",
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        0);

    json requestData =
        {
            {"model", "qwen3.5:4b"},
            {"prompt", prompt},
            {"stream", false}};

    string requestBody = requestData.dump();

    if (!WinHttpSendRequest(
            request,
            L"Content-Type: application/json",
            -1,
            (LPVOID)requestBody.c_str(),
            requestBody.size(),
            requestBody.size(),
            0))
    {
        cout << "\n[ERROR] WinHttpSendRequest failed: "
             << GetLastError() << endl;
        return;
    }

    if (!WinHttpReceiveResponse(request, NULL))
    {
        cout << "\n[ERROR] WinHttpReceiveResponse failed: "
             << GetLastError() << endl;
        return;
    }

    char buffer[4096];
    DWORD bytesRead;
    string result;

    while (WinHttpReadData(
        request,
        buffer,
        sizeof(buffer) - 1,
        &bytesRead))
    {
        if (bytesRead == 0)
            break;

        buffer[bytesRead] = '\0';
        result += buffer;
    }

  
    cout << result << endl;

    if (result.empty())
    {
        cout << "\n[ERROR] Ollama returned an empty response.\n";
        cout << "Check that Ollama is running.\n";
        return;
    }

    try
    {
        json responseData = json::parse(result);

        cout << "\n";
        cout << "================ WEAK STUDENT ANALYSIS ================\n";
        cout << responseData["response"].get<string>();
        cout << "\n=========================================================\n";
    }
    catch (const json::exception &e)
    {
        cout << "\n[ERROR] Invalid response from Ollama.\n";
        cout << e.what() << endl;
        cout << "\nRaw response:\n"
             << result << endl;
    }

    WinHttpCloseHandle(request);
    WinHttpCloseHandle(connect);
    WinHttpCloseHandle(session);
}
// ==================== MAIN ====================

int main()

{

    Student b1;

    vector<Student> Student_record;

    load_data(Student_record);

    int choice = 0;

    bool loop = true;

    int Number_Record = 0;

    clear_screen();

    while (loop)

    {

        line();

        title("MAIN MENU");

        line();

        // menu print

        cout << " 1. Insert Student Details\n"

             << " 2. Display all student\n"

             << " 3. Update Details & Search Student\n"

             << " 4. Delete Student\n"

             << " 5. AI Helper\n"

             << " 6. Exit" << endl;

        // choice enter

        cout << "Enter your choice : ";

        cin >> choice;

        // switch case for input

        switch (choice)

        {

        case 1:

            title("STUDENT RECORD SYSTEM");

            cout << "  Number of students : ";

            cin >> Number_Record;

            for (int i = 0; i < Number_Record; i++)

            {

                cout << "\n";

                title("STUDENT " + to_string(i + 1));

                Student temp;

                temp.insert_details(Student_record);

                Student_record.push_back(temp);
                save_data(Student_record);
            }

            break;

        case 2:

            title("STUDENT DISPLAYING");

            for (Student &key : Student_record)

            {

                key.student_info();

                cout << "\n";
            }

            break;

        case 3:

            title("SEARCH & UPDATE STUDENT DETAILS");

            b1.Search_Student(Student_record);

            break;

        case 4:

            title("DELETE STUDENT");

            b1.delete_student(Student_record);

            break;

        case 5:
            b1.AI_Assistant(Student_record);
            break;

        case 6:

            cout << "EXIT" << endl;

            loop = false;

            break;

        default:

            cout << "Invallid Input!!" << endl;

            break;
        }
    }

    save_data(Student_record);

    return 0;
}