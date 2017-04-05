de.sc.portal.env.msg = {};

de.sc.portal.env.msg.MOD_CLUSTER_MANAGER = "mod_cluster_manager";

de.sc.portal.env.msg.poll = function(servers)
{
   	var mod_cluster_manager_10001 = servers[0][0].getModClusterManagerURL();
   	var mod_cluster_manager_20001 = servers[1][0].getModClusterManagerURL();

   	window.setInterval(function()
   	{
		$.ajax
		({
			url: ((window.location.href.indexOf("http") === 0) ? ("/cgi-bin/get.cgi?"+escape(mod_cluster_manager_10001)) : "_Mod_cluster Status.htm"), dataType:"html"
		})
		.success(function(data)
		{
			var mod_cluster_manager_10001_content = data;
			$.ajax
			({
				url: ((window.location.href.indexOf("http") === 0) ? ("/cgi-bin/get.cgi?"+escape(mod_cluster_manager_20001)) : "_Mod_cluster Status2.htm"), dataType:"html"
			})
			.success(function(data)
			{
				var mod_cluster_manager_20001_content = data;
				
				$.event.trigger(
				{
					type: de.sc.portal.env.msg.MOD_CLUSTER_MANAGER,
					clusters:
					[
						{
							cluster:servers[0],
							content:mod_cluster_manager_10001_content
						},
						{
							cluster:servers[1],
							content:mod_cluster_manager_20001_content
						}
					]
				});
			})
			.error(function(xhr, statusmsg, err)
			{
				de.sc.log("\ncheckavailability:\nstatus:'"+statusmsg+"'\nerror:'"+err+"'\nurl: '"+mod_cluster_manager_20001+"'\nthis:'"+window.location.href+"'", de.sc.WRN);
			});	
		})
		.error(function(xhr, statusmsg, err)
		{
			de.sc.log("\ncheckavailability:\nstatus:'"+statusmsg+"'\nerror:'"+err+"'\nurl: '"+mod_cluster_manager_10001+"'\nthis:'"+window.location.href+"'", de.sc.WRN);
		});	

   	}, 5000);
};
