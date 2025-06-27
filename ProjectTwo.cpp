
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Define the Course structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Global map to hold all courses by their courseNumber
map<string, Course> courseCatalog;

// Function to convert input to uppercase for consistency
string toUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Load data from file into the courseCatalog map
void loadDataStructure(const string& filename) {
    courseCatalog.clear();  // Clear existing data

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 2) {
            Course course;
            course.courseNumber = toUpper(tokens[0]);
            course.courseTitle = tokens[1];

            for (size_t i = 2; i < tokens.size(); ++i) {
                course.prerequisites.push_back(toUpper(tokens[i]));
            }

            courseCatalog[course.courseNumber] = course;
        }
    }

    file.close();
    cout << "Course data successfully loaded." << endl;
}

// Print the sorted course list
void printCourseList() {
    if (courseCatalog.empty()) {
        cout << "Error: Course data not loaded. Please load the file first (Option 1)." << endl;
        return;
    }

    vector<string> sortedCourses;
    for (const auto& pair : courseCatalog) {
        sortedCourses.push_back(pair.first);
    }

    sort(sortedCourses.begin(), sortedCourses.end());

    for (const string& courseNum : sortedCourses) {
        const Course& course = courseCatalog[courseNum];
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

// Print course info and its prerequisites
void printCourseInfo(const string& inputCourseNum) {
    string courseNum = toUpper(inputCourseNum);

    if (courseCatalog.find(courseNum) == courseCatalog.end()) {
        cout << "Course " << inputCourseNum << " not found." << endl;
        return;
    }

    Course course = courseCatalog[courseNum];
    cout << course.courseNumber << ", " << course.courseTitle << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    } else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

// Menu display
void displayMenu() {
    cout << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit." << endl;
    cout << endl;
    cout << "What would you like to do? ";
}

int main() {
    int choice;
    string filename;
    string userInput;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter file name to load: ";
                cin >> filename;
                loadDataStructure(filename);
                break;
            case 2:
                printCourseList();
                break;
            case 3:
                cout << "What course do you want to know about? ";
                cin >> userInput;
                printCourseInfo(userInput);
                break;
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                return 0;
            default:
                cout << choice << " is not a valid option." << endl;
                break;
        }
    }
}
