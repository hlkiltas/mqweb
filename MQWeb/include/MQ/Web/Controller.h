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
#ifndef _MQWeb_Controller_h
#define _MQWeb_Controller_h

#include "Poco/SharedPtr.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/MediaType.h"

#include "Poco/JSON/Object.h"

#include "MQ/QueueManager.h"
#include "MQ/CommandServer.h"

namespace MQ {
namespace Web {


class Controller : public Poco::Net::PartHandler
	/// Base class for all controllers
{
public:

	typedef void (Controller::*ActionFn)();

	typedef std::map<std::string, ActionFn> ActionMap;

	Controller();
		/// Constructor

	virtual ~Controller();
		/// Destructor

	Poco::JSON::Object& data();
		/// Returns the data.

	Poco::Net::HTMLForm& form();
		/// Returns the active form.

	std::string getAction() const;
		/// Returns the called action. The action is the second part of the URL path.
		/// For example qmgr/view/PIGEON will return "view".

	virtual void beforeAction();
		/// Called before an action is executed.

	virtual void afterAction();
		/// Called after an action is executed. The default implementation renders
		/// the associated view. When no view is set, a JSON view will be used

	void formElementToJSONArray(const std::string& name, Poco::JSON::Array::Ptr arr);
		/// Stores each element with the given name in a JSON array

	virtual const ActionMap& getActions() const = 0;
		/// Returns all actions.

	const std::vector<std::string>& getParameters() const;
		/// Returns all parameters

	static std::string htmlize(const std::string &str);
		/// Helper function for replacing some HTML specific characters: <, >, " and &.

	bool isGet() const;
		/// Returns true when the HTTP method GET is used.

	virtual bool isJSON() const;
		/// Return true when the view is a JSON view.
		/// Default is true.

	bool isPost() const;
		/// Returns true when the HTTP method POST is used.

	void set(const std::string& name, const Poco::Dynamic::Var& var);
		/// Sets a variable in data for use in a view

	Poco::Net::HTTPServerRequest& request();
		/// Returns the HTTP request

	Poco::Net::HTTPServerResponse& response();
		/// Returns the HTTP response

	void setResponseStatus(Poco::Net::HTTPServerResponse::HTTPStatus status);
		/// Sets the HTTP response status. This will send the response to the client.

	void setResponseStatus(Poco::Net::HTTPServerResponse::HTTPStatus status, const std::string& reason);
		/// Sets the HTTP response status and reason. This will send the response to the client.

	void render();
		/// Renders the view

protected:


	virtual void handlePart(const Poco::Net::MessageHeader& header, std::istream& stream);


	virtual void handle(const std::vector<std::string>& parameters, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);


private:


	Poco::Net::HTTPServerRequest* _request;


	Poco::Net::HTTPServerResponse* _response;


	Poco::Net::HTMLForm _form;


	Poco::JSON::Object::Ptr _data;


	std::string _action;


	std::vector<std::string> _parameters;


	std::map<std::string, std::string> _namedParameters;


	friend class ControllerRequestHandler;
};


inline void Controller::afterAction()
{
	render();
}


inline void Controller::beforeAction()
{
	//default: do nothing
}


inline Poco::JSON::Object& Controller::data()
{
	poco_assert_dbg(_data);

	return *_data;
}


inline Poco::Net::HTMLForm& Controller::form()
{
	return _form;
}


inline std::string Controller::getAction() const
{
	return _action;
}


inline const std::vector<std::string>& Controller::getParameters() const
{
	return _parameters;
}


inline bool Controller::isGet() const
{
	return _request->getMethod().compare("GET") == 0;
}


inline bool Controller::isJSON() const
{
	return true;
}

inline bool Controller::isPost() const
{
	return _request->getMethod().compare("POST") == 0;
}


inline void Controller::set(const std::string& name, const Poco::Dynamic::Var& var)
{
	_data->set(name, var);
}


inline void Controller::setResponseStatus(Poco::Net::HTTPServerResponse::HTTPStatus status)
{
	_response->setStatus(status);
	_response->send();
}


inline void Controller::setResponseStatus(Poco::Net::HTTPServerResponse::HTTPStatus status, const std::string &reason)
{
	_response->setStatusAndReason(status, reason);
	_response->send();
}


inline Poco::Net::HTTPServerRequest& Controller::request()
{
	poco_assert_dbg(_request);

	return *_request;
}


inline Poco::Net::HTTPServerResponse& Controller::response()
{
	poco_assert_dbg(_response);

	return *_response;
}

}} // Namespace MQ::Web

#endif // _MQWeb_Controller_h
