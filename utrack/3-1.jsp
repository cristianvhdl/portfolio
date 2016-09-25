<%@ page language="java" import="cs5530.*" %>
<html>
<head>

  <title>uTrack Feedback</title>

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

    <h1>Record Feedback for POI</h1><br>

    <%
    out.print((String)session.getAttribute("result"));
    %>
  
<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="feed_form" method=post  action="3-1.jsp">
        <input type=hidden name="searchAttribute" value="fav">
		<label for="pid">select the pid you want to record feedback for:</label>
		<input type=text name="pid">
		<br>
		<label for="score">enter the score:</label>
		<input type=number max="10" min="1" value="5" name="score">
		<br>
		<label for="text">enter feedback summary:</label>
		<textarea name="text" cols="50" rows="10"></textarea>
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String pid = request.getParameter("pid");
    String score = request.getParameter("score");
    String text = request.getParameter("text");
    POI a = new POI();
    String result = a.feedback((String)session.getAttribute("login"), pid, score, text);
    out.print(result);
}
%>

<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>