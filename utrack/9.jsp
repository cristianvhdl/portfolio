<%@ page language="java" import="cs5530.*" %>
<html>
<head>

  <title>uTrack Login</title>

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

    <h2>two degrees of seperation</h2><br>

<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="2sep_form" method=post  action="9.jsp">
        <input type=hidden name="searchAttribute" value="login">
		<label for="login2">enter another user to find degree of seperation:</label>
		<input type=text name="login2">
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String login = (String)session.getAttribute("login");
    String login2 = request.getParameter("login2");
    Account a = new Account();
    String result = a.degree_seperation(login, login2);
    out.print(result);
}
%>
<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>