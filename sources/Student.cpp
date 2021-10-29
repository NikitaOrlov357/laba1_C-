//Copyright by Pepchik 2021

#include "Student.hpp"

#include <iomanip>
#include <utility>



Student::Student(std::string _name, std::any _group,
                 std::any _avg, std::any _debt) {
  name = std::move(_name);
  group = std::move(_group);
  avg = std::move(_avg);
  debt = std::move(_debt);
}

//-------------------CHECK---------------

bool Base_Check(std::any a1, std::any a2)
{
  if (a1.type() != a2.type())
    return false;
  if (a1.type() == typeid(std::string))
    return std::any_cast<std::string>(a1)== std::any_cast<std::string>(a2);
  if (a1.type() == typeid(nullptr))
    return true;
  if (a1.type() == typeid(double))
    return std::any_cast<double>(a1) == std::any_cast<double>(a2);
  if (a1.type() == typeid(size_t))
    return std::any_cast<size_t>(a1) == std::any_cast<size_t>(a2);
  if (a1.type() == typeid(std::vector<std::string>))
    return
        std::any_cast<std::vector<std::string>>(a1)
        == std::any_cast<std::vector<std::string>>(a2);
  return false;
}

bool Student::operator==(const Student& student) const
{
      bool n =  name == student.name;
      bool g = Base_Check(group, student.group);
      bool a = Base_Check(avg, student.avg);
      bool d = Base_Check(debt, student.debt);
      return n && g && a && d;
}

Student::Student() = default;

auto get_name(const json& j) -> std::string {
  return j.get<std::string>();
}

auto get_debt(const json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::vector<std::string>>();
}

auto get_avg(const json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else if (j.is_number_float())
    return j.get<double>();
  else
    return j.get<std::size_t>();
}

auto get_group(const json& j) -> std::any {
  if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::size_t>();
}

void from_json(const json& j, Student& s) {
  s.name = get_name(j.at("name"));
  s.group = get_group(j.at("group"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_debt(j.at("debt"));
}

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

std::string toString(std::any& item);


//-----------------PRINT-----------------------

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


//--------------------PARS-----------------------

std::vector<Student> JSON_parsing(json& data)
{
  std::vector<Student> students;
  for (auto const& item : data.at("items"))
  {
    Student student1;
    from_json(item, student1);
    students.push_back(student1);
  }
  return students;
}
//----------------------TAKE-----------------------

json JSON_taking(int argc, char** argv) {
  if (argc < 2) throw std::runtime_error{"The file path was not passed"};
  std::string filePath(argv[1]);
  std::ifstream jsonFile(filePath);
  if (!jsonFile) throw std::runtime_error{"unable to open json: " + filePath};
  json data;
  jsonFile >> data;
  if (!data.at("items").is_array())
    throw std::runtime_error{"the array must be contained in the file"};

  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>())
    throw std::runtime_error{"_meta value does not match the array size"};
  return data;
}