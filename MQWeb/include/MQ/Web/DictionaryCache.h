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
#ifndef _MQWeb_DictionaryCache_H
#define _MQWeb_DictionaryCache_H

#include "Poco/ExpireCache.h"
#include "Poco/Mutex.h"

#include "MQ/Web/Dictionary.h"

namespace MQ {
namespace Web {


class DictionaryCache
	/// Cache for dictionaries
{
public:
	DictionaryCache();
		/// Constructor

	virtual ~DictionaryCache();
		/// Destructor

	Poco::SharedPtr<Dictionary> getDictionary(const std::string& name);
		/// Returns a dictionary for a specific object

	static DictionaryCache* instance();

private:

	void setup();

	Poco::ExpireCache<std::string, Dictionary> _cache;

	Poco::Mutex _mutex;

	static DictionaryCache* _instance;

	Poco::SharedPtr<Dictionary> load(const std::string& name);
};

inline DictionaryCache* DictionaryCache::instance()
{
	return _instance;
}

}} // Namespace MQ::Web

#endif // _MQWeb_DictionaryCache_H
