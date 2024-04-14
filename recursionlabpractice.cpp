#include <string>
#include <vector>
#include <iostream>

using namespace std;

enum Gender {
    MALE,
    FEMALE
};


class Student {

private:
    long id;            // Unique ID
    string name;        // Name of student
    Gender gender;      // Gender of student
    string courseCode;  // Course code (CIIC or ICOM)
    double gpa;         // GPA of student

public:
    Student(long id, const string &name, Gender gender, double gpa){
        this->id = id;
        this->name = name;
        this->gender = gender;
        this->courseCode = "";
        this->gpa = gpa;
    }

    Student(long id, const string &name, Gender gender, string courseCode, double gpa){
        this->id = id;
        this->name = name;
        this->gender = gender;
        this->courseCode = courseCode;
        this->gpa = gpa;
    }

    Student(){}

    static string toString(Student& s){
        string genderLetter = (s.gender  == MALE ? "M" : "F");
        return string("{" + to_string(s.id) + "," + s.name + "," + genderLetter + "," + to_string(s.gpa) + "}");
    }

    static string toString(vector<Student>& v){
        string result = "{";
        for (Student s : v) {
            result += toString(s) + ",";
        }
        result += "}";
        return result;
    }

    static string toString(vector<long>& v){
        string result = "{";
        for (long id : v) {
            result += to_string(id) + ",";
        }
        result += "}";
        return result;
    }

    // Getters
    long getID() const {return id;}
    string getName() const {return name;}
    Gender getGender() const {return gender;}
    double getGPA() const {return gpa;}
    string getCourseCode() const {return courseCode;}

    //Setters
    void setName(string name){this->name = name;}
    void setGender(Gender gender){this->gender = gender;}
    void setGPA(double gpa){this->gpa = gpa;}
    void setCourseCode(string code){this->courseCode = code;}

    // EXERCISES
    static double maxStudentGPA(vector<Student>& v);
    static double maxStudentGPAHelper(vector<Student>& v,int index,int max);
    static double minStudentGPA(vector<Student>& v);
    static double minStudentGPAHelper(vector<Student>& v,int min,int index);
    static double averageGPA(vector<Student> &v, int N);
    static double averageHelper(vector<Student>& v, int N, int index, double total);
    static vector<long> countStudents(vector<Student>& v, string code);
    static vector<long> countStudentsHelper(vector<Student>& v,string code, int index,vector<long> result);
    static void removeByID(vector<Student> &v, long ID);
    static void removeByIDHelper(vector<Student> &v, long ID,int index);
    static void updateStudent(vector<Student> &v, const Student &s);
    static void updateStudentHelper(vector<Student> &v, const Student &s,int index,bool found);
    static vector<Student> findStudents(vector<Student>& v, float gpa);
    static vector<Student> findStudentsHelper(vector<Student>& v, float gpa,int index,vector<Student> result);
    static vector<Student> honorIdentifier(vector<Student>& v1, vector<Student>& v2);
    static vector<Student> honorIdentifierHelper(vector<Student>& v1, vector<Student>& v2, int index,vector<Student> result);
   
};

/*
* EXERCISE: #1A
*
* IMPLEMENT USING AN ENHANCED FOR LOOP (ForEach).
*
* Returns the highest GPA value possessed by any Student in the given list.
*  
*/
double Student::maxStudentGPAHelper(vector<Student>&v,int index, int max){
    if(index >= v.size()) return max;
    if(v[index].getGPA() > max) max = v[index].getGPA();
    return maxStudentGPAHelper(v,++index,max);
}
double Student::maxStudentGPA(vector<Student>& v){
    //YOUR CODE HERE
    if(v.empty()) return 0;
    return maxStudentGPAHelper(v,0,0); //DUMMY RETURN
}

/*
* EXERCISE: #1B
*
* IMPLEMENT USING A REGULAR FOR LOOP.
*
* Returns the lowest GPA value possessed by any Student in the given list.
*
*/
double Student::minStudentGPAHelper(vector<Student>& v,int min,int index){
    if(index >= v.size()) return min;
    if(v[index].getGPA() < min) min = v[index].getGPA();
    return minStudentGPAHelper(v,min,++index);
}
double Student::minStudentGPA(vector<Student>& v){
    if(v.empty()) return  0;
    return minStudentGPAHelper(v,v[0].getGPA(),0);
}

/* 
* Exercise #1C
*
* IMPLEMENT USING A WHILE LOOP
*
* For the first N students, calculate the average gpa
* 
* Formula: average = sum / N
*    Assume N is greater than 0
*/
double Student::averageHelper(vector<Student>& v, int N, int index,double total){
    if(index >= N) return total/N;
    total += v[index].getGPA();
    return averageHelper(v,N,++index,total);
}
double Student::averageGPA(vector<Student> &v, int N){
    if(v.empty()) return 0;
    return averageHelper(v,N,0,0);
}

/**
 * 
* EXERCISE #2
* 
* IMPLEMENT IT USING AN ENHANCED FOR LOOP (ForEach)
*
* Given a course code, you must return a vector that contains 
* only the unique ID of the Students that have that particular course code.
*/

vector<long> Student::countStudentsHelper(vector<Student>& v,string code, int index,vector<long> result){
    if(v.empty() || index >= v.size()) return result;
    if(v[index].getCourseCode() == code) result.push_back(v[index].getID());
    return countStudentsHelper(v,code,++index,result);
}
vector<long> Student::countStudents(vector<Student>& v, string code){
    vector<long> result;
    return countStudentsHelper(v,code,0,result);
}

