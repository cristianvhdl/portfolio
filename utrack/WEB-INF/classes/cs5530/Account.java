package cs5530;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;

public class Account 
{
	Connector con=null;
	Connector con2=null;
	String input = "", login = null, query, query2;
	ResultSet results, results2;

	public String login(){

		try{
			con= new Connector();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

			while ((input = in.readLine()) == null && input.length() == 0);
			if(input.equalsIgnoreCase("y"))
			{

				System.out.println("login: ");
				login = in.readLine();
				// check if name exists
				query = "SELECT login FROM user WHERE login='"+login+"'";
				try {
					results = con.stmt.executeQuery(query);
					if (!results.next())
					{
						System.err.println("the username "+login+" does not exsist\n");								
						return null;
					}

				} catch (Exception e){
					System.err.println(e.getMessage());
					throw(e);
				}

				System.out.println("password: ");
				input = in.readLine();
				// check if password matches
				query = "SELECT pswrd FROM user WHERE login='"+login+"' AND pswrd='"+input+"'";
				try {
					results = con.stmt.executeQuery(query);
					if (!results.next())
					{
						System.err.println("wrong password.\n");
						return null;	

					}

				} catch (Exception e){
					System.err.println(e.getMessage());
					throw(e);
				}

				//if credentials match
				System.out.println("Welcome Back, " + login);

			}
			else if (input.equalsIgnoreCase("n"))
			{
				String pswd, name, address, phone;
				System.out.println("let's get you set up on UTrack!");
				System.out.println("type your new login: ");
				login = in.readLine();

				// check if login name is available
				query = "SELECT login FROM user WHERE login='"+login+"'";
				tryagain:
					try {
						results = con.stmt.executeQuery(query);
						if (results.next())
						{
							System.out.println("looks like that login name is taken, pick a new login:");
							login = in.readLine();
							break tryagain;
						}
					} catch (Exception e){
						System.err.println(e.getMessage());
						throw(e);
					}

				// obtain other information on table. No restrictions
				System.out.println("type your new password: ");
				pswd = in.readLine();
				System.out.println("what's your name: ");
				name = in.readLine();
				System.out.println("what's your address: ");
				address = in.readLine();
				System.out.println("what's your number: ");
				phone = in.readLine();

				// insert new user into user table
				query = "INSERT INTO user (login, name, admin, pswrd, address, phone) VALUES ('" +login+ "', '" +name+ "', 'n', '" +pswd+ "', '" +address+ "', '" +phone+ "')";
				try {
					if (con.stmt.execute(query))
					{
						System.err.println("couldn't add user to database.");
						//break;								
					}

				} catch (Exception e){
					System.err.println(e.getMessage());
					throw(e);
				}
			}

			con.closeConnection();
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}

		return login;
	}

	public String login(String username, String password)
	{
		try{
			con= new Connector();
			query = "SELECT pswrd FROM user WHERE login='"+username+"' AND pswrd='"+password+"'";
			try {
				results = con.stmt.executeQuery(query);
				if (!results.next())
				{
					con.closeConnection();
					return "error";
				}

			} catch (Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}


			con2 = new Connector();
			query = "SELECT * FROM user WHERE admin ='y' AND login ='"+username+"'";
			results = con2.stmt.executeQuery(query);
			try {
				if (results.first())
				{
					con2.closeConnection();
					return "admin";							
				}

			} catch (Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}
			con.closeConnection();
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}


		return "Ah, poop.";

	}

