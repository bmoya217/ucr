/*
 * Template JAVA User Interface
 * =============================
 *
 * Database Management Systems
 * Department of Computer Science & Engineering
 * University of California - Riverside
 *
 * Target DBMS: 'Postgres'
 *
 */


import java.sql.DriverManager;
import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * This class defines a simple embedded SQL utility class that is designed to
 * work with PostgreSQL JDBC drivers.
 *
 */
public class Cafe {

   //login info for later use
   private static String authorisedUser = null;

   // reference to physical database connection.
   private Connection _connection = null;

   // handling the keyboard inputs through a BufferedReader
   // This variable can be global for convenience.
   static BufferedReader in = new BufferedReader(
                                new InputStreamReader(System.in));

   /**
    * Creates a new instance of Cafe
    *
    * @param hostname the MySQL or PostgreSQL server hostname
    * @param database the name of the database
    * @throws java.sql.SQLException when failed to make a connection.
    */
   public Cafe (String dbname, String dbport) throws SQLException {

      System.out.print("Connecting to database...\n");
      try{
         // constructs the connection URL
         String url = "jdbc:postgresql://127.0.0.1:" + dbport + "/" + dbname;
         System.out.print("Connection URL: " + url + "\n");

         // obtain a physical connection
         this._connection = DriverManager.getConnection(url);
         System.out.println("Done\n");
      }catch (Exception e){
         System.err.println("Error - Unable to Connect to Database: " + e.getMessage() );
         System.out.println("Make sure you started postgres on this machine");
         System.exit(-1);
      }//end catch
   }//end Cafe

   /**
    * Method to execute an update SQL statement.  Update SQL instructions
    * includes CREATE, INSERT, UPDATE, DELETE, and DROP.
    *
    * @param sql the input SQL string
    * @throws java.sql.SQLException when update failed
    */
   public void executeUpdate (String sql) throws SQLException {
      // creates a statement object
      Statement stmt = this._connection.createStatement ();

      // issues the update instruction
      stmt.executeUpdate (sql);

      // close the instruction
      stmt.close ();
   }//end executeUpdate

   /**
    * Method to execute an input query SQL instruction (i.e. SELECT).  This
    * method issues the query to the DBMS and outputs the results to
    * standard out.
    *
    * @param query the input query string
    * @return the number of rows returned
    * @throws java.sql.SQLException when failed to execute the query
    */
   public int executeQueryAndPrintResult (String query) throws SQLException {
      // creates a statement object
      Statement stmt = this._connection.createStatement ();

      // issues the query instruction
      ResultSet rs = stmt.executeQuery (query);

      /*
       ** obtains the metadata object for the returned result set.  The metadata
       ** contains row and column info.
       */
      ResultSetMetaData rsmd = rs.getMetaData ();
      int numCol = rsmd.getColumnCount ();
      int rowCount = 0;

      // iterates through the result set and output them to standard out.
      boolean outputHeader = true;
      while (rs.next()){
	 if(outputHeader){
	    for(int i = 1; i <= numCol; i++){
		System.out.print(rsmd.getColumnName(i) + "\t");
	    }
	    System.out.println();
	    outputHeader = false;
	 }
         for (int i=1; i<=numCol; ++i)
            System.out.print (rs.getString (i) + "\t");
         System.out.println ();
         ++rowCount;
      }//end while
      stmt.close ();
      return rowCount;
   }//end executeQuery

   /**
    * Method to execute an input query SQL instruction (i.e. SELECT).  This
    * method issues the query to the DBMS and returns the results as
    * a list of records. Each record in turn is a list of attribute values
    *
    * @param query the input query string
    * @return the query result as a list of records
    * @throws java.sql.SQLException when failed to execute the query
    */
   public List<List<String>> executeQueryAndReturnResult (String query) throws SQLException { 
      // creates a statement object 
      Statement stmt = this._connection.createStatement (); 
 
      // issues the query instruction 
      ResultSet rs = stmt.executeQuery (query); 
 
      /* 
       ** obtains the metadata object for the returned result set.  The metadata 
       ** contains row and column info. 
       */ 
      ResultSetMetaData rsmd = rs.getMetaData (); 
      int numCol = rsmd.getColumnCount (); 
      int rowCount = 0; 
 
      // iterates through the result set and saves the data returned by the query. 
      boolean outputHeader = false;
      List<List<String>> result  = new ArrayList<List<String>>(); 
      while (rs.next()){
          List<String> record = new ArrayList<String>(); 
         for (int i=1; i<=numCol; ++i) 
            record.add(rs.getString (i)); 
         result.add(record); 
      }//end while 
      stmt.close (); 
      return result; 
   }//end executeQueryAndReturnResult

   /**
    * Method to execute an input query SQL instruction (i.e. SELECT).  This
    * method issues the query to the DBMS and returns the number of results
    *
    * @param query the input query string
    * @return the number of rows returned
    * @throws java.sql.SQLException when failed to execute the query
    */
   public int executeQuery (String query) throws SQLException {
       // creates a statement object
       Statement stmt = this._connection.createStatement ();

       // issues the query instruction
       ResultSet rs = stmt.executeQuery (query);

       int rowCount = 0;

       // iterates through the result set and count nuber of results.
       if(rs.next()){
          rowCount++;
       }//end while
       stmt.close ();
       return rowCount;
   }

