/*  =========================================================================
    FtyCommonMqttTestMathDto - class description

    Copyright (C) 2014 - 2020 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

#ifndef FTY_COMMON_MQTT_TEST_MATH_DTO_HPP
#define FTY_COMMON_MQTT_TEST_MATH_DTO_HPP

#include <list>
#include <string>

namespace messagebus
{
  using UserData = std::list<std::string>;
}

struct MathOperation
{
  std::string operation;
  MathOperation() = default;
  MathOperation(const std::string& _operation)
    : operation(_operation)
  {
  }
};

void operator<<(messagebus::UserData& userData, const MathOperation& object);
void operator>>(messagebus::UserData& payload, MathOperation& object);

struct MathResult
{
  std::string result;
  std::string status;
  MathResult() = default;
  MathResult(const std::string& _result, const std::string& _status)
    : result(_result)
    , status(_status)
  {
  }
};

void operator<<(messagebus::UserData& userData, const MathResult& object);
void operator>>(messagebus::UserData& payload, MathResult& object);

#endif // FTY_COMMON_MQTT_TEST_MATH_DTO_HPP
