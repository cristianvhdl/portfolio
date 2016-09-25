package cs5530;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;

public class Browse {
	
	Connector con=null;
	String input = "", login = null, query;
	ResultSet results;
	
	public void poi(String login) throws Exception
	{
		Boolean pfl=true, pfh=true, af=true, kf=true, cf=true;
		int pl = 0, ph = 0;
		String addr, key, cat;
		try{
			con= new Connector();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			System.out.println("browsing poi, enter the follow filters... (enter to skip)");
			System.out.println("lower bound price range: ");
			input = in.readLine();
			try{
				pl = Integer.parseInt(input);
			}catch(Exception e){
				pfl = false;
			}
			System.out.println("upper bound price range: ");
			input = in.readLine();
			try{
				ph = Integer.parseInt(input);
			}catch(Exception e){
				pfh = false;
			}
			System.out.println("address: (enter city or state)");
			addr = in.readLine();
			if(addr.isEmpty())
				af = false;
			System.out.println("keyword: ");
			key = in.readLine();
			if(key.isEmpty())
				kf = false;
			System.out.println("category: ");
			cat = in.readLine();
			if(cat.isEmpty())
				cf = false;
			
			System.out.println("order by... ");
			System.out.println("a. by price");
			System.out.println("b. by the avg numerical score of the feedbacks");
			System.out.println("c. by the avg numerical score of the trusted user feedbacks");
			input = in.readLine();
			
			query = "SELECT * FROM poi p WHERE ";
			
			if(pfl && pfh)
				query += "price > '" +pl+ "' AND price < '" +ph+ "' ";
			else
				query += "TRUE ";
			
			if (af)
				query += "AND address LIKE '%" +addr+ "%' ";
			
			if(kf)
				query += "AND p.pid in (SELECT hasKeyword.pid FROM hasKeyword, keyword WHERE hasKeyword.wid = keyword.wid AND word LIKE '%" +key+ "%')";
			
			if(cf)
				query += "AND cat LIKE '%" +cat+ "%'";
			
			if(input.equalsIgnoreCase("a"))
				query += "ORDER BY price DESC";
			
			if(input.equalsIgnoreCase("b"))
			{
				String temp = query;
				query = "SELECT f.pid, a.pname, a.address, a.url, a.phone, a.year, a.cat, a.price, a.ophrs, AVG(score) as average FROM feedback f, ("+temp+") as a WHERE a.pid = f.pid GROUP BY f.pid ORDER BY average DESC";
			}
			if(input.equalsIgnoreCase("b"))
			{
				String temp = query;
				query = "SELECT f.pid, a.pname, a.address, a.url, a.phone, a.year, a.cat, a.price, a.ophrs, AVG(score) as average FROM feedback f, ("+temp+") as a, (SELECT login2 FROM trust WHERE login1 ='"+login+"' AND trusted = 'y') WHERE a.pid = f.pid GROUP BY f.pid ORDER BY average DESC";
			}
			
			
			
			try {
				results = con.stmt.executeQuery(query);
				
				results.beforeFirst();
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				while (results.next()) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) System.out.print(",  ");
						String columnValue = results.getString(i);
						System.out.print(rsmd.getColumnName(i) + ": " + columnValue);
					}
					System.out.println("");
				}
			} catch (Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}
			
			con.closeConnection();
		}catch (Exception e){
			System.err.println(e.getMessage());
			throw(e);
		}
	}
	
	public String poi(String login, String plx, String phx, String addrx, String keyx, String catx, String orderby)
	{
		String output = "";
		Boolean pfl=true, pfh=true, af=true, kf=true, cf=true;
		int pl = 0, ph = 0;
		String addr, key, cat;
		try{
			con= new Connector();
			System.out.println("browsing poi, enter the follow filters... (leave blank to skip)");
			System.out.println("lower bound price range: ");
			try{
				pl = Integer.parseInt(plx);
			}catch(Exception e){
				pfl = false;
			}
			System.out.println("upper bound price range: ");
			try{
				ph = Integer.parseInt(phx);
			}catch(Exception e){
				pfh = false;
			}
			System.out.println("address: (enter city or state)");
			addr = addrx;
			if(addr.isEmpty())
				af = false;
			System.out.println("keyword: ");
			key = keyx;
			if(key.isEmpty())
				kf = false;
			System.out.println("category: ");
			cat = catx;
			if(cat.isEmpty())
				cf = false;
			
			System.out.println("order by... ");
			System.out.println("a. by price");
			System.out.println("b. by the avg numerical score of the feedbacks");
			System.out.println("c. by the avg numerical score of the trusted user feedbacks");
			
			query = "SELECT * FROM poi p WHERE ";
			
			if(pfl && pfh)
				query += "price > '" +pl+ "' AND price < '" +ph+ "' ";
			else
				query += "TRUE ";
			
			if (af)
				query += "AND address LIKE '%" +addr+ "%' ";
			
			if(kf)
				query += "AND p.pid in (SELECT hasKeyword.pid FROM hasKeyword, keyword WHERE hasKeyword.wid = keyword.wid AND word LIKE '%" +key+ "%')";
			
			if(cf)
				query += "AND cat LIKE '%" +cat+ "%'";
			
			if(orderby.equalsIgnoreCase("a"))
				query += "ORDER BY price DESC";
			
			if(orderby.equalsIgnoreCase("b"))
			{
				String temp = query;
				query = "SELECT f.pid, a.pname, a.address, a.url, a.phone, a.year, a.cat, a.price, a.ophrs, AVG(score) as average FROM feedback f, ("+temp+") as a WHERE a.pid = f.pid GROUP BY f.pid ORDER BY average DESC";
			}
			if(orderby.equalsIgnoreCase("b"))
			{
				String temp = query;
				query = "SELECT f.pid, a.pname, a.address, a.url, a.phone, a.year, a.cat, a.price, a.ophrs, AVG(score) as average FROM feedback f, ("+temp+") as a, (SELECT login2 FROM trust WHERE login1 ='"+login+"' AND trusted = 'y') WHERE a.pid = f.pid GROUP BY f.pid ORDER BY average DESC";
			}
			
			
			
			try {
				results = con.stmt.executeQuery(query);
				
				results.beforeFirst();
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				while (results.next()) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) output+=(",  ");
						String columnValue = results.getString(i);
						output+=(rsmd.getColumnName(i) + ": " + columnValue);
					}
					output+=("<br>");
				}
			} catch (Exception e){
				output+=e.toString();
			
			}
			
			con.closeConnection();
		}catch (Exception e){
			output+=e.toString();
			
		}
		return output;
	}

	public void stats() throws Exception{
		try{
			int n=0,m=0;
			con = new Connector();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			System.out.println("enter the number of stats you wish to display: ");
			while ((input = in.readLine()) == null && input.length() == 0);
			try{
				m = Integer.parseInt(input);
			}catch (Exception e){
				System.out.println("invalid input");
			}
			
			query ="SELECT cat, pname FROM (SELECT p.cat, p.pname, @r:=case when @g=p.cat then @r+1 else 1 end r, @g:=p.cat FROM (select @g:=null,@r:=0) n cross join visit v  left join poi p on v.pid = p.pid ) X WHERE r <="+m;
			
			try{
				results = con.stmt.executeQuery(query);
				System.out.println("the most popular pois(in terms of visits) for each category:\n");
				results.beforeFirst();
				// general idea taken from stackoverflow
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				while (results.next() && n < m) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) System.out.print(",  ");
						String columnValue = results.getString(i);
						System.out.print(rsmd.getColumnName(i) + ": " + columnValue);
					}
					System.out.println("");
					n++;
				}
				n=0;
			}catch(Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}
			
			query = "SELECT x.pname, x.cat, y.av FROM ( SELECT p.cat, p.pname, p.pid, @r:=case when @g=p.cat then @r+1 else 1 end r, @g:=p.cat, v.cost FROM (select @g:=null,@r:=0) n cross join visit v  left join poi p on v.pid = p.pid ) x, (select pid, avg(cost)/party av from visit group by pid) y WHERE r <= 5 and y.pid = x.pid ORDER BY y.av DESC";
			
			try{
				results = con.stmt.executeQuery(query);
				System.out.println("the most popular pois(in terms of visits) for each category:\n");
				results.beforeFirst();
				// general idea taken from stackoverflow
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				while (results.next() && n < m) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) System.out.print(",  ");
						String columnValue = results.getString(i);
						System.out.print(rsmd.getColumnName(i) + ": " + columnValue);
					}
					System.out.println("");
					n++;
				}
				n=0;
			}catch(Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}
			
			query = "SELECT x.pname, x.cat, y.average FROM ( SELECT p.cat, p.pname, p.pid, @r:=case when @g=p.cat then @r+1 else 1 end r, @g:=p.cat, v.cost FROM (select @g:=null,@r:=0) n cross join visit v  left join poi p on v.pid = p.pid ) x, (select pid, avg(score) average from feedback group by pid) y WHERE r <= 5 and y.pid = x.pid ORDER BY y.average DESC";
			
			try{
				results = con.stmt.executeQuery(query);
				System.out.println("the most popular pois(in terms of visits) for each category:\n");
				results.beforeFirst();
				// general idea taken from stackoverflow
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				while (results.next() && n < m) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) System.out.print(",  ");
						String columnValue = results.getString(i);
						System.out.print(rsmd.getColumnName(i) + ": " + columnValue);
					}
					System.out.println("");
					n++;
				}
				n=0;
			}catch(Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}
			
			con.closeConnection();
		}catch (Exception e){
			System.err.println(e.getMessage());
			throw(e);
		}
	}
	
	public String stats(String amount) throws Exception{
		String output = "";
		try{
			int n=0,m=Integer.parseInt(amount);
			con = new Connector();
			//output +=("enter the number of stats you wish to display: ");
			
			query ="SELECT cat, pname FROM (SELECT p.cat, p.pname, @r:=case when @g=p.cat then @r+1 else 1 end r, @g:=p.cat FROM (select @g:=null,@r:=0) n cross join visit v  left join poi p on v.pid = p.pid ) X WHERE r <="+m;
			
			try{
				results = con.stmt.executeQuery(query);
				output +=("the most popular pois(in terms of visits) for each category:<br><br>");
				results.beforeFirst();
				// general idea taken from stackoverflow
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				while (results.next() && n < m) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) output += (",  ");
						String columnValue = results.getString(i);
						output+=(rsmd.getColumnName(i) + ": " + columnValue);
					}
					output +=("<br>");
					n++;
				}
				n=0;
			}catch(Exception e){
				output+=(e.getMessage());
				throw(e);
			}
			
			query = "SELECT x.pname, x.cat, y.av FROM ( SELECT p.cat, p.pname, p.pid, @r:=case when @g=p.cat then @r+1 else 1 end r, @g:=p.cat, v.cost FROM (select @g:=null,@r:=0) n cross join visit v  left join poi p on v.pid = p.pid ) x, (select pid, avg(cost)/party av from visit group by pid) y WHERE r <= 5 and y.pid = x.pid ORDER BY y.av DESC";
			
			try{
				results = con.stmt.executeQuery(query);
				output +=("the most popular pois(in terms of visits) for each category:<br><br>");
				results.beforeFirst();
				// general idea taken from stackoverflow
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				while (results.next() && n < m) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) output+=(",  ");
						String columnValue = results.getString(i);
						output+=(rsmd.getColumnName(i) + ": " + columnValue);
					}
					output +=("<br>");
					n++;
				}
				n=0;
			}catch(Exception e){
				output+=(e.getMessage());
				throw(e);
			}
			
			query = "SELECT x.pname, x.cat, y.average FROM ( SELECT p.cat, p.pname, p.pid, @r:=case when @g=p.cat then @r+1 else 1 end r, @g:=p.cat, v.cost FROM (select @g:=null,@r:=0) n cross join visit v  left join poi p on v.pid = p.pid ) x, (select pid, avg(score) average from feedback group by pid) y WHERE r <= 5 and y.pid = x.pid ORDER BY y.average DESC";
			
			try{
				results = con.stmt.executeQuery(query);
				output +=("the most popular pois(in terms of visits) for each category:<br>");
				results.beforeFirst();
				// general idea taken from stackoverflow
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				while (results.next() && n < m) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) output+=(",  ");
						String columnValue = results.getString(i);
						output+=(rsmd.getColumnName(i) + ": " + columnValue);
					}
				output +=("");
					n++;
				}
				n=0;
			}catch(Exception e){
				output+=(e.getMessage());
				throw(e);
			}
			
			con.closeConnection();
		}catch (Exception e){
			output+=(e.getMessage());
			throw(e);
		}
		return output;
	}
}
