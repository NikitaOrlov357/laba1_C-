//Copyright 2021 Nik

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <string>
#include <any>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


using nlohmann::json;

json takeJson(int argc, char** argv);

#endif // INCLUDE_HEADER_HPP_