   /**
    * Method to fetch the last value from sequence. This
    * method issues the query to the DBMS and returns the current 
    * value of sequence used for autogenerated keys
    *
    * @param sequence name of the DB sequence
    * @return current value of a sequence
    * @throws java.sql.SQLException when failed to execute the query
    */
   public int getCurrSeqVal(String sequence) throws SQLException {
	Statement stmt = this._connection.createStatement ();
	
	ResultSet rs = stmt.executeQuery (String.format("Select currval('%s')", sequence));
	if (rs.next())
		return rs.getInt(1);
	return -1;
   }

   /**
    * Method to close the physical connection if it is open.
    */
   public void cleanup(){
      try{
         if (this._connection != null){
            this._connection.close ();
         }//end if
      }catch (SQLException e){
         // ignored.
      }//end try
   }//end cleanup

   /**
    * The main execution method
    *
    * @param args the command line arguments this inclues the <mysql|pgsql> <login file>
    */
   public static void main (String[] args) {
      if (args.length != 2) {
         System.err.println (
            "Usage: " +
            "java [-classpath <classpath>] " +
            Cafe.class.getName () +
            " <dbname> <port>");
         return;
      }//end if

      Greeting();
      Cafe esql = null;
      try{
         // use postgres JDBC driver.
         Class.forName ("org.postgresql.Driver").newInstance ();
         // instantiate the Cafe object and creates a physical
         // connection.
         String dbname = args[0];
         String dbport = args[1];
         esql = new Cafe (dbname, dbport);

         boolean keepon = true;
         while(keepon) {
            // These are sample SQL statements
            System.out.println("0. Exit");
            System.out.println("-------");
            System.out.println("1. Create user");
            System.out.println("2. Log in");
            
            authorisedUser = null;
            switch (readChoice()){
 	           case 0: keepon = false; break;
               case 1: CreateUser(esql); break;
               case 2: authorisedUser = LogIn(esql); break;
               default : System.out.println("Unrecognized choice!"); break;
            }//end switch
            if (authorisedUser != null) {
              boolean usermenu = true;
              String user_type = find_type(esql);
	      switch (user_type){
		case "Customer": 
		  while(usermenu) {
		  			Greeting(esql);
                    System.out.println("MAIN MENU");
                    System.out.println("---------");
                    System.out.println("0. Log out");
                    System.out.println("1. Browse Menu by ItemName");
                    System.out.println("2. Browse Menu by Type");
                    System.out.println("3. Add Order");
                    System.out.println("4. Update Order");
                    System.out.println("5. View Order History");
                    System.out.println("6. View Order Status");
                    System.out.println("7. Update User Info");

                      switch (readChoice()){
                       case 0: usermenu = false; break;
                       case 1: BrowseMenuName(esql); break;
                       case 2: BrowseMenuType(esql); break;
                       case 3: AddOrder(esql); break;
                       case 4: UpdateOrder(esql); break;
                       case 5: ViewOrderHistory(esql); break;
                       case 6: ViewOrderStatus(esql); break;
                       case 7: UpdateUserInfo(esql); break;
                       default : System.out.println("Unrecognized choice!"); break;
		      }//end switch
		  } break;
		case "Employee": 
		  while(usermenu) {
		  			Greeting(esql);
                    System.out.println("MAIN MENU");
                    System.out.println("---------");
                    System.out.println("0. Log out");
                    System.out.println("1. Browse Menu by ItemName");
                    System.out.println("2. Browse Menu by Type");
                    System.out.println("3. Add Order");
                    System.out.println("4. Update Order");
                    System.out.println("5. View Current Orders");
                    System.out.println("6. View Order Status");
                    System.out.println("7. Update User Info");

                      switch (readChoice()){
                       case 0: usermenu = false; break;
                       case 1: BrowseMenuName(esql); break;
                       case 2: BrowseMenuType(esql); break;
                       case 3: AddOrder(esql); break;
                       case 4: EmployeeUpdateOrder(esql); break;
                       case 5: ViewCurrentOrder(esql); break;
                       case 6: ViewOrderStatus(esql); break;
                       case 7: UpdateUserInfo(esql); break;
                       default : System.out.println("Unrecognized choice!"); break;
		      }//end switch
		  } break;
		case "Manager ": 
		  while(usermenu) {
		  			Greeting(esql);
                    System.out.println("MAIN MENU");
                    System.out.println("---------");
                    System.out.println("0. Log out");
                    System.out.println("1. Browse Menu by ItemName");
                    System.out.println("2. Browse Menu by Type");
                    System.out.println("3. Add Order");
                    System.out.println("4. Update Order");
                    System.out.println("5. View Current Orders");
                    System.out.println("6. View Order Status");
                    System.out.println("7. Update User Info");
                    System.out.println("8. Update Menu");
                    
                      switch (readChoice()){
                       case 0: usermenu = false; break;
                       case 1: BrowseMenuName(esql); break;
                       case 2: BrowseMenuType(esql); break;
                       case 3: AddOrder(esql); break;
                       case 4: EmployeeUpdateOrder(esql); break;
                       case 5: ViewCurrentOrder(esql); break;
                       case 6: ViewOrderStatus(esql); break;
                       case 7: ManagerUpdateUserInfo(esql); break;
                       case 8: UpdateMenu(esql); break;
                       default : System.out.println("Unrecognized choice!"); break;
		      }//end switch
		  } break;
	      }//end switch
            }//end if
         }//end while
      }catch(Exception e) {
         System.err.println (e.getMessage ());
      }finally{
         // make sure to cleanup the created table and close the connection.
         try{
            if(esql != null) {
               System.out.print("Disconnecting from database...");
               esql.cleanup ();
               System.out.println("Done\n\nBye !");
            }//end if
         }catch (Exception e) {
            // ignored.
         }//end try
      }//end try
   }//end main

