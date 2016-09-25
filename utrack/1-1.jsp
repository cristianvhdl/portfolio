
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
    out.print((String)session.getAttribute("result"));
    %>
  
<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="fav_form" method=post  action="1-1.jsp">
        <input type=hidden name="searchAttribute" value="fav">
		<label for="pid">select the pid you want to record as 'visited':</label>
		<input type=text name="pid">
		<br>
		<label for="cost">enter the total cost of the visit:</label>
		<input type=text name="cost">
		<br>
		<label for="party">enter the party size:</label>
		<input type=text name="party">
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String pid = request.getParameter("pid");
    String cost = request.getParameter("cost");
    String party = request.getParameter("party");
    POI a = new POI();
    String result = a.visit((String)session.getAttribute("login"), pid, cost, party);
    out.print(result);
}
%>

<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>