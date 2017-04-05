Raphael.fn.connection = function (obj1, obj2, line, bg)
{
    if (obj1.line && obj1.from && obj1.to)
    {
        line = obj1;
        obj1 = line.from;
        obj2 = line.to;
    }
    var bb1 = obj1.getBBox(),
        bb2 = obj2.getBBox(),
        p = [{x: bb1.x + bb1.width / 2, y: bb1.y - 1},
        {x: bb1.x + bb1.width / 2, y: bb1.y + bb1.height + 1},
        {x: bb1.x - 1, y: bb1.y + bb1.height / 2},
        {x: bb1.x + bb1.width + 1, y: bb1.y + bb1.height / 2},
        {x: bb2.x + bb2.width / 2, y: bb2.y - 1},
        {x: bb2.x + bb2.width / 2, y: bb2.y + bb2.height + 1},
        {x: bb2.x - 1, y: bb2.y + bb2.height / 2},
        {x: bb2.x + bb2.width + 1, y: bb2.y + bb2.height / 2}],
        d = {}, dis = [];
    for (var i = 0; i < 4; i++)
    {
        for (var j = 4; j < 8; j++)
        {
            var dx = Math.abs(p[i].x - p[j].x),
                dy = Math.abs(p[i].y - p[j].y);
            if ((i == j - 4) || (((i != 3 && j != 6) || p[i].x < p[j].x) && ((i != 2 && j != 7) || p[i].x > p[j].x) && ((i != 0 && j != 5) || p[i].y > p[j].y) && ((i != 1 && j != 4) || p[i].y < p[j].y)))
            {
                dis.push(dx + dy);
                d[dis[dis.length - 1]] = [i, j];
            }
        }
    }
    if (dis.length == 0)
    {
        var res = [0, 4];
    }
    else
    {
        res = d[Math.min.apply(Math, dis)];
    }
    var x1 = p[res[0]].x,
        y1 = p[res[0]].y,
        x4 = p[res[1]].x,
        y4 = p[res[1]].y;
    dx = Math.max(Math.abs(x1 - x4) / 2, 10);
    dy = Math.max(Math.abs(y1 - y4) / 2, 10);
    var x2 = [x1, x1, x1 - dx, x1 + dx][res[0]].toFixed(3),
        y2 = [y1 - dy, y1 + dy, y1, y1][res[0]].toFixed(3),
        x3 = [0, 0, 0, 0, x4, x4, x4 - dx, x4 + dx][res[1]].toFixed(3),
        y3 = [0, 0, 0, 0, y1 + dy, y1 - dy, y4, y4][res[1]].toFixed(3);
    var path = ["M", x1.toFixed(3), y1.toFixed(3), "C", x2, y2, x3, y3, x4.toFixed(3), y4.toFixed(3)].join(",");
    if (line && line.line)
    {
        line.bg && line.bg.attr({path: path});
        line.line.attr({path: path});
    }
    else
    {
        var color = typeof line == "string" ? line : "#000";
        var path_ = this.path(path);
        return {
            bg: bg && bg.split && this.path(path).attr({stroke: bg.split("|")[0], fill: "none", "stroke-width": bg.split("|")[1] || 3}),
            line: path_.attr({stroke: color, fill: "none"}),
            path: path,
            path_: path_,
            from: obj1,
            to: obj2
        };
    }
};

graffle = {};
graffle.setup = function (r)
{
	r.customAttributes.progress = function (v)
	{
		var path = this.data("mypath"),
		attrs = this.attr(),
		offset = { x: 0, y: 0 };
		if (!path)
		{
			return {
				transform: "t0,0"
			};
		}
		if (attrs.hasOwnProperty("width"))
		{
			offset.x = -this.attr("width") / 2;
			offset.y = -this.attr("height") / 2;
		}
		var len = path.getTotalLength();
		var point = path.getPointAtLength(v * len);
		
		var trail = this.data("mytrail");
		if (trail) {
			trail.attr("path", path.getSubpath(0, v * len));	// set the trail's path to just the amount current trespassed:
		}
		return {
			transform:  "t" + (point.x + offset.x) + "," + (point.y + offset.y) +
						"s" + (this.type == "text" ? 1 : v) +
						"r" + (this.type == "text" ? 0 : v*360*2)
		};
	};
	
    var dragstart = function ()
    {
        this.ox = this.type == "rect" ? this.attr("x") : this.attr("cx");
        this.oy = this.type == "rect" ? this.attr("y") : this.attr("cy");
        
        this.animate({"fill-opacity": .2}, 500);

        for (var i = 1/*0 = r*/, ii = sets.length; i < ii; i++)
        {
        	var set2change = null;
	    	if (sets[i].from[0] == this)
	    		set2change = sets[i].from;
	    	if (sets[i].to[0] == this)
	    		set2change = sets[i].to;
	    	if(!set2change)continue;
	    	
	    	set2change.data("mytransform", this.transform());
	    	break;
        }
    },
    move = function (dx, dy, x, y, e)
    {
        var att = { x:  this.ox + dx,
        			y:  this.oy + dy,
        			cx: this.ox + dx,
        			cy: this.oy + dy };
        
        for (var i = 1/*0 = r*/, ii = sets.length; i < ii; i++)
        {
        	var set2change = null;
	    	if (sets[i].from[0] == this)
	    		set2change = sets[i].from;
	    	if (sets[i].to[0] == this)
	    		set2change = sets[i].to;
	    	if(!set2change)continue;
	    	
	    	set2change.transform(this.data("mytransform")+'T'+dx+','+dy);
	    	break;
        }

        for (var i = connections.length; i--;)
        {
            r.connection(connections[i]);
        }
        r.safari();
    },
    up = function (e)
    {
        for (var i = 1/*0 = r*/, ii = sets.length; i < ii; i++)
        {
        	var set2change = null;
	    	if (sets[i].from[0] == this)
	    		set2change = sets[i].from;
	    	if (sets[i].to[0] == this)
	    		set2change = sets[i].to;
	    	if(!set2change)continue;
        	
	    	set2change.data("mytransform", this.transform());
	    	break;
        }

        this.animate({"fill-opacity": 1}, 500);
    },
    
    connections = [],
    sets = arguments;
    
    for (var i = 1/*0 = r*/, ii = sets.length; i < ii; i++)
    {
        var color = Raphael.getColor();
        if(!document.all)
       	{
	        sets[i].from.drag(move, dragstart, up);
	        sets[i].to.drag ( move, dragstart, up);
       	}
        var c = r.connection(sets[i].from, sets[i].to, sets[i].linecolor);
        connections.push(c);
        if(!document.all && sets[i].ani)
        {
        	r.setStart();
	        var circle = r.rect(0, 0, 6, 6).attr({fill: '#09c', cursor: 'pointer'});
	        circle.data("mypath", c.path_);
	        circle.attr("progress", 0);
	        if(sets[i].anitext)
	        	r.text(0, -7, sets[i].anitext);
	        var anim = Raphael.animation({ progress: 1 }, 2000, 'easeOut', function() { if(document.all)this.hide(); }).delay(1000*i).repeat(document.all ? 0 : Infinity);
	        var set = r.setFinish();
	        set.data("mypath", c.path_);
	        set.attr("progress", 0);
	        set.animate(anim);
        }
    }
};
