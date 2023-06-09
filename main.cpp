#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class Student {
private:
    string name;
    string marks;

public:
    Student(const string& name, const string& marks) : name(name), marks(marks) {}

    string getName() const {
        return name;
    }

    string getMarks() const {
        return marks;
    }

    void setMarks(const string& newMarks) {
        marks = newMarks;
    }
};

class StudentRecord {
private:
    vector<Student> students;
    string filename;

public:
    StudentRecord(const string& filename) : filename(filename) {
        readFromFile();
    }

    void storeMarks() {
        ofstream file(filename, ios::app);
        if (!file) {
            cout << "Error: Could not open file '" << filename << "'." << endl;
            return;
        }

        cout << "Enter student name (or 'q' to quit): ";
        string name;
        while (getline(cin, name)) {
            if (name == "q")
                break;

            cout << "Enter marks obtained: ";
            string marks;
            getline(cin, marks);

            students.emplace_back(name, marks);

            file << name << "," << marks << endl;

            cout << "Enter student name (or 'q' to quit): ";
        }

        cout << "Data stored successfully." << endl;
        file.close();
    }

    void updateMarks() {
        displayData();

        cout << "Enter the number of the student to update marks: ";
        int studentNum;
        cin >> studentNum;
        cin.ignore();

        if (studentNum < 1 || studentNum > students.size()) {
            cout << "Invalid student number." << endl;
            return;
        }

        cout << "Enter the updated marks: ";
        string newMarks;
        getline(cin, newMarks);

        students[studentNum - 1].setMarks(newMarks);

        writeToFile();

        cout << "Marks updated successfully." << endl;
        cout<<endl;
    }

    void deleteStudent() {
        displayData();

        cout << "Enter the number of the student to delete: ";
        int studentNum;
        cin >> studentNum;
        cin.ignore();

        if (studentNum < 1 || studentNum > students.size()) {
            cout << "Invalid student number." << endl;
            return;
        }

        students.erase(students.begin() + studentNum - 1);

        writeToFile();

        cout << "Student deleted successfully." << endl;
    }

    void displayData() const {
        if (students.empty()) {
            cout << "No data found in the file." << endl;
            return;
        }

        cout << "No.  Name         Marks" << endl;
        cout << "------------------------" << endl;
        for (int i = 0; i < students.size(); ++i) {
            cout << setw(3) << i + 1 << ".  ";
            cout << setw(12) << students[i].getName() << " ";
            cout << students[i].getMarks() << endl;
        }
    }

private:
    void readFromFile() {
        ifstream file(filename);
        if (!file) {
            cout << "Error: Could not open file '" << filename << "'." << endl;
            return;
        }

        string name, marks;
        while (getline(file, name, ',')) {
            getline(file, marks);
            students.emplace_back(name, marks);
        }
        file.close();
    }

    void writeToFile() {
        ofstream file(filename);
        if (!file) {
            cout << "Error: Could not open file '" << filename << "'." << endl;
            return;
        }

        for (const auto& student : students) {
            file << student.getName() << "," << student.getMarks() << endl;
        }
        file.close();
    }
};

int main() {
    string filename = "marks.txt";
    StudentRecord record(filename);

    while (true) {
        cout << "1. Store marks" << endl;
        cout << "2. Update marks" << endl;
        cout << "3. Display marks" << endl;
        cout << "4. Delete student" << endl;
        cout << "5. Quit" << endl;

        cout << "Enter your choice: ";
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            record.storeMarks();
        } else if (choice == "2") {
            record.updateMarks();
        } else if (choice == "3") {
            record.displayData();
        } else if (choice == "4") {
            record.deleteStudent();
        } else if (choice == "5") {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    cout << "Program exited." << endl;

    return 0;
}
