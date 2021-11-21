// Copyright 2021 Nik

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
bool anyDate(std::any a1, std::any a2)
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
      bool g = anyDate(group, student.group);
      bool a = anyDate(avg, student.avg);
      bool d = anyDate(debt, student.debt);
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