	public Boolean isAdmin() throws Exception{
		Boolean b = false;

		try{
			con= new Connector();
			//BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			query = "SELECT * FROM user WHERE admin ='y' AND login ='"+login+"'";
			results = con.stmt.executeQuery(query);
			try {
				if (results.first())
				{
					b = true;							
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

		return b;
	}

	public void award(){
		int n = 0, m = 0;
		try{
			String user;
			con = new Connector();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			System.out.println("enter the number of users you wish to award: ");
			while ((input = in.readLine()) == null && input.length() == 0);
			try{
				m = Integer.parseInt(input);
			}catch (Exception e){
				System.out.println("invalid input");
			}

			query ="select tt.login2, y-n from (select t.*, (select count(trusted) from trust where trusted='y' and t.login2 = login2) as y,  (select count(trusted) from trust where trusted='n' and t.login2 = login2) as n from trust t group by t.login2) as tt order by y-n desc";
			System.out.println("the most trusted users are: ");
			try{
				results = con.stmt.executeQuery(query);
				results.beforeFirst();
				// general idea taken from stackoverflow
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				while (results.next() && n < m) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) System.out.print(",  ");
						String columnValue = results.getString(i);
						System.out.print(rsmd.getColumnName(i) + ": " + columnValue);
						//output += "<tr><td>" + rsmd.getColumnName(i) +"</td><td>"+columnValue+"</td></tr>";
					}
					System.out.println("");
					//output += "</table>";
					n++;
				}
			}catch(Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}

			n=0;

			query ="SELECT f.login, sum(rating) as total FROM feedback f, rates r where r.fid=f.fid group by r.fid";
			System.out.println("the most useful users are: ");
			try{
				results = con.stmt.executeQuery(query);
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
			}catch(Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}




		}catch(Exception e){

		}
	}