/*
* EXERCISE #3
* 
* IMPLEMENT USING A DO...WHILE LOOP
* 
* Return a vector that contains all the Students that have a GPA greater
* or equal to the GPA passed as the parameter
* 
* Assume the list contains at least one element
*/
vector<Student> Student::findStudentsHelper(vector<Student>& v, float gpa,int index,vector<Student> result){
    if(index >= v.size()) return result;
    if(v[index].getGPA() >= gpa) result.push_back(v[index]);
    return findStudentsHelper(v,gpa,++index,result);
}
vector<Student> Student::findStudents(vector<Student>& v, float gpa){
    vector<Student> result;
    if(v.empty()) return result;
    return findStudentsHelper(v,gpa,0,result);
}

/*
* EXERCISE: #4
*
* IMPLEMENT WITH ANY LOOP
*
* Removes the first occurrence of the specified Student ID,
* if it is present. If not present, then list is unchanged.
* HINT: Verify the methods erase() and begin() of the vector
*/
void Student::removeByIDHelper(vector<Student> &v, long ID,int index){
    if(index >= v.size()) return;
    if(v[index].getID() == ID) {
        v.erase(v.begin() + index);
        return;
    }
    return removeByIDHelper(v,ID,++index);
}
void Student::removeByID(vector<Student> &v, long ID){
    return removeByIDHelper(v,ID,0);
}

/*
* EXERCISE #5
* 
* DO NOT USE WHILE LOOPS
*
* Find the Student record that matches the given Student
* and update its data. If the Student is not present, add it to the list.
* 
* Remember that each Student has an unique identifier
*/
void Student::updateStudentHelper(vector<Student> &v, const Student &s,int index,bool found){
    if(index >= v.size()) return;
    if(!found) {
        v.push_back(s);
        return;
    }
    if(v[index].getID()== s.getID()){
        found = true;
        v[index].setGender(s.getGender());
        v[index].setGPA(s.getGPA());
        v[index].setName(s.getName());
        v[index].setCourseCode(s.getCourseCode());
        return;
    }
    return updateStudentHelper(v,s, ++index, found);
}
void Student::updateStudent(vector<Student> &v, const Student &s){
    if(v.empty()) return;
    return updateStudentHelper(v,s,0,false);
}

/*
* BONUS EXERCISE
* 
* USE ONLY A SINGLE LOOP, SOLUTIONS WITH MULTIPLE LOOPS WILL
* NOT BE AWARDED POINTS
*
* Find the Students in both vectors that qualify to be a part of the honor roll
* making use of only a single loop. Students may only qualify to be part 
* of the honor roll if they have a GPA of 3.5 or higher.
*
* You may assume that both vectors have equal length.
* 
*/
vector<Student> Student::honorIdentifierHelper(vector<Student>& v1, vector<Student>& v2, int index,vector<Student> result){
    if(index >= v1.size() && index >= v2.size()) return result;
    if(index < v1.size()){
        if(v1[index].getGPA() >= 3.5) result.push_back(v1[index]);
    }
    if(index < v2.size()){
        if(v2[index].getGPA() >= 3.5) result.push_back(v2[index]);
    }
    return honorIdentifierHelper(v1,v2,++index,result);
}
vector<Student> Student::honorIdentifier(vector<Student>& v1, vector<Student>& v2){
    vector<Student> result;
    if(v1.empty() && v2.empty()) return result;
    return honorIdentifierHelper(v1,v2,0,result);
}

// TEST CASES
int main() {

    Student s1(0, "Bienve", MALE, 3.0);
    Student s2(1, "Jose Juan", MALE, 2.8);
    Student s3(2, "Ana", FEMALE, 3.5);

    Student s4(3, "Ariel", FEMALE,"CIIC", 4.0);
    Student s5(4, "Mulan", FEMALE, "ICOM", 3.56);
    Student s6(5, "Aladdin", MALE, "CIIC", 3.1);

    vector<Student> testVector1{s1, s2, s3};
    vector<Student> testVector2{s4, s5, s6};

    cout << "---------TESTS---------" << endl;

    cout << "\n----Exercise #1A----" << endl;
    cout << "Maximum GPA: " << Student::maxStudentGPA(testVector1) << endl;

    cout << "\n----Exercise #1B----" << endl;
    cout << "Minimum GPA: " << Student::minStudentGPA(testVector1) << endl;

    cout << "\n----Exercise #1C----" << endl;
    cout << "Average GPA of N Students: " << Student::averageGPA(testVector1, 2) << endl;

    cout << "\n----Exercise #2----" << endl;
    vector<long> result =  Student::countStudents(testVector2, "ICOM");
    cout << "ID of Students with code: " << Student::toString(result) << endl;

    cout << "\n----Exercise #3----" << endl;
    vector<Student> temp = Student::findStudents(testVector2, 3.50);
    cout << "Students with a high GPA: " << Student::toString(temp) << endl;

    cout << "\n----Exercise #4----" << endl;
    cout << "Before removing ID: " << Student::toString(testVector2) << endl;
    Student::removeByID(testVector2, 5l);
    cout << "After removing: " << Student::toString(testVector2) << endl;

    cout << "\n----Exercise #5----" << endl;
    Student temp1(6, "Mariela", FEMALE, 2.3);
    cout << "Before Updating: " << Student::toString(testVector1) << endl;
    Student::updateStudent(testVector1, temp1);
    cout << "After Updating: " << Student::toString(testVector1) << endl;

    cout << "\n-------Last Exercise-------" << endl;
    vector<Student> temp2 = Student::honorIdentifier(testVector1, testVector2);
    cout << "Students in honor roll: " << Student::toString(temp2) << endl;
    
}
//Christian Jose Berberena