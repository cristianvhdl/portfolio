
<%@ page language="java" import="cs5530.*" %>
<html>
<head>

  <title>uTrack Browse POIs</title>

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

    <h1>browsing poi, enter the follow filters... (leave blank to skip)</h1><br>
  
<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="browse_form" method=post  action="6.jsp">
        <input type=hidden name="searchAttribute" value="browse">
		<label for="plx">lower bound price range:</label>
		<input type=number max="100" min="0" value="5"name="plx">
		<br>
		<label for="plx">upper bound price range:</label>
		<input type=number max="100" min="0" value="55"name="plx">
		<br>
		<label for="addrx">address: (enter city or state)</label>
		<input type=text name="addrx">
		<br>
		<label for="keyx">keyword:</label>
		<input type=text name="keyx">
		<br>
		<label for="catx">category:</label>
		<input type=text name="catx">
		<br>
		<input type="radio" name="orderby" value="a" checked> order by price<br>
  		<input type="radio" name="orderby" value="b"> order by the avg numerical score of the feedbacks<br>
  		<input type="radio" name="orderby" value="c"> order by the avg numerical score of the trusted user feedbacks<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String plx =   request.getParameter("plx");
    String phx =   request.getParameter("phx");
    String addrx = request.getParameter("addrx");
    String keyx =  request.getParameter("keyx");
    String catx =  request.getParameter("catx");
    String orderby = request.getParameter("orderby");
    Browse b = new Browse();
    String result = b.poi((String)session.getAttribute("login"), plx,phx,addrx,keyx,catx,orderby);
    if (result.equals(""))
      out.print("no such POI");
    out.print(result);
}
%>

<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>