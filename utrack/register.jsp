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
<h1> let's get you set up on UTrack! </h1>

<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="login_form" method=post onsubmit="return check_all_fields(this)" action="register.jsp">
        <input type=hidden name="searchAttribute" value="login">
		<label for="login">Login*:</label>
		<input type=text name="login">
		<br>
		<label for="pswrd">Password*:</label>
		<input type=password name="password">
		<br>
		<label for="name">Name:</label>
		<input type=text name="name">
		<br>
		<label for="addr">Address:</label>
		<input type=text name="address">
		<br>
		<label for="num">Number:</label>
		<input type=text name="number">
		<br>
		*required
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String login = request.getParameter("login");
    String pswrd = request.getParameter("password");
    String name = request.getParameter("name");
    String address = request.getParameter("address");
    String number = request.getParameter("number");
    Account a = new Account();
    String result = a.register(login, pswrd, name, address, number);
    if (result.equals("error"))
        out.print("<p>There was an error with your request</p>");
    session.setAttribute("login", login);
    if (!request.equals("error"))
    	response.sendRedirect("main.jsp");
}
%>
	
</body>
</html>