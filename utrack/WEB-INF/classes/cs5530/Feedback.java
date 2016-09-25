package cs5530;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;

public class Feedback {
	Connector con=null;
	String input = "", login = null, query;
	ResultSet results;

	public void usefulness(String login) {
		System.out.println("enter the poi to find feedback: ");

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
					String pid, fid;
					int rating = 0;
					System.out.println("select the pid you want to view feedback for: ");
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

					System.out.println("select the fid for the feeback you wish to mark as 'useless,' 'useful,' or 'very useful':");
					query = "SELECT fid, login, fbdate, score, text FROM feedback where pid='"+pid+"'";
					try{
						results = con.stmt.executeQuery(query);
						results.beforeFirst();
						rsmd = results.getMetaData();
						columnsNumber = rsmd.getColumnCount();
						while (results.next()) {
							for (int i = 1; i <= columnsNumber; i++) {
								if (i > 1) System.out.print(",  ");
								String columnValue = results.getString(i);
								System.out.print(rsmd.getColumnName(i) + ": " + columnValue);
							}
							System.out.println("");
						}
					}catch(Exception e){
						System.err.println(e.getMessage());
						throw(e);
					}

					fid = in.readLine();

					System.out.println("enter the '0' for 'useless,' '1' for 'useful,' and '2' for 'very useful'");
					while ((input = in.readLine()) == null && input.length() == 0);
					try{
						rating = Integer.parseInt(input);
						if (rating < 0 | rating > 2)
						{
							System.out.println("invalid score.");
							con.closeConnection();
							return;
						}
					}catch (Exception e)
					{}


					java.sql.Date sqlDate = new java.sql.Date(new java.util.Date().getTime());
					query = "INSERT INTO rates (login, fid, rating) VALUES ('" +login+ "', '" +fid+ "', '" +rating+ "')";
					try{
						con.stmt.execute(query);
						System.out.println("feedback usefulness recorded.");

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
		}catch (Exception e){
			e.printStackTrace();
		}

	}

	public String usefulness(String login, String fid, String rating) {
		System.out.println("enter the poi to find feedback: ");

		try{
			con = new Connector();

			query = "INSERT INTO rates (login, fid, rating) VALUES ('" +login+ "', '" +fid+ "', '" +rating+ "')";
			try{
				con.stmt.execute(query);
				con.closeConnection();
				return("feedback usefulness recorded.");

			}catch (Exception e){
				return "you can only give feedback once per review(fid): "+e.toString();
			}

		}catch (Exception e){
			return e.toString();
		}
	}

