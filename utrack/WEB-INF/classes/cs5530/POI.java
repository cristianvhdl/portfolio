package cs5530;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.util.ArrayList;

public class POI {
	Connector con=null;
	String input = "", login = null, query;
	ResultSet results;

	public void favorite(String login) {
		System.out.println("enter the name of your favorite poi: ");
		try{
			con= new Connector();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			while ((input = in.readLine()) == null && input.length() == 0);

			query = "SELECT * FROM poi WHERE pname='"+input+"'";
			try
			{
				results = con.stmt.executeQuery(query);
				if (!results.next()) // pname doesn't exist in UTrack db
				{
					System.out.println(input + " does not exist in the UTrack database.");
				}
				else 
				{
					String pid;
					System.out.println("select the pid you want to record as a favorite: ");
					results.beforeFirst();
					// general idea taken from stackoverflow
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
					pid = in.readLine();  // user selects intended poi
					java.sql.Date fvdate = new java.sql.Date(new java.util.Date().getTime());
					query = "INSERT INTO favorite (login, pid, fvdate) VALUES ('" +login+ "', '" +pid+ "', '"+fvdate+"')";
					try{
						con.stmt.execute(query);
						System.out.println("favorite poi recorded.");

					}catch (Exception e){
						System.err.println(e.getMessage());
						throw(e);
					}
				}
			}catch (Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}

			con.closeConnection();
		}catch (Exception e)
		{
			e.printStackTrace();
		}
	}

	public String search(String login, String input) {
		String output = "";
		System.out.println("enter the name of your favorite poi: ");
		try{
			con= new Connector();
			query = "SELECT * FROM poi WHERE pname='"+input+"'";
			try
			{
				results = con.stmt.executeQuery(query);
				if (!results.next()) // pname doesn't exist in UTrack db
				{
					System.out.println(input + " does not exist in the UTrack database.");
					output += input + " does not exist in the UTrack database.";
				}
				else 
				{
					String pid;
					System.out.println("select the pid you want to record as a favorite: ");
					output += "select a pid: <br>";
					results.beforeFirst();
					// general idea taken from stackoverflow
					ResultSetMetaData rsmd = results.getMetaData();
					int columnsNumber = rsmd.getColumnCount();
					while (results.next()) {
						for (int i = 1; i <= columnsNumber; i++) {
							if (i > 1){
								System.out.print(",  ");
								output += ",  ";
							}
							String columnValue = results.getString(i);
							System.out.print(rsmd.getColumnName(i) + ": " + columnValue);
							output += rsmd.getColumnName(i) + ": " + columnValue;
						}
						System.out.println("");
						output += "<br>";
					}
					//					// user selects intended poi
					//					java.sql.Date fvdate = new java.sql.Date(new java.util.Date().getTime());
					//					query = "INSERT INTO favorite (login, pid, fvdate) VALUES ('" +login+ "', '" +pid+ "', '"+fvdate+"')";
					//					try{
					//						con.stmt.execute(query);
					//						System.out.println("favorite poi recorded.");
					//						output += "favorite poi recorded.";
					//
					//					}catch (Exception e){
					//						System.err.println(e.getMessage());
					//						throw(e);
					//					}
				}
			}catch (Exception e){
				System.err.println(e.getMessage());
				output += e.getMessage();
				throw(e);
			}

			con.closeConnection();
		}catch (Exception e)
		{
			e.printStackTrace();
		}

		return output += "<br>";
	}

	public String favorite(String login, String pid) {
		String output = "";
		try{
			con= new Connector();

			// user selects intended poi
			java.sql.Date fvdate = new java.sql.Date(new java.util.Date().getTime());
			query = "INSERT INTO favorite (login, pid, fvdate) VALUES ('" +login+ "', '" +pid+ "', '"+fvdate+"')";
			try{
				con.stmt.execute(query);
				System.out.println("favorite poi recorded.");
				output += "favorite poi recorded.";

			}catch (Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}
			con.closeConnection();
		}catch (Exception e)
		{
			e.printStackTrace();
		}

		return output += "<br>";
	}

