/*  =========================================================================
    MsgBusAmqpUtils - class description

    Copyright (C) 2014 - 2021 Eaton

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

#pragma once

#include <fty/messagebus/MsgBusException.hpp>
#include <fty/messagebus/amqp/MsgBusAmqpMessage.hpp>

#include <proton/message.hpp>
#include <proton/message_id.hpp>
#include <proton/types.hpp>
#include <proton/scalar_base.hpp>

#include <map>

namespace fty::messagebus::amqp
{
  using Message = fty::messagebus::amqp::AmqpMessage;
  using property_map = std::map<std::string, proton::scalar>;

  inline const MetaData getMetaDataFromAmqpProperties(const messagePointer& msg)
  {
    MetaData metaData{};

    // User properties
    if (!msg->properties().empty())
    {
      property_map props;
      proton::get(msg->properties(), props);
      for (property_map::iterator it = props.begin(); it != props.end(); ++it)
      {
        metaData.emplace(proton::to_string(it->first), proton::to_string(it->second));
      }
    }

    // Req/Rep pattern properties
    if (!msg->correlation_id().empty())
    {
      metaData.emplace(CORRELATION_ID, proton::to_string(msg->correlation_id()));
    }

    if (!msg->reply_to().empty())
    {
      metaData.emplace(REPLY_TO, msg->reply_to());
    }
    return metaData;
  }

  inline const proton::message getAmqpMessageFromMsgBusAmqpMessage(const Message& message)
  {
    proton::message msg;
    for (const auto& [key, value] : message.metaData())
    {
      if (key == REPLY_TO)
      {
        std::string correlationId = message.metaData().find(CORRELATION_ID)->second;
        msg.correlation_id(correlationId);
        msg.reply_to(value);
      }
      else if (key == SUBJECT)
      {
        msg.subject(value);
      }
      else if (key == TO)
      {
        msg.to(value);
      }
      else if (key == FROM)
      {
        msg.user(value);
      }
      else
      {
        msg.properties().put(key, value);
      }
    }
    msg.content_type("string");
    msg.body(message.userData());
    return msg;
  }

  inline const std::string getCorrelationId(const Message& message)
  {
    auto iterator = message.metaData().find(CORRELATION_ID);
    if (iterator == message.metaData().end() || iterator->second == "")
    {
      throw MessageBusException("Request must have a correlation id.");
    }
    return iterator->second;
  }

  inline const std::string getReplyQueue(const Message& message)
  {
    auto iterator = message.metaData().find(REPLY_TO);
    if (iterator == message.metaData().end() || iterator->second == "")
    {
      throw MessageBusException("Request must have a reply to.");
    }
    return iterator->second;
  }

} // namespace fty::messagebus::amqp
