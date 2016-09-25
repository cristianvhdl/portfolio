
<%@ page language="java" import="cs5530.*" %>
<html>
<head>

  <title>uTrack Suggestions</title>

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

    <h1>Find Suggestions based on another POI</h1><br>

    <%
    out.print((String)session.getAttribute("result"));
    %>
  
<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="s3l_form" method=post  action="8-1.jsp">
        <input type=hidden name="searchAttribute" value="lgs">
		<label for="pid">select the pid you like to find other suggestions:</label>
		<input type=text name="pid">
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String pid = request.getParameter("pid");
    Feedback a = new Feedback();
    String result = a.suggestions(pid);
    out.print(result);
}
%>

<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>