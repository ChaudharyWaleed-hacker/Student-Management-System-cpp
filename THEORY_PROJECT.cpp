

// Student Management System




#include<iostream>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<string>

using namespace std;

// Maximum limits
const int max_subjects = 8;
const int max_students = 54;

// Structure to store student information
struct Student {
	string id;
	string name;
	float marks[max_subjects];
	float gpa;
	char grade;
};

//------------------------Funtion Prototypes-------------------------

void showdata(Student s[], int students, int subjects);
void loadfile(Student s[], int& students, int& subjects);
void calculate_gpa(Student s[], int students, int subj);
void assign_grades(Student s[], int students);
void rank_students(Student s[], int students);
void topper_list(Student s[], int students);
void avg_of_subject(Student s[], int students, int subjects);
void pass_to_fail_ratio(Student s[], int students);
void search_student(Student s[], int students, int subjects);
void update_info(Student s[], int students, int subjects);
void show_general_report(Student s[], int students, int subjects);
void save_general_report(Student s[], int students, int subjects);
void show_student_wise_report(Student s[], int students, int subjects);
void save_student_wise_report(Student s[], int students, int subjects);
void refresh(Student s[], int students, int subjects);

//---------------------Main Function---------------------------------
int main()
{
	int students = 0, subjects = 0;
	int choice;

	Student std[max_students];

	// Load data and prepare initial results
	loadfile(std, students, subjects);
	calculate_gpa(std, students, subjects);
	assign_grades(std, students);
	rank_students(std, students);

	do {
		cout << endl << endl;
		//Clearing the stuff on the terminal to display clean menu
		system("cls");   // clear old output

		// ===== HEADER (always visible) =====

		cout << "				=========================================================================\n";
		cout << "				||                         STUDENT MANAGEMENT SYSTEM                   ||\n";
		cout << "				=========================================================================";



		cout << "\n--------------------MENU-----------------------------------------";
		cout << "\n| " << left << setw(62) << "Enter 1  : Access Data from File" << "|";
		cout << "\n| " << left << setw(62) << "Enter 2  : Get Topper List" << "|";
		cout << "\n| " << left << setw(62) << "Enter 3  : Search Student Data" << "|";
		cout << "\n| " << left << setw(62) << "Enter 4  : Update Student Data" << "|";
		cout << "\n| " << left << setw(62) << "Enter 5  : Pass to Fail Ratio" << "|";
		cout << "\n| " << left << setw(62) << "Enter 6  : Subject Wise Average" << "|";
		cout << "\n| " << left << setw(62) << "Enter 7  : Show Student-wise Report" << "|";
		cout << "\n| " << left << setw(62) << "Enter 8  : Save Student-wise Report to File" << "|";
		cout << "\n| " << left << setw(62) << "Enter 9  : Show Class General Report" << "|";
		cout << "\n| " << left << setw(62) << "Enter 10 : Save Class General Report to File" << "|";
		cout << "\n| " << left << setw(62) << "Enter 0  : Exit Program" << "|";
		cout << "\n-----------------------------------------------------------------\n";
		cout << "Enter your choice: ";
		cin >> choice;

		while (choice < 0 || choice > 10)
		{
			cout << "Invalid! Enter again: ";
			cin >> choice;
		}

		switch (choice)
		{
		case 1:
			showdata(std, students, subjects);
			break;
		case 2:
			topper_list(std, students);
			break;
		case 3:
			search_student(std, students, subjects);
			break;
		case 4:
			update_info(std, students, subjects);
			refresh(std, students, subjects);
			break;
		case 5:
			pass_to_fail_ratio(std, students);
			break;
		case 6:
			avg_of_subject(std, students, subjects);
			break;
		case 7:
			show_student_wise_report(std, students, subjects);
			break;
		case 8:
			save_student_wise_report(std, students, subjects);
			break;

		case 9:
			show_general_report(std, students, subjects);
			break;
		case 10:
			save_general_report(std, students, subjects);
			break;
		case 0:
			cout << "\nExiting Program...\n";
			break;

		}
		// ===== PAUSE =====
		if (choice != 0) {
			cout << "\nPress Enter to continue...";
			cin.ignore();
			cin.get();
		}
	} while (choice != 0);
}

//------------------------Function Intilization-----------------------

// Reads and displays student data directly from file
void showdata(Student s[], int students, int subjects)
{
	cout << "\n---------------------Student Data----------------";
	ifstream fin("students.txt");
	string word;
	fin >> word;
	cout << "\nTotal Students : " << word;
	fin >> word;
	cout << "\nTotal subjects : " << word;
	cout << "\n------------------------------------------\n";
	for (int i = 0; i < students; i++)
	{
		fin >> word;
		cout << "\nID : " << word;
		fin.ignore();
		getline(fin, word);
		cout << "\nNAME : " << word;
		cout << "\nMARKS : ";
		for (int j = 0; j < subjects; j++)
		{
			fin >> word;
			cout << word << " ";
		}
		cout << "\n------------------------------------------\n";

	}


}

