'''
 Inquire all server connection channel statuses for a queuemanager.
 MQWeb runs on localhost and is listening on port 8081.
'''
import json
import httplib
import socket
import argparse

parser = argparse.ArgumentParser(
	description='MQWeb - Python sample - Inquire Channel Status',
	epilog="For more information: http://www.mqweb.org"
)
parser.add_argument('-m', '--queuemanager', help='Name of the queuemanager', required=True)
args = parser.parse_args()

url = '/api/chstatus/inquire/' + args.queuemanager + '?ChannelType=Server-connection'

try:
	conn = httplib.HTTPConnection('localhost', 8081)
	conn.request('GET', url)
	res = conn.getresponse()
	result = json.loads(res.read())

	if 'error' in result:
		print ('Received a WebSphere MQ error: ' +
			str(result['error']['reason']['code'])
		)
	else:
		if len(result['data']) == 0:
			print "No channelstatus found"
		else:
			for data in result['data']:
				print (data['ChannelName']['value'] + ': '
					+ data['ChannelStatus']['text']
				)
except httplib.HTTPException as e:
	print ('An HTTP error occurred while inquiring channel statuses: ' +
		e.errno + e.strerror
	)
except socket.error as e:
	print e.strerror
	print 'Is the MQWeb daemon running?'
