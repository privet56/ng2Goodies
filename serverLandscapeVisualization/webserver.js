var static = require('node-static');
var sys = require("sys");

var file = new static.Server('.', { cache: 0 });

require('http').createServer(function(request, response)
{
    request.addListener('end', function()
    {
        file.serve(request, response, function (e, res)
        {
            if (e/*&& (e.status === 404)*/)
            {
            	sys.error("Error serving " + request.url + " - " + e.message);
                response.writeHead(e.status, e.headers);
                response.write(""+ e.status + " - error serving " + request.url + " - " + e.message);
                response.write(""+e.headers);
                response.end();
                //file.serveFile('/not-found.html', 404, {}, request, response);
            }
        });
    }).resume();

}).listen(8080);
