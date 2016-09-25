<%@ page language="java" import="cs5530.*" %>
<html>
<head>
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

<%
String searchAttribute = request.getParameter("searchAttribute");
if( searchAttribute == null ){
%>

	Username:
	<form name="user_search" method=get onsubmit="return check_all_fields(this)" action="driver.jsp">
		<input type=hidden name="searchAttribute" value="login">
		<input type=text name="attributeValue" length=10>
		<input type=submit>
	</form>
	Password:
	<form name="password_search" method=get onsubmit="return check_all_fields(this)" action="driver.jsp">
		<input type=hidden name="searchAttribute" value="password">
		<input type=text name="attributeValue" length=10>
		<input type=submit>
	</form>

<%

} else {

	String attributeValue = request.getParameter("attributeValue");
	Connector connector = new Connector();
	Account a = new Account();
	
%>  

  <p><b>Listing orders in JSP: </b><BR><BR>

  The orders for query: <b><%=searchAttribute%>='<%=attributeValue%>'</b> are  as follows:<BR><BR>
  <%=a.login(attributeValue)%> <BR><BR>
  
  <b>Alternate way (servlet method):</b> <BR><BR>
  <%
		//out.println("The orders for query: <b>"+searchAttribute+"='"+attributeValue+
		//			"'</b> are as follows:<BR><BR>");
		//out.println(order.getOrders(searchAttribute, attributeValue, connector.stmt));
  %>

<%
 //connector.closeStatement();
 //connector.closeConnection();
}  // We are ending the braces for else here
%>

<BR><a href="driver.jsp"> New query </a></p>

<p>jiberish <font face="Geneva, Arial, Helvetica, sans-serif">( 
  title varchar(100), quantity integer, login varchar(8), director varchar(10) 
  )</font></p>

</body>
