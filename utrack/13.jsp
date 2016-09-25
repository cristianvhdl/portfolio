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
	<h2>Award User</h2>

<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="award_form" method=post  action="13.jsp">
        <input type=hidden name="searchAttribute" value="login">
		<label for="num">enter the number of users you wish to award:</label>
		<input type=number name="num" value=1 min=1 max=10>
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
	int num = Integer.parseInt(request.getParameter("num"));
    Account a = new Account();
    String result = a.award(num);
    out.print(result);
}
%>
	<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>