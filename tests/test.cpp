//Copyright 2021 Nik

#define TEST_CPP_
#ifdef TEST_CPP_


#include <gtest/gtest.h>
#include "header.hpp"
#include <Student.hpp>


#ifndef _JSON_DIR
#define JSON_DIR "nobody"
#else
#define JSON_DIR _JSON_DIR
#endif


TEST(printTest, StudentItem)
{
  std::stringstream ss;
  Student s("test", (std::string)"test", (size_t)3, std::vector<std::string>());
  print(s, ss);
  ASSERT_EQ("| test                | test      | 3         | 0         |\n"
      "|---------------------|-----------|-----------|-----------|\n",  ss.str());
}
TEST(printTest, StudentsArray) {
    std::stringstream ss;
    std::vector<Student> students;
    students.emplace_back("test", (std::string)"test",
                          (size_t)3, std::vector<std::string>());
    students.emplace_back("test", (size_t)4,
                          (double)3.33, std::vector<std::string>());
    print(students, ss);
    ASSERT_EQ("| name                | group     | avg       | debt      |\n"
        "|---------------------|-----------|-----------|-----------|\n"
        "| test                | test      | 3         | 0         |\n"
        "|---------------------|-----------|-----------|-----------|\n"
        "| test                | 4         | 3.33      | 0         |\n"
        "|---------------------|-----------|-----------|-----------|\n",  ss.str());
}
TEST(printTest, json)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Akakiy Akaki\",\n"
      "      \"group\": \"UI8-32\",\n"
      "      \"avg\": \"5.25\",\n"
      "      \"debt\": null\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Ded Asambler\",\n"
      "      \"group\": 32,\n"
      "      \"avg\": 3.75,\n"
      "      \"debt\": \"asembler\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 2\n"
      "  }\n"
      "}";
  nlohmann::json _json = json::parse(jsonData);
  std::vector<Student> students_parsed = parsingJson(_json);
  std::stringstream ss;
  print(students_parsed, ss);
  ASSERT_EQ("| name                | group     | avg       | debt      |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| Akakiy Akaki        | UI8-32    | 5.25      | null      |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| Ded Asambler        | 32        | 3.75      | asembler  |\n"
      "|---------------------|-----------|-----------|-----------|\n", ss.str());
}

TEST(parseTest, jsonParse)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Akakiy Akaki\",\n"
      "      \"group\": \"UI8-32\",\n"
      "      \"avg\": \"5.25\",\n"
      "      \"debt\": null\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Ded Asambler\",\n"
      "      \"group\": 32,\n"
      "      \"avg\": 3.75,\n"
      "      \"debt\": \"asembler\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 2\n"
      "  }\n"
      "}";
    nlohmann::json _json = json::parse(jsonData);
    std::vector<Student> students_parsed = parsingJson(_json);
    std::vector<Student> student_inited = {
        Student("Akakiy Akaki", (std::string)"UI8-32",
                (std::string)"5.25", nullptr),
        Student("Ded Asambler", (size_t)32,
                (double)3.75, (std::string)"asembler")
    };
    ASSERT_EQ(student_inited, students_parsed);
}
TEST(parseTest, fromFile)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Akakiy Akaki\",\n"
      "      \"group\": \"2\",\n"
      "      \"avg\": \"5.25\",\n"
      "      \"debt\":  [\n"
      "        \"Java\",\n"
      "        \"C++\",\n"
      "        \"Games\"\n"
      "      ]\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Ded Asembler\",\n"
      "      \"group\": 32,\n"
      "      \"avg\": 3.75,\n"
      "      \"debt\": \"asembler\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 2\n"
      "  }\n"
      "}";
  nlohmann::json json1 = json::parse(jsonData);
  std::string path = JSON_DIR;
  path+="/test1.json";
  char* argv[] ={(char*)"", (char*)(path.c_str())};
  nlohmann::json json2 = takeJson(2, argv);
  ASSERT_EQ(json1, json2) << "Test passed!";
}

#endif // TEST_CPP_