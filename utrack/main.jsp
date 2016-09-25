<%@ page language="java" import="cs5530.*" %>
<html>
<head>

  <title>uTrack Menu</title>

<script LANGUAGE="javascript">

function check_all_fields(form_obj){
	alert(form_obj.searchAttribute.value+"='"+form_obj.attributeValue.value+"'");
	if( form_obj.attributeValue.value == ""){
		alert("Search field should be nonempty");
		return false;
	}
	return true;
}

</script> 
</head>
<body>
        <h1>Select what would you like to do: </h1><br>
		<a href="1.jsp">1.  record a 'visit' for a point of interest</a href><br>
		<a href="2.jsp">2.  declare a favorite place to visit</a href><br>
		<a href="3.jsp">3.  record feedback for point of interest</a href><br>
		<a href="4.jsp">4.  record usefullness of another's review</a href><br>
		<a href="5.jsp">5.  declare a user as 'trusted' or 'not-trusted'</a href><br>
		<a href="6.jsp">6.  browse for a point of interest</a href><br>
		<a href="7.jsp">7.  find useful feedback for a point of interest</a href><br>
		<a href="8.jsp">8.  view other suggestions</a href><br>
		<a href="9.jsp">9.  find degree of seperation</a href><br>
		<a href="10.jsp">10. show stats</a href><br>
		
		<%if(session.getAttribute("admin") != null  && session.getAttribute("admin").equals("admin"))
			{

			out.print("<a href=\"11.jsp\">11. add new point of interest*</a href><br>");
			out.print("<a href=\"12.jsp\">12. update existing point of interest*</a href><br>");
			out.print("<a href=\"13.jsp\">13. award another user*</a href><br>");
			out.print("* admin only");

		} %>
		<br><br><br>
		<a href="index.html">logout</a href>	
	
</body>
</html>