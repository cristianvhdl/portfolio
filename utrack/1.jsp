<%@ page language="java" import="cs5530.*" %>
<html>
<head>

  <title>uTrack Visit</title>

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

    <h1>Visit POI</h1><br>

<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="search_form" method=post  action="1.jsp">
        <input type=hidden name="searchAttribute" value="search">
		<label for="poi">enter the name of the poi you would like to mark as 'visited':</label>
		<input type=text name="poi">
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String poi = request.getParameter("poi");
    POI a = new POI();
    String result = a.search((String)session.getAttribute("login"), poi);
    session.setAttribute("result", result);
    response.sendRedirect("1-1.jsp");
}
%>

<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>