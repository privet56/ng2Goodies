de.sc.a = {};

de.sc.a.showmessage = "de.sc.a.showmessage";
var __i=0;

angular.module("lib", []).directive('naMessages', ['$rootScope', '$http', '$compile', '$interval', '$timeout', '$interval', '$log', '$templateCache', function($rootScope, $http, $compile, $interval, $timeout, $interval, $log, $templateCache)
{
	return {	//'{' has to be on this line!

		link: function(scope, jQueryObject, attrs)
		{
			$http.get('fragment_msg.htm').success(function(data) { $templateCache.put("fragment_msg.htm", data); });
			
			$rootScope.$on(de.sc.a.showmessage, function(event, data)
			{
				var childScope = $rootScope.$new();
				angular.extend(childScope, data);
				
				var c = $compile($templateCache.get("fragment_msg.htm"))(childScope);
				jQueryObject.append(c);
				$timeout(function ()
					{
						__i++;
						if(__i++ % 4 == 0)
							$(c).toggle("slow", function(){ $(this).remove(); });
						else if(__i++ % 3 == 0)
							$(c).toggle("explode", { pieces:9 }, "slow", function(){ $(this).remove(); });
						else if(__i++ % 2 == 0)
							$(c).toggle("drop", { direction:"left" }, "slow", function(){ $(this).remove(); });
						else
							$(c).slideUp(999, function(){ $(this).remove(); });
					},
					data.isError ? 15000 : 5000);
			});			
		},
		
		restrict:'A',
		scope: {},
		replace: false
	};
}]);
