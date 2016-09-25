
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
    %>
  
<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="usef_form" method=post  action="4-1.jsp">
        <input type=hidden name="searchAttribute" value="asd">
		<label for="pid">select the pid you want to record as 'visited':</label>
		<input type=text name="pid">
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String pid = request.getParameter("pid");
    Feedback f = new Feedback();
    String result = f.searchfid(pid);
    session.setAttribute("result", result);
    response.sendRedirect("4-2.jsp");
}
%>

<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>