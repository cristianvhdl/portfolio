
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

    <h1>uTrack Find Useful Feedback</h1><br>

    <%
    out.print((String)session.getAttribute("result"));
    %>
  
<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="sl_form" method=post  action="7-1.jsp">
        <input type=hidden name="searchAttribute" value="ls">
		<label for="pid">select the pid you want to view useful feedback for:</label>
		<input type=text name="pid">
		<br>
		<label for="sa">enter the number of results you would like to display:</label>
		<input type=number name="sa" min="1" max="100" value="10">
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String pid = request.getParameter("pid");
    String sa = request.getParameter("sa");
    Feedback a = new Feedback();
    String result = a.showUseful( pid, sa);
    out.print(result);
}
%>

<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>