	public String award(int m){
		int n = 0;
		String output = "";
		try{
			con = new Connector();
			System.out.println("enter the number of users you wish to award: ");
			// m

			query ="select tt.login2, y-n from (select t.*, (select count(trusted) from trust where trusted='y' and t.login2 = login2) as y,  (select count(trusted) from trust where trusted='n' and t.login2 = login2) as n from trust t group by t.login2) as tt order by y-n desc";
			System.out.println("the most trusted users are: ");
			output += "<br>the most trusted users are: <br>";
			try{
				results = con.stmt.executeQuery(query);
				results.beforeFirst();
				// general idea taken from stackoverflow
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				while (results.next() && n < m) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) 
						{
							System.out.print(",  ");
							output += ",	";
						}
						String columnValue = results.getString(i);
						System.out.print(rsmd.getColumnName(i) + ": " + columnValue);
						output += rsmd.getColumnName(i) + ": " + columnValue;
					}
					System.out.println("");
					output += "<br>";
					n++;
				}
			}catch(Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}

			n=0;

			query ="SELECT f.login, sum(rating) as total FROM feedback f, rates r where r.fid=f.fid group by r.fid";
			System.out.println("the most useful users are: ");
			output += "the most useful users are: <br>";
			try{
				results = con.stmt.executeQuery(query);
				results.beforeFirst();
				// general idea taken from stackoverflow
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				while (results.next() && n < m) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) 
						{
							System.out.print(",  ");
							output += ",	";
						}
						String columnValue = results.getString(i);
						System.out.print(rsmd.getColumnName(i) + ": " + columnValue);
						output += rsmd.getColumnName(i) +": "+columnValue;
					}
					System.out.println("");
					output += "<br>";
					n++;
				}
			}catch(Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}

		}catch(Exception e){}

		return output;
	}

	public void degree_seperation(String login){
		try{
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			System.out.println("enter another user name: ");
			String login2 = in.readLine();
			con= new Connector();
			con2= new Connector();

			query = "SELECT X.login as CU, Y.login OU, X.pid FROM favorite X, favorite Y WHERE X.pid = Y.pid AND X.login <> Y.login AND X.login = '"+login+"' HAVING OU = '"+login2+"'";
			query2 = "SELECT * FROM (SELECT X.login as CU, Y.login OU, X.pid FROM favorite X, favorite Y WHERE X.pid = Y.pid AND X.login <> Y.login AND X.login = '"+login+"') AS A, (SELECT X.login as CU, Y.login OU, X.pid FROM favorite X, favorite Y WHERE X.pid = Y.pid AND X.login <> Y.login AND X.login = '"+login2+"') AS B WHERE A.OU = B.OU";

			try {
				results = con.stmt.executeQuery(query);
				results2= con2.stmt.executeQuery(query2);
				if (results.next())
					System.out.println("one degree");
				if(results2.next())
					System.out.println("two degrees");
				else
					System.out.println("neither");



			} catch (Exception e){
				System.err.println("there was some trouble with your request.");
				e.printStackTrace();
			}
			con.closeConnection();
		}catch (Exception e){
			e.printStackTrace();
		}

	}

	public String degree_seperation(String login, String login2)
	{
		String output = "";
		try{
			con= new Connector();
			con2= new Connector();

			query = "SELECT X.login as CU, Y.login OU, X.pid FROM favorite X, favorite Y WHERE X.pid = Y.pid AND X.login <> Y.login AND X.login = '"+login+"' HAVING OU = '"+login2+"'";
			query2 = "SELECT * FROM (SELECT X.login as CU, Y.login OU, X.pid FROM favorite X, favorite Y WHERE X.pid = Y.pid AND X.login <> Y.login AND X.login = '"+login+"') AS A, (SELECT X.login as CU, Y.login OU, X.pid FROM favorite X, favorite Y WHERE X.pid = Y.pid AND X.login <> Y.login AND X.login = '"+login2+"') AS B WHERE A.OU = B.OU";

			try {
				results = con.stmt.executeQuery(query);
				results2= con2.stmt.executeQuery(query2);
				if (results.next())
					output = "one degree";
				if(results2.next())
					output = "two degrees";
				else
					output = "neither";



			} catch (Exception e){
				output = "there was some trouble with your request.";
				e.printStackTrace();
			}
			con.closeConnection();
		}catch (Exception e){
			e.printStackTrace();
		}

		return output;
	}

	public void trust(String login1)
	{
		String login2, trusted;
		try{
			System.out.println("enter the user's login that you would like to mark as 'trusted' or 'not trusted':");
			con= new Connector();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

			login2 = in.readLine();
			System.out.println("is the user trusted? y/n");
			trusted = in.readLine();
			query = "INSERT INTO trust (login1, login2, trusted) VALUES ('" +login1+ "', '" +login2+ "', '" +trusted+ "')";
			try {
				if (con.stmt.execute(query))
				{
					System.err.println("there was some trouble with your request.");							
				}

			} catch (Exception e){

			}
			con.closeConnection();
		}catch (Exception e){
			e.printStackTrace();
		}

	}

	public String trust(String login1, String login2, String trusted)
	{
		String output = "request was successful";
		try{
			System.out.println("enter the user's login that you would like to mark as 'trusted' or 'not trusted':");
			con= new Connector();
			//System.out.println("is the user trusted? y/n");
			query = "INSERT INTO trust (login1, login2, trusted) VALUES ('" +login1+ "', '" +login2+ "', '" +trusted+ "')";
			try {
				if (con.stmt.execute(query))
				{
					output = "there was some trouble with your request.";							
				}

			} catch (Exception e){

			}
			con.closeConnection();
		}catch (Exception e){
			e.printStackTrace();
		}

		return output;

	}

	public String register(String login, String pswd, String name, String address, String phone){
		String output = "";
		try{
			con= new Connector();

			// check if login name is available
			query = "SELECT login FROM user WHERE login='"+login+"'";
				try {
					results = con.stmt.executeQuery(query);
					if (results.next())
					{
						output = "error";
					}
				} catch (Exception e){
					System.err.println(e.getMessage());
					throw(e);
				}

			// insert new user into user table
			query = "INSERT INTO user (login, name, admin, pswrd, address, phone) VALUES ('" +login+ "', '" +name+ "', 'n', '" +pswd+ "', '" +address+ "', '" +phone+ "')";
			try {
				if (con.stmt.execute(query))
				{
					output = "error";								
				}

			} catch (Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}

			con.closeConnection();
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}

		return output;
	}
}

