/*
Design and implement a University Course Registration System in C++ using
Object-Oriented Programming Concepts. The system should allow students to be
added, courses to be created, and student registrations to courses to be
managed. It must prevent duplicate course registrations and enforce limits on
the number of students and enrollments.

- Add new student with first and last name, DOB in MM-DD-YYYY format and unique
student ID
- Add a new course with a unique course code, title and instructor name
- Register a student to a course by student ID and course code
- The program should list all students (max 10) and all courses (max 5) based on
the menu option
- Use Input validation for date format and numeric entries
*/

#include <iostream>
#include <stdexcept>
#include <string>

#define MAX_STUDENTS 10
#define MAX_COURSES 5
#define MAX_ENROLLMENT 5

using namespace std;

class Course {
private:
  string code, title, instructor, ids[MAX_ENROLLMENT];
  int enrollment;

public:
  Course() {}
  Course(string code, string title, string instructor)
    : code(code), title(title), instructor(instructor), enrollment(0) {}

  // getter methods
  string getCode() { return code; }
  string getTitle() { return title; }
  string getInstructor() { return instructor; }
  int getEnrollment() { return enrollment; }

  // Register student - checks and update enrollment
  bool registerStudent(string id) {
    if (enrollment == MAX_ENROLLMENT) // check if course is full
      return false;

    for (int i = 0; i < MAX_ENROLLMENT; i++) {
      // check if student already registered
      if (ids[i].compare(id) == 0)
        break;

      // look for empty space to add student
      if (ids[i].empty()) {
        ids[i] = id;
        // update enrollment
        enrollment++;
        return true; // successful
      }
    }
    return false; // unsucessful
  }

  // Remove student - updates enrollment
  bool removeStudent(string id) {
    for (int i = 0; i < MAX_ENROLLMENT; i++) {
      if (ids[i].compare(id) == 0) {
        // remove student
        for (int j = i; j < MAX_ENROLLMENT - 1; j++) {
          ids[j] = ids[j + 1];
        }
        // edge case - clear last index
        ids[MAX_ENROLLMENT - 1] = "";
        // update enrollment
        enrollment--;
        return true; // successful
      }
    }
    return false; // unsuccessful
  }
};

class Student {
private:
  string fn, ln, dob, id;
  Course courses[MAX_COURSES];

public:
  Student () {}
  Student (string fn, string ln, string dob, string id)
    : fn(fn), ln(ln), dob(dob), id(id) {}

  // getter methods
  string getFirstName() { return fn; }
  string getLastName() { return ln; }
  string getDOB() { return dob; }
  string getID() { return id; }
  Course *getCourses() { return courses; }

  // setter methods
  void setFirstName(string fn) { this->fn = fn; }
  void setLastName(string ln) { this->ln = ln; }
  void setDOB(string dob) { this->dob = dob; }
  void setID(string id) { this->id = id; }
  void setCourses(Course *courses) {
    for (int i = 0; i < MAX_COURSES; i++) {
      this->courses[i] = *(courses + i);
    }
  }

  // Register Course Function
  bool registerCourse(Course course) {
    for (int i = 0; i < MAX_COURSES; i++) {
      if (courses[i].getCode() == course.getCode())
        break;
      if (courses[i].getCode().empty()) {
        courses[i] = course;
        return true;
      }
    }
    return false;
  }

  // List Courses Function
  void listCourses() {
    cout << "Courses Enrolled: ";
    for (int i = 0; i < MAX_COURSES; i++) {
      if (courses[i].getTitle().empty()) {
        cout << "\n";
        return;
      }
      cout << "\n" << courses[i].getCode() << " - " << courses[i].getTitle();
    }
  }
};

class Menu {
private:
  // Checks date format
  static bool validDate(string str) {
    if (str.length() != 10) // Check if length is 10
      return false;
    if (str.substr(2, 1) != "-" || str.substr(5, 1) != "-") // Check for dashes
      return false;
    // Check dates
    string month = str.substr(0, 2), day = str.substr(3, 2), year = str.substr(6);
    int m, d, y;
    try {
      m = stoi(month);
      d = stoi(day);
      y = stoi(year);
    } catch (invalid_argument &e) {
      return false;
    }

    return true;
  }

  // Checks if a student exists and returns the index
  static int studentFound(Student *students, string id) {
    for (int i = 0; i < MAX_STUDENTS; i++) {
      if ((students + i)->getID() == id)
        return i;
    }
    return -1;
  }

  // Checks if a course exists and returns the index
  static int courseFound(Course *courses, string code) {
    for (int i = 0; i < MAX_COURSES; i++) {
      if ((courses + i)->getCode() == code)
        return i;
    }
    return -1;
  }

public:
  // Menu Function
  static string menu() {
    string choice;
    cout << "--- University Course Registration System ---\n1. Add Student\n2. "
            "Add Course\n3. Register Student to Course\n4. Delete Student\n5. "
            "Show Student's Courses\n0. Quit\nEnter choice: ";
    getline(cin, choice);
    return choice;
  }

