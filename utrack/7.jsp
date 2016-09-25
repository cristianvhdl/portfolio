
<%@ page language="java" import="cs5530.*" %>
<html>
<head>

  <title>uTrack Find Useful Feedback</title>

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

    <h1>Find Useful Feedback for a POI</h1><br>
  
<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="er_form" method=post  action="7.jsp">
        <input type=hidden name="searchAttribute" value="tr">
		<label for="pid">select the poi you wish to find useful feedback for:</label>
		<input type=text name="pid">
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String pid = request.getParameter("pid");
    POI a = new POI();
    String result = a.search((String)session.getAttribute("login"), pid);
    session.setAttribute("result", result);
    response.sendRedirect("7-1.jsp");
}
%>

<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>