/*
 * Copyright 2010 MQWeb - Franky Braem
 *
 * Licensed under the EUPL, Version 1.1 or  as soon they
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

#include "MQ/QueueManagerPool.h"

namespace MQ
{

QueueManagerFactory::QueueManagerFactory(const std::string& qmgrName)
: _qmgrName(qmgrName)
{
}

QueueManagerFactory::QueueManagerFactory(const std::string& qmgrName, const Poco::Dynamic::Struct<std::string>& connectionInformation)
: _qmgrName(qmgrName)
, _connectionInformation(connectionInformation)
{
}

QueueManagerFactory::QueueManagerFactory(const QueueManagerFactory& copy)
: _qmgrName(copy._qmgrName)
, _connectionInformation(copy._connectionInformation)
{
}

QueueManagerFactory::~QueueManagerFactory()
{
}

QueueManager::Ptr QueueManagerFactory::createObject()
{
	return new QueueManager(_qmgrName);
}

void QueueManagerFactory::activateObject(QueueManager::Ptr qmgr)
{
	if ( !qmgr->connected() )
	{
		if ( _connectionInformation.size() == 0 )
		{
			qmgr->connect();
		}
		else
		{
			qmgr->connect(_connectionInformation);
		}
	}
}

QueueManagerPool::QueueManagerPool(const QueueManagerFactory& factory, std::size_t capacity, std::size_t peakCapacity)
: _pool(factory, capacity, peakCapacity)
{
}


QueueManagerPool::~QueueManagerPool()
{
}

QueueManagerPoolGuard::QueueManagerPoolGuard(Poco::SharedPtr<QueueManagerPool> pool) 
	: _pool(pool)
	, _qmgr(pool->getQueueManager())
{
}

QueueManagerPoolGuard::~QueueManagerPoolGuard() 
{
	_pool->release(_qmgr);
}

} // Namespace MQ
