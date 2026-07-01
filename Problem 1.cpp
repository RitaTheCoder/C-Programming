#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

class Student {
private:
    string studentID;
    string name;
    string department;
    int semester;
    double marks[5];
    double totalMarks;
    double averageMarks;
    double gpa;
    string letterGrade;

    // Helper to calculate GPA and Grade per course
    void calculateMetrics() {
        totalMarks = 0;
        for (int i = 0; i < 5; i++) {
            totalMarks += marks[i];
        }
        averageMarks = totalMarks / 5.0;

        // Simplified institutional GPA mapping based on average percentage
        if (averageMarks >= 80) { gpa = 4.00; letterGrade = "A+"; }
        else if (averageMarks >= 75) { gpa = 3.75; letterGrade = "A"; }
        else if (averageMarks >= 70) { gpa = 3.50; letterGrade = "A-"; }
        else if (averageMarks >= 65) { gpa = 3.25; letterGrade = "B+"; }
        else if (averageMarks >= 60) { gpa = 3.00; letterGrade = "B"; }
        else if (averageMarks >= 55) { gpa = 2.75; letterGrade = "B-"; }
        else if (averageMarks >= 50) { gpa = 2.50; letterGrade = "C+"; }
        else if (averageMarks >= 45) { gpa = 2.25; letterGrade = "C"; }
        else if (averageMarks >= 40) { gpa = 2.00; letterGrade = "D"; }
        else { gpa = 0.00; letterGrade = "F"; }
    }

public:
    // Default Constructor
    Student() : studentID(""), name(""), department(""), semester(1), totalMarks(0), averageMarks(0), gpa(0), letterGrade("F") {
        for(int i=0; i<5; i++) marks[i] = 0;
    }

    // Function to input data
    void inputData(string id, string n, string dept, int sem, double m[]) {
        studentID = id;
        name = n;
        department = dept;
        semester = sem;
        for (int i = 0; i < 5; i++) {
            marks[i] = m[i];
        }
        calculateMetrics();
    }

    // Getters
    string getStudentID() const { return studentID; }
    string getDepartment() const { return department; }
    double getGPA() const { return gpa; }
    string getName() const { return name; }

    // Display Marksheet
    void displayMarksheet() const {
        cout << "\n=============================================\n";
        cout << "              STUDENT MARKSHEET              \n";
        cout << "=============================================\n";
        cout << "ID: " << studentID << " | Name: " << name << "\n";
        cout << "Dept: " << department << " | Semester: " << semester << "\n";
        cout << "---------------------------------------------\n";
        cout << "Course Marks: ";
        for(int i = 0; i < 5; i++) cout << marks[i] << " ";
        cout << "\n---------------------------------------------\n";
        cout << fixed << setprecision(2);
        cout << "Total Marks:   " << totalMarks << "\n";
        cout << "Average Marks: " << averageMarks << "\n";
        cout << "GPA:           " << gpa << " (" << letterGrade << ")\n";
        cout << "=============================================\n";
    }
};

// Comparator function for sorting descending by GPA
bool compareByGPA(const Student& a, const Student& b) {
    return a.getGPA() > b.getGPA();
}

int main() {
    const int SIZE = 20;
    Student students[SIZE];

    // Hardcoding sample data for 20 students to make testing seamless
    string names[SIZE] = {"Debi", "Shuvra", "Mili", "Romana", "Nuri", "Nahid", "Omor", "Rakib", "Jishan", "Amit",
                          "Simla", "Meherun", "Rekha", "Baby", "Liton", "Utpola", "Popy", "Arnob", "Rita", "Quasha"};
    string depts[SIZE] = {"CSE", "CSE", "EEE", "BBA", "CSE", "EEE", "BBA", "CSE", "EEE", "BBA",
                          "CSE", "CSE", "EEE", "BBA", "CSE", "EEE", "BBA", "CSE", "EEE", "BBA"};

    for (int i = 0; i < SIZE; i++) {
        string id = "25300" + to_string(100 + i);
        double sampleMarks[5] = {60.0 + (i % 5) * 8, 65.0 + (i % 4) * 7, 55.0 + (i % 3) * 12, 70.0 + (i % 2) * 15, 72.0};
        students[i].inputData(id, names[i], depts[i], (i % 8) + 1, sampleMarks);
    }

    cout << "--- Initialized 20 Student Records Successfully ---\n";

    // 1. Sort by GPA (Descending)
    sort(students, students + SIZE, compareByGPA);

    // 2. Display Topper
    cout << "\n>>> TOPPER OF THE INSTITUTE <<<\n";
    students[0].displayMarksheet();

    // 3. Search by Student ID
    string searchID = "25300105";
    cout << "\n>>> Searching for Student ID: " << searchID << " <<<\n";
    bool found = false;
    for (int i = 0; i < SIZE; i++) {
        if (students[i].getStudentID() == searchID) {
            students[i].displayMarksheet();
            found = true;
            break;
        }
    }
    if (!found) cout << "Student Record Not Found.\n";

    // 4. Department-wise Average GPA
    cout << "\n>>> Department-wise Average GPA <<<\n";
    string targetedDepts[] = {"CSE", "EEE", "BBA"};
    for (const string& d : targetedDepts) {
        double totalGpaSum = 0;
        int count = 0;
        for (int i = 0; i < SIZE; i++) {
            if (students[i].getDepartment() == d) {
                totalGpaSum += students[i].getGPA();
                count++;
            }
        }
        if (count > 0) {
            cout << "Department " << d << " Average GPA: " << fixed << setprecision(2) << (totalGpaSum / count) << " (Total Students: " << count << ")\n";
        }
    }

    return 0;
}
