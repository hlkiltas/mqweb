<div id="content">
	<div ng-controller="QmgrController" class="post">
		<h3>QueueManager <strong><?= mqweb.qmgr ?></strong></h3>
		<img ng-if="!mqweb.zos" src="/static/css/images/briefcase.jpg" alt="briefcase" />
		<img ng-if="mqweb.zos" src="/static/images/zos-icon.png" alt="z/OS" title="z/OS" />
		<div ng-show="qmgr != null">
			<p>
				<em><span>{{qmgr.QMgrDesc.value}}</span></em>
			</p>
			<!-- DETAILS -->
			<div class="details" style="float:left;width:70%">
				<div>
					<h2>QueueManager ID</h2>
					<div class="detail">{{qmgr.QMgrIdentifier.value}}</div>
				</div>
				<div ng-if="qmgr.CreationDate != null">
					<h2>Creation Date</h2>
					<div class="detail">
						{{qmgr.CreationDate.value}}&nbsp;{{qmgr.CreationTime.value}}
					</div>
				</div>
				<div ng-if="qmgr.AlterationDate != null">
					<h2>Alteration Date</h2>
					<div class="detail">
						{{qmgr.AlterationDate.value}}&nbsp;{{qmgr.AlterationTime.value}}
					</div>
				</div>
				<div ng-if="qmgr.Platform">
					<h2>Platform</h2>
					<div class="detail">
						{{qmgr.Platform.display}}
					</div>
				</div>
				<div ng-if="qmgr.CodedCharSetID">
					<h2>Coded Characterset ID</h2>
					<div class="detail">
						{{qmgr.CodedCharSetID.value}}
					</div>
				</div>
				<div ng-if="qmgr.DeadLetterQName && qmgr.DeadLetterQName.value">
					<h2>Dead Letter Queue</h2>
					<div class="detail">
						<a ng-href="/queue/view/<?=mqweb.qmgr?>/{{qmgr.DeadLetterQName.value}}">{{qmgr.DeadLetterQName.value}}</a>
					</div>
				</div>
				<div ng-if="!qmgr.DeadLetterQName || !qmgr.DeadLetterQName.value">
					<h2>Dead Letter Queue</h2>
					<div class="detail">
						<img style="float:left;" src="/static/images/warning-icon.png" alt="error" />
						<em style="color:#FF6666">There is no dead letter queue defined. It's recommended to have one!</em>
					</div>
				</div>
			</div> <!-- END DETAILS -->
		</div>
		<div ng-show="loading" class="loader"> </div>
		<div style="font-size:0.7em;clear:both;">
			It took {{mqweb.elapsed}} seconds to create this output.
		</div>
	</div> <!-- post -->
</div> <!-- content -->
<!-- Sidebar -->
<div id="sidebar">
	<div class="box">
		<h3>Our Services</h3>
		<ul>
			<li><a title="List Queues" href="/queue/index/<?= mqweb.qmgr ?>">List Queues</a></li>
			<li><a title="List Channels" href="/channel/index/<?= mqweb.qmgr ?>">List Channels</a></li>
		</ul>
		<h3 style="margin-top:15px">WebSphere MQ</h3>
		<ul>
			<li><a title="Information Center" target="_blank" href="http://pic.dhe.ibm.com/infocenter/wmqv7/v7r1/index.jsp">Information Center</a></li>
			<li><a title="MQSeries.net" target="_blank" href="http://www.mqseries.net/phpBB2">MQSeries.net Forum</a></li>
		</ul>
	</div>
