
<%@ page language="java" import="cs5530.*" %>
<html>
<head>

  <title>uTrack Stats</title>

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

    <h1>Find Stats on All POIs</h1><br>

  
<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="s3ol_form" method=post  action="10.jsp">
        <input type=hidden name="searchAttribute" value="lgos">
		<label for="sa">enter the number of stats you wish to display:</label>
		<input type=number max="10" min="1" value="5" name="sa">
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String sa = request.getParameter("sa");
    Browse b = new Browse();
    String result = b.stats(sa);
    out.print(result);
}
%>

<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>