	public void visit(String login){
		ArrayList<String> toAdd = new ArrayList<String>();
		ArrayList<String> pids = new ArrayList<String>();
		while (true)
		{
			another:
				try{
					// display instructions for user
					System.out.println("enter the name of the poi you would like to mark as 'visited': ");
					con = new Connector();


					// get input from user
					BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
					while ((input = in.readLine()) == null && input.length() == 0);
					//input = in.readLine();
					// check if poi exists in db
					query = "SELECT * FROM poi WHERE pname='"+input+"'";
					try
					{
						results = con.stmt.executeQuery(query);
						if (!results.next()) // pname doesn't exist in UTrack db
						{
							System.out.println(input + " does not exist in the UTrack database.");
						}
						else //if (results.first() && results.next())  // multiple pnames exist in UTrack db
						{
							String pid;
							System.out.println("select the pid you want to record as 'visited': ");
							results.beforeFirst();
							// general idea taken from stackoverflow
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
							pid = in.readLine();  // user selects intended poi
							pids.add(pid);
							System.out.println("enter the total cost of the visit: ");
							String cost = in.readLine();
							System.out.println("enter the party size: ");
							String party = in.readLine();
							java.sql.Date sqlDate = new java.sql.Date(new java.util.Date().getTime());
							query = "INSERT INTO visit (login, pid, date, cost, party) VALUES ('" +login+ "', '" +pid+ "', '"+sqlDate+"', '"+cost+"', '"+party+"')";
							toAdd.add(query);
						}
						System.out.println("would you like to record another visit? y/n");
						while ((input = in.readLine()) == null && input.length() == 0);
						if(input.equalsIgnoreCase("y"))
						{
							break another;  // record another visit
						}
						else if (input.equalsIgnoreCase("n"))
						{
							System.out.println("review visits before adding: ");
							for(int i=0; i<toAdd.size(); i++)
								System.out.println(toAdd.get(i));

							System.out.println("add visits? y/n");
							while ((input = in.readLine()) == null && input.length() == 0);
							if(input.equalsIgnoreCase("y"))
							{
								try{

									for(int i=0; i<toAdd.size(); i++)
										con.stmt.execute(toAdd.get(i));
									System.out.println("visit(s) recorded.");

									con.closeConnection();
									return;

								}catch (Exception e){
									System.err.println(e.getMessage());
									throw(e);
								}


							}
							else
								con.closeConnection();



						}

					}catch (Exception e){
						System.err.println(e.getMessage());
						throw(e);
					}

				}catch(Exception e)
		{
					e.printStackTrace();
		}
		}

	}

	public String visit(String login, String pid, String cost, String party){
		try{
			con = new Connector();

			java.sql.Date sqlDate = new java.sql.Date(new java.util.Date().getTime());
			query = "INSERT INTO visit (login, pid, date, cost, party) VALUES ('" +login+ "', '" +pid+ "', '"+sqlDate+"', '"+cost+"', '"+party+"')";
			con.stmt.execute(query);

			con.closeConnection();
			return "visit recorded.";

		}catch(Exception e)
		{
			return "Make sure you are login in: "+ e.toString();
		}

	}

	public void add(){
		try{
			con= new Connector();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			String pname, address, url, phone, cat, ophrs;
			int year= 0;
			int price = 0;
			System.out.println("type name of new poi: ");
			pname = in.readLine();
			System.out.println("address: ");
			address = in.readLine();
			System.out.println("website url: ");
			url = in.readLine();
			System.out.println("phone number: ");
			phone = in.readLine();
			System.out.println("year established: ");
			while ((input = in.readLine()) == null && input.length() == 0);
			try{
				year = Integer.parseInt(input);
			}catch (Exception e)
			{}
			System.out.println("category: ");
			cat = in.readLine();
			System.out.println("price per person: ");
			while ((input = in.readLine()) == null && input.length() == 0);
			try{
				price = Integer.parseInt(input);
			}catch (Exception e)
			{}
			System.out.println("operational hours: ");
			ophrs = in.readLine();

			// insert new user into user table
			query = "INSERT INTO poi (pname, address, url, phone, year, cat, price, ophrs) VALUES ('" +pname+ "', '" +address+ "', '" +url+ "', '" +phone+ "', '" +year+"', '" +cat+ "', '" +price+ "', '" +ophrs+ "')";
			try {
				if (con.stmt.execute(query))
				{
					System.err.println("couldn't add poi into database.");
					con.closeConnection();
					return;								
				}

			} catch (Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}
			con.closeConnection();
			return;
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}

	}

	public String add(String pname, String address, String url, String phone, String cat, String ophrs, String year, String price){
		try{
			con= new Connector();



			// insert new user into user table
			query = "INSERT INTO poi (pname, address, url, phone, year, cat, price, ophrs) VALUES ('" +pname+ "', '" +address+ "', '" +url+ "', '" +phone+ "', '" +year+"', '" +cat+ "', '" +price+ "', '" +ophrs+ "')";
			try {
				if (con.stmt.execute(query))
				{
					con.closeConnection();								
					return "couldn't add poi into database.";
				}

			} catch (Exception e){
				return e.toString();
			}

			con.closeConnection();
		}
		catch (Exception e)
		{
			return e.toString();
		}
		return "adding "+pname+ " to uTrack database.";

	}

