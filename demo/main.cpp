//Copyright by Pepchik 2021

#include <vector>
#include "Student.hpp"
#include "iostream"

int main(int argc, char** argv)
{
  nlohmann::json base = JSON_taking(argc, argv);
  std::vector<Student> students = JSON_parsing(base);
  print(students, std::cout);
}

