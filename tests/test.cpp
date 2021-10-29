//Copyright by Pepchik 2021

#define TEST_CPP_
#ifdef TEST_CPP_

#include <gtest/gtest.h>

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
      "      \"name\": \"Nikita Orlov\",\n"
      "      \"group\": \"UI2-32\",\n"
      "      \"avg\": \"10.05\",\n"
      "      \"debt\": null\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Last Guardian\",\n"
      "      \"group\": 99,\n"
      "      \"avg\": 99.99,\n"
      "      \"debt\": \"all\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 2\n"
      "  }\n"
      "}";
  nlohmann::json _json = json::parse(jsonData);
  std::vector<Student> students_parsed = JSON_parsing(_json);
  std::stringstream ss;
  print(students_parsed, ss);
  ASSERT_EQ("| name                | group     | avg       | debt      |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| Nikita Orlov        | UI2-32    | 10.05     | null      |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| Last Guardian       | 99        | 99.99     | all       |\n"
      "|---------------------|-----------|-----------|-----------|\n", ss.str());
}

TEST(parseTest, jsonParse)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Nikita Orlov\",\n"
      "      \"group\": \"UI2-32\",\n"
      "      \"avg\": \"10.05\",\n"
      "      \"debt\": null\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Last Guardian\",\n"
      "      \"group\": 99,\n"
      "      \"avg\": 99.99,\n"
      "      \"debt\": \"all\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 2\n"
      "  }\n"
      "}";
  nlohmann::json _json = json::parse(jsonData);
  std::vector<Student> students_parsed = JSON_parsing(_json);
  std::vector<Student> student_inited = {
      Student("Nikita Orlov", (std::string)"UI2-32",
              (std::string)"10.05", nullptr),
      Student("Last Guardian", (size_t)99,
              (double)99.99, (std::string)"all")
  };
  ASSERT_EQ(student_inited, students_parsed);
}
TEST(parseTest, fromFile)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Nikita Orlov\",\n"
      "      \"group\": \"32\",\n"
      "      \"avg\": \"1.23\",\n"
      "      \"debt\":  [\n"
      "        \"Java\",\n"
      "        \"JavaScript\",\n"
      "        \"Bash\"\n"
      "      ]\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Geralt\",\n"
      "      \"group\": 1,\n"
      "      \"avg\": 50.05,\n"
      "      \"debt\": \"withcer\"\n"
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
  nlohmann::json json2 = JSON_taking(2, argv);
  ASSERT_EQ(json1, json2) << "Test passed!";
}

TEST(errorCheck, lessArgsTest)
{
  try {
    std::string path = JSON_DIR;
    path+="/test1.json";
    char* argv[] ={(char*)"", (char*)(path.c_str())};
    nlohmann::json json2 = JSON_taking(1, argv);
    FAIL() << "Expected: The file path was not passed";
  }
  catch(std::runtime_error const & err) {
    EXPECT_EQ(err.what(),std::string("The file path was not passed"));
  }
  catch(...) {
    FAIL() << "Expected The file path was not passed";
  }
}

TEST(errorCheck, _metaCheck)
{
  try {
    std::string path = JSON_DIR;
    path+="/test2.json";
    char* argv[] ={(char*)"", (char*)(path.c_str())};
    nlohmann::json json2 = JSON_taking(2, argv);
    FAIL() << "Expected: _meta value does not match the array size";
  }
  catch(std::runtime_error const & err) {
    EXPECT_EQ(err.what(),std::string("_meta value does not match the array size"));
  }
  catch(...) {
    FAIL() << "Expected: _meta value does not match the array size";
  }
}
#endif // TEST_CPP_