// Loads student data from file using pass by reference
void loadfile(Student s[], int& students, int& subjects)
{
	ifstream fin("students.txt");
	if (fin.is_open())
	{
		fin >> students >> subjects;

		if (students > max_students || subjects > max_subjects)
		{
			cout << "Data Exceeds Maximum limit.";
			exit(0);

		}
		for (int i = 0; i < students; i++)
		{
			fin >> s[i].id;
			fin.ignore();
			getline(fin, s[i].name);
			for (int j = 0; j < subjects; j++)
			{
				fin >> s[i].marks[j];
			}
		}
		fin.close();

	}
	else
	{
		cout << "No existing file found !";
		exit(0);
	}
}
// Calculates GPA for each student
void calculate_gpa(Student s[], int students, int subj)
{

	for (int i = 0; i < students; i++)
	{
		float sum = 0.0;
		for (int j = 0; j < subj; j++)
			sum += s[i].marks[j];

		s[i].gpa = ((sum / (subj * 100.0)) * 4.0);
	}
}

// Assigns grade based on GPA
void assign_grades(Student s[], int students)
{
	for (int i = 0; i < students; i++)
	{
		if (s[i].gpa >= 3.5)
			s[i].grade = 'A';
		else if (s[i].gpa >= 3.0)
			s[i].grade = 'B';
		else if (s[i].gpa >= 2.5)
			s[i].grade = 'C';
		else if (s[i].gpa >= 2.0)
			s[i].grade = 'D';
		else
			s[i].grade = 'F';
	}
}