	public static void Greeting(){
		DisplayTitle("Welcome!");
	}

	public static void Greeting(Cafe esql){
		DisplayTitle(authorisedUser + ": " + find_type(esql));
	}
   
   	public static void DisplayTitle(String title){
   		int ihold = (55-title.trim().length())/2;
   		String shold = "";
   		
   		for(int i = 0; i < ihold; ++i)
   			shold = shold + " ";
   		
   		System.out.println(
			"\033c*******************************************************\n" +
			shold + title.trim() + "\n" +
			"*******************************************************\n");
   	}
   	
   	public static void DisplaySubtitle(String title){
   		int ihold = (55-title.trim().length())/2;
   		String shold = "";
   		
   		for(int i = 0; i < ihold; ++i)
   			shold = shold + " ";
   		
   		System.out.println(
			"\n\n*******************************************************\n" +
			shold + title.trim() + "\n" +
			"*******************************************************\n");
   	}
   	
   	public static boolean DisplayOrderIDs(Cafe esql){
   		String query;
   		List<List<String>> rshold;
   		
   		try{
			query = String.format("SELECT orderid FROM Orders WHERE login = '%s' AND paid = FALSE ORDER BY timeStampRecieved DESC LIMIT 5", authorisedUser);
			rshold = esql.executeQueryAndReturnResult(query);
		} catch(SQLException e){ System.err.println (e.getMessage ()); return false; }
		
		System.out.print("Your Open Orders: ");
		
		if(rshold.size() == 0){
			System.out.println("You have no current Orders,\nYou can add an Order from the main menu\nPress Enter to continue");
			try{
				in.readLine();
			} catch(Exception e) { return false; }
			return false;
		}
		for(int i = 0; i < rshold.size()-1; ++i)
			System.out.print(rshold.get(i).get(0) + ", ");
		System.out.println(rshold.get(rshold.size()-1).get(0));
		return true;
	}
   	
   	public static int readChoice() {
    	int input;
    	
      	while (true){
		    System.out.print("------------------------\nPlease make your choice: ");
			try {
		        input = Integer.parseInt(in.readLine());
		        break;
		     }catch (Exception e) { System.out.println("Your input is invalid!"); continue; }
      	}
      	return input;
   	}
   
   	public static int readRangedChoice(int min, int max){
   		int ihold = readChoice();
		while(ihold < min || ihold > max){
			System.out.println("Invalid Choice!");
			ihold = readChoice();
		}
		return ihold;
   	}
   	
   	public static String readPrice(){
		double input;
		while(true){
			System.out.print("\tEnter Price: ");
			try {
				input = Double.parseDouble(in.readLine());
				break;
			}catch (Exception e) { System.out.println("\tYour input is invalid!"); continue; }
		}
		return Double.toString(input);
	}
   	
   	//fixme
   	public static String readPhoneNumber(){
		String number;
		while(true){
			try {
				System.out.print("\tEnter Phone Number: ");
				Scanner input = new Scanner(System.in);
				number = input.nextLine();
			}catch (Exception e) { System.out.println("\tYour input is invalid!"); continue;}
   			return number;
		}
	}

	public static int readOrderID() {
		int input;
		while(true){
			System.out.print("\tEnter Order ID: ");
			try {
				input = Integer.parseInt(in.readLine());
				break;
			}catch (Exception e) { System.out.println("\tYour input is invalid!"); continue; }
		}
		return input;
	}

	public static void CreateUser(Cafe esql){
		String login="", password="", phone="", type="Customer", favItems="";
		String query;
		try{
			while(true){
				System.out.print("\tEnter Login: ");
				login = in.readLine();
				
				query = String.format("SELECT * FROM Users WHERE login = '%s'", login);
				if(esql.executeQuery(query) == 1)
					System.out.println("\tSorry! That username is taken.");
				else { break; }
			} 
			
			while(password == ""){
				System.out.print("\tEnter Password: ");
				password = in.readLine();
				if(password == "")
					System.out.println("Password cannot be empty!");
			}
			
			phone = readPhoneNumber();

			type="Customer";
			favItems="";

			query = String.format("INSERT INTO USERS (phoneNum, login, password, favItems, type) VALUES ('%s','%s','%s','%s','%s')", phone, login, password, favItems, type);
			esql.executeUpdate(query);i
			System.out.println("\nUser successfully created!\n");
		}catch(Exception e){ System.err.println (e.getMessage ()); }
   }
   
	public static double get_total(List<List<String>> items, Cafe esql){
		String query = "";
		List<List<String>> rshold;
		double dhold = 0;
		
		for(int i = 0; i < items.size(); ++i){
			try{
				query = String.format("SELECT price FROM Menu WHERE itemName = '%s'", items.get(i).get(0));
				rshold = esql.executeQueryAndReturnResult(query);
				dhold += Double.parseDouble(rshold.get(0).get(0));
			} catch (Exception E) { return 0; }
		}
		return dhold;
	}
		

