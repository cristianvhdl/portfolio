
<%@ page language="java" import="cs5530.*" %>
<html>
<head>

  <title>uTrack Usefullness</title>

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

    <h1>Record Usefullness of Another's Review</h1><br>

    <%
    out.print((String)session.getAttribute("result"));
    if(((String)session.getAttribute("result")).equals("select the fid for the feeback you wish to mark as 'useless,' 'useful,' or 'very useful':<br>"))
    	out.print("<br>...there are no reviews for this particular poi...<br><br>");
    %>
  
<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="usefulness1_form" method=post  action="4-2.jsp">
        <input type=hidden name="searchAttribute" value="dsa">
		<label for="fid">select the fid for the feeback you wish to rate:</label>
		<input type=text name="fid">
		<br>
		<label for="rating">enter the '0' for 'useless,' '1' for 'useful,' and '2' for 'very useful':</label>
		<input type=number name="rating" max="2" min="0">
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String fid = request.getParameter("fid");
    String rating = request.getParameter("rating");
    Feedback f = new Feedback();
    String result = f.usefulness((String)session.getAttribute("login"), fid, rating);
    out.print(result);
}
%>

<br>

<a href="main.jsp">return to main menu</a href>	
</body>
</html>