</div> <!-- END Sidebar -->
<div class="cl"></div>
<div class="widgets">
	<div class="col activities">
		<div ng-controller="LocalQueueController" id="localQueues">
			<a ng-click="load()"><img class="imgtip" src="/static/images/view-refresh-icon.png" style="float:right;padding-top:8px;padding-right:5px;" alt="Reload" /></a>
			<h3 data-qtip="This is a list with local queues that contains at least one message.<br /><br />System queues and transmission queues are omitted.">Local Queues</h3>
			<table ng-if="queues != null && queues.length > 0" style="font-size:0.8em;border-collapse:collapse;">
				<thead>
					<tr><th>Queue</th><th>Depth</th></tr>
				</thead>
				<tbody ng-repeat="queue in queues">
					<tr>
						<td><a ng-href="/queue/view/<?=mqweb.qmgr?>/{{queue.QName.value}}">{{queue.QName.value}}</a></td>
						<td>{{queue.CurrentQDepth.value | number}}</td>
					</tr>
				</tbody>
			</table>
			<p ng-if="queues == null || queues.length == 0">
				There are no local queues which contains messages. System queues were discarded in this view.
			</p>
			<div ng-if="loading" class="loader"></div>
		</div> <!-- localQueues -->
	</div> <!-- activities -->
	<div class="col activities">
		<div ng-controller="XmitQueueController" id="xmitQueues">
			<a ng-click="load()"><img class="imgtip" src="/static/images/view-refresh-icon.png" style="float:right;padding-top:8px;padding-right:5px;" alt="Reload" /></a>
			<h3 data-qtip="This is a list with transmission queues (USAGE=XMITQ) that contains at least one message.<br /><br />Normally, this list is empty when no channels has problems.">Transmission Queues</h3>
			<table ng-if="queues != null && queues.length > 0" style="font-size:0.8em;border-collapse:collapse;">
				<thead>
					<tr><th>Queue</th><th>Depth</th></tr>
				</thead>
				<tbody ng-repeat="queue in queues">
					<tr>
						<td><a ng-href="/queue/view/<?=mqweb.qmgr?>/{{queue.QName.value}}">{{queue.QName.value}}</a></td>
						<td>{{queue.CurrentQDepth.value | number}}</td>
					</tr>
				</tbody>
			</table>
			<p ng-if="queues == null || queues.length == 0">
				All transmission queues are empty.
			</p>
			<div ng-if="loading" class="loader"></div>
		</div> <!-- xmitQueues -->
	</div> <!-- activities -->
	<div class="col activities">
		<div ng-controller="ChannelStatusController" id="channels">
			<a ng-click="load()"><img class="imgtip" src="/static/images/view-refresh-icon.png" style="float:right;padding-top:8px;padding-right:5px;" alt="Reload" /></a>
			<h3 data-qtip="This is a list with active channel statuses.">Channel Status</h3>
			<table ng-if="channels && channels.length > 0" style="font-size:0.8em;border-collapse:collapse;">
				<thead>
					<tr><th colspan="2">Channel</th><th>Status</th></tr>
				</thead>
				<tbody ng-repeat="channel in Channels">
					<tr>
						<td ng-switch="ChannelStatus.display">
							<img ng-switch-when="Retrying" alt="The channel {{ChannelName.value}} has status Retrying" class="tip" src="/static/images/flag-red-icon.png" />
							<img ng-switch-when="Stopped" alt="The channel {{ChannelName.value}} has status Stopped' }" class="tip" src="/static/images/flag-black-icon.png" />
							<img ng-switch-when="Running" alt="The channel {{ChannelName.value}} has status Running' }" class="tip" src="/static/images/flag-green-icon.png" />
							<img ng-switch-default alt="The channel {{ChannelName.value}} has status {{ChannelStatus.display}}" class="tip" src="/static/images/flag-yellow-icon.png" />
						</td>
						<td data-bind="template: { name: statusImage }" />
						<td><a ng-href='/channel/view/<?= mqweb.qmgr ?>{{ChannelName.value}}/{{ChannelType.display}}'>{{ChannelName.value}}</a></td>
						<td>{{ChannelStatus.display}}</td>
					</tr>
				</tbody>
			</table>
			<div ng-if="channels == null || channels.length == 0">
			 <p>
				No channel status found.
			 </p>
			</div>
			<div ng-if="loading" class="loader"></div>
		</div> <!-- channels -->
	</div> <!-- activities -->
	<div class="cl"></div>
</div>
<div class="widgets">
	<div class="projects">
		<div ng-controller="EventMessageController" id="eventMessages">
			<a ng-click="load()"><img class="imgtip" src="/static/images/view-refresh-icon.png" style="float:right;padding-top:8px;padding-right:5px;" alt="Reload" /></a>
			<h3>SYSTEM.ADMIN.QMGR.EVENT</h3>
			<table ng-if="events && events.length > 0" style="border-spacing:0;border-collapse:collapse;">
				<thead>
					<tr>
						<th style="text-align:left;">Date</th>
						<th style="text-align:left;" colspan="2">Reason</th>
					</tr>
				</thead>
				<tbody ng-repeat="item in events">
					<tr>
						<td>{{item.message.PutDate}}</td>
						<td>{{item.event.reason}}</td>
						<td><span data-url="/message/event/<?=mqweb.qmgr ?>/SYSTEM.ADMIN.QMGR.EVENT/'{{item.message.MsgId}}">{{item.event.desc}}</span>
					</tr>
				</tbody>
			</table>
			<p ng-if="events == null || events.length == 0">
				No event messages found.
			</p>
			<p ng-if="events != null && events.length < curdepth" style="margin-top:5px;display:none">
				Number of messages on this queue: <strong>{{curdepth}}</strong><br />
				Only the first <strong>{{events.length}}</strong> messages are shown. Use <a href="/queue/view/<?=mqweb.qmgr?>/SYSTEM.ADMIN.QMGR.EVENT">queue detail</a> page to browse all messages.
			</p>
			<div ng-if="loading" class="loader"></div>
			<div>
				<div data-bind="template: { if: eventMessageModel.error, name: 'mqErrorTemplate', data: eventMessageModel.error }">
				</div>
			</div>
		</div> <!-- eventMessages -->
		<div class="cl"></div>
	</div>
	<div class="col contacts">
		<h3>Contact Us</h3>
		<ul class="box">
			<li><a title="Zumuta!" href="http://www.zumuta.be">My Website</a></li>
			<li><a title="Github Sourcecode Repository" href="https://github.com/fbraem/mqweb">Github Sourcecode Repository</a></li>
			<li><a title="Issues/Bugs" href="https://github.com/fbraem/mqweb/issues">Issue / Bug Reports</a></li>
		</ul>
	</div>
	<div class="cl"></div>
</div>
