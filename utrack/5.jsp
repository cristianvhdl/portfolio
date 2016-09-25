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
	<h2>Rate User</h2>

<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="award_form" method=post  action="5.jsp">
        <input type=hidden name="searchAttribute" value="login">
		<label for="login2">enter the user's login that you would like to mark as 'trusted' or 'not trusted':</label>
		<input type=text name="login2">
		<br>
		<input type="radio" name="trust" value="y" checked> y<br>
  		<input type="radio" name="trust" value="n"> n<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
	String login2 = request.getParameter("login2");
	String trust = request.getParameter("trust");
    Account a = new Account();
    String result = a.trust((String)session.getAttribute("login"), login2, trust);
    out.print(result);
}
%>
	<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>