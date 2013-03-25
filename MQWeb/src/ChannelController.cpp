/*
 * Copyright 2010 MQWeb - Franky Braem
 *
 * Licensed under the EUPL, Version 1.1 or – as soon they
 * will be approved by the European Commission - subsequent
 * versions of the EUPL (the "Licence");
 * You may not use this work except in compliance with the
 * Licence.
 * You may obtain a copy of the Licence at:
 *
 * http://joinup.ec.europa.eu/software/page/eupl
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the Licence is
 * distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the Licence for the specific language governing
 * permissions and limitations under the Licence.
 */
#include <Poco/DateTimeFormatter.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/URI.h>

#include <MQ/Web/MQController.h>
#include <MQ/Web/ChannelController.h>
#include <MQ/Web/ChannelMapper.h>
#include <MQ/Web/ChannelStatusMapper.h>
#include <MQ/Web/TemplateView.h>
#include <MQ/Web/JSONView.h>

namespace MQ
{
namespace Web
{

ChannelController::ChannelController() : MQController()
{
}


ChannelController::~ChannelController()
{

}

void ChannelController::index()
{
	setView(new TemplateView("channel/index.tpl"));
}


void ChannelController::list()
{
	Poco::JSON::Object::Ptr filter = new Poco::JSON::Object();

	std::string channelNameField = form().get("channelName", "*");
	filter->set("name", channelNameField.empty() ? "*" : channelNameField);
	filter->set("type", form().get("channelType", "All"));
	filter->set("excludeSystem", form().get("channelExcludeSystem", "0").compare("1") == 0);

	ChannelMapper channelMapper(*commandServer());
	Poco::JSON::Array::Ptr jsonChannels = channelMapper.inquire(filter);

	// A channel name is not unique. To make it possible to associate the status
	// to the correct channel, we store all channels in a temporary JSON object
	Poco::JSON::Object::Ptr jsonAllChannels = new Poco::JSON::Object();
	for(Poco::JSON::Array::ValueVector::const_iterator it = jsonChannels->begin(); it != jsonChannels->end(); ++it)
	{
		if ( it->type() == typeid(Poco::JSON::Object::Ptr) )
		{
			Poco::JSON::Object::Ptr jsonChannel = it->extract<Poco::JSON::Object::Ptr>();

			Poco::JSON::Object::Ptr jsonChannelName = jsonChannel->getObject("ChannelName");
			poco_assert_dbg(! jsonChannelName.isNull());
			std::string channelName = jsonChannelName->getValue<std::string>("value");

			Poco::JSON::Object::Ptr jsonType = jsonChannel->getObject("ChannelType");
			poco_assert_dbg(! jsonType.isNull());
			std::string type = jsonType->get("value");

			jsonAllChannels->set(type + "/" + channelName, *it);
		}
	}

	filter = new Poco::JSON::Object();
	filter->set("name", channelNameField.empty() ? "*" : channelNameField);
	filter->set("type", form().get("channelType", "All"));
	ChannelStatusMapper channelStatusMapper(*commandServer());
	Poco::JSON::Array::Ptr statuses = channelStatusMapper.inquire(filter);

	// Associate all status objects to their corresponding channel object
	for(Poco::JSON::Array::ValueVector::const_iterator it = statuses->begin(); it != statuses->end(); ++it)
	{
	if ( it->type() == typeid(Poco::JSON::Object::Ptr) )
	{
		Poco::JSON::Object::Ptr jsonStatus = it->extract<Poco::JSON::Object::Ptr>();

		Poco::JSON::Object::Ptr jsonChannelName = jsonStatus->getObject("ChannelName");
		poco_assert_dbg(! jsonChannelName.isNull());
		std::string channelName = jsonChannelName->getValue<std::string>("value");

		Poco::JSON::Object::Ptr jsonType = jsonStatus->getObject("ChannelType");
		poco_assert_dbg(! jsonType.isNull());
		std::string type = jsonType->get("value");

		Poco::JSON::Object::Ptr jsonChannel = jsonAllChannels->getObject(type + "/" + channelName);
		if ( jsonChannel.isNull() )
		{
			jsonChannel = new Poco::JSON::Object();
			jsonChannel->set("ChannelName", jsonChannelName);
			jsonChannel->set("ChannelType", jsonType);
			jsonChannel->set("autodefined", true);
			jsonAllChannels->set(type + "/" + channelName, jsonChannel);
			jsonChannels->add(jsonChannel);
		}
		jsonChannel->set("status", jsonStatus);
		}
	}

	set("channels", jsonChannels);

	if ( format().compare("html") == 0 )
	{
		setView(new TemplateView("channel/channels.tpl"));
	}
	else if ( format().compare("json") == 0 )
	{
		setView(new JSONView());
	}

}


void ChannelController::view()
{
	std::vector<std::string> parameters = getParameters();

	// First parameter is the queuemanager name
	// Second parameter is the channelname
	if ( parameters.size() < 2 )
	{
		setResponseStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
		return;
	}

	std::string channelName = parameters[1];

	std::string type = form().get("type", "All");

	Poco::JSON::Object::Ptr filter = new Poco::JSON::Object();
	filter->set("name", channelName);
	filter->set("type", type);

	ChannelMapper channelMapper(*commandServer());
	Poco::JSON::Array::Ptr jsonChannels = channelMapper.inquire(filter);
	Poco::JSON::Object::Ptr jsonChannel = jsonChannels->getObject(0);

	if ( !jsonChannel.isNull() )
	{
		set("channel", jsonChannel);
	}
	setView(new TemplateView("channel.tpl"));
}


} } // Namespace MQ::Web