	public static String LogIn(Cafe esql){
		try{
			System.out.print("\tEnter Login: ");
			String login = in.readLine();
			System.out.print("\tEnter Password: ");
			String password = in.readLine();

			String query = String.format("SELECT * FROM Users WHERE login = '%s' AND password = '%s'", login, password);

			if (esql.executeQuery(query) > 0)
				return login;
				
			return null;
		} catch(Exception e){ System.err.println (e.getMessage ()); return null; }
   	}

	public static String find_type(Cafe esql){  
		try{	
			String query = String.format("SELECT type FROM Users WHERE login = '%s'", authorisedUser);
			List<List<String>> rshold = esql.executeQueryAndReturnResult(query);
			return rshold.get(0).get(0);
		} catch(SQLException e) { System.err.println(e.getMessage()); return null; }
	}

	public static void BrowseMenuName(Cafe esql){
		String query;
		List<List<String>> rshold;
		String shold;
		String status = "";
		int ihold;
		int item_choice;
		int oid;
		
		while(true){
			DisplayTitle("Menu");
			System.out.print(status);	
			
			try{	
				query = String.format("SELECT itemName, price, description FROM Menu");
				rshold = esql.executeQueryAndReturnResult(query);
			} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
		
			System.out.println("0. Return\n---------");
			for(int i = 0; i < rshold.size(); ++i)
				System.out.println (i+1 + ". " + rshold.get(i).get(0) + "$" + String.format("%.2f", (double)Math.round(100*Double.parseDouble(rshold.get(i).get(1)))/100) + "\n\t" + rshold.get(i).get(2).trim());
		
			item_choice = readRangedChoice(0, rshold.size());
		
			if(item_choice == 0)
				break;
			
			if(DisplayOrderIDs(esql) == false)
				continue;
			oid = readOrderID();
			
			try{
				query = String.format("SELECT * FROM Orders WHERE orderid = '%s' AND login = '%s' AND paid = FALSE", oid, authorisedUser);
				ihold = esql.executeQuery(query);
			} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
			
			if(ihold == 0)
				status = "Sorry, you cannot update that order.\n\n";
			
			if(ihold == 1){
				status = "Item Added!\n\n";
				
				System.out.print("Additional Comments: ");
				try{
					shold = in.readLine();
				} catch(Exception e){ System.err.println (e.getMessage ()); return; }
				
				try{
					query = String.format("INSERT INTO ItemStatus VALUES ('%s', '%s', now(), 'Hasn''t started', '%s')", oid, rshold.get(item_choice-1).get(0), shold);
					esql.executeUpdate(query);
				} catch(SQLException e){ System.err.println (e.getMessage ()); return; }	
			}
		}
	}