// Sorts students by GPA
void rank_students(Student s[], int students)
{
	for (int i = 0; i < students - 1; i++)
	{
		for (int j = i + 1; j < students; j++)
		{
			if (s[j].gpa > s[i].gpa)
			{
				Student temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
		}
	}
}
// Displays top 3 students
void topper_list(Student s[], int students)
{
	cout << "\n\n----------------------TOPPER LIST------------------------";
	for (int i = 0; i < students && i < 3; i++)
	{
		cout << "\nNAME : " << left << setw(20) << s[i].name << right << setw(5) << "\tGPA: " << right << setw(5) << s[i].gpa << " .";
	}
	cout << endl;
}

// Calculates average marks of each subject
void avg_of_subject(Student s[], int students, int subjects)
{
	for (int j = 0; j < subjects; j++)
	{
		float sum = 0.0;
		for (int i = 0; i < students; i++)
		{
			sum += s[i].marks[j];
		}
		cout << "\nThe Average of Subject " << j + 1 << " is =" << sum / students;

	}

}

// Calculates pass and fail count
void pass_to_fail_ratio(Student s[], int students)
{
	int pass = 0, fail = 0;
	for (int i = 0; i < students; i++)
	{
		if (s[i].grade != 'F')
			pass++;

		else
			fail++;
	}
	cout << "\n\n<<<<<<<<<<<<<<<<<< Pass to Fail Ratio >>>>>>>>>>>>>>>>>>>>>>>>>>";
	cout << "\nPASS : " << pass << "\tFAIL : " << fail;

}

// Searches a student by ID
void search_student(Student s[], int students, int subjects)
{
	string ID;
	cout << "\n---------------SEARCHING STUDENT INFO------------------------";
	cout << "\nEnter the id of student to get data: ";

	while (cin >> ID)
	{
		for (int i = 0; i < students; i++)
		{
			if (s[i].id == ID)
			{
				cout << "\nNAME: " << s[i].name << "\t ID : " << s[i].id << "\tMARKS: ";
				for (int j = 0; j < subjects; j++)
				{
					cout << s[i].marks[j] << " ";
				}
				return;
			}
		}
		cout << "\nStudent Not Found!";
		cout << "\nAgain! Enter ID: ";
	}

	cout << "\n--------------------------------------------------------------";
}


// Updates student name and marks
void update_info(Student s[], int students, int subjects)
{
	string id;
	cout << "\nEnter the id for whom you want to update data: ";
	while (cin >> id)
	{

		for (int i = 0; i < students; i++)
		{
			if (s[i].id == id)
			{
				string  name;
				cout << "\nEnter new name : ";
				cin.ignore();
				getline(cin, name);
				s[i].name = name;
				cout << "\nEnter new marks (Seprated by space) : ";
				for (int j = 0; j < subjects; j++)
				{
					cin >> s[i].marks[j];
				}

				ofstream out("students.txt");
				out << students << " " << subjects << endl;
				for (int j = 0; j < students; j++)
				{
					out << s[j].id << "\n";
					out << s[j].name << endl;
					for (int k = 0; k < subjects; k++)
					{
						out << s[j].marks[k] << " ";
					}
					out << endl;


				}
				cout << "\n\tData Updated Sucessfully!";

				return;
			}
		}
		cout << "\nStudent Not Found!";
		cout << "\nAgain! Enter ID : ";

	}
}
//Saves complete student-wise report into a file
void save_student_wise_report(Student s[], int students, int subjects)
{
	string word;
	ofstream out("Report.txt");
	out << "\n====================================================================\n";
	out << "\t\tSTUDENT WISE REPORT";
	out << "\n====================================================================\n\n";
	// Check if file is opened successfully
	if (!out.is_open())
	{
		cout << "Report file could not be created  !";
		exit(0);
	}
	for (int i = 0; i < students; i++)
	{
		out << "\nID : " << s[i].id;
		out << "\nNAME : " << s[i].name;
		out << "\nMARKS : ";
		for (int j = 0; j < subjects; j++)
		{
			out << s[i].marks[j] << " ";

		}
		out << "\nGPA : " << s[i].gpa;
		out << "\nGRADE : " << s[i].grade;
		out << "\n        --------------------           ";
	}
	// Close file
	out.close();

	cout << "\n\tData Uploaded Sucessfully!";
}

//Displays student-wise report on screen
void show_student_wise_report(Student s[], int students, int subjects)
{
	cout << "\n===========================================================================\n";
	cout << "\t\tSTUDENT WISE REPORT";
	cout << "\n===========================================================================\n\n";
	for (int i = 0; i < students; i++)
	{
		cout << "\nID : " << s[i].id;
		cout << "\nNAME : " << s[i].name;
		cout << "\nMARKS : ";
		for (int j = 0; j < subjects; j++)
		{
			cout << s[i].marks[j] << " ";

		}
		cout << "\nGPA : " << s[i].gpa;
		cout << "\nGRADE : " << s[i].grade;
		cout << "\n        --------------------           ";
	}

	cout << "\n============================================================================\n";

}
// Saves class performance report into a file
void save_general_report(Student s[], int students, int subjects)
{
	ofstream out("General_report.txt");
	out << "===========================================================================\n";
	out << "\t\tCLASS PERFOMANCE REPORT";
	out << "\n===========================================================================\n\n";
	out << "TOPPER LIST(Based on Gpa)\n";
	out << "-----------------------------------------------------\n";
	for (int i = 0; i < students && i < 3; i++)
	{
		out << i + 1 << ". " << left << s[i].name << setw(10) << "\tGPA :" << s[i].gpa << "\tGRADE : " << s[i].grade;
		out << endl;
	}
	out << "\n-----------------------------------------------------\n";
	out << "\n\nSUBJECT WISE AVERAGES";
	out << "\n-----------------------------------------------------\n";
	for (int j = 0; j < subjects; j++)
	{
		float sum = 0.0;
		for (int i = 0; i < students; i++)
		{
			sum += s[i].marks[j];
		}
		out << "\nThe Average of Subject " << j + 1 << " is =" << sum / students;

	}
	out << "\n-----------------------------------------------------\n";
	out << "\nPASS / FAIL SUMMARY";
	out << "\n-----------------------------------------------------\n";
	int pass = 0, fail = 0;
	for (int i = 0; i < students; i++)
	{
		if (s[i].grade != 'F')
			pass++;

		else
			fail++;
	}
	out << "Total Students : " << students;
	out << "\nPASS : " << pass << "\nFAIL : " << fail;
	out << "\nPass Percentage : " << (float(pass) / students) * 100 << " %";
	out << "\n============================================================================\n";
	out.close();
	cout << "\n\tData Uploaded Sucessfully!";
}
// Displays class performance report on screen
void show_general_report(Student s[], int students, int subjects)
{
	cout << "\n===========================================================================\n";
	cout << "\t\tCLASS PERFOMANCE REPORT";
	cout << "\n===========================================================================\n\n";
	cout << "TOPPER LIST(Based on Gpa)\n";
	cout << "-----------------------------------------------------\n";
	for (int i = 0; i < students && i < 3; i++)
	{
		cout << i + 1 << ". " << left << s[i].name << setw(10) << "\tGPA :" << s[i].gpa << "\tGRADE : " << s[i].grade << "\t";
		cout << endl;
	}
	cout << "\n-----------------------------------------------------\n";
	cout << "\n\nSUBJECT WISE AVERAGES";
	cout << "\n-----------------------------------------------------\n";
	for (int j = 0; j < subjects; j++)
	{
		float sum = 0.0;
		for (int i = 0; i < students; i++)
		{
			sum += s[i].marks[j];
		}
		cout << "\nThe Average of Subject " << j + 1 << " is =" << sum / students;

	}
	cout << "\n-----------------------------------------------------\n";
	cout << "\nPASS / FAIL SUMMARY";
	cout << "\n-----------------------------------------------------\n";
	int pass = 0, fail = 0;
	for (int i = 0; i < students; i++)
	{
		if (s[i].grade != 'F')
			pass++;

		else
			fail++;
	}
	cout << "Total Students : " << students;
	cout << "\nPASS : " << pass << "\nFAIL : " << fail;
	cout << "\nPass Percentage : " << (float(pass) / students) * 100 << " %";
	cout << "\n============================================================================\n";

}
//Recalculates GPA, assigns grades and ranks students
void refresh(Student s[], int students, int subjects)
{
	calculate_gpa(s, students, subjects);
	assign_grades(s, students);
	rank_students(s, students);

}
