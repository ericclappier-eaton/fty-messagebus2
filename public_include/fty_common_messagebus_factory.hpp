/*  =========================================================================
    fty_common_messagebus_factory - class description

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

#ifndef FTY_COMMON_MESSAGEBUS_FACTORY_HPP
#define FTY_COMMON_MESSAGEBUS_FACTORY_HPP

#include "fty/messagebus/mqtt/fty_common_messagebus_mqtt.hpp"
#include "fty/messagebus/mqtt/fty_common_messagebus_mqtt_message.hpp"
#include "fty_common_messagebus_interface.h"
//#include "fty_common_messagebus_malamute.h"

#include <string>

namespace messagebus
{
  class MessagebusFactory
  {

  public:
    MessagebusFactory() = default;
    virtual ~MessagebusFactory(){};

    /**
   * @brief Malamute implementation
   *
   * @param _endpoint Message bus end point
   * @param clientName prefix for client Name
   *
   * @return client Name
   */
    //auto createMlmMsgBus(const std::string& _endpoint, const std::string& _clientName) -> messagebus::mqttv5::MqttMessageBus*;

    /**
   * @brief Mqtt implementation
   *
   * @param _endpoint Mqtt end point
   * @param _clientName prefix for client Name
   *
   * @return IMessageBus
   */
    auto static createMqttMsgBus(const std::string& _endpoint, const std::string& _clientName) -> messagebus::mqttv5::MqttMessageBus*;
  };

} // namespace messagebus

#endif // FTY_COMMON_MESSAGEBUS_FACTORY_HPP
