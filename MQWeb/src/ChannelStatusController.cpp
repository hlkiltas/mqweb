/*
* Copyright 2017 - KBC Group NV - Franky Braem - The MIT license
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include "MQ/Web/ChannelStatusController.h"
#include "MQ/Web/ChannelStatusInquire.h"

namespace MQ
{
namespace Web
{

ChannelStatusController::ChannelStatusController() : MQController()
{
}


ChannelStatusController::~ChannelStatusController()
{
}


void ChannelStatusController::inquire()
{
	Poco::JSON::Object::Ptr pcfParameters;

	if ( data().has("input") && data().isObject("input") )
	{
		pcfParameters = data().getObject("input");
	}
	else
	{
		pcfParameters = new Poco::JSON::Object();
		setData("input", pcfParameters);

		std::vector<std::string> parameters = getParameters();
		// First parameter is queuemanager
		// Second parameter can be a channelname and will result in inquiring
		// only that channel.
		if ( parameters.size() > 1 )
		{
			pcfParameters->set("ChannelName", parameters[1]);
		}
		else
		{
			// Handle query parameters
			pcfParameters->set("ChannelName", form().get("ChannelName", "*"));
		}

		if ( form().has("ChannelType") )
		{
			Poco::JSON::Object::Ptr filter = new Poco::JSON::Object();
			filter->set("Parameter", "ChannelType");
			filter->set("Operator", "EQ");
			filter->set("FilterValue", form().get("ChannelType"));
			pcfParameters->set("IntegerFilterCommand", filter);
		};

		Poco::JSON::Array::Ptr attrs = new Poco::JSON::Array();
		formElementToJSONArray("ChannelInstanceAttrs", attrs);
		if ( attrs->size() == 0 ) // Nothing found for ChannelInstanceAttrs, try Attrs
		{
			formElementToJSONArray("Attrs", attrs);
		}
		if ( attrs->size() > 0 )
		{
			pcfParameters->set("ChannelInstanceAttrs", attrs);
		}

		if ( form().has("InstanceType") ) pcfParameters->set("InstanceType", form().get("InstanceType"));
		if ( form().has("ClientIdentifier") ) pcfParameters->set("ClientIdentifier", form().get("ClientIdentifier"));
		if ( form().has("ChannelInstanceType") ) pcfParameters->set("ChannelInstanceType", form().get("ChannelInstanceType"));
		if ( form().has("CommandScope") ) pcfParameters->set("CommandScope", form().get("CommandScope"));
		if ( form().has("ConnectionName") ) pcfParameters->set("ConnectionName", form().get("ConnectionName"));
		if ( form().has("XmitQName") ) pcfParameters->set("XmitQName", form().get("XmitQName"));

		handleFilterForm(pcfParameters);
	}
	ChannelStatusInquire command(*commandServer(), pcfParameters);
	setData("data", command.execute());
}


} } // Namespace MQ::Web