  // Choice 1 Function - Add Student
  static void choice1(Student *students) {
    // Check if max students reached and find empty space in student array
    int index = -1;
    for (int i = 0; i < MAX_STUDENTS; i++) {
      if ((students + i)->getFirstName().empty()) {
        index = i;
        break;
      }
    }

    if (index == -1) {
      cout << "Error: Max number of students reached.\n";
      return;
    }

    string fn, ln, dob, id;

    // Get first name
    while (1) {
      cout << "First Name: ";
      getline(cin, fn);
      if (!fn.empty())
        break;
      cout << "Error: First name can not be empty.\n";
    }

    // Get last name
    while (1) {
      cout << "Last Name: ";
      getline(cin, ln);
      ;
      if (!ln.empty())
        break;
      cout << "Error: Last name can not be empty.\n";
    }

    // Get dob
    while (1) {
      cout << "DOB (MM-DD-YYYY): ";
      getline(cin, dob);
      if (validDate(dob))
        break;
      cout << "Error: Invalid date format.\n";
    }

    // Get student id
    while (id.empty()) {
      cout << "ID: ";
      getline(cin, id);
      // Check that student ID is unique
      for (int i = 0; i < MAX_STUDENTS; i++) {
        if ((students + i)->getID() == id) {
          cout << "Error: Student ID must be unique.\n";
          id.clear();
        }
      }
    }

    // Add new student
    *(students + index) = Student(fn, ln, dob, id);
  }

  // Choice 2 Function - Add Course
  static void choice2(Course *courses) {
    // Check if max courses reached and find empty space in courses array
    int index = -1;
    for (int i = 0; i < MAX_COURSES; i++) {
      if ((courses + i)->getCode().empty()) {
        index = i;
        break;
      }
    }

    if (index == -1) {
      cout << "Error: Max number of courses reached.\n";
      return;
    }

    string code, title, instructor;

    // get course code
    while (code.empty()) {
      cout << "Course Code: ";
      getline(cin, code);
      // Check that course code is unique
      for (int i = 0; i < MAX_COURSES; i++) {
        if ((courses + i)->getCode() == code) {
          cout << "Error: Coures code must be unique.\n";
          code.clear();
        }
      }
    }

    // get course title
    while (1) {
      cout << "Course Title: ";
      getline(cin, title);
      if (!title.empty())
        break;
      cout << "Error: Course title can not be empty.\n";
    }

    // get instructor name
    while (1) {
      cout << "Instructor Name: ";
      getline(cin, instructor);
      if (!instructor.empty())
        break;
      cout << "Error: Instructor can not be empty.\n";
    }

    // add new course
    *(courses + index) = Course(code, title, instructor);
  }

  // Choice 3 Function - Register Student to Course
  static void choice3(Student *students, Course *courses) {
    string id, code;
    int sindex, cindex;

    // get student id
    while (1) {
      cout << "Enter Student ID: ";
      getline(cin, id);
      sindex = studentFound(students, id);
      if (sindex != -1)
        break;
      cout << "Error: Student not found.\n";
    }

    // get course code
    while (1) {
      cout << "Enter Course Code: ";
      getline(cin, code);
      cindex = courseFound(courses, code);
      if (cindex != -1)
        break;
      cout << "Error: Course not found.\n";
    }

    // register student
    if ((students + sindex)->registerCourse(*(courses + cindex)) && (courses + cindex)->registerStudent(id)) {
      cout << "Registered.\n";
    } else {
      cout << "Invalid ID, student already registered or course full.\n";
    }
  }

  // Choice 4 Function - Delete Student
  static void choice4(Student *students, Course *courses) {
    string id;
    int index;

    // get student id
    while (1) {
      cout << "Enter Student ID: ";
      getline(cin, id);
      index = studentFound(students, id);
      if (index != -1)
        break;
      cout << "Error: Student not found.\n";
      return;
    }

    // remove student from array of students
    for (int i = index; i < MAX_STUDENTS - 1; i++) {
      (students + i)->setFirstName((students + i + 1)->getFirstName());
      (students + i)->setLastName((students + i + 1)->getLastName());
      (students + i)->setDOB((students + i + 1)->getDOB());
      (students + i)->setID((students + i + 1)->getID());
      (students + i)->setCourses((students + i + 1)->getCourses());
    }
    // edge case - clear last index
    (students + MAX_STUDENTS - 1)->setFirstName("");
    (students + MAX_STUDENTS - 1)->setLastName("");
    (students + MAX_STUDENTS - 1)->setDOB("");
    (students + MAX_STUDENTS - 1)->setID("");
    (students + MAX_STUDENTS - 1)->setCourses(new Course());

    // remove student from all courses
    for (int i = 0; i < MAX_COURSES; i++) {
      (courses + i)->removeStudent(id);
    }
  }

  // Choice 5 Function - Show Student's Courses
  static void choice5(Student *students) {
    string id;
    int index;

    // get student id
    while (1) {
      cout << "Enter Student ID: ";
      getline(cin, id);
      index = studentFound(students, id);
      if (index != -1)
        break;
      cout << "Error: Student not found.\n";
      return;
    }

    // list all courses
    (students + index)->listCourses();
  }
};

int main() {
  // Ptr arrays to store students and courese
  Student *students = new Student[MAX_STUDENTS];
  Course *courses = new Course[MAX_COURSES];
  // String to store user input
  string choice;

  while (1) {
    choice = Menu::menu();
    if (choice == "0") { // Quit
      break;
    } else if (choice == "1") { // Add student
      Menu::choice1(students);
    } else if (choice == "2") { // Add course
      Menu::choice2(courses);
    } else if (choice == "3") { // Register student to course
      Menu::choice3(students, courses);
    } else if (choice == "4") { // Delete student
      Menu::choice4(students, courses);
    } else if (choice == "5") { // Show student's courses
      Menu::choice5(students);
    } else { // Invalid Input
      cout << "Error: Invalid input, enter a number from 0-5";
    }
    cout << "\n";
  }

  cout << "Thank you for using the University Course Registration System!"
       << endl;
  return 0;
}
