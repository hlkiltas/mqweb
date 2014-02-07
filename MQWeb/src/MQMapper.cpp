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
#include "MQ/Web/MQMapper.h"

#include "Poco/JSON/Object.h"

namespace MQ {
namespace Web {

Dictionary MQMapper::_dictionary = Dictionary()
	// Common properties
	(MQCA_ALTERATION_DATE, "AlterationDate")
	(MQCA_ALTERATION_TIME, "AlterationTime")
	(MQCA_CLUSTER_NAME, "ClusterName")
	(MQCA_CLUSTER_NAMELIST, "ClusterNamelist")
	(MQCA_CREATION_DATE, "CreationDate")
	(MQCA_CREATION_TIME, "CreationTime")
	(MQIA_QSG_DISP, "QSGDisposition", DisplayMapInitializer
		(MQQSGD_COPY, "Copy")
		(MQQSGD_GROUP, "Group")
		(MQQSGD_Q_MGR, "Qmgr")
		(MQQSGD_SHARED, "Shared")
	)
	(MQCA_Q_MGR_NAME, "QMgrName")

	// QueueManager properties
	(MQIA_ACCOUNTING_CONN_OVERRIDE, "AccountingConnOverride", DisplayMapInitializer
		(MQMON_DISABLED, "Disabled")
		(MQMON_ENABLED, "Enabled")
	)
	(MQIA_ACCOUNTING_INTERVAL, "AccountingInterval")
	(MQIA_ACTIVITY_CONN_OVERRIDE, "ActivityConnOverride", DisplayMapInitializer
		(MQMON_DISABLED, "Disabled")
		(MQMON_ENABLED, "Enabled")
	)
	(MQIA_ACTIVITY_RECORDING, "ActivityRecording", DisplayMapInitializer
		(MQRECORDING_DISABLED, "Disabled")
		(MQRECORDING_MSG, "Msg")
		(MQRECORDING_Q, "Queue")
	)
	(MQIA_ACTIVITY_TRACE, "ActivityTrace", DisplayMapInitializer
		(MQMON_OFF, "Off")
		(MQMON_ON, "On")
	)
	(MQIA_ADOPTNEWMCA_CHECK, "AdoptNewMCACheck", DisplayMapInitializer
		(MQADOPT_CHECK_Q_MGR_NAME, "QmgrName")
		(MQADOPT_CHECK_NET_ADDR, "NetAddr")
		(MQADOPT_CHECK_ALL, "All")
		(MQADOPT_CHECK_NONE, "None")
	)
	(MQIA_ADOPTNEWMCA_TYPE, "AdoptNewMCAType", DisplayMapInitializer
		(MQADOPT_TYPE_NO, "No")
		(MQADOPT_TYPE_ALL, "All")
	)
	(MQIA_AUTHORITY_EVENT, "AuthorityEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQIA_BRIDGE_EVENT, "BridgeEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
#ifdef MQIA_CERT_VAL_POLICY
	(MQIA_CERT_VAL_POLICY, "CertificateValPolicy", DisplayMapInitializer
		(MQ_CERT_VAL_POLICY_ANY, "Policy Any")
		(MQ_CERT_VAL_POLICY_RFC5280, "Policy RFC5280")
	)
#endif
	(MQIA_QMGR_CFCONLOS, "CFConlos", DisplayMapInitializer
		(MQCFCONLOS_TERMINATE, "Terminate")
		(MQCFCONLOS_TOLERATE, "Tolerate")
	)
	(MQIA_CHANNEL_AUTO_DEF, "ChannelAutoDef", DisplayMapInitializer
		(MQCHAD_DISABLED, "Disabled")
		(MQCHAD_ENABLED, "Enabled")
	)
	(MQIA_CHANNEL_AUTO_DEF_EVENT, "ChannelAutoDefEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQCA_CHANNEL_AUTO_DEF_EXIT, "ChannelAutoDefExit")
	(MQIA_CHLAUTH_RECORDS, "ChannelAuthenticationRecords", DisplayMapInitializer
		(MQCHLA_DISABLED, "Disabled")
		(MQCHLA_ENABLED, "Enabled")
	)
	(MQIA_CHANNEL_EVENT, "ChannelEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
		(MQEVR_EXCEPTION, "Exception")
	)
	(MQIA_CHINIT_CONTROL, "ChannelInitiatorControl", DisplayMapInitializer
		(MQSVC_CONTROL_MANUAL, "Manual")
		(MQSVC_CONTROL_Q_MGR, "Qmgr")
		)
	(MQIA_MONITORING_CHANNEL, "ChannelMonitoring", DisplayMapInitializer
		(MQMON_NONE, "None")
		(MQMON_Q_MGR, "Qmgr")
		(MQMON_OFF, "Off")
		(MQMON_LOW, "Low")
		(MQMON_MEDIUM, "Medium")
		(MQMON_HIGH, "High")
	)
	(MQIA_STATISTICS_CHANNEL, "ChannelStatistics", DisplayMapInitializer
		(MQMON_NONE, "None")
		(MQMON_Q_MGR, "Qmgr")
		(MQMON_OFF, "Off")
		(MQMON_LOW, "Low")
		(MQMON_MEDIUM, "Medium")
		(MQMON_HIGH, "High")
	)
	(MQIA_CHINIT_ADAPTERS, "ChinitAdapters")
	(MQIA_CHINIT_DISPATCHERS, "ChinitDispatchers")
	(MQCA_CHINIT_SERVICE_PARM, "ChinitServiceParm")
	(MQIA_CHINIT_TRACE_AUTO_START, "ChinitTraceAutoStart", DisplayMapInitializer
		(MQTRAXSTR_YES, "Yes")
		(MQTRAXSTR_NO, "No")
	)
	(MQIA_CHINIT_TRACE_TABLE_SIZE, "ChinitTraceTableSize")
	(MQIA_MONITORING_AUTO_CLUSSDR, "ClusterSenderMonitoringDefault", DisplayMapInitializer
		(MQMON_Q_MGR, "Qmgr")
		(MQMON_OFF, "Off")
		(MQMON_LOW, "Low")
		(MQMON_MEDIUM, "Medium")
		(MQMON_HIGH, "High")
	)
	(MQIA_STATISTICS_AUTO_CLUSSDR, "ClusterSenderStatistics", DisplayMapInitializer
		(MQMON_Q_MGR, "Qmgr")
		(MQMON_OFF, "Off")
		(MQMON_LOW, "Low")
		(MQMON_MEDIUM, "Medium")
		(MQMON_HIGH, "High")
	)
	(MQCA_CLUSTER_WORKLOAD_DATA, "ClusterWorkLoadData")
	(MQCA_CLUSTER_WORKLOAD_EXIT, "ClusterWorkLoadExit")
	(MQIA_CLUSTER_WORKLOAD_LENGTH, "ClusterWorkLoadLength")
	(MQIA_CLWL_MRU_CHANNELS, "CLWLMRUChannels")
	(MQIA_CLWL_USEQ, "CLWLUseQ", DisplayMapInitializer
		(MQCLWL_USEQ_ANY, "Any")
		(MQCLWL_USEQ_LOCAL, "Local")
	)
	(MQIA_CODED_CHAR_SET_ID, "CodedCharSetID")
	(MQIA_COMMAND_EVENT, "CommandEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
		(MQEVR_NO_DISPLAY, "NoDisplay")
	)
	(MQCA_COMMAND_INPUT_Q_NAME, "CommandInputQName")
	(MQIA_COMMAND_LEVEL, "CommandLevel", DisplayMapInitializer
		(MQCMDL_LEVEL_1, "Level 1")
		(MQCMDL_LEVEL_101, "Level 101")
		(MQCMDL_LEVEL_110, "Level 110")
		(MQCMDL_LEVEL_200, "Level 200")
		(MQCMDL_LEVEL_220, "Level 220")
		(MQCMDL_LEVEL_221, "Level 221")
		(MQCMDL_LEVEL_320, "Level 320")
		(MQCMDL_LEVEL_420, "Level 420")
		(MQCMDL_LEVEL_500, "Level 500")
		(MQCMDL_LEVEL_510, "Level 510")
		(MQCMDL_LEVEL_520, "Level 520")
		(MQCMDL_LEVEL_530, "Level 530")
		(MQCMDL_LEVEL_531, "Level 531")
		(MQCMDL_LEVEL_600, "Level 600")
		(MQCMDL_LEVEL_700, "Level 700")
		(MQCMDL_LEVEL_701, "Level 701")
		(MQCMDL_LEVEL_710, "Level 710")
	)
	(MQIA_CMD_SERVER_CONTROL, "CommandServerControl", DisplayMapInitializer
		(MQSVC_CONTROL_MANUAL, "Manual")
		(MQSVC_CONTROL_Q_MGR, "Qmgr")
	)
	(MQIA_CONFIGURATION_EVENT, "ConfigurationEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQCA_CUSTOM, "Custom")
	(MQCA_DEAD_LETTER_Q_NAME, "DeadLetterQName")
#ifdef MQIA_DEF_CLUSTER_XMIT_Q_TYPE
	(MQIA_DEF_CLUSTER_XMIT_Q_TYPE, "DefClusterXmitQueueType", DisplayMapInitializer
		(MQCLXQ_SCTQ, "SCTQ")
		(MQCLXQ_CHANNEL, "Channel")
	)
#endif
	(MQCA_DEF_XMIT_Q_NAME, "DefXmitQName")
	(MQIA_DIST_LISTS, "DistLists", DisplayMapInitializer
		(MQDL_SUPPORTED, "Supported")
		(MQDL_NOT_SUPPORTED, "Not Supported")
	)
	(MQCA_DNS_GROUP, "DNSGroup")
	(MQIA_DNS_WLM, "DNSWLM", DisplayMapInitializer
		(MQDNSWLM_YES, "Yes")
		(MQDNSWLM_NO, "No")
	)
	(MQIA_SUITE_B_STRENGTH, "EncryptionPolicySuiteB", DisplayMapInitializer
		(MQ_SUITE_B_NONE, "None")
		(MQ_SUITE_B_128_BIT, "128 Bit")
		(MQ_SUITE_B_192_BIT, "192 Bit")
	)
	(MQIA_EXPIRY_INTERVAL, "ExpiryInterval")
	(MQIA_GROUP_UR, "GroupUR", DisplayMapInitializer
		(MQGUR_DISABLED, "Disabled")
		(MQGUR_ENABLED, "Enabled")
	)
	(MQIA_IGQ_PUT_AUTHORITY, "IGQPutAuthority", DisplayMapInitializer
		(MQIGQPA_DEFAULT, "Default")
		(MQIGQPA_CONTEXT, "Context")
		(MQIGQPA_ONLY_IGQ, "Only IGQ")
		(MQIGQPA_ALTERNATE_OR_IGQ, "Alternate or IGQ")
	)
	(MQCA_IGQ_USER_ID, "IGQUserId")
	(MQIA_INHIBIT_EVENT, "InhibitEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQIA_INTRA_GROUP_QUEUING, "IntraGroupQueueing", DisplayMapInitializer
		(MQIGQ_DISABLED, "Disabled")
		(MQIGQ_ENABLED, "Enabled")
	)
	(MQIA_IP_ADDRESS_VERSION, "IPAddressVersion", DisplayMapInitializer
		(MQIPADDR_IPV4, "IPV4")
		(MQIPADDR_IPV6, "IPV6")
	)
	(MQIA_LISTENER_TIMER, "ListenerTimer")
	(MQIA_LOCAL_EVENT, "LocalEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQIA_LOGGER_EVENT, "LoggerEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQCA_LU_GROUP_NAME, "LUGroupName")
	(MQCA_LU_NAME, "LUName")
	(MQCA_LU62_ARM_SUFFIX, "LU62ARMSuffix")
	(MQIA_LU62_CHANNELS, "LU62Channels")
	(MQIA_ACTIVE_CHANNELS, "MaxActiveChannels")
	(MQIA_MAX_CHANNELS, "MaxChannels")
	(MQIA_MAX_HANDLES, "MaxHandles")
	(MQIA_MAX_MSG_LENGTH, "MaxMsgLength")
	(MQIA_MAX_PRIORITY, "MaxPriority")
	(MQIA_MAX_PROPERTIES_LENGTH, "MaxPropertiesLength")
	(MQIA_MAX_UNCOMMITTED_MSGS, "MaxUncommitedMsgs")
	(MQIA_ACCOUNTING_MQI, "MQIAccounting", DisplayMapInitializer
		(MQMON_OFF, "Off")
		(MQMON_ON, "On")
	)
	(MQIA_STATISTICS_MQI, "MQIStatistics", DisplayMapInitializer
		(MQMON_OFF, "Off")
		(MQMON_ON, "On")
	)
	(MQIA_MSG_MARK_BROWSE_INTERVAL, "MsgMarkBrowseInterval")
	(MQIA_OUTBOUND_PORT_MAX, "OutBoundPortMax")
	(MQIA_OUTBOUND_PORT_MIN, "OutBoundPortMin")
	(MQCA_PARENT, "Parent")
	(MQIA_PERFORMANCE_EVENT, "LoggerEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQIA_PLATFORM, "Platform", DisplayMapInitializer
		(MQPL_UNIX, "UNIX")
		(MQPL_NSK, "Compaq NonStop Kernel")
		(MQPL_OS400, "i5/OS")
		(MQPL_VMS, "HP OpenVMS")
		(MQPL_WINDOWS_NT, "Windows")
		(MQPL_ZOS, "z/OS")
	)
#ifdef MQIA_PROT_POLICY_CAPABILITY
	(MQIA_PROT_POLICY_CAPABILITY, "SplCap", DisplayMapInitializer
		(MQCAP_SUPPORTED, "Supported")
		(MQCAP_NOT_SUPPORTED, "Not Supported")
	)
#endif
	(MQIA_PUBSUB_CLUSTER, "PubSubClus", DisplayMapInitializer
		(MQPSCLUS_ENABLED, "Enabled")
		(MQPSCLUS_DISABLED, "Disabled")
	)
	(MQIA_PUBSUB_MAXMSG_RETRY_COUNT, "PubSubMaxMsgRetryCount")
	(MQIA_PUBSUB_MODE, "PubSubMode", DisplayMapInitializer
		(MQPSM_COMPAT, "Compat")
		(MQPSM_DISABLED, "Disabled")
		(MQPSM_ENABLED, "Enabled")
	)
	(MQIA_PUBSUB_NP_MSG, "PubSubNPInputMsg", DisplayMapInitializer
		(MQUNDELIVERED_DISCARD, "Discard")
		(MQUNDELIVERED_KEEP, "Keep")
	)
	(MQIA_PUBSUB_NP_RESP, "PubSubNPResponse", DisplayMapInitializer
		(MQUNDELIVERED_NORMAL, "Normal")
		(MQUNDELIVERED_SAFE, "Safe")
		(MQUNDELIVERED_DISCARD, "Discard")
		(MQUNDELIVERED_KEEP, "Keep")
	)
	(MQIA_PUBSUB_SYNC_PT, "PubSubSyncPoiunt", DisplayMapInitializer
		(MQSYNCPOINT_IFPER, "IFPER")
		(MQSYNCPOINT_YES, "Yes")
	)
	(MQCA_Q_MGR_DESC, "QMgrDesc")
	(MQCA_Q_MGR_IDENTIFIER, "QMgrIdentifier")
	(MQCA_QSG_NAME, "QSGName")
	(MQIA_ACCOUNTING_Q, "QueueAccounting", DisplayMapInitializer
		(MQMON_NONE, "None")
		(MQMON_OFF, "Off")
		(MQMON_ON, "On")
	)
	(MQIA_MONITORING_Q, "QueueMonitoring", DisplayMapInitializer
		(MQMON_OFF, "Off")
		(MQMON_NONE, "None")
		(MQMON_LOW, "Low")
		(MQMON_MEDIUM, "Medium")
		(MQMON_HIGH, "High")
	)
	(MQIA_STATISTICS_Q, "QueueStatistics", DisplayMapInitializer
		(MQMON_NONE, "None")
		(MQMON_OFF, "Off")
		(MQMON_ON, "On")
	)
	(MQIA_RECEIVE_TIMEOUT, "ReceiveTimeout")
	(MQIA_RECEIVE_TIMEOUT_MIN, "ReceiveTimeoutMin")
	(MQIA_RECEIVE_TIMEOUT_TYPE, "ReceiveTimeoutType", DisplayMapInitializer
		(MQRCVTIME_MULTIPLY, "Multiply")
		(MQRCVTIME_ADD, "Add")
		(MQRCVTIME_EQUAL, "Equal")
	)
	(MQIA_REMOTE_EVENT, "RemoveEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQCA_REPOSITORY_NAME, "RepositoryName")
	(MQCA_REPOSITORY_NAMELIST, "RepositoryNamelist")
	(MQIA_SECURITY_CASE, "SecurityCase", DisplayMapInitializer
		(MQSCYC_UPPER, "Upper")
		(MQSCYC_MIXED, "Mixed")
	)
	(MQIA_SHARED_Q_Q_MGR_NAME, "SharedQQmgrName", DisplayMapInitializer
		(MQSQQM_USE, "Use")
		(MQSQQM_IGNORE, "Ignore")
	)
	(MQCA_SSL_CRL_NAMELIST, "SSLCRLNamelist")
	(MQCA_SSL_CRYPTO_HARDWARE, "SSLCryptoHardware")
	(MQIA_SSL_EVENT, "SSLEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQIA_SSL_FIPS_REQUIRED, "SSLFipsRequired", DisplayMapInitializer
		(MQSSL_FIPS_NO, "No")
		(MQSSL_FIPS_YES, "Yes")
	)
	(MQCA_SSL_KEY_REPOSITORY, "SSLKeyRepository")
	(MQIA_SSL_RESET_COUNT, "SSLKeyResetCount")
	(MQIA_SSL_TASKS, "SSLTasks")
	(MQIA_START_STOP_EVENT, "StartStopEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQIA_STATISTICS_INTERVAL, "StatisticsInterval")
	(MQIA_SYNCPOINT, "SyncPoint", DisplayMapInitializer
		(MQSP_AVAILABLE, "Available")
		(MQSP_NOT_AVAILABLE, "Not Available")
	)
	(MQIA_TCP_CHANNELS, "TCPChannels")
	(MQIA_TCP_KEEP_ALIVE, "TCPKeepAlive", DisplayMapInitializer
		(MQTCPKEEP_NO, "No")
		(MQTCPKEEP_YES, "Yes")
	)
	(MQCA_TCP_NAME, "TCPName")
	(MQIA_TCP_STACK_TYPE, "TCPStackType", DisplayMapInitializer
		(MQTCPSTACK_SINGLE, "Single")
		(MQTCPSTACK_MULTIPLE, "Multiple")
	)
	(MQIA_TRACE_ROUTE_RECORDING, "TraceRouteRecording", DisplayMapInitializer
		(MQRECORDING_DISABLED, "Disabled")
		(MQRECORDING_MSG, "Msg")
		(MQRECORDING_Q, "Q")
	)
	(MQIA_TREE_LIFE_TIME, "TreeLifeTime")
	(MQIA_TRIGGER_INTERVAL, "TriggerInterval")
	(MQCA_VERSION, "Version")
	(MQIA_XR_CAPABILITY, "XrCapability", DisplayMapInitializer
		(MQCAP_SUPPORTED, "Supported")
		(MQCAP_NOT_SUPPORTED, "Not Supported")
	)

	// QueueManager Status properties
	(MQIACF_CHINIT_STATUS, "ChannelInitiatorStatus", DisplayMapInitializer
		(MQSVC_STATUS_STOPPED, "Stopped")
		(MQSVC_STATUS_STARTING, "Starting")
		(MQSVC_STATUS_RUNNING, "Running")
		(MQSVC_STATUS_STOPPING, "Stopping")
		(MQSVC_STATUS_RETRYING, "Retrying")
	)
	(MQIACF_CMD_SERVER_STATUS, "CommandServerStatus", DisplayMapInitializer
		(MQSVC_STATUS_STOPPED, "Stopped")
		(MQSVC_STATUS_STARTING, "Starting")
		(MQSVC_STATUS_RUNNING, "Running")
		(MQSVC_STATUS_STOPPING, "Stopping")
		(MQSVC_STATUS_RETRYING, "Retrying")
	)
	(MQIACF_CONNECTION_COUNT, "ConnectionCount")
	(MQCACF_CURRENT_LOG_EXTENT_NAME, "CurrentLog")
	(MQCA_INSTALLATION_DESC, "InstallationDesc")
	(MQCA_INSTALLATION_NAME, "InstallationName")
	(MQCA_INSTALLATION_PATH, "InstallationPath")
	(MQCACF_LOG_PATH, "LogPath")
	(MQCACF_MEDIA_LOG_EXTENT_NAME, "MediaRecoveryLog")
	(MQIACF_Q_MGR_STATUS, "QMgrStatus", DisplayMapInitializer
		(MQQMSTA_STARTING, "Starting")
		(MQQMSTA_RUNNING, "Running")
		(MQQMSTA_QUIESCING, "Quiescing")
	)
	(MQCACF_RESTART_LOG_EXTENT_NAME, "RestartRecoveryLog")
	(MQCACF_Q_MGR_START_DATE, "StartDate")
	(MQCACF_Q_MGR_START_TIME, "StartTime")
	(MQIACF_PERMIT_STANDBY, "PermitStandby", DisplayMapInitializer
		(MQSTDBY_NOT_PERMITTED, "Not Permitted")
		(MQSTDBY_PERMITTED, "Permitted")
	)

	// QUEUE properties
	(MQCA_BACKOUT_REQ_Q_NAME, "BackoutRequeueName")
	(MQIA_BACKOUT_THRESHOLD, "BackoutThreshold")
	//(MQCA_BASE_Q_NAME, "BaseQName")
	(MQCA_BASE_OBJECT_NAME, "BaseObjectName")
	(MQCA_CF_STRUC_NAME, "CFStructure")
	(MQCA_CLUSTER_DATE, "ClusterDate")
	(MQCA_CLUSTER_TIME, "ClusterTime")
	(MQIA_CLUSTER_Q_TYPE, "ClusterQType", DisplayMapInitializer
		(MQCQT_LOCAL_Q, "Local")
		(MQCQT_ALIAS_Q, "Alias")
		(MQCQT_REMOTE_Q, "Remote")
		(MQCQT_Q_MGR_ALIAS, "Qmgr Alias")
	)
	(MQIA_CLWL_Q_PRIORITY, "CLWLQueuePriority")
	(MQIA_CLWL_Q_RANK, "CLWLQueueRank")
	(MQIA_CLWL_USEQ, "CLWLUseQ", DisplayMapInitializer
		(MQCLWL_USEQ_AS_Q_MGR, "Qmgr")
		(MQCLWL_USEQ_ANY, "Any")
		(MQCLWL_USEQ_LOCAL, "Local")
	)
	(MQIA_CURRENT_Q_DEPTH, "CurrentQDepth")
	(MQIA_DEF_PUT_RESPONSE_TYPE, "DefaultPutResponse", DisplayMapInitializer
		(MQPRT_SYNC_RESPONSE, "Sync")
		(MQPRT_ASYNC_RESPONSE, "Async")
	)
	(MQIA_DEF_BIND, "DefBind", DisplayMapInitializer
		(MQBND_BIND_ON_OPEN, "On Open")
		(MQBND_BIND_NOT_FIXED, "Not Fixed")
#ifdef MQBND_BIND_ON_GROUP
		(MQBND_BIND_ON_GROUP, "On Group")
#endif
	)
	(MQIA_DEFINITION_TYPE, "DefinitionType", DisplayMapInitializer
		(MQQDT_PREDEFINED, "Predefined")
		(MQQDT_PERMANENT_DYNAMIC, "Permanent Dynamically")
		(MQQDT_SHARED_DYNAMIC, "Shared Dynamic")
		(MQQDT_TEMPORARY_DYNAMIC, "Temporary Dynamic")
	)
	(MQIA_DEF_INPUT_OPEN_OPTION, "DefInputOpenOption", DisplayMapInitializer
		(MQOO_INPUT_EXCLUSIVE, "Exclusive")
		(MQOO_INPUT_SHARED, "Shared")
	)
	(MQIA_DEF_PERSISTENCE, "DefPersistence", DisplayMapInitializer
		(MQPER_PERSISTENT, "Persistent")
		(MQPER_NOT_PERSISTENT, "Not Persistent")
	)
	(MQIA_DEF_PRIORITY, "DefPriority")
	(MQIA_DEF_READ_AHEAD, "DefReadAhead", DisplayMapInitializer
		(MQREADA_NO, "No")
		(MQREADA_YES, "Yes")
		(MQREADA_DISABLED, "Disabled")
	)
	(MQIA_DIST_LISTS, "DistLists", DisplayMapInitializer
		(MQDL_SUPPORTED, "Supported")
		(MQDL_NOT_SUPPORTED, "Not Supported")
	)
	(MQIA_HARDEN_GET_BACKOUT, "HardenGetBackout", DisplayMapInitializer
		(MQQA_BACKOUT_HARDENED, "Hardened")
		(MQQA_BACKOUT_NOT_HARDENED, "Not Hardened")
	)
	(MQIA_INDEX_TYPE, "IndexType", DisplayMapInitializer
		(MQIT_NONE, "None")
		(MQIT_MSG_ID, "Message ID")
		(MQIT_CORREL_ID, "Correlation ID")
		(MQIT_MSG_TOKEN, "Message Token")
		(MQIT_GROUP_ID, "Group ID")
	)
	(MQIA_INHIBIT_GET, "InhibitGet", DisplayMapInitializer
		(MQQA_GET_ALLOWED, "Allowed")
		(MQQA_GET_INHIBITED, "Inhibited")
	)
	(MQIA_INHIBIT_PUT, "InhibitPut", DisplayMapInitializer
		(MQQA_PUT_ALLOWED, "Allowed")
		(MQQA_PUT_INHIBITED, "Inhibited")
	)
	(MQCA_INITIATION_Q_NAME, "InitiationQName")
	(MQIA_MAX_MSG_LENGTH, "MaxMsgLength")
	(MQIA_MAX_Q_DEPTH, "MaxQDepth")
	(MQIA_MSG_DELIVERY_SEQUENCE, "MsgDeliverySequence", DisplayMapInitializer
		(MQMDS_PRIORITY, "priority")
		(MQMDS_FIFO, "FIFO")
	)
	(MQIA_NPM_CLASS, "NonPersistentMessageClass", DisplayMapInitializer
		(MQNPM_CLASS_NORMAL, "Normal")
		(MQNPM_CLASS_HIGH, "High")
	)
	(MQIA_OPEN_INPUT_COUNT, "OpenInputCount")
	(MQIA_OPEN_OUTPUT_COUNT, "OpenOutputCount")
	(MQIA_PAGESET_ID, "PageSetID")
	(MQCA_PROCESS_NAME, "ProcessName")
	(MQIA_PROPERTY_CONTROL, "PropertyControl", DisplayMapInitializer
		(MQPROP_COMPATIBILITY, "Compatibility")
		(MQPROP_NONE, "None")
		(MQPROP_ALL, "All")
		(MQPROP_FORCE_MQRFH2, "Force MQRFH2")
	)
	(MQIA_Q_DEPTH_HIGH_EVENT, "QDepthHighEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQIA_Q_DEPTH_HIGH_LIMIT, "QDepthHighLimit")
	(MQIA_Q_DEPTH_LOW_EVENT, "QDepthLowEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQIA_Q_DEPTH_LOW_LIMIT, "QDepthLowLimit")
	(MQIA_Q_DEPTH_MAX_EVENT, "QDepthMaxEvent", DisplayMapInitializer
		(MQEVR_DISABLED, "Disabled")
		(MQEVR_ENABLED, "Enabled")
	)
	(MQCA_Q_DESC, "QDesc")
	(MQCA_Q_MGR_IDENTIFIER, "QMgrIdentifier")
	(MQCA_Q_NAME, "QName")
	(MQIA_Q_SERVICE_INTERVAL, "QServiceInterval")
	(MQIA_Q_SERVICE_INTERVAL_EVENT, "QServiceIntervalEvent", DisplayMapInitializer
		(MQQSIE_HIGH, "High")
		(MQQSIE_OK, "Ok")
		(MQQSIE_NONE, "None")
	)
	(MQIA_Q_TYPE, "QType", DisplayMapInitializer
		(MQQT_ALL, "All")
		(MQQT_LOCAL, "Local")
		(MQQT_ALIAS, "Alias")
		(MQQT_CLUSTER, "Cluster")
		(MQQT_MODEL, "Model")
		(MQQT_REMOTE, "Remote")
	)
	(MQIA_ACCOUNTING_Q, "QueueAccounting", DisplayMapInitializer
		(MQMON_Q_MGR, "Qmgr")
		(MQMON_OFF, "Off")
		(MQMON_ON, "On")
	)
	(MQIA_MONITORING_Q, "QueueMonitoring", DisplayMapInitializer
		(MQMON_Q_MGR, "Qmgr")
		(MQMON_OFF, "Off")
		(MQMON_LOW, "Low")
		(MQMON_MEDIUM, "Medium")
		(MQMON_HIGH, "High")
	)
	(MQIA_STATISTICS_Q, "QueueStatistics", DisplayMapInitializer
		(MQMON_Q_MGR, "Qmgr")
		(MQMON_OFF, "Off")
		(MQMON_ON, "On")
	)
	(MQCA_REMOTE_Q_MGR_NAME, "RemoteQmgrName")
	(MQCA_REMOTE_Q_NAME, "RemoteQName")
	(MQIA_RETENTION_INTERVAL, "RetentionInterval")
	(MQIA_SCOPE, "Scope", DisplayMapInitializer
		(MQSCO_Q_MGR, "Qmgr")
		(MQSCO_CELL, "Cell")
	)
	(MQIA_SHAREABILITY, "Shareability", DisplayMapInitializer
		(MQQA_SHAREABLE, "Shareable")
		(MQQA_NOT_SHAREABLE, "Not Shareable")
	)
	(MQCA_STORAGE_CLASS, "StorageClass")
	(MQCA_TPIPE_NAME, "TpipeNames")
	(MQIA_TRIGGER_CONTROL, "TriggerControl", DisplayMapInitializer
		(MQTC_OFF, "Off")
		(MQTC_ON, "On")
	)
	(MQCA_TRIGGER_DATA, "TriggerData")
	(MQIA_TRIGGER_DEPTH, "TriggerDepth")
	(MQIA_TRIGGER_MSG_PRIORITY, "TriggerMsgPriority")
	(MQIA_TRIGGER_TYPE, "TriggerType", DisplayMapInitializer
		(MQTT_NONE, "None")
		(MQTT_FIRST, "First")
		(MQTT_EVERY, "Every")
		(MQTT_DEPTH, "Depth")
	)
	(MQIA_USAGE, "Usage", DisplayMapInitializer
		(MQUS_NORMAL, "Normal")
		(MQUS_TRANSMISSION, "Transmission")
	)
	(MQCA_XMIT_Q_NAME, "XmitQName")

	// Channel properties

	(MQIACH_BATCH_HB, "BatchHeartBeat")
	(MQIACH_BATCH_INTERVAL, "BatchInterval")
#ifdef MQIACH_BATCH_DATA_LIMIT
	(MQIACH_BATCH_DATA_LIMIT, "BatchDataLimit")
#endif
	(MQIACH_BATCH_SIZE, "BatchSize")
	(MQCACH_DESC, "ChannelDesc")
	(MQIA_MONITORING_CHANNEL, "ChannelMonitoring", DisplayMapInitializer
		(MQMON_OFF, "Off")
		(MQMON_Q_MGR, "Qmgr")
		(MQMON_LOW, "Low")
		(MQMON_MEDIUM, "Medium")
		(MQMON_HIGH, "High")
	)
	(MQCACH_CHANNEL_NAME, "ChannelName")
	(MQCACH_CHANNEL_START_DATE, "ChannelStartDate")
	(MQCACH_CHANNEL_START_TIME, "ChannelStartTime")
	(MQIA_STATISTICS_CHANNEL, "ChannelStatistics", DisplayMapInitializer
		(MQMON_OFF, "Off")
		(MQMON_Q_MGR, "Qmgr")
		(MQMON_LOW, "Low")
		(MQMON_MEDIUM, "Medium")
		(MQMON_HIGH, "High")
	)
	(MQIACH_CHANNEL_TYPE, "ChannelType", DisplayMapInitializer
		(MQCHT_ALL, "All")
		(MQCHT_SENDER, "Sender")
		(MQCHT_SERVER, "Server")
		(MQCHT_RECEIVER, "Receiver")
		(MQCHT_REQUESTER, "Requester")
		(MQCHT_SVRCONN, "Server-connection")
		(MQCHT_CLNTCONN, "Client-connection")
		(MQCHT_CLUSRCVR, "Cluster-receiver")
		(MQCHT_CLUSSDR, "Cluster-sender")
#ifdef MQCHT_MQTT
		(MQCHT_MQTT, "Telemetry")
#endif
	)
	(MQIACH_CLIENT_CHANNEL_WEIGHT, "ClientChannelWeight")
#ifdef MQCACH_CLIENT_ID
	(MQCACH_CLIENT_ID, "ClientIdentifier")
#endif
	(MQIACH_CLWL_CHANNEL_PRIORITY, "CLWLChannelPriority")
	(MQIACH_CLWL_CHANNEL_RANK, "CLWLChannelRank")
	(MQIACH_CLWL_CHANNEL_WEIGHT, "CLWLChannelWeight")
	(MQIACH_CONNECTION_AFFINITY, "ConnectionAffinity", DisplayMapInitializer
		(MQCAFTY_PREFERRED, "Preferred")
		(MQCAFTY_NONE, "None")
	)
	(MQCACH_CONNECTION_NAME, "ConnectionName")
	(MQIACH_DATA_CONVERSION, "DataConversion", DisplayMapInitializer
		(MQCDC_NO_SENDER_CONVERSION, "No")
		(MQCDC_SENDER_CONVERSION, "Sender")
	)
	(MQIACH_CHANNEL_DISP, "DefaultChannelDisposition", DisplayMapInitializer
		(MQCHLD_ALL, "All")
		(MQCHLD_PRIVATE, "Private")
		(MQCHLD_FIXSHARED, "Fix Shared")
		(MQCHLD_SHARED, "Shared")
	)
	(MQIACH_DISC_INTERVAL, "DiscInterval")
#ifdef MQIACH_DEF_RECONNECT
	(MQIACH_DEF_RECONNECT, "DefReconnect", DisplayMapInitializer
		(MQRCN_NO, "No")
		(MQRCN_YES, "Yes")
		(MQRCN_Q_MGR, "Qmgr")
		(MQRCN_DISABLED, "Disabled")
	)
#endif
	(MQIACH_HDR_COMPRESSION, "HeaderCompression", DisplayMapInitializer
		(MQCOMPRESS_NONE, "None")
		(MQCOMPRESS_SYSTEM, "System")
		(MQCOMPRESS_NOT_AVAILABLE, "Not Available")
		(MQCOMPRESS_RLE, "RLE")
		(MQCOMPRESS_ZLIBFAST, "Zlib Fast")
		(MQCOMPRESS_ZLIBHIGH, "Zlib High")
		(MQCOMPRESS_ANY, "Any")
		(MQCOMPRESS_SYSTEM, "System")
	)
	(MQIACH_HB_INTERVAL, "HeartbeatInterval")
#ifdef MQIACH_IN_DOUBT
	(MQIACH_IN_DOUBT, "InDoubt")
#endif
#ifdef MQIACH_IN_DOUBT_IN
	(MQIACH_IN_DOUBT_IN, "InDoubtInbound")
#endif
#ifdef MQIACH_IN_DOUBT_OUT
	(MQIACH_IN_DOUBT_OUT, "InDoubtOutbound")
#endif
	(MQIACH_KEEP_ALIVE_INTERVAL, "KeepAliveInterval")
	(MQCACH_LAST_MSG_DATE, "LastMsgDate")
	(MQCACH_LAST_MSG_TIME, "LastMsgTime")
	(MQCACH_LOCAL_ADDRESS, "LocalAddress")
	(MQIACH_LONG_RETRY, "LongRetryCount")
	(MQIACH_LONG_TIMER, "LongRetryInterval")
	(MQIACH_MAX_INSTANCES, "MaxInstances")
	(MQIACH_MAX_INSTS_PER_CLIENT, "MaxInstancesPerClient")
	(MQIACH_MAX_MSG_LENGTH, "MaxMsgLength")
	(MQCACH_MCA_NAME, "MCAName")
	(MQIACH_MCA_TYPE, "MCAType", DisplayMapInitializer
		(MQMCAT_PROCESS, "Process")
		(MQMCAT_THREAD, "Thread")
	)
	(MQCACH_MCA_USER_ID, "MCAUserIdentifier")
	(MQIACH_MSG_COMPRESSION, "MessageCompression", DisplayMapInitializer
		(MQCOMPRESS_NONE, "None")
		(MQCOMPRESS_RLE, "RLE")
		(MQCOMPRESS_ZLIBFAST, "Zlib Fast")
		(MQCOMPRESS_ZLIBHIGH, "Zlib High")
		(MQCOMPRESS_ANY, "Any")
	)
	(MQCACH_MODE_NAME, "ModeName")
	(MQCACH_MSG_EXIT_NAME, "MsgExit")
#ifdef MQIACH_MSGS_RECEIVED
	(MQIACH_MSGS_RECEIVED, "MsgsReceived")
#endif
	(MQIACH_MR_COUNT, "MsgRetryCount")
	(MQCACH_MR_EXIT_NAME, "MsgRetryExit")
	(MQIACH_MR_INTERVAL, "MsgRetryInterval")
	(MQCACH_MR_EXIT_USER_DATA, "MsgRetryUserData")
#ifdef MQIACH_MSGS
	(MQIACH_MSGS, "Msgs")
#endif
#ifdef MQIACH_MSGS_SENT
	(MQIACH_MSGS_SENT, "MsgsSent")
#endif
	(MQCACH_MSG_EXIT_USER_DATA, "MsgUserData")
	(MQIACH_NETWORK_PRIORITY, "NetworkPriority")
	(MQIACH_NPM_SPEED, "NonPersistentMsgSpeed", DisplayMapInitializer
		(MQNPMS_FAST, "Fast")
		(MQNPMS_NORMAL, "Normal")
	)
	(MQCACH_PASSWORD, "Password")
	(MQIA_PROPERTY_CONTROL, "PropertyControl", DisplayMapInitializer
		(MQPROP_COMPATIBILITY, "Compatibility")
		(MQPROP_NONE, "None")
		(MQPROP_ALL, "All")
	)
	(MQIACH_PUT_AUTHORITY, "PutAuthority", DisplayMapInitializer
		(MQPA_DEFAULT, "Default")
		(MQPA_CONTEXT, "Context")
	)
	(MQCACH_RCV_EXIT_NAME, "ReceiveExit")
	(MQCACH_RCV_EXIT_USER_DATA, "ReceiveUserData")
	(MQCACH_SEC_EXIT_NAME, "SecurityExit")
	(MQCACH_SEC_EXIT_USER_DATA, "SecurityUserData")
	(MQCACH_SEND_EXIT_NAME, "SendExit")
	(MQCACH_SEND_EXIT_USER_DATA, "SendUserData")
	(MQIACH_SEQUENCE_NUMBER_WRAP, "SeqNumberWrap")
	(MQIACH_SHARING_CONVERSATIONS, "SharingConversations")
	(MQIACH_SHORT_RETRY, "ShortRetryCount")
	(MQIACH_SHORT_TIMER, "ShortRetryInterval")
	(MQCACH_SSL_CIPHER_SPEC, "SSLCipherSpec")
	(MQIACH_SSL_CLIENT_AUTH, "SSLClientAuth", DisplayMapInitializer
		(MQSCA_REQUIRED, "Required")
		(MQSCA_OPTIONAL, "Optional")
	)
	(MQCACH_SSL_PEER_NAME, "SSLPeerName")
	(MQCACH_TP_NAME, "TpName")
	(MQIACH_XMIT_PROTOCOL_TYPE, "TransportType", DisplayMapInitializer
		(MQXPT_LU62, "LU62")
		(MQXPT_TCP, "TCP")
		(MQXPT_NETBIOS, "NetBIOS")
		(MQXPT_SPX, "SPX")
		(MQXPT_DECNET, "DECnet")
	)
#ifdef MQIA_USE_DEAD_LETTER_Q
	(MQIA_USE_DEAD_LETTER_Q, "UseDLQ", DisplayMapInitializer
		(MQUSEDLQ_NO, "No")
		(MQUSEDLQ_YES, "Yes")
	)
#endif
	(MQCACH_USER_ID, "UserIdentifier")
	(MQCACH_XMIT_Q_NAME, "XmitQName")

	// Channel Status Properties
	(MQIACH_BATCHES, "Batches")
	(MQIACH_BATCH_SIZE_INDICATOR, "BatchSizeIndicator")
	(MQIACH_BUFFERS_RCVD, "BuffersReceived")
	(MQIACH_BUFFERS_SENT, "BuffersSent")
	(MQIACH_BYTES_RECEIVED, "BytesReceived")
	(MQIACH_BYTES_SENT, "BytesSent")
	(MQIACH_CHANNEL_INSTANCE_TYPE, "ChannelInstanceType", DisplayMapInitializer
		(MQOT_CURRENT_CHANNEL, "Current")
		(MQOT_SAVED_CHANNEL, "Saved")
		(MQOT_SHORT_CHANNEL, "Short")
	)
	(MQIACH_CHANNEL_STATUS, "ChannelStatus", DisplayMapInitializer
		(MQCHS_BINDING, "Binding")
		(MQCHS_STARTING, "Starting")
		(MQCHS_RUNNING, "Running")
		(MQCHS_PAUSED, "Paused")
		(MQCHS_STOPPING, "Stopping")
		(MQCHS_STOPPED, "Stopped")
		(MQCHS_RETRYING, "Retrying")
		(MQCHS_REQUESTING, "Requesting")
		(MQCHS_INITIALIZING, "Initializing")
		(MQCHS_INACTIVE, "Inactive")
	)
	(MQIACH_COMPRESSION_RATE, "CompressionRate")
	(MQIACH_COMPRESSION_TIME, "CompressionTime")
	(MQCACH_CURRENT_LUWID, "CurrentLUWID")
	(MQIACH_CURRENT_MSGS, "CurrentMsgs")
	(MQIACH_CURRENT_SEQ_NUMBER, "CurrentSequenceNumber")
	(MQIACH_CURRENT_SHARING_CONVS, "CurrentSharingConverstations")
	(MQIACH_EXIT_TIME_INDICATOR, "ExitTime")
	(MQIACH_INDOUBT_STATUS, "InDoubtStatus", DisplayMapInitializer
		(MQCHIDS_NOT_INDOUBT, "Not Indoubt")
		(MQCHIDS_INDOUBT, "Indoubt")
	)
	(MQCACH_LAST_LUWID, "LastLUWID")
	(MQIACH_LAST_SEQ_NUMBER, "LastSequenceNumber")
	(MQIACH_LONG_RETRIES_LEFT, "LongRetriesLeft")
	(MQIACH_MAX_SHARING_CONVS, "MaxSharingConversations")
	(MQCACH_MCA_JOB_NAME, "MCAJobName")
	(MQIACH_MCA_STATUS, "MCAStatus", DisplayMapInitializer
		(MQMCAS_STOPPED, "Stopped")
		(MQMCAS_RUNNING, "Running")
	)
	(MQIACH_XMITQ_MSGS_AVAILABLE, "MsgsAvailable")
	(MQIACH_NETWORK_TIME_INDICATOR, "NetTime")
	(MQCACH_REMOTE_APPL_TAG, "RemoteApplTag")
#ifdef MQCACH_REMOTE_PRODUCT
	(MQCACH_REMOTE_PRODUCT, "RemoteProduct", DisplayMapInitializer
#ifdef MQMM
		(MQMM, "Queue Manager (non z/OS Platform")
#endif
#ifdef MQMV
		(MQMV, "Queue Manager on z/OS")
#endif
#ifdef MQCC
		(MQCC, "WebSphere MQ C client")
#endif
#ifdef MQNM
		(MQNM, "WebSphere MQ .NET fully managed client")
#endif
#ifdef MQJB
		(MQJB, "WebSphere MQ Classes for JAVA")
#endif
#ifdef MQJN
		(MQJN, "WebSphere MQ Classes for JMS (normal mode)")
#endif
#ifdef MQJM
		(MQJM, "WebSphere MQ Classes for JMS (migration mode)")
#endif
#ifdef MQJU
		(MQJU, "Common Java interface to the MQI")
#endif
#ifdef MQXC
		(MQXC, "XMS client C/C++ (normal mode)")
#endif
#ifdef MQXD
		(MQXD, "XMS client C/C++ (migration mode)")
#endif
#ifdef MQXN
		(MQXN, "XMS client .NET (normal mode)")
#endif
#ifdef MQXM
		(MQXM, "XMS client .NET (migration mode)")
#endif
		(0, "")
	)
#endif
#ifdef MQCACH_REMOTE_VERSION
	(MQCACH_REMOTE_VERSION, "RemoteVersion")
#endif
	(MQCACH_SSL_CERT_ISSUER_NAME, "SSLCertRemoteIssuerName")
	(MQCACH_SSL_CERT_USER_ID, "SSLCertUserId")
	(MQCACH_SSL_KEY_RESET_DATE, "SSLKeyResetDate")
	(MQIACH_SSL_KEY_RESETS, "SSLKeyResets")
	(MQCACH_SSL_KEY_RESET_TIME, "SSLKeyResetTime")
	(MQCACH_SSL_SHORT_PEER_NAME, "SSLShortPeerName")
	(MQIACH_STOP_REQUESTED, "StopRequested", DisplayMapInitializer
		(MQCHSR_STOP_NOT_REQUESTED, "Stop Not Requested")
		(MQCHSR_STOP_REQUESTED, "Stop Requested")
	)
	(MQIACH_CHANNEL_SUBSTATE, "SubState", DisplayMapInitializer
#ifdef MQCHSSTATE_CHADEXIT
		(MQCHSSTATE_CHADEXIT, "Running Channel Auto-definition Exit")
#endif
		(MQCHSSTATE_COMPRESSING, "Compressing")
		(MQCHSSTATE_END_OF_BATCH, "End Of Batch")
#ifdef MQCHSSTATE_HANDSHAKING
		(MQCHSSTATE_HANDSHAKING, "SSL Handshaking")
#endif
		(MQCHSSTATE_HEARTBEATING, "Heartbeating")
		(MQCHSSTATE_IN_MQGET, "MQQET")
		(MQCHSSTATE_IN_MQI_CALL, "MQ API Call")
		(MQCHSSTATE_IN_MQPUT, "MQPUT")
#ifdef MQCHSSTATE_MREXIT
		(MQCHSSTATE_MREXIT, "Retry Exit")
#endif
		(MQCHSSTATE_IN_MSGEXIT, "Message Exit")
		(MQCHSSTATE_NAME_SERVER, "Name Server")
		(MQCHSSTATE_NET_CONNECTING, "Network Connect")
		(MQCHSSTATE_OTHER, "Other")
		(MQCHSSTATE_IN_RCVEXIT, "Receive Exit")
		(MQCHSSTATE_RECEIVING, "Receiving")
		(MQCHSSTATE_RESYNCHING, "Resynching")
		(MQCHSSTATE_IN_SCYEXIT, "Security Exit")
		(MQCHSSTATE_IN_SENDEXIT, "Send Exit")
		(MQCHSSTATE_SENDING, "Sending")
		(MQCHSSTATE_SERIALIZING, "Serializing")
	)
	(MQIACH_XMITQ_TIME_INDICATOR, "XQTime")

	// Connection Properties
	(MQIA_APPL_TYPE, "ApplType", DisplayMapInitializer
		(MQAT_UNKNOWN, "Unknown")
		(MQAT_NO_CONTEXT, "No Context")
		(MQAT_CICS, "CICS Transaction")
		(MQAT_MVS, "Z/OS")
		(MQAT_IMS, "IMS Transaction")
		(MQAT_OS2, "OS/2")
		(MQAT_DOS, "DOS")
		(MQAT_UNIX, "Unix")
		(MQAT_QMGR, "QueueManager Process")
		(MQAT_OS400, "OS/400")
		(MQAT_WINDOWS, "Windows")
		(MQAT_CICS_VSE, "CICS VSE")
		(MQAT_WINDOWS_NT, "Windows NT")
		(MQAT_VMS, "VMS")
		(MQAT_GUARDIAN, "Guardian")
		(MQAT_NSK, "NSK")
		(MQAT_VOS, "VOS")
		(MQAT_OPEN_TP1, "Open TP1")
		(MQAT_VM, "VM")
		(MQAT_IMS_BRIDGE, "IMS Bridge")
		(MQAT_XCF, "XCF")
		(MQAT_CICS_BRIDGE, "CICS Bridge")
		(MQAT_NOTES_AGENT, "Notes Agent")
		(MQAT_TPF, "TPF")
		(MQAT_USER, "User Application")
		(MQAT_BROKER, "Broker")
		(MQAT_JAVA, "Java")
		(MQAT_DQM, "DQM")
		(MQAT_CHANNEL_INITIATOR, "Channel Initiator")
		(MQAT_WLM, "WLM")
		(MQAT_BATCH, "Batch Application")
		(MQAT_RRS_BATCH, "RRS-coordinated Batch Application")
		(MQAT_SIB, "SIB")
		(MQAT_SYSTEM_EXTENSION, "System Extension")
	)
	(MQCACF_USER_IDENTIFIER, "UserIdentifier")
	(MQCACF_APPL_NAME, "ApplName")
	(MQCACF_OBJECT_Q_MGR_NAME, "ObjectQMgrName")

	// Process Properties
	(MQCA_PROCESS_NAME, "ProcessName")

	// Topic Properties
	(MQCA_TOPIC_STRING, "TopicString")
	(MQCA_ADMIN_TOPIC_NAME, "AdminTopicNames")

	// Namelist Properties
	(MQCA_NAMELIST_NAME, "NamelistName")

	// Event Properties
	(MQIACF_REASON_QUALIFIER, "ReasonQualifier", DisplayMapInitializer
		(MQRQ_CONN_NOT_AUTHORIZED, "Conn Not Authorized")
		(MQRQ_OPEN_NOT_AUTHORIZED, "Open Not Authorized")
		(MQRQ_CLOSE_NOT_AUTHORIZED, "Close Not Authorized")
		(MQRQ_CMD_NOT_AUTHORIZED, "Cmd Not Authorized")
		(MQRQ_Q_MGR_STOPPING, "Qmgr Stopping")
		(MQRQ_Q_MGR_QUIESCING, "Qmgr Quiescing")
		(MQRQ_CHANNEL_STOPPED_OK, "Channel Stopped OK")
		(MQRQ_CHANNEL_STOPPED_ERROR, "Channel Stopped Error")
		(MQRQ_CHANNEL_STOPPED_RETRY, "Channel Stopped Retry")
		(MQRQ_CHANNEL_STOPPED_DISABLED, "Channel Stopped Disabled")
		(MQRQ_BRIDGE_STOPPED_OK, "Bridge Stopped OK")
		(MQRQ_BRIDGE_STOPPED_ERROR, "Bridge Stopped Error")
		(MQRQ_SSL_HANDSHAKE_ERROR, "SSL Handshake Error")
		(MQRQ_SSL_CIPHER_SPEC_ERROR, "SSL Cipher Spec Error")
		(MQRQ_SSL_CLIENT_AUTH_ERROR, "SSL Client Auth Error")
		(MQRQ_SSL_PEER_NAME_ERROR, "SSL Peer Name Error")
		(MQRQ_SUB_NOT_AUTHORIZED, "Sub Not Authorized")
		(MQRQ_SUB_DEST_NOT_AUTHORIZED, "Sub Dest Not Authorized")
		(MQRQ_SSL_UNKNOWN_REVOCATION, "SSL Unknown Revocation")
		(MQRQ_SYS_CONN_NOT_AUTHORIZED, "SyS Conn Not Authorized")
		(MQRQ_CHANNEL_BLOCKED_ADDRESS, "Channel Blocked Address")
		(MQRQ_CHANNEL_BLOCKED_USERID, "Channel Blocked Userid")
		(MQRQ_CHANNEL_BLOCKED_NOACCESS, "Channel Blocked NoAccess")
		(MQRQ_MAX_ACTIVE_CHANNELS, "Max Active Channels")
		(MQRQ_MAX_CHANNELS, "Max Channels")
		(MQRQ_SVRCONN_INST_LIMIT, "SvrConn Inst Limit")
		(MQRQ_CLIENT_INST_LIMIT, "Client Inst Limit")
		(MQRQ_CAF_NOT_INSTALLED, "CAF Not Installed")
	)
	// Bridge Events
	(MQIACF_BRIDGE_TYPE, "BridgeType", DisplayMapInitializer
		(MQBT_OTMA, "OTMA")
	)
	(MQCACF_BRIDGE_NAME, "BridgeName")
;

#define RCSTR(x) (x, #x)

DisplayMap MQMapper::_reasonCodes = DisplayMapInitializer
	RCSTR(MQRC_NONE                      )
	RCSTR(MQRC_APPL_FIRST                )
	RCSTR(MQRC_APPL_LAST                 )
	RCSTR(MQRC_ALIAS_BASE_Q_TYPE_ERROR   )
	RCSTR(MQRC_ALREADY_CONNECTED         )
	RCSTR(MQRC_BACKED_OUT                )
	RCSTR(MQRC_BUFFER_ERROR              )
	RCSTR(MQRC_BUFFER_LENGTH_ERROR       )
	RCSTR(MQRC_CHAR_ATTR_LENGTH_ERROR    )
	RCSTR(MQRC_CHAR_ATTRS_ERROR          )
	RCSTR(MQRC_CHAR_ATTRS_TOO_SHORT      )
	RCSTR(MQRC_CONNECTION_BROKEN         )
	RCSTR(MQRC_DATA_LENGTH_ERROR         )
	RCSTR(MQRC_DYNAMIC_Q_NAME_ERROR      )
	RCSTR(MQRC_ENVIRONMENT_ERROR         )
	RCSTR(MQRC_EXPIRY_ERROR              )
	RCSTR(MQRC_FEEDBACK_ERROR            )
	RCSTR(MQRC_GET_INHIBITED             )
	RCSTR(MQRC_HANDLE_NOT_AVAILABLE      )
	RCSTR(MQRC_HCONN_ERROR               )
	RCSTR(MQRC_HOBJ_ERROR                )
	RCSTR(MQRC_INHIBIT_VALUE_ERROR       )
	RCSTR(MQRC_INT_ATTR_COUNT_ERROR      )
	RCSTR(MQRC_INT_ATTR_COUNT_TOO_SMALL  )
	RCSTR(MQRC_INT_ATTRS_ARRAY_ERROR     )
	RCSTR(MQRC_SYNCPOINT_LIMIT_REACHED   )
	RCSTR(MQRC_MAX_CONNS_LIMIT_REACHED   )
	RCSTR(MQRC_MD_ERROR                  )
	RCSTR(MQRC_MISSING_REPLY_TO_Q        )
	RCSTR(MQRC_MSG_TYPE_ERROR            )
	RCSTR(MQRC_MSG_TOO_BIG_FOR_Q         )
	RCSTR(MQRC_MSG_TOO_BIG_FOR_Q_MGR     )
	RCSTR(MQRC_NO_MSG_AVAILABLE          )
	RCSTR(MQRC_NO_MSG_UNDER_CURSOR       )
	RCSTR(MQRC_NOT_AUTHORIZED            )
	RCSTR(MQRC_NOT_OPEN_FOR_BROWSE       )
	RCSTR(MQRC_NOT_OPEN_FOR_INPUT        )
	RCSTR(MQRC_NOT_OPEN_FOR_INQUIRE      )
	RCSTR(MQRC_NOT_OPEN_FOR_OUTPUT       )
	RCSTR(MQRC_NOT_OPEN_FOR_SET          )
	RCSTR(MQRC_OBJECT_CHANGED            )
	RCSTR(MQRC_OBJECT_IN_USE             )
	RCSTR(MQRC_OBJECT_TYPE_ERROR         )
	RCSTR(MQRC_OD_ERROR                  )
	RCSTR(MQRC_OPTION_NOT_VALID_FOR_TYPE )
	RCSTR(MQRC_OPTIONS_ERROR             )
	RCSTR(MQRC_PERSISTENCE_ERROR         )
	RCSTR(MQRC_PERSISTENT_NOT_ALLOWED    )
	RCSTR(MQRC_PRIORITY_EXCEEDS_MAXIMUM  )
	RCSTR(MQRC_PRIORITY_ERROR            )
	RCSTR(MQRC_PUT_INHIBITED             )
	RCSTR(MQRC_Q_DELETED                 )
	RCSTR(MQRC_Q_FULL                    )
	RCSTR(MQRC_Q_NOT_EMPTY               )
	RCSTR(MQRC_Q_SPACE_NOT_AVAILABLE     )
	RCSTR(MQRC_Q_TYPE_ERROR              )
	RCSTR(MQRC_Q_MGR_NAME_ERROR          )
	RCSTR(MQRC_Q_MGR_NOT_AVAILABLE       )
	RCSTR(MQRC_REPORT_OPTIONS_ERROR      )
	RCSTR(MQRC_SECOND_MARK_NOT_ALLOWED   )
	RCSTR(MQRC_SECURITY_ERROR            )
	RCSTR(MQRC_SELECTOR_COUNT_ERROR      )
	RCSTR(MQRC_SELECTOR_LIMIT_EXCEEDED   )
	RCSTR(MQRC_SELECTOR_ERROR            )
	RCSTR(MQRC_SELECTOR_NOT_FOR_TYPE     )
	RCSTR(MQRC_SIGNAL_OUTSTANDING        )
	RCSTR(MQRC_SIGNAL_REQUEST_ACCEPTED   )
	RCSTR(MQRC_STORAGE_NOT_AVAILABLE     )
	RCSTR(MQRC_SYNCPOINT_NOT_AVAILABLE   )
	RCSTR(MQRC_TRIGGER_CONTROL_ERROR     )
	RCSTR(MQRC_TRIGGER_DEPTH_ERROR       )
	RCSTR(MQRC_TRIGGER_MSG_PRIORITY_ERR  )
	RCSTR(MQRC_TRIGGER_TYPE_ERROR        )
	RCSTR(MQRC_TRUNCATED_MSG_ACCEPTED    )
	RCSTR(MQRC_TRUNCATED_MSG_FAILED      )
	RCSTR(MQRC_UNKNOWN_ALIAS_BASE_Q      )
	RCSTR(MQRC_UNKNOWN_OBJECT_NAME       )
	RCSTR(MQRC_UNKNOWN_OBJECT_Q_MGR      )
	RCSTR(MQRC_UNKNOWN_REMOTE_Q_MGR      )
	RCSTR(MQRC_WAIT_INTERVAL_ERROR       )
	RCSTR(MQRC_XMIT_Q_TYPE_ERROR         )
	RCSTR(MQRC_XMIT_Q_USAGE_ERROR        )
	RCSTR(MQRC_NOT_OPEN_FOR_PASS_ALL     )
	RCSTR(MQRC_NOT_OPEN_FOR_PASS_IDENT   )
	RCSTR(MQRC_NOT_OPEN_FOR_SET_ALL      )
	RCSTR(MQRC_NOT_OPEN_FOR_SET_IDENT    )
	RCSTR(MQRC_CONTEXT_HANDLE_ERROR      )
	RCSTR(MQRC_CONTEXT_NOT_AVAILABLE     )
	RCSTR(MQRC_SIGNAL1_ERROR             )
	RCSTR(MQRC_OBJECT_ALREADY_EXISTS     )
	RCSTR(MQRC_OBJECT_DAMAGED            )
	RCSTR(MQRC_RESOURCE_PROBLEM          )
	RCSTR(MQRC_ANOTHER_Q_MGR_CONNECTED   )
	RCSTR(MQRC_UNKNOWN_REPORT_OPTION     )
	RCSTR(MQRC_STORAGE_CLASS_ERROR       )
	RCSTR(MQRC_COD_NOT_VALID_FOR_XCF_Q   )
	RCSTR(MQRC_XWAIT_CANCELED            )
	RCSTR(MQRC_XWAIT_ERROR               )
	RCSTR(MQRC_SUPPRESSED_BY_EXIT        )
	RCSTR(MQRC_FORMAT_ERROR              )
	RCSTR(MQRC_SOURCE_CCSID_ERROR        )
	RCSTR(MQRC_SOURCE_INTEGER_ENC_ERROR  )
	RCSTR(MQRC_SOURCE_DECIMAL_ENC_ERROR  )
	RCSTR(MQRC_SOURCE_FLOAT_ENC_ERROR    )
	RCSTR(MQRC_TARGET_CCSID_ERROR        )
	RCSTR(MQRC_TARGET_INTEGER_ENC_ERROR  )
	RCSTR(MQRC_TARGET_DECIMAL_ENC_ERROR  )
	RCSTR(MQRC_TARGET_FLOAT_ENC_ERROR    )
	RCSTR(MQRC_NOT_CONVERTED             )
	RCSTR(MQRC_CONVERTED_MSG_TOO_BIG     )
	RCSTR(MQRC_TRUNCATED                 )
	RCSTR(MQRC_NO_EXTERNAL_PARTICIPANTS  )
	RCSTR(MQRC_PARTICIPANT_NOT_AVAILABLE )
	RCSTR(MQRC_OUTCOME_MIXED             )
	RCSTR(MQRC_OUTCOME_PENDING           )
	RCSTR(MQRC_BRIDGE_STARTED            )
	RCSTR(MQRC_BRIDGE_STOPPED            )
	RCSTR(MQRC_ADAPTER_STORAGE_SHORTAGE  )
	RCSTR(MQRC_UOW_IN_PROGRESS           )
	RCSTR(MQRC_ADAPTER_CONN_LOAD_ERROR   )
	RCSTR(MQRC_ADAPTER_SERV_LOAD_ERROR   )
	RCSTR(MQRC_ADAPTER_DEFS_ERROR        )
	RCSTR(MQRC_ADAPTER_DEFS_LOAD_ERROR   )
	RCSTR(MQRC_ADAPTER_CONV_LOAD_ERROR   )
	RCSTR(MQRC_BO_ERROR                  )
	RCSTR(MQRC_DH_ERROR                  )
	RCSTR(MQRC_MULTIPLE_REASONS          )
	RCSTR(MQRC_OPEN_FAILED               )
	RCSTR(MQRC_ADAPTER_DISC_LOAD_ERROR   )
	RCSTR(MQRC_CNO_ERROR                 )
	RCSTR(MQRC_CICS_WAIT_FAILED          )
	RCSTR(MQRC_DLH_ERROR                 )
	RCSTR(MQRC_HEADER_ERROR              )
	RCSTR(MQRC_SOURCE_LENGTH_ERROR       )
	RCSTR(MQRC_TARGET_LENGTH_ERROR       )
	RCSTR(MQRC_SOURCE_BUFFER_ERROR       )
	RCSTR(MQRC_TARGET_BUFFER_ERROR       )
	RCSTR(MQRC_IIH_ERROR                 )
	RCSTR(MQRC_PCF_ERROR                 )
	RCSTR(MQRC_DBCS_ERROR                )
	RCSTR(MQRC_OBJECT_NAME_ERROR         )
	RCSTR(MQRC_OBJECT_Q_MGR_NAME_ERROR   )
	RCSTR(MQRC_RECS_PRESENT_ERROR        )
	RCSTR(MQRC_OBJECT_RECORDS_ERROR      )
	RCSTR(MQRC_RESPONSE_RECORDS_ERROR    )
	RCSTR(MQRC_ASID_MISMATCH             )
	RCSTR(MQRC_PMO_RECORD_FLAGS_ERROR    )
	RCSTR(MQRC_PUT_MSG_RECORDS_ERROR     )
	RCSTR(MQRC_CONN_ID_IN_USE            )
	RCSTR(MQRC_Q_MGR_QUIESCING           )
	RCSTR(MQRC_Q_MGR_STOPPING            )
	RCSTR(MQRC_DUPLICATE_RECOV_COORD     )
	RCSTR(MQRC_PMO_ERROR                 )
	RCSTR(MQRC_API_EXIT_NOT_FOUND        )
	RCSTR(MQRC_API_EXIT_LOAD_ERROR       )
	RCSTR(MQRC_REMOTE_Q_NAME_ERROR       )
	RCSTR(MQRC_INCONSISTENT_PERSISTENCE  )
	RCSTR(MQRC_GMO_ERROR                 )
	RCSTR(MQRC_CICS_BRIDGE_RESTRICTION   )
	RCSTR(MQRC_STOPPED_BY_CLUSTER_EXIT   )
	RCSTR(MQRC_CLUSTER_RESOLUTION_ERROR  )
	RCSTR(MQRC_CONVERTED_STRING_TOO_BIG  )
	RCSTR(MQRC_TMC_ERROR                 )
	RCSTR(MQRC_PAGESET_FULL              )
	RCSTR(MQRC_STORAGE_MEDIUM_FULL       )
	RCSTR(MQRC_PAGESET_ERROR             )
	RCSTR(MQRC_NAME_NOT_VALID_FOR_TYPE   )
	RCSTR(MQRC_UNEXPECTED_ERROR          )
	RCSTR(MQRC_UNKNOWN_XMIT_Q            )
	RCSTR(MQRC_UNKNOWN_DEF_XMIT_Q        )
	RCSTR(MQRC_DEF_XMIT_Q_TYPE_ERROR     )
	RCSTR(MQRC_DEF_XMIT_Q_USAGE_ERROR    )
	RCSTR(MQRC_MSG_MARKED_BROWSE_CO_OP   )
	RCSTR(MQRC_NAME_IN_USE               )
	RCSTR(MQRC_CONNECTION_QUIESCING      )
	RCSTR(MQRC_CONNECTION_STOPPING       )
	RCSTR(MQRC_ADAPTER_NOT_AVAILABLE     )
	RCSTR(MQRC_MSG_ID_ERROR              )
	RCSTR(MQRC_CORREL_ID_ERROR           )
	RCSTR(MQRC_FILE_SYSTEM_ERROR         )
	RCSTR(MQRC_NO_MSG_LOCKED             )
	RCSTR(MQRC_SOAP_DOTNET_ERROR         )
	RCSTR(MQRC_SOAP_AXIS_ERROR           )
	RCSTR(MQRC_SOAP_URL_ERROR            )
	RCSTR(MQRC_FILE_NOT_AUDITED          )
	RCSTR(MQRC_CONNECTION_NOT_AUTHORIZED )
	RCSTR(MQRC_MSG_TOO_BIG_FOR_CHANNEL   )
	RCSTR(MQRC_CALL_IN_PROGRESS          )
	RCSTR(MQRC_RMH_ERROR                 )
	RCSTR(MQRC_Q_MGR_ACTIVE              )
	RCSTR(MQRC_Q_MGR_NOT_ACTIVE          )
	RCSTR(MQRC_Q_DEPTH_HIGH              )
	RCSTR(MQRC_Q_DEPTH_LOW               )
	RCSTR(MQRC_Q_SERVICE_INTERVAL_HIGH   )
	RCSTR(MQRC_Q_SERVICE_INTERVAL_OK     )
	RCSTR(MQRC_RFH_HEADER_FIELD_ERROR    )
	RCSTR(MQRC_RAS_PROPERTY_ERROR        )
	RCSTR(MQRC_UNIT_OF_WORK_NOT_STARTED  )
	RCSTR(MQRC_CHANNEL_AUTO_DEF_OK       )
	RCSTR(MQRC_CHANNEL_AUTO_DEF_ERROR    )
	RCSTR(MQRC_CFH_ERROR                 )
	RCSTR(MQRC_CFIL_ERROR                )
	RCSTR(MQRC_CFIN_ERROR                )
	RCSTR(MQRC_CFSL_ERROR                )
	RCSTR(MQRC_CFST_ERROR                )
	RCSTR(MQRC_INCOMPLETE_GROUP          )
	RCSTR(MQRC_INCOMPLETE_MSG            )
	RCSTR(MQRC_INCONSISTENT_CCSIDS       )
	RCSTR(MQRC_INCONSISTENT_ENCODINGS    )
	RCSTR(MQRC_INCONSISTENT_UOW          )
	RCSTR(MQRC_INVALID_MSG_UNDER_CURSOR  )
	RCSTR(MQRC_MATCH_OPTIONS_ERROR       )
	RCSTR(MQRC_MDE_ERROR                 )
	RCSTR(MQRC_MSG_FLAGS_ERROR           )
	RCSTR(MQRC_MSG_SEQ_NUMBER_ERROR      )
	RCSTR(MQRC_OFFSET_ERROR              )
	RCSTR(MQRC_ORIGINAL_LENGTH_ERROR     )
	RCSTR(MQRC_SEGMENT_LENGTH_ZERO       )
	RCSTR(MQRC_UOW_NOT_AVAILABLE         )
	RCSTR(MQRC_WRONG_GMO_VERSION         )
	RCSTR(MQRC_WRONG_MD_VERSION          )
	RCSTR(MQRC_GROUP_ID_ERROR            )
	RCSTR(MQRC_INCONSISTENT_BROWSE       )
	RCSTR(MQRC_XQH_ERROR                 )
	RCSTR(MQRC_SRC_ENV_ERROR             )
	RCSTR(MQRC_SRC_NAME_ERROR            )
	RCSTR(MQRC_DEST_ENV_ERROR            )
	RCSTR(MQRC_DEST_NAME_ERROR           )
	RCSTR(MQRC_TM_ERROR                  )
	RCSTR(MQRC_CLUSTER_EXIT_ERROR        )
	RCSTR(MQRC_CLUSTER_EXIT_LOAD_ERROR   )
	RCSTR(MQRC_CLUSTER_PUT_INHIBITED     )
	RCSTR(MQRC_CLUSTER_RESOURCE_ERROR    )
	RCSTR(MQRC_NO_DESTINATIONS_AVAILABLE )
	RCSTR(MQRC_CONN_TAG_IN_USE           )
	RCSTR(MQRC_PARTIALLY_CONVERTED       )
	RCSTR(MQRC_CONNECTION_ERROR          )
	RCSTR(MQRC_OPTION_ENVIRONMENT_ERROR  )
	RCSTR(MQRC_CD_ERROR                  )
	RCSTR(MQRC_CLIENT_CONN_ERROR         )
	RCSTR(MQRC_CHANNEL_STOPPED_BY_USER   )
	RCSTR(MQRC_HCONFIG_ERROR             )
	RCSTR(MQRC_FUNCTION_ERROR            )
	RCSTR(MQRC_CHANNEL_STARTED           )
	RCSTR(MQRC_CHANNEL_STOPPED           )
	RCSTR(MQRC_CHANNEL_CONV_ERROR        )
	RCSTR(MQRC_SERVICE_NOT_AVAILABLE     )
	RCSTR(MQRC_INITIALIZATION_FAILED     )
	RCSTR(MQRC_TERMINATION_FAILED        )
	RCSTR(MQRC_UNKNOWN_Q_NAME            )
	RCSTR(MQRC_SERVICE_ERROR             )
	RCSTR(MQRC_Q_ALREADY_EXISTS          )
	RCSTR(MQRC_USER_ID_NOT_AVAILABLE     )
	RCSTR(MQRC_UNKNOWN_ENTITY            )
	RCSTR(MQRC_UNKNOWN_AUTH_ENTITY       )
	RCSTR(MQRC_UNKNOWN_REF_OBJECT        )
	RCSTR(MQRC_CHANNEL_ACTIVATED         )
	RCSTR(MQRC_CHANNEL_NOT_ACTIVATED     )
	RCSTR(MQRC_UOW_CANCELED              )
	RCSTR(MQRC_FUNCTION_NOT_SUPPORTED    )
	RCSTR(MQRC_SELECTOR_TYPE_ERROR       )
	RCSTR(MQRC_COMMAND_TYPE_ERROR        )
	RCSTR(MQRC_MULTIPLE_INSTANCE_ERROR   )
	RCSTR(MQRC_SYSTEM_ITEM_NOT_ALTERABLE )
	RCSTR(MQRC_BAG_CONVERSION_ERROR      )
	RCSTR(MQRC_SELECTOR_OUT_OF_RANGE     )
	RCSTR(MQRC_SELECTOR_NOT_UNIQUE       )
	RCSTR(MQRC_INDEX_NOT_PRESENT         )
	RCSTR(MQRC_STRING_ERROR              )
	RCSTR(MQRC_ENCODING_NOT_SUPPORTED    )
	RCSTR(MQRC_SELECTOR_NOT_PRESENT      )
	RCSTR(MQRC_OUT_SELECTOR_ERROR        )
	RCSTR(MQRC_STRING_TRUNCATED          )
	RCSTR(MQRC_SELECTOR_WRONG_TYPE       )
	RCSTR(MQRC_INCONSISTENT_ITEM_TYPE    )
	RCSTR(MQRC_INDEX_ERROR               )
	RCSTR(MQRC_SYSTEM_BAG_NOT_ALTERABLE  )
	RCSTR(MQRC_ITEM_COUNT_ERROR          )
	RCSTR(MQRC_FORMAT_NOT_SUPPORTED      )
	RCSTR(MQRC_SELECTOR_NOT_SUPPORTED    )
	RCSTR(MQRC_ITEM_VALUE_ERROR          )
	RCSTR(MQRC_HBAG_ERROR                )
	RCSTR(MQRC_PARAMETER_MISSING         )
	RCSTR(MQRC_CMD_SERVER_NOT_AVAILABLE  )
	RCSTR(MQRC_STRING_LENGTH_ERROR       )
	RCSTR(MQRC_INQUIRY_COMMAND_ERROR     )
	RCSTR(MQRC_NESTED_BAG_NOT_SUPPORTED  )
	RCSTR(MQRC_BAG_WRONG_TYPE            )
	RCSTR(MQRC_ITEM_TYPE_ERROR           )
	RCSTR(MQRC_SYSTEM_BAG_NOT_DELETABLE  )
	RCSTR(MQRC_SYSTEM_ITEM_NOT_DELETABLE )
	RCSTR(MQRC_CODED_CHAR_SET_ID_ERROR   )
	RCSTR(MQRC_MSG_TOKEN_ERROR           )
	RCSTR(MQRC_MISSING_WIH               )
	RCSTR(MQRC_WIH_ERROR                 )
	RCSTR(MQRC_RFH_ERROR                 )
	RCSTR(MQRC_RFH_STRING_ERROR          )
	RCSTR(MQRC_RFH_COMMAND_ERROR         )
	RCSTR(MQRC_RFH_PARM_ERROR            )
	RCSTR(MQRC_RFH_DUPLICATE_PARM        )
	RCSTR(MQRC_RFH_PARM_MISSING          )
	RCSTR(MQRC_CHAR_CONVERSION_ERROR     )
	RCSTR(MQRC_UCS2_CONVERSION_ERROR     )
	RCSTR(MQRC_DB2_NOT_AVAILABLE         )
	RCSTR(MQRC_OBJECT_NOT_UNIQUE         )
	RCSTR(MQRC_CONN_TAG_NOT_RELEASED     )
	RCSTR(MQRC_CF_NOT_AVAILABLE          )
	RCSTR(MQRC_CF_STRUC_IN_USE           )
	RCSTR(MQRC_CF_STRUC_LIST_HDR_IN_USE  )
	RCSTR(MQRC_CF_STRUC_AUTH_FAILED      )
	RCSTR(MQRC_CF_STRUC_ERROR            )
	RCSTR(MQRC_CONN_TAG_NOT_USABLE       )
	RCSTR(MQRC_GLOBAL_UOW_CONFLICT       )
	RCSTR(MQRC_LOCAL_UOW_CONFLICT        )
	RCSTR(MQRC_HANDLE_IN_USE_FOR_UOW     )
	RCSTR(MQRC_UOW_ENLISTMENT_ERROR      )
	RCSTR(MQRC_UOW_MIX_NOT_SUPPORTED     )
	RCSTR(MQRC_WXP_ERROR                 )
	RCSTR(MQRC_CURRENT_RECORD_ERROR      )
	RCSTR(MQRC_NEXT_OFFSET_ERROR         )
	RCSTR(MQRC_NO_RECORD_AVAILABLE       )
	RCSTR(MQRC_OBJECT_LEVEL_INCOMPATIBLE )
	RCSTR(MQRC_NEXT_RECORD_ERROR         )
	RCSTR(MQRC_BACKOUT_THRESHOLD_REACHED )
	RCSTR(MQRC_MSG_NOT_MATCHED           )
	RCSTR(MQRC_JMS_FORMAT_ERROR          )
	RCSTR(MQRC_SEGMENTS_NOT_SUPPORTED    )
	RCSTR(MQRC_WRONG_CF_LEVEL            )
	RCSTR(MQRC_CONFIG_CREATE_OBJECT      )
	RCSTR(MQRC_CONFIG_CHANGE_OBJECT      )
	RCSTR(MQRC_CONFIG_DELETE_OBJECT      )
	RCSTR(MQRC_CONFIG_REFRESH_OBJECT     )
	RCSTR(MQRC_CHANNEL_SSL_ERROR         )
	RCSTR(MQRC_PARTICIPANT_NOT_DEFINED   )
	RCSTR(MQRC_CF_STRUC_FAILED           )
	RCSTR(MQRC_API_EXIT_ERROR            )
	RCSTR(MQRC_API_EXIT_INIT_ERROR       )
	RCSTR(MQRC_API_EXIT_TERM_ERROR       )
	RCSTR(MQRC_EXIT_REASON_ERROR         )
	RCSTR(MQRC_RESERVED_VALUE_ERROR      )
	RCSTR(MQRC_NO_DATA_AVAILABLE         )
	RCSTR(MQRC_SCO_ERROR                 )
	RCSTR(MQRC_KEY_REPOSITORY_ERROR      )
	RCSTR(MQRC_CRYPTO_HARDWARE_ERROR     )
	RCSTR(MQRC_AUTH_INFO_REC_COUNT_ERROR )
	RCSTR(MQRC_AUTH_INFO_REC_ERROR       )
	RCSTR(MQRC_AIR_ERROR                 )
	RCSTR(MQRC_AUTH_INFO_TYPE_ERROR      )
	RCSTR(MQRC_AUTH_INFO_CONN_NAME_ERROR )
	RCSTR(MQRC_LDAP_USER_NAME_ERROR      )
	RCSTR(MQRC_LDAP_USER_NAME_LENGTH_ERR )
	RCSTR(MQRC_LDAP_PASSWORD_ERROR       )
	RCSTR(MQRC_SSL_ALREADY_INITIALIZED   )
	RCSTR(MQRC_SSL_CONFIG_ERROR          )
	RCSTR(MQRC_SSL_INITIALIZATION_ERROR  )
	RCSTR(MQRC_Q_INDEX_TYPE_ERROR        )
	RCSTR(MQRC_CFBS_ERROR                )
	RCSTR(MQRC_SSL_NOT_ALLOWED           )
	RCSTR(MQRC_JSSE_ERROR                )
	RCSTR(MQRC_SSL_PEER_NAME_MISMATCH    )
	RCSTR(MQRC_SSL_PEER_NAME_ERROR       )
	RCSTR(MQRC_UNSUPPORTED_CIPHER_SUITE  )
	RCSTR(MQRC_SSL_CERTIFICATE_REVOKED   )
	RCSTR(MQRC_SSL_CERT_STORE_ERROR      )
	RCSTR(MQRC_CLIENT_EXIT_LOAD_ERROR    )
	RCSTR(MQRC_CLIENT_EXIT_ERROR         )
	RCSTR(MQRC_UOW_COMMITTED             )
	RCSTR(MQRC_SSL_KEY_RESET_ERROR       )
	RCSTR(MQRC_UNKNOWN_COMPONENT_NAME    )
	RCSTR(MQRC_LOGGER_STATUS             )
	RCSTR(MQRC_COMMAND_MQSC              )
	RCSTR(MQRC_COMMAND_PCF               )
	RCSTR(MQRC_CFIF_ERROR                )
	RCSTR(MQRC_CFSF_ERROR                )
	RCSTR(MQRC_CFGR_ERROR                )
	RCSTR(MQRC_MSG_NOT_ALLOWED_IN_GROUP  )
	RCSTR(MQRC_FILTER_OPERATOR_ERROR     )
	RCSTR(MQRC_NESTED_SELECTOR_ERROR     )
	RCSTR(MQRC_EPH_ERROR                 )
	RCSTR(MQRC_RFH_FORMAT_ERROR          )
	RCSTR(MQRC_CFBF_ERROR                )
	RCSTR(MQRC_CLIENT_CHANNEL_CONFLICT   )
	RCSTR(MQRC_SD_ERROR                  )
	RCSTR(MQRC_TOPIC_STRING_ERROR        )
	RCSTR(MQRC_STS_ERROR                 )
	RCSTR(MQRC_NO_SUBSCRIPTION           )
	RCSTR(MQRC_SUBSCRIPTION_IN_USE       )
	RCSTR(MQRC_STAT_TYPE_ERROR           )
	RCSTR(MQRC_SUB_USER_DATA_ERROR       )
	RCSTR(MQRC_SUB_ALREADY_EXISTS        )
	RCSTR(MQRC_IDENTITY_MISMATCH         )
	RCSTR(MQRC_ALTER_SUB_ERROR           )
	RCSTR(MQRC_DURABILITY_NOT_ALLOWED    )
	RCSTR(MQRC_NO_RETAINED_MSG           )
	RCSTR(MQRC_SRO_ERROR                 )
	RCSTR(MQRC_SUB_NAME_ERROR            )
	RCSTR(MQRC_OBJECT_STRING_ERROR       )
	RCSTR(MQRC_PROPERTY_NAME_ERROR       )
	RCSTR(MQRC_SEGMENTATION_NOT_ALLOWED  )
	RCSTR(MQRC_CBD_ERROR                 )
	RCSTR(MQRC_CTLO_ERROR                )
	RCSTR(MQRC_NO_CALLBACKS_ACTIVE       )
	RCSTR(MQRC_CALLBACK_NOT_REGISTERED   )
	RCSTR(MQRC_OPTIONS_CHANGED           )
	RCSTR(MQRC_READ_AHEAD_MSGS           )
	RCSTR(MQRC_SELECTOR_SYNTAX_ERROR     )
	RCSTR(MQRC_HMSG_ERROR                )
	RCSTR(MQRC_CMHO_ERROR                )
	RCSTR(MQRC_DMHO_ERROR                )
	RCSTR(MQRC_SMPO_ERROR                )
	RCSTR(MQRC_IMPO_ERROR                )
	RCSTR(MQRC_PROPERTY_NAME_TOO_BIG     )
	RCSTR(MQRC_PROP_VALUE_NOT_CONVERTED  )
	RCSTR(MQRC_PROP_TYPE_NOT_SUPPORTED   )
	RCSTR(MQRC_PROPERTY_VALUE_TOO_BIG    )
	RCSTR(MQRC_PROP_CONV_NOT_SUPPORTED   )
	RCSTR(MQRC_PROPERTY_NOT_AVAILABLE    )
	RCSTR(MQRC_PROP_NUMBER_FORMAT_ERROR  )
	RCSTR(MQRC_PROPERTY_TYPE_ERROR       )
	RCSTR(MQRC_PROPERTIES_TOO_BIG        )
	RCSTR(MQRC_PUT_NOT_RETAINED          )
	RCSTR(MQRC_ALIAS_TARGTYPE_CHANGED    )
	RCSTR(MQRC_DMPO_ERROR                )
	RCSTR(MQRC_PD_ERROR                  )
	RCSTR(MQRC_CALLBACK_TYPE_ERROR       )
	RCSTR(MQRC_CBD_OPTIONS_ERROR         )
	RCSTR(MQRC_MAX_MSG_LENGTH_ERROR      )
	RCSTR(MQRC_CALLBACK_ROUTINE_ERROR    )
	RCSTR(MQRC_CALLBACK_LINK_ERROR       )
	RCSTR(MQRC_OPERATION_ERROR           )
	RCSTR(MQRC_BMHO_ERROR                )
	RCSTR(MQRC_UNSUPPORTED_PROPERTY      )
	RCSTR(MQRC_PROP_NAME_NOT_CONVERTED   )
	RCSTR(MQRC_GET_ENABLED               )
	RCSTR(MQRC_MODULE_NOT_FOUND          )
	RCSTR(MQRC_MODULE_INVALID            )
	RCSTR(MQRC_MODULE_ENTRY_NOT_FOUND    )
	RCSTR(MQRC_MIXED_CONTENT_NOT_ALLOWED )
	RCSTR(MQRC_MSG_HANDLE_IN_USE         )
	RCSTR(MQRC_HCONN_ASYNC_ACTIVE        )
	RCSTR(MQRC_MHBO_ERROR                )
	RCSTR(MQRC_PUBLICATION_FAILURE       )
	RCSTR(MQRC_SUB_INHIBITED             )
	RCSTR(MQRC_SELECTOR_ALWAYS_FALSE     )
	RCSTR(MQRC_XEPO_ERROR                )
	RCSTR(MQRC_DURABILITY_NOT_ALTERABLE  )
	RCSTR(MQRC_TOPIC_NOT_ALTERABLE       )
	RCSTR(MQRC_SUBLEVEL_NOT_ALTERABLE    )
	RCSTR(MQRC_PROPERTY_NAME_LENGTH_ERR  )
	RCSTR(MQRC_DUPLICATE_GROUP_SUB       )
	RCSTR(MQRC_GROUPING_NOT_ALTERABLE    )
	RCSTR(MQRC_SELECTOR_INVALID_FOR_TYPE )
	RCSTR(MQRC_HOBJ_QUIESCED             )
	RCSTR(MQRC_HOBJ_QUIESCED_NO_MSGS     )
	RCSTR(MQRC_SELECTION_STRING_ERROR    )
	RCSTR(MQRC_RES_OBJECT_STRING_ERROR   )
	RCSTR(MQRC_CONNECTION_SUSPENDED      )
	RCSTR(MQRC_INVALID_DESTINATION       )
	RCSTR(MQRC_INVALID_SUBSCRIPTION      )
	RCSTR(MQRC_SELECTOR_NOT_ALTERABLE    )
	RCSTR(MQRC_RETAINED_MSG_Q_ERROR      )
	RCSTR(MQRC_RETAINED_NOT_DELIVERED    )
	RCSTR(MQRC_RFH_RESTRICTED_FORMAT_ERR )
	RCSTR(MQRC_CONNECTION_STOPPED        )
	RCSTR(MQRC_ASYNC_UOW_CONFLICT        )
	RCSTR(MQRC_ASYNC_XA_CONFLICT         )
	RCSTR(MQRC_PUBSUB_INHIBITED          )
	RCSTR(MQRC_MSG_HANDLE_COPY_FAILURE   )
	RCSTR(MQRC_DEST_CLASS_NOT_ALTERABLE  )
	RCSTR(MQRC_OPERATION_NOT_ALLOWED     )
	RCSTR(MQRC_ACTION_ERROR              )
	RCSTR(MQRC_CHANNEL_NOT_AVAILABLE     )
	RCSTR(MQRC_HOST_NOT_AVAILABLE        )
	RCSTR(MQRC_CHANNEL_CONFIG_ERROR      )
	RCSTR(MQRC_UNKNOWN_CHANNEL_NAME      )
	RCSTR(MQRC_LOOPING_PUBLICATION       )
	RCSTR(MQRC_ALREADY_JOINED            )
	RCSTR(MQRC_STANDBY_Q_MGR             )
	RCSTR(MQRC_RECONNECTING              )
	RCSTR(MQRC_RECONNECTED               )
	RCSTR(MQRC_RECONNECT_QMID_MISMATCH   )
	RCSTR(MQRC_RECONNECT_INCOMPATIBLE    )
	RCSTR(MQRC_RECONNECT_FAILED          )
	RCSTR(MQRC_CALL_INTERRUPTED          )
	RCSTR(MQRC_NO_SUBS_MATCHED           )
	RCSTR(MQRC_SELECTION_NOT_AVAILABLE   )
	RCSTR(MQRC_CHANNEL_SSL_WARNING       )
	RCSTR(MQRC_OCSP_URL_ERROR            )
	RCSTR(MQRC_CONTENT_ERROR             )
	RCSTR(MQRC_RECONNECT_Q_MGR_REQD      )
	RCSTR(MQRC_RECONNECT_TIMED_OUT       )
	RCSTR(MQRC_PUBLISH_EXIT_ERROR        )
	RCSTR(MQRC_SSL_ALT_PROVIDER_REQUIRED )
	RCSTR(MQRC_PRECONN_EXIT_LOAD_ERROR   )
	RCSTR(MQRC_PRECONN_EXIT_NOT_FOUND    )
	RCSTR(MQRC_PRECONN_EXIT_ERROR        )
	RCSTR(MQRC_CD_ARRAY_ERROR            )

	RCSTR(MQRC_REOPEN_EXCL_INPUT_ERROR   )
	RCSTR(MQRC_REOPEN_INQUIRE_ERROR      )
	RCSTR(MQRC_REOPEN_SAVED_CONTEXT_ERR  )
	RCSTR(MQRC_REOPEN_TEMPORARY_Q_ERROR  )
	RCSTR(MQRC_ATTRIBUTE_LOCKED          )
	RCSTR(MQRC_CURSOR_NOT_VALID          )
	RCSTR(MQRC_ENCODING_ERROR            )
	RCSTR(MQRC_STRUC_ID_ERROR            )
	RCSTR(MQRC_NULL_POINTER              )
	RCSTR(MQRC_NO_CONNECTION_REFERENCE   )
	RCSTR(MQRC_NO_BUFFER                 )
	RCSTR(MQRC_BINARY_DATA_LENGTH_ERROR  )
	RCSTR(MQRC_BUFFER_NOT_AUTOMATIC      )
	RCSTR(MQRC_INSUFFICIENT_BUFFER       )
	RCSTR(MQRC_INSUFFICIENT_DATA         )
	RCSTR(MQRC_DATA_TRUNCATED            )
	RCSTR(MQRC_ZERO_LENGTH               )
	RCSTR(MQRC_NEGATIVE_LENGTH           )
	RCSTR(MQRC_NEGATIVE_OFFSET           )
	RCSTR(MQRC_INCONSISTENT_FORMAT       )
	RCSTR(MQRC_INCONSISTENT_OBJECT_STATE )
	RCSTR(MQRC_CONTEXT_OBJECT_NOT_VALID  )
	RCSTR(MQRC_CONTEXT_OPEN_ERROR        )
	RCSTR(MQRC_STRUC_LENGTH_ERROR        )
	RCSTR(MQRC_NOT_CONNECTED             )
	RCSTR(MQRC_NOT_OPEN                  )
	RCSTR(MQRC_DISTRIBUTION_LIST_EMPTY   )
	RCSTR(MQRC_INCONSISTENT_OPEN_OPTIONS )
	RCSTR(MQRC_WRONG_VERSION             )
	RCSTR(MQRC_REFERENCE_ERROR           )
;


MQMapper::MQMapper(CommandServer& commandServer) : _commandServer(commandServer)
{
}

MQMapper::~MQMapper()
{
}

void MQMapper::mapToJSON(const PCF& pcf, Poco::JSON::Object::Ptr& json)
{
	std::vector<MQLONG> parameters = pcf.getParameters();
	for(std::vector<MQLONG>::iterator it = parameters.begin(); it != parameters.end(); ++it)
	{
		std::string name = _dictionary.getName(*it);
		if ( name.empty() )
		{
			name = "id_" + Poco::NumberFormatter::format(*it);
		}

		Poco::JSON::Object::Ptr field = new Poco::JSON::Object();
		json->set(name, field);

		field->set("id", *it);

		if ( pcf.isNumber(*it) )
		{
			MQLONG value = pcf.getParameterNum(*it);
			field->set("value", value);

			if ( _dictionary.hasDisplayMap(*it) )
			{
				std::string displayValue = _dictionary.getDisplayValue(*it, value);
				if ( displayValue.empty() )
				{
					displayValue = "Unknown value " + Poco::NumberFormatter::format(value) + " for " + Poco::NumberFormatter::format(*it);
				}
				field->set("display", displayValue);
			}
		}
		else if ( pcf.isString(*it) )
		{
			field->set("value", pcf.getParameterString(*it));
		}
		else if ( pcf.isNumberList(*it) )
		{
			std::vector<MQLONG> values = pcf.getParameterNumList(*it);
			Poco::JSON::Array::Ptr jsonValues = new Poco::JSON::Array();
			field->set("value", jsonValues);

			if ( _dictionary.hasDisplayMap(*it) )
			{
				for(std::vector<MQLONG>::iterator vit = values.begin(); vit != values.end(); ++vit)
				{
					Poco::JSON::Object::Ptr jsonValueObject = new Poco::JSON::Object();

					std::string displayValue = _dictionary.getDisplayValue(*it, *vit);
					if ( displayValue.empty() )
					{
						displayValue = "Unknown value " + Poco::NumberFormatter::format(*vit) + " for " + Poco::NumberFormatter::format(*it);
					}
					jsonValueObject->set("value", *vit);
					jsonValueObject->set("display", displayValue);
					jsonValues->add(jsonValueObject);
				}
			}
			else
			{
				for(std::vector<MQLONG>::iterator vit = values.begin(); vit != values.end(); ++vit)
				{
					jsonValues->add(*vit);
				}
			}
		}
		else
		{
			//TODO:
		}
	}
}

/*
void MQMapper::mapNumberToJSON(const PCF& pcf, Poco::JSON::Object::Ptr& json, const std::string& name, int parameter)
{
	if ( pcf.hasParameter(parameter) )
	{
		json->set(name, pcf.getParameterNum(parameter));
	}
}


void MQMapper::mapStringToJSON(const PCF& pcf, Poco::JSON::Object::Ptr& json, const std::string& name, int parameter)
{
	if (    pcf.hasParameter(parameter) )
	{
		json->set(name, pcf.getParameterString(parameter));
	}
}


void MQMapper::mapDateToJSON(const PCF& pcf, Poco::JSON::Object::Ptr& json, const std::string& name, int dateParameter, int timeParameter)
{
	if (    pcf.hasParameter(dateParameter)
	   && pcf.hasParameter(timeParameter) )
	{
		Poco::DateTime dateTime = pcf.getParameterDate(dateParameter, timeParameter);
		json->set(name, Poco::DateTimeFormatter::format(dateTime, "%d-%m-%Y %H:%M:%S"));
	}
}
*/

std::string MQMapper::getReasonString(MQLONG reasonCode)
{
	DisplayMap::const_iterator it = _reasonCodes.find(reasonCode);
	if ( it == _reasonCodes.end() )
	{
		return "";
	}
	return it->second;
}
}} //  Namespace MQ::Web