	public void update(){

		try{
			con= new Connector();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			String pname, address, url, phone, cat, ophrs;
			int year= 0;
			int price = 0;
			String pid="";
			System.out.println("type name of poi you would like to update: ");
			pname = in.readLine();
			query = "SELECT * FROM poi WHERE pname='"+pname+"'";
			try{
				results = con.stmt.executeQuery(query);				
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
			}catch (Exception e)
			{
				System.err.println(e.getMessage());
				throw(e);
			}
			System.out.println("enter the pid of the poi you wish to update:");
			pid = in.readLine();  // user selects intended poi

			System.out.println("updated address: ");
			address = in.readLine();
			System.out.println("update url: ");
			url = in.readLine();
			System.out.println("update phone number: ");
			phone = in.readLine();
			System.out.println("update year established: ");
			while ((input = in.readLine()) == null && input.length() == 0);
			try{
				year = Integer.parseInt(input);
			}catch (Exception e)
			{}
			System.out.println("update category: ");
			cat = in.readLine();
			System.out.println("update price per person: ");
			while ((input = in.readLine()) == null && input.length() == 0);
			try{
				price = Integer.parseInt(input);
			}catch (Exception e)
			{}
			System.out.println("update operational hours: ");
			ophrs = in.readLine();

			// insert new user into user table
			query = "UPDATE poi SET address='" +address+ "', url='" +url+ "', phone='" +phone+ "', year='" +year+"', cat='" +cat+ "', price='" +price+ "', ophrs='" +ophrs+ "' WHERE pid = '"+pid+"'";
			try {
				if (con.stmt.execute(query))
				{
					System.err.println("couldn't add poi into database.");
					con.closeConnection();
					return;								
				}
				System.out.println("update successful.");

			} catch (Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}
			con.closeConnection();
			return;
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}

	}

	public String update(String pid, String address, String url, String phone, String cat, String ophrs, String year, String price){

		try{
			con= new Connector();

			// insert new user into user table
			query = "UPDATE poi SET address='" +address+ "', url='" +url+ "', phone='" +phone+ "', year='" +year+"', cat='" +cat+ "', price='" +price+ "', ophrs='" +ophrs+ "' WHERE pid = '"+pid+"'";
			try {
				if (con.stmt.execute(query))
				{
					con.closeConnection();
					return "couldn't update poi in database.";								
				}

			} catch (Exception e){
				return e.toString();
			}
			con.closeConnection();
			return ("update successful.");
		}
		catch (Exception e)
		{
			return e.toString();
		}

	}

	public void feedback(String login) {
		System.out.println("enter the poi to record feedback: ");

		try{
			con = new Connector();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			while ((input = in.readLine()) == null && input.length() == 0);

			query = "SELECT * FROM poi WHERE pname='"+input+"'";

			try
			{
				results = con.stmt.executeQuery(query);
				if (!results.next()) // pname doesn't exist in UTrack db
				{
					System.out.println(input + " does not exist in the UTrack database.");
				}
				else // print pid
				{
					String pid, text;
					int score = 1;
					System.out.println("select the pid you want to record feedback for: ");
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

					pid = in.readLine();  // user selects intended poi

					System.out.println("enter the score: (1-10)");
					while ((input = in.readLine()) == null && input.length() == 0);
					try{
						score = Integer.parseInt(input);
						if (score < 1 | score > 10)
						{
							System.out.println("invalid score.");
							con.closeConnection();
							return;
						}
					}catch (Exception e)
					{}

					System.out.println("enter feedback summary: ");
					text = in.readLine();

					java.sql.Date sqlDate = new java.sql.Date(new java.util.Date().getTime());
					query = "INSERT INTO feedback (login, pid, fbdate, score, text) VALUES ('" +login+ "', '" +pid+ "', '"+sqlDate+"', '" +score+ "', '" +text+ "')";
					try{
						con.stmt.execute(query);
						System.out.println("feedback recorded.");

					}catch (Exception e){
						System.err.println(e.getMessage());
						throw(e);
					}

				}

			}catch (Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}
		}catch (Exception e){
			e.printStackTrace();
		}

	}

	public String feedback(String login, String pid, String score, String text) {
		System.out.println("enter the poi to record feedback: ");

		try{
			con = new Connector();

			System.out.println("enter the score: (1-10)");
			System.out.println("enter feedback summary: ");

			java.sql.Date sqlDate = new java.sql.Date(new java.util.Date().getTime());
			query = "INSERT INTO feedback (login, pid, fbdate, score, text) VALUES ('" +login+ "', '" +pid+ "', '"+sqlDate+"', '" +score+ "', '" +text+ "')";
			try{
				con.stmt.execute(query);
				con.closeConnection();
				return ("feedback recorded.");

			}catch (Exception e){
				return "error 1: " + e.toString();
			}
			

		}catch (Exception e){
			return "error 2:" + e.toString();
		}

	}

}
