
<%@ page language="java" import="cs5530.*" %>
<html>
<head>

  <title>uTrack Update POI</title>

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

    <h1>Update POI</h1><br>

    <%
    out.print((String)session.getAttribute("result"));
    %>
  
<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	<form name="add_form" method=post  action="12-1.jsp">
        <input type=hidden name="searchAttribute" value="add">
		<label for="pid">enter the pid of the poi you wish to update:</label>
		<input type=text name="pid">
		<br>
		<label for="address">updated address:</label>
		<input type=text name="address">
		<br>
		<label for="url">updated website url:</label>
		<input type=text name="url">
		<br>
		<label for="phone">updated phone number:</label>
		<input type=text name="phone">
		<br>
		<label for="cat">updated category:</label>
		<input type=text name="cat">
		<br>
		<label for="ophrs">updated operation hours:</label>
		<input type=text name="ophrs" value="8am-8pm">
		<br>
		<label for="yoe">updated year of establishment:</label>
		<input type=number ="yoe" max="2016" min="1990" value="2016">
		<br>
		<label for="price">updated average price per person:</label>
		<input type=number name="price" min="1" value="10">
		<br>
		<input type=submit>
	</form>
	<br>


<%
} else {
    String pid = request.getParameter("pid");
    String address = request.getParameter("address");
    String url = request.getParameter("url");
    String phone = request.getParameter("phone");
    String cat = request.getParameter("cat");
    String ophrs = request.getParameter("ophrs");
    String yoe = request.getParameter("yoe");
    String price = request.getParameter("price");
    POI a = new POI();
    String result = a.update(pid, address, url, phone, cat, ophrs, yoe, price);
    out.print(result);
}
%>

<br>
<a href="main.jsp">return to main menu</a href>	
</body>
</html>