	public static void BrowseMenuType(Cafe esql){
		String query;
		List<List<String>> rshold;
		String type;
		String shold;
		String status = "";
		int choice;
		int ihold;
		int oid;
		
		while(true){
			DisplayTitle("Menu Catagories");
			
			try{
				query = String.format("SELECT DISTINCT type FROM Menu");
				rshold = esql.executeQueryAndReturnResult(query);
			} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
			
			System.out.println("0. Return\n---------");
			for(int i = 0; i < rshold.size(); ++i)
				System.out.println (i+1 + ". " + rshold.get(i).get(0));
		
			choice = readRangedChoice(0, rshold.size());
		
			if(choice == 0)
				return;
		
			type = rshold.get(choice-1).get(0);
			
			while(true){
				DisplaySubtitle(type);
				System.out.print(status);
				
				try{	
					query = String.format("SELECT itemName, price, description FROM Menu WHERE type = '%s'", type);
					rshold = esql.executeQueryAndReturnResult(query);
				} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
		
				System.out.println("0. Return\n---------");
				for(int i = 0; i < rshold.size(); ++i)
					System.out.println (i+1 + ". " + rshold.get(i).get(0) + "$" + String.format("%.2f", (double)Math.round(100*Double.parseDouble(rshold.get(i).get(1)))/100) + "\n\t" + rshold.get(i).get(2).trim());
				choice = readRangedChoice(0, rshold.size());
		
				if(choice == 0)
					break;
				
				if(DisplayOrderIDs(esql) == false)
					continue;
				oid = readOrderID();
			
				try{
					query = String.format("SELECT * FROM Orders WHERE orderid = '%s' AND login = '%s' AND paid = FALSE", oid, authorisedUser);
					ihold = esql.executeQuery(query);
				} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
			
				if(ihold == 0)
					status = "Sorry, you cannot update that order.\n\n";
			
				if(ihold == 1){
					status = "Item Added!\n\n";
					System.out.print("Additional Comments: ");
					try{
						shold = in.readLine();
					} catch(Exception e){ System.err.println (e.getMessage ()); return; }
				
					try{
						query = String.format("INSERT INTO ItemStatus VALUES ('%s', '%s', now(), 'Hasn''t started', '%s')", oid, rshold.get(choice-1).get(0), shold);
						esql.executeUpdate(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
				}
			}
		}
	}

	public static void AddOrder(Cafe esql){
		String query;
		List<List<String>> rshold;
		int ihold;
		
		try{
			query = String.format("SELECT nextval('orders_orderid_seq')");
			rshold = esql.executeQueryAndReturnResult(query);
		} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
		ihold = Integer.parseInt(rshold.get(0).get(0));
	
		try{
			query = String.format("INSERT INTO Orders VALUES ('%s', '%s', false, now(), 0)", ihold, authorisedUser);
			esql.executeUpdate(query);
		} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
      	
		System.out.print("\nYour new Order ID is: " + ihold + "\n------------------------\nPress Enter to continue.");
		try{
			in.readLine();
		} catch(Exception e){ System.err.println (e.getMessage ()); return; }
	}

	public static void UpdateOrder(Cafe esql){
		String query;
		List<List<String>> rshold;
		String shold;
		int ihold;
		int item_choice;
		int modify_choice;
		int oid;
		
		while(true){
			DisplayTitle("Update Order");
			
			System.out.println("NOTICE: Paid Orders cannot be updated.\n");
			System.out.println("0. Return\n---------");
			System.out.println("1. Enter Order ID");
			
			ihold = readRangedChoice(0, 1);
			
			if(ihold == 0)
				return;
			
			DisplayOrderIDs(esql);
			oid = readOrderID();
		
			try{
				query = String.format("SELECT * FROM Orders WHERE orderid = '%s' AND login = '%s' AND paid = FALSE", oid, authorisedUser);
				ihold = esql.executeQuery(query);
			} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
		
			while(ihold == 1){
				DisplaySubtitle("Order #" + oid);
	
				try{
					query = String.format("SELECT * FROM ItemStatus WHERE orderid = '%s'", oid);
					rshold = esql.executeQueryAndReturnResult(query);
				} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
	
				System.out.println (0 + ". Return\n");
				for(int i = 0; i < rshold.size(); ++i)
					System.out.println (i+1 + ". " + rshold.get(i).get(1) + rshold.get(i).get(3).trim() + "\n\t" + rshold.get(i).get(4).trim());
		
				item_choice = readRangedChoice(0, rshold.size());
			
				if(item_choice == 0)
					break;
				
				DisplaySubtitle(rshold.get(item_choice-1).get(1));
				
				System.out.println("Comments: " + rshold.get(item_choice-1).get(4).trim() + "\n");

				System.out.println("0. Return\n---------");
				System.out.println("1. Remove Item From Order");
				System.out.println("2. Add Comment");
				
				modify_choice = readRangedChoice(0, 2);
			
				if(modify_choice == 1){
					try{
						query = String.format("DELETE FROM ItemStatus WHERE orderid = '%s' AND itemname = '%s' AND lastUpdated = '%s'", oid, rshold.get(item_choice-1).get(1), rshold.get(item_choice-1).get(2));
						esql.executeUpdate(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
				}
			
				if(modify_choice == 2){
					System.out.print("Comment: ");
				
					try{
						shold = in.readLine();
					} catch(Exception e){ System.err.println (e.getMessage ()); return; }
				
					try{
						query = String.format("UPDATE ItemStatus SET comments = '%s' WHERE orderid = '%s' AND itemname = '%s' AND lastUpdated = '%s'", shold, oid, rshold.get(item_choice-1).get(1), rshold.get(item_choice-1).get(2));
						esql.executeUpdate(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
				}
			}
		}
	}

	public static void EmployeeUpdateOrder(Cafe esql){
		String query;
		List<List<String>> items;
		List<List<String>> types;
		String shold;
		String status = "";
		int ihold;
		int item_choice;
		int modify_choice;
		int oid;
		
		while(true){
			DisplayTitle("Update Order");
			
			System.out.println("0. Return\n---------");
			System.out.println("1. Enter Order ID");
			
			ihold = readRangedChoice(0, 1);
			
			if(ihold == 0)
				return;
			
			DisplayOrderIDs(esql);
			oid = readOrderID();
		
			try{
				query = String.format("SELECT * FROM Orders WHERE orderid = '%s'", oid);
				ihold = esql.executeQuery(query);
			} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
		
			while(ihold == 1){
				DisplaySubtitle("Order #" + oid);
				System.out.print(status);
				status = "";
	
				try{
					query = String.format("SELECT * FROM ItemStatus WHERE orderid  = '%s'", oid);
					items = esql.executeQueryAndReturnResult(query);
				} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
	
				System.out.println("0. Return\n---------");
				for(int i = 0; i < items.size(); ++i)
					System.out.println (i+1 + ". " + items.get(i).get(1) + items.get(i).get(3).trim() + "\n\t" + items.get(i).get(4).trim());
				
				System.out.println(items.size()+1 + ". Confirm Order Payment");

				item_choice = readRangedChoice(0, items.size()+1);
			
				if(item_choice == 0)
					break;
				
				if(item_choice == items.size()+1){
					try{
						query = String.format("UPDATE Orders SET paid = TRUE WHERE orderid = '%s'", oid);
						esql.executeUpdate(query);
						status = "Order #" + oid + " set to Paid\n\n";
						continue;
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
				}
				
				DisplaySubtitle(items.get(item_choice-1).get(1));
				System.out.print(status);
				status = "";
				System.out.println("Comments: " + items.get(item_choice-1).get(4).trim() + "\n");
				
				while(true){
					try{
						query = String.format("SELECT DISTINCT status FROM ItemStatus");
						types = esql.executeQueryAndReturnResult(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
				
					System.out.println("0. Return\n---------");
					for(int i = 0; i < types.size(); ++i)
						System.out.println(i+1 + ". " + types.get(i).get(0));
				
					modify_choice = readRangedChoice(0, types.size());
				
					if(modify_choice == 0)
						break;
			
					shold = types.get(modify_choice).get(0);
					try{
						query = String.format("UPDATE ItemStatus SET status = '%s' WHERE orderid = '%s' AND itemname = '%s' AND lastUpdated = '%s'", shold, oid, items.get(item_choice-1).get(1), items.get(item_choice-1).get(2));
						esql.executeUpdate(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
					status = "Item Status updated!";
				}
			}
		}
	}

	public static void ViewOrderHistory(Cafe esql){
		DisplayTitle("Order History");
		
		String query;
		List<List<String>> rshold1;
		List<List<String>> rshold2;
		
		try{
			query = String.format("SELECT orderid, paid FROM Orders WHERE login = '%s' ORDER BY timeStampRecieved DESC LIMIT 5", authorisedUser);
			rshold1 = esql.executeQueryAndReturnResult(query);
		} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
		
		for(int i = 0; i < rshold1.size(); ++i){
			System.out.println(rshold1.get(i).get(0) + ": Order Paid = " + rshold1.get(i).get(1) + "\n");
			
			try{
				query = String.format("SELECT itemName, comments FROM ItemStatus WHERE orderid = '%s'", rshold1.get(i).get(0));
				rshold2 = esql.executeQueryAndReturnResult(query);
			} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
			
			for(int j = 0; j < rshold2.size(); ++j)
				System.out.println("\t" + rshold2.get(i).get(0).trim() + "\n\t\t" + rshold2.get(i).get(1).trim());
		}
		
		System.out.print("UPDATE ItemStatus SET comments------------------------\nPress Enter to Continue.\n");
		try{
			in.readLine();
		} catch(Exception e){ System.err.println (e.getMessage ()); return; }
	}
	
	public static void UpdateUserInfo(Cafe esql){
		String query;
		List<List<String>> rshold;
		String shold;
		String status = "";
		int ihold;
		int modify_choice;
		
		while(true){
			DisplayTitle("Update User Info");

			System.out.println("0. Return\n---------");
			System.out.println("1. Password");
			System.out.println("2. Phone Number");
			System.out.println("3. Favorite Items");
		
			modify_choice = readRangedChoice(0, 3);
	
			if(modify_choice == 0)
				break;
			
			if(modify_choice == 1){
				do{
					System.out.print("Enter new Password: ");
					try{
						shold = in.readLine();
						if(shold == "")
							System.out.print("Passwords cannot be empty!");
					}catch(Exception e){ return; }
				} while(shold == "");
				
				try{
					query = String.format("UPDATE Users SET password = '%s' WHERE login = '%s'", shold, authorisedUser);
					esql.executeUpdate(query);
				} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
			}
			
			if(modify_choice == 2){
				shold = readPhoneNumber();
				
				try{
					query = String.format("UPDATE Users SET phoneNum = '%s' WHERE login = '%s'", shold, authorisedUser);
					esql.executeUpdate(query);
				} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
			}
			
			if(modify_choice == 3){
				do{
					System.out.print("Enter new Password: ");
					try{
						shold = in.readLine();
						if(shold == "")
							System.out.print("Passwords cannot be empty!");
					} catch(Exception e){ System.err.println (e.getMessage ()); return; }
				} while(shold == "");
				
				try{
					query = String.format("UPDATE Users SET password = '%s' WHERE login = '%s'", shold, authorisedUser);
					esql.executeUpdate(query);
				} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
			}
		}
	}

	public static void ManagerUpdateUserInfo(Cafe esql){
		String query;
		List<List<String>> rshold;
		String shold;
		String login;
		String status = "";
		int ihold;
		int modify_choice;
		
		while(true){
			DisplayTitle("Update User Info");
			System.out.print(status);
			status = "";
			
			System.out.println("0. Return\n---------");
			System.out.println("1. Enter the Login of a User to update");
			ihold = readRangedChoice(0, 1);
			
			if(ihold == 0)
				return;
			
			try{
				System.out.print("\nEnter Login: ");
				login = in.readLine();
			} catch(Exception e){ System.err.println (e.getMessage ()); return; }
			
			try{
				query = String.format("SELECT * FROM Users WHERE login = '%s'", login);
				ihold = esql.executeQuery(query);
			} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
			
			if(ihold == 0){
				status = "Invalid Login entered.\n\n";
				continue;
			}
			
			while(true){
				DisplaySubtitle(login);
				System.out.print(status);
				status = "";
				
				System.out.println("0. Return\n---------");
				System.out.println("1. Password");
				System.out.println("2. Phone Number");
				System.out.println("3. Favorite Items");
				System.out.println("4. Type");
		
				modify_choice = readRangedChoice(0, 4);
	
				if(modify_choice == 0)
					break;
			
				if(modify_choice == 1){
					do{
						System.out.print("Enter new Password: ");
						try{
							shold = in.readLine();
							if(shold == "")
								System.out.print("Passwords cannot be empty!");
						}catch(Exception e){ return; }
					} while(shold == "");
				
					try{
						query = String.format("UPDATE Users SET password = '%s' WHERE login = '%s'", shold, login);
						esql.executeUpdate(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
					status = "Password updated!\n\n";
				}
			
				if(modify_choice == 2){
					shold = readPhoneNumber();
				
					try{
						query = String.format("UPDATE Users SET phoneNum = '%s' WHERE login = '%s'", shold, login);
						esql.executeUpdate(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
					status = "Phone number updated!\n\n";
				}
			
				if(modify_choice == 3){
					System.out.print("Enter Favorite Items: ");
					try{
						shold = in.readLine();
					} catch(Exception e){ System.err.println (e.getMessage ()); return; }
					
					try{
						query = String.format("UPDATE Users SET favItems = '%s' WHERE login = '%s'", shold, login);
						esql.executeUpdate(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
					status = "Favorite Items updated!\n\n";
				}
				
				if(modify_choice == 4){
					try{	
						query = String.format("SELECT DISTINCT type FROM Users");
						rshold = esql.executeQueryAndReturnResult(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
					
					System.out.println("Select User Type:\n-----------------");
					for(int i = 0; i < rshold.size(); ++i)
						System.out.println ("\t" + (i+1) + ". " + rshold.get(i).get(0));
				
					ihold = readRangedChoice(0, rshold.size());
					shold = rshold.get(ihold-1).get(0); 
					
					try{
						query = String.format("UPDATE Users SET type = '%s' WHERE login = '%s'", shold, login);
						rshold = esql.executeQueryAndReturnResult(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
					status = "User Type updated!\n\n";
				}
			}
		}
	}

//status: fixme -> cannot delete menu item that is referenced as a foreign key
	public static void UpdateMenu(Cafe esql){
		String query;
		List<List<String>> items;
		List<List<String>> types;
		String status = "";
		int ihold;
		int item_choice;
		int modify_choice;
		int type_choice;
		String n, t, p, d, u;
		boolean valid_name;
		
		while(true){
			DisplayTitle("Update Menu");
			System.out.print (status);
			status = "";
			
			System.out.println("0. Return\n---------");
			System.out.println("1. Add Menu Item");
			System.out.println("2. Modify Menu Item");
			System.out.println("3. Delete Menu Item");
			
			ihold = readRangedChoice(0, 3);
			
			if(ihold == 0)
				return;
			
			if(ihold == 1){
				DisplaySubtitle("New Item");
				
				do{
					try{
						System.out.print("\tEnter item Name: ");
						n = in.readLine();
						query = String.format("SELECT itemName FROM Menu WHERE itemName = '%s'", n);
						if(esql.executeQuery(query) == 1){
							valid_name = false;
							
							System.out.println("\tItem Name already taken!\n");
							System.out.println("\t0. Return\n---------");
							System.out.println("\t1. Try Again");
					
							if(readRangedChoice(0, 1) == 0)
								break;
						} else { valid_name = true; }
					} catch(Exception e){ System.err.println (e.getMessage ()); return; }
				} while(valid_name == false);
				
				if(valid_name == false)
					continue;
					
				try{	
					query = String.format("SELECT DISTINCT type FROM Menu");
					types = esql.executeQueryAndReturnResult(query);
				} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
					
				System.out.println("\n\tSelect item Type:\n\t-----------------\n\t\t0. NEW ITEM TYPE");
				for(int i = 0; i < types.size(); ++i)
					System.out.println ("\t\t" + (i+1) + ". " + types.get(i).get(0));
				
				modify_choice = readRangedChoice(0, types.size());
				if(modify_choice == 0){
					do{
						System.out.print("\tEnter item Type: ");
						try{
							t = in.readLine();
							if(t == "")
								System.out.print("Type cannot be empty!");
						} catch(Exception e){ System.err.println (e.getMessage ()); return; }
					} while(t == "");
				} else { t = types.get(modify_choice-1).get(0); }
				
				try{
					p = readPrice();
					System.out.print("\tEnter item Description: ");
					d = in.readLine();
					System.out.print("\tEnter item URL: ");
					u = in.readLine();
				} catch(Exception e){ System.err.println (e.getMessage ()); return; }
				
				try{
					query = String.format("INSERT INTO Menu VALUES ('%s','%s','%s','%s','%s')", n, t, p, d, u);
					esql.executeUpdate(query);
				} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
				
				status = "Menu Item added!\n\n";
			}
			
			if(ihold == 2){
				while(true){
					DisplaySubtitle("Modify Item");
					System.out.print(status);
					status = "";
					
					try{	
						query = String.format("SELECT itemName, description FROM Menu");
						items = esql.executeQueryAndReturnResult(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
		
					System.out.println("0. Return\n---------");
					for(int i = 0; i < items.size(); ++i)
						System.out.println (i+1 + ". " + items.get(i).get(0));
		
					item_choice = readRangedChoice(0, items.size());
		
					if(item_choice == 0)
						break;
					
					while(true){
						DisplaySubtitle(items.get(item_choice-1).get(0));
						System.out.print(status);
					
						System.out.println("Select the Attribute you wish to modify.\n");
						System.out.println("0. Return\n---------");
						System.out.println("1. Type");
						System.out.println("2. Price");
						System.out.println("3. Description");
						System.out.println("4. Image URL");
				
						modify_choice = readRangedChoice(0, 4);
					
						if(modify_choice == 0)
							break;
						
						if(modify_choice == 1){
							try{	
								query = String.format("SELECT DISTINCT type FROM Menu");
								types = esql.executeQueryAndReturnResult(query);
							} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
				
							System.out.println("Select Item Type:\n-----------------\n0. NEW ITEM TYPE");
							for(int i = 0; i < types.size(); ++i)
								System.out.println (i+1 + ". " + types.get(i).get(0));
				
							type_choice = readRangedChoice(0, types.size());
							if(type_choice == 0){
								do{
									System.out.print("Enter Item Type: ");
									try{
										t = in.readLine();
										if(t == "")
											System.out.print("Type cannot be empty!");
									}catch(Exception e){ System.err.println (e.getMessage ()); return; }
								} while(t == "");
							}
							else
								t = types.get(type_choice-1).get(0);
								
							try{
								query = String.format("UPDATE Menu SET type = '%s' WHERE itemName = '%s'", t, items.get(item_choice-1).get(0));
								esql.executeUpdate(query);
							} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
							status = "Item Type updated!\n\n";
						}
						
						if(modify_choice == 2){
							p = readPrice();
							
							try{
								query = String.format("UPDATE Menu SET price = '%s' WHERE itemName = '%s'", p, items.get(item_choice-1).get(0));
								esql.executeUpdate(query);
							} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
							status = "Item Price updated!\n\n";
						}
						
						if(modify_choice == 3){
							try{
								System.out.print("Enter new Description: ");
								d = in.readLine();
							} catch(Exception e){ System.err.println (e.getMessage ()); return; }
							
							try{
								query = String.format("UPDATE Menu SET description = '%s' WHERE itemName = '%s'", d, items.get(item_choice-1).get(0));
								esql.executeUpdate(query);
							} catch(SQLException e){ System.err.println (e.getMessage ()); return;}
							status = "Item Description updated!\n\n";
						}
						
						if(modify_choice == 4){
							try{
								System.out.print("Enter new Image URL: ");
								u = in.readLine();
							} catch(Exception e){ System.err.println (e.getMessage ()); return; }
							
							try{
								query = String.format("UPDATE Menu SET imageURL = '%s' WHERE itemName = '%s'", u, items.get(item_choice-1).get(0));
								esql.executeUpdate(query);
							} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
							status = "Image URL updated!\n\n";
						}
					}
				}
			}
			
			if(ihold == 3){
				while(true){
					DisplaySubtitle("Delete Item");
					
					try{	
						query = String.format("SELECT itemName FROM Menu");
						items = esql.executeQueryAndReturnResult(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
		
					System.out.println("0. Return\n---------");
					for(int i = 0; i < items.size(); ++i)
						System.out.println (i+1 + ". " + items.get(i).get(0));
		
					item_choice = readRangedChoice(0, items.size());
		
					if(item_choice == 0)
						break;
				
					System.out.println("\n0. Return\n---------");
					System.out.println("1. Confirm delete of " + items.get(item_choice-1).get(0));
				
					modify_choice = readRangedChoice(0, 1);
					
					if(modify_choice == 0)
						continue;
					
					try{
						query = String.format("DELETE FROM Menu WHERE itemName = '%s'", items.get(item_choice-1).get(0));
						esql.executeUpdate(query);
					} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
					status = "Menu Item Deleted!\n\n";
				}
			}
		}
	}

	public static void ViewOrderStatus(Cafe esql){
		String query;
		List<List<String>> rshold;
		List<List<String>> menus;
		int oid;
		int ihold;
		double dhold; 
		boolean first = true;
		
		DisplayTitle("Order Status");
		
		while(true){
			if(first == true){
				System.out.println("0. Return\n---------");
				System.out.println("1. Enter Order ID");
				
				ihold = readRangedChoice(0, 1);
			
				if(ihold == 0)
					return;
			}
			first = false;
			
			DisplayOrderIDs(esql);
			oid = readOrderID();
		
			;d, uTE ItemStatus SET comments
				query = String.format("SELECT login, paid FROM Orders WHERE orderid = '%s'", oid);
				rshold = esql.executeQueryAndReturnResult(query);
			} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
			
			if(rshold.size() == 0){
				System.out.println("Sorry, you cannot view this order.\n");
				continue;
			}
			
			if(rshold.get(0).get(0) != authorisedUser && find_type(esql) == "Customer"){
				System.out.println("Sorry, you cannot view this order.\n");
				continue;
			}
			
			DisplaySubtitle("Order #" + oid);
			
			System.out.println("User Login: " + rshold.get(0).get(0) + "\nOrder Paid = " + rshold.get(0).get(1) + "\n");
			
			try{
				query = String.format("SELECT itemName, comments FROM ItemStatus WHERE orderid = '%s'", oid);
				rshold = esql.executeQueryAndReturnResult(query);
			} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
			
			for(int i = 0; i < rshold.size(); ++i)
				System.out.println(rshold.get(i).get(0) + rshold.get(i).get(1));
			

			System.out.println("Order Subtotal: $" + (double)Math.round(100*get_total(rshold, esql))/100);

			System.out.println("\n\n0. Return\n---------");
			System.out.println("1. Look up another Order");		
			
			ihold = readRangedChoice(0, 1);
			
			if(ihold == 0)
				return;
		}
	}

	public static void ViewCurrentOrder(Cafe esql){
		DisplayTitle("Current Orders");
		
		String query;
		List<List<String>> rshold;
		
		try{
			query = String.format("SELECT * FROM Orders WHERE paid = FALSE AND timeStampRecieved >= now() - interval \'1 day\'");
			rshold = esql.executeQueryAndReturnResult(query);
		} catch(SQLException e){ System.err.println (e.getMessage ()); return; }
		
		for(int i = 0; i < rshold.size(); ++i)
			System.out.println(rshold.get(i).get(0) + " " + rshold.get(i).get(1) + "\n\t" + rshold.get(i).get(3) + "\n");
		
		System.out.print("------------------------\nPress Enter to Continue. ");
		try{
			in.readLine();
		} catch(Exception e){ System.err.println (e.getMessage ()); return; }
	}

}
