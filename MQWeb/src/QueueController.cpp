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
#include "MQ/Web/QueueController.h"
#include "MQ/Web/QueueCopy.h"
#include "MQ/Web/QueueClear.h"
#include "MQ/Web/QueueCreate.h"
#include "MQ/Web/QueueInquire.h"
#include "MQ/Web/QueueRemove.h"

namespace MQ
{
namespace Web
{


QueueController::QueueController() : MQController()
{
}


QueueController::~QueueController()
{
}

void QueueController::clear()
{
	Poco::JSON::Object::Ptr pcfParameters;

	if (data().has("input") && data().isObject("input"))
	{
		pcfParameters = data().getObject("input");
	}
	else
	{
		pcfParameters = new Poco::JSON::Object();
		meta().set("input", pcfParameters);

		std::vector<std::string> parameters = getParameters();
		// First parameter is queuemanager
		// Second parameter can be a queuename. If this is passed, the
		// query parameter QName or queueName is ignored.
		if (parameters.size() > 1)
		{
			pcfParameters->set("QName", parameters[1]);
		}
		else
		{
			// Handle query parameters
			pcfParameters->set("QName", form().get("QName", "*"));
		}

		if (form().has("CommandScope"))
		{
			pcfParameters->set("CommandScope", form().get("CommandScope"));
		}

		if (form().has("QSGDisposition"))
		{
			pcfParameters->set("QSGDisposition", form().get("QSGDisposition"));
		}

	}

	QueueClear command(*commandServer(), pcfParameters);
	setData("data", command.execute());
}

void QueueController::copy()
{
	Poco::JSON::Object::Ptr pcfParameters;
	if ( data().has("input") && data().isObject("input") )
	{
		pcfParameters = data().getObject("input");
	}
	else
	{
		pcfParameters = new Poco::JSON::Object();

		std::vector<std::string> parameters = getParameters();
		if ( parameters.size() > 2 )
		{
			pcfParameters->set("FromQName", parameters[2]);
		}
		if ( parameters.size() > 1 )
		{
			pcfParameters->set("ToQName", parameters[1]);
		}

		// Copy all query parameters to PCF
		for(Poco::Net::NameValueCollection::ConstIterator it = form().begin(); it != form().end(); ++it)
		{
			pcfParameters->set(it->first, it->second);
		}
	}
	QueueCopy command(*commandServer(), pcfParameters);
	command.execute();
}

void QueueController::create()
{
	Poco::JSON::Object::Ptr pcfParameters;
	if ( data().has("input") && data().isObject("input") )
	{
		pcfParameters = data().getObject("input");
	}
	else
	{
		pcfParameters = new Poco::JSON::Object();

		std::vector<std::string> parameters = getParameters();
		if ( parameters.size() > 1 )
		{
			pcfParameters->set("QName", parameters[1]);
		}
		// Copy all query parameters to PCF, except QName if it is already set on the URI
		for(Poco::Net::NameValueCollection::ConstIterator it = form().begin(); it != form().end(); ++it)
		{
			if (parameters.size() > 1 && Poco::icompare(it->first, "QName") == 0) continue;
			pcfParameters->set(it->first, it->second);
		}
	}
	QueueCreate command(*commandServer(), pcfParameters);
	command.execute();
}

void QueueController::remove()
{
	Poco::JSON::Object::Ptr pcfParameters;

	if ( data().has("input") && data().isObject("input") )
	{
		pcfParameters = data().getObject("input");
	}
	else
	{
		pcfParameters = new Poco::JSON::Object();
		meta().set("input", pcfParameters);

		std::vector<std::string> parameters = getParameters();
		// First parameter is queuemanager
		// Second parameter can be a queuename. If this is passed, the
		// query parameter QName or queueName is ignored.
		if ( parameters.size() > 1 )
		{
			pcfParameters->set("QName", parameters[1]);
		}
		else
		{
			// Handle query parameters
			std::string queueName;
			if ( form().has("QName") )
			{
				queueName = form().get("QName");
			}
			pcfParameters->set("QName", queueName);
		}

		if ( form().has("CommandScope") )
		{
			pcfParameters->set("CommandScope", form().get("CommandScope"));
		}

		if ( form().has("QSGDisposition") )
		{
			pcfParameters->set("QSGDisposition", form().get("QSGDisposition"));
		}

		if ( form().has("QType") )
		{
			pcfParameters->set("QType", form().get("QType"));
		}
	}

	QueueRemove command(*commandServer(), pcfParameters);
	command.execute();
}

void QueueController::inquire()
{
	Poco::JSON::Object::Ptr pcfParameters;

	if ( data().has("input") && data().isObject("input") )
	{
		pcfParameters = data().getObject("input");
	}
	else
	{
		pcfParameters = new Poco::JSON::Object();
		meta().set("input", pcfParameters);

		std::vector<std::string> parameters = getParameters();
		// First parameter is queuemanager
		// Second parameter can be a queuename. If this is passed, the
		// query parameter QName or queueName is ignored.
		if ( parameters.size() > 1 )
		{
			pcfParameters->set("QName", parameters[1]);
		}
		else
		{
			// Handle query parameters
			pcfParameters->set("QName", form().get("QName", "*"));
		}

		if ( form().has("ClusterInfo") )
		{
			std::string clusterInfo = form().get("ClusterInfo");
			pcfParameters->set("ClusterInfo", Poco::icompare(clusterInfo, "true") == 0 ? "true" : "false");
		}

		if ( form().has("ClusterName") )
		{
			pcfParameters->set("ClusterName", form().get("ClusterName"));
		}

		if ( form().has("ClusterNameList") )
		{
			pcfParameters->set("ClusterNamelist", form().get("ClusterNamelist"));
		}

		if ( form().has("CommandScope") )
		{
			pcfParameters->set("CommandScope", form().get("CommandScope"));
		}

		if ( form().has("PageSetId") )
		{
			int pageSetId = 0;
			if ( Poco::NumberParser::tryParse(form().get("PageSetId"), pageSetId) )
			{
				pcfParameters->set("PageSetId", pageSetId);
			}
		}

		if ( form().has("QSGDisposition") )
		{
			pcfParameters->set("QSGDisposition", form().get("QSGDisposition"));
		}

		std::string queueDepthField;
		if ( form().has("CurrentQDepth") )
		{
			queueDepthField = form().get("CurrentQDepth", "");
		}
		else if ( form().has("QueueDepth"))
		{
			queueDepthField = form().get("QueueDepth", "");
		}
		if ( !queueDepthField.empty() )
		{
			int queueDepth = 0;
			if ( Poco::NumberParser::tryParse(queueDepthField, queueDepth) )
			{
				Poco::JSON::Object::Ptr filter = new Poco::JSON::Object();
				filter->set("Parameter", "CurrentQDepth");
				filter->set("Operator", "NLT"); //Not Less##
				filter->set("FilterValue", queueDepth);
				pcfParameters->set("IntegerFilterCommand", filter);
			}
		}

		handleFilterForm(pcfParameters);

		if ( form().has("QueueUsage") )
		{
			pcfParameters->set("Usage", form().get("QueueUsage"));
		}
		else if ( form().has("Usage") )
		{
			pcfParameters->set("Usage", form().get("Usage"));
		}

		if ( form().has("QueueType") )
		{
			pcfParameters->set("QType", form().get("QueueType"));
		}

		pcfParameters->set("ExcludeSystem", form().get("ExcludeSystem", "false").compare("true") == 0);
		pcfParameters->set("ExcludeTemp", form().get("ExcludeTemp", "false").compare("true") == 0);

		Poco::JSON::Array::Ptr attrs = new Poco::JSON::Array();
		formElementToJSONArray("QAttrs", attrs);
		if ( attrs->size() == 0 ) // Nothing found for QAttrs, try Attrs
		{
			formElementToJSONArray("Attrs", attrs);
		}
		if ( attrs->size() > 0 )
		{
			pcfParameters->set("QAttrs", attrs);
		}
	}

	QueueInquire command(*commandServer(), pcfParameters);
	setData("data", command.execute());
}


} } // Namespace MQ::Web
