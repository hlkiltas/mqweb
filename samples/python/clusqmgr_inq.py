'''
 Inquire all cluster information from a queuemanager.
 MQWeb runs on localhost and is listening on port 8081.
'''
import json
import httplib
import socket
import argparse

parser = argparse.ArgumentParser(
	description='MQWeb - Python sample - Inquire Cluster Queuemanager',
	epilog="For more information: http://www.mqweb.org"
)
parser.add_argument('-m', '--queuemanager', help='Name of the queuemanager', required=True)
args = parser.parse_args()

url = '/api/clusqmgr/inquire/' + args.queuemanager

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
			print "No cluster queuemanagers found"
		else:
			for data in result['data']:
				print (data['ClusterName']['value'] + ': '
					+ data['QMgrName']['value']
				)
except httplib.HTTPException as e:
	print ('An HTTP error occurred while inquiring cluster queuemanagers: ' +
		e.errno + e.strerror
	)
except socket.error as e:
	print e.strerror
	print 'Is the MQWeb daemon running?'
