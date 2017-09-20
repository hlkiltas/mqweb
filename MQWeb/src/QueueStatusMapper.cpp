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
#include "MQ/Web/QueueStatusMapper.h"

namespace MQ {
namespace Web {

QueueStatusMapper::QueueStatusMapper(CommandServer& commandServer, Poco::JSON::Object::Ptr input)
: MQMapper(commandServer, "QueueStatus", input)
{
}

QueueStatusMapper::~QueueStatusMapper()
{
}


void QueueStatusMapper::change()
{
	poco_assert_dbg(false); // Not yet implemented
}


void QueueStatusMapper::create(bool replace)
{
	poco_assert_dbg(false); // Not yet implemented
}


void QueueStatusMapper::copy(bool replace)
{
	poco_assert_dbg(false); // Not yet implemented
}


Poco::JSON::Array::Ptr QueueStatusMapper::inquire()
{
	createCommand(MQCMD_INQUIRE_Q_STATUS);

	// Required parameters
	addParameter<std::string>(MQCA_Q_NAME, "QName");

	// Optional parameters
	//TODO: ByteStringFilter
	addParameter<std::string>(MQCACF_COMMAND_SCOPE, "CommandScope");
	addIntegerFilter();
	addParameterNumFromString(MQIACF_OPEN_TYPE, "OpenType");
	addParameterNumFromString(MQIA_QSG_DISP, "QSGDisposition");
	addAttributeList(MQIACF_Q_STATUS_ATTRS, "QStatusAttrs");
	addParameterNumFromString(MQIACF_STATUS_TYPE, "StatusType");
	addStringFilter();

	PCF::Vector commandResponse;
	execute(commandResponse);

	bool excludeSystem = _input->optValue("ExcludeSystem", false);
	bool excludeTemp = _input->optValue("ExcludeTemp", false);

	Poco::JSON::Array::Ptr json = new Poco::JSON::Array();

	for(PCF::Vector::iterator it = commandResponse.begin(); it != commandResponse.end(); it++)
	{
		if ( (*it)->isExtendedResponse() ) // Skip extended response
			continue;

		if ( (*it)->getReasonCode() != MQRC_NONE ) // Skip errors (2035 not authorized for example)
			continue;

		std::string qName = (*it)->getParameterString(MQCA_Q_NAME);
		if ( excludeSystem
			&& qName.compare(0, 7, "SYSTEM.") == 0 )
		{
			continue;
		}

		if ( excludeTemp
			&& (*it)->hasParameter(MQIA_DEFINITION_TYPE)
			&& (*it)->getParameterNum(MQIA_DEFINITION_TYPE) == MQQDT_TEMPORARY_DYNAMIC )
		{
			continue;
		}

		json->add(createJSON(**it));
	}

	return json;
}

}} //  Namespace MQ::Web
