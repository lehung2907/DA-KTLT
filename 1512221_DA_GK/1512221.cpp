#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct Student{
	string StudentID;
	string Name;
	string Faculty;
	string Course;
	string DayOfBirth;
	string Image;
	string Intro;
	string Email;
	string Hobby;
};
Student SV[1000];//khai bao phan tu gom 1000 sinh vien
int Num = 0;
const int total = 9;
const string profile = "Website";
string Templatee = "data/Template.html";
void ReadFile(Student Freshman[100], int &Num);
void WriteTemplate(string TemplateLine[1000], int n, int Count);
//hàm đọc file lưu danh sách sinh viên
void ReadFile(Student SV[1000], int &Num){
	string line;
	ifstream File("data/CheckList.csv");
	while (File.good()){
		Student A;
		//đọc từng yếu tố của một sinh viên
		getline(File, A.StudentID, ',');
		getline(File, A.Name, ',');
		getline(File, A.Faculty, ',');
		getline(File, A.Course, ',');
		getline(File, A.DayOfBirth, ',');
		getline(File, A.Email, ',');
		getline(File, A.Image, ',');
		getline(File, A.Intro, ',');
		getline(File, A.Hobby);
		getline(File, line);
		SV[Num] = A;//lưu sinh viên 
		Num++;
	}
	File.close();//đóng file
}
//trình diễn sinh viên
void FreshmanShow(Student Freshman[100], int n){
	//n:số thứ tự sinh viên
	int Num;
	ReadFile(Freshman, Num);//gọi hàm đọc file sinh viên ở trên
	//xuất ra các yếu tố thông tin sinh viên
	cout << "Student ID:" << Freshman[n].StudentID << endl;
	cout << "Name:" << Freshman[n].Name << endl;
	cout << "Faculty:" << Freshman[n].Faculty << endl;
	cout << "Course:" << Freshman[n].Course << endl;
	cout << "Day Of Birth:" << Freshman[n].DayOfBirth << endl;
	cout << "Email:" << Freshman[n].Email << endl;
	cout << "Image:" << Freshman[n].Image << endl;
	cout << "Intro:" << Freshman[n].Intro << endl;
	cout << "Hobby:" << Freshman[n].Hobby << endl;
}
//hàm đọc template
void ReadTemplate(string TemplateLine[1000], int &Count){
	Count = 0;
	ifstream Template(Templatee);
	if (Template.is_open()){
		while (Template.good()){
			getline(Template, TemplateLine[Count]);
			Count++;
			//đọc từng dòng trên template
		}
	}
	Template.close();
}
//thêm các sinh viên vào từng template bằng việc thay thế các ký tự trong template
void TemplateReplace(string &str, const string &from, const string &to) {
	if (from.empty()){
		return;
	}
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos)//npos=-1
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}
//hàm viết template để đưa thông tin sinh viên vào file html
void WriteTemplate(string TemplateLine[1000], int n, int Count){

	ReadFile(SV, Num);//gọi hàm đọc file sinh viên
	string FileName = profile + "/" + SV[n].StudentID + ".html";//đặt tên cho file html theo MSSV 
	ofstream File(FileName);
	ReadTemplate(TemplateLine, Count);//gọi hàm đọc template

	//khai báo các ký hiệu tổng quát (để thay thế bằng thông tin của sinh viên)
	const string from[total] =
	{
		"$id", "$name", "$birthday", "$faculty",
		"$school_year", "$gmail", "$avatar", "$info", "$hobbies"
	};
	//khai báo các thành phần sẽ xuất ra trong file html
	const string to[total] = { SV[n].StudentID, SV[n].Name, SV[n].DayOfBirth, SV[n].Faculty, SV[n].Course, SV[n].Email,
		SV[n].Image, SV[n].Intro, SV[n].Hobby };

	for (int Line = 0; Line < Count; Line++)
	{//chạy trên từng dòng
		for (int Content = 0; Content < total; Content++)
		{//chạy trên từng yếu tố của sinh viên
			TemplateReplace(TemplateLine[Line], from[Content], to[Content]);//thay thế những $Name, $Faculty,... bằng thông tin sinh viên
		}

		File << TemplateLine[Line];//ghi vào template
		File << endl;//xuống dòng
	}
}
int main(){
	string TemplateLine[1000];//khai áo mảng string
	int Content;
	ReadFile(SV, Num);
	cout << "Input ordinal student:";//nhập vào sinh viên
	cin >> Content;
	WriteTemplate(TemplateLine, Content, 0);//gọi hàm viết template
	//system("pause");
	return 0;
}