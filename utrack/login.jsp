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

    <h1>uTrack</h1><br>

<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="login_form" method=post  action="login.jsp">
        <input type=hidden name="searchAttribute" value="login">
		<label for="login">Login:</label>
		<input type=text name="login" value="admin">
		<br>
		<label for="pswrd">Password:</label>
		<input type=password name="password" value="a">
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String login = request.getParameter("login");
    String pswrd = request.getParameter("password");
    Account a = new Account();
    String result = a.login(login, pswrd);
    out.print(result);
    if (result.equals("error"))
        out.print("<p>There was an error with your request</p>");
    session.setAttribute("login", login);
    if (result.equals("admin"))
        session.setAttribute("admin", result);
    
   if (!result.equals("error"))
        response.sendRedirect("main.jsp");
}
%>
	
</body>
</html>