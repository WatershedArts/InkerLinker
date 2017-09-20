
var ids = {};
//-----------------------------------------------------
// *
// * Document Ready
// *
//-----------------------------------------------------
$(document).ready( function()
{
	$.getJSON( "./content.json", function( data )
	{
		$.each( data, function( key, val )
		{
			if(val.pagename.match("Help"))
			{
				for(var i = 0; i < val.content.length; i++)
				{
					var p = '<li><a onClick="document.getElementById(\''+val.content[i].topic+'\').scrollIntoView(); window.scrollBy(0,-75);" >'+val.content[i].topic+'</a></li>';
					$(p).appendTo('#helpcontent');

					var caro = "<div id="+val.content[i].topic+"><h3>"+val.content[i].topic+"</h3><p>"+val.content[i].text+"</p><img src='"+val.content[i].gif+"'/></div>";


					$(caro).appendTo('#Help');
				}
			}
			else if(val.pagename.match("Nodes"))
			{

				for(var i = 0; i < val.content.length; i++)
				{
					var p = '<li><a onClick="document.getElementById(\''+val.content[i].nodename+'\').scrollIntoView(); window.scrollBy(0,-75);">'+val.content[i].nodename+'</a></li>';

					var thisNew = "<ul>";
					for (var a = 0; a < val.content[i].actions.length; a++) {
						thisNew += "<li>"+val.content[i].actions[a].portno+ ' ' + val.content[i].actions[a].action + "</li>";
					}
					thisNew += "</ul>";
					var tdata = "<tr id='"+val.content[i].nodename+"'>" +
						"<td><strong>"+val.content[i].nodename+"</strong></td>" +
						"<td>"+val.content[i].description+"</td>" +
						"<td>"+val.content[i].nodename+"</td>" +
						"<td>"+thisNew+"</td>" +
						"</tr>";

					$(tdata).appendTo('#tbody');
					$(p).appendTo('#nodescontent');
				}
			}
		});
	});
});
