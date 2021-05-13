#include<iostream>
#include<string>
using namespace std;

class Student
{

private: 
	string name_;
	string SRN_;
	float CGPA_;

public:

	explicit Student(string SRN = "", string name = "", float CPGA = 0.0) : SRN_(SRN), name_(name), CGPA_(CPGA) {}
    friend ostream& operator<<(ostream& o, const Student& s){
		return o << s.SRN_ << "\t" << s.name_ << "\t" << s.CGPA_;
	}
	friend bool operator<(const Student& lhs, const Student& rhs){
		return lhs.SRN_ < rhs.SRN_;
	}
	friend bool operator>(const Student& lhs, const Student& rhs){
		return lhs.SRN_ > rhs.SRN_;
	}
	friend bool operator==(const Student& lhs, const Student& rhs){
		return lhs.SRN_ == rhs.SRN_;
	}
	friend bool operator!=(const Student& lhs, const Student& rhs)
   {
	return !(lhs.SRN_ == rhs.SRN_);
   }
};