	public String searchfid(String pid){
		String output = "";
		try{
			con = new Connector();
			output = ("select the fid for the feeback you wish to mark as 'useless,' 'useful,' or 'very useful':<br>");
			query = "SELECT fid, login, fbdate, score, text FROM feedback where pid='"+pid+"'";
			try{
				results = con.stmt.executeQuery(query);
				results.beforeFirst();
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				while (results.next()) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) output += (",  ");
						String columnValue = results.getString(i);
						output += (rsmd.getColumnName(i) + ": " + columnValue);
					}
					output += "<br>";
				}
			}catch(Exception e){
				System.err.println(e.getMessage());
				throw(e);
			}

		}catch(Exception e){
			return e.toString();
		}


		return output;

	}


	public void suggestions (){
		System.out.println("enter the poi to find suggestions: ");
		try{
			con = new Connector();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			while ((input = in.readLine()) == null && input.length() == 0);
			query = "SELECT * FROM poi WHERE pname='"+input+"'";

			results = con.stmt.executeQuery(query);
			String pid, fid;
			int rating = 0;
			if (!results.next()) // pname doesn't exist in UTrack db
			{
				System.out.println(input + " does not exist in the UTrack database.");
			}
			else // print pid
			{
				System.out.println("select the pid you like and wish to find suggestions for: ");
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
			}
			pid = in.readLine();

			query = "SELECT * FROM poi p, (SELECT pid FROM visit WHERE login IN (SELECT login  FROM visit  WHERE pid ='"+pid+"')) A, (SELECT pid, count(*) AS count FROM visit GROUP BY pid) B WHERE A.pid=p.pid AND B.pid=A.pid AND B.pid=p.pid GROUP BY p.pid ORDER BY B.count DESC";

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

			con.closeConnection();
		}catch(Exception e){

		}
	}

	public String suggestions (String pid){
		System.out.println("enter the poi to find suggestions: ");
		String output="";
		try{
			con = new Connector();

			System.out.println("select the pid you like and wish to find suggestions for: ");

			query = "SELECT * FROM poi p, (SELECT pid FROM visit WHERE login IN (SELECT login  FROM visit  WHERE pid ='"+pid+"')) A, (SELECT pid, count(*) AS count FROM visit GROUP BY pid) B WHERE A.pid=p.pid AND B.pid=A.pid AND B.pid=p.pid GROUP BY p.pid ORDER BY B.count DESC";

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
				output += "<br>";
			}

			con.closeConnection();
		}catch(Exception e){

		}
		return output;
	}

	public void showUseful() {
		System.out.println("enter the poi to find useful feedback: ");

		try{
			con = new Connector();
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			while ((input = in.readLine()) == null && input.length() == 0);

			query = "SELECT * FROM poi WHERE pname='"+input+"'";

			try
			{
				results = con.stmt.executeQuery(query);
				String pid, fid;
				int rating = 0;
				if (!results.next()) // pname doesn't exist in UTrack db
				{
					System.out.println(input + " does not exist in the UTrack database.");
				}
				else // print pid
				{
					System.out.println("select the pid you want to view useful feedback for: ");
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
				}
				pid = in.readLine();  // user selects intended poi

				query = "SELECT feedback.fid, feedback.score, feedback.text, a.average a FROM feedback, (select fid, avg(rating) as average FROM rates GROUP BY fid) as a WHERE a.fid = feedback.fid AND feedback.pid ='"+pid+"' ORDER BY a DESC";
				System.out.println("suggest trying: ");
				try{
					results = con.stmt.executeQuery(query);
					results.beforeFirst();
					ResultSetMetaData rsmd = results.getMetaData();
					int columnsNumber = rsmd.getColumnCount();
					int show = 0, showAmt;

					System.out.println("enter the number of results you would like to display: (1-10)");
					while ((input = in.readLine()) == null && input.length() == 0);
					try{
						showAmt = Integer.parseInt(input);
						if (showAmt < 1 | showAmt > 10)
						{
							System.out.println("invalid entry.");
							con.closeConnection();
							return;
						}
					}catch(Exception e){
						System.err.println(e.getMessage());
						throw(e);
					}

					while (results.next() && show < showAmt) {
						for (int i = 1; i <= columnsNumber; i++) {
							if (i > 1) System.out.print(",  ");
							String columnValue = results.getString(i);
							System.out.print(rsmd.getColumnName(i) + ": " + columnValue);
						}
						System.out.println("");
						show++;
					}



				}catch (Exception e){
					System.err.println(e.getMessage());
					throw(e);
				}

			}catch (Exception e){
				e.printStackTrace();
			}

			con.closeConnection();
		}catch (Exception e){
			e.printStackTrace();
		}
	}

	public String showUseful(String pid, String sa) {
		String output = "";
		//System.out.println("enter the poi to find useful feedback: ");

		try{
			con = new Connector();

			//System.out.println("select the pid you want to view useful feedback for: ");


			query = "SELECT feedback.fid, feedback.score, feedback.text, a.average a FROM feedback, (select fid, avg(rating) as average FROM rates GROUP BY fid) as a WHERE a.fid = feedback.fid AND feedback.pid ='"+pid+"' ORDER BY a DESC";
			output += ("suggest trying: <br>");
			try{
				results = con.stmt.executeQuery(query);
				results.beforeFirst();
				ResultSetMetaData rsmd = results.getMetaData();
				int columnsNumber = rsmd.getColumnCount();
				int show = 0, showAmt = Integer.parseInt(sa);

				//System.out.println("enter the number of results you would like to display: (1-10)");


				while (results.next() && show < showAmt) {
					for (int i = 1; i <= columnsNumber; i++) {
						if (i > 1) output+=(",  ");
						String columnValue = results.getString(i);
						output+=(rsmd.getColumnName(i) + ": " + columnValue);
					}
					output += "<br>";
					show++;
				}

			}catch (Exception e){
				output += e.toString();
			}

			con.closeConnection();
		}catch (Exception e){
			output += e.toString();
		}

		return output;
	}

}
