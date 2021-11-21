//Copyright 2021 Nik

#include "Student.hpp"
#include <iomanip>
#include <utility>

std::string toString(std::any& item)
{
  std::stringstream ss;
  int check = 0;
  if (item.type() == typeid(std::nullptr_t)){
    ss << "null";
    check = check + 1;
  }
  if (item.type() == typeid(std::string)){
    ss << std::any_cast<std::string>(item);
    check = check + 1;
  }
  if (item.type() == typeid(double)){
    ss << std::any_cast<double>(item);
    check = check + 1;
  }
  if (item.type() == typeid(std::vector<std::string>)){
    ss << std::any_cast<std::vector<std::string> >(item).size();
    check = check + 1;
  }
  if (item.type() == typeid(size_t)){
    ss << std::any_cast<size_t>(item);
    check = check + 1;
  }
  if (check == 0)
    ss << "error";
  return ss.str();
}

void print(std::string s1, std::string s2,
           std::string s3, std::string s4, std::ostream& os)
{
  os << "| " << std::setw(20) << std::left << s1 << "| "
     <<  std::setw(10) << std::left << s2 << "| "
     <<  std::setw(10) << std::left << s3 << "| "
     <<  std::setw(10) << std::left << s4 << "|\n"
     << "|---------------------|-----------|-----------|-----------|\n";
}

void print(Student& student, std::ostream& os)
{
  print(student.name, toString(student.group), toString(student.avg),
        toString(student.debt), os);
}


void print(std::vector<Student>& students, std::ostream& os)
{
  print("name", "group", "avg", "debt", os);
  for (Student& student : students) {
    print(student, os);
  }
}
